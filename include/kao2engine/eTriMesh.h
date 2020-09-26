#ifndef H_KAO2AR_TRIMESH
#define H_KAO2AR_TRIMESH

#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{
    class eGeoSet;

    ////////////////////////////////////////////////////////////////
    // eTriMesh interface
    // <kao2.005D0568> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTriMesh : public eGeometry
    {
        /*** Properties ***/

        protected:

            /*[0x58]*/ eGeoSet* geo;

        /*** Methods ***/

        public:

            eTriMesh();
            ~eTriMesh();

        private:

            void createFromOtherObject(const eTriMesh &other);

        public:

            eTriMesh(const eTriMesh &other);
            eTriMesh& operator = (const eTriMesh &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eNode >> */

            void destroyNode() override;

            void renderNode(eDrawContext &draw_context) const override;

            void editingRebuildCollision() override;
            void editingClearCollision() override;
            void editingApplyNewTransform(eSRP &new_transform, int32_t marked_id) override;

            /* << eTriMesh >> */

            eGeoSet* getGeoset() const;
            void setGeoset(eGeoSet* new_geo);
    };


    ////////////////////////////////////////////////////////////////
    // eTriMesh TypeInfo
    // <kao2.0046D6C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRIMESH_ID = 0x3005;

    extern TypeInfo E_TRIMESH_TYPEINFO;

}

#endif
