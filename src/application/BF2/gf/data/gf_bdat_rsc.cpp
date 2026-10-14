#include "gf/data/gf_bdat_rsc.h"
#include "bdat.h"

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

void initRscEnDebugName(const CBdatWrapper &wrapper) { s_members[RscEnDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getRscEnDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnDebugName], id, 7).valueString;
}

void initRscEnTypeFamily(const CBdatWrapper &wrapper) { s_members[RscEnTypeFamily] = Bdat::getMember(wrapper.data, "TypeFamily"); }

u32 getRscEnTypeFamily(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTypeFamily] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTypeFamily], id, 1).valueU8;
}

void initRscEnTypeGenus(const CBdatWrapper &wrapper) { s_members[RscEnTypeGenus] = Bdat::getMember(wrapper.data, "TypeGenus"); }

u32 getRscEnTypeGenus(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTypeGenus] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTypeGenus], id, 1).valueU8;
}

void initRscEnActType(const CBdatWrapper &wrapper) { s_members[RscEnActType] = Bdat::getMember(wrapper.data, "ActType"); }

u32 getRscEnActType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnActType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnActType], id, 1).valueU8;
}

void initRscEnFlyHeight(const CBdatWrapper &wrapper) { s_members[RscEnFlyHeight] = Bdat::getMember(wrapper.data, "FlyHeight"); }

s32 getRscEnFlyHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlyHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFlyHeight], id, 5).valueS16;
}

void initRscEnFldMoveType(const CBdatWrapper &wrapper) { s_members[RscEnFldMoveType] = Bdat::getMember(wrapper.data, "FldMoveType"); }

u32 getRscEnFldMoveType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFldMoveType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFldMoveType], id, 1).valueU8;
}

void initRscEnMaterial(const CBdatWrapper &wrapper) { s_members[RscEnMaterial] = Bdat::getMember(wrapper.data, "Material"); }

u32 getRscEnMaterial(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnMaterial] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnMaterial], id, 1).valueU8;
}

void initRscEnProxyID(const CBdatWrapper &wrapper) { s_members[RscEnProxyID] = Bdat::getMember(wrapper.data, "ProxyID"); }

u32 getRscEnProxyID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnProxyID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnProxyID], id, 1).valueU8;
}

void initRscEnEnRadius(const CBdatWrapper &wrapper) { s_members[RscEnEnRadius] = Bdat::getMember(wrapper.data, "EnRadius"); }

u32 getRscEnEnRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEnRadius] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnEnRadius], id, 1).valueU8;
}

void initRscEnEnRadius2(const CBdatWrapper &wrapper) { s_members[RscEnEnRadius2] = Bdat::getMember(wrapper.data, "EnRadius2"); }

u32 getRscEnEnRadius2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEnRadius2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnEnRadius2], id, 1).valueU8;
}

void initRscEnChestHeight(const CBdatWrapper &wrapper) { s_members[RscEnChestHeight] = Bdat::getMember(wrapper.data, "ChestHeight"); }

u32 getRscEnChestHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnChestHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnChestHeight], id, 2).valueU16;
}

void initRscEnChestHeight2(const CBdatWrapper &wrapper) { s_members[RscEnChestHeight2] = Bdat::getMember(wrapper.data, "ChestHeight2"); }

u32 getRscEnChestHeight2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnChestHeight2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnChestHeight2], id, 2).valueU16;
}

void initRscEnBallRadius(const CBdatWrapper &wrapper) { s_members[RscEnBallRadius] = Bdat::getMember(wrapper.data, "BallRadius"); }

f32 getRscEnBallRadius(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[RscEnBallRadius] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[RscEnBallRadius], id, 8).valueF32;
  }

  return value;
}

void initRscEnBallHeight(const CBdatWrapper &wrapper) { s_members[RscEnBallHeight] = Bdat::getMember(wrapper.data, "BallHeight"); }

f32 getRscEnBallHeight(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[RscEnBallHeight] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[RscEnBallHeight], id, 8).valueF32;
  }

  return value;
}

void initRscEnCharColli(const CBdatWrapper &wrapper) { s_members[RscEnCharColli] = Bdat::getMember(wrapper.data, "CharColli"); }

f32 getRscEnCharColli(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[RscEnCharColli] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[RscEnCharColli], id, 8).valueF32;
  }

  return value;
}

void initRscEnoffsetID(const CBdatWrapper &wrapper) { s_members[RscEnoffsetID] = Bdat::getMember(wrapper.data, "offsetID"); }

u32 getRscEnoffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnoffsetID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnoffsetID], id, 2).valueU16;
}

void initRscEnEyeRot(const CBdatWrapper &wrapper) { s_members[RscEnEyeRot] = Bdat::getMember(wrapper.data, "EyeRot"); }

u32 getRscEnEyeRot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEyeRot] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnEyeRot], id, 1).valueU8;
}

void initRscEnSearchBaseBone(const CBdatWrapper &wrapper) { s_members[RscEnSearchBaseBone] = Bdat::getMember(wrapper.data, "SearchBaseBone"); }

const char *getRscEnSearchBaseBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnSearchBaseBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnSearchBaseBone], id, 7).valueString;
}

void initRscEnCenterBone(const CBdatWrapper &wrapper) { s_members[RscEnCenterBone] = Bdat::getMember(wrapper.data, "CenterBone"); }

const char *getRscEnCenterBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnCenterBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnCenterBone], id, 7).valueString;
}

void initRscEnCamBone(const CBdatWrapper &wrapper) { s_members[RscEnCamBone] = Bdat::getMember(wrapper.data, "CamBone"); }

const char *getRscEnCamBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnCamBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnCamBone], id, 7).valueString;
}

void initRscEnFrontAngle(const CBdatWrapper &wrapper) { s_members[RscEnFrontAngle] = Bdat::getMember(wrapper.data, "FrontAngle"); }

u32 getRscEnFrontAngle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFrontAngle] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFrontAngle], id, 1).valueU8;
}

void initRscEnTurnAngleSmall(const CBdatWrapper &wrapper) { s_members[RscEnTurnAngleSmall] = Bdat::getMember(wrapper.data, "TurnAngleSmall"); }

u32 getRscEnTurnAngleSmall(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTurnAngleSmall] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTurnAngleSmall], id, 1).valueU8;
}

void initRscEnTurnAngleBig(const CBdatWrapper &wrapper) { s_members[RscEnTurnAngleBig] = Bdat::getMember(wrapper.data, "TurnAngleBig"); }

u32 getRscEnTurnAngleBig(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnTurnAngleBig] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnTurnAngleBig], id, 1).valueU8;
}

void initRscEnUnduration(const CBdatWrapper &wrapper) { s_members[RscEnUnduration] = Bdat::getMember(wrapper.data, "Unduration"); }

u32 getRscEnUnduration(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUnduration] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUnduration], id, 1).valueU8;
}

void initRscEnModel(const CBdatWrapper &wrapper) { s_members[RscEnModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRscEnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnModel] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnModel], id, 7).valueString;
}

void initRscEnChrFile(const CBdatWrapper &wrapper) { s_members[RscEnChrFile] = Bdat::getMember(wrapper.data, "ChrFile"); }

const char *getRscEnChrFile(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnChrFile] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnChrFile], id, 7).valueString;
}

void initRscEnMotion(const CBdatWrapper &wrapper) { s_members[RscEnMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRscEnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnMotion], id, 7).valueString;
}

void initRscEnRefMotion(const CBdatWrapper &wrapper) { s_members[RscEnRefMotion] = Bdat::getMember(wrapper.data, "RefMotion"); }

const char *getRscEnRefMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRefMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnRefMotion], id, 7).valueString;
}

void initRscEnEffectPack(const CBdatWrapper &wrapper) { s_members[RscEnEffectPack] = Bdat::getMember(wrapper.data, "EffectPack"); }

const char *getRscEnEffectPack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnEffectPack] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnEffectPack], id, 7).valueString;
}

void initRscEnLoopEffect(const CBdatWrapper &wrapper) { s_members[RscEnLoopEffect] = Bdat::getMember(wrapper.data, "LoopEffect"); }

const char *getRscEnLoopEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnLoopEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnLoopEffect], id, 7).valueString;
}

void initRscEnSePack(const CBdatWrapper &wrapper) { s_members[RscEnSePack] = Bdat::getMember(wrapper.data, "SePack"); }

const char *getRscEnSePack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnSePack] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnSePack], id, 7).valueString;
}

void initRscEnVoice(const CBdatWrapper &wrapper) { s_members[RscEnVoice] = Bdat::getMember(wrapper.data, "Voice"); }

const char *getRscEnVoice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnVoice] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnVoice], id, 7).valueString;
}

void initRscEnVoiceEx(const CBdatWrapper &wrapper) { s_members[RscEnVoiceEx] = Bdat::getMember(wrapper.data, "VoiceEx"); }

u32 getRscEnVoiceEx(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnVoiceEx] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnVoiceEx], id, 1).valueU8;
}

void initRscEnClipEvent(const CBdatWrapper &wrapper) { s_members[RscEnClipEvent] = Bdat::getMember(wrapper.data, "ClipEvent"); }

const char *getRscEnClipEvent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnClipEvent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnClipEvent], id, 7).valueString;
}

void initRscEnComp_Eff(const CBdatWrapper &wrapper) { s_members[RscEnComp_Eff] = Bdat::getMember(wrapper.data, "Comp_Eff"); }

const char *getRscEnComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnComp_Eff], id, 7).valueString;
}

void initRscEnComp_Se(const CBdatWrapper &wrapper) { s_members[RscEnComp_Se] = Bdat::getMember(wrapper.data, "Comp_Se"); }

const char *getRscEnComp_Se(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnComp_Se] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnComp_Se], id, 7).valueString;
}

void initRscEnComp_Vo(const CBdatWrapper &wrapper) { s_members[RscEnComp_Vo] = Bdat::getMember(wrapper.data, "Comp_Vo"); }

const char *getRscEnComp_Vo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnComp_Vo] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnComp_Vo], id, 7).valueString;
}

void initRscEnFlagNoEcSkip(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoEcSkip] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagNoEcSkipFlag] = Bdat::getMember(wrapper.data, "NoEcSkip");
}

bool isRscEnFlagNoEcSkip(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoEcSkip] == nullptr || s_members[RscEnFlagNoEcSkipFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoEcSkip], id, s_members[RscEnFlagNoEcSkipFlag]) != 0;
}

void initRscEnFlagMap(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagMap] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagMapFlag] = Bdat::getMember(wrapper.data, "Map");
}

bool isRscEnFlagMap(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagMap] == nullptr || s_members[RscEnFlagMapFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagMap], id, s_members[RscEnFlagMapFlag]) != 0;
}

void initRscEnFlagEvt(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagEvt] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagEvtFlag] = Bdat::getMember(wrapper.data, "Evt");
}

bool isRscEnFlagEvt(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagEvt] == nullptr || s_members[RscEnFlagEvtFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagEvt], id, s_members[RscEnFlagEvtFlag]) != 0;
}

void initRscEnFlagNoWinVo(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoWinVo] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagNoWinVoFlag] = Bdat::getMember(wrapper.data, "NoWinVo");
}

bool isRscEnFlagNoWinVo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoWinVo] == nullptr || s_members[RscEnFlagNoWinVoFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoWinVo], id, s_members[RscEnFlagNoWinVoFlag]) != 0;
}

void initRscEnFlagBait(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagBait] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagBaitFlag] = Bdat::getMember(wrapper.data, "Bait");
}

bool isRscEnFlagBait(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagBait] == nullptr || s_members[RscEnFlagBaitFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagBait], id, s_members[RscEnFlagBaitFlag]) != 0;
}

void initRscEnFlagUseSearchBone(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagUseSearchBone] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagUseSearchBoneFlag] = Bdat::getMember(wrapper.data, "UseSearchBone");
}

bool isRscEnFlagUseSearchBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagUseSearchBone] == nullptr || s_members[RscEnFlagUseSearchBoneFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagUseSearchBone], id, s_members[RscEnFlagUseSearchBoneFlag]) != 0;
}

void initRscEnFlagNoVanish(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoVanish] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagNoVanishFlag] = Bdat::getMember(wrapper.data, "NoVanish");
}

bool isRscEnFlagNoVanish(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoVanish] == nullptr || s_members[RscEnFlagNoVanishFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoVanish], id, s_members[RscEnFlagNoVanishFlag]) != 0;
}

