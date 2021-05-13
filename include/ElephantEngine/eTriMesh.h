#ifndef H_KAO2AR_TRIMESH
#define H_KAO2AR_TRIMESH

#include <ElephantEngine/eGeometry.h>

namespace ZookieWizard
{
    class eGeoSet;
    class ePhyTriMesh;

    ////////////////////////////////////////////////////////////////
    // eTriMesh interface
    // <kao2.005D0568> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTriMesh : public eGeometry
    {
        /*** Properties ***/

        protected:

            /*[0x58]*/ eGeoSet* geo;

            /*[0x64]*/ ePhyTriMesh* modifier;

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

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eNode >> */

            void destroyNode() override;

            void renderNode(eDrawContext &draw_context) const override;

            void editingRebuildCollision() override;
            void editingClearCollision(bool create_empty_pointer) override;
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
