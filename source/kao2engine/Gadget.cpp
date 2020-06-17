#include <kao2engine/Gadget.h>
#include <kao2ar/Archive.h>

#include <kao2engine/Actor.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Gadget interface
    // <kao2.00597A50> (constructor)
    // <kao2.00597AC0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GADGET_TYPEINFO
    (
        E_GADGET_ID,
        "Gadget",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* Gadget::getType() const
    {
        return &E_GADGET_TYPEINFO;
    }

    Gadget::Gadget()
    : eRefCounter()
    {
        unknown_08 = nullptr;
    }

    Gadget::~Gadget() {}


    ////////////////////////////////////////////////////////////////
    // Gadget serialization
    // <kao2.00597BF0>
    ////////////////////////////////////////////////////////////////
    void Gadget::serialize(Archive &ar)
    {
        /* [0x08] Actor link */
        ar.serialize((eObject**)&unknown_08, &E_ACTOR_TYPEINFO);

        /* [0x0C] Gadget name */
        ar.serializeString(name);

        /* ASSERTION */

        if (ar.isInReadMode())
        {
            if ((name.getLength() <= 0) || name.compareExact(getType()->name, true))
            {
                ar.replaceStringDuringSerialization(name, getDefaultGadgetName());
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // Gadget: get textual representation
    ////////////////////////////////////////////////////////////////
    eString Gadget::getStringRepresentation() const
    {
        return name;
    }


    ////////////////////////////////////////////////////////////////
    // Gadget: get script representation
    ////////////////////////////////////////////////////////////////
    eString Gadget::generateScriptText() const
    {
        eString result;

        result += "gadget ";
        result += getType()->name;
        result += " ";
        result += name;

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // Gadget: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString Gadget::getDefaultGadgetName() const
    {
        int32_t pos;
        eString result;

        char first_sign[2];
        char* class_name = (char*)getType()->name;

        if ('e' == class_name[0])
        {
            pos = 1;
        }
        else
        {
            pos = 0;
        }

        first_sign[0] = StringFunctions::toLowerCase(class_name[pos]);
        first_sign[1] = 0x00;

        result = first_sign;
        result += &(class_name[pos + 1]);

        return result;
    }

}
