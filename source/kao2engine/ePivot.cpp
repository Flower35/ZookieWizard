#include <kao2engine/ePivot.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePivot interface
    // <kao2.00485CC0> (constructor)
    // <kao2.004860E0> (destructor)
    ////////////////////////////////////////////////////////////////

    extern TypeInfo E_PIVOT_TYPEINFO
    (
        E_PIVOT_ID,
        "ePivot",
        &E_TRANSFORM_TYPEINFO,
        []() -> eObject*
        {
            return new ePivot;
        }
    );

    TypeInfo* ePivot::getType()
    {
        return &E_PIVOT_TYPEINFO;
    }

    ePivot::ePivot()
    : eTransform()
    {
        flags |= 0x00071000;
    }

    ePivot::~ePivot() {}


    ////////////////////////////////////////////////////////////////
    // ePivot serialization
    // <kao2.00486660>
    ////////////////////////////////////////////////////////////////
    void ePivot::serialize(Archive &ar)
    {
        int32_t a;

        eTransform::serialize(ar);

        if (ar.getVersion() < 0x7D)
        {
            throw ErrorMessage
            (
                "ePivot::serialize():\n" \
                "ar.version() 125 required!"
            );
        }

        /* Animations */
        animations.serialize(ar);

        /* Unknown group */
        a = 0x00;
        ar.readOrWrite(&a, 0x04);
        if (0 != a)
        {
            throw ErrorMessage
            (
                "ePivot::serialize():\n" \
                "non-empty group member is not supported!"
            );
        }
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: set animation object for rendering
    ////////////////////////////////////////////////////////////////
    void ePivot::renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp)
    {
        animations.setAnimation(GUI::animationID, GUI::timerGetFrames());

        eTransform::renderObject(&animations, draw_flags, parent_srp);
    }


    ////////////////////////////////////////////////////////////////
    // ePivot: skip eSRP updating (if called from "eGroup")
    ////////////////////////////////////////////////////////////////
    void ePivot::updateSRP(eAnimate* anim, eSRP &parent_srp)
    {
        return;
    }

}
