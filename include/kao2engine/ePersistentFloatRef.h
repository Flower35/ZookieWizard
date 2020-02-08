#ifndef H_KAO2AR_PERSISTENTFLOATREF
#define H_KAO2AR_PERSISTENTFLOATREF

#include <kao2engine/Float.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef interface
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

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePersistentFloatRef TypeInfo
    // <kao2.00528830> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PERSISTENTFLOATREF_ID = 0xEEEF70A7;

    extern TypeInfo E_PERSISTENTFLOATREF_TYPEINFO;

}

#endif
