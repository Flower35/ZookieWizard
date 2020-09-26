#include <kao2engine/ePadSeqeunce.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadSeqeunce interface
    // <kao2.005239D1> (constructor)
    // <kao2.00523B70> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PADSEQEUNCE_TYPEINFO
    (
        E_PADSEQEUNCE_ID,
        "ePadSeqeunce",
        &E_GADGET_TYPEINFO,
        []() -> eObject*
        {
            return new ePadSeqeunce;
        }
    );

    TypeInfo* ePadSeqeunce::getType() const
    {
        return &E_PADSEQEUNCE_TYPEINFO;
    }

    ePadSeqeunce::ePadSeqeunce()
    : Gadget()
    {}

    ePadSeqeunce::~ePadSeqeunce()
    {}


    ////////////////////////////////////////////////////////////////
    // ePadSeqeunce: cloning the object
    ////////////////////////////////////////////////////////////////

    void ePadSeqeunce::createFromOtherObject(const ePadSeqeunce &other)
    {}

    ePadSeqeunce::ePadSeqeunce(const ePadSeqeunce &other)
    : Gadget(other)
    {
        createFromOtherObject(other);
    }

    ePadSeqeunce& ePadSeqeunce::operator = (const ePadSeqeunce &other)
    {
        if ((&other) != this)
        {
            Gadget::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* ePadSeqeunce::cloneFromMe() const
    {
        return new ePadSeqeunce(*this);
    }

}
