#ifndef H_KAO2AR_GEOMETRY
#define H_KAO2AR_GEOMETRY

#include <kao2engine/eNode.h>

namespace ZookieWizard
{
    class eMaterial;

    ////////////////////////////////////////////////////////////////
    // eGeometry interface
    // <kao2.005D0678> (vptr)
    ////////////////////////////////////////////////////////////////

    class eGeometry : public eNode
    {
        /*** Properties ***/

        protected:

            /*[0x3C]*/ eMaterial* material;
            /*[0x40-0x48]*/ ePoint3 boxBoundMin;
            /*[0x4C-0x54]*/ ePoint3 boxBoundMax;

        /*** Methods ***/

        public:

            eGeometry(eString s, eNode* x);
            eGeometry();
            ~eGeometry();

        private:

            void createFromOtherObject(const eGeometry &other);

        public:

            eGeometry(const eGeometry &other);
            eGeometry& operator = (const eGeometry &other);
            eObject* cloneFromMe() const override;

            /* << eObject >> */

            TypeInfo* getType() const override;
            void serialize(Archive &ar) override;

            /* << eNode >> */

            bool createCollisionEntry() override;

            ePoint3 editingGetCenterPoint() const override;
            void editingRebuildCollision() override;

            int32_t parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property) override;
            int32_t parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params) override;

            /* << eGeometry >> */

            void optimizeGeometryByComparingMaterials(eGeometry &other);

            void oldNodeSerialization(ePoint3* arg1);

            eMaterial* getMaterial() const;
            void setMaterial(eMaterial* new_material);

            void setBoundaryBox(ePoint3 &new_min, ePoint3 &new_max);
    };


    ////////////////////////////////////////////////////////////////
    // eGeometry TypeInfo
    // <kao2.0046FA20> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_GEOMETRY_ID = 0x034567FD;

    extern TypeInfo E_GEOMETRY_TYPEINFO;

}

#endif
