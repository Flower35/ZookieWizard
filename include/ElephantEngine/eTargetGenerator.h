#ifndef H_KAO2AR_TARGETGENERATOR
#define H_KAO2AR_TARGETGENERATOR

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTargetGenerator interface
    // <kao2.005D8830> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTargetGenerator : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/
            /*[0x1C]*/

        /*** Methods ***/

        public:

            eTargetGenerator();
            ~eTargetGenerator();

        private:

            void createFromOtherObject(const eTargetGenerator &other);

        public:

            eTargetGenerator(const eTargetGenerator &other);
            eTargetGenerator& operator = (const eTargetGenerator &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTargetGenerator TypeInfo
    // <kao2.005A5000> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TARGETGENERATOR_ID = 0x3BE0ACF2;

    extern TypeInfo E_TARGETGENERATOR_TYPEINFO;

}

#endif
