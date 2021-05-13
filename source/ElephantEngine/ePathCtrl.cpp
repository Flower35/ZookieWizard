#include <ElephantEngine/ePathCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePathCtrl interface
    // <kao2.004229C0> (constructor)
    // <kao2.00422A90> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PATHCTRL_TYPEINFO
    (
        E_PATHCTRL_ID,
        "ePathCtrl",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* ePathCtrl::getType() const
    {
        return &E_PATHCTRL_TYPEINFO;
    }

    ePathCtrl::ePathCtrl()
    : Gadget()
    {
        /*[0x10]*/ unknown_10 = nullptr;

        /*[0x20]*/ unknown_20 = nullptr;
        /*[0x24]*/ unknown_24 = nullptr;

        /*[0x14]*/ unknown_14 = 0;
        /*[0x18]*/ unknown_18 = 0;

        /*[0x28]*/ unknown_28 = nullptr;
        /*[0x2C]*/ unknown_2C = nullptr;

        /*[0x40]*/ unknown_40 = 0x00;
    }

    ePathCtrl::~ePathCtrl()
    {
        unknown_24->decRef();

        unknown_20->decRef();

        unknown_10->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // ePathCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePathCtrl::createFromOtherObject(const ePathCtrl &other)
    {
        unknown_10 = other.unknown_10;
        if (nullptr != unknown_10)
        {
            unknown_10->incRef();
        }

        unknown_14 = other.unknown_14;
        unknown_18 = other.unknown_18;
        unknown_1C = other.unknown_1C;

        unknown_20 = other.unknown_20;
        if (nullptr != unknown_20)
        {
            unknown_20->incRef();
        }

        unknown_24 = other.unknown_24;
        if (nullptr != unknown_24)
        {
            unknown_24->incRef();
        }

        unknown_28 = other.unknown_28;
        unknown_2C = other.unknown_2C;

        unknown_30 = other.unknown_30;
        unknown_34 = other.unknown_34;
        unknown_38 = other.unknown_38;
        unknown_40 = other.unknown_40;
    }

    ePathCtrl::ePathCtrl(const ePathCtrl &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    ePathCtrl& ePathCtrl::operator = (const ePathCtrl &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            unknown_24->decRef();

            unknown_20->decRef();

            unknown_10->decRef();

            /****************/

            createFromOtherObject(other);

            /****************/

            // << AFTER >>
        }

        return (*this);
    }

    eObject* ePathCtrl::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // ePathCtrl: serialization
    // <kao2.004240B0>
    ////////////////////////////////////////////////////////////////
    void ePathCtrl::serialize(Archive &ar)
    {
        Gadget::serialize(ar);

        /* [0x10] unknown */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_10, nullptr);

        /* [0x14] unknown values */

        ar.readOrWrite(&unknown_14, 0x04);
        ar.readOrWrite(&unknown_18, 0x04);
        ar.readOrWrite(&unknown_1C, 0x04);

        /* [0x20] unknown */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_20, nullptr);

        /* [0x24] unknown */

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_24, nullptr);

        /* [0x28] unknown */

        ar.serialize((eObject**)&unknown_28, nullptr);

        /* [0x2C] unknown */

        ar.serialize((eObject**)&unknown_2C, nullptr);

        /* [0x30] unknown values */

        ar.readOrWrite(&unknown_30, 0x04);
        ar.readOrWrite(&unknown_34, 0x04);
        ar.readOrWrite(&unknown_38, 0x04);
        ar.readOrWrite(&unknown_40, 0x01);
    }


    ////////////////////////////////////////////////////////////////
    // ePathCtrl: get default name (scripting shenanigans)
    ////////////////////////////////////////////////////////////////
    eString ePathCtrl::getDefaultGadgetName() const
    {
        return "ctrl";
    }

}
