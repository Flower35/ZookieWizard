#ifndef H_KAO2AR_SPEAKING
#define H_KAO2AR_SPEAKING

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpeaking interface
    ////////////////////////////////////////////////////////////////

    class eSpeaking : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x78]*/ eString unknown_78;
            /*[0x7C]*/ eString unknown_7C;
            /*(...)*/
            /*[0xBC]*/

        /*** Methods ***/

        public:

            eSpeaking();
            ~eSpeaking();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSpeaking TypeInfo
    // <kao2.00458AF0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPEAKING_ID = 0x3BF132FA;

    extern TypeInfo E_SPEAKING_TYPEINFO;

}

#endif
