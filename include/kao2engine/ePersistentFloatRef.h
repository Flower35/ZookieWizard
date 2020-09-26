#ifndef H_KAO2AR_PERSISTENTFLOATREF
#define H_KAO2AR_PERSISTENTFLOATREF

#include <kao2engine/Float.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef interface
    // <kao2.005D59F8> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePersistentFloatRef : public Float
    {
        /*** Properties ***/

        protected:

            /*[0x14]*/ int32_t id;

        /*** Methods ***/

        public:

            ePersistentFloatRef();
            ~ePersistentFloatRef();

        private:

            void createFromOtherObject(const ePersistentFloatRef &other);

        public:

            ePersistentFloatRef(const ePersistentFloatRef &other);
            ePersistentFloatRef& operator = (const ePersistentFloatRef &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef TypeInfo
    // <kao2.00528800> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PERSISTENTFLOATREF_ID = 0xEEEF70A7;

    extern TypeInfo E_PERSISTENTFLOATREF_TYPEINFO;

}

#endif
