#ifndef H_KAO2AR_PARENTLISTENER
#define H_KAO2AR_PARENTLISTENER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParentListener interface
    // <kao2.005D4FE8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eParentListener : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0744]*/

        /*** Methods ***/

        public:

            eParentListener();
            ~eParentListener();

        private:

            void createFromOtherObject(const eParentListener &other);

        public:

            eParentListener(const eParentListener &other);
            eParentListener& operator = (const eParentListener &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eParentListener TypeInfo
    // <kao2.005173E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARENTLISTENER_ID = 0x00002CDF;

    extern TypeInfo E_PARENTLISTENER_TYPEINFO;

}

#endif
