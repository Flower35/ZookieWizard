#ifndef H_KAO2AR_LEVELCHANGER
#define H_KAO2AR_LEVELCHANGER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLevelChanger interface
    // <kao2.005CFE70> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLevelChanger : public Gadget
    {
        /*** Methods ***/

        public:

            eLevelChanger();
            ~eLevelChanger();

        private:

            void createFromOtherObject(const eLevelChanger &other);

        public:

            eLevelChanger(const eLevelChanger &other);
            eLevelChanger& operator = (const eLevelChanger &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLevelChanger TypeInfo
    // <kao2.00457810> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LEVELCHANGER_ID = 0x3D2646A2;

    extern TypeInfo E_LEVELCHANGER_TYPEINFO;

}

#endif
