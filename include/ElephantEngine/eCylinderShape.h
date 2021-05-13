#ifndef H_KAO2AR_CYLINDERSHAPE
#define H_KAO2AR_CYLINDERSHAPE

#include <ElephantEngine/ePrimitive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eCylinderShape interface
    // <kao2.005D2334> (vptr)
    ////////////////////////////////////////////////////////////////

    class eCylinderShape : public ePrimitive
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ float unknown_08;
            /*[0x0C]*/ float unknown_0C;
            /*[0x10-0x1C]*/ ePoint4 unknown_10;
            /*[0x20]*/ float unknown_20;
            /*[0x24]*/ float unknown_24;
            /*[0x28]*/ float unknown_28;

        /*** Methods ***/

        public:

            eCylinderShape(float x, float y);
            ~eCylinderShape();

        private:

            void createFromOtherObject(const eCylinderShape &other);

        public:

            eCylinderShape(const eCylinderShape &other);
            eCylinderShape& operator = (const eCylinderShape &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eCylinderShape TypeInfo
    // <kao2.004B97B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_CYLINDERSHAPE_ID = 0x00166677;

    extern TypeInfo E_CYLINDERSHAPE_TYPEINFO;

}

#endif
