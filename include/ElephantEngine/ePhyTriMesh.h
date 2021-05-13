#ifndef H_KAO2AR_PHYTRIMESH
#define H_KAO2AR_PHYTRIMESH

#include <ElephantEngine/eModifier.h>

#include <ElephantEngine/eGeoArray.h>

namespace ZookieWizard
{
    class eTransform;
    class eTriMesh;

    class eGeoSet;
    class eMorpherMod;

    ////////////////////////////////////////////////////////////////
    // Bone Structure
    ////////////////////////////////////////////////////////////////

    struct eBoneBase
    {
        /*** Properties ***/

            eTransform* xform;
            eMatrix4x4 matrix;

        /*** Methods ***/

            eBoneBase();

            void serializeBone(Archive &ar);
    };

    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh interface
    // <kao2.005D210C> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePhyTriMesh : public eModifier
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eTriMesh* trimeshLink;
            /*[0x0C]*/ eGeoSet* geosetLink;
            /*[0x10]*/ eGeoArray<ePhyVertex>* phyVertices;

            /*[0x14]*/ int32_t bonesCount;
            /*[0x18]*/ int32_t bonesMaxLength;
            /*[0x1C]*/ eBoneBase* bones;

            /*[0x20]*/ eGeoArray<ePoint4>* defaultVertices;
            /*[0x24]*/ eGeoArray<ePoint4>* defaultNormals;
            /*[0x28]*/ eMorpherMod* morph;

        /*** Methods ***/

        public:

            ePhyTriMesh(eTriMesh* x, eGeoSet* y);
            ~ePhyTriMesh();

        private:

            void createFromOtherObject(const ePhyTriMesh &other);

        public:

            ePhyTriMesh(const ePhyTriMesh &other);
            ePhyTriMesh& operator = (const ePhyTriMesh &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;
            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << ePhyTriMesh >> */

            void deleteBones();

            void transformVertices(eSRP &new_transform);

            void prepareMatrices(bool update) const;
            void animateVertices();

            eTransform* getArmatureParent() const;

        private:

            /* << ePhyTriMesh >> */

            void clearNewPhyTriMesh(eTriMesh* x, eGeoSet* y);
            void clearExistingPhyTriMesh();
    };


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh TypeInfo
    // <kao2.004B16E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PHYTRIMESH_ID = 0x3003;

    extern TypeInfo E_PHYTRIMESH_TYPEINFO;

}

#endif
