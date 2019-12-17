#ifndef H_KAO2AR_GADGETINSTANCEWHEN
#define H_KAO2AR_GADGETINSTANCEWHEN

#include <kao2engine/When.h>

namespace ZookieWizard
{
    class Gadget;

    ////////////////////////////////////////////////////////////////
    // GadgetInstanceWhen interface
    ////////////////////////////////////////////////////////////////

    class GadgetInstanceWhen : public When
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ Gadget* unknown_10;
            int32_t unknown_new_id;

        /*** Methods ***/

        public:

            GadgetInstanceWhen();
            ~GadgetInstanceWhen();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void saveWhenToTextFile(FileOperator &file, int32_t indentation) override;
    };


    ////////////////////////////////////////////////////////////////
    // GadgetInstanceWhen TypeInfo
    // <kao2.0059ED00> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GADGETINSTANCEWHEN_ID = 0x0002205D;

    extern TypeInfo E_GADGETINSTANCEWHEN_TYPEINFO;

}

#endif
