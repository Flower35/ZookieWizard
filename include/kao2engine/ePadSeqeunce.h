#ifndef H_KAO2AR_PADSEQEUNCE
#define H_KAO2AR_PADSEQEUNCE

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePadSeqeunce interface
    // <kao2.005D5768> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePadSeqeunce : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/

        /*** Methods ***/

        public:

            ePadSeqeunce();
            ~ePadSeqeunce();

        private:

            void createFromOtherObject(const ePadSeqeunce &other);

        public:

            ePadSeqeunce(const ePadSeqeunce &other);
            ePadSeqeunce& operator = (const ePadSeqeunce &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePadSeqeunce TypeInfo
    // <kao2.00523970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PADSEQEUNCE_ID = 0x3F1A9115;

    extern TypeInfo E_PADSEQEUNCE_TYPEINFO;

}

#endif
