#ifndef H_KAO2AR_TEXTURE
#define H_KAO2AR_TEXTURE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class eTexTransform;
    class eBitmap;
    struct eAnimate;

    ////////////////////////////////////////////////////////////////
    // eTexture interface
    // <kao2.005D0760> (vptr)
    ////////////////////////////////////////////////////////////////

    class eTexture : public eRefCounter
    {
        /*** Properties ***/

        protected:

            /*[0x08]*/ uint32_t params;
            /*[0x0C]*/ eTexTransform* form;
            /*[0x10]*/ eBitmap* bmp;
            /*[0x14]*/ int32_t unknown_14;

        /*** Methods ***/

        public:

            eTexture(eBitmap* x);
            ~eTexture();

        private:

            void createFromOtherObject(const eTexture &other);

        public:

            eTexture(const eTexture &other);
            eTexture& operator = (const eTexture &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeNodeToXmlFile(ColladaExporter &exporter) const override;

            /* << eTexture >> */

            bool matchesPath(eString &searched_path) const;

            GLuint getTextureId() const;
            eBitmap* getBitmap() const;

            void setTextureTransform(eTexTransform* new_form);
            void updateTextureMatrix(eAnimate* anim) const;
    };


    ////////////////////////////////////////////////////////////////
    // eTexture TypeInfo
    // <kao2.00473570> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTURE_ID = 0x1002;

    extern TypeInfo E_TEXTURE_TYPEINFO;

}

#endif
