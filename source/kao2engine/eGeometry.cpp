#include <kao2engine/eGeometry.h>
#include <kao2ar/Archive.h>

#include <kao2engine/eMaterial.h>

#include <kao2engine/eALBox.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eGeometry interface
    // <kao2.0046F040> (overloaded constructor)
    // <kao2.0046EF90> (constructor)
    // <kao2.0046F160> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_GEOMETRY_TYPEINFO
    (
        E_GEOMETRY_ID,
        "eGeometry",
        &E_NODE_TYPEINFO,
        []() -> eObject*
        {
            return nullptr;
        }
    );

    TypeInfo* eGeometry::getType() const
    {
        return &E_GEOMETRY_TYPEINFO;
    }

    eGeometry::eGeometry(eString s, eNode* x)
    : eNode(s, x)
    {
        /*[0x3C]*/ material = nullptr;
        /*[0x40]*/ boxBoundMin.x = 1.0f;
        /*[0x4C]*/ boxBoundMax.x = 0;
    }

    eGeometry::eGeometry()
    : eNode()
    {
        /*[0x3C]*/ material = nullptr;
        /*[0x40]*/ boxBoundMin.x = 1.0f;
        /*[0x4C]*/ boxBoundMax.x = 0;
    }

    eGeometry::~eGeometry()
    {
        /*[0x3C]*/ material->decRef();
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: cloning the object
    ////////////////////////////////////////////////////////////////

    void eGeometry::createFromOtherObject(const eGeometry &other)
    {
        material = other.material;
        if (nullptr != material)
        {
            material->incRef();
        }

        boxBoundMin = other.boxBoundMin;
        boxBoundMax = other.boxBoundMax;
    }

    eGeometry::eGeometry(const eGeometry &other)
    : eNode(other)
    {
        createFromOtherObject(other);
    }

    eGeometry& eGeometry::operator = (const eGeometry &other)
    {
        if ((&other) != this)
        {
            eNode::operator = (other);

            /****************/

            material->decRef();

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eGeometry::cloneFromMe() const
    {
        return nullptr;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: serialization
    // <kao2.0046F1D0>
    ////////////////////////////////////////////////////////////////
    void eGeometry::serialize(Archive &ar)
    {
        int32_t a;

        eNode::serialize(ar);

        /* Material */
        ArFunctions::serialize_eRefCounter(ar, (eRefCounter**)&material, &E_MATERIAL_TYPEINFO);

        /* Bounding box */
        if (ar.getVersion() < 0x82)
        {
            a = 0x01;
            ar.readOrWrite(&a, 0x04);
            if (0x01 != a)
            {
                throw ErrorMessage
                (
                    "eGeometry::serialize():\n" \
                    "non-empty object is not supported!"
                );
            }
        }
        else
        {
            boxBoundMin.serialize(ar);
            boxBoundMax.serialize(ar);
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: create collision entry
    ////////////////////////////////////////////////////////////////
    bool eGeometry::createCollisionEntry()
    {
        eALBox* new_albox = nullptr;

        float boundaries[6] =
        {
            boxBoundMin.x, boxBoundMin.y, boxBoundMin.z,
            boxBoundMax.x, boxBoundMax.y, boxBoundMax.z
        };

        new_albox = new eALBox();
        new_albox->incRef();

        new_albox->createAxisListEntry(this, boundaries);

        new_albox->decRef();

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: (editor option) find object in 3D space
    ////////////////////////////////////////////////////////////////
    ePoint3 eGeometry::editingGetCenterPoint() const
    {
        return (boxBoundMax + boxBoundMin) * 0.5f;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: (editor option) rebuild collision
    ////////////////////////////////////////////////////////////////
    void eGeometry::editingRebuildCollision()
    {
        createCollisionEntry();
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: custom TXT parser methods
    ////////////////////////////////////////////////////////////////

    int32_t eGeometry::parsingSetProperty(char* result_msg, const TxtParsingNodeProp &property)
    {
        int32_t test[2];
        eString prop_name;
        eString dummy_name;

        if (1 != (test[0] = eNode::parsingSetProperty(result_msg, property)))
        {
            return test[0];
        }

        prop_name = property.getName();

        if (prop_name.compareExact("materialCollision", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorPropType(result_msg, "materialCollision", TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            property.getValue(&dummy_name);

            test[0] = (-1);

            for (test[1] = 0; ((-1) == test[0]) && (test[1] < KAO2_MATERIAL_TYPES_COUNT); test[1]++)
            {
                if (dummy_name.compareExact(theMaterialTypes[test[1]].name, true))
                {
                    test[0] = theMaterialTypes[test[1]].id;
                }
            }

            if ((-1) == test[0])
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Unknown collision type for \"materialCollision\" property!");
                return 2;
            }

            if (nullptr == material)
            {
                setMaterial(new eMaterial(nullptr));
            }

            material->setCollisionType(test[0]);

            return 0;
        }
        else if (prop_name.compareExact("materialSound", true))
        {
            if (!property.checkType(TXT_PARSING_NODE_PROPTYPE_STRING))
            {
                TxtParsingNode_ErrorPropType(result_msg, "materialSound", TXT_PARSING_NODE_PROPTYPE_STRING);
                return 2;
            }

            property.getValue(&dummy_name);

            test[0] = (-1);

            for (test[1] = 0; ((-1) == test[0]) && (test[1] < KAO2_MATERIAL_SOUNDS_COUNT); test[1]++)
            {
                if (dummy_name.compareExact(theMaterialSounds[test[1]].name, true))
                {
                    test[0] = theMaterialSounds[test[1]].id;
                }
            }

            if ((-1) == test[0])
            {
                sprintf_s(result_msg, LARGE_BUFFER_SIZE, "Unknown sound type for \"materialSound\" property!");
                return 2;
            }

            if (nullptr == material)
            {
                setMaterial(new eMaterial(nullptr));
            }

            material->setSoundType((uint16_t)test[0]);

            return 0;
        }

        return 1;
    }

    int32_t eGeometry::parsingCustomMessage(char* result_msg, const eString &message, int32_t params_count, const TxtParsingNodeProp* params)
    {
        int32_t test[1];

        if (1 != (test[0] = eNode::parsingCustomMessage(result_msg, message, params_count, params)))
        {
            return test[0];
        }

        if (message.compareExact("rebuildCollision", true))
        {
            if (0 != params_count)
            {
                TxtParsingNode_ErrorArgCount(result_msg, "rebuildCollision", 0);
                return 2;
            }

            /********************************/

            editingRebuildCollision();
            return 0;
        }

        return 1;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: optimize data by removing "eMaterial" duplicates
    ////////////////////////////////////////////////////////////////
    void eGeometry::optimizeGeometryByComparingMaterials(eGeometry &other)
    {
        if ((nullptr != material) && (nullptr != other.material))
        {
            if (material->checkSimilarityToAnotherMaterial(*(other.material)))
            {
                setMaterial(other.material);
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: old serialization
    // <kao2.0046F980>
    ////////////////////////////////////////////////////////////////
    void eGeometry::oldNodeSerialization(ePoint3* arg1)
    {
        boxBoundMin = arg1[0];
        boxBoundMax = arg1[1];

        /*[0x1C]*/ flags &= 0xFFFFFFEF;
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: get or set the Material
    ////////////////////////////////////////////////////////////////

    eMaterial* eGeometry::getMaterial() const
    {
        return material;
    }

    void eGeometry::setMaterial(eMaterial* new_material)
    {
        if (material != new_material)
        {
            material->decRef();

            material = new_material;

            if (nullptr != material)
            {
                material->incRef();
            }
        }
    }


    ////////////////////////////////////////////////////////////////
    // eGeometry: set boundary box
    ////////////////////////////////////////////////////////////////
    void eGeometry::setBoundaryBox(ePoint3 &new_min, ePoint3 &new_max)
    {
        boxBoundMin = new_min;
        boxBoundMax = new_max;
    }

}