void initRscEnFlagNoCamera(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagNoCamera] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagNoCameraFlag] = Bdat::getMember(wrapper.data, "NoCamera");
}

bool isRscEnFlagNoCamera(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagNoCamera] == nullptr || s_members[RscEnFlagNoCameraFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagNoCamera], id, s_members[RscEnFlagNoCameraFlag]) != 0;
}

void initRscEnFlagWeaponDrawDisp(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagWeaponDrawDisp] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagWeaponDrawDispFlag] = Bdat::getMember(wrapper.data, "WeaponDrawDisp");
}

bool isRscEnFlagWeaponDrawDisp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagWeaponDrawDisp] == nullptr || s_members[RscEnFlagWeaponDrawDispFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagWeaponDrawDisp], id, s_members[RscEnFlagWeaponDrawDispFlag]) != 0;
}

void initRscEnFlagJoinAll(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagJoinAll] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagJoinAllFlag] = Bdat::getMember(wrapper.data, "JoinAll");
}

bool isRscEnFlagJoinAll(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagJoinAll] == nullptr || s_members[RscEnFlagJoinAllFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagJoinAll], id, s_members[RscEnFlagJoinAllFlag]) != 0;
}

void initRscEnFlagDeathMotion(const CBdatWrapper &wrapper) {
  s_members[RscEnFlagDeathMotion] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnFlagDeathMotionFlag] = Bdat::getMember(wrapper.data, "DeathMotion");
}

bool isRscEnFlagDeathMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFlagDeathMotion] == nullptr || s_members[RscEnFlagDeathMotionFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnFlagDeathMotion], id, s_members[RscEnFlagDeathMotionFlag]) != 0;
}

void initRscEnWeaponNum1(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum1] = Bdat::getMember(wrapper.data, "WeaponNum1"); }

u32 getRscEnWeaponNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum1], id, 2).valueU16;
}

void initRscEnWeaponNum2(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum2] = Bdat::getMember(wrapper.data, "WeaponNum2"); }

u32 getRscEnWeaponNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum2], id, 2).valueU16;
}

void initRscEnWeaponNum3(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum3] = Bdat::getMember(wrapper.data, "WeaponNum3"); }

u32 getRscEnWeaponNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum3], id, 2).valueU16;
}

void initRscEnWeaponNum4(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum4] = Bdat::getMember(wrapper.data, "WeaponNum4"); }

u32 getRscEnWeaponNum4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum4], id, 2).valueU16;
}

void initRscEnWeaponNum5(const CBdatWrapper &wrapper) { s_members[RscEnWeaponNum5] = Bdat::getMember(wrapper.data, "WeaponNum5"); }

u32 getRscEnWeaponNum5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWeaponNum5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWeaponNum5], id, 2).valueU16;
}

void initRscEnMemorySlot(const CBdatWrapper &wrapper) { s_members[RscEnMemorySlot] = Bdat::getMember(wrapper.data, "MemorySlot"); }

u32 getRscEnMemorySlot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnMemorySlot] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnMemorySlot], id, 1).valueU8;
}

void initRscEnRace(const CBdatWrapper &wrapper) { s_members[RscEnRace] = Bdat::getMember(wrapper.data, "Race"); }

u32 getRscEnRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRace] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRace], id, 1).valueU8;
}

void initRscEnDrType(const CBdatWrapper &wrapper) { s_members[RscEnDrType] = Bdat::getMember(wrapper.data, "DrType"); }

u32 getRscEnDrType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnDrType] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnDrType], id, 1).valueU8;
}

void initRscEnGoldDivideRev(const CBdatWrapper &wrapper) { s_members[RscEnGoldDivideRev] = Bdat::getMember(wrapper.data, "GoldDivideRev"); }

s32 getRscEnGoldDivideRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGoldDivideRev] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnGoldDivideRev], id, 4).valueS8;
}

void initRscEnFootStep(const CBdatWrapper &wrapper) { s_members[RscEnFootStep] = Bdat::getMember(wrapper.data, "FootStep"); }

u32 getRscEnFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFootStep] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFootStep], id, 1).valueU8;
}

void initRscEnFootStepEffect(const CBdatWrapper &wrapper) { s_members[RscEnFootStepEffect] = Bdat::getMember(wrapper.data, "FootStepEffect"); }

u32 getRscEnFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnFootStepEffect], id, 1).valueU8;
}

void initRscEnRotateX(const CBdatWrapper &wrapper) { s_members[RscEnRotateX] = Bdat::getMember(wrapper.data, "RotateX"); }

s32 getRscEnRotateX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateX] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateX], id, 4).valueS8;
}

void initRscEnRotateY(const CBdatWrapper &wrapper) { s_members[RscEnRotateY] = Bdat::getMember(wrapper.data, "RotateY"); }

s32 getRscEnRotateY(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateY] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateY], id, 4).valueS8;
}

void initRscEnRotateZ(const CBdatWrapper &wrapper) { s_members[RscEnRotateZ] = Bdat::getMember(wrapper.data, "RotateZ"); }

s32 getRscEnRotateZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateZ] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateZ], id, 4).valueS8;
}

void initRscEnRotateDeg(const CBdatWrapper &wrapper) { s_members[RscEnRotateDeg] = Bdat::getMember(wrapper.data, "RotateDeg"); }

s32 getRscEnRotateDeg(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateDeg] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotateDeg], id, 4).valueS8;
}

void initRscEnRotEffScale(const CBdatWrapper &wrapper) { s_members[RscEnRotEffScale] = Bdat::getMember(wrapper.data, "RotEffScale"); }

u32 getRscEnRotEffScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotEffScale] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnRotEffScale], id, 2).valueU16;
}

void initRscEnExtraParts1(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts1] = Bdat::getMember(wrapper.data, "ExtraParts1"); }

u32 getRscEnExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts1], id, 1).valueU8;
}

void initRscEnExtraParts2(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts2] = Bdat::getMember(wrapper.data, "ExtraParts2"); }

u32 getRscEnExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts2], id, 1).valueU8;
}

void initRscEnExtraParts3(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts3] = Bdat::getMember(wrapper.data, "ExtraParts3"); }

u32 getRscEnExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts3], id, 1).valueU8;
}

void initRscEnExtraParts4(const CBdatWrapper &wrapper) { s_members[RscEnExtraParts4] = Bdat::getMember(wrapper.data, "ExtraParts4"); }

u32 getRscEnExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnExtraParts4], id, 1).valueU8;
}

void initRscEnDeadSeNum(const CBdatWrapper &wrapper) { s_members[RscEnDeadSeNum] = Bdat::getMember(wrapper.data, "DeadSeNum"); }

u32 getRscEnDeadSeNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnDeadSeNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnDeadSeNum], id, 1).valueU8;
}

void initRscEnRotateBone(const CBdatWrapper &wrapper) { s_members[RscEnRotateBone] = Bdat::getMember(wrapper.data, "RotateBone"); }

const char *getRscEnRotateBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnRotateBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnRotateBone], id, 7).valueString;
}

void initRscEnGenusNAME(const CBdatWrapper &wrapper) { s_members[RscEnGenusNAME] = Bdat::getMember(wrapper.data, "NAME"); }

u32 getRscEnGenusNAME(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGenusNAME] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnGenusNAME], id, 1).valueU8;
}

void initRscEnGenusCAPTION(const CBdatWrapper &wrapper) { s_members[RscEnGenusCAPTION] = Bdat::getMember(wrapper.data, "CAPTION"); }

u32 getRscEnGenusCAPTION(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGenusCAPTION] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnGenusCAPTION], id, 1).valueU8;
}

void initRscEnGenusFlaggimmicktype(const CBdatWrapper &wrapper) {
  s_members[RscEnGenusFlaggimmicktype] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnGenusFlaggimmicktypeFlag] = Bdat::getMember(wrapper.data, "gimmicktype");
}

bool isRscEnGenusFlaggimmicktype(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnGenusFlaggimmicktype] == nullptr || s_members[RscEnGenusFlaggimmicktypeFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnGenusFlaggimmicktype], id, s_members[RscEnGenusFlaggimmicktypeFlag]) != 0;
}

void initRscEnUndFlagUndX(const CBdatWrapper &wrapper) {
  s_members[RscEnUndFlagUndX] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnUndFlagUndXFlag] = Bdat::getMember(wrapper.data, "UndX");
}

bool isRscEnUndFlagUndX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndFlagUndX] == nullptr || s_members[RscEnUndFlagUndXFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnUndFlagUndX], id, s_members[RscEnUndFlagUndXFlag]) != 0;
}

void initRscEnUndFlagUndZ(const CBdatWrapper &wrapper) {
  s_members[RscEnUndFlagUndZ] = Bdat::getMember(wrapper.data, "Flag");
  s_members[RscEnUndFlagUndZFlag] = Bdat::getMember(wrapper.data, "UndZ");
}

bool isRscEnUndFlagUndZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndFlagUndZ] == nullptr || s_members[RscEnUndFlagUndZFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RscEnUndFlagUndZ], id, s_members[RscEnUndFlagUndZFlag]) != 0;
}

void initRscEnUndUndMinX(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMinX] = Bdat::getMember(wrapper.data, "UndMinX"); }

s32 getRscEnUndUndMinX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMinX] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMinX], id, 4).valueS8;
}

void initRscEnUndUndMaxX(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMaxX] = Bdat::getMember(wrapper.data, "UndMaxX"); }

s32 getRscEnUndUndMaxX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMaxX] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMaxX], id, 4).valueS8;
}

void initRscEnUndUndMinZ(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMinZ] = Bdat::getMember(wrapper.data, "UndMinZ"); }

s32 getRscEnUndUndMinZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMinZ] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMinZ], id, 4).valueS8;
}

void initRscEnUndUndMaxZ(const CBdatWrapper &wrapper) { s_members[RscEnUndUndMaxZ] = Bdat::getMember(wrapper.data, "UndMaxZ"); }

s32 getRscEnUndUndMaxZ(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndMaxZ] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndMaxZ], id, 4).valueS8;
}

void initRscEnUndUndDeg(const CBdatWrapper &wrapper) { s_members[RscEnUndUndDeg] = Bdat::getMember(wrapper.data, "UndDeg"); }

u32 getRscEnUndUndDeg(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnUndUndDeg] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnUndUndDeg], id, 1).valueU8;
}

void initRscNpcListModel(const CBdatWrapper &wrapper) { s_members[RscNpcListModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRscNpcListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListModel], id, 7).valueString;
}

void initRscNpcListMotion(const CBdatWrapper &wrapper) { s_members[RscNpcListMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRscNpcListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListMotion], id, 7).valueString;
}

void initRscNpcListAddMotion(const CBdatWrapper &wrapper) { s_members[RscNpcListAddMotion] = Bdat::getMember(wrapper.data, "AddMotion"); }

const char *getRscNpcListAddMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListAddMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListAddMotion], id, 7).valueString;
}

void initRscNpcListComp_Eff(const CBdatWrapper &wrapper) { s_members[RscNpcListComp_Eff] = Bdat::getMember(wrapper.data, "Comp_Eff"); }

const char *getRscNpcListComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListComp_Eff], id, 7).valueString;
}

void initRscNpcListCollisionId(const CBdatWrapper &wrapper) { s_members[RscNpcListCollisionId] = Bdat::getMember(wrapper.data, "CollisionId"); }

u32 getRscNpcListCollisionId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListCollisionId] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListCollisionId], id, 2).valueU16;
}

void initRscNpcListSE(const CBdatWrapper &wrapper) { s_members[RscNpcListSE] = Bdat::getMember(wrapper.data, "SE"); }

const char *getRscNpcListSE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListSE] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcListSE], id, 7).valueString;
}

void initRscNpcListSeEnv(const CBdatWrapper &wrapper) { s_members[RscNpcListSeEnv] = Bdat::getMember(wrapper.data, "SeEnv"); }

u32 getRscNpcListSeEnv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListSeEnv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListSeEnv], id, 2).valueU16;
}

void initRscNpcListRace(const CBdatWrapper &wrapper) { s_members[RscNpcListRace] = Bdat::getMember(wrapper.data, "Race"); }

u32 getRscNpcListRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListRace] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListRace], id, 1).valueU8;
}

void initRscNpcListFootStep(const CBdatWrapper &wrapper) { s_members[RscNpcListFootStep] = Bdat::getMember(wrapper.data, "FootStep"); }

u32 getRscNpcListFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListFootStep] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListFootStep], id, 2).valueU16;
}

