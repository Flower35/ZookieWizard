#ifndef H_KAO2AR_SPLINE3D
#define H_KAO2AR_SPLINE3D

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    ////////////////////////////////////////////////////////////////
    // Spline Joint structure
    ////////////////////////////////////////////////////////////////

    struct eSplineJointBase
    {
        /*** Properties ***/

            /*[0x00-0x08]*/ float unknown_00[3];
            /*[0x0C-0x14]*/ float unknown_0C[3];
            /*[0x18-0x20]*/ float unknown_18[3];
            /*[0x24]*/ eString name;

        /*** Methods ***/

            eSplineJointBase();

            void serializeSplineJoint(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eSpline3D interface
    ////////////////////////////////////////////////////////////////

    class eSpline3D : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ int32_t jointsCount;
            /*[0x0C]*/ int32_t jointsMaxLength;
            /*[0x10]*/ eSplineJointBase* joints;

            /*[0x14]*/ float unknown_14;

        /*** Methods ***/

        public:

            eSpline3D();
            ~eSpline3D();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSpline3D TypeInfo
    // <kao2.004A6970> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINE3D_ID = 0x64716E01;

    extern TypeInfo E_SPLINE3D_TYPEINFO;

}

#endif
