#ifndef H_KAO2AR_OSCILATIONCTRL
#define H_KAO2AR_OSCILATIONCTRL

#include <ElephantEngine/eRefCounter.h>

#include <ElephantEngine/eLinearCtrl.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // eOscilationCtrl interface
    // <kao2.005D6C60> (vptr)
    ////////////////////////////////////////////////////////////////

    class eOscilationCtrl : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x0008-0x004C]*/ eLinearCtrl unknown_0008;
            /*[0x0050-0x0094]*/ eLinearCtrl unknown_0050;
            /*[0x0098-0x00DC]*/ eLinearCtrl unknown_0098;
            /*[0x00E0-0x0124]*/ eLinearCtrl unknown_00E0;
            /*(...)*/
            /*[0x0130]*/

        /*** Methods ***/

        public:

            eOscilationCtrl();
            ~eOscilationCtrl();

        private:

            void createFromOtherObject(const eOscilationCtrl &other);

        public:

            eOscilationCtrl(const eOscilationCtrl &other);
            eOscilationCtrl& operator = (const eOscilationCtrl &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eOscilationCtrl TypeInfo
    // <kao2.0055CEE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OSCILATIONCTRL_ID = 0x0F0F12ED;

    extern TypeInfo E_OSCILATIONCTRL_TYPEINFO;

}

#endif
