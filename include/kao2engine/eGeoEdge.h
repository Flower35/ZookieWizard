#ifndef H_KAO2AR_GEOEDGE
#define H_KAO2AR_GEOEDGE

#include <kao2engine/eGeometry.h>

#include <kao2engine/eGeoArray.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoEdge interface
    ////////////////////////////////////////////////////////////////

    class eGeoEdge : public eGeometry
    {

        /*** Properties ***/

        protected:

            /*[0x58]*/ eGeoArray<ePoint4>* unknown_58;

        /*** Methods ***/

        public:

            eGeoEdge();
            ~eGeoEdge();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eGeoEdge TypeInfo
    // <kao2.005ADDA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOEDGE_ID = 0x034567FE;

    extern TypeInfo E_GEOEDGE_TYPEINFO;

}

#endif
