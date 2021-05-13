#ifndef H_KAO2AR_BOMBAEXPLODUJACA
#define H_KAO2AR_BOMBAEXPLODUJACA

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eBombaExplodujaca interface
    // <kao2.005CFCC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBombaExplodujaca : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x90]*/

        /*** Methods ***/

        public:

            eBombaExplodujaca();
            ~eBombaExplodujaca();

        private:

            void createFromOtherObject(const eBombaExplodujaca &other);

        public:

            eBombaExplodujaca(const eBombaExplodujaca &other);
            eBombaExplodujaca& operator = (const eBombaExplodujaca &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eBombaExplodujaca TypeInfo
    // <kao2.00453AD0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BOMBAEXPLODUJACA_ID = 0x3DEC4BC6;

    extern TypeInfo E_BOMBAEXPLODUJACA_TYPEINFO;

}

#endif
