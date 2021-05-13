#ifndef H_KAO2AR_DEMOPLAYER
#define H_KAO2AR_DEMOPLAYER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eDemoPlayer interface
    // <kao2.005CFF28> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDemoPlayer : public Gadget
    {
        /*** Methods ***/

        public:

            eDemoPlayer();
            ~eDemoPlayer();

        private:

            void createFromOtherObject(const eDemoPlayer &other);

        public:

            eDemoPlayer(const eDemoPlayer &other);
            eDemoPlayer& operator = (const eDemoPlayer &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eDemoPlayer TypeInfo
    // <kao2.00458E80> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DEMOPLAYER_ID = 0x3D3B21E9;

    extern TypeInfo E_DEMOPLAYER_TYPEINFO;

}

#endif
