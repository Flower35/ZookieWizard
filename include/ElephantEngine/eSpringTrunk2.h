#ifndef H_KAO2AR_SPRINGTRUNK2
#define H_KAO2AR_SPRINGTRUNK2

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpringTrunk2 interface
    // <kao2.005D3D40> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSpringTrunk2 : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x28]*/

        /*** Methods ***/

        public:

            eSpringTrunk2();
            ~eSpringTrunk2();

        private:

            void createFromOtherObject(const eSpringTrunk2 &other);

        public:

            eSpringTrunk2(const eSpringTrunk2 &other);
            eSpringTrunk2& operator = (const eSpringTrunk2 &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSpringTrunk2 TypeInfo
    // <kao2.004F2BD0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPRINGTRUNK2_ID = 0x00025402;

    extern TypeInfo E_SPRINGTRUNK2_TYPEINFO;

}

#endif
