#include "gf/data/gf_bdat_rsc.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbrs {

enum {
  RscEnDebugName,
  RscEnTypeFamily,
  RscEnTypeGenus,
  RscEnActType,
  RscEnFlyHeight,
  RscEnFldMoveType,
  RscEnMaterial,
  RscEnProxyID,
  RscEnEnRadius,
  RscEnEnRadius2,
  RscEnChestHeight,
  RscEnChestHeight2,
  RscEnBallRadius,
  RscEnBallHeight,
  RscEnCharColli,
  RscEnoffsetID,
  RscEnEyeRot,
  RscEnSearchBaseBone,
  RscEnCenterBone,
  RscEnCamBone,
  RscEnFrontAngle,
  RscEnTurnAngleSmall,
  RscEnTurnAngleBig,
  RscEnUnduration,
  RscEnModel,
  RscEnChrFile,
  RscEnMotion,
  RscEnRefMotion,
  RscEnEffectPack,
  RscEnLoopEffect,
  RscEnSePack,
  RscEnVoice,
  RscEnVoiceEx,
  RscEnClipEvent,
  RscEnComp_Eff,
  RscEnComp_Se,
  RscEnComp_Vo,
  RscEnFlagNoEcSkip,
  RscEnFlagNoEcSkipFlag,
  RscEnFlagMap,
  RscEnFlagMapFlag,
  RscEnFlagEvt,
  RscEnFlagEvtFlag,
  RscEnFlagNoWinVo,
  RscEnFlagNoWinVoFlag,
  RscEnFlagBait,
  RscEnFlagBaitFlag,
  RscEnFlagUseSearchBone,
  RscEnFlagUseSearchBoneFlag,
  RscEnFlagNoVanish,
  RscEnFlagNoVanishFlag,
  RscEnFlagNoCamera,
  RscEnFlagNoCameraFlag,
  RscEnFlagWeaponDrawDisp,
  RscEnFlagWeaponDrawDispFlag,
  RscEnFlagJoinAll,
  RscEnFlagJoinAllFlag,
  RscEnFlagDeathMotion,
  RscEnFlagDeathMotionFlag,
  RscEnWeaponNum1,
  RscEnWeaponNum2,
  RscEnWeaponNum3,
  RscEnWeaponNum4,
  RscEnWeaponNum5,
  RscEnMemorySlot,
  RscEnRace,
  RscEnDrType,
  RscEnGoldDivideRev,
  RscEnFootStep,
  RscEnFootStepEffect,
  RscEnRotateX,
  RscEnRotateY,
  RscEnRotateZ,
  RscEnRotateDeg,
  RscEnRotEffScale,
  RscEnExtraParts1,
  RscEnExtraParts2,
  RscEnExtraParts3,
  RscEnExtraParts4,
  RscEnDeadSeNum,
  RscEnRotateBone,
  RscEnGenusNAME,
  RscEnGenusCAPTION,
  RscEnGenusFlaggimmicktype,
  RscEnGenusFlaggimmicktypeFlag,
  RscEnUndFlagUndX,
  RscEnUndFlagUndXFlag,
  RscEnUndFlagUndZ,
  RscEnUndFlagUndZFlag,
  RscEnUndUndMinX,
  RscEnUndUndMaxX,
  RscEnUndUndMinZ,
  RscEnUndUndMaxZ,
  RscEnUndUndDeg,
  RscNpcListModel,
  RscNpcListMotion,
  RscNpcListAddMotion,
  RscNpcListComp_Eff,
  RscNpcListCollisionId,
  RscNpcListSE,
  RscNpcListSeEnv,
  RscNpcListRace,
  RscNpcListFootStep,
  RscNpcListFootStepEffect,
  RscNpcListRoots,
  RscNpcListGender,
  RscNpcListName,
  RscNpcListOffsetID,
  RscNpcListEyeRot,
  RscNpcListExtraParts1,
  RscNpcListExtraParts2,
  RscNpcListExtraParts3,
  RscNpcListExtraParts4,
  RscNpcListExtraParts5,
  RscNpcListExtraParts6,
  RscNpcListScale,
  RscNpcListEventAsset,
  RscMobListModel,
  RscMobListMotion,
  RscMobListAddMotion,
  RscMobListComp_Eff,
  RscMobListCollisionId,
  RscMobListSE,
  RscMobListSeEnv,
  RscMobListRace,
  RscMobListFootStep,
  RscMobListFootStepEffect,
  RscMobListOffsetID,
  RscMobListExtraParts1,
  RscMobListExtraParts2,
  RscMobListExtraParts3,
  RscMobListExtraParts4,
  RscMobListExtraParts5,
  RscMobListExtraParts6,
  RSC_MapObjListModel,
  RSC_MapObjListMotion,
  RSC_MapObjListComp_Eff,
  RSC_MapObjListSE,
  RSC_MapObjListSeEnv,
  RSC_MapObjListflagBigObj,
  RSC_MapObjListflagBigObjFlag,
  RSC_MapObjListExtraParts1,
  RSC_TboxListModel,
  RSC_TboxListMotion,
  RSC_PcWpnModel,
  RSC_PcWpnMotion,
  RSC_PcWpnMenuImageID,
  RSC_PcWpnMountWpn01rIn,
  RSC_PcWpnMountWpn01rOut,
  RSC_PcWpnMountWpn02rIn,
  RSC_PcWpnMountWpn02rOut,
  RSC_PcWpnMountWpn03rIn,
  RSC_PcWpnMountWpn03rOut,
  RSC_PcWpnMountWpn03lIn,
  RSC_PcWpnMountWpn03lOut,
  RSC_PcWpnMountWpn04rIn,
  RSC_PcWpnMountWpn04rOut,
  RSC_PcWpnMountWpn05rIn,
  RSC_PcWpnMountWpn05rOut,
  RSC_PcWpnMountWpn05lIn,
  RSC_PcWpnMountWpn05lOut,
  RSC_PcWpnMountWpn06rIn,
  RSC_PcWpnMountWpn06rOut,
  RSC_PcWpnMountWpn07rIn,
  RSC_PcWpnMountWpn07rOut,
  RSC_PcWpnMountWpn07lIn,
  RSC_PcWpnMountWpn07lOut,
  RSC_PcWpnMountWpn08rIn,
  RSC_PcWpnMountWpn08rOut,
  RSC_PcWpnMountWpn09rIn,
  RSC_PcWpnMountWpn09rOut,
  RSC_PcWpnMountWpn09lIn,
  RSC_PcWpnMountWpn09lOut,
  RSC_PcWpnMountWpn10rIn,
  RSC_PcWpnMountWpn10rOut,
  RSC_PcWpnMountWpn10lIn,
  RSC_PcWpnMountWpn10lOut,
  RSC_PcWpnMountWpn11rIn,
  RSC_PcWpnMountWpn11rOut,
  RSC_PcWpnMountWpn12rIn,
  RSC_PcWpnMountWpn12rOut,
  RSC_PcWpnMountWpn12lIn,
  RSC_PcWpnMountWpn12lOut,
  RSC_PcWpnMountWpn13rIn,
  RSC_PcWpnMountWpn13rOut,
  RSC_PcWpnMountWpn14rIn,
  RSC_PcWpnMountWpn14rOut,
  RSC_PcWpnMountWpn15rIn,
  RSC_PcWpnMountWpn15rOut,
  RSC_PcWpnMountWpn16rIn,
  RSC_PcWpnMountWpn16rOut,
  RSC_PcWpnMountWpn16lIn,
  RSC_PcWpnMountWpn16lOut,
  RSC_PcWpnMountWpn17rIn,
  RSC_PcWpnMountWpn17rOut,
  RSC_PcWpnMountWpn18rIn,
  RSC_PcWpnMountWpn18rOut,
  RSC_PcWpnMountWpn19rIn,
  RSC_PcWpnMountWpn19rOut,
  RSC_PcWpnMountWpn20rIn,
  RSC_PcWpnMountWpn20rOut,
  RSC_PcWpnMountWpn20lIn,
  RSC_PcWpnMountWpn20lOut,
  RSC_PcWpnMountWpn21rIn,
  RSC_PcWpnMountWpn21rOut,
  RSC_PcWpnMountWpn22rIn,
  RSC_PcWpnMountWpn22rOut,
  RSC_PcWpnMountWpn22lIn,
  RSC_PcWpnMountWpn22lOut,
  RSC_PcWpnMountWpn23rIn,
  RSC_PcWpnMountWpn23rOut,
  RSC_PcWpnMountWpn23lIn,
  RSC_PcWpnMountWpn23lOut,
  RSC_PcWpnMountWpn24rIn,
  RSC_PcWpnMountWpn24rOut,
  RSC_PcWpnMountWpn24lIn,
  RSC_PcWpnMountWpn24lOut,
  RSC_PcWpnMountWpn25rIn,
  RSC_PcWpnMountWpn25rOut,
  RSC_PcWpnMountWpn25lIn,
  RSC_PcWpnMountWpn25lOut,
  RSC_PcWpnMountWpn26rIn,
  RSC_PcWpnMountWpn26rOut,
  RSC_PcWpnMountWpn26lIn,
  RSC_PcWpnMountWpn26lOut,
  RscEnWpnModel,
  RscEnWpnScale,
  RscEnWpnMotion,
  RscEnWpnMtpInChara,
  RscEnWpnMtpInWpn,
  RscEnWpnMtpOutChara,
  RscEnWpnMtpOutWpn,
  RscNpcWpnModel,
  RscNpcWpnMotion,
  DriverParamExtMountNpc,
  DriverParamExtMountBone,
  DriverParamExtMountCond,
  VoiceTableDriver1,
  VoiceTableDriver2,
  VoiceTableDriver3,
  VoiceTableDriver4,
  VoiceTableDriver5,
  VoiceTableDriver6,
  VoiceTableBladeBlade1,
  VoiceTableBladeBlade2,
  VoiceTableBladeBlade3,
  VoiceTableBladeBlade4,
  VoiceTableBladeBlade5,
  VoiceTableBladeBlade6,
  VoiceTableBladeBlade7,
  VoiceTableBladeBlade8,
  VoiceTableBladeBlade9,
  VoiceTableBladeBlade10,
  VoiceTableBladeBlade11,
  VoiceTableRareRareBlade1,
  VoiceTableRareRareBlade2,
  VoiceTableRareRareBlade3,
  VoiceTableRareRareBlade4,
  VoiceTableRareRareBlade5,
  VoiceTableRareRareBlade6,
  VoiceTableRareRareBlade7,
  VoiceTableRareRareBlade8,
  VoiceTableRareRareBlade9,
  VoiceTableRareRareBlade10,
  VoiceTableRareRareBlade11,
  VoiceTableRareRareBlade12,
  VoiceTableRareRareBlade13,
  VoiceTableRareRareBlade14,
  VoiceTableRareRareBlade15,
  VoiceTableRareRareBlade16,
  VoiceTableRareRareBlade17,
  VoiceTableRareRareBlade18,
  VoiceTableRareRareBlade19,
  VoiceTableRareRareBlade20,
  VoiceTableRareRareBlade21,
  VoiceTableRareRareBlade22,
  VoiceTableRareRareBlade23,
  VoiceTableRareRareBlade24,
  VoiceTableRareRareBlade25,
  VoiceTableRareRareBlade26,
  VoiceTableRareRareBlade27,
  VoiceTableRareRareBlade28,
  VoiceTableRareRareBlade29,
  VoiceTableRareRareBlade30,
  VoiceTableRareRareBlade31,
  VoiceTableRareRareBlade32,
  VoiceTableRareRareBlade33,
  VoiceTableRareRareBlade34,
  VoiceTableRareRareBlade35,
  VoiceTableRareRareBlade36,
  VoiceTableRareRareBlade37,
  VoiceTableCommonCommonBlade1,
  VoiceTableCommonCommonBlade2,
  VoiceTableCommonCommonBlade3,
  VoiceTableCommonCommonBlade4,
  VoiceTableCommonCommonBlade5,
  VoiceTableCommonCommonBlade6,
  VoiceTableCommonCommonBlade7,
  VoiceTableCommonCommonBlade8,
  VoiceTableCommonCommonBlade9,
  VoiceTableCommonCommonBlade10,
  VoiceTableCommonCommonBlade11,
  VoiceTableCommonCommonBlade12,
  VoiceTableCommonCommonBlade13,
  VoiceTableCommonCommonBlade14,
  VoiceTableCommonCommonBlade15,
  VoiceTableCommonCommonBlade16,
  VoiceTableCommonCommonBlade17,
  VoiceTableCommonCommonBlade18,
  VoiceTableCommonCommonBlade19,
  VoiceTableCommonCommonBlade20,
  VoiceTableCommonCommonBlade21,
  VoiceTableCommonCommonBlade22,
  VoiceTableCommonCommonBlade23,
  VoiceTableCommonCommonBlade24,
  VoiceTableCommonCommonBlade25,
  VoiceTableCommonCommonBlade26,
  VoiceTableCommonCommonBlade27,
  VoiceTableCommonCommonBlade28,
  VoiceTableCommonCommonBlade29,
  VoiceTableCommonCommonBlade30,
  VoiceTableCommonCommonBlade31,
  VoiceTableCommonCommonBlade32,
  FLD_actorSELOD,
  FLD_actorSEse_type,
  FLD_actorSEseName,
  FLD_actorSEmax_volume_Dist,
  FLD_actorSEmin_volume_Dist,
  FLD_actorSEvolumeMAX,
  FLD_actorSEvolumeMIN,
  FLD_actorSEoffsetX,
  FLD_actorSEoffsetY,
  FLD_actorSEoffsetZ,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initRscEnDebugName(const CBdatWrapper &wrapper) { s_members[RscEnDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getRscEnDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnDebugName], id, 7).valueString;
}

void initRscEnTypeFamily(const CBdatWrapper &wrapper) { s_members[RscEnTypeFamily] = Bdat::getMember(wrapper.unknown00, "TypeFamily"); }

u32 getRscEnTypeFamily(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTypeFamily] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTypeFamily], id, 1).valueU8;
}

void initRscEnTypeGenus(const CBdatWrapper &wrapper) { s_members[RscEnTypeGenus] = Bdat::getMember(wrapper.unknown00, "TypeGenus"); }

u32 getRscEnTypeGenus(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTypeGenus] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTypeGenus], id, 1).valueU8;
}

void initRscEnActType(const CBdatWrapper &wrapper) { s_members[RscEnActType] = Bdat::getMember(wrapper.unknown00, "ActType"); }

u32 getRscEnActType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnActType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnActType], id, 1).valueU8;
}

void initRscEnFlyHeight(const CBdatWrapper &wrapper) { s_members[RscEnFlyHeight] = Bdat::getMember(wrapper.unknown00, "FlyHeight"); }

s32 getRscEnFlyHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlyHeight] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFlyHeight], id, 5).valueS16;
}

void initRscEnFldMoveType(const CBdatWrapper &wrapper) { s_members[RscEnFldMoveType] = Bdat::getMember(wrapper.unknown00, "FldMoveType"); }

u32 getRscEnFldMoveType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFldMoveType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFldMoveType], id, 1).valueU8;
}

void initRscEnMaterial(const CBdatWrapper &wrapper) { s_members[RscEnMaterial] = Bdat::getMember(wrapper.unknown00, "Material"); }

u32 getRscEnMaterial(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnMaterial] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnMaterial], id, 1).valueU8;
}

void initRscEnProxyID(const CBdatWrapper &wrapper) { s_members[RscEnProxyID] = Bdat::getMember(wrapper.unknown00, "ProxyID"); }

u32 getRscEnProxyID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnProxyID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnProxyID], id, 1).valueU8;
}

void initRscEnEnRadius(const CBdatWrapper &wrapper) { s_members[RscEnEnRadius] = Bdat::getMember(wrapper.unknown00, "EnRadius"); }

u32 getRscEnEnRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEnRadius] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnEnRadius], id, 1).valueU8;
}

void initRscEnEnRadius2(const CBdatWrapper &wrapper) { s_members[RscEnEnRadius2] = Bdat::getMember(wrapper.unknown00, "EnRadius2"); }

u32 getRscEnEnRadius2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEnRadius2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnEnRadius2], id, 1).valueU8;
}

void initRscEnChestHeight(const CBdatWrapper &wrapper) { s_members[RscEnChestHeight] = Bdat::getMember(wrapper.unknown00, "ChestHeight"); }

u32 getRscEnChestHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnChestHeight] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnChestHeight], id, 2).valueU16;
}

void initRscEnChestHeight2(const CBdatWrapper &wrapper) { s_members[RscEnChestHeight2] = Bdat::getMember(wrapper.unknown00, "ChestHeight2"); }

