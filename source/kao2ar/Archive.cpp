#include <kao2ar/Archive.h>
#include <kao2ar/eObject.h>

#include <kao2engine/Log.h>
#include <kao2engine/eScene.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AR HELPER FUNCTION: get path based on game version
    ////////////////////////////////////////////////////////////////
    eString ArFunctions::getFullArchivePath(const eString &filename, const eString &media_dir, int32_t engine_version, int32_t flags)
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
                switch (engine_version)
                {
                    case GAME_VERSION_ASTERIX_XXL2_PSP:
                    case GAME_VERSION_KAO_TW_PC:
                    {
                        result += "build/pc/";
                        break;
                    }

                    default:
                    {
                        result += "build/win32/";
                    }
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

        engineOpenedWith = (-1);
        engineSavedWith = (-1);

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
    bool Archive::open(eString path, int32_t mode, int32_t engine_version, int32_t ver_max_override)
    {
        int32_t a;
        int32_t ver_min;
        int32_t ver_max;

        switch (engine_version)
        {
            case GAME_VERSION_KAO2_PL_PC:
            {
                ver_min = 0x67;
                ver_max = 0x87;

                break;
            }

            case GAME_VERSION_KAO2_EUR_PC:
            {
                ver_min = 0x67;
                ver_max = 0x89;

                break;
            }

            case GAME_VERSION_KAO_TW_PC:
            {
                ver_min = 0x8B;
                ver_max = 0x90;

                break;
            }

            case GAME_VERSION_ASTERIX_XXL2_PSP:
            {
                ver_min = 0x8B;
                ver_max = 0x93;

                break;
            }

            default:
            {
                throw ErrorMessage
                (
                    "Archive::open():\n" \
                    "Engine version has not been set!\n" \
                    "Please select one from a drop-down menu."
                );

                return false;
            }
        }

        /* Remember mode flags, construct file path, remember engine version, open file. */

        modeFlags = mode;

        if (isInReadMode())
        {
            theLog.print(eString(" @ ARCHIVE: READING \"") + path + "\"\n");

            engineOpenedWith = engine_version;
            engineSavedWith = engine_version;

            a = (FILE_OPERATOR_MODE_BINARY | FILE_OPERATOR_MODE_READ);
        }
        else if (isInWriteMode())
        {
            theLog.print(eString(" @ ARCHIVE: SAVING \"") + path + "\"\n");

            engineSavedWith = engine_version;

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
                path.getFilename(true).getText()
            );

            return false;
        }

        /* [0x04] Check or save version */

        if (false == isInReadMode())
        {
            if ((ver_max_override >= ver_min) && (ver_max_override < ver_max))
            {
                ver_max = ver_max_override;
            }

            version = ver_max;
        }

        readOrWrite(&version, 0x04);

        if (isInReadMode() && ((version < ver_min) || (version > ver_max)))
        {
            throw ErrorMessage
            (
                "[%s]\n" \
                "invalid archive version %i\n" \
                "(current version: %i, minimum: %i).",
                path.getFilename(true).getText(), version, ver_max, ver_min
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
                path.getFilename(true).getText(),
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

        ArFunctions::serialize_eRefCounter(*this, &parentObject, &E_REFCOUNTER_TYPEINFO);

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
            /* Now we can just set output version to the maximum supported by current engine */
            version = ver_max;

            selectedObject = parentObject;

            if ((nullptr != parentObject) && parentObject->getType()->checkHierarchy(&E_NODE_TYPEINFO))
            {
                if (0 == (AR_MODE_SKIP_PROXIES & modeFlags))
                {
                    ((eNode*)parentObject)->reloadXRef(mediaDirectory, engine_version);
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

    bool Archive::checkGameEngine(int32_t opened, int32_t saved) const
    {
        bool result = true;

        /* Compare versions in which the Archive has been opened */
        switch (opened)
        {
            case GAME_VERSION_KAO2_PL_PC:
            case GAME_VERSION_KAO2_EUR_PC:
            case GAME_VERSION_KAO_TW_PC:
            case GAME_VERSION_ASTERIX_XXL2_PSP:
            {
                result &= (opened == engineOpenedWith);

                break;
            }
        }

        /* Compare versions in which the Archive is being saved */
        switch (saved)
        {
            case GAME_VERSION_KAO2_PL_PC:
            case GAME_VERSION_KAO2_EUR_PC:
            case GAME_VERSION_KAO_TW_PC:
            case GAME_VERSION_ASTERIX_XXL2_PSP:
            {
                result &= (saved == engineSavedWith);

                break;
            }
        }

        return result;
    }

    int32_t Archive::getCurrentEngineVersion() const
    {
        if (isInReadMode())
        {
            return engineOpenedWith;
        }
        else
        {
            return engineSavedWith;
        }
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
    // Archive: Main serializaion function
    // <kao2.00464D00>
    ////////////////////////////////////////////////////////////////
    void Archive::serialize(eObject** o, TypeInfo* t)
    {
        int32_t a;
        TypeInfo* current_type;
        eObject* current_object;

        if (isInReadMode())
        {
            /* Get instruction type */

            readOrWrite(&a, 0x04);

            switch (a)
            {
                case 0x00:
                {
                    /* Find object from ID */

                    readOrWrite(&a, 0x04);

                    current_type = InterfaceManager.getTypeInfo(a);

                    /* Safety check (NOT PRESENT IN GAME): is the new object a subclass of certain type? */

                    if (nullptr != t)
                    {
                        if (!current_type->checkHierarchy(t))
                        {
                            throw ErrorMessage
                            (
                                "Archive::serialize():\n" \
                                "Wrong object type in archive!\n\n" \
                                "Expected: 0x%08X - %s\n" \
                                "TypeInfo: 0x%08X - %s.",
                                t->id,
                                t->name,
                                current_type->id,
                                current_type->name
                            );

                            return;
                        }
                    }

                    /* Create, store back, then check object */

                    current_object = current_type->create();

                    (*o) = current_object;

                    if (nullptr == current_object)
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

                    addItem(current_object, AR_ITEM_TYPE_OBJECT);

                    /* Serialize object */

                    current_object->serialize(*this);

                    if (isInDebugMode())
                    {
                        theLog.print(current_object);
                    }

                    return;
                }

                case 0x01:
                {
                    /* Empty object */

                    (*o) = nullptr;

                    return;
                }

                default:
                {
                    /* Get object pointer from temporary list */

                    current_object = (eObject*)getItem((a - 2), AR_ITEM_TYPE_OBJECT);

                    /* Safety check (NOT PRESENT IN GAME): is the new object a subclass of certain type? */

                    current_type = current_object->getType();

                    if (nullptr != t)
                    {
                        if (!current_type->checkHierarchy(t))
                        {
                            throw ErrorMessage
                            (
                                "Archive::serialize():\n" \
                                "Wrong object type in archive!\n\n" \
                                "Expected: 0x%08X - %s\n" \
                                "TypeInfo: 0x%08X - %s.",
                                t->id,
                                t->name,
                                current_type->id,
                                current_type->name
                            );

                            return;
                        }
                    }

                    (*o) = current_object;

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
                    readOrWrite(&(current_type->id), 0x04);

                    /* Deserialize object */

                    (*o)->serialize(*this);

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
            if (nullptr != s.getPointer())
            {
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
            else
            {
                throw ErrorMessage
                (
                    "Archive::serializeString():\n" \
                    "Empty String pointers are not supported by Kao2 engine!"
                );
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
    // Archive: Compare some object with current root
    ////////////////////////////////////////////////////////////////
    bool Archive::compareWithMyRoot(eRefCounter* object) const
    {
        return (parentObject == object);
    }


    ////////////////////////////////////////////////////////////////
    // Archive: Check TypeInfo without serialization
    // <kao2.00463130>
    ////////////////////////////////////////////////////////////////
    void Archive::checkTypeInfo(TypeInfo** t)
    {
        int32_t index = 0;

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
                (*t) = InterfaceManager.getTypeInfo(index);

                return;
            }
        }
        else
        {
            if (nullptr != (*t))
            {
                /* TypeInfo exists */
                readOrWrite(&((*t)->id), 0x04);
            }
            else
            {
                /* Write empty ID */
                readOrWrite(&index, 0x04);
            }
        }
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
        mediaDirectory = new_media_dir;
        mediaDirectory.assertPath();
    }

}
