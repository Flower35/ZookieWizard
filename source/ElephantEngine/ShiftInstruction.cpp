#include <ElephantEngine/ShiftInstruction.h>
#include <ElephantBase/Archive.h>

#include <ElephantEngine/State.h>

#include <ElephantEngine/Anim.h>
#include <ElephantEngine/eFloat.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ShiftInstruction interface
    // <kao2.0058F4A0> (constructor)
    // <kao2.0058F5C0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_SHIFTINSTRUCTION_TYPEINFO
    (
        E_SHIFTINSTRUCTION_ID,
        "ShiftInstruction",
        &E_VOIDINSTRUCTION_TYPEINFO,
        []() -> eObject*
        {
            return new ShiftInstruction(nullptr, nullptr);
        }
    );

    const TypeInfo* ShiftInstruction::getType() const
    {
        return &E_SHIFTINSTRUCTION_TYPEINFO;
    }

    ShiftInstruction::ShiftInstruction(State* x, State* y)
    : VoidInstruction()
    {
        /* [0x08] */ destinationState = x;
        /* [0x0C] */ currentState = y;

        /* [0x10] */ groupCount = 0;
        /* [0x14] */ groupMaxLength = 0;
        /* [0x18] */ group = nullptr;
    }

    ShiftInstruction::~ShiftInstruction()
    {
        if (nullptr != group)
        {
            delete[](group);
        }
    }


    ////////////////////////////////////////////////////////////////
    // Unknown structure
    // <kao2.0058AF9C> (contructor)
    // <kao2.0058AFB2> (serialization)
    ////////////////////////////////////////////////////////////////

    ShiftInstructionBase::ShiftInstructionBase()
    {
        unknown_00 = nullptr;
        unknown_04 = nullptr;

        anim_id = (-1);
    }

    void ShiftInstructionBase::serialize(Archive &ar)
    {
        if (ar.getVersion() <= 0x88)
        {
            ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_00, &E_ANIM_TYPEINFO);
        }
        else
        {
            ar.readOrWrite(&anim_id, 0x04);
        }

        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_04, &E_REFCOUNTER_TYPEINFO);
    }


    ////////////////////////////////////////////////////////////////
    // ShiftInstruction serialization
    // <kao2.0058FB40>
    ////////////////////////////////////////////////////////////////
    void ShiftInstruction::serialize(Archive &ar)
    {
        int32_t i;

        /* [0x08] Destination State link */
        ar.serialize((eObject**)&destinationState, &E_STATE_TYPEINFO);

        /* [0x0C] Currrent State link */
        ar.serialize((eObject**)&currentState, &E_STATE_TYPEINFO);

        if (ar.getVersion() >= 0x70)
        {
            if (ar.isInReadMode())
            {
                if (nullptr != group)
                {
                    delete[](group);
                }

                ar.readOrWrite(&groupMaxLength, 0x04);

                group = new ShiftInstructionBase [groupMaxLength];

                for (i = 0; i < groupMaxLength; i++)
                {
                    group[i].serialize(ar);

                    groupCount = (i+1);
                }
            }
            else
            {
                ar.readOrWrite(&groupCount, 0x04);

                for (i = 0; i < groupCount; i++)
                {
                    group[i].serialize(ar);
                }
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // ShiftInstruction: save to text file
    ////////////////////////////////////////////////////////////////
    void ShiftInstruction::saveInstructionToTextFile(FileOperator &file, int32_t indentation) const
    {
        eString result;

        State* test_state;

        ArFunctions::writeNewLine(file, indentation);

        file << "shift ";

        if (nullptr != destinationState)
        {
            result = destinationState->getStringRepresentation();

            test_state = destinationState->getOwner();

            while (nullptr != test_state)
            {
                if (currentState != test_state)
                {
                    result = test_state->getStringRepresentation() + "::" + result;

                    test_state = test_state->getOwner();
                }
                else
                {
                    test_state = nullptr;
                }
            }

            file << result;
        }
        else
        {
            file << "< EMPTY_STATE >";
        }

        if (groupCount > 0)
        {
            if (nullptr != group[0].unknown_04)
            {
                file << "[";

                file << group[0].unknown_04->getStringRepresentation();

                file << "]";
            }
        }
    }

}
