#ifndef H_KAO2AR_TEXTRANSFORM
#define H_KAO2AR_TEXTRANSFORM

#include <ElephantEngine/eRefCounter.h>

#include <ElephantEngine/eLeafCtrl.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTexTransform interface
    // <kao2.005D0748> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTexTransform : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eLeafCtrl<float>* xScale;
            /*[0x0C]*/ eLeafCtrl<float>* yScale;
            /*[0x10]*/ eLeafCtrl<float>* uOffset;
            /*[0x14]*/ eLeafCtrl<float>* vOffset;

        /*** Methods ***/

        public:

            eTexTransform();
            ~eTexTransform();

        private:

            void createFromOtherObject(const eTexTransform &other);

        public:

            eTexTransform(const eTexTransform &other);
            eTexTransform& operator = (const eTexTransform &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eTexTransform >> */

            void updateTextureMatrix(eAnimate* anim) const;

            eLeafCtrl<float>* getXScaleCtrl() const;
            eLeafCtrl<float>* getYScaleCtrl() const;
            eLeafCtrl<float>* getUOffsetCtrl() const;
            eLeafCtrl<float>* getVOffsetCtrl() const;

            void setXScaleCtrl(eLeafCtrl<float>* new_ctrl);
            void setYScaleCtrl(eLeafCtrl<float>* new_ctrl);
            void setUOffsetCtrl(eLeafCtrl<float>* new_ctrl);
            void setVOffsetCtrl(eLeafCtrl<float>* new_ctrl);
    };


    ////////////////////////////////////////////////////////////////
    // eTexTransform TypeInfo
    // <kao2.00472D80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTRANSFORM_ID = 0x1004;

    extern TypeInfo E_TEXTRANSFORM_TYPEINFO;

}

#endif
