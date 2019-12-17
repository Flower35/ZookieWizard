#ifndef H_KAO2AR_GADGETCLASSWHEN
#define H_KAO2AR_GADGETCLASSWHEN

#include <kao2engine/When.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // GadgetClassWhen interface
    ////////////////////////////////////////////////////////////////

    class GadgetClassWhen : public When
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ TypeInfo* unknown_10;

        /*** Methods ***/

        public:

            GadgetClassWhen();
            ~GadgetClassWhen();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void saveWhenToTextFile(FileOperator &file, int32_t indentation) override;
    };


    ////////////////////////////////////////////////////////////////
    // GadgetClassWhen TypeInfo
    // <kao2.0059E1E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GADGETCLASSWHEN_ID = 0x0002201D;

    extern TypeInfo E_GADGETCLASSWHEN_TYPEINFO;

}

#endif
