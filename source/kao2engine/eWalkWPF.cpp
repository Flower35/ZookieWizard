#include <kao2engine/eWalkWPF.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWalkWPF interface
    // <kao2.00425784> (constructor)
    // <kao2.00425800> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_WALKWPF_TYPEINFO
    (
        E_WALKWPF_ID,
        "eWalkWPF",
        &E_WALK_TYPEINFO,
        []() -> eObject*
        {
            return new eWalkWPF;
        }
    );

    TypeInfo* eWalkWPF::getType() const
    {
        return &E_WALKWPF_TYPEINFO;
    }

    eWalkWPF::eWalkWPF()
    : eWalk()
    {}

    eWalkWPF::~eWalkWPF()
    {}


    ////////////////////////////////////////////////////////////////
    // eWalkWPF: cloning the object
    ////////////////////////////////////////////////////////////////

    void eWalkWPF::createFromOtherObject(const eWalkWPF &other)
    {}

    eWalkWPF::eWalkWPF(const eWalkWPF &other)
    : eWalk(other)
    {
        createFromOtherObject(other);
    }

    eWalkWPF& eWalkWPF::operator = (const eWalkWPF &other)
    {
        if ((&other) != this)
        {
            eWalk::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eWalkWPF::cloneFromMe() const
    {
        return new eWalkWPF(*this);
    }

}
