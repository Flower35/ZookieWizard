#ifndef H_KAO2AR_PARTICLEMANAGER
#define H_KAO2AR_PARTICLEMANAGER

#include <kao2engine/Gadget.h>

namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // eParticleManager interface
    ////////////////////////////////////////////////////////////////

    class eParticleManager : public Gadget
    {

        /*** Properties ***/

        protected:

            /*[0x10]*/
            /*[0x14]*/
            /*[0x18]*/
            /*[0x1C]*/
            /*[0x20]*/
            /*[0x24]*/
            /*[0x28]*/ int32_t maxNumParticles;
            /*[0x2C]*/ eString particleName;
            /*[0x30]*/
            /*[0x34]*/
            /*[0x35]*/ bool attachToSceneRoot;
            /*[0x38-0x40]*/ ePoint3 offset;
            /*[0x44]*/ float scale;


        /*** Methods ***/

        public:

            eParticleManager();
            ~eParticleManager();

            TypeInfo* getType() override;
    };


    ////////////////////////////////////////////////////////////////
    // eParticleManager TypeInfo
    // <kao2.004465A0> (registration)
    ////////////////////////////////////////////////////////////////

    static const int E_PARTICLEMANAGER_ID = 0x3B8B1F8C;

    extern TypeInfo E_PARTICLEMANAGER_TYPEINFO;

}

#endif