u32 getRscEnChestHeight2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnChestHeight2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnChestHeight2], id, 2).valueU16;
}

void initRscEnBallRadius(const CBdatWrapper &wrapper) { s_members[RscEnBallRadius] = Bdat::getMember(wrapper.unknown00, "BallRadius"); }

f32 getRscEnBallRadius(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[RscEnBallRadius] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[RscEnBallRadius], id, 8).valueF32;
  }

  return value;
}

void initRscEnBallHeight(const CBdatWrapper &wrapper) { s_members[RscEnBallHeight] = Bdat::getMember(wrapper.unknown00, "BallHeight"); }

f32 getRscEnBallHeight(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[RscEnBallHeight] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[RscEnBallHeight], id, 8).valueF32;
  }

  return value;
}

void initRscEnCharColli(const CBdatWrapper &wrapper) { s_members[RscEnCharColli] = Bdat::getMember(wrapper.unknown00, "CharColli"); }

f32 getRscEnCharColli(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[RscEnCharColli] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[RscEnCharColli], id, 8).valueF32;
  }

  return value;
}

void initRscEnoffsetID(const CBdatWrapper &wrapper) { s_members[RscEnoffsetID] = Bdat::getMember(wrapper.unknown00, "offsetID"); }

u32 getRscEnoffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnoffsetID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnoffsetID], id, 2).valueU16;
}

void initRscEnEyeRot(const CBdatWrapper &wrapper) { s_members[RscEnEyeRot] = Bdat::getMember(wrapper.unknown00, "EyeRot"); }

u32 getRscEnEyeRot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEyeRot] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnEyeRot], id, 1).valueU8;
}

void initRscEnSearchBaseBone(const CBdatWrapper &wrapper) { s_members[RscEnSearchBaseBone] = Bdat::getMember(wrapper.unknown00, "SearchBaseBone"); }

const char *getRscEnSearchBaseBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnSearchBaseBone] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnSearchBaseBone], id, 7).valueString;
}

void initRscEnCenterBone(const CBdatWrapper &wrapper) { s_members[RscEnCenterBone] = Bdat::getMember(wrapper.unknown00, "CenterBone"); }

const char *getRscEnCenterBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnCenterBone] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnCenterBone], id, 7).valueString;
}

void initRscEnCamBone(const CBdatWrapper &wrapper) { s_members[RscEnCamBone] = Bdat::getMember(wrapper.unknown00, "CamBone"); }

const char *getRscEnCamBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnCamBone] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnCamBone], id, 7).valueString;
}

void initRscEnFrontAngle(const CBdatWrapper &wrapper) { s_members[RscEnFrontAngle] = Bdat::getMember(wrapper.unknown00, "FrontAngle"); }

u32 getRscEnFrontAngle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFrontAngle] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFrontAngle], id, 1).valueU8;
}

void initRscEnTurnAngleSmall(const CBdatWrapper &wrapper) { s_members[RscEnTurnAngleSmall] = Bdat::getMember(wrapper.unknown00, "TurnAngleSmall"); }

u32 getRscEnTurnAngleSmall(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTurnAngleSmall] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTurnAngleSmall], id, 1).valueU8;
}

void initRscEnTurnAngleBig(const CBdatWrapper &wrapper) { s_members[RscEnTurnAngleBig] = Bdat::getMember(wrapper.unknown00, "TurnAngleBig"); }

u32 getRscEnTurnAngleBig(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTurnAngleBig] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTurnAngleBig], id, 1).valueU8;
}

void initRscEnUnduration(const CBdatWrapper &wrapper) { s_members[RscEnUnduration] = Bdat::getMember(wrapper.unknown00, "Unduration"); }

u32 getRscEnUnduration(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUnduration] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUnduration], id, 1).valueU8;
}

void initRscEnModel(const CBdatWrapper &wrapper) { s_members[RscEnModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRscEnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnModel], id, 7).valueString;
}

void initRscEnChrFile(const CBdatWrapper &wrapper) { s_members[RscEnChrFile] = Bdat::getMember(wrapper.unknown00, "ChrFile"); }

const char *getRscEnChrFile(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnChrFile] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnChrFile], id, 7).valueString;
}

void initRscEnMotion(const CBdatWrapper &wrapper) { s_members[RscEnMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRscEnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnMotion], id, 7).valueString;
}

void initRscEnRefMotion(const CBdatWrapper &wrapper) { s_members[RscEnRefMotion] = Bdat::getMember(wrapper.unknown00, "RefMotion"); }

const char *getRscEnRefMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRefMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnRefMotion], id, 7).valueString;
}

void initRscEnEffectPack(const CBdatWrapper &wrapper) { s_members[RscEnEffectPack] = Bdat::getMember(wrapper.unknown00, "EffectPack"); }

const char *getRscEnEffectPack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEffectPack] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnEffectPack], id, 7).valueString;
}

void initRscEnLoopEffect(const CBdatWrapper &wrapper) { s_members[RscEnLoopEffect] = Bdat::getMember(wrapper.unknown00, "LoopEffect"); }

const char *getRscEnLoopEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnLoopEffect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnLoopEffect], id, 7).valueString;
}

void initRscEnSePack(const CBdatWrapper &wrapper) { s_members[RscEnSePack] = Bdat::getMember(wrapper.unknown00, "SePack"); }

const char *getRscEnSePack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnSePack] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnSePack], id, 7).valueString;
}

void initRscEnVoice(const CBdatWrapper &wrapper) { s_members[RscEnVoice] = Bdat::getMember(wrapper.unknown00, "Voice"); }

const char *getRscEnVoice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnVoice] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnVoice], id, 7).valueString;
}

void initRscEnVoiceEx(const CBdatWrapper &wrapper) { s_members[RscEnVoiceEx] = Bdat::getMember(wrapper.unknown00, "VoiceEx"); }

u32 getRscEnVoiceEx(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnVoiceEx] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnVoiceEx], id, 1).valueU8;
}

void initRscEnClipEvent(const CBdatWrapper &wrapper) { s_members[RscEnClipEvent] = Bdat::getMember(wrapper.unknown00, "ClipEvent"); }

const char *getRscEnClipEvent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnClipEvent] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnClipEvent], id, 7).valueString;
}

void initRscEnComp_Eff(const CBdatWrapper &wrapper) { s_members[RscEnComp_Eff] = Bdat::getMember(wrapper.unknown00, "Comp_Eff"); }

const char *getRscEnComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnComp_Eff], id, 7).valueString;
}

void initRscEnComp_Se(const CBdatWrapper &wrapper) { s_members[RscEnComp_Se] = Bdat::getMember(wrapper.unknown00, "Comp_Se"); }

const char *getRscEnComp_Se(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnComp_Se] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnComp_Se], id, 7).valueString;
}

void initRscEnComp_Vo(const CBdatWrapper &wrapper) { s_members[RscEnComp_Vo] = Bdat::getMember(wrapper.unknown00, "Comp_Vo"); }

const char *getRscEnComp_Vo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnComp_Vo] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnComp_Vo], id, 7).valueString;
}

void initRscEnFlagNoEcSkip(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoEcSkip] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagNoEcSkipFlag] = Bdat::getMember(wrapper.unknown00, "NoEcSkip");
}

bool isRscEnFlagNoEcSkip(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoEcSkip] == nullptr || s_members[RscEnFlagNoEcSkipFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoEcSkip], id, s_members[RscEnFlagNoEcSkipFlag]) != 0;
}

void initRscEnFlagMap(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagMap] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagMapFlag] = Bdat::getMember(wrapper.unknown00, "Map");
}

bool isRscEnFlagMap(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagMap] == nullptr || s_members[RscEnFlagMapFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagMap], id, s_members[RscEnFlagMapFlag]) != 0;
}

void initRscEnFlagEvt(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagEvt] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagEvtFlag] = Bdat::getMember(wrapper.unknown00, "Evt");
}

bool isRscEnFlagEvt(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagEvt] == nullptr || s_members[RscEnFlagEvtFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagEvt], id, s_members[RscEnFlagEvtFlag]) != 0;
}

void initRscEnFlagNoWinVo(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoWinVo] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagNoWinVoFlag] = Bdat::getMember(wrapper.unknown00, "NoWinVo");
}

bool isRscEnFlagNoWinVo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoWinVo] == nullptr || s_members[RscEnFlagNoWinVoFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoWinVo], id, s_members[RscEnFlagNoWinVoFlag]) != 0;
}

void initRscEnFlagBait(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagBait] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagBaitFlag] = Bdat::getMember(wrapper.unknown00, "Bait");
}

bool isRscEnFlagBait(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagBait] == nullptr || s_members[RscEnFlagBaitFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagBait], id, s_members[RscEnFlagBaitFlag]) != 0;
}

void initRscEnFlagUseSearchBone(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagUseSearchBone] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagUseSearchBoneFlag] = Bdat::getMember(wrapper.unknown00, "UseSearchBone");
}

bool isRscEnFlagUseSearchBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagUseSearchBone] == nullptr || s_members[RscEnFlagUseSearchBoneFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagUseSearchBone], id, s_members[RscEnFlagUseSearchBoneFlag]) != 0;
}

void initRscEnFlagNoVanish(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoVanish] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagNoVanishFlag] = Bdat::getMember(wrapper.unknown00, "NoVanish");
}

bool isRscEnFlagNoVanish(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoVanish] == nullptr || s_members[RscEnFlagNoVanishFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoVanish], id, s_members[RscEnFlagNoVanishFlag]) != 0;
}

void initRscEnFlagNoCamera(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoCamera] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagNoCameraFlag] = Bdat::getMember(wrapper.unknown00, "NoCamera");
}

bool isRscEnFlagNoCamera(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoCamera] == nullptr || s_members[RscEnFlagNoCameraFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoCamera], id, s_members[RscEnFlagNoCameraFlag]) != 0;
}

void initRscEnFlagWeaponDrawDisp(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagWeaponDrawDisp] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagWeaponDrawDispFlag] = Bdat::getMember(wrapper.unknown00, "WeaponDrawDisp");
}

bool isRscEnFlagWeaponDrawDisp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagWeaponDrawDisp] == nullptr || s_members[RscEnFlagWeaponDrawDispFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagWeaponDrawDisp], id, s_members[RscEnFlagWeaponDrawDispFlag]) != 0;
}

void initRscEnFlagJoinAll(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagJoinAll] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagJoinAllFlag] = Bdat::getMember(wrapper.unknown00, "JoinAll");
}

bool isRscEnFlagJoinAll(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagJoinAll] == nullptr || s_members[RscEnFlagJoinAllFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagJoinAll], id, s_members[RscEnFlagJoinAllFlag]) != 0;
}

void initRscEnFlagDeathMotion(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagDeathMotion] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnFlagDeathMotionFlag] = Bdat::getMember(wrapper.unknown00, "DeathMotion");
}

bool isRscEnFlagDeathMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagDeathMotion] == nullptr || s_members[RscEnFlagDeathMotionFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagDeathMotion], id, s_members[RscEnFlagDeathMotionFlag]) != 0;
}

void initRscEnWeaponNum1(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum1] = Bdat::getMember(wrapper.unknown00, "WeaponNum1"); }

u32 getRscEnWeaponNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum1], id, 2).valueU16;
}

void initRscEnWeaponNum2(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum2] = Bdat::getMember(wrapper.unknown00, "WeaponNum2"); }

u32 getRscEnWeaponNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum2], id, 2).valueU16;
}

void initRscEnWeaponNum3(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum3] = Bdat::getMember(wrapper.unknown00, "WeaponNum3"); }

u32 getRscEnWeaponNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum3], id, 2).valueU16;
}

void initRscEnWeaponNum4(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum4] = Bdat::getMember(wrapper.unknown00, "WeaponNum4"); }

u32 getRscEnWeaponNum4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum4], id, 2).valueU16;
}

void initRscEnWeaponNum5(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum5] = Bdat::getMember(wrapper.unknown00, "WeaponNum5"); }

u32 getRscEnWeaponNum5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum5], id, 2).valueU16;
}

void initRscEnMemorySlot(const CBdatWrapper &wrapper) { s_members[RscEnMemorySlot] = Bdat::getMember(wrapper.unknown00, "MemorySlot"); }

u32 getRscEnMemorySlot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnMemorySlot] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnMemorySlot], id, 1).valueU8;
}

void initRscEnRace(const CBdatWrapper &wrapper) { s_members[RscEnRace] = Bdat::getMember(wrapper.unknown00, "Race"); }

u32 getRscEnRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRace] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRace], id, 1).valueU8;
}

void initRscEnDrType(const CBdatWrapper &wrapper) { s_members[RscEnDrType] = Bdat::getMember(wrapper.unknown00, "DrType"); }

u32 getRscEnDrType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnDrType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnDrType], id, 1).valueU8;
}

void initRscEnGoldDivideRev(const CBdatWrapper &wrapper) { s_members[RscEnGoldDivideRev] = Bdat::getMember(wrapper.unknown00, "GoldDivideRev"); }

s32 getRscEnGoldDivideRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGoldDivideRev] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnGoldDivideRev], id, 4).valueS8;
}

void initRscEnFootStep(const CBdatWrapper &wrapper) { s_members[RscEnFootStep] = Bdat::getMember(wrapper.unknown00, "FootStep"); }

u32 getRscEnFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFootStep] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFootStep], id, 1).valueU8;
}

void initRscEnFootStepEffect(const CBdatWrapper &wrapper) { s_members[RscEnFootStepEffect] = Bdat::getMember(wrapper.unknown00, "FootStepEffect"); }

u32 getRscEnFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFootStepEffect], id, 1).valueU8;
}

void initRscEnRotateX(const CBdatWrapper &wrapper) { s_members[RscEnRotateX] = Bdat::getMember(wrapper.unknown00, "RotateX"); }

s32 getRscEnRotateX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateX] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateX], id, 4).valueS8;
}

void initRscEnRotateY(const CBdatWrapper &wrapper) { s_members[RscEnRotateY] = Bdat::getMember(wrapper.unknown00, "RotateY"); }

s32 getRscEnRotateY(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateY] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateY], id, 4).valueS8;
}

void initRscEnRotateZ(const CBdatWrapper &wrapper) { s_members[RscEnRotateZ] = Bdat::getMember(wrapper.unknown00, "RotateZ"); }

s32 getRscEnRotateZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateZ] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateZ], id, 4).valueS8;
}

void initRscEnRotateDeg(const CBdatWrapper &wrapper) { s_members[RscEnRotateDeg] = Bdat::getMember(wrapper.unknown00, "RotateDeg"); }

s32 getRscEnRotateDeg(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateDeg] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateDeg], id, 4).valueS8;
}

void initRscEnRotEffScale(const CBdatWrapper &wrapper) { s_members[RscEnRotEffScale] = Bdat::getMember(wrapper.unknown00, "RotEffScale"); }

u32 getRscEnRotEffScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotEffScale] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotEffScale], id, 2).valueU16;
}

void initRscEnExtraParts1(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts1] = Bdat::getMember(wrapper.unknown00, "ExtraParts1"); }

u32 getRscEnExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts1], id, 1).valueU8;
}

void initRscEnExtraParts2(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts2] = Bdat::getMember(wrapper.unknown00, "ExtraParts2"); }

u32 getRscEnExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts2], id, 1).valueU8;
}

void initRscEnExtraParts3(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts3] = Bdat::getMember(wrapper.unknown00, "ExtraParts3"); }

u32 getRscEnExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts3], id, 1).valueU8;
}

void initRscEnExtraParts4(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts4] = Bdat::getMember(wrapper.unknown00, "ExtraParts4"); }

u32 getRscEnExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts4], id, 1).valueU8;
}

void initRscEnDeadSeNum(const CBdatWrapper &wrapper) { s_members[RscEnDeadSeNum] = Bdat::getMember(wrapper.unknown00, "DeadSeNum"); }

u32 getRscEnDeadSeNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnDeadSeNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnDeadSeNum], id, 1).valueU8;
}

void initRscEnRotateBone(const CBdatWrapper &wrapper) { s_members[RscEnRotateBone] = Bdat::getMember(wrapper.unknown00, "RotateBone"); }

const char *getRscEnRotateBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateBone] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnRotateBone], id, 7).valueString;
}

void initRscEnGenusNAME(const CBdatWrapper &wrapper) { s_members[RscEnGenusNAME] = Bdat::getMember(wrapper.unknown00, "NAME"); }

u32 getRscEnGenusNAME(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGenusNAME] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnGenusNAME], id, 1).valueU8;
}

