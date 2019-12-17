#ifndef H_KAO2AR_CYLINDERSHAPE
#define H_KAO2AR_CYLINDERSHAPE

#include <kao2engine/ePrimitive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylinderShape interface
    ////////////////////////////////////////////////////////////////

    class eCylinderShape : public ePrimitive
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/
            /*(...)*/
            /*[0x28]*/

        /*** Methods ***/

        public:

            eCylinderShape();
            ~eCylinderShape();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eCylinderShape TypeInfo
    // <kao2.004B97E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CYLINDERSHAPE_ID = 0x00166677;

    extern TypeInfo E_CYLINDERSHAPE_TYPEINFO;

}

#endif