void initRscNpcListFootStepEffect(const CBdatWrapper &wrapper) {
  s_members[RscNpcListFootStepEffect] = Bdat::getMember(wrapper.data, "FootStepEffect");
}

u32 getRscNpcListFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListFootStepEffect], id, 1).valueU8;
}

void initRscNpcListRoots(const CBdatWrapper &wrapper) { s_members[RscNpcListRoots] = Bdat::getMember(wrapper.data, "Roots"); }

u32 getRscNpcListRoots(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListRoots] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListRoots], id, 1).valueU8;
}

void initRscNpcListGender(const CBdatWrapper &wrapper) { s_members[RscNpcListGender] = Bdat::getMember(wrapper.data, "Gender"); }

u32 getRscNpcListGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListGender] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListGender], id, 1).valueU8;
}

void initRscNpcListName(const CBdatWrapper &wrapper) { s_members[RscNpcListName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getRscNpcListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListName], id, 2).valueU16;
}

void initRscNpcListOffsetID(const CBdatWrapper &wrapper) { s_members[RscNpcListOffsetID] = Bdat::getMember(wrapper.data, "OffsetID"); }

u32 getRscNpcListOffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListOffsetID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListOffsetID], id, 2).valueU16;
}

void initRscNpcListEyeRot(const CBdatWrapper &wrapper) { s_members[RscNpcListEyeRot] = Bdat::getMember(wrapper.data, "EyeRot"); }

u32 getRscNpcListEyeRot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListEyeRot] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListEyeRot], id, 1).valueU8;
}

void initRscNpcListExtraParts1(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts1] = Bdat::getMember(wrapper.data, "ExtraParts1"); }

u32 getRscNpcListExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts1], id, 1).valueU8;
}

void initRscNpcListExtraParts2(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts2] = Bdat::getMember(wrapper.data, "ExtraParts2"); }

u32 getRscNpcListExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts2], id, 1).valueU8;
}

void initRscNpcListExtraParts3(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts3] = Bdat::getMember(wrapper.data, "ExtraParts3"); }

u32 getRscNpcListExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts3], id, 1).valueU8;
}

void initRscNpcListExtraParts4(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts4] = Bdat::getMember(wrapper.data, "ExtraParts4"); }

u32 getRscNpcListExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts4], id, 1).valueU8;
}

void initRscNpcListExtraParts5(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts5] = Bdat::getMember(wrapper.data, "ExtraParts5"); }

u32 getRscNpcListExtraParts5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts5], id, 1).valueU8;
}

void initRscNpcListExtraParts6(const CBdatWrapper &wrapper) { s_members[RscNpcListExtraParts6] = Bdat::getMember(wrapper.data, "ExtraParts6"); }

u32 getRscNpcListExtraParts6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListExtraParts6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListExtraParts6], id, 1).valueU8;
}

void initRscNpcListScale(const CBdatWrapper &wrapper) { s_members[RscNpcListScale] = Bdat::getMember(wrapper.data, "Scale"); }

u32 getRscNpcListScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListScale] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListScale], id, 2).valueU16;
}

void initRscNpcListEventAsset(const CBdatWrapper &wrapper) { s_members[RscNpcListEventAsset] = Bdat::getMember(wrapper.data, "EventAsset"); }

u32 getRscNpcListEventAsset(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcListEventAsset] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscNpcListEventAsset], id, 2).valueU16;
}

void initRscMobListModel(const CBdatWrapper &wrapper) { s_members[RscMobListModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRscMobListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListModel], id, 7).valueString;
}

void initRscMobListMotion(const CBdatWrapper &wrapper) { s_members[RscMobListMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRscMobListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListMotion], id, 7).valueString;
}

void initRscMobListAddMotion(const CBdatWrapper &wrapper) { s_members[RscMobListAddMotion] = Bdat::getMember(wrapper.data, "AddMotion"); }

const char *getRscMobListAddMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListAddMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListAddMotion], id, 7).valueString;
}

void initRscMobListComp_Eff(const CBdatWrapper &wrapper) { s_members[RscMobListComp_Eff] = Bdat::getMember(wrapper.data, "Comp_Eff"); }

const char *getRscMobListComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListComp_Eff], id, 7).valueString;
}

void initRscMobListCollisionId(const CBdatWrapper &wrapper) { s_members[RscMobListCollisionId] = Bdat::getMember(wrapper.data, "CollisionId"); }

u32 getRscMobListCollisionId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListCollisionId] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListCollisionId], id, 2).valueU16;
}

void initRscMobListSE(const CBdatWrapper &wrapper) { s_members[RscMobListSE] = Bdat::getMember(wrapper.data, "SE"); }

const char *getRscMobListSE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListSE] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscMobListSE], id, 7).valueString;
}

void initRscMobListSeEnv(const CBdatWrapper &wrapper) { s_members[RscMobListSeEnv] = Bdat::getMember(wrapper.data, "SeEnv"); }

u32 getRscMobListSeEnv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListSeEnv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListSeEnv], id, 2).valueU16;
}

void initRscMobListRace(const CBdatWrapper &wrapper) { s_members[RscMobListRace] = Bdat::getMember(wrapper.data, "Race"); }

u32 getRscMobListRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListRace] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListRace], id, 1).valueU8;
}

void initRscMobListFootStep(const CBdatWrapper &wrapper) { s_members[RscMobListFootStep] = Bdat::getMember(wrapper.data, "FootStep"); }

u32 getRscMobListFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListFootStep] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListFootStep], id, 2).valueU16;
}

void initRscMobListFootStepEffect(const CBdatWrapper &wrapper) {
  s_members[RscMobListFootStepEffect] = Bdat::getMember(wrapper.data, "FootStepEffect");
}

u32 getRscMobListFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListFootStepEffect], id, 1).valueU8;
}

void initRscMobListOffsetID(const CBdatWrapper &wrapper) { s_members[RscMobListOffsetID] = Bdat::getMember(wrapper.data, "OffsetID"); }

u32 getRscMobListOffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListOffsetID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListOffsetID], id, 2).valueU16;
}

void initRscMobListExtraParts1(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts1] = Bdat::getMember(wrapper.data, "ExtraParts1"); }

u32 getRscMobListExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts1], id, 1).valueU8;
}

void initRscMobListExtraParts2(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts2] = Bdat::getMember(wrapper.data, "ExtraParts2"); }

u32 getRscMobListExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts2], id, 1).valueU8;
}

void initRscMobListExtraParts3(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts3] = Bdat::getMember(wrapper.data, "ExtraParts3"); }

u32 getRscMobListExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts3], id, 1).valueU8;
}

void initRscMobListExtraParts4(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts4] = Bdat::getMember(wrapper.data, "ExtraParts4"); }

u32 getRscMobListExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts4], id, 1).valueU8;
}

void initRscMobListExtraParts5(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts5] = Bdat::getMember(wrapper.data, "ExtraParts5"); }

u32 getRscMobListExtraParts5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts5], id, 1).valueU8;
}

void initRscMobListExtraParts6(const CBdatWrapper &wrapper) { s_members[RscMobListExtraParts6] = Bdat::getMember(wrapper.data, "ExtraParts6"); }

u32 getRscMobListExtraParts6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscMobListExtraParts6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscMobListExtraParts6], id, 1).valueU8;
}

void initRSC_MapObjListModel(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRSC_MapObjListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListModel], id, 7).valueString;
}

void initRSC_MapObjListMotion(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRSC_MapObjListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListMotion], id, 7).valueString;
}

void initRSC_MapObjListComp_Eff(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListComp_Eff] = Bdat::getMember(wrapper.data, "Comp_Eff"); }

const char *getRSC_MapObjListComp_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListComp_Eff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListComp_Eff], id, 7).valueString;
}

void initRSC_MapObjListSE(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListSE] = Bdat::getMember(wrapper.data, "SE"); }

const char *getRSC_MapObjListSE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListSE] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListSE], id, 7).valueString;
}

void initRSC_MapObjListSeEnv(const CBdatWrapper &wrapper) { s_members[RSC_MapObjListSeEnv] = Bdat::getMember(wrapper.data, "SeEnv"); }

u32 getRSC_MapObjListSeEnv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListSeEnv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListSeEnv], id, 2).valueU16;
}

void initRSC_MapObjListflagBigObj(const CBdatWrapper &wrapper) {
  s_members[RSC_MapObjListflagBigObj] = Bdat::getMember(wrapper.data, "flag");
  s_members[RSC_MapObjListflagBigObjFlag] = Bdat::getMember(wrapper.data, "BigObj");
}

bool isRSC_MapObjListflagBigObj(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListflagBigObj] == nullptr || s_members[RSC_MapObjListflagBigObjFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[RSC_MapObjListflagBigObj], id, s_members[RSC_MapObjListflagBigObjFlag]) != 0;
}

void initRSC_MapObjListExtraParts1(const CBdatWrapper &wrapper) {
  s_members[RSC_MapObjListExtraParts1] = Bdat::getMember(wrapper.data, "ExtraParts1");
}

u32 getRSC_MapObjListExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_MapObjListExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RSC_MapObjListExtraParts1], id, 1).valueU8;
}

void initRSC_TboxListModel(const CBdatWrapper &wrapper) { s_members[RSC_TboxListModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRSC_TboxListModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_TboxListModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_TboxListModel], id, 7).valueString;
}

void initRSC_TboxListMotion(const CBdatWrapper &wrapper) { s_members[RSC_TboxListMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRSC_TboxListMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_TboxListMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_TboxListMotion], id, 7).valueString;
}

void initRSC_PcWpnModel(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRSC_PcWpnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnModel], id, 7).valueString;
}

void initRSC_PcWpnMotion(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRSC_PcWpnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMotion], id, 7).valueString;
}

void initRSC_PcWpnMenuImageID(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMenuImageID] = Bdat::getMember(wrapper.data, "MenuImageID"); }

u32 getRSC_PcWpnMenuImageID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMenuImageID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMenuImageID], id, 2).valueU16;
}

void initRSC_PcWpnMountWpn01rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn01rIn] = Bdat::getMember(wrapper.data, "Wpn01rIn"); }

const char *getRSC_PcWpnMountWpn01rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn01rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn01rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn01rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn01rOut] = Bdat::getMember(wrapper.data, "Wpn01rOut"); }

const char *getRSC_PcWpnMountWpn01rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn01rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn01rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn02rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn02rIn] = Bdat::getMember(wrapper.data, "Wpn02rIn"); }

const char *getRSC_PcWpnMountWpn02rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn02rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn02rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn02rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn02rOut] = Bdat::getMember(wrapper.data, "Wpn02rOut"); }

const char *getRSC_PcWpnMountWpn02rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn02rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn02rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03rIn] = Bdat::getMember(wrapper.data, "Wpn03rIn"); }

const char *getRSC_PcWpnMountWpn03rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03rOut] = Bdat::getMember(wrapper.data, "Wpn03rOut"); }

const char *getRSC_PcWpnMountWpn03rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03lIn] = Bdat::getMember(wrapper.data, "Wpn03lIn"); }

const char *getRSC_PcWpnMountWpn03lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn03lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn03lOut] = Bdat::getMember(wrapper.data, "Wpn03lOut"); }

const char *getRSC_PcWpnMountWpn03lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn03lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn03lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn04rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn04rIn] = Bdat::getMember(wrapper.data, "Wpn04rIn"); }

const char *getRSC_PcWpnMountWpn04rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn04rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn04rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn04rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn04rOut] = Bdat::getMember(wrapper.data, "Wpn04rOut"); }

const char *getRSC_PcWpnMountWpn04rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn04rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn04rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05rIn] = Bdat::getMember(wrapper.data, "Wpn05rIn"); }

const char *getRSC_PcWpnMountWpn05rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05rOut] = Bdat::getMember(wrapper.data, "Wpn05rOut"); }

const char *getRSC_PcWpnMountWpn05rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05lIn] = Bdat::getMember(wrapper.data, "Wpn05lIn"); }

const char *getRSC_PcWpnMountWpn05lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn05lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn05lOut] = Bdat::getMember(wrapper.data, "Wpn05lOut"); }

const char *getRSC_PcWpnMountWpn05lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn05lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn05lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn06rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn06rIn] = Bdat::getMember(wrapper.data, "Wpn06rIn"); }

