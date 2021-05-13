#ifndef H_KAO2AR_FSSPRITE
#define H_KAO2AR_FSSPRITE

#include <ElephantEngine/eFSOp.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFSSprite interface
    // <kao2.005D67F0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFSSprite : public eFSOp
    {
        /*** Properties ***/

        protected:

            /*(...)*/
            /*[0x74]*/

        /*** Methods ***/

        public:

            eFSSprite();
            ~eFSSprite();

        private:

            void createFromOtherObject(const eFSSprite &other);

        public:

            eFSSprite(const eFSSprite &other);
            eFSSprite& operator = (const eFSSprite &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFSSprite TypeInfo
    // <kao2.00553EB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FSSPRITE_ID = 0xFF777790;

    extern TypeInfo E_FSSPRITE_TYPEINFO;


    ////////////////////////////////////////////////////////////////
    // Static Gadget
    ////////////////////////////////////////////////////////////////

    extern eFSSprite theFSSprite;

}

#endif
