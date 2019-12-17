#ifndef H_KAO2AR_SNDEMITEROMNI
#define H_KAO2AR_SNDEMITEROMNI

#include <kao2engine/eSndEmiter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni interface
    ////////////////////////////////////////////////////////////////

    class eSndEmiterOmni : public eSndEmiter
    {

        /*** Properties ***/

        protected:

            /*[0xB8]*/
            /*(...)*/
            /*[0xC8]*/ float unknown_C8;    
            /*[0xCC]*/ float unknown_CC;
            /*(...)*/
            /*[0xD8]*/

        /*** Methods ***/

        public:

            eSndEmiterOmni();
            ~eSndEmiterOmni();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSndEmiterOmni TypeInfo
    // <kao2.0056CC20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SNDEMITEROMNI_ID = 0x09994525;

    extern TypeInfo E_SNDEMITEROMNI_TYPEINFO;

}

#endif
