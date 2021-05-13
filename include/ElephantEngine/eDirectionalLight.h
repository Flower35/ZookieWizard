#ifndef H_KAO2AR_DIRECTIONALLIGHT
#define H_KAO2AR_DIRECTIONALLIGHT

#include <ElephantEngine/eLight.h>

namespace ZookieWizard
{
    class eTransform;

    ////////////////////////////////////////////////////////////////
    // eDirectionalLight interface
    // <kao2.005D0E18> (vptr)
    ////////////////////////////////////////////////////////////////

    class eDirectionalLight : public eLight
    {
        /*** Properties ***/

        protected:

            /*[0x6C-0x74]*/ ePoint3 position;
            /*[0x78]*/ eTransform* target;

        /*** Methods ***/

        public:

            eDirectionalLight();
            ~eDirectionalLight();

        private:

            void createFromOtherObject(const eDirectionalLight &other);

        public:

            eDirectionalLight(const eDirectionalLight &other);
            eDirectionalLight& operator = (const eDirectionalLight &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;

            /* << eNode >> */

            void assertNodeLinksSameArchive() override;

            void renderNode(eDrawContext &draw_context) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eLight >> */

            /*[[vptr]+0x74]*/ void bindLight(int32_t light_id) const override;

            /* << eDirectionalLight >> */

            ePoint3 getPosition() const;
            void setPosition(ePoint3 &new_position);

            eTransform* getLightTarget() const;
            void setLightTarget(eTransform* new_target);
    };


    ////////////////////////////////////////////////////////////////
    // eDirectionalLight TypeInfo
    // <kao2.0047FC60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_DIRECTIONALLIGHT_ID = 0x03454501;

    extern TypeInfo E_DIRECTIONALLIGHT_TYPEINFO;

}

#endif
