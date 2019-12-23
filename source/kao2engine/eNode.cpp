#include <kao2engine/eNode.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eALBox.h>
#include <kao2engine/eScene.h>
#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eNode interface
    // <kao2.00478AD0> (overloaded constructor)
    // <kao2.004789C0> (constructor)
    // <kao2.00478D50> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_NODE_TYPEINFO
    (
        E_NODE_ID,
        "eNode",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eNode;
        }
    );

    TypeInfo* eNode::getType()
    {
        return &E_NODE_TYPEINFO;
    }

    eNode::eNode(eString s, eNode* x)
    : ePrimitive()
    {
        /*[0x08]*/ scene = nullptr;
        /*[0x0C]*/ unknown_0C = 0x00FFFFFF;
        /*[0x10]*/ parent = nullptr;
        /*[0x14]*/ name = s;
        /*[0x18]*/ unknown_18 = nullptr;
        /*[0x1C]*/ flags = 0x249D;
        /*[0x30]*/ flags02 = 0x00FF;
        /*[0x34]*/ unknown_34 = nullptr;
        /*[0x2C]*/ sphBound[3] = -1.0f;

        if (nullptr != x)
        {
            /* TODO: "kao2.00478B55 -- CALL 00478E00" */
        }
    }

    eNode::eNode()
    : ePrimitive()
    {
        /*[0x08]*/ scene = nullptr;
        /*[0x0C]*/ unknown_0C = 0x00FFFFFF;
        /*[0x10]*/ parent = nullptr;
        /*[0x18]*/ unknown_18 = nullptr;
        /*[0x1C]*/ flags = 0x249D;
        /*[0x30]*/ flags02 = 0x00FF;
        /*[0x34]*/ unknown_34 = nullptr;
        /*[0x2C]*/ sphBound[3] = -1.0f;

        visGroup = (-1);
    }

    eNode::~eNode()
    {
        unknown_34->decRef();

        unknown_18->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eNode serialization
    // <kao2.00478FF0>
    ////////////////////////////////////////////////////////////////
    void eNode::serialize(Archive &ar)
    {
        eGeometry* test_object;
        ePoint3 test_boundary[2];

        /* Node name and node parent */

        ar.serializeString(name);

        ar.serialize((eObject**)&parent, &E_NODE_TYPEINFO);

        ar.readOrWrite(&unknown_0C, 0x04);

        if (ar.getVersion() <= 0x55)
        {
            throw ErrorMessage
            (
                "eNode::serialize():\n" \
                "ar.version() 86 required!"
            );
        }
        
        if (ar.getVersion() < 0x82)
        {
            test_boundary[0].serialize(ar);
            test_boundary[1].serialize(ar);

            if (getType()->checkHierarchy(&E_GEOMETRY_TYPEINFO))
            {
                test_object = (eGeometry*)this;

                test_object->oldNodeSerialization(test_boundary);
            }
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_18, &E_ALBOX_TYPEINFO);

        ar.readOrWrite(&flags, 0x04);

        ar.readOrWrite(&(sphBound[0]), 0x04);
        ar.readOrWrite(&(sphBound[1]), 0x04);
        ar.readOrWrite(&(sphBound[2]), 0x04);
        ar.readOrWrite(&(sphBound[3]), 0x04);

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_34, &E_REFCOUNTER_TYPEINFO);

        ar.readOrWrite(&flags02, 0x02);

        if (false == ar.isInReadMode())
        {
            flags02 |= 0x2000;
        }

        /* From "Kao Challengers" */

        if (ar.getVersion() < 0x8D)
        {
            visGroup = (-1);
        }
        else if (ar.getVersion() < 0x90)
        {
            int16_t x = visGroup;
            ar.readOrWrite(&x, 0x02);
            visGroup = x;
        }
        else
        {
            ar.readOrWrite(&visGroup, 0x04);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get name
    ////////////////////////////////////////////////////////////////
    eString eNode::getStringRepresentation()
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: set name
    ////////////////////////////////////////////////////////////////
    void eNode::setName(eString new_name)
    {
        name = new_name;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: get parent node
    ////////////////////////////////////////////////////////////////
    eNode* eNode::getParentNode()
    {
        return parent;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: set parent node
    ////////////////////////////////////////////////////////////////
    void eNode::setParentNode(eNode* new_parent)
    {
        parent = new_parent;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: apply or erase flag bits
    ////////////////////////////////////////////////////////////////

    void eNode::setFlags(int32_t bits_to_apply)
    {
        flags |= bits_to_apply;
    }

    void eNode::unsetFlags(int32_t bits_to_erase)
    {
        flags &= (~bits_to_erase);
    }


    ////////////////////////////////////////////////////////////////
    // eNode: print
    ////////////////////////////////////////////////////////////////
    eString eNode::getLogPrintMessage()
    {
        eString result = eObject::getLogPrintMessage();

        result += "\n - \"";
        result += name;
        result += "\"";

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eNode: export readable structure
    ////////////////////////////////////////////////////////////////
    void eNode::writeStructureToTextFile(FileOperator &file, int32_t indentation)
    {
        char bufor[512];
        TypeInfo* info = getType();

        sprintf_s
        (
            bufor,
            512,
            "[%08X] %s (\"%s\")",
            info->id,
            info->name,
            name.getText()
        );

        ArFunctions::writeNewLine(file, indentation);
        file << bufor;


        sprintf_s
        (
            bufor,
            512,
            " - flags: %08X",
            flags
        );

        ArFunctions::writeNewLine(file, indentation);
        file << bufor;

        if (nullptr != parent)
        {
            info = parent->getType();

            sprintf_s
            (
                bufor,
                512,
                " - parent: [%08X] %s (\"%s\")",
                info->id,
                info->name,
                parent->getStringRepresentation().getText()
            );

            ArFunctions::writeNewLine(file, indentation);
            file << bufor;
        }

        if (nullptr != unknown_18)
        {
            info = unknown_18->getType();

            sprintf_s
            (
                bufor,
                512,
                " - albox: [%08X] %s (ptr=%08X)",
                info->id,
                info->name,
                (int32_t)unknown_18
            );

            ArFunctions::writeNewLine(file, indentation);
            file << bufor;
        }

        ArFunctions::writeNewLine(file, 0);
    }

}
