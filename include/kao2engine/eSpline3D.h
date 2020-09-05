#ifndef H_KAO2AR_SPLINE3D
#define H_KAO2AR_SPLINE3D

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Spline Vertex structure
    ////////////////////////////////////////////////////////////////

    struct eSplineVertexBase
    {
        /*** Properties ***/

            /*[0x00-0x20]*/ ePoint3 position[3];
            /*[0x24]*/ eString name;

        /*** Methods ***/

            eSplineVertexBase();

            void serializeSplineJoint(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eSpline3D interface
    ////////////////////////////////////////////////////////////////

    class eSpline3D : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t verticesCount;
            /*[0x0C]*/ int32_t verticesMaxLength;
            /*[0x10]*/ eSplineVertexBase* vertices;

            /*[0x14]*/ float unknown_14;

        /*** Methods ***/

        public:

            eSpline3D();
            ~eSpline3D();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;

            void renderSpline(bool use_outline) const;

            void clearVertices();
            void addVertex(ePoint3 new_pos_a, ePoint3 new_pos_b, ePoint3 new_pos_c, eString new_name);

            int32_t getVerticesCount() const;
            ePoint3 getVertexPosition(int32_t vertex_id, int32_t param_id) const;
            void setVertexPosition(int32_t vertex_id, int32_t param_id, ePoint3 new_position);

            void splineGetSegment(ePoint3 &result, float time) const;

        private:

            void splineGetPoint(ePoint3 &result, float time) const;
    };


    ////////////////////////////////////////////////////////////////
    // eSpline3D TypeInfo
    // <kao2.004A6970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINE3D_ID = 0x64716E01;

    extern TypeInfo E_SPLINE3D_TYPEINFO;

}

#endif
