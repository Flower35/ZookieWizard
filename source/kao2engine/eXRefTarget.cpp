#include <kao2engine/eXRefTarget.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

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
    void eXRefTarget::renderXRefScene(eDrawContext &draw_context) const
    {
        if (nullptr != scene)
        {
            scene->renderNode(draw_context);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: set name and load target (used with eProxy)
    ////////////////////////////////////////////////////////////////
    bool eXRefTarget::loadTarget(eString media_dir, int32_t engine_version, int32_t ar_flags, eString model_name)
    {
        bool result = false;
        eScene* previous_scene;
        Archive parallel_ar(media_dir);

        fileName = model_name;

        /* Remember parent scene */
        previous_scene = ArFunctions::getCurrentScene();

        if (nullptr != scene)
        {
            scene->decRef();
            scene = nullptr;
        }

        try
        {
            parallel_ar.open
            (
                fileName,
                ((AR_MODE_READ | ar_flags) & (~ AR_MODE_WRITE)),
                engine_version,
                true,
                0
            );

            parallel_ar.copySceneFromMe(&scene);

            result = true;
        }
        catch (ErrorMessage &e)
        {
            e.display();
        }

        /* Restore parent scene */
        ArFunctions::setCurrentScene(previous_scene);

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: save external model to a separate AR file
    ////////////////////////////////////////////////////////////////
    void eXRefTarget::exportTarget(eString media_dir, int32_t engine_version, int32_t ar_flags) const
    {
        eScene* previous_scene;
        Archive parallel_ar(media_dir);

        if (nullptr != scene)
        {
            /* Remember parent scene */
            previous_scene = ArFunctions::getCurrentScene();

            /* Set nested secene as the current (global) scene */
            ArFunctions::setCurrentScene(scene);

            /* Prepare new archive to be saved */
            parallel_ar.setMyParentScene(scene);

            try
            {
                parallel_ar.open
                (
                    fileName,
                    ((AR_MODE_WRITE | ar_flags) & (~ AR_MODE_READ)),
                    engine_version,
                    true,
                    0
                );
            }
            catch (ErrorMessage &e)
            {
                e.display();
            }

            /* Restore parent scene */
            ArFunctions::setCurrentScene(previous_scene);
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
