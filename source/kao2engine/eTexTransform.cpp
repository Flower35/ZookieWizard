#include <kao2engine/eTexTransform.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTexTransform interface
    // <kao2.00472DE9> (constructor)
    // <kao2.00472E80> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_TEXTRANSFORM_TYPEINFO
    (
        E_TEXTRANSFORM_ID,
        "eTexTransform",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eTexTransform;
        }
    );

    TypeInfo* eTexTransform::getType() const
    {
        return &E_TEXTRANSFORM_TYPEINFO;
    }

    eTexTransform::eTexTransform()
    : eRefCounter()
    {
        xScale = nullptr;
        yScale = nullptr;
        uOffset = nullptr;
        vOffset = nullptr;
    }

    eTexTransform::~eTexTransform()
    {
        xScale->decRef();
        yScale->decRef();
        uOffset->decRef();
        vOffset->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eTexTransform: cloning the object
    ////////////////////////////////////////////////////////////////

    void eTexTransform::createFromOtherObject(const eTexTransform &other)
    {
        xScale = other.xScale;
        if (nullptr != xScale)
        {
            xScale->incRef();
        }

        yScale = other.yScale;
        if (nullptr != yScale)
        {
            yScale->incRef();
        }

        uOffset = other.uOffset;
        if (nullptr != uOffset)
        {
            uOffset->incRef();
        }

        vOffset = other.vOffset;
        if (nullptr != vOffset)
        {
            vOffset->incRef();
        }
    }

    eTexTransform::eTexTransform(const eTexTransform &other)
    : eRefCounter(other)
    {
        createFromOtherObject(other);
    }

    eTexTransform& eTexTransform::operator = (const eTexTransform &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            xScale->decRef();
            yScale->decRef();
            uOffset->decRef();
            vOffset->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eTexTransform::cloneFromMe() const
    {
        return new eTexTransform(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eTexTransform: serialization
    // <kao2.00472C80>
    ////////////////////////////////////////////////////////////////
    void eTexTransform::serialize(Archive &ar)
    {
        /* Texture's X-scale controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&xScale, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Texture's Y-scale controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&yScale, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Texture's U-offset controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&uOffset, &E_LEAFCTRL_FLOAT_TYPEINFO);

        /* Texture's V-offset controller */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&vOffset, &E_LEAFCTRL_FLOAT_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // eTexTransform: update texture matrix
    ////////////////////////////////////////////////////////////////
    void eTexTransform::updateTextureMatrix(eAnimate* anim) const
    {
        /* Reset the Texture Mapping matrix and update it */

        glMatrixMode(GL_TEXTURE);

        glLoadIdentity();

        if (nullptr != anim)
        {
            float move_u = 0;
            float move_v = 0;
            float scale_x = 1.0f;
            float scale_y = 1.0f;

            if (nullptr != xScale)
            {
                scale_x = xScale->ctrlGetTransform(scale_x, anim);
            }

            if (nullptr != yScale)
            {
                scale_y = yScale->ctrlGetTransform(scale_y, anim);
            }

            if (nullptr != uOffset)
            {
                move_u = uOffset->ctrlGetTransform(move_u, anim);
            }

            if (nullptr != vOffset)
            {
                move_v = vOffset->ctrlGetTransform(move_v, anim);
            }

            if ((1.0f != scale_x) || (1.0f != scale_y))
            {
                glTranslatef(1.0f, 1.0f, 1.0f);

                glScalef(scale_x, scale_y, 1.0f);

                glTranslatef((-1.0f), (-1.0f), (-1.0f));
            }

            if ((0 != move_u) || (0 != move_v))
            {
                glTranslatef(move_u, move_v, 0);
            }
        }

        /* Back to the model view matrix */

        glMatrixMode(GL_MODELVIEW);
    }

}
