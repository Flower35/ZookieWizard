#include <denis/DenisLevelWObj.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // World Object Reference: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelWObj::DenisLevelWObj()
    {
        std::memset(name, 0x00, 32);

        vertexCount = 0;
    }


    ////////////////////////////////////////////////////////////////
    // World Object Reference: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelWObj::~DenisLevelWObj() {}


    ////////////////////////////////////////////////////////////////
    // World Object Reference: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelWObj::serialize(DenisFileOperator &file)
    {
        /* Object name */

        file.readOrWrite(name, 0x20);

        /* Vertices count */

        file.readOrWrite(&vertexCount, 0x04);

        /* (--dsp--) load object to validate vertices count */
    }

}
