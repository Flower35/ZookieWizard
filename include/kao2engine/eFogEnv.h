#ifndef H_KAO2AR_FOGENV
#define H_KAO2AR_FOGENV

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFogEnv interface
    ////////////////////////////////////////////////////////////////

    class eFogEnv : public eRefCounter
    {

        /*** Properties ***/

        protected:

            /*[0x08-0x10]*/ GLfloat color[4];
            /*[0x14]*/ GLfloat fogStart;
            /*[0x18]*/ GLfloat fogEnd;
            /*[0x1C]*/ GLfloat fogMax;

        /*** Methods ***/

        public:

            eFogEnv();
            ~eFogEnv();

            void serialize(Archive &ar) override;
            TypeInfo* getType() const override;
    };


    ////////////////////////////////////////////////////////////////
    // eFogEnv TypeInfo
    // <kao2.0047E7E0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOGENV_ID = 0x3F800002;

    extern TypeInfo E_FOGENV_TYPEINFO;

}

#endif
