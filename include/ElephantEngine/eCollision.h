#ifndef H_KAO2AR_COLLISION
#define H_KAO2AR_COLLISION

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCollision interface
    ////////////////////////////////////////////////////////////////

    class eCollision : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x11]*/ bool enabled;
            /*[0x14]*/

        /*** Methods ***/

        public:

            eCollision();
            ~eCollision();

        private:

            void createFromOtherObject(const eCollision &other);

        public:

            eCollision(const eCollision &other);
            eCollision& operator = (const eCollision &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCollision TypeInfo
    // <kao2.00598110> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_COLLISION_ID = 0x0002FCFF;

    extern TypeInfo E_COLLISION_TYPEINFO;

}

#endif
