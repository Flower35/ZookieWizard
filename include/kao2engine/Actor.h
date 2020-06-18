#ifndef H_KAO2AR_ACTOR
#define H_KAO2AR_ACTOR

#include <kao2engine/ePivot.h>

#include <kao2engine/Namespace.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Actor interface
    ////////////////////////////////////////////////////////////////

    class Actor : public ePivot
    {

        /*** Properties ***/

        protected:

            /*[0x0114]*/ Namespace* script;
            /*[0x0118]*/ eString scriptPath;
            /*(kao3)[0x04D0-0x04D8]*/ Collection<ArFunctions::serialize_eRefCounter> unknown_04D0;
            /*(kao3)[0x04DC-0x04E4]*/ Collection<ArFunctions::serialize_eRefCounter> unknown_04DC;

        /*** Methods ***/

        public:

            Actor();
            ~Actor();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;

            void destroyNode() override;

            void saveMyScript(Archive &ar) const;
    };


    ////////////////////////////////////////////////////////////////
    // Actor TypeInfo
    // <kao2.00572890> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_ACTOR_ID = 0x07EA0000;

    extern TypeInfo E_ACTOR_TYPEINFO;

}

#endif
