#ifndef H_KAO2AR_MULTITRANSFORMNODE
#define H_KAO2AR_MULTITRANSFORMNODE

#include <ElephantEngine/eTransform.h>
#include <ElephantEngine/eMultiTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMultiTransformNode interface
    // (Virtual node used to represent instances inside eMultiTransform)
    ////////////////////////////////////////////////////////////////

    class eMultiTransformNode : public eTransform
    {
        /*** Properties ***/

    protected:
        /*[0x00-0x08]*/ float dummy_rotationA[3];
        /*[0x0C]*/ uint8_t color[4];
        /*[0x10-0x18]*/ float dummy_rotationB[3];
        /*[0x1C]*/ float unknown_1C;
        /*[0x2C]*/ float unknown_2C;

    public:

        eMultiTransformNode();
        ~eMultiTransformNode();

    private:

        void createFromOtherObject(const eMultiTransformNode& other);

    public:

        eMultiTransformNode(const eMultiTransformNode& other);
        eMultiTransformNode& operator = (const eMultiTransformNode& other);
        eObject* cloneFromMe() const override;
        void setupInstance(eMultiTransformBase& transform_base);
        void setupBase(eMultiTransformBase& transform_base);

        /* << eObject >> */

        const TypeInfo* getType() const override;
        void serialize(Archive& ar) override;

        void dumpTreeAsJsonValue(JsonValue& output, bool dumpChildNodes) const override;
    };


    ////////////////////////////////////////////////////////////////
    // eMultiTransformNode TypeInfo
    ////////////////////////////////////////////////////////////////

    static const int E_MULTITRANSFORMNODE_ID = 0xABCDEF00;

    extern TypeInfo E_MULTITRANSFORMNODE_TYPEINFO;

}

#endif
