#include <ElephantEngine/eGlobalCtrl.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGlobalCtrl interface
    // <kao2.0055C610> (constructor)
    // <kao2.00550D80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GLOBALCTRL_TYPEINFO
    (
        E_GLOBALCTRL_ID,
        "eGlobalCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eGlobalCtrl;
        }
    );

    TypeInfo* eGlobalCtrl::getType() const
    {
        return &E_GLOBALCTRL_TYPEINFO;
    }

    eGlobalCtrl::eGlobalCtrl()
    : eRefCounter()
    {
        /*[0x0130]*/ unknown_0130 = 0x01;

        /*[0x0154]*/ unknown_0154 = 1.0f;
        /*[0x0158]*/ unknown_0158 = 1.0f;
        /*[0x015C]*/ unknown_015C = 1.0f;
        /*[0x0160]*/ unknown_0160 = 1.0f;

        /*[0x012C]*/ unknown_012C = 1000.0f;

        /*[0x0008]*/ unknown_0008 = 0;

        /*[0x0168]*/ unknown_0168 = 0x00;
    }

    eGlobalCtrl::~eGlobalCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eGlobalCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGlobalCtrl::createFromOtherObject(const eGlobalCtrl &other)
    {
        unknown_0008 = other.unknown_0008;

        unknown_000C = other.unknown_000C;
        unknown_0054 = other.unknown_0054;
        unknown_009C = other.unknown_009C;
        unknown_00E4 = other.unknown_00E4;

        unknown_012C = other.unknown_012C;
        unknown_0130 = other.unknown_0130;
        unknown_0134 = other.unknown_0134;
        unknown_0138 = other.unknown_0138;
        unknown_013C = other.unknown_013C;
        unknown_0140 = other.unknown_0140;
        unknown_0144 = other.unknown_0144;
        unknown_0148 = other.unknown_0148;
        unknown_014C = other.unknown_014C;
        unknown_0150 = other.unknown_0150;

        unknown_0154 = other.unknown_0154;
        unknown_0158 = other.unknown_0158;
        unknown_015C = other.unknown_015C;
        unknown_0160 = other.unknown_0160;
    }

    eGlobalCtrl::eGlobalCtrl(const eGlobalCtrl &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eGlobalCtrl& eGlobalCtrl::operator = (const eGlobalCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGlobalCtrl::cloneFromMe() const
    {
        return new eGlobalCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eGlobalCtrl: serialization
    // <kao2.0055CA40>
    ////////////////////////////////////////////////////////////////
    void eGlobalCtrl::serialize(Archive &ar)
    {
        /* [0x0008] unknown */
        ar.readOrWrite(&unknown_0008, 0x04);

        /* eLinearCtrl::serialize() */
        unknown_000C.serialize(ar);
        unknown_0054.serialize(ar);
        unknown_009C.serialize(ar);
        unknown_00E4.serialize(ar);

        /* unknown values */
        ar.readOrWrite(&unknown_012C, 0x04);
        ar.readOrWrite(&unknown_0130, 0x01);
        ar.readOrWrite(&unknown_0134, 0x04);
        ar.readOrWrite(&unknown_0138, 0x04);
        ar.readOrWrite(&unknown_013C, 0x04);
        ar.readOrWrite(&unknown_0140, 0x04);
        ar.readOrWrite(&unknown_0144, 0x04);
        ar.readOrWrite(&unknown_0148, 0x04);
        ar.readOrWrite(&unknown_014C, 0x04);
        ar.readOrWrite(&unknown_0150, 0x01);

        /* unknown values */
        ar.readOrWrite(&unknown_0154, 0x04);
        ar.readOrWrite(&unknown_0158, 0x04);
        ar.readOrWrite(&unknown_015C, 0x04);
        ar.readOrWrite(&unknown_0160, 0x04);

        /* Some preparations of "eLinearCtrl" sub-objects */

        /* [0x0164] [0x015C] (overwrite) */
        unknown_0160 = 1.0f;
        unknown_015C = 1.0f;
    }

}
