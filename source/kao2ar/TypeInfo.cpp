#include <kao2ar/TypeInfo.h>

namespace ZookieWizard
{
    Kao2Interfaces InterfaceManager;
}


////////////////////////////////////////////////////////////////
// KAO2 INTERFACES: definitions
////////////////////////////////////////////////////////////////

#include <kao2ar/eObject.h>

#include <kao2engine/eMusicManager.h>
#include <kao2engine/eTextWriter.h>
#include <kao2engine/eNPCMap.h>
#include <kao2engine/eWalk.h>
#include <kao2engine/eWalkWPF.h>
#include <kao2engine/ePathFinder.h>
#include <kao2engine/eEmptyCtrl.h>
#include <kao2engine/eKasztanCtrl.h>
#include <kao2engine/eNaviPoint.h>
#include <kao2engine/eRndNavi.h>
#include <kao2engine/eEnumNavi.h>
#include <kao2engine/eNearestNavi.h>
#include <kao2engine/eGroupCtrl.h>
#include <kao2engine/eFlock.h>
#include <kao2engine/eTargeting.h>
#include <kao2engine/eBeeAttack.h>
#include <kao2engine/eDirectionCtrl.h>
#include <kao2engine/eFollowWPF.h>
#include <kao2engine/eVisibilityCtrl.h>
#include <kao2engine/eParticleCtrl.h>
#include <kao2engine/eTeleportCtrl.h>
#include <kao2engine/eFlockAway.h>
#include <kao2engine/eFloatObject.h>
#include <kao2engine/eCollisionCtrl.h>
#include <kao2engine/eDisableGeo.h>
#include <kao2engine/eBoids.h>
#include <kao2engine/eButterfly.h>
#include <kao2engine/eNeckCtrl.h>
#include <kao2engine/eSnd.h>
#include <kao2engine/eStaticSnd.h>
#include <kao2engine/eSpider.h>
#include <kao2engine/eCinemaMode.h>
#include <kao2engine/eFloatCtrlObject.h>
#include <kao2engine/eSplineWalk.h>
#include <kao2engine/eGravitation.h>
#include <kao2engine/eFootPrints.h>
#include <kao2engine/eAnimNotyfier.h>
#include <kao2engine/eRealTimeClock.h>
#include <kao2engine/eParticleManager.h>
#include <kao2engine/eWaterCircles.h>
#include <kao2engine/eFlockEx.h>
#include <kao2engine/eLinkToObject.h>
#include <kao2engine/eRollCtrl.h>
#include <kao2engine/eSplineSwim.h>
#include <kao2engine/eStrafeCtrl.h>
#include <kao2engine/ePlaszczka.h>
#include <kao2engine/eDzwig.h>
#include <kao2engine/eHitForceCtrl.h>
#include <kao2engine/eSwitelikKao.h>
#include <kao2engine/eKolec.h>
#include <kao2engine/eBombaExplodujaca.h>
#include <kao2engine/ePowerBar.h>
#include <kao2engine/eLevelChanger.h>
#include <kao2engine/eSpeaking.h>
#include <kao2engine/eDemoPlayer.h>
#include <kao2engine/eBonusBieg.h>
#include <kao2engine/eBaseballBieg.h>
#include <kao2engine/eTextWriterEx.h>
#include <kao2engine/eReadySteadyGo.h>
#include <kao2engine/eEnemyMapUpgrader.h>
#include <kao2engine/eMotorowki.h>
#include <kao2engine/eAskYesNo.h>
#include <kao2engine/eCredits.h>
#include <kao2engine/eDirectionCtrlEx.h>
#include <kao2engine/eFloat.h>
#include <kao2engine/eTriMesh.h>
#include <kao2engine/eGeoSet.h>
#include <kao2engine/eGeoArray.h>
#include <kao2engine/eBitmap.h>
#include <kao2engine/eTexTransform.h>
#include <kao2engine/eTexture.h>
#include <kao2engine/eNode.h>
#include <kao2engine/eTransform.h>
#include <kao2engine/eMaterial.h>
#include <kao2engine/eEnvironment.h>
#include <kao2engine/eFogEnv.h>
#include <kao2engine/eOmniLight.h>
#include <kao2engine/eDirectionalLight.h>
#include <kao2engine/eMaterialState.h>
#include <kao2engine/eGroup.h>
#include <kao2engine/eProxy.h>
#include <kao2engine/eAnimBillboardTarget.h>
#include <kao2engine/eAnimBillboardProxy.h>
#include <kao2engine/ePivot.h>
#include <kao2engine/eScene.h>
#include <kao2engine/eALZoneSensor.h>
#include <kao2engine/eZone.h>
#include <kao2engine/eBoxZone.h>
#include <kao2engine/eMorpherTarget.h>
#include <kao2engine/eMorpherMod.h>
#include <kao2engine/eMultiCtrl.h>
#include <kao2engine/eXYZPoint3Ctrl.h>
#include <kao2engine/eXYZEulerRotation.h>
#include <kao2engine/eSRPCombineCtrl.h>
#include <kao2engine/eLeafCtrl.h>
#include <kao2engine/eSpline3D.h>
#include <kao2engine/ePathConstrainCtrl.h>
#include <kao2engine/eBezierSplineNode.h>
#include <kao2engine/eALBox.h>
#include <kao2engine/eCylNode.h>
#include <kao2engine/eSphNode.h>
#include <kao2engine/eBillboard.h>
#include <kao2engine/eXRefTarget.h>
#include <kao2engine/eXRefProxy.h>
#include <kao2engine/eXRefManager.h>
#include <kao2engine/eMultiTransform.h>
#include <kao2engine/ePhyTriMesh.h>
#include <kao2engine/eTrack.h>
#include <kao2engine/eAnimState.h>
#include <kao2engine/eTouchSensor.h>
#include <kao2engine/eBlockIndexCtrl.h>
#include <kao2engine/eGlobalLightCtrl.h>
#include <kao2engine/ePadGadget.h>
#include <kao2engine/eTorpedoMode.h>
#include <kao2engine/eVibrate.h>
#include <kao2engine/eHistory.h>
#include <kao2engine/eCameraShaker.h>
#include <kao2engine/eCameraFOVCtrl.h>
#include <kao2engine/eMotorboatCameraCtrl.h>
#include <kao2engine/eMotorboatCameraCtrl4.h>
#include <kao2engine/eSplineHintFollowCameraCtrl.h>
#include <kao2engine/eGameCamera.h>
#include <kao2engine/eLookAtMeKao.h>
#include <kao2engine/ePadRot.h>
#include <kao2engine/eIcePhysics.h>
#include <kao2engine/eSnowboardOrientation.h>
#include <kao2engine/eSnowboardPhysics.h>
#include <kao2engine/eSnowboardJumpPhysics.h>
#include <kao2engine/eSnowboardRampPhysics.h>
#include <kao2engine/eStrafeTarget.h>
#include <kao2engine/eWalkingPhysics.h>
#include <kao2engine/ePushableObject.h>
#include <kao2engine/eExtraAlbox.h>
#include <kao2engine/eJumpPhysics.h>
#include <kao2engine/eSpringTrunk2.h>
#include <kao2engine/eWaterPhysics.h>
#include <kao2engine/eWhaleManager.h>
#include <kao2engine/eWhalePhysics.h>
#include <kao2engine/eFlyingObjectCtrl.h>
#include <kao2engine/eFlyingTarget.h>
#include <kao2engine/eEggTarget.h>
#include <kao2engine/eGloveTarget.h>
#include <kao2engine/eMultiTargetThrower.h>
#include <kao2engine/eEggsFactory.h>
#include <kao2engine/eEggsNotStatic.h>
#include <kao2engine/eWaterTarget.h>
#include <kao2engine/ePowerUp.h>
#include <kao2engine/eEnergy.h>
#include <kao2engine/eKaoKiller.h>
#include <kao2engine/eTraceGadget.h>
#include <kao2engine/eCamera.h>
#include <kao2engine/eFollowCameraCtrl.h>
#include <kao2engine/eCameraZonePacket.h>
#include <kao2engine/eSnowCameraCtrl.h>
#include <kao2engine/eDoubleCameraTarget.h>
#include <kao2engine/eSecondCameraTarget.h>
#include <kao2engine/eOctopussy2ndTarget.h>
#include <kao2engine/eParentListener.h>
#include <kao2engine/eHeroParent.h>
#include <kao2engine/eAddNode.h>
#include <kao2engine/eObjectLinker.h>
#include <kao2engine/eSimpleCR.h>
#include <kao2engine/eTimerGadget.h>
#include <kao2engine/eScreenCounter.h>
#include <kao2engine/eMoveTo.h>
#include <kao2engine/eGoUpAndDown.h>
#include <kao2engine/eCylinderIsectGadget.h>
#include <kao2engine/eFocMill471Deflector.h>
#include <kao2engine/eSetRotation.h>
#include <kao2engine/ePadSeqeunce.h>
#include <kao2engine/eObjectChain.h>
#include <kao2engine/eKalmar.h>
#include <kao2engine/eFreeRotate.h>
#include <kao2engine/eGroupMsgForward.h>
#include <kao2engine/ePersistentFloatRef.h>
#include <kao2engine/eLightBlinker.h>
#include <kao2engine/eCameraDeflector.h>
#include <kao2engine/ePathCamCtrl.h>
#include <kao2engine/eGravity.h>
#include <kao2engine/eOrtho2D.h>
#include <kao2engine/eParticleEmiter.h>
#include <kao2engine/ePointEmiter.h>
#include <kao2engine/eLineEmiter.h>
#include <kao2engine/ePlaneEmiter.h>
#include <kao2engine/eSphereEmiter.h>
#include <kao2engine/eFSSprite.h>
#include <kao2engine/eShadowCaster.h>
#include <kao2engine/eParticleSet.h>
#include <kao2engine/eMarks.h>
#include <kao2engine/eIceCubeMarks.h>
#include <kao2engine/ePosCtrl.h>
#include <kao2engine/eRotCtrl.h>
#include <kao2engine/eColorCtrl.h>
#include <kao2engine/eOscilationCtrl.h>
#include <kao2engine/eFSMB.h>
#include <kao2engine/eSnow.h>
#include <kao2engine/eForrestFlakes.h>
#include <kao2engine/eLavaFlakes.h>
#include <kao2engine/eRain.h>
#include <kao2engine/eLisajoux.h>
#include <kao2engine/eSkyManager.h>
#include <kao2engine/ePlanktonFlakes.h>
#include <kao2engine/eBubbleFlakes.h>
#include <kao2engine/eElectricity.h>
#include <kao2engine/eOMB.h>
#include <kao2engine/eSndEmiterAmb.h>
#include <kao2engine/eSndEmiterOmni.h>
#include <kao2engine/eSoundCtrl.h>
#include <kao2engine/Actor.h>
#include <kao2engine/eString2.h>
#include <kao2engine/eFloatPair.h>
#include <kao2engine/eFloatTriple.h>
#include <kao2engine/IfInstruction.h>
#include <kao2engine/AndInstruction.h>
#include <kao2engine/NotInstruction.h>
#include <kao2engine/IfElseInstruction.h>
#include <kao2engine/StatusInstruction.h>
#include <kao2engine/StaticStatusInstruction.h>
#include <kao2engine/MsgInstruction.h>
#include <kao2engine/StaticMsgInstruction.h>
#include <kao2engine/BlockInstruction.h>
#include <kao2engine/ShiftInstruction.h>
#include <kao2engine/SuperInstruction.h>
#include <kao2engine/OwnerUpdateInstruction.h>
#include <kao2engine/McastInstanceInstruction.h>
#include <kao2engine/McastClassInstruction.h>
#include <kao2engine/NodeRefSendInstruction.h>
#include <kao2engine/EmptyVoidInstruction.h>
#include <kao2engine/AfterInstruction.h>
#include <kao2engine/State.h>
#include <kao2engine/eCollisionSphere.h>
#include <kao2engine/eCollisionCylinder.h>
#include <kao2engine/eCollisionMesh.h>
#include <kao2engine/eActorCollision.h>
#include <kao2engine/eTurnCollisionOff.h>
#include <kao2engine/eSetCollisionFlags.h>
#include <kao2engine/Float.h>
#include <kao2engine/Key.h>
#include <kao2engine/Rnd.h>
#include <kao2engine/Log.h>
#include <kao2engine/Anim.h>
#include <kao2engine/Timer.h>
#include <kao2engine/SessionFloat.h>
#include <kao2engine/Namespace.h>
#include <kao2engine/GadgetRef.h>
#include <kao2engine/When.h>
#include <kao2engine/GadgetClassWhen.h>
#include <kao2engine/WorldWhen.h>
#include <kao2engine/GadgetInstanceWhen.h>
#include <kao2engine/MeWhen.h>
#include <kao2engine/ActorClassWhen.h>
#include <kao2engine/ActorInstanceWhen.h>
#include <kao2engine/NodeRef.h>
#include <kao2engine/eActivate.h>
#include <kao2engine/eAddPowerUp.h>
#include <kao2engine/eTargetGenerator.h>
#include <kao2engine/eCloneChild.h>
#include <kao2engine/eBonusShooting.h>
#include <kao2engine/eGeoEdge.h>
#include <kao2engine/eAmbientLight.h>
#include <kao2engine/eSndEmiterBox.h>
#include <kao2engine/AnimDumper.h>
#include <kao2engine/StateDumper.h>
#include <kao2engine/MsgDumper.h>


