#ifndef H_KAO2AR_FORRESTFLAKES
#define H_KAO2AR_FORRESTFLAKES

#include <ElephantEngine/eSnow.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eForrestFlakes interface
    // <kao2.005D6E28> (vptr)
    ////////////////////////////////////////////////////////////////

    class eForrestFlakes : public eSnow
    {
        /*** Methods ***/

        public:

            eForrestFlakes();
            ~eForrestFlakes();

        private:

            void createFromOtherObject(const eForrestFlakes &other);

        public:

            eForrestFlakes(const eForrestFlakes &other);
            eForrestFlakes& operator = (const eForrestFlakes &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eForrestFlakes TypeInfo
    // <kao2.005611D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FORRESTFLAKES_ID = 0x0323A7F7;

    extern TypeInfo E_FORRESTFLAKES_TYPEINFO;

}

#endif
