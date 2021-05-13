#ifndef H_KAO2AR_WATERCIRCLES
#define H_KAO2AR_WATERCIRCLES

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eWaterCircles interface
    // <kao2.005CF770> (vptr)
    ////////////////////////////////////////////////////////////////

    class eWaterCircles : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x60]*/

        /*** Methods ***/

        public:

            eWaterCircles();
            ~eWaterCircles();

        private:

            void createFromOtherObject(const eWaterCircles &other);

        public:

            eWaterCircles(const eWaterCircles &other);
            eWaterCircles& operator = (const eWaterCircles &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eWaterCircles TypeInfo
    // <kao2.00448D20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_WATERCIRCLES_ID = 0x3DC2F58A;

    extern TypeInfo E_WATERCIRCLES_TYPEINFO;

}

#endif
