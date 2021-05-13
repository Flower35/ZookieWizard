#include <ElephantBase/TypeInfo.h>

namespace ZookieWizard
{
    Kao2Interfaces InterfaceManager;
}


////////////////////////////////////////////////////////////////
// KAO2 INTERFACES: definitions
////////////////////////////////////////////////////////////////

#include <ElephantBase/eObject.h>

#include <ElephantEngine/eMusicManager.h>
#include <ElephantEngine/eTextWriter.h>
#include <ElephantEngine/eNPCMap.h>
#include <ElephantEngine/eWalk.h>
#include <ElephantEngine/eWalkWPF.h>
#include <ElephantEngine/ePathFinder.h>
#include <ElephantEngine/eEmptyCtrl.h>
#include <ElephantEngine/eKasztanCtrl.h>
#include <ElephantEngine/eNaviPoint.h>
#include <ElephantEngine/eRndNavi.h>
#include <ElephantEngine/eEnumNavi.h>
#include <ElephantEngine/eNearestNavi.h>
#include <ElephantEngine/eGroupCtrl.h>
#include <ElephantEngine/eFlock.h>
#include <ElephantEngine/eTargeting.h>
#include <ElephantEngine/eBeeAttack.h>
#include <ElephantEngine/eDirectionCtrl.h>
#include <ElephantEngine/eFollowWPF.h>
#include <ElephantEngine/eVisibilityCtrl.h>
#include <ElephantEngine/eParticleCtrl.h>
#include <ElephantEngine/eTeleportCtrl.h>
#include <ElephantEngine/eFlockAway.h>
#include <ElephantEngine/eFloatObject.h>
#include <ElephantEngine/eCollisionCtrl.h>
#include <ElephantEngine/eDisableGeo.h>
#include <ElephantEngine/eBoids.h>
#include <ElephantEngine/eButterfly.h>
#include <ElephantEngine/eNeckCtrl.h>
#include <ElephantEngine/eSnd.h>
#include <ElephantEngine/eStaticSnd.h>
#include <ElephantEngine/eSpider.h>
#include <ElephantEngine/eCinemaMode.h>
#include <ElephantEngine/eFloatCtrlObject.h>
#include <ElephantEngine/eSplineWalk.h>
#include <ElephantEngine/eGravitation.h>
#include <ElephantEngine/eFootPrints.h>
#include <ElephantEngine/eAnimNotyfier.h>
#include <ElephantEngine/eRealTimeClock.h>
#include <ElephantEngine/eParticleManager.h>
#include <ElephantEngine/eWaterCircles.h>
#include <ElephantEngine/eFlockEx.h>
#include <ElephantEngine/eLinkToObject.h>
#include <ElephantEngine/eRollCtrl.h>
#include <ElephantEngine/eSplineSwim.h>
#include <ElephantEngine/eStrafeCtrl.h>
#include <ElephantEngine/ePlaszczka.h>
#include <ElephantEngine/eDzwig.h>
#include <ElephantEngine/eHitForceCtrl.h>
#include <ElephantEngine/eSwitelikKao.h>
#include <ElephantEngine/eKolec.h>
#include <ElephantEngine/eBombaExplodujaca.h>
#include <ElephantEngine/ePowerBar.h>
#include <ElephantEngine/eLevelChanger.h>
#include <ElephantEngine/eSpeaking.h>
#include <ElephantEngine/eDemoPlayer.h>
#include <ElephantEngine/eBonusBieg.h>
#include <ElephantEngine/eBaseballBieg.h>
#include <ElephantEngine/eTextWriterEx.h>
#include <ElephantEngine/eReadySteadyGo.h>
#include <ElephantEngine/eEnemyMapUpgrader.h>
#include <ElephantEngine/eMotorowki.h>
#include <ElephantEngine/eAskYesNo.h>
#include <ElephantEngine/eCredits.h>
#include <ElephantEngine/eDirectionCtrlEx.h>
#include <ElephantEngine/eFloat.h>
#include <ElephantEngine/eTriMesh.h>
#include <ElephantEngine/eGeoSet.h>
#include <ElephantEngine/eGeoArray.h>
#include <ElephantEngine/eBitmap.h>
#include <ElephantEngine/eTexTransform.h>
#include <ElephantEngine/eTexture.h>
#include <ElephantEngine/eNode.h>
#include <ElephantEngine/eTransform.h>
#include <ElephantEngine/eMaterial.h>
#include <ElephantEngine/eEnvironment.h>
#include <ElephantEngine/eFogEnv.h>
#include <ElephantEngine/eOmniLight.h>
#include <ElephantEngine/eDirectionalLight.h>
#include <ElephantEngine/eMaterialState.h>
#include <ElephantEngine/eGroup.h>
#include <ElephantEngine/eProxy.h>
#include <ElephantEngine/eAnimBillboardTarget.h>
#include <ElephantEngine/eAnimBillboardProxy.h>
#include <ElephantEngine/ePivot.h>
#include <ElephantEngine/eScene.h>
#include <ElephantEngine/eALZoneSensor.h>
#include <ElephantEngine/eZone.h>
#include <ElephantEngine/eBoxZone.h>
#include <ElephantEngine/eMorpherTarget.h>
#include <ElephantEngine/eMorpherMod.h>
#include <ElephantEngine/eMultiCtrl.h>
#include <ElephantEngine/eXYZPoint3Ctrl.h>
#include <ElephantEngine/eXYZEulerRotation.h>
#include <ElephantEngine/eSRPCombineCtrl.h>
#include <ElephantEngine/eLeafCtrl.h>
#include <ElephantEngine/eSpline3D.h>
#include <ElephantEngine/ePathConstrainCtrl.h>
#include <ElephantEngine/eBezierSplineNode.h>
#include <ElephantEngine/eALBox.h>
#include <ElephantEngine/eCylNode.h>
#include <ElephantEngine/eSphNode.h>
#include <ElephantEngine/eBillboard.h>
#include <ElephantEngine/eXRefTarget.h>
#include <ElephantEngine/eXRefProxy.h>
#include <ElephantEngine/eXRefManager.h>
#include <ElephantEngine/eMultiTransform.h>
#include <ElephantEngine/ePhyTriMesh.h>
#include <ElephantEngine/eTrack.h>
#include <ElephantEngine/eAnimState.h>
#include <ElephantEngine/eTouchSensor.h>
#include <ElephantEngine/eBlockIndexCtrl.h>
#include <ElephantEngine/eGlobalLightCtrl.h>
#include <ElephantEngine/ePadGadget.h>
#include <ElephantEngine/eTorpedoMode.h>
#include <ElephantEngine/eVibrate.h>
#include <ElephantEngine/eHistory.h>
#include <ElephantEngine/eCameraShaker.h>
#include <ElephantEngine/eCameraFOVCtrl.h>
#include <ElephantEngine/eMotorboatCameraCtrl.h>
#include <ElephantEngine/eMotorboatCameraCtrl4.h>
#include <ElephantEngine/eSplineHintFollowCameraCtrl.h>
#include <ElephantEngine/eGameCamera.h>
#include <ElephantEngine/eLookAtMeKao.h>
#include <ElephantEngine/ePadRot.h>
#include <ElephantEngine/eIcePhysics.h>
#include <ElephantEngine/eSnowboardOrientation.h>
#include <ElephantEngine/eSnowboardPhysics.h>
#include <ElephantEngine/eSnowboardJumpPhysics.h>
#include <ElephantEngine/eSnowboardRampPhysics.h>
#include <ElephantEngine/eStrafeTarget.h>
#include <ElephantEngine/eWalkingPhysics.h>
#include <ElephantEngine/ePushableObject.h>
#include <ElephantEngine/eExtraAlbox.h>
#include <ElephantEngine/eJumpPhysics.h>
#include <ElephantEngine/eSpringTrunk2.h>
#include <ElephantEngine/eWaterPhysics.h>
#include <ElephantEngine/eWhaleManager.h>
#include <ElephantEngine/eWhalePhysics.h>
#include <ElephantEngine/eFlyingObjectCtrl.h>
#include <ElephantEngine/eFlyingTarget.h>
#include <ElephantEngine/eEggTarget.h>
#include <ElephantEngine/eGloveTarget.h>
#include <ElephantEngine/eMultiTargetThrower.h>
#include <ElephantEngine/eEggsFactory.h>
#include <ElephantEngine/eEggsNotStatic.h>
#include <ElephantEngine/eWaterTarget.h>
#include <ElephantEngine/ePowerUp.h>
#include <ElephantEngine/eEnergy.h>
#include <ElephantEngine/eKaoKiller.h>
#include <ElephantEngine/eTraceGadget.h>
#include <ElephantEngine/eCamera.h>
#include <ElephantEngine/eFollowCameraCtrl.h>
#include <ElephantEngine/eCameraZonePacket.h>
#include <ElephantEngine/eSnowCameraCtrl.h>
#include <ElephantEngine/eDoubleCameraTarget.h>
#include <ElephantEngine/eSecondCameraTarget.h>
#include <ElephantEngine/eOctopussy2ndTarget.h>
#include <ElephantEngine/eParentListener.h>
#include <ElephantEngine/eHeroParent.h>
#include <ElephantEngine/eAddNode.h>
#include <ElephantEngine/eObjectLinker.h>
#include <ElephantEngine/eSimpleCR.h>
#include <ElephantEngine/eTimerGadget.h>
#include <ElephantEngine/eScreenCounter.h>
#include <ElephantEngine/eMoveTo.h>
#include <ElephantEngine/eGoUpAndDown.h>
#include <ElephantEngine/eCylinderIsectGadget.h>
#include <ElephantEngine/eFocMill471Deflector.h>
#include <ElephantEngine/eSetRotation.h>
#include <ElephantEngine/ePadSeqeunce.h>
#include <ElephantEngine/eObjectChain.h>
#include <ElephantEngine/eKalmar.h>
#include <ElephantEngine/eFreeRotate.h>
#include <ElephantEngine/eGroupMsgForward.h>
#include <ElephantEngine/ePersistentFloatRef.h>
#include <ElephantEngine/eLightBlinker.h>
#include <ElephantEngine/eCameraDeflector.h>
#include <ElephantEngine/ePathCamCtrl.h>
#include <ElephantEngine/eGravity.h>
#include <ElephantEngine/eOrtho2D.h>
#include <ElephantEngine/eParticleEmiter.h>
#include <ElephantEngine/ePointEmiter.h>
#include <ElephantEngine/eLineEmiter.h>
#include <ElephantEngine/ePlaneEmiter.h>
#include <ElephantEngine/eSphereEmiter.h>
#include <ElephantEngine/eFSSprite.h>
#include <ElephantEngine/eShadowCaster.h>
#include <ElephantEngine/eParticleSet.h>
#include <ElephantEngine/eMarks.h>
#include <ElephantEngine/eIceCubeMarks.h>
#include <ElephantEngine/ePosCtrl.h>
#include <ElephantEngine/eRotCtrl.h>
#include <ElephantEngine/eColorCtrl.h>
#include <ElephantEngine/eOscilationCtrl.h>
#include <ElephantEngine/eFSMB.h>
#include <ElephantEngine/eSnow.h>
#include <ElephantEngine/eForrestFlakes.h>
#include <ElephantEngine/eLavaFlakes.h>
#include <ElephantEngine/eRain.h>
#include <ElephantEngine/eLisajoux.h>
#include <ElephantEngine/eSkyManager.h>
#include <ElephantEngine/ePlanktonFlakes.h>
#include <ElephantEngine/eBubbleFlakes.h>
#include <ElephantEngine/eElectricity.h>
#include <ElephantEngine/eOMB.h>
#include <ElephantEngine/eSndEmiterAmb.h>
#include <ElephantEngine/eSndEmiterOmni.h>
#include <ElephantEngine/eSoundCtrl.h>
#include <ElephantEngine/Actor.h>
#include <ElephantEngine/eString2.h>
#include <ElephantEngine/eFloatPair.h>
#include <ElephantEngine/eFloatTriple.h>
#include <ElephantEngine/IfInstruction.h>
#include <ElephantEngine/AndInstruction.h>
#include <ElephantEngine/NotInstruction.h>
#include <ElephantEngine/IfElseInstruction.h>
#include <ElephantEngine/StatusInstruction.h>
#include <ElephantEngine/StaticStatusInstruction.h>
#include <ElephantEngine/MsgInstruction.h>
#include <ElephantEngine/StaticMsgInstruction.h>
#include <ElephantEngine/BlockInstruction.h>
#include <ElephantEngine/ShiftInstruction.h>
#include <ElephantEngine/SuperInstruction.h>
#include <ElephantEngine/OwnerUpdateInstruction.h>
#include <ElephantEngine/McastInstanceInstruction.h>
#include <ElephantEngine/McastClassInstruction.h>
#include <ElephantEngine/NodeRefSendInstruction.h>
#include <ElephantEngine/EmptyVoidInstruction.h>
#include <ElephantEngine/AfterInstruction.h>
#include <ElephantEngine/State.h>
#include <ElephantEngine/eCollisionSphere.h>
#include <ElephantEngine/eCollisionCylinder.h>
#include <ElephantEngine/eCollisionMesh.h>
#include <ElephantEngine/eActorCollision.h>
#include <ElephantEngine/eTurnCollisionOff.h>
#include <ElephantEngine/eSetCollisionFlags.h>
#include <ElephantEngine/Float.h>
#include <ElephantEngine/Key.h>
#include <ElephantEngine/Rnd.h>
#include <ElephantEngine/Log.h>
#include <ElephantEngine/Anim.h>
#include <ElephantEngine/Timer.h>
#include <ElephantEngine/SessionFloat.h>
#include <ElephantEngine/Namespace.h>
#include <ElephantEngine/GadgetRef.h>
#include <ElephantEngine/When.h>
#include <ElephantEngine/GadgetClassWhen.h>
#include <ElephantEngine/WorldWhen.h>
#include <ElephantEngine/GadgetInstanceWhen.h>
#include <ElephantEngine/MeWhen.h>
#include <ElephantEngine/ActorClassWhen.h>
#include <ElephantEngine/ActorInstanceWhen.h>
#include <ElephantEngine/NodeRef.h>
#include <ElephantEngine/eActivate.h>
#include <ElephantEngine/eAddPowerUp.h>
#include <ElephantEngine/eTargetGenerator.h>
#include <ElephantEngine/eCloneChild.h>
#include <ElephantEngine/eBonusShooting.h>
#include <ElephantEngine/eGeoEdge.h>
#include <ElephantEngine/eAmbientLight.h>
#include <ElephantEngine/eSndEmiterBox.h>
#include <ElephantEngine/AnimDumper.h>
#include <ElephantEngine/StateDumper.h>
#include <ElephantEngine/MsgDumper.h>


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
