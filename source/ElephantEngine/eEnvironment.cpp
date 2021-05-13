#include <ElephantEngine/eEnvironment.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/eFogEnv.h>
#include <ElephantEngine/eLight.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eEnvironment interface
    // <kao2.0047D550> (constructor)
    // <kao2.0047D810> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_ENVIRONMENT_TYPEINFO
    (
        E_ENVIRONMENT_ID,
        "eEnvironment",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eEnvironment("UntitledEnvironment");
        }
    );

    const TypeInfo* eEnvironment::getType() const
    {
        return &E_ENVIRONMENT_TYPEINFO;
    }

    eEnvironment::eEnvironment(eString s)
    : eGroup(s, nullptr)
    {
        /*[0x54-0x60]*/
        unknown_54[0] = 0;
        unknown_54[1] = 0;
        unknown_54[2] = 0;
        unknown_54[3] = 1.0f;

        /*[0x64]*/ fog = nullptr;

    }

    eEnvironment::~eEnvironment()
    {
        /*[0x64]*/ fog->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: cloning the object
    ////////////////////////////////////////////////////////////////

    void eEnvironment::createFromOtherObject(const eEnvironment &other)
    {
        lights = other.lights;

        unknown_54[0] = other.unknown_54[0];
        unknown_54[1] = other.unknown_54[1];
        unknown_54[2] = other.unknown_54[2];
        unknown_54[3] = other.unknown_54[3];

        if (nullptr != other.fog)
        {
            fog = new eFogEnv(*(other.fog));
            fog->incRef();

            flags |= 0x00001000;
        }
        else
        {
            fog = nullptr;

            flags &= (~ 0x00001000);
        }
    }

    eEnvironment::eEnvironment(const eEnvironment &other)
    : eGroup(other)
    {
        createFromOtherObject(other);
    }

    eEnvironment& eEnvironment::operator = (const eEnvironment &other)
    {
        if ((&other) != this)
        {
            eGroup::operator = (other);

            /****************/

            fog->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eEnvironment::cloneFromMe() const
    {
        return new eEnvironment(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: serialization
    // <kao2.0047DBA0>
    ////////////////////////////////////////////////////////////////
    void eEnvironment::serialize(Archive &ar)
    {
        eGroup::serialize(ar);

        lights.serialize(ar, &E_LIGHT_TYPEINFO);

        /* [0x54] unknown */
        ar.readOrWrite(&(unknown_54[0]), 0x04);
        ar.readOrWrite(&(unknown_54[1]), 0x04);
        ar.readOrWrite(&(unknown_54[2]), 0x04);
        ar.readOrWrite(&(unknown_54[3]), 0x04);

        if (0x1000 & flags)
        {
            if (ar.getVersion() < 0x78)
            {
                throw ErrorMessage
                (
                    "eEnvironment::serialize()\n" \
                    "ar.version() 120 required!"
                );
            }

            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&fog, &E_FOGENV_TYPEINFO);
        }
        else
        {
            if (ar.isInReadMode())
            {
                fog->decRef();
                fog = nullptr;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: export readable structure
    ////////////////////////////////////////////////////////////////
    void eEnvironment::writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const
    {
        int32_t a, b;
        float dummy_floats[3];
        eNode* child_node;
        eString light_path;
        const char* light_type;
        char bufor[LARGE_BUFFER_SIZE];

        /* "eGroup": parent class */

        eGroup::writeStructureToTextFile(file, indentation, true);

        /* "eEnvironment": additional info */

        b = lights.getSize();

        for (a = 0; a < b; a++)
        {
            if (nullptr != (child_node = (eNode*)lights.getIthChild(a)))
            {
                light_path = child_node->getArchivePath();
                light_type = child_node->getType()->name;
            }
            else
            {
                light_path = "<EMPTY>";
                light_type = "";
            }

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                " - light [%d/%d]: (%s) \"%s\"",
                (a + 1),
                b,
                light_type,
                light_path.getText()
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);
        }

        if (nullptr != fog)
        {
            fog->getFogColor(dummy_floats);

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                " - fog color: (%.6f, %.6f, %.6f)",
                dummy_floats[0],
                dummy_floats[1],
                dummy_floats[2]
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);

            dummy_floats[0] = fog->getFogStart();
            dummy_floats[1] = fog->getFogEnd();
            dummy_floats[2] = fog->getFogMax();

            sprintf_s
            (
                bufor, LARGE_BUFFER_SIZE,
                " - fog start, end, max: (%.6f, %.6f, %.6f)",
                dummy_floats[0],
                dummy_floats[1],
                dummy_floats[2]
            );

            ArFunctions::writeIndentation(file, indentation);
            file << bufor;
            ArFunctions::writeNewLine(file, 0);
        }

        /****************/

        if (!group_written)
        {
            MACRO_KAO2_GROUP_FOREACH_NODE({ child_node->writeStructureToTextFile(file, (indentation + 1), false); })
        }
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: find reference to some node when deleting it
    ////////////////////////////////////////////////////////////////
    void eEnvironment::findAndDereference(eNode* target)
    {
        lights.findAndDeleteChild((eRefCounter*)target);

        eGroup::findAndDereference(target);
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: fixups after Node Clone pasting
    ////////////////////////////////////////////////////////////////
    void eEnvironment::assertNodeLinksSameArchive()
    {
        int32_t a;
        eLight* dummy_light;
        eGroup* root = getRootNode();

        for (a = 0; a < lights.getSize(); a++)
        {
            if (nullptr != (dummy_light = (eLight*)lights.getIthChild(a)))
            {
                if (dummy_light->getRootNode() != root)
                {
                    lights.deleteIthChild(a);
                    a--;
                }
            }
        }

        eGroup::assertNodeLinksSameArchive();
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: use lighting and render the child nodes
    ////////////////////////////////////////////////////////////////
    void eEnvironment::renderNode(eDrawContext &draw_context) const
    {
        int32_t valid_lights = 0;
        eLight* dummy_light;

        bool lights_enabled = (GUI::drawFlags::DRAW_FLAG_LIGHTING & draw_context.getDrawFlags());

        if (lights_enabled)
        {
            for (int32_t i = 0; i < lights.getSize(); i++)
            {
                dummy_light = (eLight*)lights.getIthChild(i);

                if (nullptr != dummy_light)
                {
                    draw_context.useLight(dummy_light);

                    valid_lights++;
                }
            }
        }

        eGroup::renderNode(draw_context);

        if (lights_enabled)
        {
            draw_context.decreaseLights(valid_lights);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eEnvironment::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test;
        float dummy_floats[3];
        eString prop_name;

        if (1 != (test = eGroup::parsingSetProperty(result_msg, property)))
        {
            return test;
        }

        prop_name = property.getName();

        if (prop_name.compareExact("fogColor", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorPropType(result_msg, "fogColor", TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            property.getValue(dummy_floats);

            setFogColor(dummy_floats);
            return 0;
        }
        else if (prop_name.compareExact("fogStart", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                dummy_floats[0] = (float)test;
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(dummy_floats);
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "fogStart", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            setFogStart(dummy_floats[0]);
            return 0;
        }
        else if (prop_name.compareExact("fogEnd", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                dummy_floats[0] = (float)test;
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(dummy_floats);
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "fogEnd", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            setFogEnd(dummy_floats[0]);
            return 0;
        }
        else if (prop_name.compareExact("fogMax", true))
        {
            if (property.checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                property.getValue(&test);
                dummy_floats[0] = (float)test;
            }
            else if (property.checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                property.getValue(dummy_floats);
            }
            else
            {
                TxtParsingNode_ErrorPropType(result_msg, "fogMax", TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            setFogMax(dummy_floats[0]);
            return 0;
        }

        return 1;
    }

    int32_t eEnvironment::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test;
        float dummy_floats[3];
        eLight* dummy_light = nullptr;

        if (1 != (test = eGroup::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test;
        }

        if (message.compareExact("clearLights", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "clearLights", 0);
                return 2;
            }

            /********************************/

            clearLighs();
            return 0;
        }
        else if (message.compareExact("addLight", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "addLight", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                TxtParsingNode_ErrorArgType(result_msg, "addLight", 0, TXT_PARSING_NODE_PROPTYPE_NODEREF);
                return 2;
            }

            /********************************/

            params[0].getValue(&dummy_light);

            if (nullptr == dummy_light)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"addLight\" message: noderef is not set!");
                return 2;
            }

            if (!(dummy_light->getType()->checkHierarchy(&E_LIGHT_TYPEINFO)))
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"addLight\" message: expected the noderef to be a child of \"eLight\"!");
                return 2;
            }

            /********************************/

            addLight(dummy_light);
            return 0;
        }
        else if (message.compareExact("removeLight", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "removeLight", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_NODEREF))
            {
                TxtParsingNode_ErrorArgType(result_msg, "removeLight", 0, TXT_PARSING_NODE_PROPTYPE_NODEREF);
                return 2;
            }

            /********************************/

            params[0].getValue(&dummy_light);

            if (nullptr == dummy_light)
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"removeLight\" message: noderef is not set!");
                return 2;
            }

            if (!(dummy_light->getType()->checkHierarchy(&E_LIGHT_TYPEINFO)))
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "\"removeLight\" message: expected the noderef to be a child of \"eLight\"!");
                return 2;
            }

            /********************************/

            removeLight(dummy_light);
            return 0;
        }
        else if (message.compareExact("setFogColor", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setFogColor", 1);
                return 2;
            }

            /********************************/

            if (!params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT3))
            {
                TxtParsingNode_ErrorArgType(result_msg, "setFogColor", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT3);
                return 2;
            }

            params[0].getValue(dummy_floats);

            /********************************/

            setFogColor(dummy_floats);
            return 0;
        }
        else if (message.compareExact("setFogStart", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setFogStart", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&test);
                dummy_floats[0] = (float)test;
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(dummy_floats);
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setFogStart", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            setFogStart(dummy_floats[0]);
            return 0;
        }
        else if (message.compareExact("setFogEnd", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setFogEnd", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&test);
                dummy_floats[0] = (float)test;
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(dummy_floats);
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setFogEnd", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            setFogEnd(dummy_floats[0]);
            return 0;
        }
        else if (message.compareExact("setFogMax", true))
        {
            if (1 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "setFogMax", 1);
                return 2;
            }

            /********************************/

            if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_INTEGER))
            {
                params[0].getValue(&test);
                dummy_floats[0] = (float)test;
            }
            else if (params[0].checkType(TXT_PARSING_NODE_PROPTYPE_FLOAT1))
            {
                params[0].getValue(dummy_floats);
            }
            else
            {
                TxtParsingNode_ErrorArgType(result_msg, "setFogMax", 0, TXT_PARSING_NODE_PROPTYPE_FLOAT1);
                return 2;
            }

            /********************************/

            setFogMax(dummy_floats[0]);
            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: add or remove a lighting source
    ////////////////////////////////////////////////////////////////

    void eEnvironment::clearLighs()
    {
        lights.clear();
    }

    void eEnvironment::addLight(eLight* new_light)
    {
        int32_t a, b = lights.getSize();

        if (nullptr != new_light)
        {
            for (a = 0; a < b; a++)
            {
                if (lights.getIthChild(a) == new_light)
                {
                    return;
                }
            }

            lights.appendChild(new_light);
        }
    }

    void eEnvironment::removeLight(eLight* selected_light)
    {
        if (nullptr != selected_light)
        {
            lights.findAndDeleteChild(selected_light);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eEnvironment: fog editing
    ////////////////////////////////////////////////////////////////

    void eEnvironment::setFogColor(float* values)
    {
        if (nullptr == fog)
        {
            fog = new eFogEnv();
            fog->incRef();
        }

        flags |= 0x00001000;

        fog->setFogColor(values);
    }

    void eEnvironment::setFogStart(float value)
    {
        if (nullptr == fog)
        {
            fog = new eFogEnv();
            fog->incRef();
        }

        flags |= 0x00001000;

        fog->setFogStart(value);
    }

    void eEnvironment::setFogEnd(float value)
    {
        if (nullptr == fog)
        {
            fog = new eFogEnv();
            fog->incRef();
        }

        flags |= 0x00001000;

        fog->setFogEnd(value);
    }

    void eEnvironment::setFogMax(float value)
    {
        if (nullptr == fog)
        {
            fog = new eFogEnv();
            fog->incRef();
        }

        flags |= 0x00001000;

        fog->setFogMax(value);
    }

}
