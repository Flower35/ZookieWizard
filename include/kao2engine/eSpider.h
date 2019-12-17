#ifndef H_KAO2AR_SPIDER
#define H_KAO2AR_SPIDER

#include <kao2engine/Gadget.h>

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

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eSpider TypeInfo
    // <kao2.0043AE90> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SPIDER_ID = 0x3B9365F6;

    extern TypeInfo E_SPIDER_TYPEINFO;

}

#endif
