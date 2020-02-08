#include <kao2engine/eTransform.h>
#include <kao2ar/Archive.h>

#include <utilities/ColladaExporter.h>

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

    TypeInfo* eTransform::getType() const
    {
        return &E_TRANSFORM_TYPEINFO;
    }

    eTransform::eTransform()
    : eGroup()
    {
        /*[0xA8]*/ ctrl = nullptr;

        defaultTransform[0].getMatrix().transpose(transposedMatrix);

        jointType = false;
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
    eSRP eTransform::getXForm() const
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


    ////////////////////////////////////////////////////////////////
    // eTransform: COLLADA exporting
    ////////////////////////////////////////////////////////////////
    void eTransform::writeNodeToXmlFile(ColladaExporter &exporter) const
    {
        int32_t i;
        float alpha, beta, gamma;
        char bufor[64];
        eNode* test_node;

        switch (exporter.getState())
        {
            case COLLADA_EXPORTER_STATE_LIGHTS:
            case COLLADA_EXPORTER_STATE_CAMERAS:
            case COLLADA_EXPORTER_STATE_EFFECTS:
            case COLLADA_EXPORTER_STATE_IMAGES:
            case COLLADA_EXPORTER_STATE_MATERIALS:
            case COLLADA_EXPORTER_STATE_GEOMETRIES:
            case COLLADA_EXPORTER_STATE_CONTROLLERS:
            case COLLADA_EXPORTER_STATE_ANIMATIONS:
            {
                /* Collecting objects for COLLADA libraries... */

                eGroup::writeNodeToXmlFile(exporter);

                break;
            }

            case COLLADA_EXPORTER_STATE_VISUAL_SCENES:
            {
                exporter.openTag("node");

                i = exporter.getObjectRefId(COLLADA_EXPORTER_OBJ_NODE, this, true);
                sprintf_s(bufor, 64, "Node%d", i);
                exporter.insertTagAttrib("id", bufor);
                exporter.insertTagAttrib("name", name);

                if (jointType)
                {
                    exporter.insertTagAttrib("sid", bufor);
                    exporter.insertTagAttrib("type", "JOINT");
                }
                else
                {
                    exporter.insertTagAttrib("type", "NODE");
                }

                alpha = modifiedTransform[0].scale;
                sprintf_s(bufor, 64, "%f %f %f", alpha, alpha, alpha);
                exporter.openTag("scale");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                modifiedTransform[0].rot.toEulerAngles(true, alpha, beta, gamma);

                sprintf_s(bufor, 64, "0 0 1 %f", (gamma / 180.0 * M_PI));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                sprintf_s(bufor, 64, "0 1 0 %f", (beta / 180.0 * M_PI));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                sprintf_s(bufor, 64, "1 0 0 %f", (alpha / 180.0 * M_PI));
                exporter.openTag("rotate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                alpha = defaultTransform[0].pos.x;
                beta = defaultTransform[0].pos.y;
                gamma = defaultTransform[0].pos.z;
                sprintf_s(bufor, 64, "%f %f %f", alpha, beta, gamma);
                exporter.openTag("translate");
                exporter.writeInsideTag(bufor);
                exporter.closeTag();

                /* "eGroup" could exist as independent node (without parent "eTransform") */
                /* That's why we are not calling `eGroup::writeNodeToXmlFile()` */

                for (i = 0; i < nodes.getSize(); i++)
                {
                    test_node = (eNode*)nodes.getIthChild(i);

                    if (nullptr != test_node)
                    {
                        test_node->writeNodeToXmlFile(exporter);
                    }
                }

                exporter.closeTag(); // "node"

                break;
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eTransform: set node type (helpful when exporting)
    ////////////////////////////////////////////////////////////////

    void eTransform::setTypeToJoint(bool is_joint)
    {
        jointType = is_joint;
    }

    bool eTransform::isJointNode() const
    {
        return jointType;
    }

}