const char *getRSC_PcWpnMountWpn06rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn06rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn06rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn06rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn06rOut] = Bdat::getMember(wrapper.data, "Wpn06rOut"); }

const char *getRSC_PcWpnMountWpn06rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn06rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn06rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07rIn] = Bdat::getMember(wrapper.data, "Wpn07rIn"); }

const char *getRSC_PcWpnMountWpn07rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07rOut] = Bdat::getMember(wrapper.data, "Wpn07rOut"); }

const char *getRSC_PcWpnMountWpn07rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07lIn] = Bdat::getMember(wrapper.data, "Wpn07lIn"); }

const char *getRSC_PcWpnMountWpn07lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn07lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn07lOut] = Bdat::getMember(wrapper.data, "Wpn07lOut"); }

const char *getRSC_PcWpnMountWpn07lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn07lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn07lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn08rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn08rIn] = Bdat::getMember(wrapper.data, "Wpn08rIn"); }

const char *getRSC_PcWpnMountWpn08rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn08rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn08rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn08rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn08rOut] = Bdat::getMember(wrapper.data, "Wpn08rOut"); }

const char *getRSC_PcWpnMountWpn08rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn08rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn08rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09rIn] = Bdat::getMember(wrapper.data, "Wpn09rIn"); }

const char *getRSC_PcWpnMountWpn09rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09rOut] = Bdat::getMember(wrapper.data, "Wpn09rOut"); }

const char *getRSC_PcWpnMountWpn09rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09lIn] = Bdat::getMember(wrapper.data, "Wpn09lIn"); }

const char *getRSC_PcWpnMountWpn09lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn09lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn09lOut] = Bdat::getMember(wrapper.data, "Wpn09lOut"); }

const char *getRSC_PcWpnMountWpn09lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn09lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn09lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10rIn] = Bdat::getMember(wrapper.data, "Wpn10rIn"); }

const char *getRSC_PcWpnMountWpn10rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10rOut] = Bdat::getMember(wrapper.data, "Wpn10rOut"); }

const char *getRSC_PcWpnMountWpn10rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10lIn] = Bdat::getMember(wrapper.data, "Wpn10lIn"); }

const char *getRSC_PcWpnMountWpn10lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn10lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn10lOut] = Bdat::getMember(wrapper.data, "Wpn10lOut"); }

const char *getRSC_PcWpnMountWpn10lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn10lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn10lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn11rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn11rIn] = Bdat::getMember(wrapper.data, "Wpn11rIn"); }

const char *getRSC_PcWpnMountWpn11rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn11rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn11rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn11rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn11rOut] = Bdat::getMember(wrapper.data, "Wpn11rOut"); }

const char *getRSC_PcWpnMountWpn11rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn11rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn11rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12rIn] = Bdat::getMember(wrapper.data, "Wpn12rIn"); }

const char *getRSC_PcWpnMountWpn12rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12rOut] = Bdat::getMember(wrapper.data, "Wpn12rOut"); }

const char *getRSC_PcWpnMountWpn12rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12lIn] = Bdat::getMember(wrapper.data, "Wpn12lIn"); }

const char *getRSC_PcWpnMountWpn12lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn12lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn12lOut] = Bdat::getMember(wrapper.data, "Wpn12lOut"); }

const char *getRSC_PcWpnMountWpn12lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn12lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn12lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn13rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn13rIn] = Bdat::getMember(wrapper.data, "Wpn13rIn"); }

const char *getRSC_PcWpnMountWpn13rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn13rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn13rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn13rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn13rOut] = Bdat::getMember(wrapper.data, "Wpn13rOut"); }

const char *getRSC_PcWpnMountWpn13rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn13rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn13rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn14rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn14rIn] = Bdat::getMember(wrapper.data, "Wpn14rIn"); }

const char *getRSC_PcWpnMountWpn14rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn14rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn14rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn14rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn14rOut] = Bdat::getMember(wrapper.data, "Wpn14rOut"); }

const char *getRSC_PcWpnMountWpn14rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn14rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn14rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn15rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn15rIn] = Bdat::getMember(wrapper.data, "Wpn15rIn"); }

const char *getRSC_PcWpnMountWpn15rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn15rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn15rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn15rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn15rOut] = Bdat::getMember(wrapper.data, "Wpn15rOut"); }

const char *getRSC_PcWpnMountWpn15rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn15rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn15rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16rIn] = Bdat::getMember(wrapper.data, "Wpn16rIn"); }

const char *getRSC_PcWpnMountWpn16rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16rOut] = Bdat::getMember(wrapper.data, "Wpn16rOut"); }

const char *getRSC_PcWpnMountWpn16rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16lIn] = Bdat::getMember(wrapper.data, "Wpn16lIn"); }

const char *getRSC_PcWpnMountWpn16lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn16lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn16lOut] = Bdat::getMember(wrapper.data, "Wpn16lOut"); }

const char *getRSC_PcWpnMountWpn16lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn16lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn16lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn17rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn17rIn] = Bdat::getMember(wrapper.data, "Wpn17rIn"); }

const char *getRSC_PcWpnMountWpn17rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn17rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn17rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn17rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn17rOut] = Bdat::getMember(wrapper.data, "Wpn17rOut"); }

const char *getRSC_PcWpnMountWpn17rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn17rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn17rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn18rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn18rIn] = Bdat::getMember(wrapper.data, "Wpn18rIn"); }

const char *getRSC_PcWpnMountWpn18rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn18rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn18rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn18rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn18rOut] = Bdat::getMember(wrapper.data, "Wpn18rOut"); }

const char *getRSC_PcWpnMountWpn18rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn18rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn18rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn19rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn19rIn] = Bdat::getMember(wrapper.data, "Wpn19rIn"); }

const char *getRSC_PcWpnMountWpn19rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn19rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn19rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn19rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn19rOut] = Bdat::getMember(wrapper.data, "Wpn19rOut"); }

const char *getRSC_PcWpnMountWpn19rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn19rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn19rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20rIn] = Bdat::getMember(wrapper.data, "Wpn20rIn"); }

const char *getRSC_PcWpnMountWpn20rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20rOut] = Bdat::getMember(wrapper.data, "Wpn20rOut"); }

const char *getRSC_PcWpnMountWpn20rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20lIn] = Bdat::getMember(wrapper.data, "Wpn20lIn"); }

const char *getRSC_PcWpnMountWpn20lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn20lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn20lOut] = Bdat::getMember(wrapper.data, "Wpn20lOut"); }

const char *getRSC_PcWpnMountWpn20lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn20lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn20lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn21rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn21rIn] = Bdat::getMember(wrapper.data, "Wpn21rIn"); }

const char *getRSC_PcWpnMountWpn21rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn21rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn21rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn21rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn21rOut] = Bdat::getMember(wrapper.data, "Wpn21rOut"); }

const char *getRSC_PcWpnMountWpn21rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn21rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn21rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22rIn] = Bdat::getMember(wrapper.data, "Wpn22rIn"); }

const char *getRSC_PcWpnMountWpn22rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22rOut] = Bdat::getMember(wrapper.data, "Wpn22rOut"); }

const char *getRSC_PcWpnMountWpn22rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22lIn] = Bdat::getMember(wrapper.data, "Wpn22lIn"); }

const char *getRSC_PcWpnMountWpn22lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn22lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn22lOut] = Bdat::getMember(wrapper.data, "Wpn22lOut"); }

const char *getRSC_PcWpnMountWpn22lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn22lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn22lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23rIn] = Bdat::getMember(wrapper.data, "Wpn23rIn"); }

const char *getRSC_PcWpnMountWpn23rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23rOut] = Bdat::getMember(wrapper.data, "Wpn23rOut"); }

const char *getRSC_PcWpnMountWpn23rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23lIn] = Bdat::getMember(wrapper.data, "Wpn23lIn"); }

const char *getRSC_PcWpnMountWpn23lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn23lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn23lOut] = Bdat::getMember(wrapper.data, "Wpn23lOut"); }

const char *getRSC_PcWpnMountWpn23lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn23lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn23lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24rIn] = Bdat::getMember(wrapper.data, "Wpn24rIn"); }

const char *getRSC_PcWpnMountWpn24rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24rOut] = Bdat::getMember(wrapper.data, "Wpn24rOut"); }

const char *getRSC_PcWpnMountWpn24rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24lIn] = Bdat::getMember(wrapper.data, "Wpn24lIn"); }

const char *getRSC_PcWpnMountWpn24lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn24lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn24lOut] = Bdat::getMember(wrapper.data, "Wpn24lOut"); }

const char *getRSC_PcWpnMountWpn24lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn24lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn24lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25rIn] = Bdat::getMember(wrapper.data, "Wpn25rIn"); }

const char *getRSC_PcWpnMountWpn25rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25rOut] = Bdat::getMember(wrapper.data, "Wpn25rOut"); }

const char *getRSC_PcWpnMountWpn25rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25lIn] = Bdat::getMember(wrapper.data, "Wpn25lIn"); }

const char *getRSC_PcWpnMountWpn25lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn25lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn25lOut] = Bdat::getMember(wrapper.data, "Wpn25lOut"); }

const char *getRSC_PcWpnMountWpn25lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn25lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn25lOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26rIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26rIn] = Bdat::getMember(wrapper.data, "Wpn26rIn"); }

const char *getRSC_PcWpnMountWpn26rIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26rIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26rIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26rOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26rOut] = Bdat::getMember(wrapper.data, "Wpn26rOut"); }

const char *getRSC_PcWpnMountWpn26rOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26rOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26rOut], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26lIn(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26lIn] = Bdat::getMember(wrapper.data, "Wpn26lIn"); }

const char *getRSC_PcWpnMountWpn26lIn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26lIn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26lIn], id, 7).valueString;
}

void initRSC_PcWpnMountWpn26lOut(const CBdatWrapper &wrapper) { s_members[RSC_PcWpnMountWpn26lOut] = Bdat::getMember(wrapper.data, "Wpn26lOut"); }

const char *getRSC_PcWpnMountWpn26lOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RSC_PcWpnMountWpn26lOut] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RSC_PcWpnMountWpn26lOut], id, 7).valueString;
}

void initRscEnWpnModel(const CBdatWrapper &wrapper) { s_members[RscEnWpnModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRscEnWpnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnModel], id, 7).valueString;
}

void initRscEnWpnScale(const CBdatWrapper &wrapper) { s_members[RscEnWpnScale] = Bdat::getMember(wrapper.data, "Scale"); }

u32 getRscEnWpnScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnScale] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RscEnWpnScale], id, 2).valueU16;
}

void initRscEnWpnMotion(const CBdatWrapper &wrapper) { s_members[RscEnWpnMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRscEnWpnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMotion], id, 7).valueString;
}

void initRscEnWpnMtpInChara(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpInChara] = Bdat::getMember(wrapper.data, "MtpInChara"); }

const char *getRscEnWpnMtpInChara(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpInChara] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpInChara], id, 7).valueString;
}

void initRscEnWpnMtpInWpn(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpInWpn] = Bdat::getMember(wrapper.data, "MtpInWpn"); }

const char *getRscEnWpnMtpInWpn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpInWpn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpInWpn], id, 7).valueString;
}

void initRscEnWpnMtpOutChara(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpOutChara] = Bdat::getMember(wrapper.data, "MtpOutChara"); }

const char *getRscEnWpnMtpOutChara(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpOutChara] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpOutChara], id, 7).valueString;
}

void initRscEnWpnMtpOutWpn(const CBdatWrapper &wrapper) { s_members[RscEnWpnMtpOutWpn] = Bdat::getMember(wrapper.data, "MtpOutWpn"); }

const char *getRscEnWpnMtpOutWpn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscEnWpnMtpOutWpn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscEnWpnMtpOutWpn], id, 7).valueString;
}

void initRscNpcWpnModel(const CBdatWrapper &wrapper) { s_members[RscNpcWpnModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getRscNpcWpnModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcWpnModel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcWpnModel], id, 7).valueString;
}

void initRscNpcWpnMotion(const CBdatWrapper &wrapper) { s_members[RscNpcWpnMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getRscNpcWpnMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RscNpcWpnMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[RscNpcWpnMotion], id, 7).valueString;
}

void initDriverParamExtMountNpc(const CBdatWrapper &wrapper) { s_members[DriverParamExtMountNpc] = Bdat::getMember(wrapper.data, "ExtMountNpc"); }

u32 getDriverParamExtMountNpc(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DriverParamExtMountNpc] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DriverParamExtMountNpc], id, 2).valueU16;
}