void initRscEnGenusCAPTION(const CBdatWrapper &wrapper) { s_members[RscEnGenusCAPTION] = Bdat::getMember(wrapper.unknown00, "CAPTION"); }

u32 getRscEnGenusCAPTION(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGenusCAPTION] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnGenusCAPTION], id, 1).valueU8;
}

void initRscEnGenusFlaggimmicktype(const CBdatWrapper &wrapper) {
  s_members[RscEnGenusFlaggimmicktype] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnGenusFlaggimmicktypeFlag] = Bdat::getMember(wrapper.unknown00, "gimmicktype");
}

bool isRscEnGenusFlaggimmicktype(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGenusFlaggimmicktype] == nullptr || s_members[RscEnGenusFlaggimmicktypeFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnGenusFlaggimmicktype], id, s_members[RscEnGenusFlaggimmicktypeFlag]) != 0;
}

void initRscEnUndFlagUndX(const CBdatWrapper &wrapper) {
  s_members[RscEnUndFlagUndX] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnUndFlagUndXFlag] = Bdat::getMember(wrapper.unknown00, "UndX");
}

bool isRscEnUndFlagUndX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndFlagUndX] == nullptr || s_members[RscEnUndFlagUndXFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnUndFlagUndX], id, s_members[RscEnUndFlagUndXFlag]) != 0;
}

void initRscEnUndFlagUndZ(const CBdatWrapper &wrapper) {
  s_members[RscEnUndFlagUndZ] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[RscEnUndFlagUndZFlag] = Bdat::getMember(wrapper.unknown00, "UndZ");
}

bool isRscEnUndFlagUndZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndFlagUndZ] == nullptr || s_members[RscEnUndFlagUndZFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnUndFlagUndZ], id, s_members[RscEnUndFlagUndZFlag]) != 0;
}

void initRscEnUndUndMinX(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMinX] = Bdat::getMember(wrapper.unknown00, "UndMinX"); }

s32 getRscEnUndUndMinX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMinX] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMinX], id, 4).valueS8;
}

void initRscEnUndUndMaxX(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMaxX] = Bdat::getMember(wrapper.unknown00, "UndMaxX"); }

s32 getRscEnUndUndMaxX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMaxX] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMaxX], id, 4).valueS8;
}

void initRscEnUndUndMinZ(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMinZ] = Bdat::getMember(wrapper.unknown00, "UndMinZ"); }

s32 getRscEnUndUndMinZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMinZ] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMinZ], id, 4).valueS8;
}

void initRscEnUndUndMaxZ(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMaxZ] = Bdat::getMember(wrapper.unknown00, "UndMaxZ"); }

s32 getRscEnUndUndMaxZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMaxZ] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMaxZ], id, 4).valueS8;
}

void initRscEnUndUndDeg(const CBdatWrapper &wrapper) { s_members[RscEnUndUndDeg] = Bdat::getMember(wrapper.unknown00, "UndDeg"); }

u32 getRscEnUndUndDeg(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndDeg] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndDeg], id, 1).valueU8;
}

void initRscNpcListModel(const CBdatWrapper &wrapper) { s_members[RscNpcListModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRscNpcListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListModel], id, 7).valueString;
}

void initRscNpcListMotion(const CBdatWrapper &wrapper) { s_members[RscNpcListMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRscNpcListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListMotion], id, 7).valueString;
}

void initRscNpcListAddMotion(const CBdatWrapper &wrapper) { s_members[RscNpcListAddMotion] = Bdat::getMember(wrapper.unknown00, "AddMotion"); }

const char *getRscNpcListAddMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListAddMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListAddMotion], id, 7).valueString;
}

void initRscNpcListComp_Eff(const CBdatWrapper &wrapper) { s_members[RscNpcListComp_Eff] = Bdat::getMember(wrapper.unknown00, "Comp_Eff"); }

const char *getRscNpcListComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListComp_Eff], id, 7).valueString;
}

void initRscNpcListCollisionId(const CBdatWrapper &wrapper) { s_members[RscNpcListCollisionId] = Bdat::getMember(wrapper.unknown00, "CollisionId"); }

u32 getRscNpcListCollisionId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListCollisionId] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListCollisionId], id, 2).valueU16;
}

void initRscNpcListSE(const CBdatWrapper &wrapper) { s_members[RscNpcListSE] = Bdat::getMember(wrapper.unknown00, "SE"); }

const char *getRscNpcListSE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListSE] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListSE], id, 7).valueString;
}

void initRscNpcListSeEnv(const CBdatWrapper &wrapper) { s_members[RscNpcListSeEnv] = Bdat::getMember(wrapper.unknown00, "SeEnv"); }

u32 getRscNpcListSeEnv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListSeEnv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListSeEnv], id, 2).valueU16;
}

void initRscNpcListRace(const CBdatWrapper &wrapper) { s_members[RscNpcListRace] = Bdat::getMember(wrapper.unknown00, "Race"); }

u32 getRscNpcListRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListRace] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListRace], id, 1).valueU8;
}

void initRscNpcListFootStep(const CBdatWrapper &wrapper) { s_members[RscNpcListFootStep] = Bdat::getMember(wrapper.unknown00, "FootStep"); }

u32 getRscNpcListFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListFootStep] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListFootStep], id, 2).valueU16;
}

void initRscNpcListFootStepEffect(const CBdatWrapper &wrapper) { s_members[RscNpcListFootStepEffect] = Bdat::getMember(wrapper.unknown00, "FootStepEffect"); }

u32 getRscNpcListFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListFootStepEffect], id, 1).valueU8;
}

void initRscNpcListRoots(const CBdatWrapper &wrapper) { s_members[RscNpcListRoots] = Bdat::getMember(wrapper.unknown00, "Roots"); }

u32 getRscNpcListRoots(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListRoots] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListRoots], id, 1).valueU8;
}

void initRscNpcListGender(const CBdatWrapper &wrapper) { s_members[RscNpcListGender] = Bdat::getMember(wrapper.unknown00, "Gender"); }

u32 getRscNpcListGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListGender] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListGender], id, 1).valueU8;
}

void initRscNpcListName(const CBdatWrapper &wrapper) { s_members[RscNpcListName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getRscNpcListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListName], id, 2).valueU16;
}

void initRscNpcListOffsetID(const CBdatWrapper &wrapper) { s_members[RscNpcListOffsetID] = Bdat::getMember(wrapper.unknown00, "OffsetID"); }

u32 getRscNpcListOffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListOffsetID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListOffsetID], id, 2).valueU16;
}

void initRscNpcListEyeRot(const CBdatWrapper &wrapper) { s_members[RscNpcListEyeRot] = Bdat::getMember(wrapper.unknown00, "EyeRot"); }

u32 getRscNpcListEyeRot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListEyeRot] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListEyeRot], id, 1).valueU8;
}

void initRscNpcListExtraParts1(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts1] = Bdat::getMember(wrapper.unknown00, "ExtraParts1"); }

u32 getRscNpcListExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts1], id, 1).valueU8;
}

void initRscNpcListExtraParts2(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts2] = Bdat::getMember(wrapper.unknown00, "ExtraParts2"); }

u32 getRscNpcListExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts2], id, 1).valueU8;
}

void initRscNpcListExtraParts3(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts3] = Bdat::getMember(wrapper.unknown00, "ExtraParts3"); }

u32 getRscNpcListExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts3], id, 1).valueU8;
}

void initRscNpcListExtraParts4(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts4] = Bdat::getMember(wrapper.unknown00, "ExtraParts4"); }

u32 getRscNpcListExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts4], id, 1).valueU8;
}

void initRscNpcListExtraParts5(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts5] = Bdat::getMember(wrapper.unknown00, "ExtraParts5"); }

u32 getRscNpcListExtraParts5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts5], id, 1).valueU8;
}

void initRscNpcListExtraParts6(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts6] = Bdat::getMember(wrapper.unknown00, "ExtraParts6"); }

u32 getRscNpcListExtraParts6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts6], id, 1).valueU8;
}

void initRscNpcListScale(const CBdatWrapper &wrapper) { s_members[RscNpcListScale] = Bdat::getMember(wrapper.unknown00, "Scale"); }

u32 getRscNpcListScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListScale] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListScale], id, 2).valueU16;
}

void initRscNpcListEventAsset(const CBdatWrapper &wrapper) { s_members[RscNpcListEventAsset] = Bdat::getMember(wrapper.unknown00, "EventAsset"); }

u32 getRscNpcListEventAsset(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListEventAsset] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListEventAsset], id, 2).valueU16;
}

void initRscMobListModel(const CBdatWrapper &wrapper) { s_members[RscMobListModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRscMobListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListModel], id, 7).valueString;
}

void initRscMobListMotion(const CBdatWrapper &wrapper) { s_members[RscMobListMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRscMobListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListMotion], id, 7).valueString;
}

void initRscMobListAddMotion(const CBdatWrapper &wrapper) { s_members[RscMobListAddMotion] = Bdat::getMember(wrapper.unknown00, "AddMotion"); }

const char *getRscMobListAddMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListAddMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListAddMotion], id, 7).valueString;
}

void initRscMobListComp_Eff(const CBdatWrapper &wrapper) { s_members[RscMobListComp_Eff] = Bdat::getMember(wrapper.unknown00, "Comp_Eff"); }

const char *getRscMobListComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListComp_Eff], id, 7).valueString;
}

void initRscMobListCollisionId(const CBdatWrapper &wrapper) { s_members[RscMobListCollisionId] = Bdat::getMember(wrapper.unknown00, "CollisionId"); }

u32 getRscMobListCollisionId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListCollisionId] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListCollisionId], id, 2).valueU16;
}

void initRscMobListSE(const CBdatWrapper &wrapper) { s_members[RscMobListSE] = Bdat::getMember(wrapper.unknown00, "SE"); }

const char *getRscMobListSE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListSE] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListSE], id, 7).valueString;
}

void initRscMobListSeEnv(const CBdatWrapper &wrapper) { s_members[RscMobListSeEnv] = Bdat::getMember(wrapper.unknown00, "SeEnv"); }

u32 getRscMobListSeEnv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListSeEnv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListSeEnv], id, 2).valueU16;
}

void initRscMobListRace(const CBdatWrapper &wrapper) { s_members[RscMobListRace] = Bdat::getMember(wrapper.unknown00, "Race"); }

u32 getRscMobListRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListRace] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListRace], id, 1).valueU8;
}

void initRscMobListFootStep(const CBdatWrapper &wrapper) { s_members[RscMobListFootStep] = Bdat::getMember(wrapper.unknown00, "FootStep"); }

u32 getRscMobListFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListFootStep] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListFootStep], id, 2).valueU16;
}

void initRscMobListFootStepEffect(const CBdatWrapper &wrapper) { s_members[RscMobListFootStepEffect] = Bdat::getMember(wrapper.unknown00, "FootStepEffect"); }

u32 getRscMobListFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListFootStepEffect], id, 1).valueU8;
}

void initRscMobListOffsetID(const CBdatWrapper &wrapper) { s_members[RscMobListOffsetID] = Bdat::getMember(wrapper.unknown00, "OffsetID"); }

u32 getRscMobListOffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListOffsetID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListOffsetID], id, 2).valueU16;
}

void initRscMobListExtraParts1(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts1] = Bdat::getMember(wrapper.unknown00, "ExtraParts1"); }

u32 getRscMobListExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts1], id, 1).valueU8;
}

void initRscMobListExtraParts2(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts2] = Bdat::getMember(wrapper.unknown00, "ExtraParts2"); }

u32 getRscMobListExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts2], id, 1).valueU8;
}

void initRscMobListExtraParts3(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts3] = Bdat::getMember(wrapper.unknown00, "ExtraParts3"); }

u32 getRscMobListExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts3], id, 1).valueU8;
}

void initRscMobListExtraParts4(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts4] = Bdat::getMember(wrapper.unknown00, "ExtraParts4"); }

u32 getRscMobListExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts4], id, 1).valueU8;
}

void initRscMobListExtraParts5(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts5] = Bdat::getMember(wrapper.unknown00, "ExtraParts5"); }

u32 getRscMobListExtraParts5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts5], id, 1).valueU8;
}

void initRscMobListExtraParts6(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts6] = Bdat::getMember(wrapper.unknown00, "ExtraParts6"); }

u32 getRscMobListExtraParts6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts6], id, 1).valueU8;
}

void initRSC_MapObjListModel(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRSC_MapObjListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListModel], id, 7).valueString;
}

void initRSC_MapObjListMotion(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRSC_MapObjListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListMotion], id, 7).valueString;
}

void initRSC_MapObjListComp_Eff(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListComp_Eff] = Bdat::getMember(wrapper.unknown00, "Comp_Eff"); }

const char *getRSC_MapObjListComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListComp_Eff], id, 7).valueString;
}

void initRSC_MapObjListSE(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListSE] = Bdat::getMember(wrapper.unknown00, "SE"); }

const char *getRSC_MapObjListSE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListSE] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListSE], id, 7).valueString;
}

void initRSC_MapObjListSeEnv(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListSeEnv] = Bdat::getMember(wrapper.unknown00, "SeEnv"); }

u32 getRSC_MapObjListSeEnv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListSeEnv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListSeEnv], id, 2).valueU16;
}

void initRSC_MapObjListflagBigObj(const CBdatWrapper &wrapper) {
  s_members[RSC_MapObjListflagBigObj] = Bdat::getMember(wrapper.unknown00, "flag");
  s_members[RSC_MapObjListflagBigObjFlag] = Bdat::getMember(wrapper.unknown00, "BigObj");
}

bool isRSC_MapObjListflagBigObj(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListflagBigObj] == nullptr || s_members[RSC_MapObjListflagBigObjFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RSC_MapObjListflagBigObj], id, s_members[RSC_MapObjListflagBigObjFlag]) != 0;
}

void initRSC_MapObjListExtraParts1(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListExtraParts1] = Bdat::getMember(wrapper.unknown00, "ExtraParts1"); }

u32 getRSC_MapObjListExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListExtraParts1], id, 1).valueU8;
}

void initRSC_TboxListModel(const CBdatWrapper &wrapper) { s_members[RSC_TboxListModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRSC_TboxListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_TboxListModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_TboxListModel], id, 7).valueString;
}

void initRSC_TboxListMotion(const CBdatWrapper &wrapper) { s_members[RSC_TboxListMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRSC_TboxListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_TboxListMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_TboxListMotion], id, 7).valueString;
}

void initRSC_PcWpnModel(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRSC_PcWpnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnModel], id, 7).valueString;
}

void initRSC_PcWpnMotion(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRSC_PcWpnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMotion], id, 7).valueString;
}

void initRSC_PcWpnMenuImageID(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMenuImageID] = Bdat::getMember(wrapper.unknown00, "MenuImageID"); }

u32 getRSC_PcWpnMenuImageID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMenuImageID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMenuImageID], id, 2).valueU16;
}

void initRSC_PcWpnMountWpn01rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn01rIn] = Bdat::getMember(wrapper.unknown00, "Wpn01rIn"); }

const char *getRSC_PcWpnMountWpn01rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn01rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn01rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn01rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn01rOut] = Bdat::getMember(wrapper.unknown00, "Wpn01rOut"); }

const char *getRSC_PcWpnMountWpn01rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn01rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn01rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn02rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn02rIn] = Bdat::getMember(wrapper.unknown00, "Wpn02rIn"); }

const char *getRSC_PcWpnMountWpn02rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn02rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn02rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn02rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn02rOut] = Bdat::getMember(wrapper.unknown00, "Wpn02rOut"); }

const char *getRSC_PcWpnMountWpn02rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn02rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn02rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03rIn] = Bdat::getMember(wrapper.unknown00, "Wpn03rIn"); }

const char *getRSC_PcWpnMountWpn03rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03rOut] = Bdat::getMember(wrapper.unknown00, "Wpn03rOut"); }

const char *getRSC_PcWpnMountWpn03rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03lIn] = Bdat::getMember(wrapper.unknown00, "Wpn03lIn"); }

const char *getRSC_PcWpnMountWpn03lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03lOut] = Bdat::getMember(wrapper.unknown00, "Wpn03lOut"); }

const char *getRSC_PcWpnMountWpn03lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn04rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn04rIn] = Bdat::getMember(wrapper.unknown00, "Wpn04rIn"); }

