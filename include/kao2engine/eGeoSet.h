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
            /*[0x0C]*/ int32_t defaultVertexCount;
            /*[0x10]*/ int32_t texCoordsCount;
            /*[0x14]*/ eGeoArray<ushort>* indicesOffsets;
            /*[0x18]*/ eGeoArray<ushort>* indicesArray;
            /*[0x1C-0x20]*/ eGeoArray<ePoint4>* verticesArray[2];
            /*[0x24-0x28]*/ eGeoArray<ePoint4>* normalsArray[2];
            /*[0x2C-0x38]*/ eGeoArray<ePoint2>* texCoordsArray[4];
            /*[0x3C]*/ eGeoArray<ePoint4>* colorsArray;
            /*[0x40-0x4C]*/ int32_t texCoordsId[4];
            /*[0x50]*/ GLuint displayList;
            /*[0x54]*/ int32_t currentSet;
            /*[0x58]*/ ePhyTriMesh* phy;
            /*[0x5C]*/ eGeoArray<eABB>* aabbTree;


        /*** Methods ***/

        private:

            void displayVertexBufferObject(int32_t texID, bool use_color) const;

        public:

            eGeoSet();
            ~eGeoSet();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            int32_t getTextureCoordsCount() const;
            int32_t getTextureId(int32_t i) const;

            void draw(int32_t draw_flags, int32_t texID) const;
            void prepareForDrawing();

            void setVerticesArray(eGeoArray<ePoint4>* new_vertices_array);
            void setNormalsArray(eGeoArray<ePoint4>* new_normals_array);
            void setIndicesOffsets(eGeoArray<ushort>* new_indices_offets);
            void setIndicesArray(eGeoArray<ushort>* new_indices_array);
            void setTextureCoordsArray(eGeoArray<ePoint2>* new_uv_array);
            void setColorsArray(eGeoArray<ePoint4>* new_colors_array);
            void setTwoIntegers(int32_t a, int32_t b);

            eGeoArray<ePoint4>* getVerticesArray() const;
            eGeoArray<ePoint4>* getNormalsArray() const;
            eGeoArray<ePoint2>* getTextureCoordsArray() const;
            eGeoArray<ePoint4>* getColorsArray() const;
            eGeoArray<ushort>* getIndicesOffsets() const;
            eGeoArray<ushort>* getIndicesArray() const;
            ePhyTriMesh* getPhyTriMesh() const;

            void transformVertices(eSRP &new_transform, eString &mesh_name, ePoint3 &box_min, ePoint3 &box_max);
            void buildAabbTree(eString &mesh_name);
            void clearAabbTree();
    };


    ////////////////////////////////////////////////////////////////
    // eGeoSet TypeInfo
    // <kao2.0046D7C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOSET_ID = 0x3004;

    extern TypeInfo E_GEOSET_TYPEINFO;

}

#endif
