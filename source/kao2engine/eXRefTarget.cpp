#include <kao2engine/eXRefTarget.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eScene.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eXRefTarget interface
    // <kao2.004AD1E2> (constructor)
    // <kao2.004AD290> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_XREFTARGET_TYPEINFO
    (
        E_XREFTARGET_ID,
        "eXRefTarget",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eXRefTarget;
        }
    );

    TypeInfo* eXRefTarget::getType() const
    {
        return &E_XREFTARGET_TYPEINFO;
    }

    eXRefTarget::eXRefTarget()
    : eRefCounter()
    {
        /*[0x14]*/ scene = nullptr;
    }

    eXRefTarget::~eXRefTarget()
    {
        scene->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget serialization
    // <kao2.004AD030>
    ////////////////////////////////////////////////////////////////
    void eXRefTarget::serialize(Archive &ar)
    {
        eScene* previous_scene;

        /* [0x18] name */
        ar.serializeString(fileName);

        /* Please remember previous scene pointer! */
        previous_scene = ArFunctions::getCurrentScene();

        /* [0x14] scene */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&scene, &E_SCENE_TYPEINFO);

        /* Bring back the outer scene link */
        ArFunctions::setCurrentScene(previous_scene);

        if (ar.isInReadMode())
        {
            //// (--dsp--) <kao2.004AD0B8>
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: render child scene in parent scene
    ////////////////////////////////////////////////////////////////
    void eXRefTarget::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        if (nullptr != scene)
        {
            scene->renderObject(anim, draw_flags, parent_srp);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: set name and load target (used with eProxy)
    ////////////////////////////////////////////////////////////////
    bool eXRefTarget::loadTarget(Archive &ar, int32_t ar_flags, eString model_name)
    {
        Archive parallel_ar(ar.getMediaDir());

        fileName = model_name;

        if (nullptr != scene)
        {
            scene->decRef();
        }

        try
        {
            parallel_ar.open
            (
                fileName,
                ((AR_MODE_READ | ar_flags) & (~ AR_MODE_WRITE)),
                ar.getCurrentEngineVersion()
            );

            parallel_ar.copySceneFromMe(&scene);

            return true;
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: save external model to a separate AR file
    ////////////////////////////////////////////////////////////////
    void eXRefTarget::exportTarget(Archive &ar, int32_t ar_flags) const
    {
        Archive parallel_ar(ar.getMediaDir());

        if (nullptr != scene)
        {
            parallel_ar.setMyParentScene(scene);

            try
            {
                parallel_ar.open
                (
                    fileName,
                    ((AR_MODE_WRITE | ar_flags) & (~ AR_MODE_READ)),
                    ar.getCurrentEngineVersion()
                );
            }
            catch (ErrorMessage &e)
            {
                e.display();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: get local scene
    ////////////////////////////////////////////////////////////////
    eScene* eXRefTarget::getLocalScene() const
    {
        return scene;
    }

}
