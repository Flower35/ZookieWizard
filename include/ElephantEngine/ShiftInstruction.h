#ifndef H_KAO2AR_SHIFTINSTRUCTION
#define H_KAO2AR_SHIFTINSTRUCTION

#include <ElephantEngine/VoidInstruction.h>

namespace ZookieWizard
{
    class State;
    class Namespace;

    class Anim;

    ////////////////////////////////////////////////////////////////
    // Unknown structure
    ////////////////////////////////////////////////////////////////

    struct ShiftInstructionBase
    {
        /*** Properties ***/

            /*[0x00]*/ Anim* unknown_00;
            /*[0x04]*/ eRefCounter* unknown_04; // "eFloat", "eFloatTriple".
            int32_t anim_id;

        /*** Methods ***/

            ShiftInstructionBase();

            void serialize(Archive &ar);
    };

    ////////////////////////////////////////////////////////////////
    // ShiftInstruction interface
    ////////////////////////////////////////////////////////////////

    class ShiftInstruction : public VoidInstruction
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ State* destinationState;
            /*[0x0C]*/ State* currentState;

            /*[0x10]*/ int32_t groupCount;
            /*[0x14]*/ int32_t groupMaxLength;
            /*[0x18]*/ ShiftInstructionBase* group;

        /*** Methods ***/

        public:

            ShiftInstruction(State* x, State* y);
            ~ShiftInstruction();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void saveInstructionToTextFile(FileOperator &file, int32_t indentation) const override;
    };


    ////////////////////////////////////////////////////////////////
    // ShiftInstruction TypeInfo
    // <kao2.0058FBA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SHIFTINSTRUCTION_ID = 0x00022003;

    extern TypeInfo E_SHIFTINSTRUCTION_TYPEINFO;

}

#endif
