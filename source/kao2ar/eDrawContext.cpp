#include <kao2ar/eDrawContext.h>

#include <kao2engine/eTexture.h>
#include <kao2engine/eMaterial.h>
#include <kao2engine/eLight.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eDrawContext: initialization
    ////////////////////////////////////////////////////////////////

    eDrawContext::eDrawContext()
    {
        drawFlags = 0;
        nodeFlags = 0;
        anim = nullptr;
        parentSRP = nullptr;
        parentMatrix = nullptr;
        markedID = (-1);

        lightsCount = 0;

        previousMaterial = nullptr;
        previousTextureID = 0;
        previousTexture = nullptr;
        previousMaterialFlags = 0x0010;
        previousAlphaTest = (-1.0f);
    }

    ////////////////////////////////////////////////////////////////
    // eDrawContext: get or set the draw flags
    ////////////////////////////////////////////////////////////////

    int32_t eDrawContext::getDrawFlags() const
    {
        return drawFlags;
    }

    void eDrawContext::setDrawFlags(int32_t new_flags)
    {
        drawFlags = new_flags;
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: check or set the node flags
    ////////////////////////////////////////////////////////////////

    bool eDrawContext::checkNodeFlags(uint32_t current_node_flags, bool is_group) const
    {
        if ((nodeFlags & current_node_flags) == nodeFlags)
        {
            return true;
        }

        if (is_group && (GUI::drawFlags::DRAW_FLAG_PROXIES & drawFlags))
        {
            uint32_t test_flags = (~ 0x70000000) & nodeFlags;

            return ((test_flags & current_node_flags) == test_flags);
        }

        return false;
    }

    void eDrawContext::setNodeFlags(uint32_t new_flags)
    {
        nodeFlags = new_flags;
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: get or set the "eAnimate" object
    ////////////////////////////////////////////////////////////////

    eAnimate* eDrawContext::getAnimateObject() const
    {
        return anim;
    }

    void eDrawContext::setAnimateObject(const eAnimate* new_object)
    {
        anim = (eAnimate*)new_object;
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: get or set the parent SRP pointer
    ////////////////////////////////////////////////////////////////

    eSRP* eDrawContext::getParentSRP() const
    {
        return parentSRP;
    }

    void eDrawContext::setParentSRP(const eSRP* new_parent_srp)
    {
        parentSRP = (eSRP*)new_parent_srp;
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: get or set the parent matrix pointer
    ////////////////////////////////////////////////////////////////

    eMatrix4x4* eDrawContext::getParentMatrix() const
    {
        return parentMatrix;
    }

    void eDrawContext::setParentMatrix(const eMatrix4x4* new_parent_matrix)
    {
        parentMatrix = (eMatrix4x4*)new_parent_matrix;
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: get, set, check the Marked ID
    // * Current object from Archive will have `ID >= (-1)`
    // * Child node of the selected `eGroup` will have `ID >= (0)`
    // * Object marked on list will receive `ID = (-2)`
    // * Object that is a child of marked group will receive `ID = (-3)`
    // * Any object that is not selected or marked will receive `ID = (-4)`
    ////////////////////////////////////////////////////////////////

    int32_t eDrawContext::getMarekedId() const
    {
        return markedID;
    }

    void eDrawContext::setMarkedId(int32_t new_marked_id)
    {
        markedID = new_marked_id;
    }

    bool eDrawContext::setMarkedForGroupNode()
    {
        if (isNodeMarkedOrChildOfMarked())
        {
            markedID = (-3);
            return true;
        }

        return false;
    }

    void eDrawContext::setMarkedForChildNode(bool matches_id)
    {
        markedID = matches_id ? (-2) : (-4);
    }

    bool eDrawContext::isNodeSelectedOrMarked() const
    {
        return (((-2) == markedID) || ((-1) == markedID));
    }

    bool eDrawContext::isNodeMarkedOrChildOfMarked() const
    {
        return (((-2) == markedID) || ((-3) == markedID));
    }

    bool eDrawContext::isNodeOutlined() const
    {
        return ((GUI::drawFlags::DRAW_FLAG_OUTLINE & drawFlags) && isNodeMarkedOrChildOfMarked());
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: use material (binding texture, checking colors, blending)
    // <kao2.0048D7A0>
    ////////////////////////////////////////////////////////////////
    void eDrawContext::useMaterial(const eMaterial* material, int32_t texture_id)
    {
        GLuint texture_bind_id = 0;
        eTexture* test_texture;

        int32_t test_material_flags;
        int32_t material_flags_diff;
        int32_t blend_flags;
        bool dummy_test;
        float test_alpha_ref;


        /********************************/
        /* Comparing material and texture IDs and binding the OpenGL 2D texture */

        if (previousMaterial == material)
        {
            if (previousTextureID == texture_id)
            {
                return;
            }
        }

        bool textures_enabled = (GUI::drawFlags::DRAW_FLAG_TEXTURES & drawFlags);
        bool valid_texture = false;

        if (nullptr == material)
        {
            test_material_flags = 0x0010;
            test_alpha_ref = (-1.0f);
        }
        else
        {
            test_material_flags = material->getMaterialFlags();
            test_alpha_ref = material->getAlphaTestRef();

            if (texture_id >= material->getTexturesCount())
            {
                test_material_flags |= 0x0010;
            }
            else
            {
                test_texture = material->getIthTexture(texture_id);

                if (previousTexture != test_texture)
                {
                    if (textures_enabled && (nullptr != test_texture))
                    {
                        glBindTexture(GL_TEXTURE_2D, test_texture->getTextureId());

                        /* Empty `eAnimate` object will reset the Texture Mapping matrix */

                        test_texture->updateTextureMatrix((GUI::drawFlags::DRAW_FLAG_ANIMS & drawFlags) ? anim : nullptr);
                    }

                    previousTexture = test_texture;
                }

                valid_texture = textures_enabled;
            }
        }

        if (!valid_texture)
        {
            previousTexture = nullptr;

            glMatrixMode(GL_TEXTURE);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
        }

        /********************************/
        /* Setting and comparing temporary flags */

        if (0 == (GUI::drawFlags::DRAW_FLAG_BLENDING & drawFlags))
        {
            test_material_flags &= (~ 0x0E);

            /* Wireframe backfaces */
            glPolygonMode(GL_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_BACK, GL_FILL);
        }

        blend_flags = (test_material_flags >> 1) & 0x03;

        if ((texture_id > 0) && (0 != blend_flags))
        {
            test_material_flags = (test_material_flags + 2) & (~ 0x08);
        }

        if (!textures_enabled)
        {
            test_material_flags |= 0x10;
        }

        dummy_test = 0x08 & test_material_flags;
        material_flags_diff = previousMaterialFlags ^ test_material_flags;

        if (dummy_test && (test_alpha_ref != previousAlphaTest))
        {
            material_flags_diff |= 0x08;
        }

        if (0 != material_flags_diff)
        {
            if (0x01 & material_flags_diff)
            {
                if (0x01 & test_material_flags)
                {
                    glDisable(GL_CULL_FACE);
                }
                else
                {
                    glEnable(GL_CULL_FACE);
                }
            }

            if (0x08 & material_flags_diff)
            {
                if (dummy_test)
                {
                    glEnable(GL_ALPHA_TEST);

                    if (test_alpha_ref != previousAlphaTest)
                    {
                        glAlphaFunc(GL_GREATER, test_alpha_ref);

                        previousAlphaTest = test_alpha_ref;
                    }
                }
                else
                {
                    glDisable(GL_ALPHA_TEST);
                }
            }

            if (0x10 & material_flags_diff)
            {
                if (0x10 & test_material_flags)
                {
                    glDisable(GL_TEXTURE_2D);
                }
                else
                {
                    glEnable(GL_TEXTURE_2D);
                }
            }

            if (0x06 & material_flags_diff)
            {
                if ((dummy_test = (0 == (0x06 & previousMaterialFlags))) || (0 != blend_flags))
                {
                    if (dummy_test)
                    {
                        glEnable(GL_BLEND);
                        glDepthMask(GL_FALSE);
                    }

                    if (0x01 == blend_flags)
                    {
                        /* "TM_BLEND" */
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    }
                    else if (0x02 == blend_flags)
                    {
                        /* "TM_ADDITIVE" */
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                    }
                    else
                    {
                        /* "TM_OPAQUE" */
                        glBlendFunc(GL_ONE, GL_ZERO);
                    }
                }
                else
                {
                    glDisable(GL_BLEND);
                    glDepthMask(GL_TRUE);

                    glBlendFunc(GL_ONE, GL_ZERO);
                }
            }

            previousMaterialFlags = test_material_flags;
        }

        /********************************/
        /* Checking the `eMaterialState` */

        /* (...) */

        /********************************/
        /* Updating current material pointer and current texture ID */

        previousMaterial = (eMaterial*)material;
        previousTextureID = texture_id;
    }


    ////////////////////////////////////////////////////////////////
    // eDrawContext: use light or make space for lights
    ////////////////////////////////////////////////////////////////

    void eDrawContext::useLight(const eLight* light)
    {
        if (nullptr != light)
        {
            if (0 == lightsCount)
            {
                glEnable(GL_LIGHTING);
            }

            if (lightsCount < 5)
            {
                light->bindLight(lightsCount);

                glEnable(GL_LIGHT0 + lightsCount);
            }

            lightsCount++;
        }
    }

    void eDrawContext::decreaseLights(int32_t number)
    {
        for (int32_t a = 0; a < number; a++)
        {
            lightsCount--;

            if (lightsCount < 5)
            {
                glDisable(GL_LIGHT0 + lightsCount);
            }
        }

        if (0 == lightsCount)
        {
            glDisable(GL_LIGHTING);
        }
    }

}
