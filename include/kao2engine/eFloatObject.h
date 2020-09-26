#ifndef H_KAO2AR_FLOATOBJECT
#define H_KAO2AR_FLOATOBJECT

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFloatObject interface
    // <kao2.005CEAB0> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFloatObject : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x88]*/

        /*** Methods ***/

        public:

            eFloatObject();
            ~eFloatObject();

        private:

            void createFromOtherObject(const eFloatObject &other);

        public:

            eFloatObject(const eFloatObject &other);
            eFloatObject& operator = (const eFloatObject &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFloatObject TypeInfo
    // <kao2.00432B40> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FLOATOBJECT_ID = 0x3A5611B7;

    extern TypeInfo E_FLOATOBJECT_TYPEINFO;

}

#endif
