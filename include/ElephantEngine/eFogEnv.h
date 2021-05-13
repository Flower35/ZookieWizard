#ifndef H_KAO2AR_FOGENV
#define H_KAO2AR_FOGENV

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eFogEnv interface
    // <kao2.005D0D08> (vptr)
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

        private:

            void createFromOtherObject(const eFogEnv &other);

        public:

            eFogEnv(const eFogEnv &other);
            eFogEnv& operator = (const eFogEnv &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eFogEnv >> */

            void getFogColor(float* values) const;
            float getFogStart() const;
            float getFogEnd() const;
            float getFogMax() const;

            void setFogColor(float* values);
            void setFogStart(float value);
            void setFogEnd(float value);
            void setFogMax(float value);
    };


    ////////////////////////////////////////////////////////////////
    // eFogEnv TypeInfo
    // <kao2.0047E7B0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_FOGENV_ID = 0x3F800002;

    extern TypeInfo E_FOGENV_TYPEINFO;

}

#endif
