#ifndef H_KAO2AR_HEROPARENT
#define H_KAO2AR_HEROPARENT

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eHeroParent interface
    // <kao2.005D5038> (vptr)
    ////////////////////////////////////////////////////////////////

    class eHeroParent : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x54]*/

        /*** Methods ***/

        public:

            eHeroParent();
            ~eHeroParent();

        private:

            void createFromOtherObject(const eHeroParent &other);

        public:

            eHeroParent(const eHeroParent &other);
            eHeroParent& operator = (const eHeroParent &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eHeroParent TypeInfo
    // <kao2.00518110> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_HEROPARENT_ID = 0x00002CDE;

    extern TypeInfo E_HEROPARENT_TYPEINFO;

}

#endif
