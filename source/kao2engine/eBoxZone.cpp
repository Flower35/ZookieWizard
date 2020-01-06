#include <kao2engine/eBoxZone.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBoxZone interface
    // <kao2.0049DF30> (constructor)
    // <kao2.0049E010> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_BOXZONE_TYPEINFO
    (
        E_BOXZONE_ID,
        "eBoxZone",
        &E_ZONE_TYPEINFO,
        []() -> eObject*
        {
            return new eBoxZone;
        }
    );

    TypeInfo* eBoxZone::getType()
    {
        return &E_BOXZONE_TYPEINFO;
    }

    eBoxZone::eBoxZone()
    : eZone()
    {}

    eBoxZone::~eBoxZone() {}


    ////////////////////////////////////////////////////////////////
    // eBoxZone serialization
    // <kao2.0049E290>
    ////////////////////////////////////////////////////////////////
    void eBoxZone::serialize(Archive &ar)
    {
        eZone::serialize(ar);

        boxBoundMin.serialize(ar);
        boxBoundMax.serialize(ar);
    }


    ////////////////////////////////////////////////////////////////
    // eBoxZone: rener
    ////////////////////////////////////////////////////////////////
    void eBoxZone::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        if (GUI::drawFlags::DRAW_FLAG_BOXZONES & draw_flags)
        {
            /* (--dsp--) use `glCallList()` here !!! */

            glBindTexture(GL_TEXTURE_2D, 0);

            glColor3f(1.0f, 0, 0);

            glLineWidth(2.0f);

            glBegin(GL_LINES);

            /* Cube Front */

            glVertex3f(boxBoundMin.x, boxBoundMin.y, boxBoundMin.z);
            glVertex3f(boxBoundMax.x, boxBoundMin.y, boxBoundMin.z);

            glVertex3f(boxBoundMax.x, boxBoundMin.y, boxBoundMin.z);
            glVertex3f(boxBoundMax.x, boxBoundMin.y, boxBoundMax.z);

            glVertex3f(boxBoundMax.x, boxBoundMin.y, boxBoundMax.z);
            glVertex3f(boxBoundMin.x, boxBoundMin.y, boxBoundMax.z);

            glVertex3f(boxBoundMin.x, boxBoundMin.y, boxBoundMax.z);
            glVertex3f(boxBoundMin.x, boxBoundMin.y, boxBoundMin.z);

            /* Cube Back */

            glVertex3f(boxBoundMin.x, boxBoundMax.y, boxBoundMin.z);
            glVertex3f(boxBoundMax.x, boxBoundMax.y, boxBoundMin.z);

            glVertex3f(boxBoundMax.x, boxBoundMax.y, boxBoundMin.z);
            glVertex3f(boxBoundMax.x, boxBoundMax.y, boxBoundMax.z);

            glVertex3f(boxBoundMax.x, boxBoundMax.y, boxBoundMax.z);
            glVertex3f(boxBoundMin.x, boxBoundMax.y, boxBoundMax.z);

            glVertex3f(boxBoundMin.x, boxBoundMax.y, boxBoundMax.z);
            glVertex3f(boxBoundMin.x, boxBoundMax.y, boxBoundMin.z);

            /* Cube Left */

            glVertex3f(boxBoundMin.x, boxBoundMax.y, boxBoundMax.z);
            glVertex3f(boxBoundMin.x, boxBoundMin.y, boxBoundMax.z);

            glVertex3f(boxBoundMin.x, boxBoundMax.y, boxBoundMin.z);
            glVertex3f(boxBoundMin.x, boxBoundMin.y, boxBoundMin.z);

            /* Cube Right */

            glVertex3f(boxBoundMax.x, boxBoundMax.y, boxBoundMax.z);
            glVertex3f(boxBoundMax.x, boxBoundMin.y, boxBoundMax.z);

            glVertex3f(boxBoundMax.x, boxBoundMax.y, boxBoundMin.z);
            glVertex3f(boxBoundMax.x, boxBoundMin.y, boxBoundMin.z);

            /* Stop drawing lines */

            glEnd();

            glColor3f(1.0f, 1.0f, 1.0f);

            glLineWidth(1.0f);
        }
    }

}