void initDriverParamExtMountBone(const CBdatWrapper &wrapper) { s_members[DriverParamExtMountBone] = Bdat::getMember(wrapper.data, "ExtMountBone"); }

const char *getDriverParamExtMountBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DriverParamExtMountBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[DriverParamExtMountBone], id, 7).valueString;
}

void initDriverParamExtMountCond(const CBdatWrapper &wrapper) { s_members[DriverParamExtMountCond] = Bdat::getMember(wrapper.data, "ExtMountCond"); }

u32 getDriverParamExtMountCond(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DriverParamExtMountCond] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DriverParamExtMountCond], id, 2).valueU16;
}

void initVoiceTableDriver1(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver1] = Bdat::getMember(wrapper.data, "Driver1"); }

const char *getVoiceTableDriver1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver1], id, 7).valueString;
}

void initVoiceTableDriver2(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver2] = Bdat::getMember(wrapper.data, "Driver2"); }

const char *getVoiceTableDriver2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver2], id, 7).valueString;
}

void initVoiceTableDriver3(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver3] = Bdat::getMember(wrapper.data, "Driver3"); }

const char *getVoiceTableDriver3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver3], id, 7).valueString;
}

void initVoiceTableDriver4(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver4] = Bdat::getMember(wrapper.data, "Driver4"); }

const char *getVoiceTableDriver4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver4], id, 7).valueString;
}

void initVoiceTableDriver5(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver5] = Bdat::getMember(wrapper.data, "Driver5"); }

const char *getVoiceTableDriver5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver5], id, 7).valueString;
}

void initVoiceTableDriver6(const CBdatWrapper &wrapper) { s_members[VoiceTableDriver6] = Bdat::getMember(wrapper.data, "Driver6"); }

const char *getVoiceTableDriver6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableDriver6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableDriver6], id, 7).valueString;
}

void initVoiceTableBladeBlade1(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade1] = Bdat::getMember(wrapper.data, "Blade1"); }

const char *getVoiceTableBladeBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade1], id, 7).valueString;
}

void initVoiceTableBladeBlade2(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade2] = Bdat::getMember(wrapper.data, "Blade2"); }

const char *getVoiceTableBladeBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade2], id, 7).valueString;
}

void initVoiceTableBladeBlade3(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade3] = Bdat::getMember(wrapper.data, "Blade3"); }

const char *getVoiceTableBladeBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade3], id, 7).valueString;
}

void initVoiceTableBladeBlade4(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade4] = Bdat::getMember(wrapper.data, "Blade4"); }

const char *getVoiceTableBladeBlade4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade4], id, 7).valueString;
}

void initVoiceTableBladeBlade5(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade5] = Bdat::getMember(wrapper.data, "Blade5"); }

const char *getVoiceTableBladeBlade5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade5], id, 7).valueString;
}

void initVoiceTableBladeBlade6(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade6] = Bdat::getMember(wrapper.data, "Blade6"); }

const char *getVoiceTableBladeBlade6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade6], id, 7).valueString;
}

void initVoiceTableBladeBlade7(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade7] = Bdat::getMember(wrapper.data, "Blade7"); }

const char *getVoiceTableBladeBlade7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade7], id, 7).valueString;
}

void initVoiceTableBladeBlade8(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade8] = Bdat::getMember(wrapper.data, "Blade8"); }

const char *getVoiceTableBladeBlade8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade8], id, 7).valueString;
}

void initVoiceTableBladeBlade9(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade9] = Bdat::getMember(wrapper.data, "Blade9"); }

const char *getVoiceTableBladeBlade9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade9], id, 7).valueString;
}

void initVoiceTableBladeBlade10(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade10] = Bdat::getMember(wrapper.data, "Blade10"); }

const char *getVoiceTableBladeBlade10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade10], id, 7).valueString;
}

void initVoiceTableBladeBlade11(const CBdatWrapper &wrapper) { s_members[VoiceTableBladeBlade11] = Bdat::getMember(wrapper.data, "Blade11"); }

const char *getVoiceTableBladeBlade11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableBladeBlade11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableBladeBlade11], id, 7).valueString;
}

void initVoiceTableRareRareBlade1(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade1] = Bdat::getMember(wrapper.data, "RareBlade1"); }

const char *getVoiceTableRareRareBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade1], id, 7).valueString;
}

void initVoiceTableRareRareBlade2(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade2] = Bdat::getMember(wrapper.data, "RareBlade2"); }

const char *getVoiceTableRareRareBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade2], id, 7).valueString;
}

void initVoiceTableRareRareBlade3(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade3] = Bdat::getMember(wrapper.data, "RareBlade3"); }

const char *getVoiceTableRareRareBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade3], id, 7).valueString;
}

void initVoiceTableRareRareBlade4(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade4] = Bdat::getMember(wrapper.data, "RareBlade4"); }

const char *getVoiceTableRareRareBlade4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade4], id, 7).valueString;
}

void initVoiceTableRareRareBlade5(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade5] = Bdat::getMember(wrapper.data, "RareBlade5"); }

const char *getVoiceTableRareRareBlade5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade5], id, 7).valueString;
}

void initVoiceTableRareRareBlade6(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade6] = Bdat::getMember(wrapper.data, "RareBlade6"); }

const char *getVoiceTableRareRareBlade6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade6], id, 7).valueString;
}

void initVoiceTableRareRareBlade7(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade7] = Bdat::getMember(wrapper.data, "RareBlade7"); }

const char *getVoiceTableRareRareBlade7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade7], id, 7).valueString;
}

void initVoiceTableRareRareBlade8(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade8] = Bdat::getMember(wrapper.data, "RareBlade8"); }

const char *getVoiceTableRareRareBlade8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade8], id, 7).valueString;
}

void initVoiceTableRareRareBlade9(const CBdatWrapper &wrapper) { s_members[VoiceTableRareRareBlade9] = Bdat::getMember(wrapper.data, "RareBlade9"); }

const char *getVoiceTableRareRareBlade9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade9], id, 7).valueString;
}

void initVoiceTableRareRareBlade10(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade10] = Bdat::getMember(wrapper.data, "RareBlade10");
}

const char *getVoiceTableRareRareBlade10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade10], id, 7).valueString;
}

void initVoiceTableRareRareBlade11(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade11] = Bdat::getMember(wrapper.data, "RareBlade11");
}

const char *getVoiceTableRareRareBlade11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade11], id, 7).valueString;
}

void initVoiceTableRareRareBlade12(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade12] = Bdat::getMember(wrapper.data, "RareBlade12");
}

const char *getVoiceTableRareRareBlade12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade12], id, 7).valueString;
}

void initVoiceTableRareRareBlade13(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade13] = Bdat::getMember(wrapper.data, "RareBlade13");
}

const char *getVoiceTableRareRareBlade13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade13], id, 7).valueString;
}

void initVoiceTableRareRareBlade14(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade14] = Bdat::getMember(wrapper.data, "RareBlade14");
}

const char *getVoiceTableRareRareBlade14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade14], id, 7).valueString;
}

void initVoiceTableRareRareBlade15(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade15] = Bdat::getMember(wrapper.data, "RareBlade15");
}

const char *getVoiceTableRareRareBlade15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade15], id, 7).valueString;
}

void initVoiceTableRareRareBlade16(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade16] = Bdat::getMember(wrapper.data, "RareBlade16");
}

const char *getVoiceTableRareRareBlade16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade16], id, 7).valueString;
}

void initVoiceTableRareRareBlade17(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade17] = Bdat::getMember(wrapper.data, "RareBlade17");
}

const char *getVoiceTableRareRareBlade17(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade17] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade17], id, 7).valueString;
}

void initVoiceTableRareRareBlade18(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade18] = Bdat::getMember(wrapper.data, "RareBlade18");
}

const char *getVoiceTableRareRareBlade18(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade18] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade18], id, 7).valueString;
}

void initVoiceTableRareRareBlade19(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade19] = Bdat::getMember(wrapper.data, "RareBlade19");
}

const char *getVoiceTableRareRareBlade19(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade19] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade19], id, 7).valueString;
}

void initVoiceTableRareRareBlade20(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade20] = Bdat::getMember(wrapper.data, "RareBlade20");
}

const char *getVoiceTableRareRareBlade20(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade20] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade20], id, 7).valueString;
}

void initVoiceTableRareRareBlade21(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade21] = Bdat::getMember(wrapper.data, "RareBlade21");
}

const char *getVoiceTableRareRareBlade21(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade21] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade21], id, 7).valueString;
}

void initVoiceTableRareRareBlade22(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade22] = Bdat::getMember(wrapper.data, "RareBlade22");
}

const char *getVoiceTableRareRareBlade22(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade22] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade22], id, 7).valueString;
}

void initVoiceTableRareRareBlade23(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade23] = Bdat::getMember(wrapper.data, "RareBlade23");
}

const char *getVoiceTableRareRareBlade23(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade23] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade23], id, 7).valueString;
}

void initVoiceTableRareRareBlade24(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade24] = Bdat::getMember(wrapper.data, "RareBlade24");
}

const char *getVoiceTableRareRareBlade24(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade24] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade24], id, 7).valueString;
}

void initVoiceTableRareRareBlade25(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade25] = Bdat::getMember(wrapper.data, "RareBlade25");
}

const char *getVoiceTableRareRareBlade25(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade25] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade25], id, 7).valueString;
}

void initVoiceTableRareRareBlade26(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade26] = Bdat::getMember(wrapper.data, "RareBlade26");
}

const char *getVoiceTableRareRareBlade26(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade26] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade26], id, 7).valueString;
}

void initVoiceTableRareRareBlade27(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade27] = Bdat::getMember(wrapper.data, "RareBlade27");
}

const char *getVoiceTableRareRareBlade27(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade27] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade27], id, 7).valueString;
}

void initVoiceTableRareRareBlade28(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade28] = Bdat::getMember(wrapper.data, "RareBlade28");
}

const char *getVoiceTableRareRareBlade28(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade28] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade28], id, 7).valueString;
}

void initVoiceTableRareRareBlade29(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade29] = Bdat::getMember(wrapper.data, "RareBlade29");
}

const char *getVoiceTableRareRareBlade29(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade29] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade29], id, 7).valueString;
}

void initVoiceTableRareRareBlade30(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade30] = Bdat::getMember(wrapper.data, "RareBlade30");
}

const char *getVoiceTableRareRareBlade30(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade30] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade30], id, 7).valueString;
}

void initVoiceTableRareRareBlade31(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade31] = Bdat::getMember(wrapper.data, "RareBlade31");
}

const char *getVoiceTableRareRareBlade31(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade31] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade31], id, 7).valueString;
}

void initVoiceTableRareRareBlade32(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade32] = Bdat::getMember(wrapper.data, "RareBlade32");
}

const char *getVoiceTableRareRareBlade32(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade32] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade32], id, 7).valueString;
}

void initVoiceTableRareRareBlade33(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade33] = Bdat::getMember(wrapper.data, "RareBlade33");
}

const char *getVoiceTableRareRareBlade33(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade33] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade33], id, 7).valueString;
}

void initVoiceTableRareRareBlade34(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade34] = Bdat::getMember(wrapper.data, "RareBlade34");
}

const char *getVoiceTableRareRareBlade34(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade34] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade34], id, 7).valueString;
}

void initVoiceTableRareRareBlade35(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade35] = Bdat::getMember(wrapper.data, "RareBlade35");
}

const char *getVoiceTableRareRareBlade35(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade35] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade35], id, 7).valueString;
}

void initVoiceTableRareRareBlade36(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade36] = Bdat::getMember(wrapper.data, "RareBlade36");
}

const char *getVoiceTableRareRareBlade36(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade36] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade36], id, 7).valueString;
}

void initVoiceTableRareRareBlade37(const CBdatWrapper &wrapper) {
  s_members[VoiceTableRareRareBlade37] = Bdat::getMember(wrapper.data, "RareBlade37");
}

const char *getVoiceTableRareRareBlade37(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableRareRareBlade37] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableRareRareBlade37], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade1(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade1] = Bdat::getMember(wrapper.data, "CommonBlade1");
}

const char *getVoiceTableCommonCommonBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade1], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade2(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade2] = Bdat::getMember(wrapper.data, "CommonBlade2");
}

const char *getVoiceTableCommonCommonBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade2], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade3(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade3] = Bdat::getMember(wrapper.data, "CommonBlade3");
}

const char *getVoiceTableCommonCommonBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade3], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade4(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade4] = Bdat::getMember(wrapper.data, "CommonBlade4");
}

const char *getVoiceTableCommonCommonBlade4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade4], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade5(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade5] = Bdat::getMember(wrapper.data, "CommonBlade5");
}

const char *getVoiceTableCommonCommonBlade5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade5], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade6(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade6] = Bdat::getMember(wrapper.data, "CommonBlade6");
}

const char *getVoiceTableCommonCommonBlade6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade6], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade7(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade7] = Bdat::getMember(wrapper.data, "CommonBlade7");
}

const char *getVoiceTableCommonCommonBlade7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade7], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade8(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade8] = Bdat::getMember(wrapper.data, "CommonBlade8");
}

const char *getVoiceTableCommonCommonBlade8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade8], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade9(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade9] = Bdat::getMember(wrapper.data, "CommonBlade9");
}

const char *getVoiceTableCommonCommonBlade9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade9], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade10(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade10] = Bdat::getMember(wrapper.data, "CommonBlade10");
}

const char *getVoiceTableCommonCommonBlade10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade10], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade11(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade11] = Bdat::getMember(wrapper.data, "CommonBlade11");
}

const char *getVoiceTableCommonCommonBlade11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade11], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade12(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade12] = Bdat::getMember(wrapper.data, "CommonBlade12");
}

const char *getVoiceTableCommonCommonBlade12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade12], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade13(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade13] = Bdat::getMember(wrapper.data, "CommonBlade13");
}

const char *getVoiceTableCommonCommonBlade13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade13], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade14(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade14] = Bdat::getMember(wrapper.data, "CommonBlade14");
}

const char *getVoiceTableCommonCommonBlade14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade14], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade15(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade15] = Bdat::getMember(wrapper.data, "CommonBlade15");
}

const char *getVoiceTableCommonCommonBlade15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade15], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade16(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade16] = Bdat::getMember(wrapper.data, "CommonBlade16");
}

const char *getVoiceTableCommonCommonBlade16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade16], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade17(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade17] = Bdat::getMember(wrapper.data, "CommonBlade17");
}

const char *getVoiceTableCommonCommonBlade17(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade17] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade17], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade18(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade18] = Bdat::getMember(wrapper.data, "CommonBlade18");
}

const char *getVoiceTableCommonCommonBlade18(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade18] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade18], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade19(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade19] = Bdat::getMember(wrapper.data, "CommonBlade19");
}

const char *getVoiceTableCommonCommonBlade19(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade19] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade19], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade20(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade20] = Bdat::getMember(wrapper.data, "CommonBlade20");
}

const char *getVoiceTableCommonCommonBlade20(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade20] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade20], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade21(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade21] = Bdat::getMember(wrapper.data, "CommonBlade21");
}

const char *getVoiceTableCommonCommonBlade21(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade21] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade21], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade22(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade22] = Bdat::getMember(wrapper.data, "CommonBlade22");
}

const char *getVoiceTableCommonCommonBlade22(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade22] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade22], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade23(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade23] = Bdat::getMember(wrapper.data, "CommonBlade23");
}

const char *getVoiceTableCommonCommonBlade23(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade23] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade23], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade24(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade24] = Bdat::getMember(wrapper.data, "CommonBlade24");
}

const char *getVoiceTableCommonCommonBlade24(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade24] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade24], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade25(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade25] = Bdat::getMember(wrapper.data, "CommonBlade25");
}

const char *getVoiceTableCommonCommonBlade25(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade25] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade25], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade26(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade26] = Bdat::getMember(wrapper.data, "CommonBlade26");
}

const char *getVoiceTableCommonCommonBlade26(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade26] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade26], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade27(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade27] = Bdat::getMember(wrapper.data, "CommonBlade27");
}

const char *getVoiceTableCommonCommonBlade27(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade27] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade27], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade28(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade28] = Bdat::getMember(wrapper.data, "CommonBlade28");
}

const char *getVoiceTableCommonCommonBlade28(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade28] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade28], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade29(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade29] = Bdat::getMember(wrapper.data, "CommonBlade29");
}

const char *getVoiceTableCommonCommonBlade29(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade29] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade29], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade30(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade30] = Bdat::getMember(wrapper.data, "CommonBlade30");
}

const char *getVoiceTableCommonCommonBlade30(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade30] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade30], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade31(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade31] = Bdat::getMember(wrapper.data, "CommonBlade31");
}

const char *getVoiceTableCommonCommonBlade31(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade31] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade31], id, 7).valueString;
}

void initVoiceTableCommonCommonBlade32(const CBdatWrapper &wrapper) {
  s_members[VoiceTableCommonCommonBlade32] = Bdat::getMember(wrapper.data, "CommonBlade32");
}

const char *getVoiceTableCommonCommonBlade32(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[VoiceTableCommonCommonBlade32] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[VoiceTableCommonCommonBlade32], id, 7).valueString;
}

void initFLD_actorSELOD(const CBdatWrapper &wrapper) { s_members[FLD_actorSELOD] = Bdat::getMember(wrapper.data, "LOD"); }

const char *getFLD_actorSELOD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSELOD] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[FLD_actorSELOD], id, 7).valueString;
}

void initFLD_actorSEse_type(const CBdatWrapper &wrapper) { s_members[FLD_actorSEse_type] = Bdat::getMember(wrapper.data, "se_type"); }

u32 getFLD_actorSEse_type(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEse_type] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEse_type], id, 1).valueU8;
}

void initFLD_actorSEseName(const CBdatWrapper &wrapper) { s_members[FLD_actorSEseName] = Bdat::getMember(wrapper.data, "seName"); }

u32 getFLD_actorSEseName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEseName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEseName], id, 2).valueU16;
}

void initFLD_actorSEmax_volume_Dist(const CBdatWrapper &wrapper) {
  s_members[FLD_actorSEmax_volume_Dist] = Bdat::getMember(wrapper.data, "max_volume_Dist");
}

f32 getFLD_actorSEmax_volume_Dist(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEmax_volume_Dist] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEmax_volume_Dist], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEmin_volume_Dist(const CBdatWrapper &wrapper) {
  s_members[FLD_actorSEmin_volume_Dist] = Bdat::getMember(wrapper.data, "min_volume_Dist");
}

f32 getFLD_actorSEmin_volume_Dist(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEmin_volume_Dist] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEmin_volume_Dist], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEvolumeMAX(const CBdatWrapper &wrapper) { s_members[FLD_actorSEvolumeMAX] = Bdat::getMember(wrapper.data, "volumeMAX"); }

u32 getFLD_actorSEvolumeMAX(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEvolumeMAX] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEvolumeMAX], id, 1).valueU8;
}

void initFLD_actorSEvolumeMIN(const CBdatWrapper &wrapper) { s_members[FLD_actorSEvolumeMIN] = Bdat::getMember(wrapper.data, "volumeMIN"); }

u32 getFLD_actorSEvolumeMIN(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_actorSEvolumeMIN] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_actorSEvolumeMIN], id, 1).valueU8;
}

void initFLD_actorSEoffsetX(const CBdatWrapper &wrapper) { s_members[FLD_actorSEoffsetX] = Bdat::getMember(wrapper.data, "offsetX"); }

f32 getFLD_actorSEoffsetX(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEoffsetX] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEoffsetX], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEoffsetY(const CBdatWrapper &wrapper) { s_members[FLD_actorSEoffsetY] = Bdat::getMember(wrapper.data, "offsetY"); }

f32 getFLD_actorSEoffsetY(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEoffsetY] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEoffsetY], id, 8).valueF32;
  }

  return value;
}

void initFLD_actorSEoffsetZ(const CBdatWrapper &wrapper) { s_members[FLD_actorSEoffsetZ] = Bdat::getMember(wrapper.data, "offsetZ"); }

f32 getFLD_actorSEoffsetZ(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[FLD_actorSEoffsetZ] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[FLD_actorSEoffsetZ], id, 8).valueF32;
  }

  return value;
}

} // namespace _gfbrs

u32 GfBdatRsc::getRscEnStart() const { return Bdat::getIdTop(unknown10->data); }

const char *GfBdatRsc::getRscEnDebugName(u32 id) const { return _gfbrs::getRscEnDebugName(*unknown10, id); }

u32 GfBdatRsc::getRscEnTypeFamily(u32 id) const { return _gfbrs::getRscEnTypeFamily(*unknown10, id); }

u32 GfBdatRsc::getRscEnTypeGenus(u32 id) const { return _gfbrs::getRscEnTypeGenus(*unknown10, id); }

u32 GfBdatRsc::getRscEnActType(u32 id) const { return _gfbrs::getRscEnActType(*unknown10, id); }

s32 GfBdatRsc::getRscEnFlyHeight(u32 id) const { return _gfbrs::getRscEnFlyHeight(*unknown10, id); }

u32 GfBdatRsc::getRscEnFldMoveType(u32 id) const { return _gfbrs::getRscEnFldMoveType(*unknown10, id); }

u32 GfBdatRsc::getRscEnMaterial(u32 id) const { return _gfbrs::getRscEnMaterial(*unknown10, id); }

u32 GfBdatRsc::getRscEnProxyID(u32 id) const { return _gfbrs::getRscEnProxyID(*unknown10, id); }

u32 GfBdatRsc::getRscEnEnRadius(u32 id) const { return _gfbrs::getRscEnEnRadius(*unknown10, id); }

u32 GfBdatRsc::getRscEnEnRadius2(u32 id) const { return _gfbrs::getRscEnEnRadius2(*unknown10, id); }

u32 GfBdatRsc::getRscEnChestHeight(u32 id) const { return _gfbrs::getRscEnChestHeight(*unknown10, id); }

u32 GfBdatRsc::getRscEnChestHeight2(u32 id) const { return _gfbrs::getRscEnChestHeight2(*unknown10, id); }

f32 GfBdatRsc::getRscEnBallRadius(u32 id) const { return _gfbrs::getRscEnBallRadius(*unknown10, id); }

f32 GfBdatRsc::getRscEnBallHeight(u32 id) const { return _gfbrs::getRscEnBallHeight(*unknown10, id); }

f32 GfBdatRsc::getRscEnCharColli(u32 id) const { return _gfbrs::getRscEnCharColli(*unknown10, id); }

u32 GfBdatRsc::getRscEnoffsetID(u32 id) const { return _gfbrs::getRscEnoffsetID(*unknown10, id); }

u32 GfBdatRsc::getRscEnEyeRot(u32 id) const { return _gfbrs::getRscEnEyeRot(*unknown10, id); }

const char *GfBdatRsc::getRscEnSearchBaseBone(u32 id) const { return _gfbrs::getRscEnSearchBaseBone(*unknown10, id); }

const char *GfBdatRsc::getRscEnCenterBone(u32 id) const { return _gfbrs::getRscEnCenterBone(*unknown10, id); }

const char *GfBdatRsc::getRscEnCamBone(u32 id) const { return _gfbrs::getRscEnCamBone(*unknown10, id); }

u32 GfBdatRsc::getRscEnFrontAngle(u32 id) const { return _gfbrs::getRscEnFrontAngle(*unknown10, id); }

u32 GfBdatRsc::getRscEnTurnAngleSmall(u32 id) const { return _gfbrs::getRscEnTurnAngleSmall(*unknown10, id); }

u32 GfBdatRsc::getRscEnTurnAngleBig(u32 id) const { return _gfbrs::getRscEnTurnAngleBig(*unknown10, id); }

u32 GfBdatRsc::getRscEnUnduration(u32 id) const { return _gfbrs::getRscEnUnduration(*unknown10, id); }

const char *GfBdatRsc::getRscEnModel(u32 id) const { return _gfbrs::getRscEnModel(*unknown10, id); }

const char *GfBdatRsc::getRscEnChrFile(u32 id) const { return _gfbrs::getRscEnChrFile(*unknown10, id); }

const char *GfBdatRsc::getRscEnMotion(u32 id) const { return _gfbrs::getRscEnMotion(*unknown10, id); }

