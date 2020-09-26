#ifndef H_KAO2AR_BILLBOARD
#define H_KAO2AR_BILLBOARD

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBillboard interface
    // <kao2.005D1EA8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBillboard : public eTransform
    {
        /*** Properties ***/

        protected:

            /*[0xAC]*/ bool billboarded;

        /*** Methods ***/

        public:

            eBillboard();
            ~eBillboard();

        private:

            void createFromOtherObject(const eBillboard &other);

        public:

            eBillboard(const eBillboard &other);
            eBillboard& operator = (const eBillboard &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eBillboard TypeInfo
    // <kao2.004AC990> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BILLBOARD_ID = 0x00008222;

    extern TypeInfo E_BILLBOARD_TYPEINFO;

}

#endif
