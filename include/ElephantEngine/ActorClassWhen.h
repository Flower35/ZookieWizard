#ifndef H_KAO2AR_ACTORCLASSWHEN
#define H_KAO2AR_ACTORCLASSWHEN

#include <ElephantEngine/When.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ActorClassWhen interface
    ////////////////////////////////////////////////////////////////

    class ActorClassWhen : public When
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ eString className;

        /*** Methods ***/

        public:

            ActorClassWhen();
            ~ActorClassWhen();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveWhenToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // ActorClassWhen TypeInfo
    // <kao2.0059F1F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTORCLASSWHEN_ID = 0x0002202D;

    extern TypeInfo E_ACTORCLASSWHEN_TYPEINFO;

}

#endif
