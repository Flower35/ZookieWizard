#ifndef H_KAO2AR_CAMERADEFLECTOR
#define H_KAO2AR_CAMERADEFLECTOR

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCameraDeflector interface
    // <kao_tw.006A3B7C> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCameraDeflector : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x34]*/

        /*** Methods ***/

        public:

            eCameraDeflector();
            ~eCameraDeflector();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eCameraDeflector TypeInfo
    // <kao_tw.005DDC70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CAMERADEFLECTOR_ID = 0x0C3A0002;

    extern TypeInfo E_CAMERADEFLECTOR_TYPEINFO;

}

#endif
