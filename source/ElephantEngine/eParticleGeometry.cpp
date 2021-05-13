#include <ElephantEngine/eParticleGeometry.h>
#include <ElephantBase/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleGeometry interface
    // <kao2.005618F0> (constructor)
    // <kao2.005583B0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_PARTICLEGEOMETRY_TYPEINFO
    (
        E_PARTICLEGEOMETRY_ID,
        "eParticleGeometry",
        &E_GEOMETRY_TYPEINFO,
        []() -> eObject*
        {
            return new eParticleGeometry;
        }
    );

    const TypeInfo* eParticleGeometry::getType() const
    {
        return &E_PARTICLEGEOMETRY_TYPEINFO;
    }

    eParticleGeometry::eParticleGeometry()
    : eGeometry()
    {
        /*[0xC0]*/ unknown_C0 = 0;
        /*[0x58]*/ unknown_58 = 0;
        /*[0xBC]*/ unknown_BC = 0;

        /*[0x00C4]*/ unknown_C4 = (-1);
    }

    eParticleGeometry::~eParticleGeometry()
    {}


    ////////////////////////////////////////////////////////////////
    // eParticleGeometry: cloning the object
    ////////////////////////////////////////////////////////////////

    void eParticleGeometry::createFromOtherObject(const eParticleGeometry &other)
    {
        unknown_58 = other.unknown_58;

        unknown_BC = other.unknown_BC;
        unknown_C0 = other.unknown_C0;
        unknown_C4 = other.unknown_C4;
    }

    eParticleGeometry::eParticleGeometry(const eParticleGeometry &other)
    : eGeometry(other)
    {
        createFromOtherObject(other);
    }

    eParticleGeometry& eParticleGeometry::operator = (const eParticleGeometry &other)
    {
        if ((&other) != this)
        {
            eGeometry::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eParticleGeometry::cloneFromMe() const
    {
        return new eParticleGeometry(*this);
    }

}
