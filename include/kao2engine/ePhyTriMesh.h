#ifndef H_KAO2AR_PHYTRIMESH
#define H_KAO2AR_PHYTRIMESH

#include <kao2engine/eModifier.h>

#include <kao2engine/eGeoArray.h>

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
    ////////////////////////////////////////////////////////////////

    class ePhyTriMesh : public eModifier
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ eTriMesh* tri;
            /*[0x0C]*/ eGeoSet* geo;
            /*[0x10]*/ eGeoArray<ePhyVertex>* vertices;
            
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            eString getLogPrintMessage() override;

            void prepareMatrices(bool update);
            void animateVertices();
    };


    ////////////////////////////////////////////////////////////////
    // ePhyTriMesh TypeInfo
    // <kao2.004B1710> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PHYTRIMESH_ID = 0x3003;

    extern TypeInfo E_PHYTRIMESH_TYPEINFO;

}

#endif
