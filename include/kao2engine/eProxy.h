#ifndef H_KAO2AR_PROXY
#define H_KAO2AR_PROXY

#include <kao2engine/eTransform.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eProxy interface
    ////////////////////////////////////////////////////////////////

    class eProxy : public eTransform
    {

        /*** Properties ***/

        protected:

            /*[0xAC]*/ eString targetFile;
            /*[0xB0]*/ int32_t category;

            // 0 = "(particle)"
            // 1 = "(hero)"
            // 3 = "(enemy)"
            // 4 = "(fluff)"
            // 5 = "(geoproxy)"
            // 6 = "(object)"

        /*** Methods ***/

        private:

            bool canBeLoadedOrExported(int32_t &ar_flags);

        public:

            eProxy();
            ~eProxy();

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void renderObject(float time, int32_t draw_flags) override;
    };


    ////////////////////////////////////////////////////////////////
    // eProxy TypeInfo
    // <kao2.00485610> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PROXY_ID = 0x13454032;

    extern TypeInfo E_PROXY_TYPEINFO;

}

#endif
