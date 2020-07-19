#ifndef H_ZOOKIEWIZARD_SPECIALMODELS
#define H_ZOOKIEWIZARD_SPECIALMODELS

namespace ZookieWizard
{
    namespace GUI
    {
        ////////////////////////////////////////////////////////////////
        // Special Models
        ////////////////////////////////////////////////////////////////

        #define ZOOKIEWIZARD_SPECIALMODEL_ARROW 0
        #define ZOOKIEWIZARD_SPECIALMODEL_KAO 1
        #define ZOOKIEWIZARD_SPECIALMODEL_CAMERA 2
        #define ZOOKIEWIZARD_SPECIALMODEL_LIGHT 3

        #define ZOOKIEWIZARD_SPECIALMODEL_COUNT 4

        bool prepareSpecialModels();
        void renderSpecialModel(bool use_texture, int32_t id);
        void clearSpecialModels();
    }
}

#endif
