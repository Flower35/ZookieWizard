#ifndef H_KAO2AR_SPLINEBASE
#define H_KAO2AR_SPLINEBASE

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{
    class eBezierSplineNode;

    ////////////////////////////////////////////////////////////////
    // eSplineBase interface
    ////////////////////////////////////////////////////////////////

    class eSplineBase : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/ eBezierSplineNode* unknown_10;
            /*(...)*/
            /*[0x24]*/

        /*** Methods ***/

        public:

            eSplineBase();
            ~eSplineBase();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSplineBase TypeInfo
    // <kao2.0043E670> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINEBASE_ID = 0x3BB4FDE7;

    extern TypeInfo E_SPLINEBASE_TYPEINFO;

}

#endif