const char *GfBdatRsc::getRscEnRefMotion(u32 id) const { return _gfbrs::getRscEnRefMotion(*unknown10, id); }

const char *GfBdatRsc::getRscEnEffectPack(u32 id) const { return _gfbrs::getRscEnEffectPack(*unknown10, id); }

const char *GfBdatRsc::getRscEnLoopEffect(u32 id) const { return _gfbrs::getRscEnLoopEffect(*unknown10, id); }

const char *GfBdatRsc::getRscEnSePack(u32 id) const { return _gfbrs::getRscEnSePack(*unknown10, id); }

const char *GfBdatRsc::getRscEnVoice(u32 id) const { return _gfbrs::getRscEnVoice(*unknown10, id); }

u32 GfBdatRsc::getRscEnVoiceEx(u32 id) const { return _gfbrs::getRscEnVoiceEx(*unknown10, id); }

const char *GfBdatRsc::getRscEnClipEvent(u32 id) const { return _gfbrs::getRscEnClipEvent(*unknown10, id); }

const char *GfBdatRsc::getRscEnComp_Eff(u32 id) const { return _gfbrs::getRscEnComp_Eff(*unknown10, id); }

const char *GfBdatRsc::getRscEnComp_Se(u32 id) const { return _gfbrs::getRscEnComp_Se(*unknown10, id); }

