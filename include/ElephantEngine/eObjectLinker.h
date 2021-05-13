#ifndef H_KAO2AR_OBJECTLINKER
#define H_KAO2AR_OBJECTLINKER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eObjectLinker interface
    // <kao2.005D50F8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eObjectLinker : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x28]*/

        /*** Methods ***/

        public:

            eObjectLinker();
            ~eObjectLinker();

        private:

            void createFromOtherObject(const eObjectLinker &other);

        public:

            eObjectLinker(const eObjectLinker &other);
            eObjectLinker& operator = (const eObjectLinker &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eObjectLinker TypeInfo
    // <kao2.00519B20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_OBJECTLINKER_ID = 0x00002ABF;

    extern TypeInfo E_OBJECTLINKER_TYPEINFO;

}

#endif
