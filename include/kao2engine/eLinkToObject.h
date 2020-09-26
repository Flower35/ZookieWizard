#ifndef H_KAO2AR_LINKTOOBJECT
#define H_KAO2AR_LINKTOOBJECT

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLinkToObject interface
    // <kao2.005CF848> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLinkToObject : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x38]*/

        /*** Methods ***/

        public:

            eLinkToObject();
            ~eLinkToObject();

        private:

            void createFromOtherObject(const eLinkToObject &other);

        public:

            eLinkToObject(const eLinkToObject &other);
            eLinkToObject& operator = (const eLinkToObject &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eLinkToObject TypeInfo
    // <kao2.0044AAB0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LINKTOOBJECT_ID = 0x3BA2CFFF;

    extern TypeInfo E_LINKTOOBJECT_TYPEINFO;

}

#endif
