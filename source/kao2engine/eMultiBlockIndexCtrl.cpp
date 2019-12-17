#include <kao2engine/eMultiBlockIndexCtrl.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eBlockIndexCtrl.h>
#include <kao2engine/Actor.h>

#include <kao2ar/ArTemplates.h>

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

    TypeInfo* eMultiBlockIndexCtrl::getType()
    {
        return &E_MULTIBLOCKINDEXCTRL_TYPEINFO;
    }

    eMultiBlockIndexCtrl::eMultiBlockIndexCtrl()
    : eRefCounter()
    {
        /*[0x08]*/ actor = nullptr;
    }

    eMultiBlockIndexCtrl::~eMultiBlockIndexCtrl() {}


    ////////////////////////////////////////////////////////////////
    // eMultiBlockIndexCtrl serialization
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