const char *getRSC_PcWpnMountWpn04rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn04rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn04rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn04rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn04rOut] = Bdat::getMember(wrapper.unknown00, "Wpn04rOut"); }

const char *getRSC_PcWpnMountWpn04rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn04rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn04rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05rIn] = Bdat::getMember(wrapper.unknown00, "Wpn05rIn"); }

const char *getRSC_PcWpnMountWpn05rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05rOut] = Bdat::getMember(wrapper.unknown00, "Wpn05rOut"); }

const char *getRSC_PcWpnMountWpn05rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05lIn] = Bdat::getMember(wrapper.unknown00, "Wpn05lIn"); }

const char *getRSC_PcWpnMountWpn05lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05lOut] = Bdat::getMember(wrapper.unknown00, "Wpn05lOut"); }

const char *getRSC_PcWpnMountWpn05lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn06rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn06rIn] = Bdat::getMember(wrapper.unknown00, "Wpn06rIn"); }

const char *getRSC_PcWpnMountWpn06rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn06rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn06rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn06rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn06rOut] = Bdat::getMember(wrapper.unknown00, "Wpn06rOut"); }

const char *getRSC_PcWpnMountWpn06rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn06rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn06rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07rIn] = Bdat::getMember(wrapper.unknown00, "Wpn07rIn"); }

const char *getRSC_PcWpnMountWpn07rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07rOut] = Bdat::getMember(wrapper.unknown00, "Wpn07rOut"); }

const char *getRSC_PcWpnMountWpn07rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07lIn] = Bdat::getMember(wrapper.unknown00, "Wpn07lIn"); }

const char *getRSC_PcWpnMountWpn07lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07lOut] = Bdat::getMember(wrapper.unknown00, "Wpn07lOut"); }

const char *getRSC_PcWpnMountWpn07lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn08rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn08rIn] = Bdat::getMember(wrapper.unknown00, "Wpn08rIn"); }

const char *getRSC_PcWpnMountWpn08rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn08rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn08rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn08rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn08rOut] = Bdat::getMember(wrapper.unknown00, "Wpn08rOut"); }

const char *getRSC_PcWpnMountWpn08rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn08rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn08rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09rIn] = Bdat::getMember(wrapper.unknown00, "Wpn09rIn"); }

const char *getRSC_PcWpnMountWpn09rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09rOut] = Bdat::getMember(wrapper.unknown00, "Wpn09rOut"); }

const char *getRSC_PcWpnMountWpn09rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09lIn] = Bdat::getMember(wrapper.unknown00, "Wpn09lIn"); }

const char *getRSC_PcWpnMountWpn09lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09lOut] = Bdat::getMember(wrapper.unknown00, "Wpn09lOut"); }

const char *getRSC_PcWpnMountWpn09lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10rIn] = Bdat::getMember(wrapper.unknown00, "Wpn10rIn"); }

const char *getRSC_PcWpnMountWpn10rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10rOut] = Bdat::getMember(wrapper.unknown00, "Wpn10rOut"); }

const char *getRSC_PcWpnMountWpn10rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10lIn] = Bdat::getMember(wrapper.unknown00, "Wpn10lIn"); }

const char *getRSC_PcWpnMountWpn10lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10lOut] = Bdat::getMember(wrapper.unknown00, "Wpn10lOut"); }

const char *getRSC_PcWpnMountWpn10lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn11rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn11rIn] = Bdat::getMember(wrapper.unknown00, "Wpn11rIn"); }

const char *getRSC_PcWpnMountWpn11rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn11rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn11rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn11rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn11rOut] = Bdat::getMember(wrapper.unknown00, "Wpn11rOut"); }

const char *getRSC_PcWpnMountWpn11rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn11rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn11rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12rIn] = Bdat::getMember(wrapper.unknown00, "Wpn12rIn"); }

const char *getRSC_PcWpnMountWpn12rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12rOut] = Bdat::getMember(wrapper.unknown00, "Wpn12rOut"); }

const char *getRSC_PcWpnMountWpn12rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12lIn] = Bdat::getMember(wrapper.unknown00, "Wpn12lIn"); }

const char *getRSC_PcWpnMountWpn12lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12lOut] = Bdat::getMember(wrapper.unknown00, "Wpn12lOut"); }

const char *getRSC_PcWpnMountWpn12lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn13rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn13rIn] = Bdat::getMember(wrapper.unknown00, "Wpn13rIn"); }

const char *getRSC_PcWpnMountWpn13rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn13rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn13rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn13rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn13rOut] = Bdat::getMember(wrapper.unknown00, "Wpn13rOut"); }

const char *getRSC_PcWpnMountWpn13rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn13rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn13rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn14rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn14rIn] = Bdat::getMember(wrapper.unknown00, "Wpn14rIn"); }

const char *getRSC_PcWpnMountWpn14rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn14rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn14rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn14rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn14rOut] = Bdat::getMember(wrapper.unknown00, "Wpn14rOut"); }

const char *getRSC_PcWpnMountWpn14rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn14rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn14rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn15rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn15rIn] = Bdat::getMember(wrapper.unknown00, "Wpn15rIn"); }

const char *getRSC_PcWpnMountWpn15rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn15rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn15rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn15rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn15rOut] = Bdat::getMember(wrapper.unknown00, "Wpn15rOut"); }

const char *getRSC_PcWpnMountWpn15rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn15rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn15rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16rIn] = Bdat::getMember(wrapper.unknown00, "Wpn16rIn"); }

const char *getRSC_PcWpnMountWpn16rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16rOut] = Bdat::getMember(wrapper.unknown00, "Wpn16rOut"); }

const char *getRSC_PcWpnMountWpn16rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16lIn] = Bdat::getMember(wrapper.unknown00, "Wpn16lIn"); }

const char *getRSC_PcWpnMountWpn16lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16lOut] = Bdat::getMember(wrapper.unknown00, "Wpn16lOut"); }

const char *getRSC_PcWpnMountWpn16lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn17rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn17rIn] = Bdat::getMember(wrapper.unknown00, "Wpn17rIn"); }

const char *getRSC_PcWpnMountWpn17rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn17rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn17rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn17rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn17rOut] = Bdat::getMember(wrapper.unknown00, "Wpn17rOut"); }

const char *getRSC_PcWpnMountWpn17rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn17rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn17rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn18rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn18rIn] = Bdat::getMember(wrapper.unknown00, "Wpn18rIn"); }

const char *getRSC_PcWpnMountWpn18rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn18rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn18rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn18rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn18rOut] = Bdat::getMember(wrapper.unknown00, "Wpn18rOut"); }

const char *getRSC_PcWpnMountWpn18rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn18rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn18rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn19rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn19rIn] = Bdat::getMember(wrapper.unknown00, "Wpn19rIn"); }

const char *getRSC_PcWpnMountWpn19rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn19rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn19rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn19rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn19rOut] = Bdat::getMember(wrapper.unknown00, "Wpn19rOut"); }

const char *getRSC_PcWpnMountWpn19rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn19rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn19rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20rIn] = Bdat::getMember(wrapper.unknown00, "Wpn20rIn"); }

const char *getRSC_PcWpnMountWpn20rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20rOut] = Bdat::getMember(wrapper.unknown00, "Wpn20rOut"); }

const char *getRSC_PcWpnMountWpn20rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20lIn] = Bdat::getMember(wrapper.unknown00, "Wpn20lIn"); }

const char *getRSC_PcWpnMountWpn20lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20lOut] = Bdat::getMember(wrapper.unknown00, "Wpn20lOut"); }

const char *getRSC_PcWpnMountWpn20lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn21rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn21rIn] = Bdat::getMember(wrapper.unknown00, "Wpn21rIn"); }

const char *getRSC_PcWpnMountWpn21rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn21rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn21rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn21rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn21rOut] = Bdat::getMember(wrapper.unknown00, "Wpn21rOut"); }

const char *getRSC_PcWpnMountWpn21rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn21rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn21rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22rIn] = Bdat::getMember(wrapper.unknown00, "Wpn22rIn"); }

const char *getRSC_PcWpnMountWpn22rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22rOut] = Bdat::getMember(wrapper.unknown00, "Wpn22rOut"); }

const char *getRSC_PcWpnMountWpn22rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22lIn] = Bdat::getMember(wrapper.unknown00, "Wpn22lIn"); }

const char *getRSC_PcWpnMountWpn22lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22lOut] = Bdat::getMember(wrapper.unknown00, "Wpn22lOut"); }

const char *getRSC_PcWpnMountWpn22lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23rIn] = Bdat::getMember(wrapper.unknown00, "Wpn23rIn"); }

const char *getRSC_PcWpnMountWpn23rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23rOut] = Bdat::getMember(wrapper.unknown00, "Wpn23rOut"); }

const char *getRSC_PcWpnMountWpn23rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23lIn] = Bdat::getMember(wrapper.unknown00, "Wpn23lIn"); }

const char *getRSC_PcWpnMountWpn23lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23lOut] = Bdat::getMember(wrapper.unknown00, "Wpn23lOut"); }

const char *getRSC_PcWpnMountWpn23lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24rIn] = Bdat::getMember(wrapper.unknown00, "Wpn24rIn"); }

const char *getRSC_PcWpnMountWpn24rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24rOut] = Bdat::getMember(wrapper.unknown00, "Wpn24rOut"); }

const char *getRSC_PcWpnMountWpn24rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24lIn] = Bdat::getMember(wrapper.unknown00, "Wpn24lIn"); }

const char *getRSC_PcWpnMountWpn24lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24lOut] = Bdat::getMember(wrapper.unknown00, "Wpn24lOut"); }

const char *getRSC_PcWpnMountWpn24lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25rIn] = Bdat::getMember(wrapper.unknown00, "Wpn25rIn"); }

const char *getRSC_PcWpnMountWpn25rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25rOut] = Bdat::getMember(wrapper.unknown00, "Wpn25rOut"); }

const char *getRSC_PcWpnMountWpn25rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25lIn] = Bdat::getMember(wrapper.unknown00, "Wpn25lIn"); }

const char *getRSC_PcWpnMountWpn25lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25lOut] = Bdat::getMember(wrapper.unknown00, "Wpn25lOut"); }

const char *getRSC_PcWpnMountWpn25lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26rIn] = Bdat::getMember(wrapper.unknown00, "Wpn26rIn"); }

const char *getRSC_PcWpnMountWpn26rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26rIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26rOut] = Bdat::getMember(wrapper.unknown00, "Wpn26rOut"); }

const char *getRSC_PcWpnMountWpn26rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26rOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26lIn] = Bdat::getMember(wrapper.unknown00, "Wpn26lIn"); }

const char *getRSC_PcWpnMountWpn26lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26lIn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26lOut] = Bdat::getMember(wrapper.unknown00, "Wpn26lOut"); }

const char *getRSC_PcWpnMountWpn26lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26lOut] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26lOut], id, 7).valueString;
}

void initRscEnWpnModel(const CBdatWrapper &wrapper) { s_members[RscEnWpnModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRscEnWpnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnModel], id, 7).valueString;
}

void initRscEnWpnScale(const CBdatWrapper &wrapper) { s_members[RscEnWpnScale] = Bdat::getMember(wrapper.unknown00, "Scale"); }

u32 getRscEnWpnScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnScale] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWpnScale], id, 2).valueU16;
}

void initRscEnWpnMotion(const CBdatWrapper &wrapper) { s_members[RscEnWpnMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRscEnWpnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMotion], id, 7).valueString;
}

void initRscEnWpnMtpInChara(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpInChara] = Bdat::getMember(wrapper.unknown00, "MtpInChara"); }

const char *getRscEnWpnMtpInChara(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpInChara] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpInChara], id, 7).valueString;
}

void initRscEnWpnMtpInWpn(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpInWpn] = Bdat::getMember(wrapper.unknown00, "MtpInWpn"); }

const char *getRscEnWpnMtpInWpn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpInWpn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpInWpn], id, 7).valueString;
}

void initRscEnWpnMtpOutChara(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpOutChara] = Bdat::getMember(wrapper.unknown00, "MtpOutChara"); }

const char *getRscEnWpnMtpOutChara(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpOutChara] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpOutChara], id, 7).valueString;
}

void initRscEnWpnMtpOutWpn(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpOutWpn] = Bdat::getMember(wrapper.unknown00, "MtpOutWpn"); }

const char *getRscEnWpnMtpOutWpn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpOutWpn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpOutWpn], id, 7).valueString;
}

void initRscNpcWpnModel(const CBdatWrapper &wrapper) { s_members[RscNpcWpnModel] = Bdat::getMember(wrapper.unknown00, "Model"); }

const char *getRscNpcWpnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcWpnModel] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcWpnModel], id, 7).valueString;
}

void initRscNpcWpnMotion(const CBdatWrapper &wrapper) { s_members[RscNpcWpnMotion] = Bdat::getMember(wrapper.unknown00, "Motion"); }

const char *getRscNpcWpnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcWpnMotion] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcWpnMotion], id, 7).valueString;
}

void initDriverParamExtMountNpc(const CBdatWrapper &wrapper) { s_members[DriverParamExtMountNpc] = Bdat::getMember(wrapper.unknown00, "ExtMountNpc"); }

u32 getDriverParamExtMountNpc(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DriverParamExtMountNpc] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DriverParamExtMountNpc], id, 2).valueU16;
}

void initDriverParamExtMountBone(const CBdatWrapper &wrapper) { s_members[DriverParamExtMountBone] = Bdat::getMember(wrapper.unknown00, "ExtMountBone"); }

const char *getDriverParamExtMountBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DriverParamExtMountBone] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[DriverParamExtMountBone], id, 7).valueString;
}

void initDriverParamExtMountCond(const CBdatWrapper &wrapper) { s_members[DriverParamExtMountCond] = Bdat::getMember(wrapper.unknown00, "ExtMountCond"); }

u32 getDriverParamExtMountCond(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DriverParamExtMountCond] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DriverParamExtMountCond], id, 2).valueU16;
}

void initVoiceTableDriver1(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver1] = Bdat::getMember(wrapper.unknown00, "Driver1"); }

const char *getVoiceTableDriver1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver1], id, 7).valueString;
}

void initVoiceTableDriver2(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver2] = Bdat::getMember(wrapper.unknown00, "Driver2"); }

const char *getVoiceTableDriver2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver2], id, 7).valueString;
}

void initVoiceTableDriver3(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver3] = Bdat::getMember(wrapper.unknown00, "Driver3"); }

const char *getVoiceTableDriver3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver3], id, 7).valueString;
}

void initVoiceTableDriver4(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver4] = Bdat::getMember(wrapper.unknown00, "Driver4"); }

const char *getVoiceTableDriver4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver4], id, 7).valueString;
}

void initVoiceTableDriver5(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver5] = Bdat::getMember(wrapper.unknown00, "Driver5"); }

const char *getVoiceTableDriver5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver5], id, 7).valueString;
}

void initVoiceTableDriver6(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver6] = Bdat::getMember(wrapper.unknown00, "Driver6"); }

const char *getVoiceTableDriver6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver6], id, 7).valueString;
}

void initVoiceTableBladeBlade1(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade1] = Bdat::getMember(wrapper.unknown00, "Blade1"); }

const char *getVoiceTableBladeBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade1], id, 7).valueString;
}

void initVoiceTableBladeBlade2(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade2] = Bdat::getMember(wrapper.unknown00, "Blade2"); }

const char *getVoiceTableBladeBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade2], id, 7).valueString;
}

void initVoiceTableBladeBlade3(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade3] = Bdat::getMember(wrapper.unknown00, "Blade3"); }

const char *getVoiceTableBladeBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade3], id, 7).valueString;
}

void initVoiceTableBladeBlade4(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade4] = Bdat::getMember(wrapper.unknown00, "Blade4"); }

const char *getVoiceTableBladeBlade4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade4], id, 7).valueString;
}

void initVoiceTableBladeBlade5(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade5] = Bdat::getMember(wrapper.unknown00, "Blade5"); }

const char *getVoiceTableBladeBlade5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade5], id, 7).valueString;
}

void initVoiceTableBladeBlade6(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade6] = Bdat::getMember(wrapper.unknown00, "Blade6"); }

const char *getVoiceTableBladeBlade6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade6], id, 7).valueString;
}

void initVoiceTableBladeBlade7(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade7] = Bdat::getMember(wrapper.unknown00, "Blade7"); }

const char *getVoiceTableBladeBlade7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade7], id, 7).valueString;
}

void initVoiceTableBladeBlade8(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade8] = Bdat::getMember(wrapper.unknown00, "Blade8"); }

const char *getVoiceTableBladeBlade8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade8], id, 7).valueString;
}