const char *GfBdatRsc::getRscEnComp_Vo(u32 id) const { return _gfbrs::getRscEnComp_Vo(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagNoEcSkip(u32 id) const { return _gfbrs::isRscEnFlagNoEcSkip(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagMap(u32 id) const { return _gfbrs::isRscEnFlagMap(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagEvt(u32 id) const { return _gfbrs::isRscEnFlagEvt(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagNoWinVo(u32 id) const { return _gfbrs::isRscEnFlagNoWinVo(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagBait(u32 id) const { return _gfbrs::isRscEnFlagBait(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagUseSearchBone(u32 id) const { return _gfbrs::isRscEnFlagUseSearchBone(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagNoVanish(u32 id) const { return _gfbrs::isRscEnFlagNoVanish(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagNoCamera(u32 id) const { return _gfbrs::isRscEnFlagNoCamera(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagWeaponDrawDisp(u32 id) const { return _gfbrs::isRscEnFlagWeaponDrawDisp(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagJoinAll(u32 id) const { return _gfbrs::isRscEnFlagJoinAll(*unknown10, id); }

bool GfBdatRsc::isRscEnFlagDeathMotion(u32 id) const { return _gfbrs::isRscEnFlagDeathMotion(*unknown10, id); }

u32 GfBdatRsc::getRscEnWeaponNum1(u32 id) const { return _gfbrs::getRscEnWeaponNum1(*unknown10, id); }

u32 GfBdatRsc::getRscEnWeaponNum2(u32 id) const { return _gfbrs::getRscEnWeaponNum2(*unknown10, id); }

u32 GfBdatRsc::getRscEnWeaponNum3(u32 id) const { return _gfbrs::getRscEnWeaponNum3(*unknown10, id); }

u32 GfBdatRsc::getRscEnWeaponNum4(u32 id) const { return _gfbrs::getRscEnWeaponNum4(*unknown10, id); }

u32 GfBdatRsc::getRscEnWeaponNum5(u32 id) const { return _gfbrs::getRscEnWeaponNum5(*unknown10, id); }

u32 GfBdatRsc::getRscEnMemorySlot(u32 id) const { return _gfbrs::getRscEnMemorySlot(*unknown10, id); }

u32 GfBdatRsc::getRscEnRace(u32 id) const { return _gfbrs::getRscEnRace(*unknown10, id); }

u32 GfBdatRsc::getRscEnDrType(u32 id) const { return _gfbrs::getRscEnDrType(*unknown10, id); }

s32 GfBdatRsc::getRscEnGoldDivideRev(u32 id) const { return _gfbrs::getRscEnGoldDivideRev(*unknown10, id); }

u32 GfBdatRsc::getRscEnFootStep(u32 id) const { return _gfbrs::getRscEnFootStep(*unknown10, id); }

u32 GfBdatRsc::getRscEnFootStepEffect(u32 id) const { return _gfbrs::getRscEnFootStepEffect(*unknown10, id); }

s32 GfBdatRsc::getRscEnRotateX(u32 id) const { return _gfbrs::getRscEnRotateX(*unknown10, id); }

s32 GfBdatRsc::getRscEnRotateY(u32 id) const { return _gfbrs::getRscEnRotateY(*unknown10, id); }

s32 GfBdatRsc::getRscEnRotateZ(u32 id) const { return _gfbrs::getRscEnRotateZ(*unknown10, id); }

s32 GfBdatRsc::getRscEnRotateDeg(u32 id) const { return _gfbrs::getRscEnRotateDeg(*unknown10, id); }

u32 GfBdatRsc::getRscEnRotEffScale(u32 id) const { return _gfbrs::getRscEnRotEffScale(*unknown10, id); }

u32 GfBdatRsc::getRscEnExtraParts1(u32 id) const { return _gfbrs::getRscEnExtraParts1(*unknown10, id); }

u32 GfBdatRsc::getRscEnExtraParts2(u32 id) const { return _gfbrs::getRscEnExtraParts2(*unknown10, id); }

u32 GfBdatRsc::getRscEnExtraParts3(u32 id) const { return _gfbrs::getRscEnExtraParts3(*unknown10, id); }

u32 GfBdatRsc::getRscEnExtraParts4(u32 id) const { return _gfbrs::getRscEnExtraParts4(*unknown10, id); }

u32 GfBdatRsc::getRscEnDeadSeNum(u32 id) const { return _gfbrs::getRscEnDeadSeNum(*unknown10, id); }

const char *GfBdatRsc::getRscEnRotateBone(u32 id) const { return _gfbrs::getRscEnRotateBone(*unknown10, id); }

u32 GfBdatRsc::getRscEnGenusStart() const { return Bdat::getIdTop(unknown18->data); }

u32 GfBdatRsc::getRscEnGenusNAME(u32 id) const { return _gfbrs::getRscEnGenusNAME(*unknown18, id); }

u32 GfBdatRsc::getRscEnGenusCAPTION(u32 id) const { return _gfbrs::getRscEnGenusCAPTION(*unknown18, id); }

bool GfBdatRsc::isRscEnGenusFlaggimmicktype(u32 id) const { return _gfbrs::isRscEnGenusFlaggimmicktype(*unknown18, id); }

u32 GfBdatRsc::getRscEnUndStart() const { return Bdat::getIdTop(unknown20->data); }

bool GfBdatRsc::isRscEnUndFlagUndX(u32 id) const { return _gfbrs::isRscEnUndFlagUndX(*unknown20, id); }

bool GfBdatRsc::isRscEnUndFlagUndZ(u32 id) const { return _gfbrs::isRscEnUndFlagUndZ(*unknown20, id); }

s32 GfBdatRsc::getRscEnUndUndMinX(u32 id) const { return _gfbrs::getRscEnUndUndMinX(*unknown20, id); }

s32 GfBdatRsc::getRscEnUndUndMaxX(u32 id) const { return _gfbrs::getRscEnUndUndMaxX(*unknown20, id); }

s32 GfBdatRsc::getRscEnUndUndMinZ(u32 id) const { return _gfbrs::getRscEnUndUndMinZ(*unknown20, id); }

s32 GfBdatRsc::getRscEnUndUndMaxZ(u32 id) const { return _gfbrs::getRscEnUndUndMaxZ(*unknown20, id); }

u32 GfBdatRsc::getRscEnUndUndDeg(u32 id) const { return _gfbrs::getRscEnUndUndDeg(*unknown20, id); }

u32 GfBdatRsc::getRscNpcListStart() const { return Bdat::getIdTop(unknown28->data); }

const char *GfBdatRsc::getRscNpcListModel(u32 id) const { return _gfbrs::getRscNpcListModel(*unknown28, id); }

const char *GfBdatRsc::getRscNpcListMotion(u32 id) const { return _gfbrs::getRscNpcListMotion(*unknown28, id); }

const char *GfBdatRsc::getRscNpcListAddMotion(u32 id) const { return _gfbrs::getRscNpcListAddMotion(*unknown28, id); }

const char *GfBdatRsc::getRscNpcListComp_Eff(u32 id) const { return _gfbrs::getRscNpcListComp_Eff(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListCollisionId(u32 id) const { return _gfbrs::getRscNpcListCollisionId(*unknown28, id); }

const char *GfBdatRsc::getRscNpcListSE(u32 id) const { return _gfbrs::getRscNpcListSE(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListSeEnv(u32 id) const { return _gfbrs::getRscNpcListSeEnv(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListRace(u32 id) const { return _gfbrs::getRscNpcListRace(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListFootStep(u32 id) const { return _gfbrs::getRscNpcListFootStep(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListFootStepEffect(u32 id) const { return _gfbrs::getRscNpcListFootStepEffect(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListRoots(u32 id) const { return _gfbrs::getRscNpcListRoots(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListGender(u32 id) const { return _gfbrs::getRscNpcListGender(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListName(u32 id) const { return _gfbrs::getRscNpcListName(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListOffsetID(u32 id) const { return _gfbrs::getRscNpcListOffsetID(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListEyeRot(u32 id) const { return _gfbrs::getRscNpcListEyeRot(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListExtraParts1(u32 id) const { return _gfbrs::getRscNpcListExtraParts1(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListExtraParts2(u32 id) const { return _gfbrs::getRscNpcListExtraParts2(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListExtraParts3(u32 id) const { return _gfbrs::getRscNpcListExtraParts3(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListExtraParts4(u32 id) const { return _gfbrs::getRscNpcListExtraParts4(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListExtraParts5(u32 id) const { return _gfbrs::getRscNpcListExtraParts5(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListExtraParts6(u32 id) const { return _gfbrs::getRscNpcListExtraParts6(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListScale(u32 id) const { return _gfbrs::getRscNpcListScale(*unknown28, id); }

u32 GfBdatRsc::getRscNpcListEventAsset(u32 id) const { return _gfbrs::getRscNpcListEventAsset(*unknown28, id); }

u32 GfBdatRsc::getRscMobListStart() const { return Bdat::getIdTop(unknown38->data); }

const char *GfBdatRsc::getRscMobListModel(u32 id) const { return _gfbrs::getRscMobListModel(*unknown38, id); }

const char *GfBdatRsc::getRscMobListMotion(u32 id) const { return _gfbrs::getRscMobListMotion(*unknown38, id); }

const char *GfBdatRsc::getRscMobListAddMotion(u32 id) const { return _gfbrs::getRscMobListAddMotion(*unknown38, id); }

const char *GfBdatRsc::getRscMobListComp_Eff(u32 id) const { return _gfbrs::getRscMobListComp_Eff(*unknown38, id); }

u32 GfBdatRsc::getRscMobListCollisionId(u32 id) const { return _gfbrs::getRscMobListCollisionId(*unknown38, id); }

const char *GfBdatRsc::getRscMobListSE(u32 id) const { return _gfbrs::getRscMobListSE(*unknown38, id); }

u32 GfBdatRsc::getRscMobListSeEnv(u32 id) const { return _gfbrs::getRscMobListSeEnv(*unknown38, id); }

u32 GfBdatRsc::getRscMobListRace(u32 id) const { return _gfbrs::getRscMobListRace(*unknown38, id); }

u32 GfBdatRsc::getRscMobListFootStep(u32 id) const { return _gfbrs::getRscMobListFootStep(*unknown38, id); }

u32 GfBdatRsc::getRscMobListFootStepEffect(u32 id) const { return _gfbrs::getRscMobListFootStepEffect(*unknown38, id); }

u32 GfBdatRsc::getRscMobListOffsetID(u32 id) const { return _gfbrs::getRscMobListOffsetID(*unknown38, id); }

u32 GfBdatRsc::getRscMobListExtraParts1(u32 id) const { return _gfbrs::getRscMobListExtraParts1(*unknown38, id); }

u32 GfBdatRsc::getRscMobListExtraParts2(u32 id) const { return _gfbrs::getRscMobListExtraParts2(*unknown38, id); }

u32 GfBdatRsc::getRscMobListExtraParts3(u32 id) const { return _gfbrs::getRscMobListExtraParts3(*unknown38, id); }

u32 GfBdatRsc::getRscMobListExtraParts4(u32 id) const { return _gfbrs::getRscMobListExtraParts4(*unknown38, id); }

u32 GfBdatRsc::getRscMobListExtraParts5(u32 id) const { return _gfbrs::getRscMobListExtraParts5(*unknown38, id); }

u32 GfBdatRsc::getRscMobListExtraParts6(u32 id) const { return _gfbrs::getRscMobListExtraParts6(*unknown38, id); }

u32 GfBdatRsc::getRSC_MapObjListStart() const { return Bdat::getIdTop(unknown60->data); }

const char *GfBdatRsc::getRSC_MapObjListModel(u32 id) const { return _gfbrs::getRSC_MapObjListModel(*unknown60, id); }

const char *GfBdatRsc::getRSC_MapObjListMotion(u32 id) const { return _gfbrs::getRSC_MapObjListMotion(*unknown60, id); }

const char *GfBdatRsc::getRSC_MapObjListComp_Eff(u32 id) const { return _gfbrs::getRSC_MapObjListComp_Eff(*unknown60, id); }

const char *GfBdatRsc::getRSC_MapObjListSE(u32 id) const { return _gfbrs::getRSC_MapObjListSE(*unknown60, id); }

u32 GfBdatRsc::getRSC_MapObjListSeEnv(u32 id) const { return _gfbrs::getRSC_MapObjListSeEnv(*unknown60, id); }

bool GfBdatRsc::isRSC_MapObjListflagBigObj(u32 id) const { return _gfbrs::isRSC_MapObjListflagBigObj(*unknown60, id); }

u32 GfBdatRsc::getRSC_MapObjListExtraParts1(u32 id) const { return _gfbrs::getRSC_MapObjListExtraParts1(*unknown60, id); }

u32 GfBdatRsc::getRSC_TboxListStart() const { return Bdat::getIdTop(unknown58->data); }

const char *GfBdatRsc::getRSC_TboxListModel(u32 id) const { return _gfbrs::getRSC_TboxListModel(*unknown58, id); }

const char *GfBdatRsc::getRSC_TboxListMotion(u32 id) const { return _gfbrs::getRSC_TboxListMotion(*unknown58, id); }

u32 GfBdatRsc::getRSC_PcWpnStart() const { return Bdat::getIdTop(unknown40->data); }

const char *GfBdatRsc::getRSC_PcWpnModel(u32 id) const { return _gfbrs::getRSC_PcWpnModel(*unknown40, id); }

const char *GfBdatRsc::getRSC_PcWpnMotion(u32 id) const { return _gfbrs::getRSC_PcWpnMotion(*unknown40, id); }

u32 GfBdatRsc::getRSC_PcWpnMenuImageID(u32 id) const { return _gfbrs::getRSC_PcWpnMenuImageID(*unknown40, id); }

u32 GfBdatRsc::getRSC_PcWpnMountStart() const { return Bdat::getIdTop(unknown48->data); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn01rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn01rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn01rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn01rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn02rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn02rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn02rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn02rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn03lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn03lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn04rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn04rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn04rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn04rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn05lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn05lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn06rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn06rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn06rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn06rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn07lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn07lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn08rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn08rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn08rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn08rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn09lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn09lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn10lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn10lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn11rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn11rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn11rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn11rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn12lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn12lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn13rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn13rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn13rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn13rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn14rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn14rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn14rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn14rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn15rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn15rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn15rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn15rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn16lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn16lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn17rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn17rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn17rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn17rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn18rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn18rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn18rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn18rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn19rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn19rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn19rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn19rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn20lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn20lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn21rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn21rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn21rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn21rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn22lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn22lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn23lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn23lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn24lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn24lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn25lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn25lOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26rIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26rIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26rOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26rOut(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26lIn(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26lIn(*unknown48, id); }

const char *GfBdatRsc::getRSC_PcWpnMountWpn26lOut(u32 id) const { return _gfbrs::getRSC_PcWpnMountWpn26lOut(*unknown48, id); }

u32 GfBdatRsc::getRscEnWpnStart() const { return Bdat::getIdTop(unknown50->data); }

const char *GfBdatRsc::getRscEnWpnModel(u32 id) const { return _gfbrs::getRscEnWpnModel(*unknown50, id); }

u32 GfBdatRsc::getRscEnWpnScale(u32 id) const { return _gfbrs::getRscEnWpnScale(*unknown50, id); }

const char *GfBdatRsc::getRscEnWpnMotion(u32 id) const { return _gfbrs::getRscEnWpnMotion(*unknown50, id); }

const char *GfBdatRsc::getRscEnWpnMtpInChara(u32 id) const { return _gfbrs::getRscEnWpnMtpInChara(*unknown50, id); }

const char *GfBdatRsc::getRscEnWpnMtpInWpn(u32 id) const { return _gfbrs::getRscEnWpnMtpInWpn(*unknown50, id); }

const char *GfBdatRsc::getRscEnWpnMtpOutChara(u32 id) const { return _gfbrs::getRscEnWpnMtpOutChara(*unknown50, id); }

const char *GfBdatRsc::getRscEnWpnMtpOutWpn(u32 id) const { return _gfbrs::getRscEnWpnMtpOutWpn(*unknown50, id); }

u32 GfBdatRsc::getRscNpcWpnStart() const { return Bdat::getIdTop(unknown30->data); }

const char *GfBdatRsc::getRscNpcWpnModel(u32 id) const { return _gfbrs::getRscNpcWpnModel(*unknown30, id); }

const char *GfBdatRsc::getRscNpcWpnMotion(u32 id) const { return _gfbrs::getRscNpcWpnMotion(*unknown30, id); }

u32 GfBdatRsc::getDriverParamStart() const { return Bdat::getIdTop(unknown68->data); }

u32 GfBdatRsc::getDriverParamExtMountNpc(u32 id) const { return _gfbrs::getDriverParamExtMountNpc(*unknown68, id); }

const char *GfBdatRsc::getDriverParamExtMountBone(u32 id) const { return _gfbrs::getDriverParamExtMountBone(*unknown68, id); }

u32 GfBdatRsc::getDriverParamExtMountCond(u32 id) const { return _gfbrs::getDriverParamExtMountCond(*unknown68, id); }

u32 GfBdatRsc::getVoiceTableStart() const { return Bdat::getIdTop(unknown70->data); }

const char *GfBdatRsc::getVoiceTableDriver1(u32 id) const { return _gfbrs::getVoiceTableDriver1(*unknown70, id); }

const char *GfBdatRsc::getVoiceTableDriver2(u32 id) const { return _gfbrs::getVoiceTableDriver2(*unknown70, id); }

const char *GfBdatRsc::getVoiceTableDriver3(u32 id) const { return _gfbrs::getVoiceTableDriver3(*unknown70, id); }

const char *GfBdatRsc::getVoiceTableDriver4(u32 id) const { return _gfbrs::getVoiceTableDriver4(*unknown70, id); }

const char *GfBdatRsc::getVoiceTableDriver5(u32 id) const { return _gfbrs::getVoiceTableDriver5(*unknown70, id); }

const char *GfBdatRsc::getVoiceTableDriver6(u32 id) const { return _gfbrs::getVoiceTableDriver6(*unknown70, id); }

u32 GfBdatRsc::getVoiceTableBladeStart() const { return Bdat::getIdTop(unknown78->data); }

const char *GfBdatRsc::getVoiceTableBladeBlade1(u32 id) const { return _gfbrs::getVoiceTableBladeBlade1(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade2(u32 id) const { return _gfbrs::getVoiceTableBladeBlade2(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade3(u32 id) const { return _gfbrs::getVoiceTableBladeBlade3(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade4(u32 id) const { return _gfbrs::getVoiceTableBladeBlade4(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade5(u32 id) const { return _gfbrs::getVoiceTableBladeBlade5(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade6(u32 id) const { return _gfbrs::getVoiceTableBladeBlade6(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade7(u32 id) const { return _gfbrs::getVoiceTableBladeBlade7(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade8(u32 id) const { return _gfbrs::getVoiceTableBladeBlade8(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade9(u32 id) const { return _gfbrs::getVoiceTableBladeBlade9(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade10(u32 id) const { return _gfbrs::getVoiceTableBladeBlade10(*unknown78, id); }

const char *GfBdatRsc::getVoiceTableBladeBlade11(u32 id) const { return _gfbrs::getVoiceTableBladeBlade11(*unknown78, id); }

u32 GfBdatRsc::getVoiceTableRareStart() const { return Bdat::getIdTop(unknown80->data); }

const char *GfBdatRsc::getVoiceTableRareRareBlade1(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade1(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade2(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade2(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade3(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade3(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade4(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade4(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade5(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade5(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade6(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade6(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade7(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade7(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade8(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade8(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade9(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade9(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade10(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade10(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade11(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade11(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade12(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade12(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade13(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade13(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade14(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade14(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade15(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade15(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade16(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade16(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade17(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade17(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade18(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade18(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade19(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade19(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade20(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade20(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade21(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade21(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade22(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade22(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade23(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade23(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade24(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade24(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade25(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade25(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade26(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade26(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade27(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade27(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade28(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade28(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade29(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade29(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade30(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade30(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade31(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade31(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade32(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade32(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade33(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade33(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade34(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade34(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade35(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade35(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade36(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade36(*unknown80, id); }

const char *GfBdatRsc::getVoiceTableRareRareBlade37(u32 id) const { return _gfbrs::getVoiceTableRareRareBlade37(*unknown80, id); }

u32 GfBdatRsc::getVoiceTableCommonStart() const { return Bdat::getIdTop(unknown88->data); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade1(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade1(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade2(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade2(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade3(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade3(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade4(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade4(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade5(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade5(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade6(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade6(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade7(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade7(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade8(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade8(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade9(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade9(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade10(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade10(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade11(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade11(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade12(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade12(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade13(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade13(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade14(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade14(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade15(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade15(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade16(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade16(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade17(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade17(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade18(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade18(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade19(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade19(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade20(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade20(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade21(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade21(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade22(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade22(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade23(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade23(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade24(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade24(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade25(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade25(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade26(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade26(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade27(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade27(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade28(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade28(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade29(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade29(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade30(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade30(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade31(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade31(*unknown88, id); }

const char *GfBdatRsc::getVoiceTableCommonCommonBlade32(u32 id) const { return _gfbrs::getVoiceTableCommonCommonBlade32(*unknown88, id); }

u32 GfBdatRsc::getFLD_actorSEStart() const { return Bdat::getIdTop(unknown90->data); }

const char *GfBdatRsc::getFLD_actorSELOD(u32 id) const { return _gfbrs::getFLD_actorSELOD(*unknown90, id); }

u32 GfBdatRsc::getFLD_actorSEse_type(u32 id) const { return _gfbrs::getFLD_actorSEse_type(*unknown90, id); }

u32 GfBdatRsc::getFLD_actorSEseName(u32 id) const { return _gfbrs::getFLD_actorSEseName(*unknown90, id); }

f32 GfBdatRsc::getFLD_actorSEmax_volume_Dist(u32 id) const { return _gfbrs::getFLD_actorSEmax_volume_Dist(*unknown90, id); }

f32 GfBdatRsc::getFLD_actorSEmin_volume_Dist(u32 id) const { return _gfbrs::getFLD_actorSEmin_volume_Dist(*unknown90, id); }

u32 GfBdatRsc::getFLD_actorSEvolumeMAX(u32 id) const { return _gfbrs::getFLD_actorSEvolumeMAX(*unknown90, id); }

u32 GfBdatRsc::getFLD_actorSEvolumeMIN(u32 id) const { return _gfbrs::getFLD_actorSEvolumeMIN(*unknown90, id); }

f32 GfBdatRsc::getFLD_actorSEoffsetX(u32 id) const { return _gfbrs::getFLD_actorSEoffsetX(*unknown90, id); }

f32 GfBdatRsc::getFLD_actorSEoffsetY(u32 id) const { return _gfbrs::getFLD_actorSEoffsetY(*unknown90, id); }

f32 GfBdatRsc::getFLD_actorSEoffsetZ(u32 id) const { return _gfbrs::getFLD_actorSEoffsetZ(*unknown90, id); }

} // namespace gf
