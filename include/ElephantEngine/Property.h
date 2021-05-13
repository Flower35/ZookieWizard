#ifndef H_KAO2AR_PROPERTY
#define H_KAO2AR_PROPERTY

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{
    class Gadget;

    ////////////////////////////////////////////////////////////////
    // Property interface
    ////////////////////////////////////////////////////////////////

    class Property : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eString name;
            /*[0x0C]*/ int32_t type;
            /*[0x10]*/ void* numValue;
            /*[0x14]*/ eString strValue;
            /*[0x18]*/ Property* unknown_18;
            /*[0x1C]*/ Gadget* gadget;
            /*[0x20]*/ int32_t offset;
            int16_t unknown_new_id;

        /*** Methods ***/

        public:

            Property();
            ~Property();

            void serialize(Archive &ar) override;
            const TypeInfo* getType() const override;

            eString generateScriptText() const override;

            bool compareGadgets(Gadget* source) const;
    };


    ////////////////////////////////////////////////////////////////
    // Property TypeInfo
    // <kao2.00592DC0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PROPERTY_ID = 0xFFFFFFFF;

    extern TypeInfo E_PROPERTY_TYPEINFO;

}

#endif
