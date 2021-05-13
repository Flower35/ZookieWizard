#include <ElephantEngine/MsgDumper.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // MsgDumper interface
    // <kao2.005B00D1> (constructor)
    // <kao2.005B0140> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MSGDUMPER_TYPEINFO
    (
        E_MSGDUMPER_ID,
        "MsgDumper",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new MsgDumper;
        }
    );

    const TypeInfo* MsgDumper::getType() const
    {
        return &E_MSGDUMPER_TYPEINFO;
    }

    MsgDumper::MsgDumper()
    : Gadget()
    {}

    MsgDumper::~MsgDumper()
    {}


    ////////////////////////////////////////////////////////////////
    // MsgDumper: cloning the object
    ////////////////////////////////////////////////////////////////

    void MsgDumper::createFromOtherObject(const MsgDumper &other)
    {}

    MsgDumper::MsgDumper(const MsgDumper &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    MsgDumper& MsgDumper::operator = (const MsgDumper &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* MsgDumper::cloneFromMe() const
    {
        return new MsgDumper(*this);
    }

}