namespace ZookieWizard
{

    ////////////////////////////////////////////////////////////////
    // TYPE INFO: constructor
    ////////////////////////////////////////////////////////////////

    TypeInfo::TypeInfo(int _id, const char* _name, TypeInfo* _parent, eObject* (*_create)())
    {
        id = _id;
        name = _name;
        parent = _parent;
        create = _create;
    }


    ////////////////////////////////////////////////////////////////
    // TYPE INFO: test hierachy
    // <kao2.00462CB0>
    ////////////////////////////////////////////////////////////////

    bool TypeInfo::checkHierarchy(const TypeInfo* assumed_type) const
    {
        const TypeInfo* test = this;

        if (nullptr != assumed_type)
        {
            while (nullptr != test)
            {
                if (test == assumed_type)
                {
                    return true;
                }
                else
                {
                    test = test->parent;
                }
            }
        }

        return false;
    }


    ////////////////////////////////////////////////////////////////
    // KAO2 INTERFACES: register all known types
    ////////////////////////////////////////////////////////////////

    bool Kao2Interfaces::registerInterfaces()
    {
        interfacesCount = 0;

        registerTypeInfo(&E_MUSICMANAGER_TYPEINFO);
        registerTypeInfo(&E_TEXTWRITER_TYPEINFO);
        registerTypeInfo(&E_NPCMAP_TYPEINFO);
        registerTypeInfo(&E_WALK_TYPEINFO);
        registerTypeInfo(&E_WALKWPF_TYPEINFO);
        registerTypeInfo(&E_PATHFINDER_TYPEINFO);
        registerTypeInfo(&E_EMPTYCTRL_TYPEINFO);
        registerTypeInfo(&E_KASZTANCTRL_TYPEINFO);
        registerTypeInfo(&E_NAVIPOINT_TYPEINFO);
        registerTypeInfo(&E_RNDNAVI_TYPEINFO);
        registerTypeInfo(&E_ENUMNAVI_TYPEINFO);
        registerTypeInfo(&E_NEARESTNAVI_TYPEINFO);
        registerTypeInfo(&E_GROUPCTRL_TYPEINFO);
        registerTypeInfo(&E_FLOCK_TYPEINFO);
        registerTypeInfo(&E_TARGETING_TYPEINFO);
        registerTypeInfo(&E_BEEATTACK_TYPEINFO);
        registerTypeInfo(&E_DIRECTIONCTRL_TYPEINFO);
        registerTypeInfo(&E_FOLLOWWPF_TYPEINFO);
        registerTypeInfo(&E_VISIBILITYCTRL_TYPEINFO);
        registerTypeInfo(&E_PARTICLECTRL_TYPEINFO);
        registerTypeInfo(&E_TELEPORTCTRL_TYPEINFO);
        registerTypeInfo(&E_FLOCKAWAY_TYPEINFO);
        registerTypeInfo(&E_FLOATOBJECT_TYPEINFO);
        registerTypeInfo(&E_COLLISIONCTRL_TYPEINFO);
        registerTypeInfo(&E_DISABLEGEO_TYPEINFO);
        registerTypeInfo(&E_BOIDS_TYPEINFO);
        registerTypeInfo(&E_BUTTERFLY_TYPEINFO);
        registerTypeInfo(&E_NECKCTRL_TYPEINFO);
        registerTypeInfo(&E_SND_TYPEINFO);
        registerTypeInfo(&E_STATICSND_TYPEINFO);
        registerTypeInfo(&E_SPIDER_TYPEINFO);
        registerTypeInfo(&E_CINEMAMODE_TYPEINFO);
        registerTypeInfo(&E_FLOATCTRLOBJECT_TYPEINFO);
        registerTypeInfo(&E_SPLINEWALK_TYPEINFO);
        registerTypeInfo(&E_GRAVITATION_TYPEINFO);
        registerTypeInfo(&E_FOOTPRINTS_TYPEINFO);
        registerTypeInfo(&E_ANIMNOTYFIER_TYPEINFO);
        registerTypeInfo(&E_REALTIMECLOCK_TYPEINFO);
        registerTypeInfo(&E_PARTICLEMANAGER_TYPEINFO);
        registerTypeInfo(&E_WATERCIRCLES_TYPEINFO);
        registerTypeInfo(&E_FLOCKEX_TYPEINFO);
        registerTypeInfo(&E_LINKTOOBJECT_TYPEINFO);
        registerTypeInfo(&E_ROLLCTRL_TYPEINFO);
        registerTypeInfo(&E_SPLINESWIM_TYPEINFO);
        registerTypeInfo(&E_STRAFECTRL_TYPEINFO);
        registerTypeInfo(&E_PLASZCZKA_TYPEINFO);
        registerTypeInfo(&E_DZWIG_TYPEINFO);
        registerTypeInfo(&E_HITFORCECTRL_TYPEINFO);
        registerTypeInfo(&E_SWITELIKKAO_TYPEINFO);
        registerTypeInfo(&E_KOLEC_TYPEINFO);
        registerTypeInfo(&E_BOMBAEXPLODUJACA_TYPEINFO);
        registerTypeInfo(&E_POWERBAR_TYPEINFO);
        registerTypeInfo(&E_LEVELCHANGER_TYPEINFO);
        registerTypeInfo(&E_SPEAKING_TYPEINFO);
        registerTypeInfo(&E_DEMOPLAYER_TYPEINFO);
        registerTypeInfo(&E_BONUSBIEG_TYPEINFO);
        registerTypeInfo(&E_BASEBALLBIEG_TYPEINFO);
        registerTypeInfo(&E_TEXTWRITEREX_TYPEINFO);
        registerTypeInfo(&E_READYSTEADYGO_TYPEINFO);
        registerTypeInfo(&E_ENEMYMAPUPGRADER_TYPEINFO);
        registerTypeInfo(&E_MOTOROWKI_TYPEINFO);
        registerTypeInfo(&E_ASKYESNO_TYPEINFO);
        registerTypeInfo(&E_CREDITS_TYPEINFO);
        registerTypeInfo(&E_DIRECTIONCTRLEX_TYPEINFO);
        registerTypeInfo(&E_FLOAT_TYPEINFO);
        registerTypeInfo(&E_TRIMESH_TYPEINFO);
        registerTypeInfo(&E_GEOSET_TYPEINFO);
        registerTypeInfo(&E_GEOARRAY_USHORT_TYPEINFO);
        registerTypeInfo(&E_GEOARRAY_EPOINT2_TYPEINFO);
        registerTypeInfo(&E_GEOARRAY_EPOINT4_TYPEINFO);
        registerTypeInfo(&E_BITMAP_TYPEINFO);
        registerTypeInfo(&E_TEXTRANSFORM_TYPEINFO);
        registerTypeInfo(&E_TEXTURE_TYPEINFO);
        registerTypeInfo(&E_NODE_TYPEINFO);
        registerTypeInfo(&E_TRANSFORM_TYPEINFO);
        registerTypeInfo(&E_MATERIAL_TYPEINFO);
        registerTypeInfo(&E_ENVIRONMENT_TYPEINFO);
        registerTypeInfo(&E_FOGENV_TYPEINFO);
        registerTypeInfo(&E_OMNILIGHT_TYPEINFO);
        registerTypeInfo(&E_DIRECTIONALLIGHT_TYPEINFO);
        registerTypeInfo(&E_MATERIALSTATE_TYPEINFO);
        registerTypeInfo(&E_GROUP_TYPEINFO);
        registerTypeInfo(&E_PROXY_TYPEINFO);
        registerTypeInfo(&E_ANIMBILLBOARDTARGET_TYPEINFO);
        registerTypeInfo(&E_ANIMBILLBOARDPROXY_TYPEINFO);
        registerTypeInfo(&E_PIVOT_TYPEINFO);
        registerTypeInfo(&E_SCENE_TYPEINFO);
        registerTypeInfo(&E_ALZONESENSOR_TYPEINFO);
        registerTypeInfo(&E_ZONE_TYPEINFO);
        registerTypeInfo(&E_BOXZONE_TYPEINFO);
        registerTypeInfo(&E_MORPHERTARGET_TYPEINFO);
        registerTypeInfo(&E_MORPHERMOD_TYPEINFO);
        registerTypeInfo(&E_MULTICTRL_ESRP_TYPEINFO);
        registerTypeInfo(&E_MULTICTRL_FLOAT_TYPEINFO);
        registerTypeInfo(&E_XYZPOINT3CTRL_TYPEINFO);
        registerTypeInfo(&E_XYZEULERROTATION_TYPEINFO);
        registerTypeInfo(&E_SRPCOMBINECTRL_TYPEINFO);
        registerTypeInfo(&E_LEAFCTRL_FLOAT_TYPEINFO);
        registerTypeInfo(&E_LEAFCTRL_EPOINT3_TYPEINFO);
        registerTypeInfo(&E_LEAFCTRL_EQUAT_TYPEINFO);
        registerTypeInfo(&E_SPLINE3D_TYPEINFO);
        registerTypeInfo(&E_PATHCONSTRAINCTRL_TYPEINFO);
        registerTypeInfo(&E_BEZIERSPLINENODE_TYPEINFO);
        registerTypeInfo(&E_ALBOX_TYPEINFO);
        registerTypeInfo(&E_CYLNODE_TYPEINFO);
        registerTypeInfo(&E_SPHNODE_TYPEINFO);
        registerTypeInfo(&E_BILLBOARD_TYPEINFO);
        registerTypeInfo(&E_XREFTARGET_TYPEINFO);
        registerTypeInfo(&E_XREFPROXY_TYPEINFO);
        registerTypeInfo(&E_XREFMANAGER_TYPEINFO);
        registerTypeInfo(&E_MULTITRANSFORM_TYPEINFO);
        registerTypeInfo(&E_PHYTRIMESH_TYPEINFO);
        registerTypeInfo(&E_GEOARRAY_EPHYVERTEX_TYPEINFO);
        registerTypeInfo(&E_TRACK_TYPEINFO);
        registerTypeInfo(&E_ANIMSTATE_TYPEINFO);
        registerTypeInfo(&E_GEOARRAY_EABB_TYPEINFO);
        registerTypeInfo(&E_TOUCHSENSOR_TYPEINFO);
        registerTypeInfo(&E_BLOCKINDEXCTRL_TYPEINFO);
        registerTypeInfo(&E_GLOBALLIGHTCTRL_TYPEINFO);
        registerTypeInfo(&E_PADGADGET_TYPEINFO);
        registerTypeInfo(&E_TORPEDOMODE_TYPEINFO);
        registerTypeInfo(&E_VIBRATE_TYPEINFO);
        registerTypeInfo(&E_HISTORY_TYPEINFO);
        registerTypeInfo(&E_CAMERASHAKER_TYPEINFO);
        registerTypeInfo(&E_CAMERAFOVCTRL_TYPEINFO);
        registerTypeInfo(&E_MOTORBOATCAMERACTRL_TYPEINFO);
        registerTypeInfo(&E_MOTORBOATCAMERACTRL4_TYPEINFO);
        registerTypeInfo(&E_SPLINEHINTFOLLOWCAMERACTRL_TYPEINFO);
        registerTypeInfo(&E_GAMECAMERA_TYPEINFO);
        registerTypeInfo(&E_LOOKATMEKAO_TYPEINFO);
        registerTypeInfo(&E_PADROT_TYPEINFO);
        registerTypeInfo(&E_ICEPHYSICS_TYPEINFO);
        registerTypeInfo(&E_SNOWBOARDORIENTATION_TYPEINFO);
        registerTypeInfo(&E_SNOWBOARDPHYSICS_TYPEINFO);
        registerTypeInfo(&E_SNOWBOARDJUMPPHYSICS_TYPEINFO);
        registerTypeInfo(&E_SNOWBOARDRAMPPHYSICS_TYPEINFO);
        registerTypeInfo(&E_STRAFETARGET_TYPEINFO);
        registerTypeInfo(&E_WALKINGPHYSICS_TYPEINFO);
        registerTypeInfo(&E_PUSHABLEOBJECT_TYPEINFO);
        registerTypeInfo(&E_EXTRAALBOX_TYPEINFO);
        registerTypeInfo(&E_JUMPPHYSICS_TYPEINFO);
        registerTypeInfo(&E_SPRINGTRUNK2_TYPEINFO);
        registerTypeInfo(&E_WATERPHYSICS_TYPEINFO);
        registerTypeInfo(&E_WHALEMANAGER_TYPEINFO);
        registerTypeInfo(&E_WHALEPHYSICS_TYPEINFO);
        registerTypeInfo(&E_FLYINGOBJECTCTRL_TYPEINFO);
        registerTypeInfo(&E_FLYINGTARGET_TYPEINFO);
        registerTypeInfo(&E_EGGTARGET_TYPEINFO);
        registerTypeInfo(&E_GLOVETARGET_TYPEINFO);
        registerTypeInfo(&E_MULTITARGETTHROWER_TYPEINFO);
        registerTypeInfo(&E_EGGSFACTORY_TYPEINFO);
        registerTypeInfo(&E_EGGSNOTSTATIC_TYPEINFO);
        registerTypeInfo(&E_WATERTARGET_TYPEINFO);
        registerTypeInfo(&E_POWERUP_TYPEINFO);
        registerTypeInfo(&E_ENERGY_TYPEINFO);
        registerTypeInfo(&E_KAOKILLER_TYPEINFO);
        registerTypeInfo(&E_TRACEGADGET_TYPEINFO);
        registerTypeInfo(&E_CAMERA_TYPEINFO);
        registerTypeInfo(&E_FOLLOWCAMERACTRL_TYPEINFO);
        registerTypeInfo(&E_CAMERAZONEPACKET_TYPEINFO);
        registerTypeInfo(&E_SNOWCAMERACTRL_TYPEINFO);
        registerTypeInfo(&E_DOUBLECAMERATARGET_TYPEINFO);
        registerTypeInfo(&E_SECONDCAMERATARGET_TYPEINFO);
        registerTypeInfo(&E_OCTOPUSSY2NDTARGET_TYPEINFO);
        registerTypeInfo(&E_PARENTLISTENER_TYPEINFO);
        registerTypeInfo(&E_HEROPARENT_TYPEINFO);
        registerTypeInfo(&E_ADDNODE_TYPEINFO);
        registerTypeInfo(&E_OBJECTLINKER_TYPEINFO);
        registerTypeInfo(&E_SIMPLECR_TYPEINFO);
        registerTypeInfo(&E_TIMERGADGET_TYPEINFO);
        registerTypeInfo(&E_SCREENCOUNTER_TYPEINFO);
        registerTypeInfo(&E_MOVETO_TYPEINFO);
        registerTypeInfo(&E_GOUPANDDOWN_TYPEINFO);
        registerTypeInfo(&E_CYLINDERISECTGADGET_TYPEINFO);
        registerTypeInfo(&E_FOCMILL471DEFLECTOR_TYPEINFO);
        registerTypeInfo(&E_SETROTATION_TYPEINFO);
        registerTypeInfo(&E_PADSEQEUNCE_TYPEINFO);
        registerTypeInfo(&E_OBJECTCHAIN_TYPEINFO);
        registerTypeInfo(&E_KALMAR_TYPEINFO);
        registerTypeInfo(&E_FREEROTATE_TYPEINFO);
        registerTypeInfo(&E_GROUPMSGFORWARD_TYPEINFO);
        registerTypeInfo(&E_PERSISTENTFLOATREF_TYPEINFO);
        registerTypeInfo(&E_LIGHTBLINKER_TYPEINFO);
        registerTypeInfo(&E_CAMERADEFLECTOR_TYPEINFO);
        registerTypeInfo(&E_PATHCAMCTRL_TYPEINFO);
        registerTypeInfo(&E_GRAVITY_TYPEINFO);
        registerTypeInfo(&E_ORTHO2D_TYPEINFO);
        registerTypeInfo(&E_PARTICLEEMITER_TYPEINFO);
        registerTypeInfo(&E_POINTEMITER_TYPEINFO);
        registerTypeInfo(&E_LINEEMITER_TYPEINFO);
        registerTypeInfo(&E_PLANEEMITER_TYPEINFO);
        registerTypeInfo(&E_SPHEREEMITER_TYPEINFO);
        registerTypeInfo(&E_FSSPRITE_TYPEINFO);
        registerTypeInfo(&E_SHADOWCASTER_TYPEINFO);
        registerTypeInfo(&E_PARTICLESET_TYPEINFO);
        registerTypeInfo(&E_MARKS_TYPEINFO);
        registerTypeInfo(&E_ICECUBEMARKS_TYPEINFO);
        registerTypeInfo(&E_POSCTRL_TYPEINFO);
        registerTypeInfo(&E_ROTCTRL_TYPEINFO);
        registerTypeInfo(&E_COLORCTRL_TYPEINFO);
        registerTypeInfo(&E_OSCILATIONCTRL_TYPEINFO);
        registerTypeInfo(&E_FSMB_TYPEINFO);
        registerTypeInfo(&E_SNOW_TYPEINFO);
        registerTypeInfo(&E_FORRESTFLAKES_TYPEINFO);
        registerTypeInfo(&E_LAVAFLAKES_TYPEINFO);
        registerTypeInfo(&E_RAIN_TYPEINFO);
        registerTypeInfo(&E_LISAJOUX_TYPEINFO);
        registerTypeInfo(&E_SKYMANAGER_TYPEINFO);
        registerTypeInfo(&E_PLANKTONFLAKES_TYPEINFO);
        registerTypeInfo(&E_BUBBLEFLAKES_TYPEINFO);
        registerTypeInfo(&E_ELECTRICITY_TYPEINFO);
        registerTypeInfo(&E_OMB_TYPEINFO);
        registerTypeInfo(&E_SNDEMITERAMB_TYPEINFO);
        registerTypeInfo(&E_SNDEMITEROMNI_TYPEINFO);
        registerTypeInfo(&E_SOUNDCTRL_TYPEINFO);
        registerTypeInfo(&E_ACTOR_TYPEINFO);
        registerTypeInfo(&E_STRING2_TYPEINFO);
        registerTypeInfo(&E_FLOATPAIR_TYPEINFO);
        registerTypeInfo(&E_FLOATTRIPLE_TYPEINFO);
        registerTypeInfo(&E_IFINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_ANDINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_NOTINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_IFELSEINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_STATUSINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_STATICSTATUSINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_MSGINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_STATICMSGINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_BLOCKINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_SHIFTINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_SUPERINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_OWNERUPDATEINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_MCASTINSTANCEINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_MCASTCLASSINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_NODEREFSENDINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_EMPTYVOIDINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_AFTERINSTRUCTION_TYPEINFO);
        registerTypeInfo(&E_STATE_TYPEINFO);
        registerTypeInfo(&E_COLLISIONSPHERE_TYPEINFO);
        registerTypeInfo(&E_COLLISIONCYLINDER_TYPEINFO);
        registerTypeInfo(&E_COLLISIONMESH_TYPEINFO);
        registerTypeInfo(&E_ACTORCOLLISION_TYPEINFO);
        registerTypeInfo(&E_TURNCOLLISIONOFF_TYPEINFO);
        registerTypeInfo(&E_SETCOLLISIONFLAGS_TYPEINFO);
        registerTypeInfo(&E_FLOAT_GADGET_TYPEINFO);
        registerTypeInfo(&E_KEY_TYPEINFO);
        registerTypeInfo(&E_RND_TYPEINFO);
        registerTypeInfo(&E_LOG_TYPEINFO);
        registerTypeInfo(&E_ANIM_TYPEINFO);
        registerTypeInfo(&E_TIMER_TYPEINFO);
        registerTypeInfo(&E_SESSIONFLOAT_TYPEINFO);
        registerTypeInfo(&E_NAMESPACE_TYPEINFO);
        registerTypeInfo(&E_GADGETREF_TYPEINFO);
        registerTypeInfo(&E_WHEN_TYPEINFO);
        registerTypeInfo(&E_GADGETCLASSWHEN_TYPEINFO);
        registerTypeInfo(&E_WORLDWHEN_TYPEINFO);
        registerTypeInfo(&E_GADGETINSTANCEWHEN_TYPEINFO);
        registerTypeInfo(&E_MEWHEN_TYPEINFO);
        registerTypeInfo(&E_ACTORCLASSWHEN_TYPEINFO);
        registerTypeInfo(&E_ACTORINSTANCEWHEN_TYPEINFO);
        registerTypeInfo(&E_NODEREF_TYPEINFO);
        registerTypeInfo(&E_ACTIVATE_TYPEINFO);
        registerTypeInfo(&E_ADDPOWERUP_TYPEINFO);
        registerTypeInfo(&E_TARGETGENERATOR_TYPEINFO);
        registerTypeInfo(&E_CLONECHILD_TYPEINFO);
        registerTypeInfo(&E_BONUSSHOOTING_TYPEINFO);
        registerTypeInfo(&E_GEOEDGE_TYPEINFO);
        registerTypeInfo(&E_AMBIENTLIGHT_TYPEINFO);
        registerTypeInfo(&E_SNDEMITERBOX_TYPEINFO);
        registerTypeInfo(&E_ANIMDUMPER_TYPEINFO);
        registerTypeInfo(&E_STATEDUMPER_TYPEINFO);
        registerTypeInfo(&E_MSGDUMPER_TYPEINFO);

        return true;
    }


