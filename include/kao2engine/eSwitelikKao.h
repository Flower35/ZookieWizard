#ifndef H_KAO2AR_SWITELIKKAO
#define H_KAO2AR_SWITELIKKAO

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSwitelikKao interface
    // <kao2.005CFB80> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSwitelikKao : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0xA4]*/

        /*** Methods ***/

        public:

            eSwitelikKao();
            ~eSwitelikKao();

        private:

            void createFromOtherObject(const eSwitelikKao &other);

        public:

            eSwitelikKao(const eSwitelikKao &other);
            eSwitelikKao& operator = (const eSwitelikKao &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSwitelikKao TypeInfo
    // <kao2.00451390> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SWITELIKKAO_ID = 0x3D50E749;

    extern TypeInfo E_SWITELIKKAO_TYPEINFO;

}

#endif