void initVoiceTableBladeBlade9(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade9] = Bdat::getMember(wrapper.unknown00, "Blade9"); }

const char *getVoiceTableBladeBlade9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade9], id, 7).valueString;
}

void initVoiceTableBladeBlade10(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade10] = Bdat::getMember(wrapper.unknown00, "Blade10"); }

const char *getVoiceTableBladeBlade10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade10], id, 7).valueString;
}

void initVoiceTableBladeBlade11(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade11] = Bdat::getMember(wrapper.unknown00, "Blade11"); }

const char *getVoiceTableBladeBlade11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade11], id, 7).valueString;
}

void initVoiceTableRareRareBlade1(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade1] = Bdat::getMember(wrapper.unknown00, "RareBlade1"); }

const char *getVoiceTableRareRareBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade1], id, 7).valueString;
}

void initVoiceTableRareRareBlade2(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade2] = Bdat::getMember(wrapper.unknown00, "RareBlade2"); }

const char *getVoiceTableRareRareBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade2], id, 7).valueString;
}

void initVoiceTableRareRareBlade3(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade3] = Bdat::getMember(wrapper.unknown00, "RareBlade3"); }

const char *getVoiceTableRareRareBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade3], id, 7).valueString;
}

void initVoiceTableRareRareBlade4(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade4] = Bdat::getMember(wrapper.unknown00, "RareBlade4"); }

const char *getVoiceTableRareRareBlade4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade4], id, 7).valueString;
}

void initVoiceTableRareRareBlade5(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade5] = Bdat::getMember(wrapper.unknown00, "RareBlade5"); }

const char *getVoiceTableRareRareBlade5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade5], id, 7).valueString;
}

void initVoiceTableRareRareBlade6(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade6] = Bdat::getMember(wrapper.unknown00, "RareBlade6"); }

const char *getVoiceTableRareRareBlade6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade6], id, 7).valueString;
}

void initVoiceTableRareRareBlade7(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade7] = Bdat::getMember(wrapper.unknown00, "RareBlade7"); }

const char *getVoiceTableRareRareBlade7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade7], id, 7).valueString;
}

void initVoiceTableRareRareBlade8(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade8] = Bdat::getMember(wrapper.unknown00, "RareBlade8"); }

const char *getVoiceTableRareRareBlade8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade8], id, 7).valueString;
}

void initVoiceTableRareRareBlade9(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade9] = Bdat::getMember(wrapper.unknown00, "RareBlade9"); }

const char *getVoiceTableRareRareBlade9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade9], id, 7).valueString;
}

void initVoiceTableRareRareBlade10(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade10] = Bdat::getMember(wrapper.unknown00, "RareBlade10"); }

const char *getVoiceTableRareRareBlade10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade10], id, 7).valueString;
}

void initVoiceTableRareRareBlade11(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade11] = Bdat::getMember(wrapper.unknown00, "RareBlade11"); }

const char *getVoiceTableRareRareBlade11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade11], id, 7).valueString;
}

void initVoiceTableRareRareBlade12(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade12] = Bdat::getMember(wrapper.unknown00, "RareBlade12"); }

const char *getVoiceTableRareRareBlade12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade12], id, 7).valueString;
}

void initVoiceTableRareRareBlade13(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade13] = Bdat::getMember(wrapper.unknown00, "RareBlade13"); }

const char *getVoiceTableRareRareBlade13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade13], id, 7).valueString;
}

void initVoiceTableRareRareBlade14(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade14] = Bdat::getMember(wrapper.unknown00, "RareBlade14"); }

const char *getVoiceTableRareRareBlade14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade14], id, 7).valueString;
}

void initVoiceTableRareRareBlade15(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade15] = Bdat::getMember(wrapper.unknown00, "RareBlade15"); }

const char *getVoiceTableRareRareBlade15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade15], id, 7).valueString;
}

void initVoiceTableRareRareBlade16(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade16] = Bdat::getMember(wrapper.unknown00, "RareBlade16"); }

const char *getVoiceTableRareRareBlade16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade16], id, 7).valueString;
}

void initVoiceTableRareRareBlade17(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade17] = Bdat::getMember(wrapper.unknown00, "RareBlade17"); }

const char *getVoiceTableRareRareBlade17(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade17] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade17], id, 7).valueString;
}

void initVoiceTableRareRareBlade18(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade18] = Bdat::getMember(wrapper.unknown00, "RareBlade18"); }

const char *getVoiceTableRareRareBlade18(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade18] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade18], id, 7).valueString;
}

void initVoiceTableRareRareBlade19(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade19] = Bdat::getMember(wrapper.unknown00, "RareBlade19"); }

const char *getVoiceTableRareRareBlade19(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade19] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade19], id, 7).valueString;
}

void initVoiceTableRareRareBlade20(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade20] = Bdat::getMember(wrapper.unknown00, "RareBlade20"); }

const char *getVoiceTableRareRareBlade20(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade20] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade20], id, 7).valueString;
}

void initVoiceTableRareRareBlade21(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade21] = Bdat::getMember(wrapper.unknown00, "RareBlade21"); }

const char *getVoiceTableRareRareBlade21(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade21] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade21], id, 7).valueString;
}

void initVoiceTableRareRareBlade22(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade22] = Bdat::getMember(wrapper.unknown00, "RareBlade22"); }

const char *getVoiceTableRareRareBlade22(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade22] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade22], id, 7).valueString;
}

void initVoiceTableRareRareBlade23(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade23] = Bdat::getMember(wrapper.unknown00, "RareBlade23"); }

const char *getVoiceTableRareRareBlade23(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade23] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade23], id, 7).valueString;
}

void initVoiceTableRareRareBlade24(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade24] = Bdat::getMember(wrapper.unknown00, "RareBlade24"); }

const char *getVoiceTableRareRareBlade24(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade24] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade24], id, 7).valueString;
}

void initVoiceTableRareRareBlade25(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade25] = Bdat::getMember(wrapper.unknown00, "RareBlade25"); }

const char *getVoiceTableRareRareBlade25(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade25] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade25], id, 7).valueString;
}

void initVoiceTableRareRareBlade26(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade26] = Bdat::getMember(wrapper.unknown00, "RareBlade26"); }

const char *getVoiceTableRareRareBlade26(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade26] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade26], id, 7).valueString;
}

void initVoiceTableRareRareBlade27(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade27] = Bdat::getMember(wrapper.unknown00, "RareBlade27"); }

const char *getVoiceTableRareRareBlade27(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade27] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade27], id, 7).valueString;
}

void initVoiceTableRareRareBlade28(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade28] = Bdat::getMember(wrapper.unknown00, "RareBlade28"); }

const char *getVoiceTableRareRareBlade28(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade28] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade28], id, 7).valueString;
}

void initVoiceTableRareRareBlade29(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade29] = Bdat::getMember(wrapper.unknown00, "RareBlade29"); }

const char *getVoiceTableRareRareBlade29(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade29] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade29], id, 7).valueString;
}

void initVoiceTableRareRareBlade30(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade30] = Bdat::getMember(wrapper.unknown00, "RareBlade30"); }

const char *getVoiceTableRareRareBlade30(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade30] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade30], id, 7).valueString;
}

void initVoiceTableRareRareBlade31(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade31] = Bdat::getMember(wrapper.unknown00, "RareBlade31"); }

const char *getVoiceTableRareRareBlade31(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade31] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade31], id, 7).valueString;
}

void initVoiceTableRareRareBlade32(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade32] = Bdat::getMember(wrapper.unknown00, "RareBlade32"); }

const char *getVoiceTableRareRareBlade32(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade32] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade32], id, 7).valueString;
}

void initVoiceTableRareRareBlade33(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade33] = Bdat::getMember(wrapper.unknown00, "RareBlade33"); }

const char *getVoiceTableRareRareBlade33(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade33] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade33], id, 7).valueString;
}

void initVoiceTableRareRareBlade34(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade34] = Bdat::getMember(wrapper.unknown00, "RareBlade34"); }

const char *getVoiceTableRareRareBlade34(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade34] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade34], id, 7).valueString;
}

void initVoiceTableRareRareBlade35(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade35] = Bdat::getMember(wrapper.unknown00, "RareBlade35"); }

const char *getVoiceTableRareRareBlade35(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade35] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade35], id, 7).valueString;
}

void initVoiceTableRareRareBlade36(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade36] = Bdat::getMember(wrapper.unknown00, "RareBlade36"); }

const char *getVoiceTableRareRareBlade36(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade36] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade36], id, 7).valueString;
}

void initVoiceTableRareRareBlade37(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade37] = Bdat::getMember(wrapper.unknown00, "RareBlade37"); }

const char *getVoiceTableRareRareBlade37(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade37] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade37], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade1(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade1] = Bdat::getMember(wrapper.unknown00, "CommonBlade1"); }

const char *getVoiceTableCommonCommonBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade1], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade2(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade2] = Bdat::getMember(wrapper.unknown00, "CommonBlade2"); }

const char *getVoiceTableCommonCommonBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade2], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade3(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade3] = Bdat::getMember(wrapper.unknown00, "CommonBlade3"); }

const char *getVoiceTableCommonCommonBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade3], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade4(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade4] = Bdat::getMember(wrapper.unknown00, "CommonBlade4"); }

const char *getVoiceTableCommonCommonBlade4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade4], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade5(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade5] = Bdat::getMember(wrapper.unknown00, "CommonBlade5"); }

const char *getVoiceTableCommonCommonBlade5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade5], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade6(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade6] = Bdat::getMember(wrapper.unknown00, "CommonBlade6"); }

const char *getVoiceTableCommonCommonBlade6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade6], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade7(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade7] = Bdat::getMember(wrapper.unknown00, "CommonBlade7"); }

const char *getVoiceTableCommonCommonBlade7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade7], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade8(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade8] = Bdat::getMember(wrapper.unknown00, "CommonBlade8"); }

const char *getVoiceTableCommonCommonBlade8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade8], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade9(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade9] = Bdat::getMember(wrapper.unknown00, "CommonBlade9"); }

const char *getVoiceTableCommonCommonBlade9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade9], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade10(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade10] = Bdat::getMember(wrapper.unknown00, "CommonBlade10"); }

const char *getVoiceTableCommonCommonBlade10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade10], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade11(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade11] = Bdat::getMember(wrapper.unknown00, "CommonBlade11"); }

const char *getVoiceTableCommonCommonBlade11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade11], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade12(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade12] = Bdat::getMember(wrapper.unknown00, "CommonBlade12"); }

const char *getVoiceTableCommonCommonBlade12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade12], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade13(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade13] = Bdat::getMember(wrapper.unknown00, "CommonBlade13"); }

const char *getVoiceTableCommonCommonBlade13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade13], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade14(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade14] = Bdat::getMember(wrapper.unknown00, "CommonBlade14"); }

const char *getVoiceTableCommonCommonBlade14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade14], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade15(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade15] = Bdat::getMember(wrapper.unknown00, "CommonBlade15"); }

const char *getVoiceTableCommonCommonBlade15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade15], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade16(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade16] = Bdat::getMember(wrapper.unknown00, "CommonBlade16"); }

const char *getVoiceTableCommonCommonBlade16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade16], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade17(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade17] = Bdat::getMember(wrapper.unknown00, "CommonBlade17"); }

const char *getVoiceTableCommonCommonBlade17(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade17] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade17], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade18(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade18] = Bdat::getMember(wrapper.unknown00, "CommonBlade18"); }

const char *getVoiceTableCommonCommonBlade18(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade18] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade18], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade19(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade19] = Bdat::getMember(wrapper.unknown00, "CommonBlade19"); }

const char *getVoiceTableCommonCommonBlade19(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade19] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade19], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade20(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade20] = Bdat::getMember(wrapper.unknown00, "CommonBlade20"); }

const char *getVoiceTableCommonCommonBlade20(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade20] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade20], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade21(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade21] = Bdat::getMember(wrapper.unknown00, "CommonBlade21"); }

const char *getVoiceTableCommonCommonBlade21(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade21] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade21], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade22(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade22] = Bdat::getMember(wrapper.unknown00, "CommonBlade22"); }

const char *getVoiceTableCommonCommonBlade22(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade22] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade22], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade23(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade23] = Bdat::getMember(wrapper.unknown00, "CommonBlade23"); }

const char *getVoiceTableCommonCommonBlade23(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade23] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade23], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade24(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade24] = Bdat::getMember(wrapper.unknown00, "CommonBlade24"); }

const char *getVoiceTableCommonCommonBlade24(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade24] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade24], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade25(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade25] = Bdat::getMember(wrapper.unknown00, "CommonBlade25"); }

const char *getVoiceTableCommonCommonBlade25(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade25] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade25], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade26(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade26] = Bdat::getMember(wrapper.unknown00, "CommonBlade26"); }

const char *getVoiceTableCommonCommonBlade26(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade26] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade26], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade27(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade27] = Bdat::getMember(wrapper.unknown00, "CommonBlade27"); }

const char *getVoiceTableCommonCommonBlade27(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade27] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade27], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade28(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade28] = Bdat::getMember(wrapper.unknown00, "CommonBlade28"); }

const char *getVoiceTableCommonCommonBlade28(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade28] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade28], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade29(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade29] = Bdat::getMember(wrapper.unknown00, "CommonBlade29"); }

const char *getVoiceTableCommonCommonBlade29(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade29] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade29], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade30(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade30] = Bdat::getMember(wrapper.unknown00, "CommonBlade30"); }

const char *getVoiceTableCommonCommonBlade30(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade30] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade30], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade31(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade31] = Bdat::getMember(wrapper.unknown00, "CommonBlade31"); }

const char *getVoiceTableCommonCommonBlade31(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade31] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade31], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade32(const CBdatWrapper &wrapper) { s_members[VoiceTableCommonCommonBlade32] = Bdat::getMember(wrapper.unknown00, "CommonBlade32"); }

const char *getVoiceTableCommonCommonBlade32(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade32] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade32], id, 7).valueString;
}

void initFLD_actorSELOD(const CBdatWrapper &wrapper) { s_members[FLD_actorSELOD] = Bdat::getMember(wrapper.unknown00, "LOD"); }

const char *getFLD_actorSELOD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSELOD] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[FLD_actorSELOD], id, 7).valueString;
}

void initFLD_actorSEse_type(const CBdatWrapper &wrapper) { s_members[FLD_actorSEse_type] = Bdat::getMember(wrapper.unknown00, "se_type"); }

u32 getFLD_actorSEse_type(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEse_type] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEse_type], id, 1).valueU8;
}

void initFLD_actorSEseName(const CBdatWrapper &wrapper) { s_members[FLD_actorSEseName] = Bdat::getMember(wrapper.unknown00, "seName"); }

u32 getFLD_actorSEseName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEseName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEseName], id, 2).valueU16;
}

void initFLD_actorSEmax_volume_Dist(const CBdatWrapper &wrapper) { s_members[FLD_actorSEmax_volume_Dist] = Bdat::getMember(wrapper.unknown00, "max_volume_Dist"); }

f32 getFLD_actorSEmax_volume_Dist(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEmax_volume_Dist] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEmax_volume_Dist], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEmin_volume_Dist(const CBdatWrapper &wrapper) { s_members[FLD_actorSEmin_volume_Dist] = Bdat::getMember(wrapper.unknown00, "min_volume_Dist"); }

f32 getFLD_actorSEmin_volume_Dist(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEmin_volume_Dist] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEmin_volume_Dist], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEvolumeMAX(const CBdatWrapper &wrapper) { s_members[FLD_actorSEvolumeMAX] = Bdat::getMember(wrapper.unknown00, "volumeMAX"); }

u32 getFLD_actorSEvolumeMAX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEvolumeMAX] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEvolumeMAX], id, 1).valueU8;
}

void initFLD_actorSEvolumeMIN(const CBdatWrapper &wrapper) { s_members[FLD_actorSEvolumeMIN] = Bdat::getMember(wrapper.unknown00, "volumeMIN"); }

u32 getFLD_actorSEvolumeMIN(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEvolumeMIN] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEvolumeMIN], id, 1).valueU8;
}