    ////////////////////////////////////////////////////////////////
    // KAO2 INTERFACES: register type
    ////////////////////////////////////////////////////////////////

    bool Kao2Interfaces::registerTypeInfo(const TypeInfo* info)
    {
        if (interfacesCount >= MAX_INTERFACES)
        {
            throw ErrorMessage
            (
                "registerTypeInfo():\n" \
                "too many interfaces. Increase MAX_INTERFACES (%i)",
                MAX_INTERFACES
            );

            return false;
        }

        for (int i = 0; i < interfacesCount; i++)
        {
            if (0 == std::strcmp(list[i]->name, info->name))
            {
                throw ErrorMessage
                (
                    "registerTypeInfo():\n" \
                    "class/interface \"%s\" is duplicated.",
                    info->name
                );

                return false;
            }

            if (info->id == list[i]->id)
            {
                throw ErrorMessage
                (
                    "registerTypeInfo():\n" \
                    "class/interface \"%s\" has duplicated uid 0x%04X (see class/interface \"%s\").",
                    info->name,
                    info->id,
                    list[i]->name
                );

                return false;
            }
        }

        list[interfacesCount] = (TypeInfo*)info;
        interfacesCount++;

        return true;
    }

    ////////////////////////////////////////////////////////////////
    // KAO2 INTERFACES: find type
    ////////////////////////////////////////////////////////////////

    TypeInfo* Kao2Interfaces::getTypeInfo(int id) const
    {
        for (int i=0; i < interfacesCount; i++)
        {
            if (list[i]->id == id)
            {
                return list[i];
            }
        }

        throw ErrorMessage
        (
            "getTypeInfo():\n" \
            "TypeInfo for Index 0x%08X not found!",
            id
        );

        return nullptr;
    }

    TypeInfo* Kao2Interfaces::getTypeInfo(const char* name) const
    {
        for (int i=0; i < interfacesCount; i++)
        {
            if (0 == std::strcmp(list[i]->name, name))
            {
                return list[i];
            }
        }

        throw ErrorMessage
        (
            "getTypeInfo():\n" \
            "TypeInfo for name \"%s\" not found!",
            name
        );

        return nullptr;
    }

}
