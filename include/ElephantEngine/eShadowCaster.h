#ifndef H_KAO2AR_SHADOWCASTER
#define H_KAO2AR_SHADOWCASTER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eShadowCaster interface
    // <kao2.005D69D8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eShadowCaster : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x3C]*/

        /*** Methods ***/

        public:

            eShadowCaster();
            ~eShadowCaster();

        private:

            void createFromOtherObject(const eShadowCaster &other);

        public:

            eShadowCaster(const eShadowCaster &other);
            eShadowCaster& operator = (const eShadowCaster &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eShadowCaster TypeInfo
    // <kao2.00556EA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SHADOWCASTER_ID = 0x54AD0300;

    extern TypeInfo E_SHADOWCASTER_TYPEINFO;

}

#endif
