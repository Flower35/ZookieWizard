#ifndef H_KAO2AR_GAMECAMERA
#define H_KAO2AR_GAMECAMERA

#include <ElephantEngine/eCamera.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGameCamera interface
    // <kao2.005D2EC8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGameCamera : public eCamera
    {
        /*** Properties ***/

        protected:

            /*[0x01E8]*/
            /*(...)*/
            /*[0x0408]*/

        /*** Methods ***/

        public:

            eGameCamera(eString x);
            ~eGameCamera();

        private:

            void createFromOtherObject(const eGameCamera &other);

        public:

            eGameCamera(const eGameCamera &other);
            eGameCamera& operator = (const eGameCamera &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eGameCamera TypeInfo
    // <kao2.004D97E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GAMECAMERA_ID = 0x0CA4E7A2;

    extern TypeInfo E_GAMECAMERA_TYPEINFO;

}

#endif
