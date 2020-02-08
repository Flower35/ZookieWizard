#ifndef H_KAO2AR_MEWHEN
#define H_KAO2AR_MEWHEN

#include <kao2engine/When.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // MeWhen interface
    ////////////////////////////////////////////////////////////////

    class MeWhen : public When
    {
        /*** Methods ***/

        public:

            MeWhen();
            ~MeWhen();

            TypeInfo* getType() const override;

            void saveWhenToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // MeWhen TypeInfo
    // <kao2.0059E8E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_MEWHEN_ID = 0x0002204E;

    extern TypeInfo E_MEWHEN_TYPEINFO;

}

#endif
