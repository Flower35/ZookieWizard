#ifndef H_KAO2AR_LIGHT
#define H_KAO2AR_LIGHT

#include <kao2engine/eNode.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eLight interface
    // <kao2.005D0D28> (vptr)
    ////////////////////////////////////////////////////////////////

    class eLight : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C-0x48]*/ float diffuse[4];
            /*[0x4C-0x58]*/ float ambient[4];
            /*[0x5C-0x68]*/ float specular[4];

        /*** Methods ***/

        public:

            eLight();
            ~eLight();

        private:

            void createFromOtherObject(const eLight &other);

        public:

            eLight(const eLight &other);
            eLight& operator = (const eLight &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            void writeStructureToTextFile(FileOperator &file, int32_t indentation, bool group_written) const override;

            /* << eNode >> */

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eLight >> */

            void getDiffuseColor(float* values) const;
            void getAmbientColor(float* values) const;
            void getSpecularColor(float* values) const;

            void setDiffuseColor(float* values);
            void setAmbientColor(float* values);
            void setSpecularColor(float* values);

            /*[[vptr]+0x74]*/ virtual void bindLight(int32_t light_id) const = 0;

        protected:

            /* << eLight >> */

            void useBasicLightParams(int32_t light_id) const;
    };


    ////////////////////////////////////////////////////////////////
    // eLight TypeInfo
    // <kao2.0047F0C0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_LIGHT_ID = 0x03454500;

    extern TypeInfo E_LIGHT_TYPEINFO;

}

#endif
