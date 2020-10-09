#ifndef H_KAO2AR_ANIMBILLBOARDTARGET
#define H_KAO2AR_ANIMBILLBOARDTARGET

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eAnimBillboardTarget interface
    // <kao_tw.0069A0BC> (vptr)
    ////////////////////////////////////////////////////////////////

    class eAnimBillboardTarget : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ float unknown_08;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10-0x18]*/ ePoint3 unknown_10;

            /*[0x30]*/ eString framesListFilename;
            /*[0x34]*/ uint8_t unknown_34;


        /*** Methods ***/

        public:

            eAnimBillboardTarget();
            ~eAnimBillboardTarget();

        private:

            void createFromOtherObject(const eAnimBillboardTarget &other);

        public:

            eAnimBillboardTarget(const eAnimBillboardTarget &other);
            eAnimBillboardTarget& operator = (const eAnimBillboardTarget &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eAnimBillboardTarget TypeInfo
    // <kao2.00477680> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ANIMBILLBOARDTARGET_ID = 0xA31B1BD0;

    extern TypeInfo E_ANIMBILLBOARDTARGET_TYPEINFO;

}

#endif
