#include <kao2engine/eTransform.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTransform interface
    // <kao2.0047BAA0> (constructor)
    // <kao2.0047BC80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TRANSFORM_TYPEINFO
    (
        E_TRANSFORM_ID,
        "eTransform",
        &E_GROUP_TYPEINFO,
        []() -> eObject*
        {
            return new eTransform;
        }
    );

    TypeInfo* eTransform::getType()
    {
        return &E_TRANSFORM_TYPEINFO;
    }

    eTransform::eTransform()
    : eGroup()
    {
        /*[0xA8]*/ ctrl = nullptr;

        defaultTransform[0].getMatrix().transpose(transposedMatrix);
    }

    eTransform::~eTransform()
    {
        ctrl->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTransform serialization
    // <kao2.0047BE00>
    ////////////////////////////////////////////////////////////////
    void eTransform::serialize(Archive &ar)
    {
        eGroup::serialize(ar);

        defaultTransform[0].serialize(ar);
        defaultTransform[1].serialize(ar);

        if (ar.isInReadMode())
        {
            modifiedTransform[0] = defaultTransform[0];
            modifiedTransform[1] = defaultTransform[1];

            modifiedTransform[0].getMatrix().transpose(transposedMatrix);
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: set xform
    ////////////////////////////////////////////////////////////////
    void eTransform::setXForm(eSRP new_xform)
    {
        defaultTransform[0] = new_xform;
        defaultTransform[1] = defaultTransform[0];

        modifiedTransform[0] = defaultTransform[0];
        modifiedTransform[1] = defaultTransform[1];

        modifiedTransform[0].getMatrix().transpose(transposedMatrix);
    }



    ////////////////////////////////////////////////////////////////
    // eTransform: get current xform
    ////////////////////////////////////////////////////////////////
    eSRP eTransform::getXForm()
    {
        return modifiedTransform[1];
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: reposition the model in 3D space
    ////////////////////////////////////////////////////////////////
    void eTransform::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        if (0 == (GUI::drawFlags::DRAW_FLAG_INVISIBLE & draw_flags))
        {
            if (0 == (0x01 & flags))
            {
                return;
            }
        }

        /* Calculate transformation (for animations) */

        if (GUI::drawFlags::DRAW_FLAG_ANIMS & draw_flags)
        {
            updateSRP(anim, parent_srp);
        }

        /* Apply Transformation (on top of previous ones) */

        glPushMatrix();

        glMultMatrixf(transposedMatrix);

        /* Draw children nodes */

        eGroup::renderObject(anim, draw_flags, modifiedTransform[1]);

        /* Restore parent matrix */

        glPopMatrix();
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: update SRP structure
    // <kao2.0047BCF0>
    ////////////////////////////////////////////////////////////////
    void eTransform::updateSRP(eAnimate* anim, eSRP &parent_srp)
    {
        eSRP test_srp;
        eSRP previous_srp;

        if (nullptr != ctrl)
        {
            previous_srp = modifiedTransform[0];

            modifiedTransform[0] = ctrl->ctrlGetTransform(test_srp, anim);

            /* (--dsp--) Checking if `previous_srp != form01` and changing some "eNode" flags */

            /* Update render matrix */

            modifiedTransform[0].getMatrix().transpose(transposedMatrix);
        }

        /* Update world transformation matrix */

        modifiedTransform[1] = modifiedTransform[0].applyAnotherSRP(parent_srp);

        /* (--dsp--) <kao2.0047BD9A> (update "eALBox" if exists) */
    }

}
