#ifndef H_KAO2AR_ANIMDUMPER
#define H_KAO2AR_ANIMDUMPER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // AnimDumper interface
    // <kao2.005E1278> (vptr)
    ////////////////////////////////////////////////////////////////

    class AnimDumper : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            AnimDumper();
            ~AnimDumper();

        private:

            void createFromOtherObject(const AnimDumper &other);

        public:

            AnimDumper(const AnimDumper &other);
            AnimDumper& operator = (const AnimDumper &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // AnimDumper TypeInfo
    // <kao2.005AF760> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMDUMPER_ID = 0x00020007;

    extern TypeInfo E_ANIMDUMPER_TYPEINFO;

}

#endif
