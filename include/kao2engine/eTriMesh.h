#ifndef H_KAO2AR_TRIMESH
#define H_KAO2AR_TRIMESH

#include <kao2engine/eGeometry.h>

namespace ZookieWizard
{
    class eGeoSet;

    ////////////////////////////////////////////////////////////////
    // eTriMesh interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            void renderObject(eAnimate* anim, int32_t draw_flags, eSRP &parent_srp) override;

            eGeoSet* getGeoset() const;
            void setGeoset(eGeoSet* new_geo);
    };


    ////////////////////////////////////////////////////////////////
    // eTriMesh TypeInfo
    // <kao2.0046D6F0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TRIMESH_ID = 0x3005;

    extern TypeInfo E_TRIMESH_TYPEINFO;

}

#endif
