#ifndef H_KAO2AR_ACTORINSTANCEWHEN
#define H_KAO2AR_ACTORINSTANCEWHEN

#include <kao2engine/When.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ActorInstanceWhen interface
    // <kao2.005D8710> (vptr)
    ////////////////////////////////////////////////////////////////

    class ActorInstanceWhen : public When
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ eString instanceName;

        /*** Methods ***/

        public:

            ActorInstanceWhen();
            ~ActorInstanceWhen();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void saveWhenToTextFile(FileOperator &file, int32_t indentation) override;
    };


    ////////////////////////////////////////////////////////////////
    // ActorInstanceWhen TypeInfo
    // <kao2.0059F740> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTORINSTANCEWHEN_ID = 0x0002203D;

    extern TypeInfo E_ACTORINSTANCEWHEN_TYPEINFO;

}

#endif
