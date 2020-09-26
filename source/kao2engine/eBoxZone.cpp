#include <kao2engine/eBoxZone.h>
#include <kao2ar/Archive.h>
#include <kao2ar/eDrawContext.h>

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

    TypeInfo* eBoxZone::getType() const
    {
        return &E_BOXZONE_TYPEINFO;
    }

    eBoxZone::eBoxZone()
    : eZone()
    {
        /*[0x1C]*/ flags |= 0x40000000;
    }

    eBoxZone::~eBoxZone()
    {}


    ////////////////////////////////////////////////////////////////
    // eBoxZone: cloning the object
    ////////////////////////////////////////////////////////////////

    void eBoxZone::createFromOtherObject(const eBoxZone &other)
    {}

    eBoxZone::eBoxZone(const eBoxZone &other)
    : eZone(other)
    {
        createFromOtherObject(other);
    }

    eBoxZone& eBoxZone::operator = (const eBoxZone &other)
    {
        if ((&other) != this)
        {
            eZone::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eBoxZone::cloneFromMe() const
    {
        return new eBoxZone(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eBoxZone: serialization
    // <kao2.0049E290>
    ////////////////////////////////////////////////////////////////
    void eBoxZone::serialize(Archive &ar)
    {
        eZone::serialize(ar);

        boxBoundMin.serialize(ar);
        boxBoundMax.serialize(ar);
    }


    ////////////////////////////////////////////////////////////////
    // eBoxZone: render this node
    ////////////////////////////////////////////////////////////////
    void eBoxZone::renderNode(eDrawContext &draw_context) const
    {
        if (GUI::drawFlags::DRAW_FLAG_BOXZONES & draw_context.getDrawFlags())
        {
            /* Inactive color (red) */
            float color[3] = {1.0f, 0, 0};

            bool is_selected_or_marked = draw_context.isNodeSelectedOrMarked();

            if (is_selected_or_marked)
            {
                glPushMatrix();
                GUI::multiplyBySelectedObjectTransform(false);
            }

            if (draw_context.isNodeOutlined())
            {
                /* Active color */
                GUI::colorOfMarkedObject(color[0], color[1], color[2]);
            }

            GUI::renderBoundingBox
            (
                2.0f,
                color[0], color[1], color[2],
                boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
                boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
            );

            if (is_selected_or_marked)
            {
                glPopMatrix();
            }
        }
    }

}
