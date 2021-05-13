#ifndef H_KAO2AR_GEOEDGE
#define H_KAO2AR_GEOEDGE

#include <ElephantEngine/eGeometry.h>

#include <ElephantEngine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoEdge interface
    // <kao2.005E1030> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGeoEdge : public eGeometry
    {
        /*** Properties ***/

        protected:

            /*[0x58]*/ eGeoArray<ePoint4>* edges;

        /*** Methods ***/

        public:

            eGeoEdge();
            ~eGeoEdge();

        private:

            void createFromOtherObject(const eGeoEdge &other);

        public:

            eGeoEdge(const eGeoEdge &other);
            eGeoEdge& operator = (const eGeoEdge &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            void renderNode(eDrawContext &draw_context) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id);

            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;
    };


    ////////////////////////////////////////////////////////////////
    // eGeoEdge TypeInfo
    // <kao2.005ADD70> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOEDGE_ID = 0x034567FE;

    extern TypeInfo E_GEOEDGE_TYPEINFO;

}

#endif
