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

            void writeStructureToTextFile(FileOperator &file, int32_t indentation) override;

            void renderObject(eAnimate* anim, int32_t draw_flag, eSRP &parent_srp) override;

            void setTargetName(eString new_target);
            void setCategory(int32_t new_category);
    };


    ////////////////////////////////////////////////////////////////
    // eProxy TypeInfo
    // <kao2.00485610> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PROXY_ID = 0x13454032;

    extern TypeInfo E_PROXY_TYPEINFO;

}

#endif
