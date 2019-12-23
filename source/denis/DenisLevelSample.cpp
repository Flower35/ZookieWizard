#include <denis/DenisLevelSample.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // Level Ambient sample: constructor
    ////////////////////////////////////////////////////////////////

    DenisLevelSample::DenisLevelSample()
    {
        std::memset(name, 0x00, (8+1));
    }


    ////////////////////////////////////////////////////////////////
    // Level Ambient sample: destructor
    ////////////////////////////////////////////////////////////////

    DenisLevelSample::~DenisLevelSample() {}


    ////////////////////////////////////////////////////////////////
    // Level Ambient sample: serialization
    ////////////////////////////////////////////////////////////////

    void DenisLevelSample::serialize(DenisFileOperator &file)
    {
        int32_t dummy = 0;

        /* Sound filename */

        file.readOrWrite(name, 0x08);

        /* Unused (4 bytes) */

        file.readOrWrite(&dummy, 0x04);
    }

}