void initFLD_actorSEoffsetX(const CBdatWrapper &wrapper) { s_members[FLD_actorSEoffsetX] = Bdat::getMember(wrapper.unknown00, "offsetX"); }

f32 getFLD_actorSEoffsetX(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEoffsetX] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEoffsetX], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEoffsetY(const CBdatWrapper &wrapper) { s_members[FLD_actorSEoffsetY] = Bdat::getMember(wrapper.unknown00, "offsetY"); }

f32 getFLD_actorSEoffsetY(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEoffsetY] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEoffsetY], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEoffsetZ(const CBdatWrapper &wrapper) { s_members[FLD_actorSEoffsetZ] = Bdat::getMember(wrapper.unknown00, "offsetZ"); }

f32 getFLD_actorSEoffsetZ(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEoffsetZ] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEoffsetZ], id, 8).valueF32;
  }

  return value;
}

} // namespace _gfbrs

GfBdatRsc::GfBdatRsc()
    : m_rscEn(nullptr), m_rscEnGenus(nullptr), m_rscEnUnd(nullptr), m_rscNpcList(nullptr), m_rscNpcWpn(nullptr), m_rscMobList(nullptr), m_RSC_PcWpn(nullptr), m_RSC_PcWpnMount(nullptr),
      m_rscEnWpn(nullptr), m_RSC_TboxList(nullptr), m_RSC_MapObjList(nullptr), m_driverParam(nullptr), m_voiceTable(nullptr), m_voiceTableBlade(nullptr), m_voiceTableRare(nullptr),
      m_voiceTableCommon(nullptr), m_FLD_actorSE(nullptr) {
  bdatRefresh();
}

GfBdatRsc::~GfBdatRsc() { destroyFP(); }

void GfBdatRsc::destroyFP() {
  if (m_rscEn != nullptr) {
    delete m_rscEn;
    m_rscEn = nullptr;
  }

  if (m_rscEnGenus != nullptr) {
    delete m_rscEnGenus;
    m_rscEnGenus = nullptr;
  }

  if (m_rscEnUnd != nullptr) {
    delete m_rscEnUnd;
    m_rscEnUnd = nullptr;
  }

  if (m_rscNpcList != nullptr) {
    delete m_rscNpcList;
    m_rscNpcList = nullptr;
  }

  if (m_rscNpcWpn != nullptr) {
    delete m_rscNpcWpn;
    m_rscNpcWpn = nullptr;
  }

  if (m_rscMobList != nullptr) {
    delete m_rscMobList;
    m_rscMobList = nullptr;
  }

  if (m_RSC_PcWpn != nullptr) {
    delete m_RSC_PcWpn;
    m_RSC_PcWpn = nullptr;
  }

  if (m_RSC_PcWpnMount != nullptr) {
    delete m_RSC_PcWpnMount;
    m_RSC_PcWpnMount = nullptr;
  }

  if (m_rscEnWpn != nullptr) {
    delete m_rscEnWpn;
    m_rscEnWpn = nullptr;
  }

  if (m_RSC_TboxList != nullptr) {
    delete m_RSC_TboxList;
    m_RSC_TboxList = nullptr;
  }

  if (m_RSC_MapObjList != nullptr) {
    delete m_RSC_MapObjList;
    m_RSC_MapObjList = nullptr;
  }

  if (m_driverParam != nullptr) {
    delete m_driverParam;
    m_driverParam = nullptr;
  }

  if (m_voiceTable != nullptr) {
    delete m_voiceTable;
    m_voiceTable = nullptr;
  }

  if (m_voiceTableBlade != nullptr) {
    delete m_voiceTableBlade;
    m_voiceTableBlade = nullptr;
  }

  if (m_voiceTableRare != nullptr) {
    delete m_voiceTableRare;
    m_voiceTableRare = nullptr;
  }

  if (m_voiceTableCommon != nullptr) {
    delete m_voiceTableCommon;
    m_voiceTableCommon = nullptr;
  }

  if (m_FLD_actorSE != nullptr) {
    delete m_FLD_actorSE;
    m_FLD_actorSE = nullptr;
  }
}

void GfBdatRsc::createFP() {
  m_rscEn = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_EN)};
  m_rscEnGenus = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_EN_GENUS)};
  m_rscEnUnd = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_EN_UND)};
  m_rscNpcList = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_NPC_LIST)};
  m_rscNpcWpn = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_NPC_WPN)};
  m_rscMobList = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_MOB_LIST)};
  m_RSC_PcWpn = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_PC_WPN)};
  m_RSC_PcWpnMount = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_PC_WPN_MOUNT)};
  m_rscEnWpn = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_EN_WPN)};
  m_RSC_TboxList = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_TBOX_LIST)};
  m_RSC_MapObjList = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_RSC_MAP_OBJ_LIST)};
  m_driverParam = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_CHR_DRIVER_PARAM)};
  m_voiceTable = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_FLD_VOICE_TABLE)};
  m_voiceTableBlade = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_FLD_VOICE_TABLE_BLADE)};
  m_voiceTableRare = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_FLD_VOICE_TABLE_RARE)};
  m_voiceTableCommon = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_FLD_VOICE_TABLE_COMMON)};
  m_FLD_actorSE = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper{GfDataBdat::getFP(BDAT_FLD_ACTOR_SE)};
}

