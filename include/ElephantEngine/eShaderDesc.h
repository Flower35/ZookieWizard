#ifndef H_KAO2AR_SHADERDESC
#define H_KAO2AR_SHADERDESC

#include <ElephantEngine/eRefCounter.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eShaderDesc interface
    ////////////////////////////////////////////////////////////////

    class eShaderDesc : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ eString name;
            /*[0x0C]*/ int32_t params;

        /*** Methods ***/

        public:

            eShaderDesc(eString _name, int32_t _params);
            ~eShaderDesc();

        private:

            void createFromOtherObject(const eShaderDesc &other);

        public:

            eShaderDesc(const eShaderDesc &other);
            eShaderDesc& operator = (const eShaderDesc &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            eString getStringRepresentation() const override;

            /* << eShaderDesc >> */

            int32_t getParamsCount() const;
    };

}

#endif
