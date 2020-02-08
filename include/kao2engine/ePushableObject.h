#ifndef H_KAO2AR_PUSHABLEOBJECT
#define H_KAO2AR_PUSHABLEOBJECT

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePushableObject interface
    // <kao2.005D3880> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePushableObject : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/
            /*[0x1C]*/
            /*[0x20]*/

        /*** Methods ***/

        public:

            ePushableObject();
            ~ePushableObject();

            TypeInfo* getType() const override;

            eString getDefaultGadgetName() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePushableObject TypeInfo
    // <kao2.004EB3E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PUSHABLEOBJECT_ID = 0x00020831;

    extern TypeInfo E_PUSHABLEOBJECT_TYPEINFO;

}

#endif
