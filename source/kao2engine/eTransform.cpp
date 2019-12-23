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

        form01.getMatrix().transpose(transposedMatrix);
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

        form01.serialize(ar);
        form02.serialize(ar);

        if (ar.isInReadMode())
        {
            form01.getMatrix().transpose(transposedMatrix);
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&ctrl, &E_CTRL_ESRP_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: set xform
    ////////////////////////////////////////////////////////////////
    void eTransform::setXForm(eSRP new_xform)
    {
        form01 = new_xform;

        form02 = form01;

        form01.getMatrix().transpose(transposedMatrix);
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: reposition the model in 3D space
    ////////////////////////////////////////////////////////////////
    void eTransform::renderObject(float time, int32_t draw_flags)
    {
        glPushMatrix();

        /* Apply Transformation (on top of previous ones) */

        glMultMatrixf(transposedMatrix);

        /* Draw children nodes */

        eGroup::renderObject(time, draw_flags);

        /* Restore parent matrix */

        glPopMatrix();
    }

}
