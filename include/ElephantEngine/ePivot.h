#ifndef H_KAO2AR_PIVOT
#define H_KAO2AR_PIVOT

#include <ElephantEngine/eTransform.h>

#include <ElephantBase/eAnimate.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePivot interface
    // <kao2.005D1140> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePivot : public eTransform
    {
        /*** Properties ***/

        protected:

            /*[0x00AC-0x00E4]*/ eAnimate animations;
            /*[0x00E8-0x00F0]*/ // (collection)

        /*** Methods ***/

        public:

            ePivot();
            ~ePivot();

        private:

            void createFromOtherObject(const ePivot &other);

        public:

            ePivot(const ePivot &other);
            ePivot& operator = (const ePivot &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;

            /* << eNode >> */

            void updateBeforeRendering(eDrawContext &draw_context) override;
            void renderNode(eDrawContext &draw_context) const override;

            void editingNewNodeSetup() override;

            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << ePivot >> */

            void rebuildEmptyAnimState(bool is_root);

            void animClearTracks();
            void animAddTrack(eString anim_name, float first_frame, float frames_count);
            void animRemoveTrack(eString anim_name);
    };


    ////////////////////////////////////////////////////////////////
    // ePivot TypeInfo
    // <kao2.00487060> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PIVOT_ID = 0x00AA3456;

    extern TypeInfo E_PIVOT_TYPEINFO;

}

#endif
