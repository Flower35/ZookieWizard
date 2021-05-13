#ifndef H_KAO2AR_FOOTPRINTS
#define H_KAO2AR_FOOTPRINTS

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFootPrints interface
    // <kao2.005CF598> (vptr)
    ////////////////////////////////////////////////////////////////

    class eFootPrints : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x0010]*/
            /*(...)*/
            /*[0x0184]*/

        /*** Methods ***/

        public:

            eFootPrints();
            ~eFootPrints();

        private:

            void createFromOtherObject(const eFootPrints &other);

        public:

            eFootPrints(const eFootPrints &other);
            eFootPrints& operator = (const eFootPrints &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFootPrints TypeInfo
    // <kao2.00444810> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOOTPRINTS_ID = 0x3B46EC8F;

    extern TypeInfo E_FOOTPRINTS_TYPEINFO;

}

#endif
