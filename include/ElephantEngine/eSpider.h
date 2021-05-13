#ifndef H_KAO2AR_SPIDER
#define H_KAO2AR_SPIDER

#include <ElephantEngine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eSpider interface
    // <kao2.005CF040> (vptr)
    ////////////////////////////////////////////////////////////////

    class eSpider : public Gadget
    {
        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*(...)*/
            /*[0x44]*/

        /*** Methods ***/

        public:

            eSpider();
            ~eSpider();

        private:

            void createFromOtherObject(const eSpider &other);

        public:

            eSpider(const eSpider &other);
            eSpider& operator = (const eSpider &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eSpider TypeInfo
    // <kao2.0043AE60> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPIDER_ID = 0x3B9365F6;

    extern TypeInfo E_SPIDER_TYPEINFO;

}

#endif
