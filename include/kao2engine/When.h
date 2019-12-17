#ifndef H_KAO2AR_WHEN
#define H_KAO2AR_WHEN

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class VoidInstruction;

    ////////////////////////////////////////////////////////////////
    // When interface
    ////////////////////////////////////////////////////////////////

    class When : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString message;
            /*[0x0C]*/ VoidInstruction* instruction;

        /*** Methods ***/

        public:

            When();
            ~When();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            virtual void saveWhenToTextFile(FileOperator &file, int32_t indentation) = 0;
    };


    ////////////////////////////////////////////////////////////////
    // When TypeInfo
    // <kao2.0059DE30> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WHEN_ID = 0x0002200D;

    extern TypeInfo E_WHEN_TYPEINFO;

}

#endif
