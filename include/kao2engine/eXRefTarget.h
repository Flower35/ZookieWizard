#ifndef H_KAO2AR_XREFTARGET
#define H_KAO2AR_XREFTARGET

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class eScene;

    ////////////////////////////////////////////////////////////////
    // eXRefTarget interface
    ////////////////////////////////////////////////////////////////

    class eXRefTarget : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/
            /*(...)*/
            /*[0x14]*/ eScene* scene;
            /*[0x18]*/ eString fileName;
            /*(...)*/
            /*[0x24]*/

        /*** Methods ***/

        public:

            eXRefTarget();
            ~eXRefTarget();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;

            bool loadTarget(Archive &ar, int32_t ar_flags, eString model_name);
            void exportTarget(Archive &ar, int32_t ar_flags) const;

            eScene* getLocalScene() const;
    };


    ////////////////////////////////////////////////////////////////
    // eXRefTarget TypeInfo
    // <kao2.004AD1B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_XREFTARGET_ID = 0x87EF0001;

    extern TypeInfo E_XREFTARGET_TYPEINFO;

}

#endif
