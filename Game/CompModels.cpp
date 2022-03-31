#include "StdAfx.h"
#include "LCDDrawing.h"

#include "Models/Enemies/Headman/Headman.h"
#include "Models/Enemies/Eyeman/Eyeman.h"
#include "Models/Enemies/Boneman/Boneman.h"
#include "Models/Enemies/Werebull/Werebull.h"
#include "Models/Enemies/Scorpman/Scorpman.h"
#include "Models/Enemies/Walker/Walker.h"
#include "Models/Enemies/Woman/Woman.h"
#include "Models/Enemies/Gizmo/Gizmo.h"
#include "Models/Enemies/Fish/Fish.h"
#include "Models/Enemies/Beast/Beast.h"
#include "Models/Enemies/Devil/Devil.h"
#include "Models/Enemies/ElementalLava/ElementalLava.h"

#include "Models/Weapons/Knife/KnifeItem.h"
#include "Models/Weapons/Colt/ColtItem.h"
#include "Models/Weapons/SingleShotgun/SingleShotgunItem.h"
#include "Models/Weapons/DoubleShotgun/DoubleShotgunItem.h"
#include "Models/Weapons/Minigun/MinigunItem.h"
#include "Models/Weapons/Tommygun/TommygunItem.h"
#include "Models/Weapons/RocketLauncher/RocketLauncherItem.h"
#include "Models/Weapons/GrenadeLauncher/GrenadeLauncherItem.h"
#include "Models/Weapons/Laser/LaserItem.h"
#include "Models/Weapons/Cannon/Cannon.h"

// model's data
static CModelObject _moModel;
static CModelObject _moFloor;
static CPlacement3D _plModel;
static ANGLE3D _aRotation;
static BOOL _bHasFloor = FALSE;
static FLOAT _fFloorY = 0.0f;
static FLOAT _fFOV = 90.0f;
static FLOAT3D _vLightDir = FLOAT3D( -0.2f, -0.2f, -0.2f);
static _colLight = C_GRAY;
static _colAmbient = C_vdGRAY;

// model setting values
static CTString _strLastModel = "";
static BOOL _bModelOK = FALSE;

extern FLOAT _fMsgAppearFade;

CModelObject *AddAttachment_t(CModelObject *pmoParent, INDEX iPosition,
   const CTFileName &fnmModel, INDEX iAnim,
   const CTFileName &fnmTexture,
   const CTFileName &fnmReflection=CTFILENAME(""),
   const CTFileName &fnmSpecular=CTFILENAME(""))
{
  CAttachmentModelObject *pamo = pmoParent->AddAttachmentModel(iPosition);
  ASSERT(pamo!=NULL);
  pamo->amo_moModelObject.SetData_t(fnmModel);
  pamo->amo_moModelObject.PlayAnim(iAnim, AOF_LOOPING);
  pamo->amo_moModelObject.mo_toTexture.SetData_t(fnmTexture);
  pamo->amo_moModelObject.mo_toReflection.SetData_t(fnmReflection);
  pamo->amo_moModelObject.mo_toSpecular.SetData_t(fnmSpecular);
  return &pamo->amo_moModelObject;
}

