#ifndef H_KAO2AR_BILLBOARD
#define H_KAO2AR_BILLBOARD

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBillboard interface
    ////////////////////////////////////////////////////////////////

    class eBillboard : public eTransform
    {

        /*** Properties ***/

        protected:

            /*[0xAC]*/ bool enabled;

        /*** Methods ***/

        public:

            eBillboard();
            ~eBillboard();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBillboard TypeInfo
    // <kao2.004AC9C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BILLBOARD_ID = 0x00008222;

    extern TypeInfo E_BILLBOARD_TYPEINFO;

}

#endif
