#ifndef H_KAO2AR_GEOEDGE
#define H_KAO2AR_GEOEDGE

#include <kao2engine/eGeometry.h>

#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoEdge interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderNode(eDrawContext &draw_context) const override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id);

            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;
    };


    ////////////////////////////////////////////////////////////////
    // eGeoEdge TypeInfo
    // <kao2.005ADDA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOEDGE_ID = 0x034567FE;

    extern TypeInfo E_GEOEDGE_TYPEINFO;

}

#endif
