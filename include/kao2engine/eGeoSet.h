#ifndef H_KAO2AR_GEOSET
#define H_KAO2AR_GEOSET

#include <kao2engine/eRefCounter.h>

#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{
    class ePhyTriMesh;

    ////////////////////////////////////////////////////////////////
    // eGeoSet interface
    ////////////////////////////////////////////////////////////////

    class eGeoSet : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t unknown_08;
            /*[0x0C]*/ int32_t indicesCount;
            /*[0x10]*/ int32_t texCoordsCount;
            /*[0x14]*/ eGeoArray<ushort>* indicesOffsets;
            /*[0x18]*/ eGeoArray<ushort>* indicesArray;
            /*[0x1C-0x20]*/ eGeoArray<ePoint4>* verticesArray[2];
            /*[0x24-0x28]*/ eGeoArray<ePoint4>* normalsArray[2];
            /*[0x2C-0x38]*/ eGeoArray<ePoint2>* texCoordsArray[4];
            /*[0x3C]*/ eGeoArray<ePoint4>* colorsArray;
            /*[0x40-0x4C]*/ int32_t texCoordsId[4];
            /*[0x50]*/ GLuint displayList;
            /*[0x54]*/ int32_t verticesCurrent;
            /*[0x58]*/ ePhyTriMesh* phy;
            /*[0x5C]*/ eGeoArray<eABB>* unknown_5C;


        /*** Methods ***/

        public:

            eGeoSet();
            ~eGeoSet();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void draw(GLuint tex_name);
            void generateDisplayList(int32_t texID, bool c);
            void prepareForDrawing();
    };


    ////////////////////////////////////////////////////////////////
    // eGeoSet TypeInfo
    // <kao2.0046D7C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOSET_ID = 0x3004;

    extern TypeInfo E_GEOSET_TYPEINFO;

}

#endif
