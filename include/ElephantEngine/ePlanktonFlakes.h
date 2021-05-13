#ifndef H_KAO2AR_PLANKTONFLAKES
#define H_KAO2AR_PLANKTONFLAKES

#include <ElephantEngine/eForrestFlakes.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // ePlanktonFlakes interface
    // <kao2.005D71B0> (vptr)
    ////////////////////////////////////////////////////////////////

    class ePlanktonFlakes : public eForrestFlakes
    {
        /*** Methods ***/

        public:

            ePlanktonFlakes();
            ~ePlanktonFlakes();

        private:

            void createFromOtherObject(const ePlanktonFlakes &other);

        public:

            ePlanktonFlakes(const ePlanktonFlakes &other);
            ePlanktonFlakes& operator = (const ePlanktonFlakes &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // ePlanktonFlakes TypeInfo
    // <kao2.00565DA0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PLANKTONFLAKES_ID = 0x0323A7E7;

    extern TypeInfo E_PLANKTONFLAKES_TYPEINFO;

}

#endif
