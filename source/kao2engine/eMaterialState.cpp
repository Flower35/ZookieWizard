#include <kao2engine/eMaterialState.h>
#include <kao2ar/Archive.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eMaterialState interface
    // <kao2.00482430> (constructor)
    // <kao2.004824E0> (destructor)
    ////////////////////////////////////////////////////////////////

    TypeInfo E_MATERIALSTATE_TYPEINFO
    (
        E_MATERIALSTATE_ID,
        "eMaterialState",
        &E_REFCOUNTER_TYPEINFO,
        []() -> eObject*
        {
            return new eMaterialState;
        }
    );

    TypeInfo* eMaterialState::getType() const
    {
        return &E_MATERIALSTATE_TYPEINFO;
    }

    eMaterialState::eMaterialState()
    : eRefCounter()
    {
        theMaterialStatesCounter++;

        GUI::materialsManager_UpdateStatistics();

        /****************/

        /*[0x28-0x34]*/
        emissive[0] = 0;
        emissive[1] = 0;
        emissive[2] = 0;
        emissive[3] = 1.0f;

        /*[0x08-0x14]*/
        ambient[0] = 0.5f;
        ambient[1] = 0.5f;
        ambient[2] = 0.5f;
        ambient[3] = 1.0f;

        /*[0x18-0x24]*/
        diffuse[0] = 0.5f;
        diffuse[1] = 0.5f;
        diffuse[2] = 0.5f;
        diffuse[3] = 1.0f;

        /*[0x38-0x44]*/
        specular[0] = 0.5f;
        specular[1] = 0.5f;
        specular[2] = 0.5f;
        specular[3] = 1.0f;

        /*[0x48]*/ shininess = 0;
        /*[0x4C]*/ useGlobalAmbientLight = true;

    }

    eMaterialState::~eMaterialState()
    {
        theMaterialStatesCounter--;

        GUI::materialsManager_UpdateStatistics();
    }


    ////////////////////////////////////////////////////////////////
    // eMaterialState: cloning the object
    ////////////////////////////////////////////////////////////////

    void eMaterialState::createFromOtherObject(const eMaterialState &other)
    {
        ambient[0] = other.ambient[0];
        ambient[1] = other.ambient[1];
        ambient[2] = other.ambient[2];
        ambient[3] = other.ambient[3];

        diffuse[0] = other.diffuse[0];
        diffuse[1] = other.diffuse[1];
        diffuse[2] = other.diffuse[2];
        diffuse[3] = other.diffuse[3];

        emissive[0] = other.emissive[0];
        emissive[1] = other.emissive[1];
        emissive[2] = other.emissive[2];
        emissive[3] = other.emissive[3];

        specular[0] = other.specular[0];
        specular[1] = other.specular[1];
        specular[2] = other.specular[2];
        specular[3] = other.specular[3];

        shininess = other.shininess;
        useGlobalAmbientLight = other.useGlobalAmbientLight;
    }

    eMaterialState::eMaterialState(const eMaterialState &other)
    : eRefCounter(other)
    {
        theMaterialStatesCounter++;

        /****************/

        createFromOtherObject(other);
    }

    eMaterialState& eMaterialState::operator = (const eMaterialState &other)
    {
        if ((&other) != this)
        {
            eRefCounter::operator = (other);

            /****************/

            createFromOtherObject(other);
        }

        return (*this);
    }

    eObject* eMaterialState::cloneFromMe() const
    {
        return new eMaterialState(*this);
    }


    ////////////////////////////////////////////////////////////////
    // eMaterialState: serialization
    // <kao2.00482500>
    ////////////////////////////////////////////////////////////////
    void eMaterialState::serialize(Archive &ar)
    {
        /* [0x18] material diffuse */
        ar.readOrWrite(&(diffuse[0]), 0x04);
        ar.readOrWrite(&(diffuse[1]), 0x04);
        ar.readOrWrite(&(diffuse[2]), 0x04);
        ar.readOrWrite(&(diffuse[3]), 0x04);

        /* [0x08] material ambient */
        ar.readOrWrite(&(ambient[0]), 0x04);
        ar.readOrWrite(&(ambient[1]), 0x04);
        ar.readOrWrite(&(ambient[2]), 0x04);
        ar.readOrWrite(&(ambient[3]), 0x04);

        if (ar.isInReadMode())
        {
            if (ar.getVersion() < 0x74)
            {
                ambient[0] = 0.5f;
                ambient[1] = 0.5f;
                ambient[2] = 0.5f;
                ambient[3] = 1.0f;

                diffuse[0] = 0.5f;
                diffuse[1] = 0.5f;
                diffuse[2] = 0.5f;
                diffuse[3] = 1.0f;
            }
        }

        if (ar.getVersion() >= 0x71)
        {
            /* [0x28] material emissive */
            ar.readOrWrite(&(emissive[0]), 0x04);
            ar.readOrWrite(&(emissive[1]), 0x04);
            ar.readOrWrite(&(emissive[2]), 0x04);
            ar.readOrWrite(&(emissive[3]), 0x04);

            /* [0x38] material specular */
            ar.readOrWrite(&(specular[0]), 0x04);
            ar.readOrWrite(&(specular[1]), 0x04);
            ar.readOrWrite(&(specular[2]), 0x04);
            ar.readOrWrite(&(specular[3]), 0x04);
        }
        else
        {
            emissive[0] = 0;
            emissive[1] = 0;
            emissive[2] = 0;
            emissive[3] = 0;

            specular[0] = 0;
            specular[1] = 0;
            specular[2] = 0;
            specular[3] = 0;
        }

        /* [0x48] material shininess */
        if (ar.getVersion() >= 0x72)
        {
            ar.readOrWrite(&shininess, 0x04);
        }
        else
        {
            shininess = 0;
        }

        /* [0x4C] should global ambient lights be used with this material? */
        if (ar.getVersion() >= 0x76)
        {
            ar.readOrWrite(&useGlobalAmbientLight, 0x01);
        }
        else
        {
            useGlobalAmbientLight = true;
        }
    }


    ////////////////////////////////////////////////////////////////
    // eMaterialState: compare with other material state
    ////////////////////////////////////////////////////////////////
    bool eMaterialState::checkSimilarityToAnotherState(const eMaterialState &other) const
    {
        if ((&other) != this)
        {
            if ((ambient[0] != other.ambient[0]) || (ambient[1] != other.ambient[1]) || (ambient[2] != other.ambient[2]) || (ambient[3] != other.ambient[3]))
            {
                return false;
            }

            if ((diffuse[0] != other.diffuse[0]) || (diffuse[1] != other.diffuse[1]) || (diffuse[2] != other.diffuse[2]) || (diffuse[3] != other.diffuse[3]))
            {
                return false;
            }

            if ((emissive[0] != other.emissive[0]) || (emissive[1] != other.emissive[1]) || (emissive[2] != other.emissive[2]) || (emissive[3] != other.emissive[3]))
            {
                return false;
            }

            if ((specular[0] != other.specular[0]) || (specular[1] != other.specular[1]) || (specular[2] != other.specular[2]) || (specular[3] != other.specular[3]))
            {
                return false;
            }

            if (shininess != other.shininess)
            {
                return false;
            }

            if (useGlobalAmbientLight != other.useGlobalAmbientLight)
            {
                return false;
            }
        }

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // eMaterialState: color getters and setters
    ////////////////////////////////////////////////////////////////

    void eMaterialState::getAmbientColor(float* values) const
    {
        values[0] = ambient[0];
        values[1] = ambient[1];
        values[2] = ambient[2];
    }

    void eMaterialState::getDiffuseColor(float* values) const
    {
        values[0] = diffuse[0];
        values[1] = diffuse[1];
        values[2] = diffuse[2];
    }

    void eMaterialState::getEmissiveColor(float* values) const
    {
        values[0] = emissive[0];
        values[1] = emissive[1];
        values[2] = emissive[2];
    }

    void eMaterialState::getSpecularColor(float* values) const
    {
        values[0] = specular[0];
        values[1] = specular[1];
        values[2] = specular[2];
    }

    float eMaterialState::getShininess() const
    {
        return shininess;
    }

    bool eMaterialState::getGlobalAmbientLightState() const
    {
        return useGlobalAmbientLight;
    }

    void eMaterialState::setAmbientColor(float* values)
    {
        ambient[0] = values[0];
        ambient[1] = values[1];
        ambient[2] = values[2];
        ambient[3] = 1.0f;
    }

    void eMaterialState::setDiffuseColor(float* values)
    {
        diffuse[0] = values[0];
        diffuse[1] = values[1];
        diffuse[2] = values[2];
        diffuse[3] = 1.0f;
    }

    void eMaterialState::setEmissiveColor(float* values)
    {
        emissive[0] = values[0];
        emissive[1] = values[1];
        emissive[2] = values[2];
        emissive[3] = 1.0f;
    }

    void eMaterialState::setSpecularColor(float* values)
    {
        specular[0] = values[0];
        specular[1] = values[1];
        specular[2] = values[2];
        specular[3] = 1.0f;
    }

    void eMaterialState::setShininess(float value)
    {
        shininess = value;
    }

    void eMaterialState::setGlobalAmbientLightState(bool value)
    {
        useGlobalAmbientLight = value;
    }

    ////////////////////////////////////////////////////////////////
    // Global MaterialStates counter
    ////////////////////////////////////////////////////////////////

    int32_t theMaterialStatesCounter = 0;

}
