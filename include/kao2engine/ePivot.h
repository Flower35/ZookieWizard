#ifndef H_KAO2AR_PIVOT
#define H_KAO2AR_PIVOT

#include <kao2engine/eTransform.h>

#include <kao2ar/eAnimate.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePivot interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) const override;

            bool renderObject(int32_t draw_flags, eAnimate* anim, eSRP &parent_srp, eMatrix4x4 &parent_matrix, int32_t marked_id) override;

            void rebuildEmptyAnimState();

            void animAddTrack(eString anim_name, float first_frame, float frames_count);
            void animRemoveTrack(eString anim_name);
    };


    ////////////////////////////////////////////////////////////////
    // ePivot TypeInfo
    // <kao2.0x00487090> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PIVOT_ID = 0x00AA3456;

    extern TypeInfo E_PIVOT_TYPEINFO;

}

#endif
