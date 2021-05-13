#ifndef H_KAO2AR_SESSIONFLOAT
#define H_KAO2AR_SESSIONFLOAT

#include <ElephantEngine/Float.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // SessionFloat interface
    // <kao2.005D8510> (vptr)
    ////////////////////////////////////////////////////////////////

    class SessionFloat : public Float
    {
        /*** Methods ***/

        public:

            SessionFloat();
            ~SessionFloat();

        private:

            void createFromOtherObject(const SessionFloat &other);

        public:

            SessionFloat(const SessionFloat &other);
            SessionFloat& operator = (const SessionFloat &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // SessionFloat TypeInfo
    // <kao2.0059CC20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SESSIONFLOAT_ID = 0x0002000E;

    extern TypeInfo E_SESSIONFLOAT_TYPEINFO;

}

#endif
