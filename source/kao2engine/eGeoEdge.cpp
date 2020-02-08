#include <kao2engine/eGeoEdge.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeoEdge interface
    // <kao2.005ADE30> (constructor)
    // <kao2.005ADF10> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GEOEDGE_TYPEINFO
    (
        E_GEOEDGE_ID,
        "eGeoEdge",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eGeoEdge;
        }
    );

    TypeInfo* eGeoEdge::getType() const
    {
        return &E_GEOEDGE_TYPEINFO;
    }

    eGeoEdge::eGeoEdge()
    : eGeometry()
    {
        unknown_58 = nullptr;

        flags |= 0x40000000;
    }

    eGeoEdge::~eGeoEdge()
    {
        unknown_58->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eGeoEdge serialization
    // <kao2.005AE000>
    ////////////////////////////////////////////////////////////////
    void eGeoEdge::serialize(Archive &ar)
    {
        eGeometry::serialize(ar);

        if (ar.getVersion() < 0x6A)
        {
            throw ErrorMessage
            (
                "eGeoEdge::serialize():\n" \
                "ar.version() 106 required!"
            );
        }

        /* [0x58] unknown */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&unknown_58, &E_GEOARRAY_EPOINT4_TYPEINFO);
    }

}