extern void SetupCompModel_t(const CTString &strName)
{
  CModelObject *pmo = &_moModel;
  _aRotation = ANGLE3D(0,0,0);
  _bHasFloor = FALSE;
  _fFloorY = 0.0f;
  _fFOV = 90.0f;
  _vLightDir = FLOAT3D( -0.2f, -0.2f, -0.2f);
  _colLight = C_GRAY;
  _colAmbient = C_vdGRAY;
  _moFloor.SetData_t(CTFILENAME("Models\\Computer\\Floor.mdl"));
  _moFloor.mo_toTexture.SetData_t(CTFILENAME("Models\\Computer\\Floor.tex"));
  if (strName=="Rocketman") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Headman.mdl"));
    pmo->PlayAnim(HEADMAN_ANIM_COMPUTERKAMIKAZE, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Rocketman.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0,-1.75), ANGLE3D(210,0,0));

    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_HEAD, 
      CTFILENAME("Models\\Enemies\\Headman\\Head.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\Head.tex"));
    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_ROCKET_LAUNCHER, 
      CTFILENAME("Models\\Enemies\\Headman\\RocketLauncher.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\RocketLauncher.tex"));
    pmo->StretchModel(FLOAT3D(1.25f,1.25f,1.25f));
    _bHasFloor = TRUE;

  } else if (strName=="Firecracker") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Headman.mdl"));
    pmo->PlayAnim(HEADMAN_ANIM_COMPUTERKAMIKAZE, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Firecracker.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0,-1.75), ANGLE3D(210,0,0));

    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_HEAD, 
      CTFILENAME("Models\\Enemies\\Headman\\FirecrackerHead.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\FirecrackerHead.tex"));
    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_CHAINSAW, 
      CTFILENAME("Models\\Enemies\\Headman\\Chainsaw.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\Chainsaw.tex"));
    pmo->StretchModel(FLOAT3D(1.25f,1.25f,1.25f));
    _bHasFloor = TRUE;

  } else if (strName=="Bomberman") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Headman.mdl"));
    pmo->PlayAnim(HEADMAN_ANIM_COMPUTERKAMIKAZE, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Bomberman.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0,-1.75), ANGLE3D(210,0,0));
  
    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_HEAD, 
      CTFILENAME("Models\\Enemies\\Headman\\Head.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\Head.tex"));
    pmo->StretchModel(FLOAT3D(1.25f,1.25f,1.25f));
    _bHasFloor = TRUE;

  } else if (strName=="Kamikaze") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Headman.mdl"));
    pmo->PlayAnim(HEADMAN_ANIM_COMPUTERKAMIKAZE, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Headman\\Kamikaze.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0,-1.75), ANGLE3D(210,0,0));
  
    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_BOMB_RIGHT_HAND, 
      CTFILENAME("Models\\Enemies\\Headman\\Projectile\\Bomb.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\Projectile\\Bomb.tex"));
    AddAttachment_t(pmo, HEADMAN_ATTACHMENT_BOMB_LEFT_HAND, 
      CTFILENAME("Models\\Enemies\\Headman\\Projectile\\Bomb.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Headman\\Projectile\\Bomb.tex"));
    pmo->StretchModel(FLOAT3D(1.25f,1.25f,1.25f));
    _bHasFloor = TRUE;

  } else if (strName=="EyemanPurple") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Eyeman\\Eyeman.mdl"));
    pmo->PlayAnim(EYEMAN_ANIM_WALK, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Eyeman\\Eyeman4.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.9f,-1.5), ANGLE3D(210,0,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _bHasFloor = TRUE;

  } else if (strName=="EyemanGreen") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Eyeman\\Eyeman.mdl"));
    pmo->PlayAnim(EYEMAN_ANIM_WALK, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Eyeman\\Eyeman5.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.2f,-2.0), ANGLE3D(210,0,0));
    pmo->StretchModel(FLOAT3D(1.3f, 1.3f, 1.3f));
    _bHasFloor = TRUE;

  } else if (strName=="Boneman") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Boneman\\Boneman.mdl"));
    pmo->PlayAnim(BONEMAN_ANIM_WALKCOMPUTER, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Boneman\\Boneman.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0f,-3.0), ANGLE3D(210,0,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _bHasFloor = TRUE;

  } else if (strName=="Bull") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Werebull\\Werebull.mdl"));
    pmo->PlayAnim(WEREBULL_ANIM_WALK, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Werebull\\Werebull.tex"));
    _plModel = CPlacement3D(FLOAT3D(0.0f,-1.5f,-4.0), ANGLE3D(-110,0,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _bHasFloor = TRUE;

  } else if (strName=="ScorpmanSoldier") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Scorpman\\Scorpman.mdl"));
    pmo->mo_toSpecular.SetData_t(CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->PlayAnim(SCORPMAN_ANIM_WALK, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Scorpman\\Soldier.tex"));
//    _plModel = CPlacement3D(FLOAT3D(0+0.2f*2,-2,-13), ANGLE3D(150,0,0));
//    _fFOV = 30;
    _plModel = CPlacement3D(FLOAT3D(0+0.5f*3,-3.0f,-7.0)*2/3, ANGLE3D(135,0,0));
    _vLightDir = FLOAT3D( 0.2f, -0.2f, -0.2f);
    _colLight = C_lGRAY;
    _colAmbient = C_vdGRAY;

    AddAttachment_t(pmo, SCORPMAN_ATTACHMENT_MINIGUN, 
      CTFILENAME("Models\\Enemies\\Scorpman\\Gun.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Scorpman\\Gun.tex"));

    pmo->StretchModel(FLOAT3D(2.0f,2.0f,2.0f));
    _bHasFloor = TRUE;

  } else if (strName=="ScorpmanGeneral") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Scorpman\\Scorpman.mdl"));
    pmo->PlayAnim(SCORPMAN_ANIM_WALK, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Scorpman\\General.tex"));
    pmo->mo_toSpecular.SetData_t(CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
//    _plModel = CPlacement3D(FLOAT3D(0+0.2f*3,-4,-19), ANGLE3D(150,0,0));
//    _fFOV = 30;
    _plModel = CPlacement3D(FLOAT3D(0+0.5f*3,-3.0f,-7.0), ANGLE3D(135,0,0));
    _vLightDir = FLOAT3D( 0.2f, -0.2f, -0.2f);
    _colLight = C_lGRAY;
    _colAmbient = C_vdGRAY;

    AddAttachment_t(pmo, SCORPMAN_ATTACHMENT_MINIGUN, 
      CTFILENAME("Models\\Enemies\\Scorpman\\Gun.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Scorpman\\Gun.tex"));

    pmo->StretchModel(FLOAT3D(3.0f,3.0f,3.0f));
    _bHasFloor = TRUE;

  } else if (strName=="WalkerSmall") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Walker\\Walker.mdl"));
    pmo->PlayAnim(WALKER_ANIM_WALKBIG, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Walker\\Walker02.tex"));
    AddAttachment_t(pmo, WALKER_ATTACHMENT_ROCKETLAUNCHER_LT, 
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.tex"),
      CTFILENAME(""),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, WALKER_ATTACHMENT_ROCKETLAUNCHER_RT, 
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.tex"),
      CTFILENAME(""),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-2.0f,-5.0), ANGLE3D(210,0,0));
    pmo->StretchModel(FLOAT3D(0.5,0.5,0.5));
    _bHasFloor = TRUE;
    _colLight = C_lGRAY;
    _colAmbient = C_vdGRAY;

  } else if (strName=="WalkerBig") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Walker\\Walker.mdl"));
    pmo->PlayAnim(WALKER_ANIM_WALKBIG, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Walker\\Walker01.tex"));
    AddAttachment_t(pmo, WALKER_ATTACHMENT_ROCKETLAUNCHER_LT, 
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.tex"),
      CTFILENAME(""),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, WALKER_ATTACHMENT_ROCKETLAUNCHER_RT, 
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.mdl"), 0,
      CTFILENAME("Models\\Enemies\\Walker\\RocketLauncher.tex"),
      CTFILENAME(""),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-4.0f,-10.0), ANGLE3D(210,0,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _bHasFloor = TRUE;

  } else if (strName=="Woman") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Woman\\Woman.mdl"));
    pmo->PlayAnim(WOMAN_ANIM_AIRSTAND, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Woman\\Woman.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,0.0f,-2.0), ANGLE3D(210,30,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _bHasFloor = TRUE;
    _fFloorY = -1.5f;

  } else if (strName=="Gizmo") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Gizmo\\Gizmo.mdl"));
    pmo->PlayAnim(GIZMO_ANIM_IDLE, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Gizmo\\Gizmo.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.5f,-1.2f), ANGLE3D(150,0,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _fFloorY = 0.0f;
    _bHasFloor = TRUE;

  } else if (strName=="Fish") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Fish\\Fish.mdl"));
    pmo->PlayAnim(FISH_ANIM_IDLE, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Fish\\Fish1.tex"));
    pmo->mo_toSpecular.SetData_t(CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    _plModel = CPlacement3D(FLOAT3D(-0.2f,-0.5f,-3.0), ANGLE3D(250,0,0));
    pmo->StretchModel(FLOAT3D(1,1,1));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="BeastNormal") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Beast\\Beast.mdl"));
    pmo->PlayAnim(BEAST_ANIM_IDLECOMPUTER, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Beast\\Beast.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-2.0f,-6.0), ANGLE3D(170,0,0));
    pmo->StretchModel(FLOAT3D(2,2,2));
    _bHasFloor = TRUE;

  } else if (strName=="BeastBig") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Beast\\Beast.mdl"));
    pmo->PlayAnim(BEAST_ANIM_IDLECOMPUTER, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Beast\\BeastBig.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-5.0f,-18.0), ANGLE3D(170,0,0));
    pmo->StretchModel(FLOAT3D(6,6,6));
    _bHasFloor = TRUE;

  } else if (strName=="ElementalLava") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\ElementalLava\\ElementalLava.mdl"));
    pmo->PlayAnim(ELEMENTALLAVA_ANIM_WALKCOMPUTER, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\ElementalLava\\Lava04Fx.tex"));
    pmo->mo_toBump.SetData_t(CTFILENAME("Models\\Enemies\\ElementalLava\\Detail.tex"));
    AddAttachment_t(pmo, ELEMENTALLAVA_ATTACHMENT_BODY_FLARE, 
      CTFILENAME("Models\\Enemies\\ElementalLava\\BodyFlare.mdl"), 0,
      CTFILENAME("Models\\Enemies\\ElementalLava\\Flare.tex"));
    AddAttachment_t(pmo, ELEMENTALLAVA_ATTACHMENT_RIGHT_HAND_FLARE, 
      CTFILENAME("Models\\Enemies\\ElementalLava\\HandFlare.mdl"), 0,
      CTFILENAME("Models\\Enemies\\ElementalLava\\Flare.tex"));
    AddAttachment_t(pmo, ELEMENTALLAVA_ATTACHMENT_LEFT_HAND_FLARE, 
      CTFILENAME("Models\\Enemies\\ElementalLava\\HandFlare.mdl"), 0,
      CTFILENAME("Models\\Enemies\\ElementalLava\\Flare.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-5.0f,-8.0), ANGLE3D(150,0,0));
    pmo->StretchModel(FLOAT3D(4,4,4));
    _bHasFloor = TRUE;

  } else if (strName=="Devil") {
    pmo->SetData_t(CTFILENAME("Models\\Enemies\\Devil\\Devil.mdl"));
    pmo->PlayAnim(DEVIL_ANIM_WALK, AOF_LOOPING);
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Enemies\\Devil\\Devil.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-12.0f,-25.0), ANGLE3D(150,0,0));
    pmo->StretchModel(FLOAT3D(12,12,12));
    _bHasFloor = TRUE;

  } else if (strName=="Knife") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\Knife\\KnifeItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\Knife\\KnifeItem.tex"));
    pmo->PlayAnim(KNIFEITEM_ANIM_COMPUTER, AOF_LOOPING);
    _plModel = CPlacement3D(FLOAT3D(0,-0.5f,-2.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    pmo->StretchModel(FLOAT3D(4,4,4));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="Colt") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\Colt\\ColtItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\Colt\\ColtMain.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.5f,-2.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, COLTITEM_ATTACHMENT_BULLETS, 
      CTFILENAME("Models\\Weapons\\Colt\\ColtBullets.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Colt\\ColtBullets.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightBlueMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, COLTITEM_ATTACHMENT_COCK, 
      CTFILENAME("Models\\Weapons\\Colt\\ColtCock.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Colt\\ColtCock.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightBlueMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, COLTITEM_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\Colt\\ColtMain.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Colt\\ColtMain.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightBlueMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(4,4,4));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="SingleShotgun") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\SingleShotgun\\SingleShotgunItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\SingleShotgun\\Handle.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.5f,-3.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, SINGLESHOTGUNITEM_ATTACHMENT_BARRELS, 
      CTFILENAME("Models\\Weapons\\SingleShotgun\\Barrels.mdl"), 0,
      CTFILENAME("Models\\Weapons\\SingleShotgun\\Barrels.tex"),
      CTFILENAME("Models\\ReflectionTextures\\DarkMetal.tex"),
      CTFILENAME("Models\\SpecularTextures\\Weak.tex"));
    AddAttachment_t(pmo, SINGLESHOTGUNITEM_ATTACHMENT_HANDLE, 
      CTFILENAME("Models\\Weapons\\SingleShotgun\\Handle.mdl"), 0,
      CTFILENAME("Models\\Weapons\\SingleShotgun\\Handle.tex"),
      CTFILENAME("Models\\ReflectionTextures\\DarkMetal.tex"),
      CTFILENAME("Models\\SpecularTextures\\Weak.tex"));
    AddAttachment_t(pmo, SINGLESHOTGUNITEM_ATTACHMENT_SLIDER, 
      CTFILENAME("Models\\Weapons\\SingleShotgun\\Slider.mdl"), 0,
      CTFILENAME("Models\\Weapons\\SingleShotgun\\Barrels.tex"),
      CTFILENAME("Models\\ReflectionTextures\\DarkMetal.tex"),
      CTFILENAME("Models\\SpecularTextures\\Weak.tex"));
    pmo->StretchModel(FLOAT3D(3.5,3.5,3.5));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="DoubleShotgun") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\DoubleShotgun\\DoubleShotgunItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\DoubleShotgun\\Handle.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.5f,-4.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, DOUBLESHOTGUNITEM_ATTACHMENT_BARRELS, 
      CTFILENAME("Models\\Weapons\\DoubleShotgun\\DshotgunBarrels.mdl"), 0,
      CTFILENAME("Models\\Weapons\\DoubleShotgun\\Barrels.tex"),
      CTFILENAME("Models\\ReflectionTextures\\BWRiples01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, DOUBLESHOTGUNITEM_ATTACHMENT_HANDLE, 
      CTFILENAME("Models\\Weapons\\DoubleShotgun\\DshotgunHandle.mdl"), 0,
      CTFILENAME("Models\\Weapons\\DoubleShotgun\\Handle.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, DOUBLESHOTGUNITEM_ATTACHMENT_SWITCH, 
      CTFILENAME("Models\\Weapons\\DoubleShotgun\\Switch.mdl"), 0,
      CTFILENAME("Models\\Weapons\\DoubleShotgun\\Switch.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(3.0,3.0,3.0));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="Tommygun") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\Tommygun\\TommygunItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\Tommygun\\Body.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.8f,-1.8f), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, TOMMYGUNITEM_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\Tommygun\\Body.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Tommygun\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, TOMMYGUNITEM_ATTACHMENT_SLIDER, 
      CTFILENAME("Models\\Weapons\\Tommygun\\Slider.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Tommygun\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(2.0,2.0,2.0));
    _bHasFloor = TRUE;
    _fFloorY = -0.5f;

  } else if (strName=="Minigun") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\Minigun\\MinigunItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\Minigun\\Minigun.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-0.5f,-3.75f), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, MINIGUNITEM_ATTACHMENT_BARRELS, 
      CTFILENAME("Models\\Weapons\\Minigun\\Barrels.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Minigun\\Barrels.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, MINIGUNITEM_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\Minigun\\Body.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Minigun\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, MINIGUNITEM_ATTACHMENT_ENGINE, 
      CTFILENAME("Models\\Weapons\\Minigun\\Engine.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Minigun\\Barrels.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(1.75,1.75,1.75));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="RocketLauncher") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\RocketLauncher\\RocketLauncherItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\RocketLauncher\\Body.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0f,-3.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, ROCKETLAUNCHERITEM_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Body.mdl"), 0,
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, ROCKETLAUNCHERITEM_ATTACHMENT_ROTATINGPART, 
      CTFILENAME("Models\\Weapons\\RocketLauncher\\RotatingPart.mdl"), 0,
      CTFILENAME("Models\\Weapons\\RocketLauncher\\RotatingPart.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, ROCKETLAUNCHERITEM_ATTACHMENT_ROCKET1, 
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.mdl"), 0,
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, ROCKETLAUNCHERITEM_ATTACHMENT_ROCKET2, 
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.mdl"), 0,
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, ROCKETLAUNCHERITEM_ATTACHMENT_ROCKET3, 
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.mdl"), 0,
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, ROCKETLAUNCHERITEM_ATTACHMENT_ROCKET4, 
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.mdl"), 0,
      CTFILENAME("Models\\Weapons\\RocketLauncher\\Projectile\\Rocket.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(2.5,2.5,2.5));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="GrenadeLauncher") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\GrenadeLauncher\\GrenadeLauncherItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\GrenadeLauncher\\Body.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0f,-4.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, GRENADELAUNCHERITEM_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\GrenadeLauncher\\Body.mdl"), 0,
      CTFILENAME("Models\\Weapons\\GrenadeLauncher\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, GRENADELAUNCHERITEM_ATTACHMENT_MOVING_PART, 
      CTFILENAME("Models\\Weapons\\GrenadeLauncher\\MovingPipe.mdl"), 0,
      CTFILENAME("Models\\Weapons\\GrenadeLauncher\\MovingPipe.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, GRENADELAUNCHERITEM_ATTACHMENT_GRENADE, 
      CTFILENAME("Models\\Weapons\\GrenadeLauncher\\GrenadeBack.mdl"), 0,
      CTFILENAME("Models\\Weapons\\GrenadeLauncher\\MovingPipe.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(2.5,2.5,2.5));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="Laser") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\Laser\\LaserItem.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\Laser\\Body.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0f,-3.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, LASERITEM_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\Laser\\Body.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Laser\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, LASERITEM_ATTACHMENT_LEFTUP, 
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, LASERITEM_ATTACHMENT_LEFTDOWN, 
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, LASERITEM_ATTACHMENT_RIGHTUP, 
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    AddAttachment_t(pmo, LASERITEM_ATTACHMENT_RIGHTDOWN, 
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Laser\\Barrel.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(2.5,2.5,2.5));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else if (strName=="Cannon") {
    pmo->SetData_t(CTFILENAME("Models\\Weapons\\Cannon\\Cannon.mdl"));
    pmo->mo_toTexture.SetData_t(CTFILENAME("Models\\Weapons\\Cannon\\Body.tex"));
    _plModel = CPlacement3D(FLOAT3D(0,-1.0f,-3.0), ANGLE3D(0,10,0));
    _aRotation = ANGLE3D(100,0,0);

    AddAttachment_t(pmo, CANNON_ATTACHMENT_BODY, 
      CTFILENAME("Models\\Weapons\\Cannon\\Body.mdl"), 0,
      CTFILENAME("Models\\Weapons\\Cannon\\Body.tex"),
      CTFILENAME("Models\\ReflectionTextures\\LightMetal01.tex"),
      CTFILENAME("Models\\SpecularTextures\\Medium.tex"));
    pmo->StretchModel(FLOAT3D(2.5,2.5,2.5));
    _bHasFloor = TRUE;
    _fFloorY = -1.0f;

  } else {
    ThrowF_t(TRANS("Unknown model '%s'"), strName);
  }
}

void RenderMessageModel(CDrawPort *pdp, const CTString &strModel)
{
  // if new model
  if (_strLastModel!=strModel) {
    _strLastModel=strModel;
    _bModelOK = FALSE;
    // try to
    try {
      // load model
      SetupCompModel_t(strModel);
      _bModelOK = TRUE;
    // if failed
    } catch(char *strError) {
      // report error
      CPrintF("Cannot setup model '%s':\n%s\n", strModel, strError);
      // do nothing
      return;
    }
  }

  // if model is not loaded ok
  if (!_bModelOK) {
    // do nothing
    return;
  }

  // prepare projection
  CRenderModel rm;
  CPerspectiveProjection3D pr;
  pr.FOVL() = AngleDeg(_fFOV);
  pr.ScreenBBoxL() = FLOATaabbox2D(
    FLOAT2D(0.0f, 0.0f),
    FLOAT2D((float)pdp->GetWidth(), (float)pdp->GetHeight())
  );
  pr.AspectRatioL() = 1.0f;
  pr.FrontClipDistanceL() = 0.3f;
  pr.ViewerPlacementL() = CPlacement3D(FLOAT3D(0,0,0), ANGLE3D(0,0,0));
  
  // initialize remdering
  CAnyProjection3D apr;
  apr = pr;
  BeginModelRenderingView(apr, pdp);
  rm.rm_vLightDirection = _vLightDir;
  const FLOAT fDistance = 1+ 10*(1/(_fMsgAppearFade+0.01) - 1/(1+0.01));

  // if model needs floor
  if( _bHasFloor) {
    // set floor's position
    CPlacement3D pl = _plModel;
    pl.pl_OrientationAngle = ANGLE3D(0,0,0);
    pl.pl_PositionVector   = _plModel.pl_PositionVector;
    pl.pl_PositionVector(2) += _fFloorY;
    pl.pl_PositionVector(3) *= fDistance;
    rm.SetObjectPlacement(pl);
    // render the floor
    rm.rm_colLight   = C_WHITE;
    rm.rm_colAmbient = C_WHITE;
    rm.rm_fDistanceFactor = -999;
    _moFloor.SetupModelRendering(rm);
    _moFloor.RenderModel(rm);
  }

  // set model's position
  CPlacement3D pl;
  pl.pl_OrientationAngle   = _plModel.pl_OrientationAngle + _aRotation*_pTimer->GetLerpedCurrentTick();
  pl.pl_PositionVector     = _plModel.pl_PositionVector;
  pl.pl_PositionVector(3) *= fDistance / pdp->dp_fWideAdjustment;
  rm.SetObjectPlacement(pl);

  // render the model
  rm.rm_colLight   = _colLight;
  rm.rm_colAmbient = _colAmbient;
  rm.rm_fDistanceFactor = -999; // force highest mip disregarding stretch factors
  _moModel.SetupModelRendering(rm);
  FLOATplane3D plFloorPlane = FLOATplane3D( FLOAT3D( 0.0f, 1.0f, 0.0f), _plModel.pl_PositionVector(2)+_fFloorY);
  CPlacement3D plLightPlacement = CPlacement3D( _plModel.pl_PositionVector
                                + rm.rm_vLightDirection * _plModel.pl_PositionVector(3) *5, ANGLE3D(0,0,0));
  _moModel.RenderShadow( rm, plLightPlacement, 200.0f, 200.0f, 1.0f, plFloorPlane);
  _moModel.RenderModel(rm);
  EndModelRenderingView();
}
