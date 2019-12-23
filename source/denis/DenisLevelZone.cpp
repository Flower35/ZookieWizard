#include <denis/DenisLevelZone.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Event Zone: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelZone::DenisLevelZone()
    {
        std::memset(name, 0x00, 32);

        sampleID = (-1);

        type = 0;
    }


    ////////////////////////////////////////////////////////////////
    // Event Zone: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelZone::~DenisLevelZone() {}


    ////////////////////////////////////////////////////////////////
    // Event Zone: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelZone::serialize(DenisFileOperator &file)
    {
        /* Zone name */

        file.readOrWrite(name, 0x20);

        /* Boundaries */

        boundBox.serialize(file);

        /* Ambient sample ID */

        file.readOrWrite(&sampleID, 0x04);

        /* Zone type */

        file.readOrWrite(&type, 0x04);
    }

}
