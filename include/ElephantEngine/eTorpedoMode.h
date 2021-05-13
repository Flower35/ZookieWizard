#ifndef H_KAO2AR_TORPEDOMODE
#define H_KAO2AR_TORPEDOMODE

#include <ElephantEngine/eFSOp.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eTorpedoMode interface
    // <kao2.005D2738> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTorpedoMode : public eFSOp
    {
        /*** Properties ***/

        protected:

            /*[0x24]*/
            /*(...)*/
            /*[0xC0]*/

        /*** Methods ***/

        public:

            eTorpedoMode();
            ~eTorpedoMode();

        private:

            void createFromOtherObject(const eTorpedoMode &other);

        public:

            eTorpedoMode(const eTorpedoMode &other);
            eTorpedoMode& operator = (const eTorpedoMode &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eTorpedoMode TypeInfo
    // <kao2.004CD0A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TORPEDOMODE_ID = 0x7074ED01;

    extern TypeInfo E_TORPEDOMODE_TYPEINFO;

}

#endif
