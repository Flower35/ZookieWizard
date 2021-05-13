#include <ElephantEngine/eXRefTarget.h>
#include <ElephantBase/Archive.h>
#include <ElephantBase/eDrawContext.h>

#include <ElephantEngine/eScene.h>

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
    // eXRefTarget: cloning the object
    ////////////////////////////////////////////////////////////////

    void eXRefTarget::createFromOtherObject(const eXRefTarget &other)
    {
        scene = other.scene;

        if (nullptr != scene)
        {
            scene->incRef();
        }

        fileName = other.fileName;
    }


    eXRefTarget::eXRefTarget(const eXRefTarget &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eXRefTarget& eXRefTarget::operator = (const eXRefTarget &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            scene->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eXRefTarget::cloneFromMe() const
    {
        return new eXRefTarget(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: serialization
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
    eXRefTarget* eXRefTarget::loadTarget(const eString &media_dir, const eString &model_name, int32_t engine_version, int32_t ar_flags)
    {
        eXRefTarget* result = nullptr;
        eScene* previous_scene;

        Archive parallel_ar(media_dir);
        eString full_path = ArFunctions::getFullArchivePath(model_name, media_dir, engine_version, ar_flags);

        /* Check if this proxy already exists */
        if (nullptr != (result = (eXRefTarget*)nodesManager_GetProxyTarget(&full_path)))
        {
            return result;
        }

        /********************************/

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
                full_path,
                (AR_MODE_IS_PROXY | AR_MODE_READ),
                engine_version,
                0
            );

            parallel_ar.copySceneFromMe(&scene);
        }
        catch (ErrorMessage &err)
        {
            err.display();
        }

        /* Restore parent scene */
        ArFunctions::setCurrentScene(previous_scene);

        /* Save this path, even if the Archive was not found (to avoid multiple errors for the same "eProxy") */
        if (!nodesManager_InsertProxyTarget(&full_path, (result = this)))
        {
            result = nullptr;
        }
        else if ((nullptr != result) && (nullptr == (result->scene)))
        {
            result = nullptr;
        }

        return result;
    }


    ////////////////////////////////////////////////////////////////
    // eXRefTarget: save external model to a separate AR file
    ////////////////////////////////////////////////////////////////
    void eXRefTarget::exportTarget(const eString &media_dir, int32_t engine_version, int32_t ar_flags) const
    {
        eScene* previous_scene;

        Archive parallel_ar(media_dir);
        eString full_path = ArFunctions::getFullArchivePath(fileName, media_dir, engine_version, ar_flags);

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
                    full_path,
                    (AR_MODE_IS_PROXY | AR_MODE_WRITE),
                    engine_version,
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
