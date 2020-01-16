#ifndef H_KAO2AR_TEXTURE
#define H_KAO2AR_TEXTURE

#include <kao2engine/eRefCounter.h>

namespace ZookieWizard
{
    class eTexTransform;
    class eBitmap;

    ////////////////////////////////////////////////////////////////
    // eTexture interface
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

            void serialize(Archive &ar) override;
            TypeInfo* getType() override;

            void writeNodeToXmlFile(ColladaExporter &exporter) override;

            GLuint getTextureName();
            eBitmap* getBitmap();
    };


    ////////////////////////////////////////////////////////////////
    // eTexture TypeInfo
    // <kao2.004735A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_TEXTURE_ID = 0x1002;

    extern TypeInfo E_TEXTURE_TYPEINFO;

}

#endif
