#ifndef H_KAO2AR_SPEAKING
#define H_KAO2AR_SPEAKING

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpeaking interface
    // <kao2.005CFEC0> (vptr)
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

        private:

            void createFromOtherObject(const eSpeaking &other);

        public:

            eSpeaking(const eSpeaking &other);
            eSpeaking& operator = (const eSpeaking &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSpeaking TypeInfo
    // <kao2.00458AC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPEAKING_ID = 0x3BF132FA;

    extern TypeInfo E_SPEAKING_TYPEINFO;

}

#endif
