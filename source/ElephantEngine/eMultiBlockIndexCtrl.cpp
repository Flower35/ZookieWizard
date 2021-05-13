#include <ElephantEngine/eMultiBlockIndexCtrl.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/eBlockIndexCtrl.h>
#include <ElephantEngine/Actor.h>

#include <ElephantBase/ArTemplates.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl interface
    // <kao2.004BD819> (constructor)
    // <kao2.0049FDD0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MULTIBLOCKINDEXCTRL_TYPEINFO
    (
        E_MULTIBLOCKINDEXCTRL_ID,
        "eMultiBlockIndexCtrl",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eMultiBlockIndexCtrl;
        }
    );

    TypeInfo* eMultiBlockIndexCtrl::getType() const
    {
        return &E_MULTIBLOCKINDEXCTRL_TYPEINFO;
    }

    eMultiBlockIndexCtrl::eMultiBlockIndexCtrl()
    : eRefCounter()
    {
        /*[0x08]*/ actor = nullptr;
    }

    eMultiBlockIndexCtrl::~eMultiBlockIndexCtrl()
    {}


    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMultiBlockIndexCtrl::createFromOtherObject(const eMultiBlockIndexCtrl &other)
    {
        throw ErrorMessage
        (
            "CRITICAL ERROR while cloning the \"eMultiBlockIndexCtrl\" object:\n" \
            "cloning << multiple block index controllers >> without context is not supported!!!"
        );
    }

    eMultiBlockIndexCtrl::eMultiBlockIndexCtrl(const eMultiBlockIndexCtrl &other)
    : eRefCounter(other)
    {
        actor = nullptr;

        /****************/

        createFromOtherObject(other);
    }

    eMultiBlockIndexCtrl& eMultiBlockIndexCtrl::operator = (const eMultiBlockIndexCtrl &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            actor = nullptr;
            controllers.clear();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMultiBlockIndexCtrl::cloneFromMe() const
    {
        return new eMultiBlockIndexCtrl(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl: serialization
    // <kao2.004BD700>
    ////////////////////////////////////////////////////////////////
    void eMultiBlockIndexCtrl::serialize(Archive &ar)
    {
        /* block index controllers */
        controllers.serialize(ar, &E_BLOCKINDEXCTRL_TYPEINFO);

        /* actor link */
        ar.serialize((eObject**)&actor, &E_ACTOR_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // Explicit templates
    // <kao2.0049FC30>: Outer serialization
    ////////////////////////////////////////////////////////////////

    void ArFunctions::serialize_eMultiBlockIndexCtrl(Archive &ar, eRefCounter** o, TypeInfo* t)
    {
        serializeKnownObject<eMultiBlockIndexCtrl>(ar, o, t);
    }

}
