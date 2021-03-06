#ifndef H_KAO2AR_TURNCOLLISIONOFF
#define H_KAO2AR_TURNCOLLISIONOFF

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff interface
    // <kao2.005D8288> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTurnCollisionOff : public Gadget
    {
        /*** Methods ***/

        public:

            eTurnCollisionOff();
            ~eTurnCollisionOff();

        private:

            void createFromOtherObject(const eTurnCollisionOff &other);

        public:

            eTurnCollisionOff(const eTurnCollisionOff &other);
            eTurnCollisionOff& operator = (const eTurnCollisionOff &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTurnCollisionOff TypeInfo
    // <kao2.0059A180> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TURNCOLLISIONOFF_ID = 0x0002FCC1;

    extern TypeInfo E_TURNCOLLISIONOFF_TYPEINFO;

}

#endif