void GfBdatRsc::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbrs::initRscEnDebugName(*m_rscEn);
  _gfbrs::initRscEnTypeFamily(*m_rscEn);
  _gfbrs::initRscEnTypeGenus(*m_rscEn);
  _gfbrs::initRscEnActType(*m_rscEn);
  _gfbrs::initRscEnFlyHeight(*m_rscEn);
  _gfbrs::initRscEnFldMoveType(*m_rscEn);
  _gfbrs::initRscEnMaterial(*m_rscEn);
  _gfbrs::initRscEnProxyID(*m_rscEn);
  _gfbrs::initRscEnEnRadius(*m_rscEn);
  _gfbrs::initRscEnEnRadius2(*m_rscEn);
  _gfbrs::initRscEnChestHeight(*m_rscEn);
  _gfbrs::initRscEnChestHeight2(*m_rscEn);
  _gfbrs::initRscEnBallRadius(*m_rscEn);
  _gfbrs::initRscEnBallHeight(*m_rscEn);
  _gfbrs::initRscEnCharColli(*m_rscEn);
  _gfbrs::initRscEnoffsetID(*m_rscEn);
  _gfbrs::initRscEnEyeRot(*m_rscEn);
  _gfbrs::initRscEnSearchBaseBone(*m_rscEn);
  _gfbrs::initRscEnCenterBone(*m_rscEn);
  _gfbrs::initRscEnCamBone(*m_rscEn);
  _gfbrs::initRscEnFrontAngle(*m_rscEn);
  _gfbrs::initRscEnTurnAngleSmall(*m_rscEn);
  _gfbrs::initRscEnTurnAngleBig(*m_rscEn);
  _gfbrs::initRscEnUnduration(*m_rscEn);
  _gfbrs::initRscEnModel(*m_rscEn);
  _gfbrs::initRscEnChrFile(*m_rscEn);
  _gfbrs::initRscEnMotion(*m_rscEn);
  _gfbrs::initRscEnRefMotion(*m_rscEn);
  _gfbrs::initRscEnEffectPack(*m_rscEn);
  _gfbrs::initRscEnLoopEffect(*m_rscEn);
  _gfbrs::initRscEnSePack(*m_rscEn);
  _gfbrs::initRscEnVoice(*m_rscEn);
  _gfbrs::initRscEnVoiceEx(*m_rscEn);
  _gfbrs::initRscEnClipEvent(*m_rscEn);
  _gfbrs::initRscEnComp_Eff(*m_rscEn);
  _gfbrs::initRscEnComp_Se(*m_rscEn);
  _gfbrs::initRscEnComp_Vo(*m_rscEn);
  _gfbrs::initRscEnFlagNoEcSkip(*m_rscEn);
  _gfbrs::initRscEnFlagMap(*m_rscEn);
  _gfbrs::initRscEnFlagEvt(*m_rscEn);
  _gfbrs::initRscEnFlagNoWinVo(*m_rscEn);
  _gfbrs::initRscEnFlagBait(*m_rscEn);
  _gfbrs::initRscEnFlagUseSearchBone(*m_rscEn);
  _gfbrs::initRscEnFlagNoVanish(*m_rscEn);
  _gfbrs::initRscEnFlagNoCamera(*m_rscEn);
  _gfbrs::initRscEnFlagWeaponDrawDisp(*m_rscEn);
  _gfbrs::initRscEnFlagJoinAll(*m_rscEn);
  _gfbrs::initRscEnFlagDeathMotion(*m_rscEn);
  _gfbrs::initRscEnWeaponNum1(*m_rscEn);
  _gfbrs::initRscEnWeaponNum2(*m_rscEn);
  _gfbrs::initRscEnWeaponNum3(*m_rscEn);
  _gfbrs::initRscEnWeaponNum4(*m_rscEn);
  _gfbrs::initRscEnWeaponNum5(*m_rscEn);
  _gfbrs::initRscEnMemorySlot(*m_rscEn);
  _gfbrs::initRscEnRace(*m_rscEn);
  _gfbrs::initRscEnDrType(*m_rscEn);
  _gfbrs::initRscEnGoldDivideRev(*m_rscEn);
  _gfbrs::initRscEnFootStep(*m_rscEn);
  _gfbrs::initRscEnFootStepEffect(*m_rscEn);
  _gfbrs::initRscEnRotateX(*m_rscEn);
  _gfbrs::initRscEnRotateY(*m_rscEn);
  _gfbrs::initRscEnRotateZ(*m_rscEn);
  _gfbrs::initRscEnRotateDeg(*m_rscEn);
  _gfbrs::initRscEnRotEffScale(*m_rscEn);
  _gfbrs::initRscEnExtraParts1(*m_rscEn);
  _gfbrs::initRscEnExtraParts2(*m_rscEn);
  _gfbrs::initRscEnExtraParts3(*m_rscEn);
  _gfbrs::initRscEnExtraParts4(*m_rscEn);
  _gfbrs::initRscEnDeadSeNum(*m_rscEn);
  _gfbrs::initRscEnRotateBone(*m_rscEn);
  _gfbrs::initRscEnGenusNAME(*m_rscEnGenus);
  _gfbrs::initRscEnGenusCAPTION(*m_rscEnGenus);
  _gfbrs::initRscEnGenusFlaggimmicktype(*m_rscEnGenus);
  _gfbrs::initRscEnUndFlagUndX(*m_rscEnUnd);
  _gfbrs::initRscEnUndFlagUndZ(*m_rscEnUnd);
  _gfbrs::initRscEnUndUndMinX(*m_rscEnUnd);
  _gfbrs::initRscEnUndUndMaxX(*m_rscEnUnd);
  _gfbrs::initRscEnUndUndMinZ(*m_rscEnUnd);
  _gfbrs::initRscEnUndUndMaxZ(*m_rscEnUnd);
  _gfbrs::initRscEnUndUndDeg(*m_rscEnUnd);
  _gfbrs::initRscNpcListModel(*m_rscNpcList);
  _gfbrs::initRscNpcListMotion(*m_rscNpcList);
  _gfbrs::initRscNpcListAddMotion(*m_rscNpcList);
  _gfbrs::initRscNpcListComp_Eff(*m_rscNpcList);
  _gfbrs::initRscNpcListCollisionId(*m_rscNpcList);
  _gfbrs::initRscNpcListSE(*m_rscNpcList);
  _gfbrs::initRscNpcListSeEnv(*m_rscNpcList);
  _gfbrs::initRscNpcListRace(*m_rscNpcList);
  _gfbrs::initRscNpcListFootStep(*m_rscNpcList);
  _gfbrs::initRscNpcListFootStepEffect(*m_rscNpcList);
  _gfbrs::initRscNpcListRoots(*m_rscNpcList);
  _gfbrs::initRscNpcListGender(*m_rscNpcList);
  _gfbrs::initRscNpcListName(*m_rscNpcList);
  _gfbrs::initRscNpcListOffsetID(*m_rscNpcList);
  _gfbrs::initRscNpcListEyeRot(*m_rscNpcList);
  _gfbrs::initRscNpcListExtraParts1(*m_rscNpcList);
  _gfbrs::initRscNpcListExtraParts2(*m_rscNpcList);
  _gfbrs::initRscNpcListExtraParts3(*m_rscNpcList);
  _gfbrs::initRscNpcListExtraParts4(*m_rscNpcList);
  _gfbrs::initRscNpcListExtraParts5(*m_rscNpcList);
  _gfbrs::initRscNpcListExtraParts6(*m_rscNpcList);
  _gfbrs::initRscNpcListScale(*m_rscNpcList);
  _gfbrs::initRscNpcListEventAsset(*m_rscNpcList);
  _gfbrs::initRscMobListModel(*m_rscMobList);
  _gfbrs::initRscMobListMotion(*m_rscMobList);
  _gfbrs::initRscMobListAddMotion(*m_rscMobList);
  _gfbrs::initRscMobListComp_Eff(*m_rscMobList);
  _gfbrs::initRscMobListCollisionId(*m_rscMobList);
  _gfbrs::initRscMobListSE(*m_rscMobList);
  _gfbrs::initRscMobListSeEnv(*m_rscMobList);
  _gfbrs::initRscMobListRace(*m_rscMobList);
  _gfbrs::initRscMobListFootStep(*m_rscMobList);
  _gfbrs::initRscMobListFootStepEffect(*m_rscMobList);
  _gfbrs::initRscMobListOffsetID(*m_rscMobList);
  _gfbrs::initRscMobListExtraParts1(*m_rscMobList);
  _gfbrs::initRscMobListExtraParts2(*m_rscMobList);
  _gfbrs::initRscMobListExtraParts3(*m_rscMobList);
  _gfbrs::initRscMobListExtraParts4(*m_rscMobList);
  _gfbrs::initRscMobListExtraParts5(*m_rscMobList);
  _gfbrs::initRscMobListExtraParts6(*m_rscMobList);
  _gfbrs::initRSC_MapObjListModel(*m_RSC_MapObjList);
  _gfbrs::initRSC_MapObjListMotion(*m_RSC_MapObjList);
  _gfbrs::initRSC_MapObjListComp_Eff(*m_RSC_MapObjList);
  _gfbrs::initRSC_MapObjListSE(*m_RSC_MapObjList);
  _gfbrs::initRSC_MapObjListSeEnv(*m_RSC_MapObjList);
  _gfbrs::initRSC_MapObjListflagBigObj(*m_RSC_MapObjList);
  _gfbrs::initRSC_MapObjListExtraParts1(*m_RSC_MapObjList);
  _gfbrs::initRSC_TboxListModel(*m_RSC_TboxList);
  _gfbrs::initRSC_TboxListMotion(*m_RSC_TboxList);
  _gfbrs::initRSC_PcWpnModel(*m_RSC_PcWpn);
  _gfbrs::initRSC_PcWpnMotion(*m_RSC_PcWpn);
  _gfbrs::initRSC_PcWpnMenuImageID(*m_RSC_PcWpn);
  _gfbrs::initRSC_PcWpnMountWpn01rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn01rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn02rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn02rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn03rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn03rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn03lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn03lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn04rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn04rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn05rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn05rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn05lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn05lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn06rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn06rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn07rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn07rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn07lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn07lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn08rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn08rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn09rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn09rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn09lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn09lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn10rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn10rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn10lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn10lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn11rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn11rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn12rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn12rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn12lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn12lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn13rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn13rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn14rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn14rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn15rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn15rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn16rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn16rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn16lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn16lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn17rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn17rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn18rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn18rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn19rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn19rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn20rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn20rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn20lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn20lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn21rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn21rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn22rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn22rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn22lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn22lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn23rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn23rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn23lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn23lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn24rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn24rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn24lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn24lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn25rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn25rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn25lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn25lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn26rIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn26rOut(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn26lIn(*m_RSC_PcWpnMount);
  _gfbrs::initRSC_PcWpnMountWpn26lOut(*m_RSC_PcWpnMount);
  _gfbrs::initRscEnWpnModel(*m_rscEnWpn);
  _gfbrs::initRscEnWpnScale(*m_rscEnWpn);
  _gfbrs::initRscEnWpnMotion(*m_rscEnWpn);
  _gfbrs::initRscEnWpnMtpInChara(*m_rscEnWpn);
  _gfbrs::initRscEnWpnMtpInWpn(*m_rscEnWpn);
  _gfbrs::initRscEnWpnMtpOutChara(*m_rscEnWpn);
  _gfbrs::initRscEnWpnMtpOutWpn(*m_rscEnWpn);
  _gfbrs::initRscNpcWpnModel(*m_rscNpcWpn);
  _gfbrs::initRscNpcWpnMotion(*m_rscNpcWpn);
  _gfbrs::initDriverParamExtMountNpc(*m_driverParam);
  _gfbrs::initDriverParamExtMountBone(*m_driverParam);
  _gfbrs::initDriverParamExtMountCond(*m_driverParam);
  _gfbrs::initVoiceTableDriver1(*m_voiceTable);
  _gfbrs::initVoiceTableDriver2(*m_voiceTable);
  _gfbrs::initVoiceTableDriver3(*m_voiceTable);
  _gfbrs::initVoiceTableDriver4(*m_voiceTable);
  _gfbrs::initVoiceTableDriver5(*m_voiceTable);
  _gfbrs::initVoiceTableDriver6(*m_voiceTable);
  _gfbrs::initVoiceTableBladeBlade1(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade2(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade3(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade4(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade5(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade6(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade7(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade8(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade9(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade10(*m_voiceTableBlade);
  _gfbrs::initVoiceTableBladeBlade11(*m_voiceTableBlade);
  _gfbrs::initVoiceTableRareRareBlade1(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade2(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade3(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade4(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade5(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade6(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade7(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade8(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade9(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade10(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade11(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade12(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade13(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade14(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade15(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade16(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade17(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade18(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade19(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade20(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade21(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade22(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade23(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade24(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade25(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade26(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade27(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade28(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade29(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade30(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade31(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade32(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade33(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade34(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade35(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade36(*m_voiceTableRare);
  _gfbrs::initVoiceTableRareRareBlade37(*m_voiceTableRare);
  _gfbrs::initVoiceTableCommonCommonBlade1(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade2(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade3(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade4(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade5(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade6(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade7(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade8(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade9(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade10(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade11(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade12(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade13(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade14(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade15(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade16(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade17(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade18(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade19(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade20(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade21(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade22(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade23(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade24(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade25(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade26(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade27(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade28(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade29(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade30(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade31(*m_voiceTableCommon);
  _gfbrs::initVoiceTableCommonCommonBlade32(*m_voiceTableCommon);
  _gfbrs::initFLD_actorSELOD(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEse_type(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEseName(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEmax_volume_Dist(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEmin_volume_Dist(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEvolumeMAX(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEvolumeMIN(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEoffsetX(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEoffsetY(*m_FLD_actorSE);
  _gfbrs::initFLD_actorSEoffsetZ(*m_FLD_actorSE);
}

u32 GfBdatRsc::getRscEnStart() const { return Bdat::getIdTop(m_rscEn->unknown00); }

u32 GfBdatRsc::getRscEnEnd() const { return Bdat::getIdTop(m_rscEn->unknown00) + Bdat::getIdCount(m_rscEn->unknown00); }

const char *GfBdatRsc::getRscEnDebugName(u32 id) const { return _gfbrs::getRscEnDebugName(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnTypeFamily(u32 id) const { return _gfbrs::getRscEnTypeFamily(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnTypeGenus(u32 id) const { return _gfbrs::getRscEnTypeGenus(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnActType(u32 id) const { return _gfbrs::getRscEnActType(*m_rscEn, id); }

s32 GfBdatRsc::getRscEnFlyHeight(u32 id) const { return _gfbrs::getRscEnFlyHeight(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnFldMoveType(u32 id) const { return _gfbrs::getRscEnFldMoveType(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnMaterial(u32 id) const { return _gfbrs::getRscEnMaterial(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnProxyID(u32 id) const { return _gfbrs::getRscEnProxyID(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnEnRadius(u32 id) const { return _gfbrs::getRscEnEnRadius(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnEnRadius2(u32 id) const { return _gfbrs::getRscEnEnRadius2(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnChestHeight(u32 id) const { return _gfbrs::getRscEnChestHeight(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnChestHeight2(u32 id) const { return _gfbrs::getRscEnChestHeight2(*m_rscEn, id); }

f32 GfBdatRsc::getRscEnBallRadius(u32 id) const { return _gfbrs::getRscEnBallRadius(*m_rscEn, id); }

f32 GfBdatRsc::getRscEnBallHeight(u32 id) const { return _gfbrs::getRscEnBallHeight(*m_rscEn, id); }

f32 GfBdatRsc::getRscEnCharColli(u32 id) const { return _gfbrs::getRscEnCharColli(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnoffsetID(u32 id) const { return _gfbrs::getRscEnoffsetID(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnEyeRot(u32 id) const { return _gfbrs::getRscEnEyeRot(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnSearchBaseBone(u32 id) const { return _gfbrs::getRscEnSearchBaseBone(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnCenterBone(u32 id) const { return _gfbrs::getRscEnCenterBone(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnCamBone(u32 id) const { return _gfbrs::getRscEnCamBone(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnFrontAngle(u32 id) const { return _gfbrs::getRscEnFrontAngle(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnTurnAngleSmall(u32 id) const { return _gfbrs::getRscEnTurnAngleSmall(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnTurnAngleBig(u32 id) const { return _gfbrs::getRscEnTurnAngleBig(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnUnduration(u32 id) const { return _gfbrs::getRscEnUnduration(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnModel(u32 id) const { return _gfbrs::getRscEnModel(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnChrFile(u32 id) const { return _gfbrs::getRscEnChrFile(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnMotion(u32 id) const { return _gfbrs::getRscEnMotion(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnRefMotion(u32 id) const { return _gfbrs::getRscEnRefMotion(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnEffectPack(u32 id) const { return _gfbrs::getRscEnEffectPack(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnLoopEffect(u32 id) const { return _gfbrs::getRscEnLoopEffect(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnSePack(u32 id) const { return _gfbrs::getRscEnSePack(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnVoice(u32 id) const { return _gfbrs::getRscEnVoice(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnVoiceEx(u32 id) const { return _gfbrs::getRscEnVoiceEx(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnClipEvent(u32 id) const { return _gfbrs::getRscEnClipEvent(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnComp_Eff(u32 id) const { return _gfbrs::getRscEnComp_Eff(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnComp_Se(u32 id) const { return _gfbrs::getRscEnComp_Se(*m_rscEn, id); }

const char *GfBdatRsc::getRscEnComp_Vo(u32 id) const { return _gfbrs::getRscEnComp_Vo(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagNoEcSkip(u32 id) const { return _gfbrs::isRscEnFlagNoEcSkip(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagMap(u32 id) const { return _gfbrs::isRscEnFlagMap(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagEvt(u32 id) const { return _gfbrs::isRscEnFlagEvt(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagNoWinVo(u32 id) const { return _gfbrs::isRscEnFlagNoWinVo(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagBait(u32 id) const { return _gfbrs::isRscEnFlagBait(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagUseSearchBone(u32 id) const { return _gfbrs::isRscEnFlagUseSearchBone(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagNoVanish(u32 id) const { return _gfbrs::isRscEnFlagNoVanish(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagNoCamera(u32 id) const { return _gfbrs::isRscEnFlagNoCamera(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagWeaponDrawDisp(u32 id) const { return _gfbrs::isRscEnFlagWeaponDrawDisp(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagJoinAll(u32 id) const { return _gfbrs::isRscEnFlagJoinAll(*m_rscEn, id); }

bool GfBdatRsc::isRscEnFlagDeathMotion(u32 id) const { return _gfbrs::isRscEnFlagDeathMotion(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnWeaponNum1(u32 id) const { return _gfbrs::getRscEnWeaponNum1(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnWeaponNum2(u32 id) const { return _gfbrs::getRscEnWeaponNum2(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnWeaponNum3(u32 id) const { return _gfbrs::getRscEnWeaponNum3(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnWeaponNum4(u32 id) const { return _gfbrs::getRscEnWeaponNum4(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnWeaponNum5(u32 id) const { return _gfbrs::getRscEnWeaponNum5(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnMemorySlot(u32 id) const { return _gfbrs::getRscEnMemorySlot(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnRace(u32 id) const { return _gfbrs::getRscEnRace(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnDrType(u32 id) const { return _gfbrs::getRscEnDrType(*m_rscEn, id); }

s32 GfBdatRsc::getRscEnGoldDivideRev(u32 id) const { return _gfbrs::getRscEnGoldDivideRev(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnFootStep(u32 id) const { return _gfbrs::getRscEnFootStep(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnFootStepEffect(u32 id) const { return _gfbrs::getRscEnFootStepEffect(*m_rscEn, id); }

s32 GfBdatRsc::getRscEnRotateX(u32 id) const { return _gfbrs::getRscEnRotateX(*m_rscEn, id); }

s32 GfBdatRsc::getRscEnRotateY(u32 id) const { return _gfbrs::getRscEnRotateY(*m_rscEn, id); }

s32 GfBdatRsc::getRscEnRotateZ(u32 id) const { return _gfbrs::getRscEnRotateZ(*m_rscEn, id); }

s32 GfBdatRsc::getRscEnRotateDeg(u32 id) const { return _gfbrs::getRscEnRotateDeg(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnRotEffScale(u32 id) const { return _gfbrs::getRscEnRotEffScale(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnExtraParts1(u32 id) const { return _gfbrs::getRscEnExtraParts1(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnExtraParts2(u32 id) const { return _gfbrs::getRscEnExtraParts2(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnExtraParts3(u32 id) const { return _gfbrs::getRscEnExtraParts3(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnExtraParts4(u32 id) const { return _gfbrs::getRscEnExtraParts4(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnDeadSeNum(u32 id) const { return _gfbrs::getRscEnDeadSeNum(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnWeaponNum(u32 resource, u32 weapon) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbrs::getRscEnWeaponNum1, _gfbrs::getRscEnWeaponNum2, _gfbrs::getRscEnWeaponNum3, _gfbrs::getRscEnWeaponNum4, _gfbrs::getRscEnWeaponNum5};
  return getters[weapon](*m_rscEn, resource);
}

u32 GfBdatRsc::getRscEnExtraParts(u32 resource, u32 part) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbrs::getRscEnExtraParts1, _gfbrs::getRscEnExtraParts2, _gfbrs::getRscEnExtraParts3, _gfbrs::getRscEnExtraParts4, nullptr, nullptr};
  return getters[part](*m_rscEn, resource);
}

const char *GfBdatRsc::getRscEnRotateBone(u32 id) const { return _gfbrs::getRscEnRotateBone(*m_rscEn, id); }

u32 GfBdatRsc::getRscEnGenusStart() const { return Bdat::getIdTop(m_rscEnGenus->unknown00); }

u32 GfBdatRsc::getRscEnGenusEnd() const { return Bdat::getIdTop(m_rscEnGenus->unknown00) + Bdat::getIdCount(m_rscEnGenus->unknown00); }

u32 GfBdatRsc::getRscEnGenusNAME(u32 id) const { return _gfbrs::getRscEnGenusNAME(*m_rscEnGenus, id); }

u32 GfBdatRsc::getRscEnGenusCAPTION(u32 id) const { return _gfbrs::getRscEnGenusCAPTION(*m_rscEnGenus, id); }

bool GfBdatRsc::isRscEnGenusFlaggimmicktype(u32 id) const { return _gfbrs::isRscEnGenusFlaggimmicktype(*m_rscEnGenus, id); }

u32 GfBdatRsc::getRscEnUndStart() const { return Bdat::getIdTop(m_rscEnUnd->unknown00); }

u32 GfBdatRsc::getRscEnUndEnd() const { return Bdat::getIdTop(m_rscEnUnd->unknown00) + Bdat::getIdCount(m_rscEnUnd->unknown00); }

bool GfBdatRsc::isRscEnUndFlagUndX(u32 id) const { return _gfbrs::isRscEnUndFlagUndX(*m_rscEnUnd, id); }

bool GfBdatRsc::isRscEnUndFlagUndZ(u32 id) const { return _gfbrs::isRscEnUndFlagUndZ(*m_rscEnUnd, id); }

s32 GfBdatRsc::getRscEnUndUndMinX(u32 id) const { return _gfbrs::getRscEnUndUndMinX(*m_rscEnUnd, id); }

s32 GfBdatRsc::getRscEnUndUndMaxX(u32 id) const { return _gfbrs::getRscEnUndUndMaxX(*m_rscEnUnd, id); }

s32 GfBdatRsc::getRscEnUndUndMinZ(u32 id) const { return _gfbrs::getRscEnUndUndMinZ(*m_rscEnUnd, id); }

s32 GfBdatRsc::getRscEnUndUndMaxZ(u32 id) const { return _gfbrs::getRscEnUndUndMaxZ(*m_rscEnUnd, id); }

u32 GfBdatRsc::getRscEnUndUndDeg(u32 id) const { return _gfbrs::getRscEnUndUndDeg(*m_rscEnUnd, id); }

u32 GfBdatRsc::getRscNpcListStart() const { return Bdat::getIdTop(m_rscNpcList->unknown00); }

u32 GfBdatRsc::getRscNpcListEnd() const { return Bdat::getIdTop(m_rscNpcList->unknown00) + Bdat::getIdCount(m_rscNpcList->unknown00); }

const char *GfBdatRsc::getRscNpcListModel(u32 id) const { return _gfbrs::getRscNpcListModel(*m_rscNpcList, id); }

const char *GfBdatRsc::getRscNpcListMotion(u32 id) const { return _gfbrs::getRscNpcListMotion(*m_rscNpcList, id); }

const char *GfBdatRsc::getRscNpcListAddMotion(u32 id) const { return _gfbrs::getRscNpcListAddMotion(*m_rscNpcList, id); }

const char *GfBdatRsc::getRscNpcListComp_Eff(u32 id) const { return _gfbrs::getRscNpcListComp_Eff(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListCollisionId(u32 id) const { return _gfbrs::getRscNpcListCollisionId(*m_rscNpcList, id); }

const char *GfBdatRsc::getRscNpcListSE(u32 id) const { return _gfbrs::getRscNpcListSE(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListSeEnv(u32 id) const { return _gfbrs::getRscNpcListSeEnv(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListRace(u32 id) const { return _gfbrs::getRscNpcListRace(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListFootStep(u32 id) const { return _gfbrs::getRscNpcListFootStep(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListFootStepEffect(u32 id) const { return _gfbrs::getRscNpcListFootStepEffect(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListRoots(u32 id) const { return _gfbrs::getRscNpcListRoots(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListGender(u32 id) const { return _gfbrs::getRscNpcListGender(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListName(u32 id) const { return _gfbrs::getRscNpcListName(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListOffsetID(u32 id) const { return _gfbrs::getRscNpcListOffsetID(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListEyeRot(u32 id) const { return _gfbrs::getRscNpcListEyeRot(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts1(u32 id) const { return _gfbrs::getRscNpcListExtraParts1(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts2(u32 id) const { return _gfbrs::getRscNpcListExtraParts2(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts3(u32 id) const { return _gfbrs::getRscNpcListExtraParts3(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts4(u32 id) const { return _gfbrs::getRscNpcListExtraParts4(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts5(u32 id) const { return _gfbrs::getRscNpcListExtraParts5(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts6(u32 id) const { return _gfbrs::getRscNpcListExtraParts6(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListScale(u32 id) const { return _gfbrs::getRscNpcListScale(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListEventAsset(u32 id) const { return _gfbrs::getRscNpcListEventAsset(*m_rscNpcList, id); }

u32 GfBdatRsc::getRscNpcListExtraParts(u32 npc, u32 part) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbrs::getRscNpcListExtraParts1,
                                                              _gfbrs::getRscNpcListExtraParts2,
                                                              _gfbrs::getRscNpcListExtraParts3,
                                                              _gfbrs::getRscNpcListExtraParts4,
                                                              _gfbrs::getRscNpcListExtraParts5,
                                                              _gfbrs::getRscNpcListExtraParts6};
  return getters[part](*m_rscNpcList, npc);
}

u32 GfBdatRsc::getRscMobListStart() const { return Bdat::getIdTop(m_rscMobList->unknown00); }

u32 GfBdatRsc::getRscMobListEnd() const { return Bdat::getIdTop(m_rscMobList->unknown00) + Bdat::getIdCount(m_rscMobList->unknown00); }

const char *GfBdatRsc::getRscMobListModel(u32 id) const { return _gfbrs::getRscMobListModel(*m_rscMobList, id); }

const char *GfBdatRsc::getRscMobListMotion(u32 id) const { return _gfbrs::getRscMobListMotion(*m_rscMobList, id); }

const char *GfBdatRsc::getRscMobListAddMotion(u32 id) const { return _gfbrs::getRscMobListAddMotion(*m_rscMobList, id); }

const char *GfBdatRsc::getRscMobListComp_Eff(u32 id) const { return _gfbrs::getRscMobListComp_Eff(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListCollisionId(u32 id) const { return _gfbrs::getRscMobListCollisionId(*m_rscMobList, id); }

const char *GfBdatRsc::getRscMobListSE(u32 id) const { return _gfbrs::getRscMobListSE(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListSeEnv(u32 id) const { return _gfbrs::getRscMobListSeEnv(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListRace(u32 id) const { return _gfbrs::getRscMobListRace(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListFootStep(u32 id) const { return _gfbrs::getRscMobListFootStep(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListFootStepEffect(u32 id) const { return _gfbrs::getRscMobListFootStepEffect(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListOffsetID(u32 id) const { return _gfbrs::getRscMobListOffsetID(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts1(u32 id) const { return _gfbrs::getRscMobListExtraParts1(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts2(u32 id) const { return _gfbrs::getRscMobListExtraParts2(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts3(u32 id) const { return _gfbrs::getRscMobListExtraParts3(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts4(u32 id) const { return _gfbrs::getRscMobListExtraParts4(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts5(u32 id) const { return _gfbrs::getRscMobListExtraParts5(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts6(u32 id) const { return _gfbrs::getRscMobListExtraParts6(*m_rscMobList, id); }

u32 GfBdatRsc::getRscMobListExtraParts(u32 id, u32 part) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbrs::getRscMobListExtraParts1,
                                                              _gfbrs::getRscMobListExtraParts2,
                                                              _gfbrs::getRscMobListExtraParts3,
                                                              _gfbrs::getRscMobListExtraParts4,
                                                              _gfbrs::getRscMobListExtraParts5,
                                                              _gfbrs::getRscMobListExtraParts6};
  return getters[part](*m_rscMobList, id);
}

u32 GfBdatRsc::getRSC_MapObjListStart() const { return Bdat::getIdTop(m_RSC_MapObjList->unknown00); }

u32 GfBdatRsc::getRSC_MapObjListEnd() const { return Bdat::getIdTop(m_RSC_MapObjList->unknown00) + Bdat::getIdCount(m_RSC_MapObjList->unknown00); }

const char *GfBdatRsc::getRSC_MapObjListModel(u32 id) const { return _gfbrs::getRSC_MapObjListModel(*m_RSC_MapObjList, id); }

const char *GfBdatRsc::getRSC_MapObjListMotion(u32 id) const { return _gfbrs::getRSC_MapObjListMotion(*m_RSC_MapObjList, id); }

const char *GfBdatRsc::getRSC_MapObjListComp_Eff(u32 id) const { return _gfbrs::getRSC_MapObjListComp_Eff(*m_RSC_MapObjList, id); }

const char *GfBdatRsc::getRSC_MapObjListSE(u32 id) const { return _gfbrs::getRSC_MapObjListSE(*m_RSC_MapObjList, id); }

u32 GfBdatRsc::getRSC_MapObjListSeEnv(u32 id) const { return _gfbrs::getRSC_MapObjListSeEnv(*m_RSC_MapObjList, id); }

bool GfBdatRsc::isRSC_MapObjListflagBigObj(u32 id) const { return _gfbrs::isRSC_MapObjListflagBigObj(*m_RSC_MapObjList, id); }

u32 GfBdatRsc::getRSC_MapObjListExtraParts1(u32 id) const { return _gfbrs::getRSC_MapObjListExtraParts1(*m_RSC_MapObjList, id); }

u32 GfBdatRsc::getRSC_TboxListStart() const { return Bdat::getIdTop(m_RSC_TboxList->unknown00); }

u32 GfBdatRsc::getRSC_TboxListEnd() const { return Bdat::getIdTop(m_RSC_TboxList->unknown00) + Bdat::getIdCount(m_RSC_TboxList->unknown00); }

const char *GfBdatRsc::getRSC_TboxListModel(u32 id) const { return _gfbrs::getRSC_TboxListModel(*m_RSC_TboxList, id); }

const char *GfBdatRsc::getRSC_TboxListMotion(u32 id) const { return _gfbrs::getRSC_TboxListMotion(*m_RSC_TboxList, id); }

u32 GfBdatRsc::getRSC_PcWpnStart() const { return Bdat::getIdTop(m_RSC_PcWpn->unknown00); }

u32 GfBdatRsc::getRSC_PcWpnEnd() const { return Bdat::getIdTop(m_RSC_PcWpn->unknown00) + Bdat::getIdCount(m_RSC_PcWpn->unknown00); }

const char *GfBdatRsc::getRSC_PcWpnModel(u32 id) const { return _gfbrs::getRSC_PcWpnModel(*m_RSC_PcWpn, id); }

const char *GfBdatRsc::getRSC_PcWpnMotion(u32 id) const { return _gfbrs::getRSC_PcWpnMotion(*m_RSC_PcWpn, id); }

u32 GfBdatRsc::getRSC_PcWpnMenuImageID(u32 id) const { return _gfbrs::getRSC_PcWpnMenuImageID(*m_RSC_PcWpn, id); }

u32 GfBdatRsc::getRSC_PcWpnMountStart() const { return Bdat::getIdTop(m_RSC_PcWpnMount->unknown00); }

u32 GfBdatRsc::getRSC_PcWpnMountEnd() const { return Bdat::getIdTop(m_RSC_PcWpnMount->unknown00) + Bdat::getIdCount(m_RSC_PcWpnMount->unknown00); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn01rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn01rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn01rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn01rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn02rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn02rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn02rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn02rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn04rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn04rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn04rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn04rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn06rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn06rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn06rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn06rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn08rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn08rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn08rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn08rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn11rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn11rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn11rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn11rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn13rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn13rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn13rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn13rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn14rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn14rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn14rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn14rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn15rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn15rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn15rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn15rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn17rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn17rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn17rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn17rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn18rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn18rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn18rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn18rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn19rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn19rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn19rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn19rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn21rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn21rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn21rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn21rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25lOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26rIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26rOut(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26lIn(*m_RSC_PcWpnMount, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26lOut(*m_RSC_PcWpnMount, id); }

u32 GfBdatRsc::getRscEnWpnStart() const { return Bdat::getIdTop(m_rscEnWpn->unknown00); }

u32 GfBdatRsc::getRscEnWpnEnd() const { return Bdat::getIdTop(m_rscEnWpn->unknown00) + Bdat::getIdCount(m_rscEnWpn->unknown00); }

const char *GfBdatRsc::getRscEnWpnModel(u32 id) const { return _gfbrs::getRscEnWpnModel(*m_rscEnWpn, id); }

u32 GfBdatRsc::getRscEnWpnScale(u32 id) const { return _gfbrs::getRscEnWpnScale(*m_rscEnWpn, id); }

const char *GfBdatRsc::getRscEnWpnMotion(u32 id) const { return _gfbrs::getRscEnWpnMotion(*m_rscEnWpn, id); }

const char *GfBdatRsc::getRscEnWpnMtpInChara(u32 id) const { return _gfbrs::getRscEnWpnMtpInChara(*m_rscEnWpn, id); }

const char *GfBdatRsc::getRscEnWpnMtpInWpn(u32 id) const { return _gfbrs::getRscEnWpnMtpInWpn(*m_rscEnWpn, id); }

const char *GfBdatRsc::getRscEnWpnMtpOutChara(u32 id) const { return _gfbrs::getRscEnWpnMtpOutChara(*m_rscEnWpn, id); }

const char *GfBdatRsc::getRscEnWpnMtpOutWpn(u32 id) const { return _gfbrs::getRscEnWpnMtpOutWpn(*m_rscEnWpn, id); }

u32 GfBdatRsc::getRscNpcWpnStart() const { return Bdat::getIdTop(m_rscNpcWpn->unknown00); }

u32 GfBdatRsc::getRscNpcWpnEnd() const { return Bdat::getIdTop(m_rscNpcWpn->unknown00) + Bdat::getIdCount(m_rscNpcWpn->unknown00); }

const char *GfBdatRsc::getRscNpcWpnModel(u32 id) const { return _gfbrs::getRscNpcWpnModel(*m_rscNpcWpn, id); }

const char *GfBdatRsc::getRscNpcWpnMotion(u32 id) const { return _gfbrs::getRscNpcWpnMotion(*m_rscNpcWpn, id); }

u32 GfBdatRsc::getDriverParamStart() const { return Bdat::getIdTop(m_driverParam->unknown00); }

u32 GfBdatRsc::getDriverParamEnd() const { return Bdat::getIdTop(m_driverParam->unknown00) + Bdat::getIdCount(m_driverParam->unknown00); }

u32 GfBdatRsc::getDriverParamExtMountNpc(u32 id) const { return _gfbrs::getDriverParamExtMountNpc(*m_driverParam, id); }

const char *GfBdatRsc::getDriverParamExtMountBone(u32 id) const { return _gfbrs::getDriverParamExtMountBone(*m_driverParam, id); }

u32 GfBdatRsc::getDriverParamExtMountCond(u32 id) const { return _gfbrs::getDriverParamExtMountCond(*m_driverParam, id); }

u32 GfBdatRsc::getVoiceTableStart() const { return Bdat::getIdTop(m_voiceTable->unknown00); }

u32 GfBdatRsc::getVoiceTableEnd() const { return Bdat::getIdTop(m_voiceTable->unknown00) + Bdat::getIdCount(m_voiceTable->unknown00); }

const char *GfBdatRsc::getVoiceTableDriver1(u32 id) const { return _gfbrs::getVoiceTableDriver1(*m_voiceTable, id); }

const char *GfBdatRsc::getVoiceTableDriver2(u32 id) const { return _gfbrs::getVoiceTableDriver2(*m_voiceTable, id); }

const char *GfBdatRsc::getVoiceTableDriver3(u32 id) const { return _gfbrs::getVoiceTableDriver3(*m_voiceTable, id); }

const char *GfBdatRsc::getVoiceTableDriver4(u32 id) const { return _gfbrs::getVoiceTableDriver4(*m_voiceTable, id); }

const char *GfBdatRsc::getVoiceTableDriver5(u32 id) const { return _gfbrs::getVoiceTableDriver5(*m_voiceTable, id); }

const char *GfBdatRsc::getVoiceTableDriver6(u32 id) const { return _gfbrs::getVoiceTableDriver6(*m_voiceTable, id); }

u32 GfBdatRsc::getVoiceTableBladeStart() const { return Bdat::getIdTop(m_voiceTableBlade->unknown00); }

u32 GfBdatRsc::getVoiceTableBladeEnd() const { return Bdat::getIdTop(m_voiceTableBlade->unknown00) + Bdat::getIdCount(m_voiceTableBlade->unknown00); }

const char *GfBdatRsc::getVoiceTableBladeBlade1(u32 id) const { return _gfbrs::getVoiceTableBladeBlade1(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade2(u32 id) const { return _gfbrs::getVoiceTableBladeBlade2(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade3(u32 id) const { return _gfbrs::getVoiceTableBladeBlade3(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade4(u32 id) const { return _gfbrs::getVoiceTableBladeBlade4(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade5(u32 id) const { return _gfbrs::getVoiceTableBladeBlade5(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade6(u32 id) const { return _gfbrs::getVoiceTableBladeBlade6(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade7(u32 id) const { return _gfbrs::getVoiceTableBladeBlade7(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade8(u32 id) const { return _gfbrs::getVoiceTableBladeBlade8(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade9(u32 id) const { return _gfbrs::getVoiceTableBladeBlade9(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade10(u32 id) const { return _gfbrs::getVoiceTableBladeBlade10(*m_voiceTableBlade, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade11(u32 id) const { return _gfbrs::getVoiceTableBladeBlade11(*m_voiceTableBlade, id); }

u32 GfBdatRsc::getVoiceTableRareStart() const { return Bdat::getIdTop(m_voiceTableRare->unknown00); }

u32 GfBdatRsc::getVoiceTableRareEnd() const { return Bdat::getIdTop(m_voiceTableRare->unknown00) + Bdat::getIdCount(m_voiceTableRare->unknown00); }

const char *GfBdatRsc::getVoiceTableRareRareBlade1(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade1(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade2(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade2(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade3(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade3(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade4(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade4(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade5(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade5(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade6(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade6(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade7(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade7(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade8(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade8(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade9(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade9(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade10(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade10(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade11(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade11(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade12(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade12(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade13(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade13(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade14(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade14(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade15(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade15(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade16(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade16(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade17(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade17(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade18(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade18(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade19(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade19(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade20(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade20(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade21(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade21(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade22(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade22(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade23(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade23(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade24(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade24(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade25(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade25(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade26(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade26(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade27(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade27(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade28(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade28(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade29(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade29(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade30(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade30(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade31(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade31(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade32(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade32(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade33(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade33(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade34(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade34(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade35(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade35(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade36(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade36(*m_voiceTableRare, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade37(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade37(*m_voiceTableRare, id); }

u32 GfBdatRsc::getVoiceTableCommonStart() const { return Bdat::getIdTop(m_voiceTableCommon->unknown00); }

u32 GfBdatRsc::getVoiceTableCommonEnd() const { return Bdat::getIdTop(m_voiceTableCommon->unknown00) + Bdat::getIdCount(m_voiceTableCommon->unknown00); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade1(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade1(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade2(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade2(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade3(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade3(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade4(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade4(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade5(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade5(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade6(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade6(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade7(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade7(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade8(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade8(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade9(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade9(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade10(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade10(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade11(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade11(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade12(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade12(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade13(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade13(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade14(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade14(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade15(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade15(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade16(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade16(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade17(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade17(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade18(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade18(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade19(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade19(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade20(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade20(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade21(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade21(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade22(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade22(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade23(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade23(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade24(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade24(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade25(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade25(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade26(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade26(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade27(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade27(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade28(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade28(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade29(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade29(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade30(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade30(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade31(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade31(*m_voiceTableCommon, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade32(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade32(*m_voiceTableCommon, id); }

u32 GfBdatRsc::getFLD_actorSEStart() const { return Bdat::getIdTop(m_FLD_actorSE->unknown00); }

u32 GfBdatRsc::getFLD_actorSEEnd() const { return Bdat::getIdTop(m_FLD_actorSE->unknown00) + Bdat::getIdCount(m_FLD_actorSE->unknown00); }

const char *GfBdatRsc::getFLD_actorSELOD(u32 id) const { return _gfbrs::getFLD_actorSELOD(*m_FLD_actorSE, id); }

u32 GfBdatRsc::getFLD_actorSEse_type(u32 id) const { return _gfbrs::getFLD_actorSEse_type(*m_FLD_actorSE, id); }

u32 GfBdatRsc::getFLD_actorSEseName(u32 id) const { return _gfbrs::getFLD_actorSEseName(*m_FLD_actorSE, id); }

f32 GfBdatRsc::getFLD_actorSEmax_volume_Dist(u32 id) const { return _gfbrs::getFLD_actorSEmax_volume_Dist(*m_FLD_actorSE, id); }

f32 GfBdatRsc::getFLD_actorSEmin_volume_Dist(u32 id) const { return _gfbrs::getFLD_actorSEmin_volume_Dist(*m_FLD_actorSE, id); }

u32 GfBdatRsc::getFLD_actorSEvolumeMAX(u32 id) const { return _gfbrs::getFLD_actorSEvolumeMAX(*m_FLD_actorSE, id); }

u32 GfBdatRsc::getFLD_actorSEvolumeMIN(u32 id) const { return _gfbrs::getFLD_actorSEvolumeMIN(*m_FLD_actorSE, id); }

f32 GfBdatRsc::getFLD_actorSEoffsetX(u32 id) const { return _gfbrs::getFLD_actorSEoffsetX(*m_FLD_actorSE, id); }

f32 GfBdatRsc::getFLD_actorSEoffsetY(u32 id) const { return _gfbrs::getFLD_actorSEoffsetY(*m_FLD_actorSE, id); }

f32 GfBdatRsc::getFLD_actorSEoffsetZ(u32 id) const { return _gfbrs::getFLD_actorSEoffsetZ(*m_FLD_actorSE, id); }

} // namespace gf
