#ifndef H_KAO2AR_GEOSET
#define H_KAO2AR_GEOSET

#include <ElephantEngine/eRefCounter.h>

#include <ElephantEngine/eGeoArray.h>

namespace ZookieWizard
{
    class ePhyTriMesh;

    ////////////////////////////////////////////////////////////////
    // eGeoSet interface
    // <kao2.005D0610> (vptr)
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
            /*[0x40-0x4C]*/ int32_t texMappingTypes[4];
            /*[0x50]*/ GLuint displayList;
            /*[0x58]*/ ePhyTriMesh* modifier;
            /*[0x5C]*/ eGeoArray<eABB>* aabbTree;

            eGeoArray<ePoint3>* unknown_points[2];
            /*[0x61]*/ uint8_t unknown_61;
            /*[0x62]*/ uint8_t unknown_62;
            /*[0x63]*/ uint8_t unknown_63;
            /*[0x64]*/ uint8_t* unknown_64;

            /*[0x6C]*/ eGeoArray<ePhyVertex>* phyVertices;

        /*** Methods ***/

        public:

            eGeoSet();
            ~eGeoSet();

        private:

            void createFromOtherObject(const eGeoSet &other);

        public:

            eGeoSet(const eGeoSet &other);
            eGeoSet& operator = (const eGeoSet &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eGeoSet >> */

            void draw(int32_t draw_flags, int32_t texID) const;
            void prepareForDrawing();

            int32_t getTextureCoordsCount() const;

            void setVerticesArray(int32_t i, eGeoArray<ePoint4>* new_vertices_array);
            void setNormalsArray(int32_t i, eGeoArray<ePoint4>* new_normals_array);
            void setPhyVertices(eGeoArray<ePhyVertex>* new_phyvertices);
            void setIndicesOffsets(eGeoArray<ushort>* new_indices_offets);
            void setIndicesArray(eGeoArray<ushort>* new_indices_array);
            void setTextureCoordsArray(int32_t i, eGeoArray<ePoint2>* new_uv_array);
            void setTexMappingType(int32_t i, int32_t mapping_type);
            void setColorsArray(eGeoArray<ePoint4>* new_colors_array);
            void setPhyTriMesh(ePhyTriMesh* new_modifier);
            void setTwoIntegers(int32_t a, int32_t b);

            eGeoArray<ePoint4>* getVerticesArray(int32_t i) const;
            eGeoArray<ePoint4>* getNormalsArray(int32_t i) const;
            eGeoArray<ePhyVertex>* getPhyVertices() const;
            eGeoArray<ePoint2>* getTextureCoordsArray(int32_t i) const;
            int32_t getTexMappingType(int32_t i) const;
            eGeoArray<ePoint4>* getColorsArray() const;
            eGeoArray<ushort>* getIndicesOffsets() const;
            eGeoArray<ushort>* getIndicesArray() const;
            ePhyTriMesh* getPhyTriMesh() const;

            void transformVertices(eSRP &new_transform, eString &mesh_name, ePoint3 &box_min, ePoint3 &box_max);
            void buildAabbTree(eString &mesh_name);
            void clearAabbTree();

        private:

            /* << eGeoSet >> */

            void clearExistingGeoSet();

            void displayVertexBufferObject(int32_t texID, bool use_color) const;
    };


    ////////////////////////////////////////////////////////////////
    // eGeoSet TypeInfo
    // <kao2.0046D790> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOSET_ID = 0x3004;

    extern TypeInfo E_GEOSET_TYPEINFO;

}

#endif
