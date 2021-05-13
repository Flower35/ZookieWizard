#include <ElephantEngine/Property.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/Gadget.h>

#include <ElephantBase/Collection.h>
#include <ElephantBase/ArTemplates.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Property interface
    // <kao2.005922A0> (constructor)
    // <kao2.005923A0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PROPERTY_TYPEINFO
    (
        E_PROPERTY_ID,
        "Property",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new Property;
        }
    );

    const TypeInfo* Property::getType() const
    {
        return &E_PROPERTY_TYPEINFO;
    }

    Property::Property()
    : eRefCounter()
    {
        /*[0x0C]*/ type = 0;
        /*[0x10]*/ numValue = nullptr;
        /*[0x18]*/ unknown_18 = nullptr;
        /*[0x1C]*/ gadget = nullptr;
        /*[0x20]*/ offset = (-1);

        unknown_new_id = (-1);

    }

    Property::~Property()
    {
        /*[0x1C]*/ gadget->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // Property serialization
    // <kao2.00592650>
    ////////////////////////////////////////////////////////////////
    void Property::serialize(Archive &ar)
    {
        /* [0x08] property name */
        ar.serializeString(name);

        if (ar.getVersion() <= 0x88)
        {
            /* [0x0C] property type */
            ar.readOrWrite(&type, 0x04);
        }
        else
        {
            ar.readOrWrite(&type, 0x01);

            if (ar.isInReadMode())
            {
                type &= 0x000000FF;
            }
        }

        if (ar.getVersion() <= 0x88)
        {
            switch (type)
            {
                case 0x01: // boolean
                {
                    ar.readOrWrite(&numValue, 0x01);

                    break;
                }

                case 0x02: // float
                case 0x03: // integer
                {
                    ar.readOrWrite(&numValue, 0x04);

                    break;
                }

                case 0x04: // string
                {
                    ar.serializeString(strValue);

                    break;
                }

                case 0x05:
                case 0x06:
                {
                    ar.serialize((eObject**)&numValue, &E_GADGET_TYPEINFO);

                    break;
                }
            }
        }
        else
        {
            switch (type)
            {
                case 0x01: // boolean
                {
                    ar.readOrWrite(&numValue, 0x01);

                    break;
                }

                case 0x04: // string
                {
                    ar.serializeString(strValue);

                    break;
                }

                case 0x02: // float
                case 0x05: // ???
                {
                    ar.readOrWrite(&numValue, 0x04);

                    break;
                }

                case 0x03: // ???
                case 0x06: // ???
                {
                    ar.readOrWrite(&numValue, 0x04);

                    break;
                }
            }
        }

        /* [0x18] unknown, possibly next property */
        ArFunctions::serialize_Property(ar, (eRefCounter**)&unknown_18, nullptr);

        if (ar.getVersion() <= 0x88)
        {
            /* [0x1C] target gadget */
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&gadget, &E_GADGET_TYPEINFO);
        }
        else
        {
            /* unknown id */
            ar.readOrWrite(&unknown_new_id, 0x02);
        }

        /* [0x20] property offset in gadget class */
        ar.readOrWrite(&offset, 0x04);
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    // <kao2.005975A0>: Outer serialization
    // <kao2.00596500>: Group template
    ////////////////////////////////////////////////////////////////

    void ArFunctions::serialize_Property(Archive &ar, eRefCounter** o, const TypeInfo* t)
    {
        serializeKnownObject<Property>(ar, o, t);
    }


    ////////////////////////////////////////////////////////////////
    // Property: get script representation
    ////////////////////////////////////////////////////////////////
    eString Property::generateScriptText() const
    {
        eString result;
        char bufor[32];

        result += "prop ";
        result += gadget->getStringRepresentation();
        result += ".";
        result += name;
        result += " = ";

        switch (type)
        {
            case 0x01: // boolean
            {
                result += ((*(uint8_t*)(&numValue)) ? "true" : "false");

                break;
            }

            case 0x02: // float
            {
                sprintf_s(bufor, 32, "%.1f", *(float*)(&numValue));

                result += bufor;

                break;
            }

            case 0x03: // integer
            {
                sprintf_s(bufor, 32, "%i", *(int32_t*)(&numValue));

                result += bufor;

                break;
            }

            case 0x04: // string
            {
                result += "\"";
                result += strValue;
                result += "\"";

                break;
            }

            case 0x05:
            case 0x06:
            {
                if (nullptr != numValue)
                {
                    result += (*(Gadget**)&numValue)->getStringRepresentation();
                }
                else
                {
                    result += "< EMPTY_GADGET >";
                }

                break;
            }
        }

        /* Very nice debugging information! ;) */
        //// sprintf_s(bufor, 32, " // offset = %i", offset);
        //// result += bufor;

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // Property: is it connected with some gadget
    ////////////////////////////////////////////////////////////////
    bool Property::compareGadgets(Gadget* source) const
    {
        return (source == gadget);
    }

}
