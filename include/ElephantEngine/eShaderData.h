#ifndef H_KAO2AR_SHADERDATA
#define H_KAO2AR_SHADERDATA

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{
    class eShaderDesc;

    ////////////////////////////////////////////////////////////////
    // Shader parameters
    ////////////////////////////////////////////////////////////////

    class eShaderParam
    {
        /*** Properties ***/

        public:

            eString paramName;
            uint32_t paramType;

        protected:

            bool boolParam;
            int32_t intParam;
            float floatParam[4];

        /*** Methods ***/

        public:

            eShaderParam();
            ~eShaderParam();

        private:

            void createFromOtherObject(const eShaderParam &other);

        public:

            eShaderParam(const eShaderParam &other);
            eShaderParam& operator = (const eShaderParam &other);

            void serialize(Archive &ar);
    };


    ////////////////////////////////////////////////////////////////
    // eShaderData interface
    // <SaddleClub.009182E4> (vptr)
    ////////////////////////////////////////////////////////////////

    class eShaderData : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eShaderDesc* shaderDescription;
            /*[0x0C]*/ eShaderParam* shaderParameters;

        /*** Methods ***/

        public:

            eShaderData();
            ~eShaderData();

        private:

            void createFromOtherObject(const eShaderData &other);

        public:

            eShaderData(const eShaderData &other);
            eShaderData& operator = (const eShaderData &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            const TypeInfo* getType() const override;
            void serialize(Archive &ar) override;
    };


    ////////////////////////////////////////////////////////////////
    // eShaderData TypeInfo
    // <SaddleClub.008E32D0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_SHADERDATA_ID = 0x09021714;

    extern TypeInfo E_SHADERDATA_TYPEINFO;

}

#endif
