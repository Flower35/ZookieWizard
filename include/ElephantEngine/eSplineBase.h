#ifndef H_KAO2AR_SPLINEBASE
#define H_KAO2AR_SPLINEBASE

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{
    class eBezierSplineNode;

    ////////////////////////////////////////////////////////////////
    // eSplineBase interface
    // <kao2.005CF380> (vptr)
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

        private:

            void createFromOtherObject(const eSplineBase &other);

        public:

            eSplineBase(const eSplineBase &other);
            eSplineBase& operator = (const eSplineBase &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSplineBase TypeInfo
    // <kao2.0043E640> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPLINEBASE_ID = 0x3BB4FDE7;

    extern TypeInfo E_SPLINEBASE_TYPEINFO;

}

#endif
