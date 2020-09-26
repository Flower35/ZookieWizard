#ifndef H_KAO2AR_BEZIERSPLINENODE
#define H_KAO2AR_BEZIERSPLINENODE

#include <kao2engine/eNode.h>

#include <kao2ar/Collection.h>

namespace ZookieWizard
{
    class eSpline3D;

    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode interface
    // <kao2.005D1CE8> (vptr)
    ////////////////////////////////////////////////////////////////

    class eBezierSplineNode : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C-0x44]*/ eSpline3D* spline;

        /*** Methods ***/

        public:

            eBezierSplineNode();
            ~eBezierSplineNode();

        private:

            void createFromOtherObject(const eBezierSplineNode &other);

        public:

            eBezierSplineNode(const eBezierSplineNode &other);
            eBezierSplineNode& operator = (const eBezierSplineNode &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void renderNode(eDrawContext &draw_context) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id);

            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eBezierSplineNode >> */

            void bezierSplineGetSegment(ePoint3 &result, float time) const;
    };


    ////////////////////////////////////////////////////////////////
    // eBezierSplineNode TypeInfo
    // <kao2.004A87F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_BEZIERSPLINENODE_ID = 0x00398884;

    extern TypeInfo E_BEZIERSPLINENODE_TYPEINFO;

}

#endif
