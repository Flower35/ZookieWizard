#include <ElephantBase/Archive.h>
#include <ElephantBase/eObject.h>

#include <ElephantEngine/Log.h>
#include <ElephantEngine/eScene.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AR HELPER FUNCTION: get path based on game version
    ////////////////////////////////////////////////////////////////
    eString ArFunctions::getFullArchivePath(const eString &filename, const eString &media_dir, int32_t ar_version, int32_t flags)
    {
        eString result;

        if (0 == (AR_MODE_ABSOLUTE_PATH & flags))
        {
            result = media_dir;
            result.assertPath();

            if (AR_MODE_PARTICLES_PATH & flags)
            {
                result += "particle/";
            }
            else if (0 == (AR_MODE_XREF_PATH & flags))
            {
                if (ar_version >= 0x8B)
                {
                    result += "build/pc/";
                }
                else
                {
                    result += "build/win32/";
                }
            }
        }

        return (result + filename);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Constructors
    ////////////////////////////////////////////////////////////////

    Archive::Archive()
    : Archive(eString(-1))
    {}

    Archive::Archive(eString new_media_dir)
    {
        modeFlags = 0;

        tempItemsCount = 0;
        tempItemsList = nullptr;
        tempItemsTypes = nullptr;

        tempStrCount = 0;
        tempStrList = nullptr;

        parentObject = nullptr;
        selectedObject = nullptr;
        markedChildId = (-1);

        /* Set working directory */

        setMediaDir(new_media_dir);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Deconstructor
    ////////////////////////////////////////////////////////////////
    Archive::~Archive()
    {
        destroyParent();

        if (nullptr != tempStrList)
        {
            deleteTempStrPtrs();

            delete[](tempStrList);
            tempStrList = nullptr;
        }

        if (nullptr != tempItemsList)
        {
            delete[](tempItemsList);
            tempItemsList = nullptr;
        }

        if (nullptr != tempItemsTypes)
        {
            delete[](tempItemsTypes);
            tempItemsTypes = nullptr;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: check if this Archive is loaded
    ////////////////////////////////////////////////////////////////
    bool Archive::isNotEmpty() const
    {
        return (nullptr != parentObject);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: open for reading or writing
    ////////////////////////////////////////////////////////////////
    bool Archive::open(eString path, int32_t mode, int32_t version_override)
    {
        int32_t a;

        /* Remember mode flags, construct file path, open file. */

        modeFlags = mode;

        baseFileName = path.getFilename(true);

        if (isInReadMode())
        {
            theLog.print(eString(" @ ARCHIVE: READING \"") + path + "\"\n");

            a = (FILE_OPERATOR_MODE_BINARY | FILE_OPERATOR_MODE_READ);
        }
        else if (isInWriteMode())
        {
            theLog.print(eString(" @ ARCHIVE: SAVING \"") + path + "\"\n");

            a = (FILE_OPERATOR_MODE_BINARY);
        }
        else
        {
            throw ErrorMessage
            (
                "Archive::open()\n" \
                "unrecognized opening mode!"
            );

            return false;
        }

        /* NOT in Read mode = Write OR Export modes */
        if (false == isInReadMode())
        {
            myFile.setDir(path.getText());
            myFile.createDir();
        }

        if (!myFile.open(path.getText(), a))
        {
            throw ErrorMessage
            (
                "Archive::open():\n" \
                "Could not open file:\n" \
                "\"%s\"",
                path.getText()
            );

            return false;
        }

        /* [0x00] Check or save archive header */

        a = *(uint32_t*)"tate";

        readOrWrite(&a, 0x04);

        if (isInReadMode() && (*(uint32_t*)"tate" != a))
        {
            throw ErrorMessage
            (
                "[%s]\n" \
                "invalid archive magic. Expected \"tate\".",
                baseFileName.getText()
            );

            return false;
        }

        /* [0x04] Check or save version */

        if (false == isInReadMode())
        {
            if ((version_override >= ARCHIVE_VERSION_MIN) && (version_override < ARCHIVE_VERSION_MAX))
            {
                version = version_override;
            }
            else
            {
                version = ARCHIVE_VERSION_MAX;
            }
        }

        readOrWrite(&version, 0x04);

        if (isInReadMode() && ((version < ARCHIVE_VERSION_MIN) || (version > ARCHIVE_VERSION_MAX)))
        {
            throw ErrorMessage
            (
                    "[%s]\n" \
                    "invalid archive version [%i] (0x%02X) !!!\n" \
                    "minimal supported version: [%i] (0x%02X)\n" \
                    "maximal supported version: [%i] (0x%02X)",
                path.getText(),
                version, version,
                ARCHIVE_VERSION_MIN, ARCHIVE_VERSION_MIN,
                ARCHIVE_VERSION_MAX, ARCHIVE_VERSION_MAX
            );

            return false;
        }

        /* [0x08] Check or save Temporary Pointers list size */

        tempItemsMaxLength = AR_MAX_ITEMS;

        readOrWrite(&tempItemsMaxLength, 0x04);

        if (isInReadMode() && ((tempItemsMaxLength < 1) || (tempItemsMaxLength > AR_MAX_ITEMS)))
        {
            throw ErrorMessage
            (
                "[%s]\n" \
                "Incorrect number of temporary class fields.\n" \
                "(max: %d)",
                path.getText(),
                AR_MAX_ITEMS
            );

            return false;
        }

        /* Allocate size for temporary object pointers */

        try
        {
            if (nullptr == tempItemsList)
            {
                tempItemsList = new void* [AR_MAX_ITEMS];
            }

            if (nullptr == tempItemsTypes)
            {
                tempItemsTypes = new uint8_t [AR_MAX_ITEMS];
            }

            if (nullptr == tempStrList)
            {
                tempStrList = new eStringBase<char>* [AR_MAX_TEMPSTR];
            }
        }
        catch (std::bad_alloc &error)
        {
            throw ErrorMessage
            (
                "Archive::open():\n" \
                "Memory allocation error.\n" \
                "%s",
                error.what()
            );

            return false;
        }

        /* Begin serialization */

        tempItemsCount = 0;

        lastSerializedNode = nullptr;

        ArFunctions::serialize_eRefCounter(*this, &parentObject, &E_REFCOUNTER_TYPEINFO);

        lastSerializedNode = nullptr;

        if (isInWriteMode())
        {
            /* Finally, update temp list size */
            myFile.setPointer(0x08);
            readOrWrite(&tempItemsCount, 0x04);
        }

        /* Close the "*.ar" file */
        close(false);

        if (isInReadMode())
        {
            selectedObject = parentObject;

            if ((nullptr != parentObject) && parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
            {
                if (0 == (AR_MODE_SKIP_PROXIES & modeFlags))
                {
                    ((eNode*)parentObject)->reloadXRef(mediaDirectory, version);
                }
                else
                {
                    modeFlags &= (~AR_MODE_SKIP_PROXIES);
                }
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Close
    ////////////////////////////////////////////////////////////////
    void Archive::close(bool hide)
    {
        if (hide)
        {
            selectedObject = nullptr;

            destroyParent();
        }

        myFile.close();

        deleteTempStrPtrs();
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Checking modes
    ////////////////////////////////////////////////////////////////

    bool Archive::isInReadMode() const
    {
        return (AR_MODE_READ & modeFlags);
    }

    bool Archive::isInWriteMode() const
    {
        return (AR_MODE_WRITE & modeFlags);
    }

    bool Archive::isInDebugMode() const
    {
        return (AR_MODE_DEBUG & modeFlags);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Checking versions
    ////////////////////////////////////////////////////////////////

    int32_t Archive::getVersion() const
    {
        return version;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Insert new temporary class
    // <kao2.004651C0>
    ////////////////////////////////////////////////////////////////
    bool Archive::addItem(void* item, int type)
    {
        if (tempItemsCount >= tempItemsMaxLength)
        {
            throw ErrorMessage
            (
                "Archive initialized incorrectly?\n" \
                "Not enough space for temporary classes!\n" \
                "(current size: %d)",
                tempItemsMaxLength
            );

            return false;
        }

        tempItemsList[tempItemsCount] = item;
        tempItemsTypes[tempItemsCount] = type;

        tempItemsCount++;

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Get stored temporary class
    // <kao2.00465290>
    ////////////////////////////////////////////////////////////////
    void* Archive::getItem(int id, int type) const
    {
        if ((id < 0) || (id >= tempItemsCount))
        {
            throw ErrorMessage
            (
                "Incorrect temporary item ID...\n" \
                "THIS SHOULD NEVER HAPPEN !!!"
            );

            return nullptr;
        }

        if (type != tempItemsTypes[id])
        {
            throw ErrorMessage
            (
                "Incorrect temporary item type...\n" \
                "THIS SHOULD NEVER HAPPEN !!!"
            );
        }

        return tempItemsList[id];
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Find class pointer in write mode
    // <kao2.00465240>
    ////////////////////////////////////////////////////////////////
    int Archive::findItem(void* item) const
    {
        for (int i = 0; i < tempItemsCount; i++)
        {
            if (tempItemsList[i] == item)
            {
                return i;
            }
        }

        return (-1);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Insert previous string copy
    ////////////////////////////////////////////////////////////////
    bool Archive::addTempStr(eStringBase<char>* str)
    {
        if (tempStrCount >= AR_MAX_TEMPSTR)
        {
            throw ErrorMessage
            (
                "Archive contains too many unnamed Gadgets!\n" \
                "Not enough space for another string reference!\n" \
                "(current size: %d)",
                AR_MAX_TEMPSTR
            );

            return false;
        }

        tempStrList[tempStrCount] = str;
        tempStrCount++;

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Read or write some data
    ////////////////////////////////////////////////////////////////
    void Archive::readOrWrite(void* pointer, int size)
    {
        if (isInReadMode())
        {
            myFile.read(pointer, size);
        }
        else if (isInWriteMode())
        {
            myFile.write(pointer, size);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: assert the correct object type during serialiation
    // (this check is NOT present in the games!)
    ////////////////////////////////////////////////////////////////
    void Archive::assertObjectType(const TypeInfo* expected_type, const TypeInfo* current_type) const
    {
        if (nullptr != expected_type)
        {
            if (!current_type->checkHierarchy(expected_type))
            {
                throw ErrorMessage
                (
                    "Archive::serialize():\n" \
                    "Wrong object type in archive!\n\n" \
                    "Expected: 0x%08X - %s\n" \
                    "TypeInfo: 0x%08X - %s.",
                    expected_type->id,
                    expected_type->name,
                    current_type->id,
                    current_type->name
                );
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Main serializaion function
    // <kao2.00464D00>
    ////////////////////////////////////////////////////////////////
    void Archive::serialize(eObject** o, const TypeInfo* t)
    {
        int32_t a;
        const TypeInfo* current_type;

        eNode* stacked_node = nullptr;
        bool has_node_type;

        try
        {
            try
            {
                if (isInReadMode())
                {
                    /* Get instruction type */

                    readOrWrite(&a, 0x04);

                    switch (a)
                    {
                        case 0:
                        {
                            /* Find object from ID */

                            readOrWrite(&a, 0x04);

                            current_type = theElephantInterfaces.getTypeInfo(a);

                            assertObjectType(t, current_type);

                            has_node_type = current_type->checkHierarchy(&E_NODE_TYPEINFO);

                            /* Create, store back, then check object */

                            (*o) = current_type->create();

                            if (nullptr == (*o))
                            {
                                throw ErrorMessage
                                (
                                    "Archive::serialize():\n" \
                                    "abstract object deserialization [TypeInfo: 0x%08X - %s]",
                                    current_type->id,
                                    current_type->name
                                );

                                return;
                            }

                            /* Add object to the temporary list */

                            addItem((*o), AR_ITEM_TYPE_OBJECT);

                            /* Serialize object */

                            if (has_node_type)
                            {
                                stacked_node = lastSerializedNode;
                            }

                            (*o)->serialize(*this);

                            if (has_node_type)
                            {
                                lastSerializedNode = stacked_node;
                            }

                            return;
                        }

                        case 1:
                        {
                            /* Empty object */

                            (*o) = nullptr;

                            return;
                        }

                        default:
                        {
                            /* Get object pointer from temporary list */

                            (*o) = (eObject*)getItem((a - 2), AR_ITEM_TYPE_OBJECT);

                            assertObjectType(t, (*o)->getType());

                            return;
                        }
                    }
                }
                else
                {
                    if (nullptr != (*o))
                    {
                        /* Check if objet ID already exists */

                        a = findItem(*o);

                        if (a < 0)
                        {
                            /* Item was not found and it needs to be serialized */

                            addItem((*o), AR_ITEM_TYPE_OBJECT);

                            current_type = (*o)->getType();

                            has_node_type = current_type->checkHierarchy(&E_NODE_TYPEINFO);

                            if (nullptr == current_type)
                            {
                                throw ErrorMessage
                                (
                                    "Archive::serialize():\n" \
                                    "abstract object serialization!"
                                );

                                return;
                            }

                            a = 0x00;
                            readOrWrite(&a, 0x04);
                            readOrWrite((void *)&(current_type->id), 0x04);

                            /* Deserialize object */

                            if (has_node_type)
                            {
                                stacked_node = lastSerializedNode;
                            }

                            (*o)->serialize(*this);

                            if (has_node_type)
                            {
                                lastSerializedNode = stacked_node;
                            }

                            return;
                        }
                        else
                        {
                            /* Write object ID */

                            a += 2;
                            readOrWrite(&a, 0x04);

                            return;
                        }
                    }
                    else
                    {
                        /* This object is empty */
                        a = 0x01;
                        readOrWrite(&a, 0x04);

                        return;
                    }
                }
            }
            catch (std::bad_alloc)
            {
                throw ErrorMessage("Memory allocation error!");
            }
        }
        catch (ErrorMessage &err)
        {
            if (!err.wasHeaderAppended())
            {
                err.appendHeader("[%s]\n(offset 0x%08X)", myFile.currentPath, myFile.getPointer());
            }

            throw;
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Read to a string
    // <kao2.00462120>
    ////////////////////////////////////////////////////////////////
    eString ArFunctions::readString(Archive &ar)
    {
        int32_t length;
        ar.readOrWrite(&length, 0x04);

        eString s(length);
        ar.readOrWrite(s.getText(), length);

        return s;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Write from a string
    // <kao2.00462180>
    ////////////////////////////////////////////////////////////////
    void ArFunctions::writeString(Archive &ar, eString &s)
    {
        int32_t length = s.getLength();
        ar.readOrWrite(&length, 0x04);

        ar.readOrWrite(s.getText(), length);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: String serialization
    // <kao2.004621E0>
    ////////////////////////////////////////////////////////////////
    void Archive::serializeString(eString &s)
    {
        int32_t a;
        eString test_str;

        if (isInReadMode())
        {
            /* Do NOT decrease reference here, because we will use "copy constructor" in `case 0`. */

            readOrWrite(&a, 0x04);

            switch (a)
            {
                case 0x00:
                {
                    s = ArFunctions::readString(*this);

                    addItem(s.getPointer(), AR_ITEM_TYPE_STRING);

                    return;
                }

                case 0x01:
                {
                    s.decRef();

                    s.setPointer(nullptr);

                    return;
                }

                default:
                {
                    s.decRef();

                    s.setPointer((eStringBase<char>*)getItem((a - 2), AR_ITEM_TYPE_STRING));

                    /* Each `eString` is created with reference counter = 1. */
                    /* Here, we have to manually increase reference, because we only copy direct pointer. */
                    /* Assign operator works fine, too, but we already decreased reference at the beginning. */

                    s.incRef();

                    return;
                }
            }
        }
        else
        {
            if (nullptr == s.getPointer())
            {
                /* Kao2 engine doesn't accept Strings with `NULLPTR` bases, */
                /* so we will have to replace them with new zero-length text. */

                s = eString(0);
            }

            /* Find identical Strings to save up memory */

            for (a = 0; a < tempItemsCount; a++)
            {
                if (AR_ITEM_TYPE_STRING == tempItemsTypes[a])
                {
                    if (s.getPointer() != tempItemsList[a])
                    {
                        test_str.setPointer((eStringBase<char>*)tempItemsList[a]);

                        if (s.compareExact(test_str, true))
                        {
                            /* Copy constructor takes care of both reference counters */
                            s = test_str;

                            /* Break out of the loop */
                            a = tempItemsCount;
                        }

                        /* Manually destroy the test string, because deconstructor would decrease refCounter! */
                        test_str.setPointer(nullptr);
                    }
                }
            }

            /* Continue with normal deserialization */

            a = findItem(s.getPointer());

            if (a < 0)
            {
                addItem(s.getPointer(), AR_ITEM_TYPE_STRING);

                a = 0x00;
                readOrWrite(&a, 0x04);

                ArFunctions::writeString(*this, s);

                return;
            }
            else
            {
                a += 2;
                readOrWrite(&a, 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: replace old string pointer during serialization!
    ////////////////////////////////////////////////////////////////
    void Archive::replaceStringDuringSerialization(eString &oldStr, eString newStr)
    {
        /* Some Gadgets could break, if we change their name WHILE */
        /* old String pointers are still present in Archive's "temporary array". */

        bool alreadyAdded = false;
        int32_t i;
        eStringBase<char>* thatPointer = oldStr.getPointer();

        for (i = 0; (false == alreadyAdded) && (i < tempStrCount); i++)
        {
            alreadyAdded = (thatPointer == tempStrList[i]);
        }

        if (false == alreadyAdded)
        {
            /* Before replacement (which decreases old reference counter) */
            /* we need to keep old string intact, because */
            /* zero-length strings usually share same IDs */

            oldStr.incRef();
            addTempStr(thatPointer);
        }

        oldStr = newStr;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Asserting objects in read mode
    ////////////////////////////////////////////////////////////////

    bool Archive::compareWithMyRoot(const eRefCounter* object) const
    {
        return (parentObject == object);
    }

    eNode* Archive::getLastSerializedNode() const
    {
        return lastSerializedNode;
    }

    void Archive::setLastSerializedNode(eNode* node)
    {
        lastSerializedNode = node;
    }

    bool Archive::assertLastSerializedNode(const eNode* node) const
    {
        return (node == lastSerializedNode);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Check TypeInfo without serialization
    // <kao2.00463130>
    ////////////////////////////////////////////////////////////////
    void Archive::checkTypeInfo(const TypeInfo** t)
    {
        uint32_t index = 0;

        if (isInReadMode())
        {
            /* Get index */
            readOrWrite(&index, 0x04);

            if (0 == index)
            {
                (*t) = nullptr;

                return;
            }
            else
            {
                /* Non-empty index */
                (*t) = theElephantInterfaces.getTypeInfo(index);

                return;
            }
        }
        else
        {
            if (nullptr != (*t))
            {
                /* TypeInfo exists */
                readOrWrite((void*)&((*t)->id), 0x04);
            }
            else
            {
                /* Write empty ID */
                readOrWrite(&index, 0x04);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Archive: get Base File Name
    ////////////////////////////////////////////////////////////////
    eString Archive::getBaseFileName() const
    {
        return baseFileName;
    }


    ////////////////////////////////////////////////////////////////
    // Archive: get or set Media Directory path
    ////////////////////////////////////////////////////////////////

    eString Archive::getMediaDir() const
    {
        return mediaDirectory;
    }

    void Archive::setMediaDir(eString new_media_dir)
    {
        mediaDirectory = new_media_dir.trimWhitespace();
        mediaDirectory.assertPath();
    }

}
