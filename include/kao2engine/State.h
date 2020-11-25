#ifndef H_KAO2AR_STATE
#define H_KAO2AR_STATE

#include <kao2engine/eRefCounter.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class VoidInstruction;
    class eNode;

    ////////////////////////////////////////////////////////////////
    // New Gadgets structure
    ////////////////////////////////////////////////////////////////

    struct NewGadgetBase
    {
        /*** Properties ***/

        public:

            /*[0x00]*/ eString name;
            /*[0x04]*/ TypeInfo* gadgetType;
            /*[0x08]*/ eRefCounter* unknown;
            /*[0x0C]*/ int32_t id;

        /*** Methods ***/

        public:

            NewGadgetBase();
            ~NewGadgetBase();

            void serialize(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // State interface
    // <kao2.005D8088>
    ////////////////////////////////////////////////////////////////

    class State : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ bool isDefault;
            /*[0x09]*/ bool isTerminal;
            /*[0x0C]*/ eString name;
            /*[0x10]*/ State* ownerState;
            /*[0x14 - 0x1C]*/ Collection<ArFunctions::serialize_eRefCounter> subStates;
            /*[0x20]*/ State* defaultState;
            /*[0x24 - 0x2C]*/ Collection<ArFunctions::serialize_StringSection> stringSections;
            /*[0x30 - 0x38]*/ Collection<ArFunctions::serialize_Property> properties;
            /*[0x3C - 0x44]*/ VoidInstruction* instructions[3];
            /*[0x48 - 0x50]*/ Collection<ArFunctions::serialize_eRefCounter> whens;
            /*[0x54 - 0x5C]*/ Collection<ArFunctions::serialize_eRefCounter> gadgets;
            /*[0x60 - 0x68]*/ Collection<ArFunctions::serialize_eRefCounter> nodeRefs;
            /*[0x6C]*/ eString anim;
            /*[0x70]*/ int32_t unknown_70;
            /*[0x74]*/ eString unknown_74;

            /*[0x78]*/ int32_t unknown_78;
            int32_t newGadgets_count;
            int32_t newGadgets_maxLength;
            NewGadgetBase* newGadgets;

        /*** Methods ***/

        public:

            State(eString s, State* x);
            ~State();

        private:

            void createFromOtherObject(const State &other);

        public:

            State(const State &other);
            State& operator = (const State &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            eString getStringRepresentation() const override;
            eString getLogPrintMessage() const override;

            /* << State >> */

            void saveStateToTextFile(FileOperator &file, int32_t indentation) const;

            State* getOwner() const;

            void removeNoderefsWithSpecifiedLink(eNode* target);

        private:

            /* << State >> */

            void clearNewState();
    };


    ////////////////////////////////////////////////////////////////
    // State TypeInfo
    // <kao2.00595CE0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_STATE_ID = 0x0AA34563;

    extern TypeInfo E_STATE_TYPEINFO;

}

#endif
