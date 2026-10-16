#include "gf/data/gf_bdat_btl.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbbt {

enum {
  ArtsDrName,
  ArtsDrDebugName,
  ArtsDrCaption,
  ArtsDrDriver,
  ArtsDrWpnType,
  ArtsDrActNo,
  ArtsDrArtsType,
  ArtsDrArtsBuff,
  ArtsDrAtrType,
  ArtsDrFlagNormal,
  ArtsDrFlagNormalFlag,
  ArtsDrFlagPierce,
  ArtsDrFlagPierceFlag,
  ArtsDrFlagNoRepelled,
  ArtsDrFlagNoRepelledFlag,
  ArtsDrNextArts,
  ArtsDrTarget,
  ArtsDrDistance,
  ArtsDrRangeType,
  ArtsDrRadius,
  ArtsDrLength,
  ArtsDrHate,
  ArtsDrHitRevise,
  ArtsDrCriRevise,
  ArtsDrBulletID,
  ArtsDrBulletNum,
  ArtsDrHitFrm1,
  ArtsDrHitFrm2,
  ArtsDrHitFrm3,
  ArtsDrHitFrm4,
  ArtsDrHitFrm5,
  ArtsDrHitFrm6,
  ArtsDrHitFrm7,
  ArtsDrHitFrm8,
  ArtsDrHitFrm9,
  ArtsDrHitFrm10,
  ArtsDrHitFrm11,
  ArtsDrHitFrm12,
  ArtsDrHitFrm13,
  ArtsDrHitFrm14,
  ArtsDrHitFrm15,
  ArtsDrHitFrm16,
  ArtsDrEfp1,
  ArtsDrEfp2,
  ArtsDrEfp3,
  ArtsDrEfp4,
  ArtsDrEfp5,
  ArtsDrEfp6,
  ArtsDrEfp7,
  ArtsDrEfp8,
  ArtsDrEfp9,
  ArtsDrEfp10,
  ArtsDrEfp11,
  ArtsDrEfp12,
  ArtsDrEfp13,
  ArtsDrEfp14,
  ArtsDrEfp15,
  ArtsDrEfp16,
  ArtsDrHitDirID1,
  ArtsDrHitDirID2,
  ArtsDrHitDirID3,
  ArtsDrHitDirID4,
  ArtsDrHitDirID5,
  ArtsDrHitDirID6,
  ArtsDrHitDirID7,
  ArtsDrHitDirID8,
  ArtsDrHitDirID9,
  ArtsDrHitDirID10,
  ArtsDrHitDirID11,
  ArtsDrHitDirID12,
  ArtsDrHitDirID13,
  ArtsDrHitDirID14,
  ArtsDrHitDirID15,
  ArtsDrHitDirID16,
  ArtsDrDmgRt1,
  ArtsDrDmgRt2,
  ArtsDrDmgRt3,
  ArtsDrDmgRt4,
  ArtsDrDmgRt5,
  ArtsDrDmgRt6,
  ArtsDrDmgRt7,
  ArtsDrDmgRt8,
  ArtsDrDmgRt9,
  ArtsDrDmgRt10,
  ArtsDrDmgRt11,
  ArtsDrDmgRt12,
  ArtsDrDmgRt13,
  ArtsDrDmgRt14,
  ArtsDrDmgRt15,
  ArtsDrDmgRt16,
  ArtsDrReAct1,
  ArtsDrReAct2,
  ArtsDrReAct3,
  ArtsDrReAct4,
  ArtsDrReAct5,
  ArtsDrReAct6,
  ArtsDrReAct7,
  ArtsDrReAct8,
  ArtsDrReAct9,
  ArtsDrReAct10,
  ArtsDrReAct11,
  ArtsDrReAct12,
  ArtsDrReAct13,
  ArtsDrReAct14,
  ArtsDrReAct15,
  ArtsDrReAct16,
  ArtsDrMoveCancelFrm,
  ArtsDrDmgMgn1,
  ArtsDrDmgMgn2,
  ArtsDrDmgMgn3,
  ArtsDrDmgMgn4,
  ArtsDrDmgMgn5,
  ArtsDrDmgMgn6,
  ArtsDrRecast1,
  ArtsDrRecast2,
  ArtsDrRecast3,
  ArtsDrRecast4,
  ArtsDrRecast5,
  ArtsDrRecast6,
  ArtsDrAtrNum,
  ArtsDrEnhance1,
  ArtsDrEnhance2,
  ArtsDrEnhance3,
  ArtsDrEnhance4,
  ArtsDrEnhance5,
  ArtsDrEnhance6,
  ArtsDrReleaseLv1,
  ArtsDrReleaseLv2,
  ArtsDrReleaseLv3,
  ArtsDrReleaseLv4,
  ArtsDrReleaseLv5,
  ArtsDrNeedWP2,
  ArtsDrNeedWP3,
  ArtsDrNeedWP4,
  ArtsDrNeedWP5,
  ArtsDrUI,
  ArtsDrPriority,
  ArtsBlName,
  ArtsBlDebugName,
  ArtsBlCaption,
  ArtsBlWpnType,
  ArtsBlCmnBlType,
  ArtsBlSpLv,
  ArtsBlActNo,
  ArtsBlArtsType,
  ArtsBlArtsBuff,
  ArtsBlFlagcommon,
  ArtsBlFlagcommonFlag,
  ArtsBlFlagPierce,
  ArtsBlFlagPierceFlag,
  ArtsBlTarget,
  ArtsBlDistance,
  ArtsBlRangeType,
  ArtsBlRadius,
  ArtsBlLength,
  ArtsBlAtr,
  ArtsBlHate,
  ArtsBlHitRevise,
  ArtsBlCriRevise,
  ArtsBlBulletID,
  ArtsBlBulletNum,
  ArtsBlHitFrm1,
  ArtsBlHitFrm2,
  ArtsBlHitFrm3,
  ArtsBlHitFrm4,
  ArtsBlHitFrm5,
  ArtsBlHitFrm6,
  ArtsBlHitFrm7,
  ArtsBlHitFrm8,
  ArtsBlHitFrm9,
  ArtsBlHitFrm10,
  ArtsBlHitFrm11,
  ArtsBlHitFrm12,
  ArtsBlHitFrm13,
  ArtsBlHitFrm14,
  ArtsBlHitFrm15,
  ArtsBlHitFrm16,
  ArtsBlEfp1,
  ArtsBlEfp2,
  ArtsBlEfp3,
  ArtsBlEfp4,
  ArtsBlEfp5,
  ArtsBlEfp6,
  ArtsBlEfp7,
  ArtsBlEfp8,
  ArtsBlEfp9,
  ArtsBlEfp10,
  ArtsBlEfp11,
  ArtsBlEfp12,
  ArtsBlEfp13,
  ArtsBlEfp14,
  ArtsBlEfp15,
  ArtsBlEfp16,
  ArtsBlHitDirID1,
  ArtsBlHitDirID2,
  ArtsBlHitDirID3,
  ArtsBlHitDirID4,
  ArtsBlHitDirID5,
  ArtsBlHitDirID6,
  ArtsBlHitDirID7,
  ArtsBlHitDirID8,
  ArtsBlHitDirID9,
  ArtsBlHitDirID10,
  ArtsBlHitDirID11,
  ArtsBlHitDirID12,
  ArtsBlHitDirID13,
  ArtsBlHitDirID14,
  ArtsBlHitDirID15,
  ArtsBlHitDirID16,
  ArtsBlDmgRt1,
  ArtsBlDmgRt2,
  ArtsBlDmgRt3,
  ArtsBlDmgRt4,
  ArtsBlDmgRt5,
  ArtsBlDmgRt6,
  ArtsBlDmgRt7,
  ArtsBlDmgRt8,
  ArtsBlDmgRt9,
  ArtsBlDmgRt10,
  ArtsBlDmgRt11,
  ArtsBlDmgRt12,
  ArtsBlDmgRt13,
  ArtsBlDmgRt14,
  ArtsBlDmgRt15,
  ArtsBlDmgRt16,
  ArtsBlReAct1,
  ArtsBlReAct2,
  ArtsBlReAct3,
  ArtsBlReAct4,
  ArtsBlReAct5,
  ArtsBlReAct6,
  ArtsBlReAct7,
  ArtsBlReAct8,
  ArtsBlReAct9,
  ArtsBlReAct10,
  ArtsBlReAct11,
  ArtsBlReAct12,
  ArtsBlReAct13,
  ArtsBlReAct14,
  ArtsBlReAct15,
  ArtsBlReAct16,
  ArtsBlDmgMgn1,
  ArtsBlDmgMgn2,
  ArtsBlDmgMgn3,
  ArtsBlDmgMgn4,
  ArtsBlDmgMgn5,
  ArtsBlDmgMgn6,
  ArtsBlAtrNum,
  ArtsBlEnhance1,
  ArtsBlEnhance2,
  ArtsBlEnhance3,
  ArtsBlEnhance4,
  ArtsBlEnhance5,
  ArtsBlEnhance6,
  ArtsBlBtnType,
  ArtsBlBtnChal1,
  ArtsBlUI,
  ArtsBlSpName,
  ArtsBlSpDebugName,
  ArtsBlSpCaption,
  ArtsBlSpWpnType,
  ArtsBlSpCmnBlType,
  ArtsBlSpActNoDr,
  ArtsBlSpActNoBl,
  ArtsBlSpActNoBl2,
  ArtsBlSpBuddyDr,
  ArtsBlSpAddBl,
  ArtsBlSpActType,
  ArtsBlSpPC01,
  ArtsBlSpPC02,
  ArtsBlSpPC03,
  ArtsBlSpPC06,
  ArtsBlSpArtsType,
  ArtsBlSpArtsBuff,
  ArtsBlSpFlagPierce,
  ArtsBlSpFlagPierceFlag,
  ArtsBlSpFlagNoMove,
  ArtsBlSpFlagNoMoveFlag,
  ArtsBlSpTarget,
  ArtsBlSpDistance,
  ArtsBlSpRangeType,
  ArtsBlSpRadius,
  ArtsBlSpLength,
  ArtsBlSpAtr,
  ArtsBlSpHate,
  ArtsBlSpHitRevise,
  ArtsBlSpCriRevise,
  ArtsBlSpBulletID,
  ArtsBlSpBulletEffID,
  ArtsBlSpBulletNum,
  ArtsBlSpHitFrm1,
  ArtsBlSpHitFrm2,
  ArtsBlSpHitFrm3,
  ArtsBlSpHitFrm4,
  ArtsBlSpHitFrm5,
  ArtsBlSpHitFrm6,
  ArtsBlSpHitFrm7,
  ArtsBlSpHitFrm8,
  ArtsBlSpHitFrm9,
  ArtsBlSpHitFrm10,
  ArtsBlSpHitFrm11,
  ArtsBlSpHitFrm12,
  ArtsBlSpHitFrm13,
  ArtsBlSpHitFrm14,
  ArtsBlSpHitFrm15,
  ArtsBlSpHitFrm16,
  ArtsBlSpEfp1,
  ArtsBlSpEfp2,
  ArtsBlSpEfp3,
  ArtsBlSpEfp4,
  ArtsBlSpEfp5,
  ArtsBlSpEfp6,
  ArtsBlSpEfp7,
  ArtsBlSpEfp8,
  ArtsBlSpEfp9,
  ArtsBlSpEfp10,
  ArtsBlSpEfp11,
  ArtsBlSpEfp12,
  ArtsBlSpEfp13,
  ArtsBlSpEfp14,
  ArtsBlSpEfp15,
  ArtsBlSpEfp16,
  ArtsBlSpHitDirID1,
  ArtsBlSpHitDirID2,
  ArtsBlSpHitDirID3,
  ArtsBlSpHitDirID4,
  ArtsBlSpHitDirID5,
  ArtsBlSpHitDirID6,
  ArtsBlSpHitDirID7,
  ArtsBlSpHitDirID8,
  ArtsBlSpHitDirID9,
  ArtsBlSpHitDirID10,
  ArtsBlSpHitDirID11,
  ArtsBlSpHitDirID12,
  ArtsBlSpHitDirID13,
  ArtsBlSpHitDirID14,
  ArtsBlSpHitDirID15,
  ArtsBlSpHitDirID16,
  ArtsBlSpDmgRt1,
  ArtsBlSpDmgRt2,
  ArtsBlSpDmgRt3,
  ArtsBlSpDmgRt4,
  ArtsBlSpDmgRt5,
  ArtsBlSpDmgRt6,
  ArtsBlSpDmgRt7,
  ArtsBlSpDmgRt8,
  ArtsBlSpDmgRt9,
  ArtsBlSpDmgRt10,
  ArtsBlSpDmgRt11,
  ArtsBlSpDmgRt12,
  ArtsBlSpDmgRt13,
  ArtsBlSpDmgRt14,
  ArtsBlSpDmgRt15,
  ArtsBlSpDmgRt16,
  ArtsBlSpReAct1,
  ArtsBlSpReAct2,
  ArtsBlSpReAct3,
  ArtsBlSpReAct4,
  ArtsBlSpReAct5,
  ArtsBlSpReAct6,
  ArtsBlSpReAct7,
  ArtsBlSpReAct8,
  ArtsBlSpReAct9,
  ArtsBlSpReAct10,
  ArtsBlSpReAct11,
  ArtsBlSpReAct12,
  ArtsBlSpReAct13,
  ArtsBlSpReAct14,
  ArtsBlSpReAct15,
  ArtsBlSpReAct16,
  ArtsBlSpDmgMgn,
  ArtsBlSpRecast,
  ArtsBlSpAtrNum,
  ArtsBlSpEnhance,
  ArtsBlSpBtnType,
  ArtsBlSpBtnChal1,
  ArtsBlSpCamera1,
  ArtsBlSpCamera2,
  ArtsBlSpCamera3,
  ArtsBlSpCameraCT1,
  ArtsBlSpCameraCT2,
  ArtsBlSpCameraEndf,
  ArtsBlSpHitEff,
  GrowLevelExp,
  GrowEnemyExp,
  GrowEnemyWP,
  GrowEnemySP,
  GrowEnemyGold,
  GrowGoldDivide,
  Lv_RevExpRevHigh,
  Lv_RevExpRevLow,
  Lv_RevDamageRevHigh,
  Lv_RevDamageRevLow,
  Wpn_EnRscR,
  Wpn_EnRscL,
  Wpn_EnTypeRange,
  Wpn_EnDamage,
  Wpn_EnStability,
  BTL_ClassName,
  BTL_ClassRole1,
  BTL_ClassRole2,
  BTL_ClassRole3,
  BTL_ClassDamageDown,
  BTL_ClassDamageUP,
  BTL_ClassHealUP,
  BTL_ClassAutoHate,
  BTL_ClassArtsHate,
  BTL_EnhanceEnhanceEffect,
  BTL_EnhanceParam1,
  BTL_EnhanceParam2,
  BTL_EnhanceCaption,
  BTL_EnhanceEffCategory,
  BTL_EnhanceEffIcon,
  BTL_EnhanceEffFlagCondition,
  BTL_EnhanceEffFlagConditionFlag,
  BTL_EnhanceEffFlagUI,
  BTL_EnhanceEffFlagUIFlag,
  BTL_EnhanceEffParam,
  BTL_EnhanceEffName,
  BTL_EnhanceEffDirect,
  BTL_Skill_BlName,
  BTL_Skill_BlDebugName,
  BTL_Skill_BlEnhance1,
  BTL_Skill_BlEnhance2,
  BTL_Skill_BlEnhance3,
  BTL_Skill_BlEnhance4,
  BTL_Skill_BlEnhance5,
  BTL_Skill_BlFlagcommon,
  BTL_Skill_BlFlagcommonFlag,
  BTL_Skill_BlTank,
  BTL_Skill_BlAttacker,
  BTL_Skill_BlHealer,
  BTL_Skill_BlUI,
  BTL_Skill_DrName,
  BTL_Skill_DrDebugName,
  BTL_Skill_DrEnhance,
  BTL_Skill_DrUI,
  BTL_BuffName,
  BTL_BuffDebugName,
  BTL_BuffCaption,
  BTL_BuffBaseNum,
  BTL_BuffBaseTime,
  BTL_BuffBaseRecast,
  BTL_BuffBaseProb,
  BTL_BuffInterval,
  BTL_BuffEffect,
  BTL_BuffIcon,
  BTL_Bl_PersonalityFlagcommon,
  BTL_Bl_PersonalityFlagcommonFlag,
  BTL_Bl_PersonalityKizunaBase,
  BTL_Bl_PersonalityVoiceID,
  BTL_Bl_KizunaLinkLinkNum,
  BTL_Bl_KizunaLinkDeadNum,
  BTL_Bl_KizunaLinkAppStNum,
  BTL_Bl_KizunaLinkAppEndNum,
  BTL_Bl_KizunaLinkAppCond,
  BTL_Bl_KizunaLinkAppCondNum,
  BTL_Bl_KizunaLinkReJudgef,
  BTL_Bl_KizunaLinkSpActType,
  BTL_Bl_KizunaLinkSpActNum,
  BTL_Bl_KizunaLinkSpActf,
  BTL_Bl_KizunaLinkStandDir,
  BTL_Bl_KizunaLinkSetKizunaLink1,
  BTL_Bl_KizunaLinkSetKizunaLink2,
  BTL_Bl_KizunaLinkSetLinkChType,
  BTL_Bl_KizunaLinkSetLinkChNum,
  BTL_Bl_KizunaLinkSetVoiceID,
  BTL_TestSettingDr1,
  BTL_TestSettingDr1Lv,
  BTL_TestSettingDr1Bl1,
  BTL_TestSettingDr1Bl2,
  BTL_TestSettingDr1Bl3,
  BTL_TestSettingDr2,
  BTL_TestSettingDr2Lv,
  BTL_TestSettingDr2Bl1,
  BTL_TestSettingDr2Bl2,
  BTL_TestSettingDr2Bl3,
  BTL_TestSettingDr3,
  BTL_TestSettingDr3Lv,
  BTL_TestSettingDr3Bl1,
  BTL_TestSettingDr3Bl2,
  BTL_TestSettingDr3Bl3,
  BTL_HanaBaseNCondNum,
  BTL_HanaBaseECondNum,
  BTL_HanaBaseNArtsNum,
  BTL_HanaBaseCircuit1Num,
  BTL_HanaBaseCircuit2Num,
  BTL_HanaBaseCircuit3Num,
  BTL_HanaBaseCircuit4Num,
  BTL_HanaBaseCircuit5Num,
  BTL_HanaBaseCircuit6Num,
  BTL_HanaBaseUI,
  BTL_HanaPowerPowerNum1,
  BTL_HanaPowerPowerNum2,
  BTL_HanaPowerPowerNum3,
  BTL_HanaPowerEtherNum1,
  BTL_HanaPowerEtherNum2,
  BTL_HanaPowerEtherNum3,
  BTL_HanaChipsetRoleParts,
  BTL_HanaChipsetAtrParts,
  BTL_HanaChipsetNArtsParts1,
  BTL_HanaChipsetNArtsParts2,
  BTL_HanaChipsetNArtsParts3,
  BTL_HanaChipsetNCondParts1,
  BTL_HanaChipsetNCondParts2,
  BTL_HanaChipsetNCondParts3,
  BTL_HanaChipsetUI,
  WildcardDatavalueF4,
  WildcardDatavalueU2,
  Vo_Field_FilterTargetFile,
  Vo_Field_FilterCondition,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];
static u8 *s_Vo_Field_FilterChangeFile;

void initArtsDrName(const CBdatWrapper &wrapper) { s_members[ArtsDrName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getArtsDrName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrName], id, 2).valueU16;
}

void initArtsDrDebugName(const CBdatWrapper &wrapper) { s_members[ArtsDrDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getArtsDrDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsDrDebugName], id, 7).valueString;
}

void initArtsDrCaption(const CBdatWrapper &wrapper) { s_members[ArtsDrCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getArtsDrCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrCaption], id, 2).valueU16;
}

void initArtsDrDriver(const CBdatWrapper &wrapper) { s_members[ArtsDrDriver] = Bdat::getMember(wrapper.data, "Driver"); }

u32 getArtsDrDriver(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDriver] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDriver], id, 1).valueU8;
}

void initArtsDrWpnType(const CBdatWrapper &wrapper) { s_members[ArtsDrWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getArtsDrWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrWpnType], id, 1).valueU8;
}

void initArtsDrActNo(const CBdatWrapper &wrapper) { s_members[ArtsDrActNo] = Bdat::getMember(wrapper.data, "ActNo"); }

u32 getArtsDrActNo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrActNo] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrActNo], id, 1).valueU8;
}

void initArtsDrArtsType(const CBdatWrapper &wrapper) { s_members[ArtsDrArtsType] = Bdat::getMember(wrapper.data, "ArtsType"); }

u32 getArtsDrArtsType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrArtsType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrArtsType], id, 1).valueU8;
}

void initArtsDrArtsBuff(const CBdatWrapper &wrapper) { s_members[ArtsDrArtsBuff] = Bdat::getMember(wrapper.data, "ArtsBuff"); }

u32 getArtsDrArtsBuff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrArtsBuff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrArtsBuff], id, 1).valueU8;
}

void initArtsDrAtrType(const CBdatWrapper &wrapper) { s_members[ArtsDrAtrType] = Bdat::getMember(wrapper.data, "AtrType"); }

u32 getArtsDrAtrType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrAtrType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrAtrType], id, 1).valueU8;
}

void initArtsDrFlagNormal(const CBdatWrapper &wrapper) {
  s_members[ArtsDrFlagNormal] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsDrFlagNormalFlag] = Bdat::getMember(wrapper.data, "Normal");
}

bool isArtsDrFlagNormal(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrFlagNormal] == nullptr || s_members[ArtsDrFlagNormalFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsDrFlagNormal], id, s_members[ArtsDrFlagNormalFlag]) != 0;
}

void initArtsDrFlagPierce(const CBdatWrapper &wrapper) {
  s_members[ArtsDrFlagPierce] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsDrFlagPierceFlag] = Bdat::getMember(wrapper.data, "Pierce");
}

bool isArtsDrFlagPierce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrFlagPierce] == nullptr || s_members[ArtsDrFlagPierceFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsDrFlagPierce], id, s_members[ArtsDrFlagPierceFlag]) != 0;
}

void initArtsDrFlagNoRepelled(const CBdatWrapper &wrapper) {
  s_members[ArtsDrFlagNoRepelled] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsDrFlagNoRepelledFlag] = Bdat::getMember(wrapper.data, "NoRepelled");
}

bool isArtsDrFlagNoRepelled(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrFlagNoRepelled] == nullptr || s_members[ArtsDrFlagNoRepelledFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsDrFlagNoRepelled], id, s_members[ArtsDrFlagNoRepelledFlag]) != 0;
}

void initArtsDrNextArts(const CBdatWrapper &wrapper) { s_members[ArtsDrNextArts] = Bdat::getMember(wrapper.data, "NextArts"); }

u32 getArtsDrNextArts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNextArts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNextArts], id, 2).valueU16;
}

void initArtsDrTarget(const CBdatWrapper &wrapper) { s_members[ArtsDrTarget] = Bdat::getMember(wrapper.data, "Target"); }

u32 getArtsDrTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrTarget] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrTarget], id, 1).valueU8;
}

void initArtsDrDistance(const CBdatWrapper &wrapper) { s_members[ArtsDrDistance] = Bdat::getMember(wrapper.data, "Distance"); }

u32 getArtsDrDistance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDistance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDistance], id, 2).valueU16;
}

void initArtsDrRangeType(const CBdatWrapper &wrapper) { s_members[ArtsDrRangeType] = Bdat::getMember(wrapper.data, "RangeType"); }

u32 getArtsDrRangeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRangeType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRangeType], id, 1).valueU8;
}

void initArtsDrRadius(const CBdatWrapper &wrapper) { s_members[ArtsDrRadius] = Bdat::getMember(wrapper.data, "Radius"); }

u32 getArtsDrRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRadius] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRadius], id, 2).valueU16;
}

void initArtsDrLength(const CBdatWrapper &wrapper) { s_members[ArtsDrLength] = Bdat::getMember(wrapper.data, "Length"); }

u32 getArtsDrLength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrLength] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrLength], id, 2).valueU16;
}

void initArtsDrHate(const CBdatWrapper &wrapper) { s_members[ArtsDrHate] = Bdat::getMember(wrapper.data, "Hate"); }

s32 getArtsDrHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHate] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHate], id, 4).valueS8;
}

void initArtsDrHitRevise(const CBdatWrapper &wrapper) { s_members[ArtsDrHitRevise] = Bdat::getMember(wrapper.data, "HitRevise"); }

s32 getArtsDrHitRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitRevise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitRevise], id, 4).valueS8;
}

void initArtsDrCriRevise(const CBdatWrapper &wrapper) { s_members[ArtsDrCriRevise] = Bdat::getMember(wrapper.data, "CriRevise"); }

s32 getArtsDrCriRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrCriRevise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrCriRevise], id, 4).valueS8;
}

void initArtsDrBulletID(const CBdatWrapper &wrapper) { s_members[ArtsDrBulletID] = Bdat::getMember(wrapper.data, "BulletID"); }

u32 getArtsDrBulletID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrBulletID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrBulletID], id, 2).valueU16;
}

void initArtsDrBulletNum(const CBdatWrapper &wrapper) { s_members[ArtsDrBulletNum] = Bdat::getMember(wrapper.data, "BulletNum"); }

u32 getArtsDrBulletNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrBulletNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrBulletNum], id, 1).valueU8;
}

void initArtsDrHitFrm1(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm1] = Bdat::getMember(wrapper.data, "HitFrm1"); }

u32 getArtsDrHitFrm1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm1], id, 1).valueU8;
}

void initArtsDrHitFrm2(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm2] = Bdat::getMember(wrapper.data, "HitFrm2"); }

u32 getArtsDrHitFrm2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm2], id, 1).valueU8;
}

void initArtsDrHitFrm3(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm3] = Bdat::getMember(wrapper.data, "HitFrm3"); }

u32 getArtsDrHitFrm3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm3], id, 1).valueU8;
}

void initArtsDrHitFrm4(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm4] = Bdat::getMember(wrapper.data, "HitFrm4"); }

u32 getArtsDrHitFrm4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm4], id, 1).valueU8;
}

void initArtsDrHitFrm5(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm5] = Bdat::getMember(wrapper.data, "HitFrm5"); }

u32 getArtsDrHitFrm5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm5], id, 1).valueU8;
}

void initArtsDrHitFrm6(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm6] = Bdat::getMember(wrapper.data, "HitFrm6"); }

u32 getArtsDrHitFrm6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm6], id, 1).valueU8;
}

void initArtsDrHitFrm7(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm7] = Bdat::getMember(wrapper.data, "HitFrm7"); }

u32 getArtsDrHitFrm7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm7], id, 1).valueU8;
}

void initArtsDrHitFrm8(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm8] = Bdat::getMember(wrapper.data, "HitFrm8"); }

u32 getArtsDrHitFrm8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm8], id, 1).valueU8;
}

void initArtsDrHitFrm9(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm9] = Bdat::getMember(wrapper.data, "HitFrm9"); }

u32 getArtsDrHitFrm9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm9], id, 1).valueU8;
}

void initArtsDrHitFrm10(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm10] = Bdat::getMember(wrapper.data, "HitFrm10"); }

u32 getArtsDrHitFrm10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm10], id, 1).valueU8;
}

void initArtsDrHitFrm11(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm11] = Bdat::getMember(wrapper.data, "HitFrm11"); }

u32 getArtsDrHitFrm11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm11], id, 1).valueU8;
}

void initArtsDrHitFrm12(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm12] = Bdat::getMember(wrapper.data, "HitFrm12"); }

u32 getArtsDrHitFrm12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm12], id, 1).valueU8;
}

void initArtsDrHitFrm13(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm13] = Bdat::getMember(wrapper.data, "HitFrm13"); }

u32 getArtsDrHitFrm13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm13], id, 1).valueU8;
}

void initArtsDrHitFrm14(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm14] = Bdat::getMember(wrapper.data, "HitFrm14"); }

u32 getArtsDrHitFrm14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm14], id, 1).valueU8;
}

void initArtsDrHitFrm15(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm15] = Bdat::getMember(wrapper.data, "HitFrm15"); }

u32 getArtsDrHitFrm15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm15], id, 1).valueU8;
}

void initArtsDrHitFrm16(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm16] = Bdat::getMember(wrapper.data, "HitFrm16"); }

u32 getArtsDrHitFrm16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm16], id, 1).valueU8;
}

void initArtsDrEfp1(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp1] = Bdat::getMember(wrapper.data, "Efp1"); }

u32 getArtsDrEfp1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp1], id, 1).valueU8;
}

void initArtsDrEfp2(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp2] = Bdat::getMember(wrapper.data, "Efp2"); }

u32 getArtsDrEfp2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp2], id, 1).valueU8;
}

void initArtsDrEfp3(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp3] = Bdat::getMember(wrapper.data, "Efp3"); }

u32 getArtsDrEfp3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp3], id, 1).valueU8;
}

void initArtsDrEfp4(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp4] = Bdat::getMember(wrapper.data, "Efp4"); }

u32 getArtsDrEfp4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp4] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp4], id, 1).valueU8;
}

void initArtsDrEfp5(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp5] = Bdat::getMember(wrapper.data, "Efp5"); }

u32 getArtsDrEfp5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp5] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp5], id, 1).valueU8;
}

void initArtsDrEfp6(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp6] = Bdat::getMember(wrapper.data, "Efp6"); }

u32 getArtsDrEfp6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp6] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp6], id, 1).valueU8;
}

void initArtsDrEfp7(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp7] = Bdat::getMember(wrapper.data, "Efp7"); }

u32 getArtsDrEfp7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp7] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp7], id, 1).valueU8;
}

void initArtsDrEfp8(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp8] = Bdat::getMember(wrapper.data, "Efp8"); }

u32 getArtsDrEfp8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp8] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp8], id, 1).valueU8;
}

void initArtsDrEfp9(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp9] = Bdat::getMember(wrapper.data, "Efp9"); }

u32 getArtsDrEfp9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp9] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp9], id, 1).valueU8;
}

void initArtsDrEfp10(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp10] = Bdat::getMember(wrapper.data, "Efp10"); }

u32 getArtsDrEfp10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp10] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp10], id, 1).valueU8;
}

void initArtsDrEfp11(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp11] = Bdat::getMember(wrapper.data, "Efp11"); }

u32 getArtsDrEfp11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp11] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp11], id, 1).valueU8;
}

void initArtsDrEfp12(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp12] = Bdat::getMember(wrapper.data, "Efp12"); }

u32 getArtsDrEfp12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp12] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp12], id, 1).valueU8;
}

void initArtsDrEfp13(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp13] = Bdat::getMember(wrapper.data, "Efp13"); }

u32 getArtsDrEfp13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp13] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp13], id, 1).valueU8;
}

void initArtsDrEfp14(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp14] = Bdat::getMember(wrapper.data, "Efp14"); }

u32 getArtsDrEfp14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp14] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp14], id, 1).valueU8;
}

void initArtsDrEfp15(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp15] = Bdat::getMember(wrapper.data, "Efp15"); }

u32 getArtsDrEfp15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp15] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp15], id, 1).valueU8;
}

void initArtsDrEfp16(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp16] = Bdat::getMember(wrapper.data, "Efp16"); }

u32 getArtsDrEfp16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp16] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp16], id, 1).valueU8;
}

void initArtsDrHitDirID1(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID1] = Bdat::getMember(wrapper.data, "HitDirID1"); }

u32 getArtsDrHitDirID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID1], id, 1).valueU8;
}

void initArtsDrHitDirID2(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID2] = Bdat::getMember(wrapper.data, "HitDirID2"); }

u32 getArtsDrHitDirID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID2], id, 1).valueU8;
}

void initArtsDrHitDirID3(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID3] = Bdat::getMember(wrapper.data, "HitDirID3"); }

u32 getArtsDrHitDirID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID3], id, 1).valueU8;
}

void initArtsDrHitDirID4(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID4] = Bdat::getMember(wrapper.data, "HitDirID4"); }

u32 getArtsDrHitDirID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID4], id, 1).valueU8;
}

void initArtsDrHitDirID5(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID5] = Bdat::getMember(wrapper.data, "HitDirID5"); }

u32 getArtsDrHitDirID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID5], id, 1).valueU8;
}

void initArtsDrHitDirID6(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID6] = Bdat::getMember(wrapper.data, "HitDirID6"); }

u32 getArtsDrHitDirID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID6], id, 1).valueU8;
}

void initArtsDrHitDirID7(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID7] = Bdat::getMember(wrapper.data, "HitDirID7"); }

u32 getArtsDrHitDirID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID7], id, 1).valueU8;
}

void initArtsDrHitDirID8(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID8] = Bdat::getMember(wrapper.data, "HitDirID8"); }

u32 getArtsDrHitDirID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID8], id, 1).valueU8;
}

void initArtsDrHitDirID9(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID9] = Bdat::getMember(wrapper.data, "HitDirID9"); }

u32 getArtsDrHitDirID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID9], id, 1).valueU8;
}

void initArtsDrHitDirID10(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID10] = Bdat::getMember(wrapper.data, "HitDirID10"); }

u32 getArtsDrHitDirID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID10], id, 1).valueU8;
}

void initArtsDrHitDirID11(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID11] = Bdat::getMember(wrapper.data, "HitDirID11"); }

u32 getArtsDrHitDirID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID11], id, 1).valueU8;
}

void initArtsDrHitDirID12(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID12] = Bdat::getMember(wrapper.data, "HitDirID12"); }

u32 getArtsDrHitDirID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID12], id, 1).valueU8;
}

void initArtsDrHitDirID13(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID13] = Bdat::getMember(wrapper.data, "HitDirID13"); }

u32 getArtsDrHitDirID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID13], id, 1).valueU8;
}

void initArtsDrHitDirID14(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID14] = Bdat::getMember(wrapper.data, "HitDirID14"); }

u32 getArtsDrHitDirID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID14], id, 1).valueU8;
}

void initArtsDrHitDirID15(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID15] = Bdat::getMember(wrapper.data, "HitDirID15"); }

u32 getArtsDrHitDirID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID15], id, 1).valueU8;
}

void initArtsDrHitDirID16(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID16] = Bdat::getMember(wrapper.data, "HitDirID16"); }

u32 getArtsDrHitDirID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID16], id, 1).valueU8;
}

void initArtsDrDmgRt1(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt1] = Bdat::getMember(wrapper.data, "DmgRt1"); }

u32 getArtsDrDmgRt1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt1], id, 1).valueU8;
}

void initArtsDrDmgRt2(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt2] = Bdat::getMember(wrapper.data, "DmgRt2"); }

u32 getArtsDrDmgRt2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt2], id, 1).valueU8;
}

void initArtsDrDmgRt3(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt3] = Bdat::getMember(wrapper.data, "DmgRt3"); }

u32 getArtsDrDmgRt3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt3], id, 1).valueU8;
}

void initArtsDrDmgRt4(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt4] = Bdat::getMember(wrapper.data, "DmgRt4"); }

u32 getArtsDrDmgRt4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt4], id, 1).valueU8;
}

void initArtsDrDmgRt5(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt5] = Bdat::getMember(wrapper.data, "DmgRt5"); }

u32 getArtsDrDmgRt5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt5], id, 1).valueU8;
}

void initArtsDrDmgRt6(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt6] = Bdat::getMember(wrapper.data, "DmgRt6"); }

u32 getArtsDrDmgRt6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt6], id, 1).valueU8;
}

void initArtsDrDmgRt7(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt7] = Bdat::getMember(wrapper.data, "DmgRt7"); }

u32 getArtsDrDmgRt7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt7], id, 1).valueU8;
}

void initArtsDrDmgRt8(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt8] = Bdat::getMember(wrapper.data, "DmgRt8"); }

u32 getArtsDrDmgRt8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt8], id, 1).valueU8;
}

void initArtsDrDmgRt9(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt9] = Bdat::getMember(wrapper.data, "DmgRt9"); }

u32 getArtsDrDmgRt9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt9], id, 1).valueU8;
}

void initArtsDrDmgRt10(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt10] = Bdat::getMember(wrapper.data, "DmgRt10"); }

u32 getArtsDrDmgRt10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt10], id, 1).valueU8;
}

void initArtsDrDmgRt11(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt11] = Bdat::getMember(wrapper.data, "DmgRt11"); }

u32 getArtsDrDmgRt11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt11], id, 1).valueU8;
}

void initArtsDrDmgRt12(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt12] = Bdat::getMember(wrapper.data, "DmgRt12"); }

u32 getArtsDrDmgRt12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt12], id, 1).valueU8;
}

void initArtsDrDmgRt13(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt13] = Bdat::getMember(wrapper.data, "DmgRt13"); }

u32 getArtsDrDmgRt13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt13], id, 1).valueU8;
}

void initArtsDrDmgRt14(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt14] = Bdat::getMember(wrapper.data, "DmgRt14"); }

u32 getArtsDrDmgRt14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt14], id, 1).valueU8;
}

void initArtsDrDmgRt15(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt15] = Bdat::getMember(wrapper.data, "DmgRt15"); }

u32 getArtsDrDmgRt15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt15], id, 1).valueU8;
}

void initArtsDrDmgRt16(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt16] = Bdat::getMember(wrapper.data, "DmgRt16"); }

u32 getArtsDrDmgRt16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt16], id, 1).valueU8;
}

void initArtsDrReAct1(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct1] = Bdat::getMember(wrapper.data, "ReAct1"); }

u32 getArtsDrReAct1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct1], id, 1).valueU8;
}

void initArtsDrReAct2(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct2] = Bdat::getMember(wrapper.data, "ReAct2"); }

u32 getArtsDrReAct2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct2], id, 1).valueU8;
}

void initArtsDrReAct3(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct3] = Bdat::getMember(wrapper.data, "ReAct3"); }

u32 getArtsDrReAct3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct3], id, 1).valueU8;
}

void initArtsDrReAct4(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct4] = Bdat::getMember(wrapper.data, "ReAct4"); }

u32 getArtsDrReAct4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct4], id, 1).valueU8;
}

void initArtsDrReAct5(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct5] = Bdat::getMember(wrapper.data, "ReAct5"); }

u32 getArtsDrReAct5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct5], id, 1).valueU8;
}

void initArtsDrReAct6(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct6] = Bdat::getMember(wrapper.data, "ReAct6"); }

u32 getArtsDrReAct6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct6], id, 1).valueU8;
}

void initArtsDrReAct7(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct7] = Bdat::getMember(wrapper.data, "ReAct7"); }

u32 getArtsDrReAct7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct7], id, 1).valueU8;
}

void initArtsDrReAct8(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct8] = Bdat::getMember(wrapper.data, "ReAct8"); }

u32 getArtsDrReAct8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct8], id, 1).valueU8;
}

void initArtsDrReAct9(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct9] = Bdat::getMember(wrapper.data, "ReAct9"); }

u32 getArtsDrReAct9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct9], id, 1).valueU8;
}

void initArtsDrReAct10(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct10] = Bdat::getMember(wrapper.data, "ReAct10"); }

u32 getArtsDrReAct10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct10], id, 1).valueU8;
}

void initArtsDrReAct11(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct11] = Bdat::getMember(wrapper.data, "ReAct11"); }

u32 getArtsDrReAct11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct11], id, 1).valueU8;
}

void initArtsDrReAct12(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct12] = Bdat::getMember(wrapper.data, "ReAct12"); }

u32 getArtsDrReAct12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct12], id, 1).valueU8;
}

void initArtsDrReAct13(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct13] = Bdat::getMember(wrapper.data, "ReAct13"); }

u32 getArtsDrReAct13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct13], id, 1).valueU8;
}

void initArtsDrReAct14(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct14] = Bdat::getMember(wrapper.data, "ReAct14"); }

u32 getArtsDrReAct14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct14], id, 1).valueU8;
}

void initArtsDrReAct15(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct15] = Bdat::getMember(wrapper.data, "ReAct15"); }

u32 getArtsDrReAct15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct15], id, 1).valueU8;
}

void initArtsDrReAct16(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct16] = Bdat::getMember(wrapper.data, "ReAct16"); }

u32 getArtsDrReAct16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct16], id, 1).valueU8;
}

void initArtsDrMoveCancelFrm(const CBdatWrapper &wrapper) { s_members[ArtsDrMoveCancelFrm] = Bdat::getMember(wrapper.data, "MoveCancelFrm"); }

u32 getArtsDrMoveCancelFrm(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrMoveCancelFrm] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrMoveCancelFrm], id, 1).valueU8;
}

void initArtsDrDmgMgn1(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn1] = Bdat::getMember(wrapper.data, "DmgMgn1"); }

u32 getArtsDrDmgMgn1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn1], id, 2).valueU16;
}

void initArtsDrDmgMgn2(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn2] = Bdat::getMember(wrapper.data, "DmgMgn2"); }

u32 getArtsDrDmgMgn2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn2], id, 2).valueU16;
}

void initArtsDrDmgMgn3(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn3] = Bdat::getMember(wrapper.data, "DmgMgn3"); }

u32 getArtsDrDmgMgn3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn3], id, 2).valueU16;
}

void initArtsDrDmgMgn4(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn4] = Bdat::getMember(wrapper.data, "DmgMgn4"); }

u32 getArtsDrDmgMgn4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn4], id, 2).valueU16;
}

void initArtsDrDmgMgn5(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn5] = Bdat::getMember(wrapper.data, "DmgMgn5"); }

u32 getArtsDrDmgMgn5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn5], id, 2).valueU16;
}

void initArtsDrDmgMgn6(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn6] = Bdat::getMember(wrapper.data, "DmgMgn6"); }

u32 getArtsDrDmgMgn6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn6], id, 2).valueU16;
}

void initArtsDrRecast1(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast1] = Bdat::getMember(wrapper.data, "Recast1"); }

u32 getArtsDrRecast1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast1], id, 2).valueU16;
}

void initArtsDrRecast2(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast2] = Bdat::getMember(wrapper.data, "Recast2"); }

u32 getArtsDrRecast2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast2], id, 2).valueU16;
}

void initArtsDrRecast3(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast3] = Bdat::getMember(wrapper.data, "Recast3"); }

u32 getArtsDrRecast3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast3], id, 2).valueU16;
}

void initArtsDrRecast4(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast4] = Bdat::getMember(wrapper.data, "Recast4"); }

u32 getArtsDrRecast4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast4], id, 2).valueU16;
}

void initArtsDrRecast5(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast5] = Bdat::getMember(wrapper.data, "Recast5"); }

u32 getArtsDrRecast5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast5], id, 2).valueU16;
}

void initArtsDrRecast6(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast6] = Bdat::getMember(wrapper.data, "Recast6"); }

u32 getArtsDrRecast6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast6], id, 2).valueU16;
}

void initArtsDrAtrNum(const CBdatWrapper &wrapper) { s_members[ArtsDrAtrNum] = Bdat::getMember(wrapper.data, "AtrNum"); }

u32 getArtsDrAtrNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrAtrNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrAtrNum], id, 1).valueU8;
}

void initArtsDrEnhance1(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance1] = Bdat::getMember(wrapper.data, "Enhance1"); }

u32 getArtsDrEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance1], id, 2).valueU16;
}

void initArtsDrEnhance2(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance2] = Bdat::getMember(wrapper.data, "Enhance2"); }

u32 getArtsDrEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance2], id, 2).valueU16;
}

void initArtsDrEnhance3(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance3] = Bdat::getMember(wrapper.data, "Enhance3"); }

u32 getArtsDrEnhance3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance3], id, 2).valueU16;
}

void initArtsDrEnhance4(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance4] = Bdat::getMember(wrapper.data, "Enhance4"); }

u32 getArtsDrEnhance4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance4], id, 2).valueU16;
}

void initArtsDrEnhance5(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance5] = Bdat::getMember(wrapper.data, "Enhance5"); }

u32 getArtsDrEnhance5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance5], id, 2).valueU16;
}

void initArtsDrEnhance6(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance6] = Bdat::getMember(wrapper.data, "Enhance6"); }

u32 getArtsDrEnhance6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance6], id, 2).valueU16;
}

void initArtsDrReleaseLv1(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv1] = Bdat::getMember(wrapper.data, "ReleaseLv1"); }

u32 getArtsDrReleaseLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv1], id, 1).valueU8;
}

void initArtsDrReleaseLv2(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv2] = Bdat::getMember(wrapper.data, "ReleaseLv2"); }

u32 getArtsDrReleaseLv2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv2], id, 1).valueU8;
}

void initArtsDrReleaseLv3(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv3] = Bdat::getMember(wrapper.data, "ReleaseLv3"); }

u32 getArtsDrReleaseLv3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv3], id, 1).valueU8;
}

void initArtsDrReleaseLv4(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv4] = Bdat::getMember(wrapper.data, "ReleaseLv4"); }

u32 getArtsDrReleaseLv4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv4], id, 1).valueU8;
}

void initArtsDrReleaseLv5(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv5] = Bdat::getMember(wrapper.data, "ReleaseLv5"); }

u32 getArtsDrReleaseLv5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv5], id, 1).valueU8;
}

void initArtsDrNeedWP2(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP2] = Bdat::getMember(wrapper.data, "NeedWP2"); }

u32 getArtsDrNeedWP2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP2], id, 2).valueU16;
}

void initArtsDrNeedWP3(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP3] = Bdat::getMember(wrapper.data, "NeedWP3"); }

u32 getArtsDrNeedWP3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP3], id, 2).valueU16;
}

void initArtsDrNeedWP4(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP4] = Bdat::getMember(wrapper.data, "NeedWP4"); }

u32 getArtsDrNeedWP4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP4], id, 2).valueU16;
}

void initArtsDrNeedWP5(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP5] = Bdat::getMember(wrapper.data, "NeedWP5"); }

u32 getArtsDrNeedWP5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP5], id, 2).valueU16;
}

void initArtsDrUI(const CBdatWrapper &wrapper) { s_members[ArtsDrUI] = Bdat::getMember(wrapper.data, "UI"); }

u32 getArtsDrUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrUI] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrUI], id, 2).valueU16;
}

void initArtsDrPriority(const CBdatWrapper &wrapper) { s_members[ArtsDrPriority] = Bdat::getMember(wrapper.data, "Priority"); }

u32 getArtsDrPriority(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrPriority] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrPriority], id, 1).valueU8;
}

void initArtsBlName(const CBdatWrapper &wrapper) { s_members[ArtsBlName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getArtsBlName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlName], id, 2).valueU16;
}

void initArtsBlDebugName(const CBdatWrapper &wrapper) { s_members[ArtsBlDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getArtsBlDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlDebugName], id, 7).valueString;
}

void initArtsBlCaption(const CBdatWrapper &wrapper) { s_members[ArtsBlCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getArtsBlCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlCaption], id, 2).valueU16;
}

void initArtsBlWpnType(const CBdatWrapper &wrapper) { s_members[ArtsBlWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getArtsBlWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlWpnType], id, 1).valueU8;
}

void initArtsBlCmnBlType(const CBdatWrapper &wrapper) { s_members[ArtsBlCmnBlType] = Bdat::getMember(wrapper.data, "CmnBlType"); }

u32 getArtsBlCmnBlType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlCmnBlType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlCmnBlType], id, 1).valueU8;
}

void initArtsBlSpLv(const CBdatWrapper &wrapper) { s_members[ArtsBlSpLv] = Bdat::getMember(wrapper.data, "SpLv"); }

u32 getArtsBlSpLv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpLv] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpLv], id, 1).valueU8;
}

void initArtsBlActNo(const CBdatWrapper &wrapper) { s_members[ArtsBlActNo] = Bdat::getMember(wrapper.data, "ActNo"); }

u32 getArtsBlActNo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlActNo] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlActNo], id, 1).valueU8;
}

void initArtsBlArtsType(const CBdatWrapper &wrapper) { s_members[ArtsBlArtsType] = Bdat::getMember(wrapper.data, "ArtsType"); }

u32 getArtsBlArtsType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlArtsType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlArtsType], id, 1).valueU8;
}

void initArtsBlArtsBuff(const CBdatWrapper &wrapper) { s_members[ArtsBlArtsBuff] = Bdat::getMember(wrapper.data, "ArtsBuff"); }

u32 getArtsBlArtsBuff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlArtsBuff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlArtsBuff], id, 1).valueU8;
}

void initArtsBlFlagcommon(const CBdatWrapper &wrapper) {
  s_members[ArtsBlFlagcommon] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsBlFlagcommonFlag] = Bdat::getMember(wrapper.data, "common");
}

bool isArtsBlFlagcommon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlFlagcommon] == nullptr || s_members[ArtsBlFlagcommonFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlFlagcommon], id, s_members[ArtsBlFlagcommonFlag]) != 0;
}

void initArtsBlFlagPierce(const CBdatWrapper &wrapper) {
  s_members[ArtsBlFlagPierce] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsBlFlagPierceFlag] = Bdat::getMember(wrapper.data, "Pierce");
}

bool isArtsBlFlagPierce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlFlagPierce] == nullptr || s_members[ArtsBlFlagPierceFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlFlagPierce], id, s_members[ArtsBlFlagPierceFlag]) != 0;
}

void initArtsBlTarget(const CBdatWrapper &wrapper) { s_members[ArtsBlTarget] = Bdat::getMember(wrapper.data, "Target"); }

u32 getArtsBlTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlTarget] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlTarget], id, 1).valueU8;
}

void initArtsBlDistance(const CBdatWrapper &wrapper) { s_members[ArtsBlDistance] = Bdat::getMember(wrapper.data, "Distance"); }

u32 getArtsBlDistance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDistance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDistance], id, 2).valueU16;
}

void initArtsBlRangeType(const CBdatWrapper &wrapper) { s_members[ArtsBlRangeType] = Bdat::getMember(wrapper.data, "RangeType"); }

u32 getArtsBlRangeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlRangeType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlRangeType], id, 1).valueU8;
}

void initArtsBlRadius(const CBdatWrapper &wrapper) { s_members[ArtsBlRadius] = Bdat::getMember(wrapper.data, "Radius"); }

u32 getArtsBlRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlRadius] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlRadius], id, 2).valueU16;
}

void initArtsBlLength(const CBdatWrapper &wrapper) { s_members[ArtsBlLength] = Bdat::getMember(wrapper.data, "Length"); }

u32 getArtsBlLength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlLength] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlLength], id, 2).valueU16;
}

void initArtsBlAtr(const CBdatWrapper &wrapper) { s_members[ArtsBlAtr] = Bdat::getMember(wrapper.data, "Atr"); }

u32 getArtsBlAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlAtr], id, 1).valueU8;
}

void initArtsBlHate(const CBdatWrapper &wrapper) { s_members[ArtsBlHate] = Bdat::getMember(wrapper.data, "Hate"); }

s32 getArtsBlHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHate] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHate], id, 4).valueS8;
}

void initArtsBlHitRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlHitRevise] = Bdat::getMember(wrapper.data, "HitRevise"); }

s32 getArtsBlHitRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitRevise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitRevise], id, 4).valueS8;
}

void initArtsBlCriRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlCriRevise] = Bdat::getMember(wrapper.data, "CriRevise"); }

s32 getArtsBlCriRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlCriRevise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlCriRevise], id, 4).valueS8;
}

void initArtsBlBulletID(const CBdatWrapper &wrapper) { s_members[ArtsBlBulletID] = Bdat::getMember(wrapper.data, "BulletID"); }

u32 getArtsBlBulletID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBulletID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBulletID], id, 2).valueU16;
}

void initArtsBlBulletNum(const CBdatWrapper &wrapper) { s_members[ArtsBlBulletNum] = Bdat::getMember(wrapper.data, "BulletNum"); }

u32 getArtsBlBulletNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBulletNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBulletNum], id, 1).valueU8;
}

void initArtsBlHitFrm1(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm1] = Bdat::getMember(wrapper.data, "HitFrm1"); }

u32 getArtsBlHitFrm1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm1], id, 1).valueU8;
}

void initArtsBlHitFrm2(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm2] = Bdat::getMember(wrapper.data, "HitFrm2"); }

u32 getArtsBlHitFrm2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm2], id, 1).valueU8;
}

void initArtsBlHitFrm3(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm3] = Bdat::getMember(wrapper.data, "HitFrm3"); }

u32 getArtsBlHitFrm3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm3], id, 1).valueU8;
}

void initArtsBlHitFrm4(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm4] = Bdat::getMember(wrapper.data, "HitFrm4"); }

u32 getArtsBlHitFrm4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm4], id, 1).valueU8;
}

void initArtsBlHitFrm5(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm5] = Bdat::getMember(wrapper.data, "HitFrm5"); }

u32 getArtsBlHitFrm5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm5], id, 1).valueU8;
}

void initArtsBlHitFrm6(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm6] = Bdat::getMember(wrapper.data, "HitFrm6"); }

u32 getArtsBlHitFrm6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm6], id, 1).valueU8;
}

void initArtsBlHitFrm7(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm7] = Bdat::getMember(wrapper.data, "HitFrm7"); }

u32 getArtsBlHitFrm7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm7], id, 1).valueU8;
}

void initArtsBlHitFrm8(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm8] = Bdat::getMember(wrapper.data, "HitFrm8"); }

u32 getArtsBlHitFrm8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm8], id, 1).valueU8;
}

void initArtsBlHitFrm9(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm9] = Bdat::getMember(wrapper.data, "HitFrm9"); }

u32 getArtsBlHitFrm9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm9], id, 1).valueU8;
}

void initArtsBlHitFrm10(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm10] = Bdat::getMember(wrapper.data, "HitFrm10"); }

u32 getArtsBlHitFrm10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm10], id, 1).valueU8;
}

void initArtsBlHitFrm11(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm11] = Bdat::getMember(wrapper.data, "HitFrm11"); }

u32 getArtsBlHitFrm11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm11], id, 1).valueU8;
}

void initArtsBlHitFrm12(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm12] = Bdat::getMember(wrapper.data, "HitFrm12"); }

u32 getArtsBlHitFrm12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm12], id, 1).valueU8;
}

void initArtsBlHitFrm13(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm13] = Bdat::getMember(wrapper.data, "HitFrm13"); }

u32 getArtsBlHitFrm13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm13], id, 1).valueU8;
}

void initArtsBlHitFrm14(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm14] = Bdat::getMember(wrapper.data, "HitFrm14"); }

u32 getArtsBlHitFrm14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm14], id, 1).valueU8;
}

void initArtsBlHitFrm15(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm15] = Bdat::getMember(wrapper.data, "HitFrm15"); }

u32 getArtsBlHitFrm15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm15], id, 1).valueU8;
}

void initArtsBlHitFrm16(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm16] = Bdat::getMember(wrapper.data, "HitFrm16"); }

u32 getArtsBlHitFrm16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm16], id, 1).valueU8;
}

void initArtsBlEfp1(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp1] = Bdat::getMember(wrapper.data, "Efp1"); }

u32 getArtsBlEfp1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp1], id, 1).valueU8;
}

void initArtsBlEfp2(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp2] = Bdat::getMember(wrapper.data, "Efp2"); }

u32 getArtsBlEfp2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp2], id, 1).valueU8;
}

void initArtsBlEfp3(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp3] = Bdat::getMember(wrapper.data, "Efp3"); }

u32 getArtsBlEfp3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp3], id, 1).valueU8;
}

void initArtsBlEfp4(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp4] = Bdat::getMember(wrapper.data, "Efp4"); }

u32 getArtsBlEfp4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp4] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp4], id, 1).valueU8;
}

void initArtsBlEfp5(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp5] = Bdat::getMember(wrapper.data, "Efp5"); }

u32 getArtsBlEfp5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp5] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp5], id, 1).valueU8;
}

void initArtsBlEfp6(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp6] = Bdat::getMember(wrapper.data, "Efp6"); }

u32 getArtsBlEfp6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp6] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp6], id, 1).valueU8;
}

void initArtsBlEfp7(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp7] = Bdat::getMember(wrapper.data, "Efp7"); }

u32 getArtsBlEfp7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp7] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp7], id, 1).valueU8;
}

void initArtsBlEfp8(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp8] = Bdat::getMember(wrapper.data, "Efp8"); }

u32 getArtsBlEfp8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp8] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp8], id, 1).valueU8;
}

void initArtsBlEfp9(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp9] = Bdat::getMember(wrapper.data, "Efp9"); }

u32 getArtsBlEfp9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp9] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp9], id, 1).valueU8;
}

void initArtsBlEfp10(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp10] = Bdat::getMember(wrapper.data, "Efp10"); }

u32 getArtsBlEfp10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp10] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp10], id, 1).valueU8;
}

void initArtsBlEfp11(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp11] = Bdat::getMember(wrapper.data, "Efp11"); }

u32 getArtsBlEfp11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp11] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp11], id, 1).valueU8;
}

void initArtsBlEfp12(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp12] = Bdat::getMember(wrapper.data, "Efp12"); }

u32 getArtsBlEfp12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp12] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp12], id, 1).valueU8;
}

void initArtsBlEfp13(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp13] = Bdat::getMember(wrapper.data, "Efp13"); }

u32 getArtsBlEfp13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp13] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp13], id, 1).valueU8;
}

void initArtsBlEfp14(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp14] = Bdat::getMember(wrapper.data, "Efp14"); }

u32 getArtsBlEfp14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp14] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp14], id, 1).valueU8;
}

void initArtsBlEfp15(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp15] = Bdat::getMember(wrapper.data, "Efp15"); }

u32 getArtsBlEfp15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp15] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp15], id, 1).valueU8;
}

void initArtsBlEfp16(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp16] = Bdat::getMember(wrapper.data, "Efp16"); }

u32 getArtsBlEfp16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp16] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp16], id, 1).valueU8;
}

void initArtsBlHitDirID1(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID1] = Bdat::getMember(wrapper.data, "HitDirID1"); }

u32 getArtsBlHitDirID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID1], id, 1).valueU8;
}

void initArtsBlHitDirID2(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID2] = Bdat::getMember(wrapper.data, "HitDirID2"); }

u32 getArtsBlHitDirID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID2], id, 1).valueU8;
}

void initArtsBlHitDirID3(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID3] = Bdat::getMember(wrapper.data, "HitDirID3"); }

u32 getArtsBlHitDirID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID3], id, 1).valueU8;
}

void initArtsBlHitDirID4(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID4] = Bdat::getMember(wrapper.data, "HitDirID4"); }

u32 getArtsBlHitDirID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID4], id, 1).valueU8;
}

void initArtsBlHitDirID5(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID5] = Bdat::getMember(wrapper.data, "HitDirID5"); }

u32 getArtsBlHitDirID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID5], id, 1).valueU8;
}

void initArtsBlHitDirID6(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID6] = Bdat::getMember(wrapper.data, "HitDirID6"); }

u32 getArtsBlHitDirID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID6], id, 1).valueU8;
}

void initArtsBlHitDirID7(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID7] = Bdat::getMember(wrapper.data, "HitDirID7"); }

u32 getArtsBlHitDirID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID7], id, 1).valueU8;
}

void initArtsBlHitDirID8(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID8] = Bdat::getMember(wrapper.data, "HitDirID8"); }

u32 getArtsBlHitDirID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID8], id, 1).valueU8;
}

void initArtsBlHitDirID9(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID9] = Bdat::getMember(wrapper.data, "HitDirID9"); }

u32 getArtsBlHitDirID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID9], id, 1).valueU8;
}

void initArtsBlHitDirID10(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID10] = Bdat::getMember(wrapper.data, "HitDirID10"); }

u32 getArtsBlHitDirID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID10], id, 1).valueU8;
}

void initArtsBlHitDirID11(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID11] = Bdat::getMember(wrapper.data, "HitDirID11"); }

u32 getArtsBlHitDirID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID11], id, 1).valueU8;
}

void initArtsBlHitDirID12(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID12] = Bdat::getMember(wrapper.data, "HitDirID12"); }

u32 getArtsBlHitDirID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID12], id, 1).valueU8;
}

void initArtsBlHitDirID13(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID13] = Bdat::getMember(wrapper.data, "HitDirID13"); }

u32 getArtsBlHitDirID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID13], id, 1).valueU8;
}

void initArtsBlHitDirID14(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID14] = Bdat::getMember(wrapper.data, "HitDirID14"); }

u32 getArtsBlHitDirID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID14], id, 1).valueU8;
}

void initArtsBlHitDirID15(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID15] = Bdat::getMember(wrapper.data, "HitDirID15"); }

u32 getArtsBlHitDirID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID15], id, 1).valueU8;
}

void initArtsBlHitDirID16(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID16] = Bdat::getMember(wrapper.data, "HitDirID16"); }

u32 getArtsBlHitDirID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID16], id, 1).valueU8;
}

void initArtsBlDmgRt1(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt1] = Bdat::getMember(wrapper.data, "DmgRt1"); }

u32 getArtsBlDmgRt1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt1], id, 1).valueU8;
}

void initArtsBlDmgRt2(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt2] = Bdat::getMember(wrapper.data, "DmgRt2"); }

u32 getArtsBlDmgRt2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt2], id, 1).valueU8;
}

void initArtsBlDmgRt3(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt3] = Bdat::getMember(wrapper.data, "DmgRt3"); }

u32 getArtsBlDmgRt3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt3], id, 1).valueU8;
}

void initArtsBlDmgRt4(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt4] = Bdat::getMember(wrapper.data, "DmgRt4"); }

u32 getArtsBlDmgRt4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt4], id, 1).valueU8;
}

void initArtsBlDmgRt5(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt5] = Bdat::getMember(wrapper.data, "DmgRt5"); }

u32 getArtsBlDmgRt5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt5], id, 1).valueU8;
}

void initArtsBlDmgRt6(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt6] = Bdat::getMember(wrapper.data, "DmgRt6"); }

u32 getArtsBlDmgRt6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt6], id, 1).valueU8;
}

void initArtsBlDmgRt7(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt7] = Bdat::getMember(wrapper.data, "DmgRt7"); }

u32 getArtsBlDmgRt7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt7], id, 1).valueU8;
}

void initArtsBlDmgRt8(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt8] = Bdat::getMember(wrapper.data, "DmgRt8"); }

u32 getArtsBlDmgRt8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt8], id, 1).valueU8;
}

void initArtsBlDmgRt9(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt9] = Bdat::getMember(wrapper.data, "DmgRt9"); }

u32 getArtsBlDmgRt9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt9], id, 1).valueU8;
}

void initArtsBlDmgRt10(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt10] = Bdat::getMember(wrapper.data, "DmgRt10"); }

u32 getArtsBlDmgRt10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt10], id, 1).valueU8;
}

void initArtsBlDmgRt11(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt11] = Bdat::getMember(wrapper.data, "DmgRt11"); }

u32 getArtsBlDmgRt11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt11], id, 1).valueU8;
}

void initArtsBlDmgRt12(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt12] = Bdat::getMember(wrapper.data, "DmgRt12"); }

u32 getArtsBlDmgRt12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt12], id, 1).valueU8;
}

void initArtsBlDmgRt13(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt13] = Bdat::getMember(wrapper.data, "DmgRt13"); }

u32 getArtsBlDmgRt13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt13], id, 1).valueU8;
}

void initArtsBlDmgRt14(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt14] = Bdat::getMember(wrapper.data, "DmgRt14"); }

u32 getArtsBlDmgRt14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt14], id, 1).valueU8;
}

void initArtsBlDmgRt15(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt15] = Bdat::getMember(wrapper.data, "DmgRt15"); }

u32 getArtsBlDmgRt15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt15], id, 1).valueU8;
}

void initArtsBlDmgRt16(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt16] = Bdat::getMember(wrapper.data, "DmgRt16"); }

u32 getArtsBlDmgRt16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt16], id, 1).valueU8;
}

void initArtsBlReAct1(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct1] = Bdat::getMember(wrapper.data, "ReAct1"); }

u32 getArtsBlReAct1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct1], id, 1).valueU8;
}

void initArtsBlReAct2(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct2] = Bdat::getMember(wrapper.data, "ReAct2"); }

u32 getArtsBlReAct2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct2], id, 1).valueU8;
}

void initArtsBlReAct3(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct3] = Bdat::getMember(wrapper.data, "ReAct3"); }

u32 getArtsBlReAct3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct3], id, 1).valueU8;
}

void initArtsBlReAct4(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct4] = Bdat::getMember(wrapper.data, "ReAct4"); }

u32 getArtsBlReAct4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct4], id, 1).valueU8;
}

void initArtsBlReAct5(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct5] = Bdat::getMember(wrapper.data, "ReAct5"); }

u32 getArtsBlReAct5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct5], id, 1).valueU8;
}

void initArtsBlReAct6(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct6] = Bdat::getMember(wrapper.data, "ReAct6"); }

u32 getArtsBlReAct6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct6], id, 1).valueU8;
}

void initArtsBlReAct7(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct7] = Bdat::getMember(wrapper.data, "ReAct7"); }

u32 getArtsBlReAct7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct7], id, 1).valueU8;
}

void initArtsBlReAct8(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct8] = Bdat::getMember(wrapper.data, "ReAct8"); }

u32 getArtsBlReAct8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct8], id, 1).valueU8;
}

void initArtsBlReAct9(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct9] = Bdat::getMember(wrapper.data, "ReAct9"); }

u32 getArtsBlReAct9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct9], id, 1).valueU8;
}

void initArtsBlReAct10(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct10] = Bdat::getMember(wrapper.data, "ReAct10"); }

u32 getArtsBlReAct10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct10], id, 1).valueU8;
}

void initArtsBlReAct11(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct11] = Bdat::getMember(wrapper.data, "ReAct11"); }

u32 getArtsBlReAct11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct11], id, 1).valueU8;
}

void initArtsBlReAct12(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct12] = Bdat::getMember(wrapper.data, "ReAct12"); }

u32 getArtsBlReAct12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct12], id, 1).valueU8;
}

void initArtsBlReAct13(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct13] = Bdat::getMember(wrapper.data, "ReAct13"); }

u32 getArtsBlReAct13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct13], id, 1).valueU8;
}

void initArtsBlReAct14(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct14] = Bdat::getMember(wrapper.data, "ReAct14"); }

u32 getArtsBlReAct14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct14], id, 1).valueU8;
}

void initArtsBlReAct15(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct15] = Bdat::getMember(wrapper.data, "ReAct15"); }

u32 getArtsBlReAct15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct15], id, 1).valueU8;
}

void initArtsBlReAct16(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct16] = Bdat::getMember(wrapper.data, "ReAct16"); }

u32 getArtsBlReAct16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct16], id, 1).valueU8;
}

void initArtsBlDmgMgn1(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn1] = Bdat::getMember(wrapper.data, "DmgMgn1"); }

u32 getArtsBlDmgMgn1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn1], id, 2).valueU16;
}

void initArtsBlDmgMgn2(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn2] = Bdat::getMember(wrapper.data, "DmgMgn2"); }

u32 getArtsBlDmgMgn2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn2], id, 2).valueU16;
}

void initArtsBlDmgMgn3(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn3] = Bdat::getMember(wrapper.data, "DmgMgn3"); }

u32 getArtsBlDmgMgn3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn3], id, 2).valueU16;
}

void initArtsBlDmgMgn4(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn4] = Bdat::getMember(wrapper.data, "DmgMgn4"); }

u32 getArtsBlDmgMgn4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn4], id, 2).valueU16;
}

void initArtsBlDmgMgn5(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn5] = Bdat::getMember(wrapper.data, "DmgMgn5"); }

u32 getArtsBlDmgMgn5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn5], id, 2).valueU16;
}

void initArtsBlDmgMgn6(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn6] = Bdat::getMember(wrapper.data, "DmgMgn6"); }

u32 getArtsBlDmgMgn6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn6], id, 2).valueU16;
}

void initArtsBlAtrNum(const CBdatWrapper &wrapper) { s_members[ArtsBlAtrNum] = Bdat::getMember(wrapper.data, "AtrNum"); }

u32 getArtsBlAtrNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlAtrNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlAtrNum], id, 1).valueU8;
}

void initArtsBlEnhance1(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance1] = Bdat::getMember(wrapper.data, "Enhance1"); }

u32 getArtsBlEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance1], id, 2).valueU16;
}

void initArtsBlEnhance2(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance2] = Bdat::getMember(wrapper.data, "Enhance2"); }

u32 getArtsBlEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance2], id, 2).valueU16;
}

void initArtsBlEnhance3(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance3] = Bdat::getMember(wrapper.data, "Enhance3"); }

u32 getArtsBlEnhance3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance3], id, 2).valueU16;
}

void initArtsBlEnhance4(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance4] = Bdat::getMember(wrapper.data, "Enhance4"); }

u32 getArtsBlEnhance4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance4], id, 2).valueU16;
}

void initArtsBlEnhance5(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance5] = Bdat::getMember(wrapper.data, "Enhance5"); }

u32 getArtsBlEnhance5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance5], id, 2).valueU16;
}

void initArtsBlEnhance6(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance6] = Bdat::getMember(wrapper.data, "Enhance6"); }

u32 getArtsBlEnhance6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance6], id, 2).valueU16;
}

void initArtsBlBtnType(const CBdatWrapper &wrapper) { s_members[ArtsBlBtnType] = Bdat::getMember(wrapper.data, "BtnType"); }

u32 getArtsBlBtnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBtnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBtnType], id, 1).valueU8;
}

void initArtsBlBtnChal1(const CBdatWrapper &wrapper) { s_members[ArtsBlBtnChal1] = Bdat::getMember(wrapper.data, "BtnChal1"); }

u32 getArtsBlBtnChal1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBtnChal1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBtnChal1], id, 2).valueU16;
}

void initArtsBlUI(const CBdatWrapper &wrapper) { s_members[ArtsBlUI] = Bdat::getMember(wrapper.data, "UI"); }

u32 getArtsBlUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlUI] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlUI], id, 2).valueU16;
}

void initArtsBlSpName(const CBdatWrapper &wrapper) { s_members[ArtsBlSpName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getArtsBlSpName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpName], id, 2).valueU16;
}

void initArtsBlSpDebugName(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getArtsBlSpDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDebugName], id, 7).valueString;
}

void initArtsBlSpCaption(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getArtsBlSpCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCaption], id, 2).valueU16;
}

void initArtsBlSpWpnType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getArtsBlSpWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpWpnType], id, 1).valueU8;
}

void initArtsBlSpCmnBlType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCmnBlType] = Bdat::getMember(wrapper.data, "CmnBlType"); }

u32 getArtsBlSpCmnBlType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCmnBlType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCmnBlType], id, 1).valueU8;
}

void initArtsBlSpActNoDr(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActNoDr] = Bdat::getMember(wrapper.data, "ActNoDr"); }

u32 getArtsBlSpActNoDr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActNoDr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActNoDr], id, 1).valueU8;
}

void initArtsBlSpActNoBl(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActNoBl] = Bdat::getMember(wrapper.data, "ActNoBl"); }

u32 getArtsBlSpActNoBl(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActNoBl] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActNoBl], id, 1).valueU8;
}

void initArtsBlSpActNoBl2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActNoBl2] = Bdat::getMember(wrapper.data, "ActNoBl2"); }

u32 getArtsBlSpActNoBl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActNoBl2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActNoBl2], id, 1).valueU8;
}

void initArtsBlSpBuddyDr(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBuddyDr] = Bdat::getMember(wrapper.data, "BuddyDr"); }

u32 getArtsBlSpBuddyDr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBuddyDr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBuddyDr], id, 1).valueU8;
}

void initArtsBlSpAddBl(const CBdatWrapper &wrapper) { s_members[ArtsBlSpAddBl] = Bdat::getMember(wrapper.data, "AddBl"); }

u32 getArtsBlSpAddBl(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpAddBl] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpAddBl], id, 1).valueU8;
}

void initArtsBlSpActType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActType] = Bdat::getMember(wrapper.data, "ActType"); }

u32 getArtsBlSpActType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActType], id, 1).valueU8;
}

void initArtsBlSpPC01(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC01] = Bdat::getMember(wrapper.data, "PC01"); }

u32 getArtsBlSpPC01(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC01] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC01], id, 1).valueU8;
}

void initArtsBlSpPC02(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC02] = Bdat::getMember(wrapper.data, "PC02"); }

u32 getArtsBlSpPC02(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC02] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC02], id, 1).valueU8;
}

void initArtsBlSpPC03(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC03] = Bdat::getMember(wrapper.data, "PC03"); }

u32 getArtsBlSpPC03(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC03] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC03], id, 1).valueU8;
}

void initArtsBlSpPC06(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC06] = Bdat::getMember(wrapper.data, "PC06"); }

u32 getArtsBlSpPC06(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC06] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC06], id, 1).valueU8;
}

void initArtsBlSpArtsType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpArtsType] = Bdat::getMember(wrapper.data, "ArtsType"); }

u32 getArtsBlSpArtsType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpArtsType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpArtsType], id, 1).valueU8;
}

void initArtsBlSpArtsBuff(const CBdatWrapper &wrapper) { s_members[ArtsBlSpArtsBuff] = Bdat::getMember(wrapper.data, "ArtsBuff"); }

u32 getArtsBlSpArtsBuff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpArtsBuff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpArtsBuff], id, 1).valueU8;
}

void initArtsBlSpFlagPierce(const CBdatWrapper &wrapper) {
  s_members[ArtsBlSpFlagPierce] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsBlSpFlagPierceFlag] = Bdat::getMember(wrapper.data, "Pierce");
}

bool isArtsBlSpFlagPierce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpFlagPierce] == nullptr || s_members[ArtsBlSpFlagPierceFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlSpFlagPierce], id, s_members[ArtsBlSpFlagPierceFlag]) != 0;
}

void initArtsBlSpFlagNoMove(const CBdatWrapper &wrapper) {
  s_members[ArtsBlSpFlagNoMove] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ArtsBlSpFlagNoMoveFlag] = Bdat::getMember(wrapper.data, "NoMove");
}

bool isArtsBlSpFlagNoMove(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpFlagNoMove] == nullptr || s_members[ArtsBlSpFlagNoMoveFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlSpFlagNoMove], id, s_members[ArtsBlSpFlagNoMoveFlag]) != 0;
}

void initArtsBlSpTarget(const CBdatWrapper &wrapper) { s_members[ArtsBlSpTarget] = Bdat::getMember(wrapper.data, "Target"); }

u32 getArtsBlSpTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpTarget] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpTarget], id, 1).valueU8;
}

void initArtsBlSpDistance(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDistance] = Bdat::getMember(wrapper.data, "Distance"); }

u32 getArtsBlSpDistance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDistance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDistance], id, 2).valueU16;
}

void initArtsBlSpRangeType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpRangeType] = Bdat::getMember(wrapper.data, "RangeType"); }

u32 getArtsBlSpRangeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpRangeType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpRangeType], id, 1).valueU8;
}

void initArtsBlSpRadius(const CBdatWrapper &wrapper) { s_members[ArtsBlSpRadius] = Bdat::getMember(wrapper.data, "Radius"); }

u32 getArtsBlSpRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpRadius] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpRadius], id, 2).valueU16;
}

void initArtsBlSpLength(const CBdatWrapper &wrapper) { s_members[ArtsBlSpLength] = Bdat::getMember(wrapper.data, "Length"); }

u32 getArtsBlSpLength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpLength] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpLength], id, 2).valueU16;
}

void initArtsBlSpAtr(const CBdatWrapper &wrapper) { s_members[ArtsBlSpAtr] = Bdat::getMember(wrapper.data, "Atr"); }

u32 getArtsBlSpAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpAtr], id, 1).valueU8;
}

void initArtsBlSpHate(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHate] = Bdat::getMember(wrapper.data, "Hate"); }

s32 getArtsBlSpHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHate], id, 4).valueS8;
}

void initArtsBlSpHitRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitRevise] = Bdat::getMember(wrapper.data, "HitRevise"); }

s32 getArtsBlSpHitRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitRevise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitRevise], id, 4).valueS8;
}

void initArtsBlSpCriRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCriRevise] = Bdat::getMember(wrapper.data, "CriRevise"); }

s32 getArtsBlSpCriRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCriRevise] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCriRevise], id, 4).valueS8;
}

void initArtsBlSpBulletID(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBulletID] = Bdat::getMember(wrapper.data, "BulletID"); }

u32 getArtsBlSpBulletID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBulletID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBulletID], id, 2).valueU16;
}

void initArtsBlSpBulletEffID(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBulletEffID] = Bdat::getMember(wrapper.data, "BulletEffID"); }

u32 getArtsBlSpBulletEffID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBulletEffID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBulletEffID], id, 2).valueU16;
}

void initArtsBlSpBulletNum(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBulletNum] = Bdat::getMember(wrapper.data, "BulletNum"); }

u32 getArtsBlSpBulletNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBulletNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBulletNum], id, 1).valueU8;
}

void initArtsBlSpHitFrm1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm1] = Bdat::getMember(wrapper.data, "HitFrm1"); }

u32 getArtsBlSpHitFrm1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm1], id, 1).valueU8;
}

void initArtsBlSpHitFrm2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm2] = Bdat::getMember(wrapper.data, "HitFrm2"); }

u32 getArtsBlSpHitFrm2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm2], id, 1).valueU8;
}

void initArtsBlSpHitFrm3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm3] = Bdat::getMember(wrapper.data, "HitFrm3"); }

u32 getArtsBlSpHitFrm3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm3], id, 1).valueU8;
}

void initArtsBlSpHitFrm4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm4] = Bdat::getMember(wrapper.data, "HitFrm4"); }

u32 getArtsBlSpHitFrm4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm4], id, 1).valueU8;
}

void initArtsBlSpHitFrm5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm5] = Bdat::getMember(wrapper.data, "HitFrm5"); }

u32 getArtsBlSpHitFrm5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm5], id, 1).valueU8;
}

void initArtsBlSpHitFrm6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm6] = Bdat::getMember(wrapper.data, "HitFrm6"); }

u32 getArtsBlSpHitFrm6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm6], id, 1).valueU8;
}

void initArtsBlSpHitFrm7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm7] = Bdat::getMember(wrapper.data, "HitFrm7"); }

u32 getArtsBlSpHitFrm7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm7], id, 1).valueU8;
}

void initArtsBlSpHitFrm8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm8] = Bdat::getMember(wrapper.data, "HitFrm8"); }

u32 getArtsBlSpHitFrm8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm8], id, 1).valueU8;
}

void initArtsBlSpHitFrm9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm9] = Bdat::getMember(wrapper.data, "HitFrm9"); }

u32 getArtsBlSpHitFrm9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm9], id, 1).valueU8;
}

void initArtsBlSpHitFrm10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm10] = Bdat::getMember(wrapper.data, "HitFrm10"); }

u32 getArtsBlSpHitFrm10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm10], id, 1).valueU8;
}

void initArtsBlSpHitFrm11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm11] = Bdat::getMember(wrapper.data, "HitFrm11"); }

u32 getArtsBlSpHitFrm11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm11], id, 1).valueU8;
}

void initArtsBlSpHitFrm12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm12] = Bdat::getMember(wrapper.data, "HitFrm12"); }

u32 getArtsBlSpHitFrm12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm12], id, 1).valueU8;
}

void initArtsBlSpHitFrm13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm13] = Bdat::getMember(wrapper.data, "HitFrm13"); }

u32 getArtsBlSpHitFrm13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm13], id, 1).valueU8;
}

void initArtsBlSpHitFrm14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm14] = Bdat::getMember(wrapper.data, "HitFrm14"); }

u32 getArtsBlSpHitFrm14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm14], id, 1).valueU8;
}

void initArtsBlSpHitFrm15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm15] = Bdat::getMember(wrapper.data, "HitFrm15"); }

u32 getArtsBlSpHitFrm15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm15], id, 1).valueU8;
}

void initArtsBlSpHitFrm16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm16] = Bdat::getMember(wrapper.data, "HitFrm16"); }

u32 getArtsBlSpHitFrm16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm16], id, 1).valueU8;
}

void initArtsBlSpEfp1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp1] = Bdat::getMember(wrapper.data, "Efp1"); }

u32 getArtsBlSpEfp1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp1], id, 1).valueU8;
}

void initArtsBlSpEfp2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp2] = Bdat::getMember(wrapper.data, "Efp2"); }

u32 getArtsBlSpEfp2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp2], id, 1).valueU8;
}

void initArtsBlSpEfp3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp3] = Bdat::getMember(wrapper.data, "Efp3"); }

u32 getArtsBlSpEfp3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp3], id, 1).valueU8;
}

void initArtsBlSpEfp4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp4] = Bdat::getMember(wrapper.data, "Efp4"); }

u32 getArtsBlSpEfp4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp4], id, 1).valueU8;
}

void initArtsBlSpEfp5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp5] = Bdat::getMember(wrapper.data, "Efp5"); }

u32 getArtsBlSpEfp5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp5], id, 1).valueU8;
}

void initArtsBlSpEfp6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp6] = Bdat::getMember(wrapper.data, "Efp6"); }

u32 getArtsBlSpEfp6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp6], id, 1).valueU8;
}

void initArtsBlSpEfp7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp7] = Bdat::getMember(wrapper.data, "Efp7"); }

u32 getArtsBlSpEfp7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp7], id, 1).valueU8;
}

void initArtsBlSpEfp8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp8] = Bdat::getMember(wrapper.data, "Efp8"); }

u32 getArtsBlSpEfp8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp8], id, 1).valueU8;
}

void initArtsBlSpEfp9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp9] = Bdat::getMember(wrapper.data, "Efp9"); }

u32 getArtsBlSpEfp9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp9], id, 1).valueU8;
}

void initArtsBlSpEfp10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp10] = Bdat::getMember(wrapper.data, "Efp10"); }

u32 getArtsBlSpEfp10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp10], id, 1).valueU8;
}

void initArtsBlSpEfp11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp11] = Bdat::getMember(wrapper.data, "Efp11"); }

u32 getArtsBlSpEfp11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp11], id, 1).valueU8;
}

void initArtsBlSpEfp12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp12] = Bdat::getMember(wrapper.data, "Efp12"); }

u32 getArtsBlSpEfp12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp12], id, 1).valueU8;
}

void initArtsBlSpEfp13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp13] = Bdat::getMember(wrapper.data, "Efp13"); }

u32 getArtsBlSpEfp13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp13], id, 1).valueU8;
}

void initArtsBlSpEfp14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp14] = Bdat::getMember(wrapper.data, "Efp14"); }

u32 getArtsBlSpEfp14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp14], id, 1).valueU8;
}

void initArtsBlSpEfp15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp15] = Bdat::getMember(wrapper.data, "Efp15"); }

u32 getArtsBlSpEfp15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp15], id, 1).valueU8;
}

void initArtsBlSpEfp16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp16] = Bdat::getMember(wrapper.data, "Efp16"); }

u32 getArtsBlSpEfp16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp16], id, 1).valueU8;
}

void initArtsBlSpHitDirID1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID1] = Bdat::getMember(wrapper.data, "HitDirID1"); }

u32 getArtsBlSpHitDirID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID1], id, 1).valueU8;
}

void initArtsBlSpHitDirID2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID2] = Bdat::getMember(wrapper.data, "HitDirID2"); }

u32 getArtsBlSpHitDirID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID2], id, 1).valueU8;
}

void initArtsBlSpHitDirID3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID3] = Bdat::getMember(wrapper.data, "HitDirID3"); }

u32 getArtsBlSpHitDirID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID3], id, 1).valueU8;
}

void initArtsBlSpHitDirID4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID4] = Bdat::getMember(wrapper.data, "HitDirID4"); }

u32 getArtsBlSpHitDirID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID4], id, 1).valueU8;
}

void initArtsBlSpHitDirID5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID5] = Bdat::getMember(wrapper.data, "HitDirID5"); }

u32 getArtsBlSpHitDirID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID5], id, 1).valueU8;
}

void initArtsBlSpHitDirID6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID6] = Bdat::getMember(wrapper.data, "HitDirID6"); }

u32 getArtsBlSpHitDirID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID6], id, 1).valueU8;
}

void initArtsBlSpHitDirID7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID7] = Bdat::getMember(wrapper.data, "HitDirID7"); }

u32 getArtsBlSpHitDirID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID7], id, 1).valueU8;
}

void initArtsBlSpHitDirID8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID8] = Bdat::getMember(wrapper.data, "HitDirID8"); }

u32 getArtsBlSpHitDirID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID8], id, 1).valueU8;
}

void initArtsBlSpHitDirID9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID9] = Bdat::getMember(wrapper.data, "HitDirID9"); }

u32 getArtsBlSpHitDirID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID9], id, 1).valueU8;
}

void initArtsBlSpHitDirID10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID10] = Bdat::getMember(wrapper.data, "HitDirID10"); }

u32 getArtsBlSpHitDirID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID10], id, 1).valueU8;
}

void initArtsBlSpHitDirID11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID11] = Bdat::getMember(wrapper.data, "HitDirID11"); }

u32 getArtsBlSpHitDirID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID11], id, 1).valueU8;
}

void initArtsBlSpHitDirID12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID12] = Bdat::getMember(wrapper.data, "HitDirID12"); }

u32 getArtsBlSpHitDirID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID12], id, 1).valueU8;
}

void initArtsBlSpHitDirID13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID13] = Bdat::getMember(wrapper.data, "HitDirID13"); }

u32 getArtsBlSpHitDirID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID13], id, 1).valueU8;
}

void initArtsBlSpHitDirID14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID14] = Bdat::getMember(wrapper.data, "HitDirID14"); }

u32 getArtsBlSpHitDirID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID14], id, 1).valueU8;
}

void initArtsBlSpHitDirID15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID15] = Bdat::getMember(wrapper.data, "HitDirID15"); }

u32 getArtsBlSpHitDirID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID15], id, 1).valueU8;
}

void initArtsBlSpHitDirID16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID16] = Bdat::getMember(wrapper.data, "HitDirID16"); }

u32 getArtsBlSpHitDirID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID16], id, 1).valueU8;
}

void initArtsBlSpDmgRt1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt1] = Bdat::getMember(wrapper.data, "DmgRt1"); }

u32 getArtsBlSpDmgRt1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt1], id, 1).valueU8;
}

void initArtsBlSpDmgRt2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt2] = Bdat::getMember(wrapper.data, "DmgRt2"); }

u32 getArtsBlSpDmgRt2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt2], id, 1).valueU8;
}

void initArtsBlSpDmgRt3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt3] = Bdat::getMember(wrapper.data, "DmgRt3"); }

u32 getArtsBlSpDmgRt3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt3], id, 1).valueU8;
}

void initArtsBlSpDmgRt4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt4] = Bdat::getMember(wrapper.data, "DmgRt4"); }

u32 getArtsBlSpDmgRt4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt4], id, 1).valueU8;
}

void initArtsBlSpDmgRt5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt5] = Bdat::getMember(wrapper.data, "DmgRt5"); }

u32 getArtsBlSpDmgRt5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt5], id, 1).valueU8;
}

void initArtsBlSpDmgRt6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt6] = Bdat::getMember(wrapper.data, "DmgRt6"); }

u32 getArtsBlSpDmgRt6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt6], id, 1).valueU8;
}

void initArtsBlSpDmgRt7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt7] = Bdat::getMember(wrapper.data, "DmgRt7"); }

u32 getArtsBlSpDmgRt7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt7], id, 1).valueU8;
}

void initArtsBlSpDmgRt8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt8] = Bdat::getMember(wrapper.data, "DmgRt8"); }

u32 getArtsBlSpDmgRt8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt8], id, 1).valueU8;
}

void initArtsBlSpDmgRt9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt9] = Bdat::getMember(wrapper.data, "DmgRt9"); }

u32 getArtsBlSpDmgRt9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt9], id, 1).valueU8;
}

void initArtsBlSpDmgRt10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt10] = Bdat::getMember(wrapper.data, "DmgRt10"); }

u32 getArtsBlSpDmgRt10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt10], id, 1).valueU8;
}

void initArtsBlSpDmgRt11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt11] = Bdat::getMember(wrapper.data, "DmgRt11"); }

u32 getArtsBlSpDmgRt11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt11], id, 1).valueU8;
}

void initArtsBlSpDmgRt12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt12] = Bdat::getMember(wrapper.data, "DmgRt12"); }

u32 getArtsBlSpDmgRt12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt12], id, 1).valueU8;
}

void initArtsBlSpDmgRt13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt13] = Bdat::getMember(wrapper.data, "DmgRt13"); }

u32 getArtsBlSpDmgRt13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt13], id, 1).valueU8;
}

void initArtsBlSpDmgRt14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt14] = Bdat::getMember(wrapper.data, "DmgRt14"); }

u32 getArtsBlSpDmgRt14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt14], id, 1).valueU8;
}

void initArtsBlSpDmgRt15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt15] = Bdat::getMember(wrapper.data, "DmgRt15"); }

u32 getArtsBlSpDmgRt15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt15], id, 1).valueU8;
}

void initArtsBlSpDmgRt16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt16] = Bdat::getMember(wrapper.data, "DmgRt16"); }

u32 getArtsBlSpDmgRt16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt16], id, 1).valueU8;
}

void initArtsBlSpReAct1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct1] = Bdat::getMember(wrapper.data, "ReAct1"); }

u32 getArtsBlSpReAct1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct1], id, 1).valueU8;
}

void initArtsBlSpReAct2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct2] = Bdat::getMember(wrapper.data, "ReAct2"); }

u32 getArtsBlSpReAct2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct2], id, 1).valueU8;
}

void initArtsBlSpReAct3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct3] = Bdat::getMember(wrapper.data, "ReAct3"); }

u32 getArtsBlSpReAct3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct3], id, 1).valueU8;
}

void initArtsBlSpReAct4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct4] = Bdat::getMember(wrapper.data, "ReAct4"); }

u32 getArtsBlSpReAct4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct4], id, 1).valueU8;
}

void initArtsBlSpReAct5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct5] = Bdat::getMember(wrapper.data, "ReAct5"); }

u32 getArtsBlSpReAct5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct5], id, 1).valueU8;
}

void initArtsBlSpReAct6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct6] = Bdat::getMember(wrapper.data, "ReAct6"); }

u32 getArtsBlSpReAct6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct6], id, 1).valueU8;
}

void initArtsBlSpReAct7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct7] = Bdat::getMember(wrapper.data, "ReAct7"); }

u32 getArtsBlSpReAct7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct7], id, 1).valueU8;
}

void initArtsBlSpReAct8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct8] = Bdat::getMember(wrapper.data, "ReAct8"); }

u32 getArtsBlSpReAct8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct8], id, 1).valueU8;
}

void initArtsBlSpReAct9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct9] = Bdat::getMember(wrapper.data, "ReAct9"); }

u32 getArtsBlSpReAct9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct9] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct9], id, 1).valueU8;
}

void initArtsBlSpReAct10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct10] = Bdat::getMember(wrapper.data, "ReAct10"); }

u32 getArtsBlSpReAct10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct10] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct10], id, 1).valueU8;
}

void initArtsBlSpReAct11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct11] = Bdat::getMember(wrapper.data, "ReAct11"); }

u32 getArtsBlSpReAct11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct11] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct11], id, 1).valueU8;
}

void initArtsBlSpReAct12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct12] = Bdat::getMember(wrapper.data, "ReAct12"); }

u32 getArtsBlSpReAct12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct12] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct12], id, 1).valueU8;
}

void initArtsBlSpReAct13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct13] = Bdat::getMember(wrapper.data, "ReAct13"); }

u32 getArtsBlSpReAct13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct13] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct13], id, 1).valueU8;
}

void initArtsBlSpReAct14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct14] = Bdat::getMember(wrapper.data, "ReAct14"); }

u32 getArtsBlSpReAct14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct14] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct14], id, 1).valueU8;
}

void initArtsBlSpReAct15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct15] = Bdat::getMember(wrapper.data, "ReAct15"); }

u32 getArtsBlSpReAct15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct15] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct15], id, 1).valueU8;
}

void initArtsBlSpReAct16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct16] = Bdat::getMember(wrapper.data, "ReAct16"); }

u32 getArtsBlSpReAct16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct16] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct16], id, 1).valueU8;
}

void initArtsBlSpDmgMgn(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgMgn] = Bdat::getMember(wrapper.data, "DmgMgn"); }

u32 getArtsBlSpDmgMgn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgMgn] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgMgn], id, 2).valueU16;
}

void initArtsBlSpRecast(const CBdatWrapper &wrapper) { s_members[ArtsBlSpRecast] = Bdat::getMember(wrapper.data, "Recast"); }

u32 getArtsBlSpRecast(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpRecast] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpRecast], id, 2).valueU16;
}

void initArtsBlSpAtrNum(const CBdatWrapper &wrapper) { s_members[ArtsBlSpAtrNum] = Bdat::getMember(wrapper.data, "AtrNum"); }

u32 getArtsBlSpAtrNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpAtrNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpAtrNum], id, 1).valueU8;
}

void initArtsBlSpEnhance(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEnhance] = Bdat::getMember(wrapper.data, "Enhance"); }

u32 getArtsBlSpEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEnhance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEnhance], id, 2).valueU16;
}

void initArtsBlSpBtnType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBtnType] = Bdat::getMember(wrapper.data, "BtnType"); }

u32 getArtsBlSpBtnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBtnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBtnType], id, 1).valueU8;
}

void initArtsBlSpBtnChal1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBtnChal1] = Bdat::getMember(wrapper.data, "BtnChal1"); }

u32 getArtsBlSpBtnChal1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBtnChal1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBtnChal1], id, 2).valueU16;
}

void initArtsBlSpCamera1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCamera1] = Bdat::getMember(wrapper.data, "Camera1"); }

const char *getArtsBlSpCamera1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCamera1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCamera1], id, 7).valueString;
}

void initArtsBlSpCamera2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCamera2] = Bdat::getMember(wrapper.data, "Camera2"); }

const char *getArtsBlSpCamera2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCamera2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCamera2], id, 7).valueString;
}

void initArtsBlSpCamera3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCamera3] = Bdat::getMember(wrapper.data, "Camera3"); }

const char *getArtsBlSpCamera3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCamera3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCamera3], id, 7).valueString;
}

void initArtsBlSpCameraCT1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCameraCT1] = Bdat::getMember(wrapper.data, "CameraCT1"); }

u32 getArtsBlSpCameraCT1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCameraCT1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCameraCT1], id, 2).valueU16;
}

void initArtsBlSpCameraCT2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCameraCT2] = Bdat::getMember(wrapper.data, "CameraCT2"); }

u32 getArtsBlSpCameraCT2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCameraCT2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCameraCT2], id, 2).valueU16;
}

void initArtsBlSpCameraEndf(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCameraEndf] = Bdat::getMember(wrapper.data, "CameraEndf"); }

u32 getArtsBlSpCameraEndf(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCameraEndf] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCameraEndf], id, 1).valueU8;
}

void initArtsBlSpHitEff(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitEff] = Bdat::getMember(wrapper.data, "HitEff"); }

u32 getArtsBlSpHitEff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitEff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitEff], id, 2).valueU16;
}

void initGrowLevelExp(const CBdatWrapper &wrapper) { s_members[GrowLevelExp] = Bdat::getMember(wrapper.data, "LevelExp"); }

u32 getGrowLevelExp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowLevelExp] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowLevelExp], id, 3).valueU32;
}

void initGrowEnemyExp(const CBdatWrapper &wrapper) { s_members[GrowEnemyExp] = Bdat::getMember(wrapper.data, "EnemyExp"); }

u32 getGrowEnemyExp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemyExp] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemyExp], id, 2).valueU16;
}

void initGrowEnemyWP(const CBdatWrapper &wrapper) { s_members[GrowEnemyWP] = Bdat::getMember(wrapper.data, "EnemyWP"); }

u32 getGrowEnemyWP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemyWP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemyWP], id, 2).valueU16;
}

void initGrowEnemySP(const CBdatWrapper &wrapper) { s_members[GrowEnemySP] = Bdat::getMember(wrapper.data, "EnemySP"); }

u32 getGrowEnemySP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemySP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemySP], id, 2).valueU16;
}

void initGrowEnemyGold(const CBdatWrapper &wrapper) { s_members[GrowEnemyGold] = Bdat::getMember(wrapper.data, "EnemyGold"); }

u32 getGrowEnemyGold(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemyGold] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemyGold], id, 3).valueU32;
}

void initGrowGoldDivide(const CBdatWrapper &wrapper) { s_members[GrowGoldDivide] = Bdat::getMember(wrapper.data, "GoldDivide"); }

u32 getGrowGoldDivide(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowGoldDivide] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowGoldDivide], id, 1).valueU8;
}

void initLv_RevExpRevHigh(const CBdatWrapper &wrapper) { s_members[Lv_RevExpRevHigh] = Bdat::getMember(wrapper.data, "ExpRevHigh"); }

u32 getLv_RevExpRevHigh(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevExpRevHigh] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevExpRevHigh], id, 2).valueU16;
}

void initLv_RevExpRevLow(const CBdatWrapper &wrapper) { s_members[Lv_RevExpRevLow] = Bdat::getMember(wrapper.data, "ExpRevLow"); }

u32 getLv_RevExpRevLow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevExpRevLow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevExpRevLow], id, 2).valueU16;
}

void initLv_RevDamageRevHigh(const CBdatWrapper &wrapper) { s_members[Lv_RevDamageRevHigh] = Bdat::getMember(wrapper.data, "DamageRevHigh"); }

u32 getLv_RevDamageRevHigh(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevDamageRevHigh] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevDamageRevHigh], id, 2).valueU16;
}

void initLv_RevDamageRevLow(const CBdatWrapper &wrapper) { s_members[Lv_RevDamageRevLow] = Bdat::getMember(wrapper.data, "DamageRevLow"); }

u32 getLv_RevDamageRevLow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevDamageRevLow] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevDamageRevLow], id, 2).valueU16;
}

void initWpn_EnRscR(const CBdatWrapper &wrapper) { s_members[Wpn_EnRscR] = Bdat::getMember(wrapper.data, "RscR"); }

u32 getWpn_EnRscR(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnRscR] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnRscR], id, 2).valueU16;
}

void initWpn_EnRscL(const CBdatWrapper &wrapper) { s_members[Wpn_EnRscL] = Bdat::getMember(wrapper.data, "RscL"); }

u32 getWpn_EnRscL(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnRscL] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnRscL], id, 2).valueU16;
}

void initWpn_EnTypeRange(const CBdatWrapper &wrapper) { s_members[Wpn_EnTypeRange] = Bdat::getMember(wrapper.data, "TypeRange"); }

u32 getWpn_EnTypeRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnTypeRange] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnTypeRange], id, 1).valueU8;
}

void initWpn_EnDamage(const CBdatWrapper &wrapper) { s_members[Wpn_EnDamage] = Bdat::getMember(wrapper.data, "Damage"); }

u32 getWpn_EnDamage(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnDamage] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnDamage], id, 2).valueU16;
}

void initWpn_EnStability(const CBdatWrapper &wrapper) { s_members[Wpn_EnStability] = Bdat::getMember(wrapper.data, "Stability"); }

u32 getWpn_EnStability(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnStability] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnStability], id, 1).valueU8;
}

void initBTL_ClassName(const CBdatWrapper &wrapper) { s_members[BTL_ClassName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getBTL_ClassName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassName], id, 2).valueU16;
}

void initBTL_ClassRole1(const CBdatWrapper &wrapper) { s_members[BTL_ClassRole1] = Bdat::getMember(wrapper.data, "Role1"); }

u32 getBTL_ClassRole1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassRole1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassRole1], id, 1).valueU8;
}

void initBTL_ClassRole2(const CBdatWrapper &wrapper) { s_members[BTL_ClassRole2] = Bdat::getMember(wrapper.data, "Role2"); }

u32 getBTL_ClassRole2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassRole2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassRole2], id, 1).valueU8;
}

void initBTL_ClassRole3(const CBdatWrapper &wrapper) { s_members[BTL_ClassRole3] = Bdat::getMember(wrapper.data, "Role3"); }

u32 getBTL_ClassRole3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassRole3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassRole3], id, 1).valueU8;
}

void initBTL_ClassDamageDown(const CBdatWrapper &wrapper) { s_members[BTL_ClassDamageDown] = Bdat::getMember(wrapper.data, "DamageDown"); }

u32 getBTL_ClassDamageDown(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassDamageDown] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassDamageDown], id, 1).valueU8;
}

void initBTL_ClassDamageUP(const CBdatWrapper &wrapper) { s_members[BTL_ClassDamageUP] = Bdat::getMember(wrapper.data, "DamageUP"); }

u32 getBTL_ClassDamageUP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassDamageUP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassDamageUP], id, 1).valueU8;
}

void initBTL_ClassHealUP(const CBdatWrapper &wrapper) { s_members[BTL_ClassHealUP] = Bdat::getMember(wrapper.data, "HealUP"); }

u32 getBTL_ClassHealUP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassHealUP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassHealUP], id, 1).valueU8;
}

void initBTL_ClassAutoHate(const CBdatWrapper &wrapper) { s_members[BTL_ClassAutoHate] = Bdat::getMember(wrapper.data, "AutoHate"); }

s32 getBTL_ClassAutoHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassAutoHate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassAutoHate], id, 4).valueS8;
}

void initBTL_ClassArtsHate(const CBdatWrapper &wrapper) { s_members[BTL_ClassArtsHate] = Bdat::getMember(wrapper.data, "ArtsHate"); }

s32 getBTL_ClassArtsHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassArtsHate] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassArtsHate], id, 4).valueS8;
}

void initBTL_EnhanceEnhanceEffect(const CBdatWrapper &wrapper) {
  s_members[BTL_EnhanceEnhanceEffect] = Bdat::getMember(wrapper.data, "EnhanceEffect");
}

u32 getBTL_EnhanceEnhanceEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEnhanceEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEnhanceEffect], id, 2).valueU16;
}

void initBTL_EnhanceParam1(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceParam1] = Bdat::getMember(wrapper.data, "Param1"); }

f32 getBTL_EnhanceParam1(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BTL_EnhanceParam1] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BTL_EnhanceParam1], id, 8).valueF32;
  }

  return value;
}

void initBTL_EnhanceParam2(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceParam2] = Bdat::getMember(wrapper.data, "Param2"); }

f32 getBTL_EnhanceParam2(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BTL_EnhanceParam2] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[BTL_EnhanceParam2], id, 8).valueF32;
  }

  return value;
}

void initBTL_EnhanceCaption(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getBTL_EnhanceCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceCaption], id, 2).valueU16;
}

void initBTL_EnhanceEffCategory(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getBTL_EnhanceEffCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffCategory], id, 1).valueU8;
}

void initBTL_EnhanceEffIcon(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffIcon] = Bdat::getMember(wrapper.data, "Icon"); }

u32 getBTL_EnhanceEffIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffIcon], id, 1).valueU8;
}

void initBTL_EnhanceEffFlagCondition(const CBdatWrapper &wrapper) {
  s_members[BTL_EnhanceEffFlagCondition] = Bdat::getMember(wrapper.data, "Flag");
  s_members[BTL_EnhanceEffFlagConditionFlag] = Bdat::getMember(wrapper.data, "Condition");
}

bool isBTL_EnhanceEffFlagCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffFlagCondition] == nullptr || s_members[BTL_EnhanceEffFlagConditionFlag] == nullptr ||
      id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_EnhanceEffFlagCondition], id, s_members[BTL_EnhanceEffFlagConditionFlag]) != 0;
}

void initBTL_EnhanceEffFlagUI(const CBdatWrapper &wrapper) {
  s_members[BTL_EnhanceEffFlagUI] = Bdat::getMember(wrapper.data, "Flag");
  s_members[BTL_EnhanceEffFlagUIFlag] = Bdat::getMember(wrapper.data, "UI");
}

bool isBTL_EnhanceEffFlagUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffFlagUI] == nullptr || s_members[BTL_EnhanceEffFlagUIFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_EnhanceEffFlagUI], id, s_members[BTL_EnhanceEffFlagUIFlag]) != 0;
}

void initBTL_EnhanceEffParam(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffParam] = Bdat::getMember(wrapper.data, "Param"); }

u32 getBTL_EnhanceEffParam(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffParam] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffParam], id, 2).valueU16;
}

void initBTL_EnhanceEffName(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getBTL_EnhanceEffName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffName], id, 2).valueU16;
}

void initBTL_EnhanceEffDirect(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffDirect] = Bdat::getMember(wrapper.data, "Direct"); }

u32 getBTL_EnhanceEffDirect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffDirect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffDirect], id, 1).valueU8;
}

void initBTL_Skill_BlName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getBTL_Skill_BlName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlName], id, 2).valueU16;
}

void initBTL_Skill_BlDebugName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getBTL_Skill_BlDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlDebugName], id, 7).valueString;
}

void initBTL_Skill_BlEnhance1(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance1] = Bdat::getMember(wrapper.data, "Enhance1"); }

u32 getBTL_Skill_BlEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance1], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance2(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance2] = Bdat::getMember(wrapper.data, "Enhance2"); }

u32 getBTL_Skill_BlEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance2], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance3(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance3] = Bdat::getMember(wrapper.data, "Enhance3"); }

u32 getBTL_Skill_BlEnhance3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance3], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance4(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance4] = Bdat::getMember(wrapper.data, "Enhance4"); }

u32 getBTL_Skill_BlEnhance4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance4], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance5(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance5] = Bdat::getMember(wrapper.data, "Enhance5"); }

u32 getBTL_Skill_BlEnhance5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance5], id, 2).valueU16;
}

void initBTL_Skill_BlFlagcommon(const CBdatWrapper &wrapper) {
  s_members[BTL_Skill_BlFlagcommon] = Bdat::getMember(wrapper.data, "Flag");
  s_members[BTL_Skill_BlFlagcommonFlag] = Bdat::getMember(wrapper.data, "common");
}

bool isBTL_Skill_BlFlagcommon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlFlagcommon] == nullptr || s_members[BTL_Skill_BlFlagcommonFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_Skill_BlFlagcommon], id, s_members[BTL_Skill_BlFlagcommonFlag]) != 0;
}

void initBTL_Skill_BlTank(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlTank] = Bdat::getMember(wrapper.data, "Tank"); }

u32 getBTL_Skill_BlTank(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlTank] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlTank], id, 1).valueU8;
}

void initBTL_Skill_BlAttacker(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlAttacker] = Bdat::getMember(wrapper.data, "Attacker"); }

u32 getBTL_Skill_BlAttacker(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlAttacker] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlAttacker], id, 1).valueU8;
}

void initBTL_Skill_BlHealer(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlHealer] = Bdat::getMember(wrapper.data, "Healer"); }

u32 getBTL_Skill_BlHealer(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlHealer] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlHealer], id, 1).valueU8;
}

void initBTL_Skill_BlUI(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlUI] = Bdat::getMember(wrapper.data, "UI"); }

u32 getBTL_Skill_BlUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlUI], id, 1).valueU8;
}

void initBTL_Skill_DrName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getBTL_Skill_DrName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrName], id, 2).valueU16;
}

void initBTL_Skill_DrDebugName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getBTL_Skill_DrDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrDebugName], id, 7).valueString;
}

void initBTL_Skill_DrEnhance(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrEnhance] = Bdat::getMember(wrapper.data, "Enhance"); }

u32 getBTL_Skill_DrEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrEnhance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrEnhance], id, 2).valueU16;
}

void initBTL_Skill_DrUI(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrUI] = Bdat::getMember(wrapper.data, "UI"); }

u32 getBTL_Skill_DrUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrUI], id, 2).valueU16;
}

void initBTL_BuffName(const CBdatWrapper &wrapper) { s_members[BTL_BuffName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getBTL_BuffName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffName], id, 1).valueU8;
}

void initBTL_BuffDebugName(const CBdatWrapper &wrapper) { s_members[BTL_BuffDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getBTL_BuffDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_BuffDebugName], id, 7).valueString;
}

void initBTL_BuffCaption(const CBdatWrapper &wrapper) { s_members[BTL_BuffCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getBTL_BuffCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffCaption], id, 1).valueU8;
}

void initBTL_BuffBaseNum(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseNum] = Bdat::getMember(wrapper.data, "BaseNum"); }

u32 getBTL_BuffBaseNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseNum], id, 2).valueU16;
}

void initBTL_BuffBaseTime(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseTime] = Bdat::getMember(wrapper.data, "BaseTime"); }

u32 getBTL_BuffBaseTime(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseTime] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseTime], id, 2).valueU16;
}

void initBTL_BuffBaseRecast(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseRecast] = Bdat::getMember(wrapper.data, "BaseRecast"); }

u32 getBTL_BuffBaseRecast(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseRecast] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseRecast], id, 2).valueU16;
}

void initBTL_BuffBaseProb(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseProb] = Bdat::getMember(wrapper.data, "BaseProb"); }

u32 getBTL_BuffBaseProb(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseProb] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseProb], id, 1).valueU8;
}

void initBTL_BuffInterval(const CBdatWrapper &wrapper) { s_members[BTL_BuffInterval] = Bdat::getMember(wrapper.data, "Interval"); }

u32 getBTL_BuffInterval(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffInterval] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffInterval], id, 2).valueU16;
}

void initBTL_BuffEffect(const CBdatWrapper &wrapper) { s_members[BTL_BuffEffect] = Bdat::getMember(wrapper.data, "Effect"); }

const char *getBTL_BuffEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_BuffEffect], id, 7).valueString;
}

void initBTL_BuffIcon(const CBdatWrapper &wrapper) { s_members[BTL_BuffIcon] = Bdat::getMember(wrapper.data, "Icon"); }

u32 getBTL_BuffIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffIcon], id, 2).valueU16;
}

void initBTL_Bl_PersonalityFlagcommon(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_PersonalityFlagcommon] = Bdat::getMember(wrapper.data, "Flag");
  s_members[BTL_Bl_PersonalityFlagcommonFlag] = Bdat::getMember(wrapper.data, "common");
}

bool isBTL_Bl_PersonalityFlagcommon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_PersonalityFlagcommon] == nullptr || s_members[BTL_Bl_PersonalityFlagcommonFlag] == nullptr ||
      id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_Bl_PersonalityFlagcommon], id, s_members[BTL_Bl_PersonalityFlagcommonFlag]) != 0;
}

void initBTL_Bl_PersonalityKizunaBase(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_PersonalityKizunaBase] = Bdat::getMember(wrapper.data, "KizunaBase");
}

u32 getBTL_Bl_PersonalityKizunaBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_PersonalityKizunaBase] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_PersonalityKizunaBase], id, 1).valueU8;
}

void initBTL_Bl_PersonalityVoiceID(const CBdatWrapper &wrapper) { s_members[BTL_Bl_PersonalityVoiceID] = Bdat::getMember(wrapper.data, "VoiceID"); }

u32 getBTL_Bl_PersonalityVoiceID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_PersonalityVoiceID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_PersonalityVoiceID], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkLinkNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkLinkNum] = Bdat::getMember(wrapper.data, "LinkNum"); }

u32 getBTL_Bl_KizunaLinkLinkNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkLinkNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkLinkNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkDeadNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkDeadNum] = Bdat::getMember(wrapper.data, "DeadNum"); }

u32 getBTL_Bl_KizunaLinkDeadNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkDeadNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkDeadNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkAppStNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkAppStNum] = Bdat::getMember(wrapper.data, "AppStNum"); }

u32 getBTL_Bl_KizunaLinkAppStNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppStNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppStNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkAppEndNum(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkAppEndNum] = Bdat::getMember(wrapper.data, "AppEndNum");
}

u32 getBTL_Bl_KizunaLinkAppEndNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppEndNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppEndNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkAppCond(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkAppCond] = Bdat::getMember(wrapper.data, "AppCond"); }

u32 getBTL_Bl_KizunaLinkAppCond(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppCond] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppCond], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkAppCondNum(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkAppCondNum] = Bdat::getMember(wrapper.data, "AppCondNum");
}

u32 getBTL_Bl_KizunaLinkAppCondNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppCondNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppCondNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkReJudgef(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkReJudgef] = Bdat::getMember(wrapper.data, "ReJudgef"); }

u32 getBTL_Bl_KizunaLinkReJudgef(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkReJudgef] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkReJudgef], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSpActType(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkSpActType] = Bdat::getMember(wrapper.data, "SpActType");
}

u32 getBTL_Bl_KizunaLinkSpActType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSpActType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSpActType], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSpActNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSpActNum] = Bdat::getMember(wrapper.data, "SpActNum"); }

u32 getBTL_Bl_KizunaLinkSpActNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSpActNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSpActNum], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSpActf(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSpActf] = Bdat::getMember(wrapper.data, "SpActf"); }

u32 getBTL_Bl_KizunaLinkSpActf(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSpActf] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSpActf], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkStandDir(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkStandDir] = Bdat::getMember(wrapper.data, "StandDir"); }

u32 getBTL_Bl_KizunaLinkStandDir(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkStandDir] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkStandDir], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSetKizunaLink1(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkSetKizunaLink1] = Bdat::getMember(wrapper.data, "KizunaLink1");
}

u32 getBTL_Bl_KizunaLinkSetKizunaLink1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetKizunaLink1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetKizunaLink1], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetKizunaLink2(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkSetKizunaLink2] = Bdat::getMember(wrapper.data, "KizunaLink2");
}

u32 getBTL_Bl_KizunaLinkSetKizunaLink2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetKizunaLink2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetKizunaLink2], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetLinkChType(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkSetLinkChType] = Bdat::getMember(wrapper.data, "LinkChType");
}

u32 getBTL_Bl_KizunaLinkSetLinkChType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetLinkChType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetLinkChType], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetLinkChNum(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkSetLinkChNum] = Bdat::getMember(wrapper.data, "LinkChNum");
}

u32 getBTL_Bl_KizunaLinkSetLinkChNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetLinkChNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetLinkChNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetVoiceID(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_KizunaLinkSetVoiceID] = Bdat::getMember(wrapper.data, "VoiceID");
}

u32 getBTL_Bl_KizunaLinkSetVoiceID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetVoiceID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetVoiceID], id, 1).valueU8;
}

void initBTL_TestSettingDr1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1] = Bdat::getMember(wrapper.data, "Dr1"); }

u32 getBTL_TestSettingDr1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1], id, 1).valueU8;
}

void initBTL_TestSettingDr1Lv(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Lv] = Bdat::getMember(wrapper.data, "Dr1Lv"); }

u32 getBTL_TestSettingDr1Lv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Lv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Lv], id, 1).valueU8;
}

void initBTL_TestSettingDr1Bl1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Bl1] = Bdat::getMember(wrapper.data, "Dr1Bl1"); }

u32 getBTL_TestSettingDr1Bl1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Bl1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Bl1], id, 2).valueU16;
}

void initBTL_TestSettingDr1Bl2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Bl2] = Bdat::getMember(wrapper.data, "Dr1Bl2"); }

u32 getBTL_TestSettingDr1Bl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Bl2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Bl2], id, 2).valueU16;
}

void initBTL_TestSettingDr1Bl3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Bl3] = Bdat::getMember(wrapper.data, "Dr1Bl3"); }

u32 getBTL_TestSettingDr1Bl3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Bl3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Bl3], id, 2).valueU16;
}

void initBTL_TestSettingDr2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2] = Bdat::getMember(wrapper.data, "Dr2"); }

u32 getBTL_TestSettingDr2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2], id, 1).valueU8;
}

void initBTL_TestSettingDr2Lv(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Lv] = Bdat::getMember(wrapper.data, "Dr2Lv"); }

u32 getBTL_TestSettingDr2Lv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Lv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Lv], id, 1).valueU8;
}

void initBTL_TestSettingDr2Bl1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Bl1] = Bdat::getMember(wrapper.data, "Dr2Bl1"); }

u32 getBTL_TestSettingDr2Bl1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Bl1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Bl1], id, 2).valueU16;
}

void initBTL_TestSettingDr2Bl2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Bl2] = Bdat::getMember(wrapper.data, "Dr2Bl2"); }

u32 getBTL_TestSettingDr2Bl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Bl2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Bl2], id, 2).valueU16;
}

void initBTL_TestSettingDr2Bl3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Bl3] = Bdat::getMember(wrapper.data, "Dr2Bl3"); }

u32 getBTL_TestSettingDr2Bl3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Bl3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Bl3], id, 2).valueU16;
}

void initBTL_TestSettingDr3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3] = Bdat::getMember(wrapper.data, "Dr3"); }

u32 getBTL_TestSettingDr3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3], id, 1).valueU8;
}

void initBTL_TestSettingDr3Lv(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Lv] = Bdat::getMember(wrapper.data, "Dr3Lv"); }

u32 getBTL_TestSettingDr3Lv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Lv] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Lv], id, 1).valueU8;
}

void initBTL_TestSettingDr3Bl1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Bl1] = Bdat::getMember(wrapper.data, "Dr3Bl1"); }

u32 getBTL_TestSettingDr3Bl1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Bl1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Bl1], id, 2).valueU16;
}

void initBTL_TestSettingDr3Bl2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Bl2] = Bdat::getMember(wrapper.data, "Dr3Bl2"); }

u32 getBTL_TestSettingDr3Bl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Bl2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Bl2], id, 2).valueU16;
}

void initBTL_TestSettingDr3Bl3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Bl3] = Bdat::getMember(wrapper.data, "Dr3Bl3"); }

u32 getBTL_TestSettingDr3Bl3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Bl3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Bl3], id, 2).valueU16;
}

void initBTL_HanaBaseNCondNum(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseNCondNum] = Bdat::getMember(wrapper.data, "NCondNum"); }

u32 getBTL_HanaBaseNCondNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseNCondNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseNCondNum], id, 1).valueU8;
}

void initBTL_HanaBaseECondNum(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseECondNum] = Bdat::getMember(wrapper.data, "ECondNum"); }

u32 getBTL_HanaBaseECondNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseECondNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseECondNum], id, 1).valueU8;
}

void initBTL_HanaBaseNArtsNum(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseNArtsNum] = Bdat::getMember(wrapper.data, "NArtsNum"); }

u32 getBTL_HanaBaseNArtsNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseNArtsNum] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseNArtsNum], id, 1).valueU8;
}

void initBTL_HanaBaseCircuit1Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit1Num] = Bdat::getMember(wrapper.data, "Circuit1Num"); }

u32 getBTL_HanaBaseCircuit1Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit1Num] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit1Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit2Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit2Num] = Bdat::getMember(wrapper.data, "Circuit2Num"); }

u32 getBTL_HanaBaseCircuit2Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit2Num] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit2Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit3Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit3Num] = Bdat::getMember(wrapper.data, "Circuit3Num"); }

u32 getBTL_HanaBaseCircuit3Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit3Num] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit3Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit4Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit4Num] = Bdat::getMember(wrapper.data, "Circuit4Num"); }

u32 getBTL_HanaBaseCircuit4Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit4Num] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit4Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit5Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit5Num] = Bdat::getMember(wrapper.data, "Circuit5Num"); }

u32 getBTL_HanaBaseCircuit5Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit5Num] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit5Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit6Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit6Num] = Bdat::getMember(wrapper.data, "Circuit6Num"); }

u32 getBTL_HanaBaseCircuit6Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit6Num] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit6Num], id, 2).valueU16;
}

void initBTL_HanaBaseUI(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getBTL_HanaBaseUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseUI], id, 7).valueString;
}

void initBTL_HanaPowerPowerNum1(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerPowerNum1] = Bdat::getMember(wrapper.data, "PowerNum1"); }

u32 getBTL_HanaPowerPowerNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerPowerNum1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerPowerNum1], id, 2).valueU16;
}

void initBTL_HanaPowerPowerNum2(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerPowerNum2] = Bdat::getMember(wrapper.data, "PowerNum2"); }

u32 getBTL_HanaPowerPowerNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerPowerNum2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerPowerNum2], id, 2).valueU16;
}

void initBTL_HanaPowerPowerNum3(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerPowerNum3] = Bdat::getMember(wrapper.data, "PowerNum3"); }

u32 getBTL_HanaPowerPowerNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerPowerNum3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerPowerNum3], id, 2).valueU16;
}

void initBTL_HanaPowerEtherNum1(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerEtherNum1] = Bdat::getMember(wrapper.data, "EtherNum1"); }

u32 getBTL_HanaPowerEtherNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerEtherNum1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerEtherNum1], id, 3).valueU32;
}

void initBTL_HanaPowerEtherNum2(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerEtherNum2] = Bdat::getMember(wrapper.data, "EtherNum2"); }

u32 getBTL_HanaPowerEtherNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerEtherNum2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerEtherNum2], id, 3).valueU32;
}

void initBTL_HanaPowerEtherNum3(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerEtherNum3] = Bdat::getMember(wrapper.data, "EtherNum3"); }

u32 getBTL_HanaPowerEtherNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerEtherNum3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerEtherNum3], id, 3).valueU32;
}

void initBTL_HanaChipsetRoleParts(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetRoleParts] = Bdat::getMember(wrapper.data, "RoleParts"); }

u32 getBTL_HanaChipsetRoleParts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetRoleParts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetRoleParts], id, 2).valueU16;
}

void initBTL_HanaChipsetAtrParts(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetAtrParts] = Bdat::getMember(wrapper.data, "AtrParts"); }

u32 getBTL_HanaChipsetAtrParts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetAtrParts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetAtrParts], id, 2).valueU16;
}

void initBTL_HanaChipsetNArtsParts1(const CBdatWrapper &wrapper) {
  s_members[BTL_HanaChipsetNArtsParts1] = Bdat::getMember(wrapper.data, "NArtsParts1");
}

u32 getBTL_HanaChipsetNArtsParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNArtsParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNArtsParts1], id, 2).valueU16;
}

void initBTL_HanaChipsetNArtsParts2(const CBdatWrapper &wrapper) {
  s_members[BTL_HanaChipsetNArtsParts2] = Bdat::getMember(wrapper.data, "NArtsParts2");
}

u32 getBTL_HanaChipsetNArtsParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNArtsParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNArtsParts2], id, 2).valueU16;
}

void initBTL_HanaChipsetNArtsParts3(const CBdatWrapper &wrapper) {
  s_members[BTL_HanaChipsetNArtsParts3] = Bdat::getMember(wrapper.data, "NArtsParts3");
}

u32 getBTL_HanaChipsetNArtsParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNArtsParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNArtsParts3], id, 2).valueU16;
}

void initBTL_HanaChipsetNCondParts1(const CBdatWrapper &wrapper) {
  s_members[BTL_HanaChipsetNCondParts1] = Bdat::getMember(wrapper.data, "NCondParts1");
}

u32 getBTL_HanaChipsetNCondParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNCondParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNCondParts1], id, 2).valueU16;
}

void initBTL_HanaChipsetNCondParts2(const CBdatWrapper &wrapper) {
  s_members[BTL_HanaChipsetNCondParts2] = Bdat::getMember(wrapper.data, "NCondParts2");
}

u32 getBTL_HanaChipsetNCondParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNCondParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNCondParts2], id, 2).valueU16;
}

void initBTL_HanaChipsetNCondParts3(const CBdatWrapper &wrapper) {
  s_members[BTL_HanaChipsetNCondParts3] = Bdat::getMember(wrapper.data, "NCondParts3");
}

u32 getBTL_HanaChipsetNCondParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNCondParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNCondParts3], id, 2).valueU16;
}

void initBTL_HanaChipsetUI(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetUI] = Bdat::getMember(wrapper.data, "UI"); }

const char *getBTL_HanaChipsetUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetUI] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetUI], id, 7).valueString;
}

void initWildcardDatavalueF4(const CBdatWrapper &wrapper) { s_members[WildcardDatavalueF4] = Bdat::getMember(wrapper.data, "valueF4"); }

f32 getWildcardDatavalueF4(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[WildcardDatavalueF4] != nullptr && id >= Bdat::getIdTop(wrapper.data) &&
      id < Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    value = wrapper.getValCheck(s_members[WildcardDatavalueF4], id, 8).valueF32;
  }

  return value;
}

void initWildcardDatavalueU2(const CBdatWrapper &wrapper) { s_members[WildcardDatavalueU2] = Bdat::getMember(wrapper.data, "valueU2"); }

u32 getWildcardDatavalueU2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[WildcardDatavalueU2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[WildcardDatavalueU2], id, 2).valueU16;
}

void initVo_Field_FilterTargetFile(const CBdatWrapper &wrapper) {
  s_members[Vo_Field_FilterTargetFile] = Bdat::getMember(wrapper.data, "TargetFile");
}

const char *getVo_Field_FilterTargetFile(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Vo_Field_FilterTargetFile] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[Vo_Field_FilterTargetFile], id, 7).valueString;
}

void initVo_Field_FilterCondition(const CBdatWrapper &wrapper) { s_members[Vo_Field_FilterCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getVo_Field_FilterCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Vo_Field_FilterCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Vo_Field_FilterCondition], id, 2).valueU16;
}

void initVo_Field_FilterChangeFile(const CBdatWrapper &wrapper) { s_Vo_Field_FilterChangeFile = Bdat::getMember(wrapper.data, "ChangeFile"); }

const char *getVo_Field_FilterChangeFile(const CBdatWrapper &wrapper, u32 id) {
  if (s_Vo_Field_FilterChangeFile == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_Vo_Field_FilterChangeFile, id, 7).valueString;
}

} // namespace _gfbbt

GfBdatBtl::GfBdatBtl()
    : unknown10(nullptr), unknown18(nullptr), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr),
      unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr), unknown70(nullptr), unknown78(nullptr),
      unknown80(nullptr), unknown88(nullptr), unknown90(nullptr), unknown98(nullptr), unknowna0(nullptr), unknowna8(nullptr), unknownb0(nullptr) {
  bdatRefresh();
}

GfBdatBtl::~GfBdatBtl() { destroyFP(); }

void GfBdatBtl::destroyFP() {
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }

  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }

  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }

  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }

  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }

  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }

  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }

  if (unknown48 != nullptr) {
    delete unknown48;
    unknown48 = nullptr;
  }

  if (unknown50 != nullptr) {
    delete unknown50;
    unknown50 = nullptr;
  }

  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }

  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }

  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }

  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }

  if (unknown78 != nullptr) {
    delete unknown78;
    unknown78 = nullptr;
  }

  if (unknown80 != nullptr) {
    delete unknown80;
    unknown80 = nullptr;
  }

  if (unknown88 != nullptr) {
    delete unknown88;
    unknown88 = nullptr;
  }

  if (unknown90 != nullptr) {
    delete unknown90;
    unknown90 = nullptr;
  }

  if (unknown98 != nullptr) {
    delete unknown98;
    unknown98 = nullptr;
  }

  if (unknowna0 != nullptr) {
    delete unknowna0;
    unknowna0 = nullptr;
  }

  if (unknowna8 != nullptr) {
    delete unknowna8;
    unknowna8 = nullptr;
  }

  if (unknownb0 != nullptr) {
    delete unknownb0;
    unknownb0 = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatBtl::createFP() {
  unknown10 = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_DR);
  unknown18 = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_BL);
  unknown20 = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_BL_SP);
  unknown28 = NEW_BDAT_WRAPPER(BDAT_BTL_GROW);
  unknown30 = NEW_BDAT_WRAPPER(BDAT_BTL_LV_REV);
  unknown38 = NEW_BDAT_WRAPPER(BDAT_BTL_WPN_EN);
  unknown40 = NEW_BDAT_WRAPPER(BDAT_BTL_CLASS);
  unknown48 = NEW_BDAT_WRAPPER(BDAT_BTL_ENHANCE);
  unknown50 = NEW_BDAT_WRAPPER(BDAT_BTL_ENHANCE_EFF);
  unknown58 = NEW_BDAT_WRAPPER(BDAT_BTL_SKILL_BL);
  unknown60 = NEW_BDAT_WRAPPER(BDAT_BTL_SKILL_DR);
  unknown68 = NEW_BDAT_WRAPPER(BDAT_BTL_BUFF);
  unknown70 = NEW_BDAT_WRAPPER(BDAT_BTL_BL_PERSONALITY);
  unknown78 = NEW_BDAT_WRAPPER(BDAT_BTL_BL_KIZUNA_LINK);
  unknown80 = NEW_BDAT_WRAPPER(BDAT_BTL_BL_KIZUNA_LINK_SET);
  unknown88 = NEW_BDAT_WRAPPER(BDAT_BTL_TEST_SETTING);
  unknown90 = NEW_BDAT_WRAPPER(BDAT_BTL_HANA_BASE);
  unknown98 = NEW_BDAT_WRAPPER(BDAT_BTL_HANA_POWER);
  unknowna0 = NEW_BDAT_WRAPPER(BDAT_BTL_HANA_CHIPSET);
  unknowna8 = NEW_BDAT_WRAPPER(BDAT_FLD_WILDCARD_DATA);
  unknownb0 = NEW_BDAT_WRAPPER(BDAT_VO_FIELD_FILTER);
}

void GfBdatBtl::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbbt::initArtsDrName(*unknown10);
  _gfbbt::initArtsDrDebugName(*unknown10);
  _gfbbt::initArtsDrCaption(*unknown10);
  _gfbbt::initArtsDrDriver(*unknown10);
  _gfbbt::initArtsDrWpnType(*unknown10);
  _gfbbt::initArtsDrActNo(*unknown10);
  _gfbbt::initArtsDrArtsType(*unknown10);
  _gfbbt::initArtsDrArtsBuff(*unknown10);
  _gfbbt::initArtsDrAtrType(*unknown10);
  _gfbbt::initArtsDrFlagNormal(*unknown10);
  _gfbbt::initArtsDrFlagPierce(*unknown10);
  _gfbbt::initArtsDrFlagNoRepelled(*unknown10);
  _gfbbt::initArtsDrNextArts(*unknown10);
  _gfbbt::initArtsDrTarget(*unknown10);
  _gfbbt::initArtsDrDistance(*unknown10);
  _gfbbt::initArtsDrRangeType(*unknown10);
  _gfbbt::initArtsDrRadius(*unknown10);
  _gfbbt::initArtsDrLength(*unknown10);
  _gfbbt::initArtsDrHate(*unknown10);
  _gfbbt::initArtsDrHitRevise(*unknown10);
  _gfbbt::initArtsDrCriRevise(*unknown10);
  _gfbbt::initArtsDrBulletID(*unknown10);
  _gfbbt::initArtsDrBulletNum(*unknown10);
  _gfbbt::initArtsDrHitFrm1(*unknown10);
  _gfbbt::initArtsDrHitFrm2(*unknown10);
  _gfbbt::initArtsDrHitFrm3(*unknown10);
  _gfbbt::initArtsDrHitFrm4(*unknown10);
  _gfbbt::initArtsDrHitFrm5(*unknown10);
  _gfbbt::initArtsDrHitFrm6(*unknown10);
  _gfbbt::initArtsDrHitFrm7(*unknown10);
  _gfbbt::initArtsDrHitFrm8(*unknown10);
  _gfbbt::initArtsDrHitFrm9(*unknown10);
  _gfbbt::initArtsDrHitFrm10(*unknown10);
  _gfbbt::initArtsDrHitFrm11(*unknown10);
  _gfbbt::initArtsDrHitFrm12(*unknown10);
  _gfbbt::initArtsDrHitFrm13(*unknown10);
  _gfbbt::initArtsDrHitFrm14(*unknown10);
  _gfbbt::initArtsDrHitFrm15(*unknown10);
  _gfbbt::initArtsDrHitFrm16(*unknown10);
  _gfbbt::initArtsDrEfp1(*unknown10);
  _gfbbt::initArtsDrEfp2(*unknown10);
  _gfbbt::initArtsDrEfp3(*unknown10);
  _gfbbt::initArtsDrEfp4(*unknown10);
  _gfbbt::initArtsDrEfp5(*unknown10);
  _gfbbt::initArtsDrEfp6(*unknown10);
  _gfbbt::initArtsDrEfp7(*unknown10);
  _gfbbt::initArtsDrEfp8(*unknown10);
  _gfbbt::initArtsDrEfp9(*unknown10);
  _gfbbt::initArtsDrEfp10(*unknown10);
  _gfbbt::initArtsDrEfp11(*unknown10);
  _gfbbt::initArtsDrEfp12(*unknown10);
  _gfbbt::initArtsDrEfp13(*unknown10);
  _gfbbt::initArtsDrEfp14(*unknown10);
  _gfbbt::initArtsDrEfp15(*unknown10);
  _gfbbt::initArtsDrEfp16(*unknown10);
  _gfbbt::initArtsDrHitDirID1(*unknown10);
  _gfbbt::initArtsDrHitDirID2(*unknown10);
  _gfbbt::initArtsDrHitDirID3(*unknown10);
  _gfbbt::initArtsDrHitDirID4(*unknown10);
  _gfbbt::initArtsDrHitDirID5(*unknown10);
  _gfbbt::initArtsDrHitDirID6(*unknown10);
  _gfbbt::initArtsDrHitDirID7(*unknown10);
  _gfbbt::initArtsDrHitDirID8(*unknown10);
  _gfbbt::initArtsDrHitDirID9(*unknown10);
  _gfbbt::initArtsDrHitDirID10(*unknown10);
  _gfbbt::initArtsDrHitDirID11(*unknown10);
  _gfbbt::initArtsDrHitDirID12(*unknown10);
  _gfbbt::initArtsDrHitDirID13(*unknown10);
  _gfbbt::initArtsDrHitDirID14(*unknown10);
  _gfbbt::initArtsDrHitDirID15(*unknown10);
  _gfbbt::initArtsDrHitDirID16(*unknown10);
  _gfbbt::initArtsDrDmgRt1(*unknown10);
  _gfbbt::initArtsDrDmgRt2(*unknown10);
  _gfbbt::initArtsDrDmgRt3(*unknown10);
  _gfbbt::initArtsDrDmgRt4(*unknown10);
  _gfbbt::initArtsDrDmgRt5(*unknown10);
  _gfbbt::initArtsDrDmgRt6(*unknown10);
  _gfbbt::initArtsDrDmgRt7(*unknown10);
  _gfbbt::initArtsDrDmgRt8(*unknown10);
  _gfbbt::initArtsDrDmgRt9(*unknown10);
  _gfbbt::initArtsDrDmgRt10(*unknown10);
  _gfbbt::initArtsDrDmgRt11(*unknown10);
  _gfbbt::initArtsDrDmgRt12(*unknown10);
  _gfbbt::initArtsDrDmgRt13(*unknown10);
  _gfbbt::initArtsDrDmgRt14(*unknown10);
  _gfbbt::initArtsDrDmgRt15(*unknown10);
  _gfbbt::initArtsDrDmgRt16(*unknown10);
  _gfbbt::initArtsDrReAct1(*unknown10);
  _gfbbt::initArtsDrReAct2(*unknown10);
  _gfbbt::initArtsDrReAct3(*unknown10);
  _gfbbt::initArtsDrReAct4(*unknown10);
  _gfbbt::initArtsDrReAct5(*unknown10);
  _gfbbt::initArtsDrReAct6(*unknown10);
  _gfbbt::initArtsDrReAct7(*unknown10);
  _gfbbt::initArtsDrReAct8(*unknown10);
  _gfbbt::initArtsDrReAct9(*unknown10);
  _gfbbt::initArtsDrReAct10(*unknown10);
  _gfbbt::initArtsDrReAct11(*unknown10);
  _gfbbt::initArtsDrReAct12(*unknown10);
  _gfbbt::initArtsDrReAct13(*unknown10);
  _gfbbt::initArtsDrReAct14(*unknown10);
  _gfbbt::initArtsDrReAct15(*unknown10);
  _gfbbt::initArtsDrReAct16(*unknown10);
  _gfbbt::initArtsDrMoveCancelFrm(*unknown10);
  _gfbbt::initArtsDrDmgMgn1(*unknown10);
  _gfbbt::initArtsDrDmgMgn2(*unknown10);
  _gfbbt::initArtsDrDmgMgn3(*unknown10);
  _gfbbt::initArtsDrDmgMgn4(*unknown10);
  _gfbbt::initArtsDrDmgMgn5(*unknown10);
  _gfbbt::initArtsDrDmgMgn6(*unknown10);
  _gfbbt::initArtsDrRecast1(*unknown10);
  _gfbbt::initArtsDrRecast2(*unknown10);
  _gfbbt::initArtsDrRecast3(*unknown10);
  _gfbbt::initArtsDrRecast4(*unknown10);
  _gfbbt::initArtsDrRecast5(*unknown10);
  _gfbbt::initArtsDrRecast6(*unknown10);
  _gfbbt::initArtsDrAtrNum(*unknown10);
  _gfbbt::initArtsDrEnhance1(*unknown10);
  _gfbbt::initArtsDrEnhance2(*unknown10);
  _gfbbt::initArtsDrEnhance3(*unknown10);
  _gfbbt::initArtsDrEnhance4(*unknown10);
  _gfbbt::initArtsDrEnhance5(*unknown10);
  _gfbbt::initArtsDrEnhance6(*unknown10);
  _gfbbt::initArtsDrReleaseLv1(*unknown10);
  _gfbbt::initArtsDrReleaseLv2(*unknown10);
  _gfbbt::initArtsDrReleaseLv3(*unknown10);
  _gfbbt::initArtsDrReleaseLv4(*unknown10);
  _gfbbt::initArtsDrReleaseLv5(*unknown10);
  _gfbbt::initArtsDrNeedWP2(*unknown10);
  _gfbbt::initArtsDrNeedWP3(*unknown10);
  _gfbbt::initArtsDrNeedWP4(*unknown10);
  _gfbbt::initArtsDrNeedWP5(*unknown10);
  _gfbbt::initArtsDrUI(*unknown10);
  _gfbbt::initArtsDrPriority(*unknown10);
  _gfbbt::initArtsBlName(*unknown18);
  _gfbbt::initArtsBlDebugName(*unknown18);
  _gfbbt::initArtsBlCaption(*unknown18);
  _gfbbt::initArtsBlWpnType(*unknown18);
  _gfbbt::initArtsBlCmnBlType(*unknown18);
  _gfbbt::initArtsBlSpLv(*unknown18);
  _gfbbt::initArtsBlActNo(*unknown18);
  _gfbbt::initArtsBlArtsType(*unknown18);
  _gfbbt::initArtsBlArtsBuff(*unknown18);
  _gfbbt::initArtsBlFlagcommon(*unknown18);
  _gfbbt::initArtsBlFlagPierce(*unknown18);
  _gfbbt::initArtsBlTarget(*unknown18);
  _gfbbt::initArtsBlDistance(*unknown18);
  _gfbbt::initArtsBlRangeType(*unknown18);
  _gfbbt::initArtsBlRadius(*unknown18);
  _gfbbt::initArtsBlLength(*unknown18);
  _gfbbt::initArtsBlAtr(*unknown18);
  _gfbbt::initArtsBlHate(*unknown18);
  _gfbbt::initArtsBlHitRevise(*unknown18);
  _gfbbt::initArtsBlCriRevise(*unknown18);
  _gfbbt::initArtsBlBulletID(*unknown18);
  _gfbbt::initArtsBlBulletNum(*unknown18);
  _gfbbt::initArtsBlHitFrm1(*unknown18);
  _gfbbt::initArtsBlHitFrm2(*unknown18);
  _gfbbt::initArtsBlHitFrm3(*unknown18);
  _gfbbt::initArtsBlHitFrm4(*unknown18);
  _gfbbt::initArtsBlHitFrm5(*unknown18);
  _gfbbt::initArtsBlHitFrm6(*unknown18);
  _gfbbt::initArtsBlHitFrm7(*unknown18);
  _gfbbt::initArtsBlHitFrm8(*unknown18);
  _gfbbt::initArtsBlHitFrm9(*unknown18);
  _gfbbt::initArtsBlHitFrm10(*unknown18);
  _gfbbt::initArtsBlHitFrm11(*unknown18);
  _gfbbt::initArtsBlHitFrm12(*unknown18);
  _gfbbt::initArtsBlHitFrm13(*unknown18);
  _gfbbt::initArtsBlHitFrm14(*unknown18);
  _gfbbt::initArtsBlHitFrm15(*unknown18);
  _gfbbt::initArtsBlHitFrm16(*unknown18);
  _gfbbt::initArtsBlEfp1(*unknown18);
  _gfbbt::initArtsBlEfp2(*unknown18);
  _gfbbt::initArtsBlEfp3(*unknown18);
  _gfbbt::initArtsBlEfp4(*unknown18);
  _gfbbt::initArtsBlEfp5(*unknown18);
  _gfbbt::initArtsBlEfp6(*unknown18);
  _gfbbt::initArtsBlEfp7(*unknown18);
  _gfbbt::initArtsBlEfp8(*unknown18);
  _gfbbt::initArtsBlEfp9(*unknown18);
  _gfbbt::initArtsBlEfp10(*unknown18);
  _gfbbt::initArtsBlEfp11(*unknown18);
  _gfbbt::initArtsBlEfp12(*unknown18);
  _gfbbt::initArtsBlEfp13(*unknown18);
  _gfbbt::initArtsBlEfp14(*unknown18);
  _gfbbt::initArtsBlEfp15(*unknown18);
  _gfbbt::initArtsBlEfp16(*unknown18);
  _gfbbt::initArtsBlHitDirID1(*unknown18);
  _gfbbt::initArtsBlHitDirID2(*unknown18);
  _gfbbt::initArtsBlHitDirID3(*unknown18);
  _gfbbt::initArtsBlHitDirID4(*unknown18);
  _gfbbt::initArtsBlHitDirID5(*unknown18);
  _gfbbt::initArtsBlHitDirID6(*unknown18);
  _gfbbt::initArtsBlHitDirID7(*unknown18);
  _gfbbt::initArtsBlHitDirID8(*unknown18);
  _gfbbt::initArtsBlHitDirID9(*unknown18);
  _gfbbt::initArtsBlHitDirID10(*unknown18);
  _gfbbt::initArtsBlHitDirID11(*unknown18);
  _gfbbt::initArtsBlHitDirID12(*unknown18);
  _gfbbt::initArtsBlHitDirID13(*unknown18);
  _gfbbt::initArtsBlHitDirID14(*unknown18);
  _gfbbt::initArtsBlHitDirID15(*unknown18);
  _gfbbt::initArtsBlHitDirID16(*unknown18);
  _gfbbt::initArtsBlDmgRt1(*unknown18);
  _gfbbt::initArtsBlDmgRt2(*unknown18);
  _gfbbt::initArtsBlDmgRt3(*unknown18);
  _gfbbt::initArtsBlDmgRt4(*unknown18);
  _gfbbt::initArtsBlDmgRt5(*unknown18);
  _gfbbt::initArtsBlDmgRt6(*unknown18);
  _gfbbt::initArtsBlDmgRt7(*unknown18);
  _gfbbt::initArtsBlDmgRt8(*unknown18);
  _gfbbt::initArtsBlDmgRt9(*unknown18);
  _gfbbt::initArtsBlDmgRt10(*unknown18);
  _gfbbt::initArtsBlDmgRt11(*unknown18);
  _gfbbt::initArtsBlDmgRt12(*unknown18);
  _gfbbt::initArtsBlDmgRt13(*unknown18);
  _gfbbt::initArtsBlDmgRt14(*unknown18);
  _gfbbt::initArtsBlDmgRt15(*unknown18);
  _gfbbt::initArtsBlDmgRt16(*unknown18);
  _gfbbt::initArtsBlReAct1(*unknown18);
  _gfbbt::initArtsBlReAct2(*unknown18);
  _gfbbt::initArtsBlReAct3(*unknown18);
  _gfbbt::initArtsBlReAct4(*unknown18);
  _gfbbt::initArtsBlReAct5(*unknown18);
  _gfbbt::initArtsBlReAct6(*unknown18);
  _gfbbt::initArtsBlReAct7(*unknown18);
  _gfbbt::initArtsBlReAct8(*unknown18);
  _gfbbt::initArtsBlReAct9(*unknown18);
  _gfbbt::initArtsBlReAct10(*unknown18);
  _gfbbt::initArtsBlReAct11(*unknown18);
  _gfbbt::initArtsBlReAct12(*unknown18);
  _gfbbt::initArtsBlReAct13(*unknown18);
  _gfbbt::initArtsBlReAct14(*unknown18);
  _gfbbt::initArtsBlReAct15(*unknown18);
  _gfbbt::initArtsBlReAct16(*unknown18);
  _gfbbt::initArtsBlDmgMgn1(*unknown18);
  _gfbbt::initArtsBlDmgMgn2(*unknown18);
  _gfbbt::initArtsBlDmgMgn3(*unknown18);
  _gfbbt::initArtsBlDmgMgn4(*unknown18);
  _gfbbt::initArtsBlDmgMgn5(*unknown18);
  _gfbbt::initArtsBlDmgMgn6(*unknown18);
  _gfbbt::initArtsBlAtrNum(*unknown18);
  _gfbbt::initArtsBlEnhance1(*unknown18);
  _gfbbt::initArtsBlEnhance2(*unknown18);
  _gfbbt::initArtsBlEnhance3(*unknown18);
  _gfbbt::initArtsBlEnhance4(*unknown18);
  _gfbbt::initArtsBlEnhance5(*unknown18);
  _gfbbt::initArtsBlEnhance6(*unknown18);
  _gfbbt::initArtsBlBtnType(*unknown18);
  _gfbbt::initArtsBlBtnChal1(*unknown18);
  _gfbbt::initArtsBlUI(*unknown18);
  _gfbbt::initArtsBlSpName(*unknown20);
  _gfbbt::initArtsBlSpDebugName(*unknown20);
  _gfbbt::initArtsBlSpCaption(*unknown20);
  _gfbbt::initArtsBlSpWpnType(*unknown20);
  _gfbbt::initArtsBlSpCmnBlType(*unknown20);
  _gfbbt::initArtsBlSpActNoDr(*unknown20);
  _gfbbt::initArtsBlSpActNoBl(*unknown20);
  _gfbbt::initArtsBlSpActNoBl2(*unknown20);
  _gfbbt::initArtsBlSpBuddyDr(*unknown20);
  _gfbbt::initArtsBlSpAddBl(*unknown20);
  _gfbbt::initArtsBlSpActType(*unknown20);
  _gfbbt::initArtsBlSpPC01(*unknown20);
  _gfbbt::initArtsBlSpPC02(*unknown20);
  _gfbbt::initArtsBlSpPC03(*unknown20);
  _gfbbt::initArtsBlSpPC06(*unknown20);
  _gfbbt::initArtsBlSpArtsType(*unknown20);
  _gfbbt::initArtsBlSpArtsBuff(*unknown20);
  _gfbbt::initArtsBlSpFlagPierce(*unknown20);
  _gfbbt::initArtsBlSpFlagNoMove(*unknown20);
  _gfbbt::initArtsBlSpTarget(*unknown20);
  _gfbbt::initArtsBlSpDistance(*unknown20);
  _gfbbt::initArtsBlSpRangeType(*unknown20);
  _gfbbt::initArtsBlSpRadius(*unknown20);
  _gfbbt::initArtsBlSpLength(*unknown20);
  _gfbbt::initArtsBlSpAtr(*unknown20);
  _gfbbt::initArtsBlSpHate(*unknown20);
  _gfbbt::initArtsBlSpHitRevise(*unknown20);
  _gfbbt::initArtsBlSpCriRevise(*unknown20);
  _gfbbt::initArtsBlSpBulletID(*unknown20);
  _gfbbt::initArtsBlSpBulletEffID(*unknown20);
  _gfbbt::initArtsBlSpBulletNum(*unknown20);
  _gfbbt::initArtsBlSpHitFrm1(*unknown20);
  _gfbbt::initArtsBlSpHitFrm2(*unknown20);
  _gfbbt::initArtsBlSpHitFrm3(*unknown20);
  _gfbbt::initArtsBlSpHitFrm4(*unknown20);
  _gfbbt::initArtsBlSpHitFrm5(*unknown20);
  _gfbbt::initArtsBlSpHitFrm6(*unknown20);
  _gfbbt::initArtsBlSpHitFrm7(*unknown20);
  _gfbbt::initArtsBlSpHitFrm8(*unknown20);
  _gfbbt::initArtsBlSpHitFrm9(*unknown20);
  _gfbbt::initArtsBlSpHitFrm10(*unknown20);
  _gfbbt::initArtsBlSpHitFrm11(*unknown20);
  _gfbbt::initArtsBlSpHitFrm12(*unknown20);
  _gfbbt::initArtsBlSpHitFrm13(*unknown20);
  _gfbbt::initArtsBlSpHitFrm14(*unknown20);
  _gfbbt::initArtsBlSpHitFrm15(*unknown20);
  _gfbbt::initArtsBlSpHitFrm16(*unknown20);
  _gfbbt::initArtsBlSpEfp1(*unknown20);
  _gfbbt::initArtsBlSpEfp2(*unknown20);
  _gfbbt::initArtsBlSpEfp3(*unknown20);
  _gfbbt::initArtsBlSpEfp4(*unknown20);
  _gfbbt::initArtsBlSpEfp5(*unknown20);
  _gfbbt::initArtsBlSpEfp6(*unknown20);
  _gfbbt::initArtsBlSpEfp7(*unknown20);
  _gfbbt::initArtsBlSpEfp8(*unknown20);
  _gfbbt::initArtsBlSpEfp9(*unknown20);
  _gfbbt::initArtsBlSpEfp10(*unknown20);
  _gfbbt::initArtsBlSpEfp11(*unknown20);
  _gfbbt::initArtsBlSpEfp12(*unknown20);
  _gfbbt::initArtsBlSpEfp13(*unknown20);
  _gfbbt::initArtsBlSpEfp14(*unknown20);
  _gfbbt::initArtsBlSpEfp15(*unknown20);
  _gfbbt::initArtsBlSpEfp16(*unknown20);
  _gfbbt::initArtsBlSpHitDirID1(*unknown20);
  _gfbbt::initArtsBlSpHitDirID2(*unknown20);
  _gfbbt::initArtsBlSpHitDirID3(*unknown20);
  _gfbbt::initArtsBlSpHitDirID4(*unknown20);
  _gfbbt::initArtsBlSpHitDirID5(*unknown20);
  _gfbbt::initArtsBlSpHitDirID6(*unknown20);
  _gfbbt::initArtsBlSpHitDirID7(*unknown20);
  _gfbbt::initArtsBlSpHitDirID8(*unknown20);
  _gfbbt::initArtsBlSpHitDirID9(*unknown20);
  _gfbbt::initArtsBlSpHitDirID10(*unknown20);
  _gfbbt::initArtsBlSpHitDirID11(*unknown20);
  _gfbbt::initArtsBlSpHitDirID12(*unknown20);
  _gfbbt::initArtsBlSpHitDirID13(*unknown20);
  _gfbbt::initArtsBlSpHitDirID14(*unknown20);
  _gfbbt::initArtsBlSpHitDirID15(*unknown20);
  _gfbbt::initArtsBlSpHitDirID16(*unknown20);
  _gfbbt::initArtsBlSpDmgRt1(*unknown20);
  _gfbbt::initArtsBlSpDmgRt2(*unknown20);
  _gfbbt::initArtsBlSpDmgRt3(*unknown20);
  _gfbbt::initArtsBlSpDmgRt4(*unknown20);
  _gfbbt::initArtsBlSpDmgRt5(*unknown20);
  _gfbbt::initArtsBlSpDmgRt6(*unknown20);
  _gfbbt::initArtsBlSpDmgRt7(*unknown20);
  _gfbbt::initArtsBlSpDmgRt8(*unknown20);
  _gfbbt::initArtsBlSpDmgRt9(*unknown20);
  _gfbbt::initArtsBlSpDmgRt10(*unknown20);
  _gfbbt::initArtsBlSpDmgRt11(*unknown20);
  _gfbbt::initArtsBlSpDmgRt12(*unknown20);
  _gfbbt::initArtsBlSpDmgRt13(*unknown20);
  _gfbbt::initArtsBlSpDmgRt14(*unknown20);
  _gfbbt::initArtsBlSpDmgRt15(*unknown20);
  _gfbbt::initArtsBlSpDmgRt16(*unknown20);
  _gfbbt::initArtsBlSpReAct1(*unknown20);
  _gfbbt::initArtsBlSpReAct2(*unknown20);
  _gfbbt::initArtsBlSpReAct3(*unknown20);
  _gfbbt::initArtsBlSpReAct4(*unknown20);
  _gfbbt::initArtsBlSpReAct5(*unknown20);
  _gfbbt::initArtsBlSpReAct6(*unknown20);
  _gfbbt::initArtsBlSpReAct7(*unknown20);
  _gfbbt::initArtsBlSpReAct8(*unknown20);
  _gfbbt::initArtsBlSpReAct9(*unknown20);
  _gfbbt::initArtsBlSpReAct10(*unknown20);
  _gfbbt::initArtsBlSpReAct11(*unknown20);
  _gfbbt::initArtsBlSpReAct12(*unknown20);
  _gfbbt::initArtsBlSpReAct13(*unknown20);
  _gfbbt::initArtsBlSpReAct14(*unknown20);
  _gfbbt::initArtsBlSpReAct15(*unknown20);
  _gfbbt::initArtsBlSpReAct16(*unknown20);
  _gfbbt::initArtsBlSpDmgMgn(*unknown20);
  _gfbbt::initArtsBlSpRecast(*unknown20);
  _gfbbt::initArtsBlSpAtrNum(*unknown20);
  _gfbbt::initArtsBlSpEnhance(*unknown20);
  _gfbbt::initArtsBlSpBtnType(*unknown20);
  _gfbbt::initArtsBlSpBtnChal1(*unknown20);
  _gfbbt::initArtsBlSpCamera1(*unknown20);
  _gfbbt::initArtsBlSpCamera2(*unknown20);
  _gfbbt::initArtsBlSpCamera3(*unknown20);
  _gfbbt::initArtsBlSpCameraCT1(*unknown20);
  _gfbbt::initArtsBlSpCameraCT2(*unknown20);
  _gfbbt::initArtsBlSpCameraEndf(*unknown20);
  _gfbbt::initArtsBlSpHitEff(*unknown20);
  _gfbbt::initGrowLevelExp(*unknown28);
  _gfbbt::initGrowEnemyExp(*unknown28);
  _gfbbt::initGrowEnemyWP(*unknown28);
  _gfbbt::initGrowEnemySP(*unknown28);
  _gfbbt::initGrowEnemyGold(*unknown28);
  _gfbbt::initGrowGoldDivide(*unknown28);
  _gfbbt::initLv_RevExpRevHigh(*unknown30);
  _gfbbt::initLv_RevExpRevLow(*unknown30);
  _gfbbt::initLv_RevDamageRevHigh(*unknown30);
  _gfbbt::initLv_RevDamageRevLow(*unknown30);
  _gfbbt::initWpn_EnRscR(*unknown38);
  _gfbbt::initWpn_EnRscL(*unknown38);
  _gfbbt::initWpn_EnTypeRange(*unknown38);
  _gfbbt::initWpn_EnDamage(*unknown38);
  _gfbbt::initWpn_EnStability(*unknown38);
  _gfbbt::initBTL_ClassName(*unknown40);
  _gfbbt::initBTL_ClassRole1(*unknown40);
  _gfbbt::initBTL_ClassRole2(*unknown40);
  _gfbbt::initBTL_ClassRole3(*unknown40);
  _gfbbt::initBTL_ClassDamageDown(*unknown40);
  _gfbbt::initBTL_ClassDamageUP(*unknown40);
  _gfbbt::initBTL_ClassHealUP(*unknown40);
  _gfbbt::initBTL_ClassAutoHate(*unknown40);
  _gfbbt::initBTL_ClassArtsHate(*unknown40);
  _gfbbt::initBTL_EnhanceEnhanceEffect(*unknown48);
  _gfbbt::initBTL_EnhanceParam1(*unknown48);
  _gfbbt::initBTL_EnhanceParam2(*unknown48);
  _gfbbt::initBTL_EnhanceCaption(*unknown48);
  _gfbbt::initBTL_EnhanceEffCategory(*unknown50);
  _gfbbt::initBTL_EnhanceEffIcon(*unknown50);
  _gfbbt::initBTL_EnhanceEffFlagCondition(*unknown50);
  _gfbbt::initBTL_EnhanceEffFlagUI(*unknown50);
  _gfbbt::initBTL_EnhanceEffParam(*unknown50);
  _gfbbt::initBTL_EnhanceEffName(*unknown50);
  _gfbbt::initBTL_EnhanceEffDirect(*unknown50);
  _gfbbt::initBTL_Skill_BlName(*unknown58);
  _gfbbt::initBTL_Skill_BlDebugName(*unknown58);
  _gfbbt::initBTL_Skill_BlEnhance1(*unknown58);
  _gfbbt::initBTL_Skill_BlEnhance2(*unknown58);
  _gfbbt::initBTL_Skill_BlEnhance3(*unknown58);
  _gfbbt::initBTL_Skill_BlEnhance4(*unknown58);
  _gfbbt::initBTL_Skill_BlEnhance5(*unknown58);
  _gfbbt::initBTL_Skill_BlFlagcommon(*unknown58);
  _gfbbt::initBTL_Skill_BlTank(*unknown58);
  _gfbbt::initBTL_Skill_BlAttacker(*unknown58);
  _gfbbt::initBTL_Skill_BlHealer(*unknown58);
  _gfbbt::initBTL_Skill_BlUI(*unknown58);
  _gfbbt::initBTL_Skill_DrName(*unknown60);
  _gfbbt::initBTL_Skill_DrDebugName(*unknown60);
  _gfbbt::initBTL_Skill_DrEnhance(*unknown60);
  _gfbbt::initBTL_Skill_DrUI(*unknown60);
  _gfbbt::initBTL_BuffName(*unknown68);
  _gfbbt::initBTL_BuffDebugName(*unknown68);
  _gfbbt::initBTL_BuffCaption(*unknown68);
  _gfbbt::initBTL_BuffBaseNum(*unknown68);
  _gfbbt::initBTL_BuffBaseTime(*unknown68);
  _gfbbt::initBTL_BuffBaseRecast(*unknown68);
  _gfbbt::initBTL_BuffBaseProb(*unknown68);
  _gfbbt::initBTL_BuffInterval(*unknown68);
  _gfbbt::initBTL_BuffEffect(*unknown68);
  _gfbbt::initBTL_BuffIcon(*unknown68);
  _gfbbt::initBTL_Bl_PersonalityFlagcommon(*unknown70);
  _gfbbt::initBTL_Bl_PersonalityKizunaBase(*unknown70);
  _gfbbt::initBTL_Bl_PersonalityVoiceID(*unknown70);
  _gfbbt::initBTL_Bl_KizunaLinkLinkNum(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkDeadNum(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkAppStNum(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkAppEndNum(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkAppCond(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkAppCondNum(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkReJudgef(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkSpActType(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkSpActNum(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkSpActf(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkStandDir(*unknown78);
  _gfbbt::initBTL_Bl_KizunaLinkSetKizunaLink1(*unknown80);
  _gfbbt::initBTL_Bl_KizunaLinkSetKizunaLink2(*unknown80);
  _gfbbt::initBTL_Bl_KizunaLinkSetLinkChType(*unknown80);
  _gfbbt::initBTL_Bl_KizunaLinkSetLinkChNum(*unknown80);
  _gfbbt::initBTL_Bl_KizunaLinkSetVoiceID(*unknown80);
  _gfbbt::initBTL_TestSettingDr1(*unknown88);
  _gfbbt::initBTL_TestSettingDr1Lv(*unknown88);
  _gfbbt::initBTL_TestSettingDr1Bl1(*unknown88);
  _gfbbt::initBTL_TestSettingDr1Bl2(*unknown88);
  _gfbbt::initBTL_TestSettingDr1Bl3(*unknown88);
  _gfbbt::initBTL_TestSettingDr2(*unknown88);
  _gfbbt::initBTL_TestSettingDr2Lv(*unknown88);
  _gfbbt::initBTL_TestSettingDr2Bl1(*unknown88);
  _gfbbt::initBTL_TestSettingDr2Bl2(*unknown88);
  _gfbbt::initBTL_TestSettingDr2Bl3(*unknown88);
  _gfbbt::initBTL_TestSettingDr3(*unknown88);
  _gfbbt::initBTL_TestSettingDr3Lv(*unknown88);
  _gfbbt::initBTL_TestSettingDr3Bl1(*unknown88);
  _gfbbt::initBTL_TestSettingDr3Bl2(*unknown88);
  _gfbbt::initBTL_TestSettingDr3Bl3(*unknown88);
  _gfbbt::initBTL_HanaBaseNCondNum(*unknown90);
  _gfbbt::initBTL_HanaBaseECondNum(*unknown90);
  _gfbbt::initBTL_HanaBaseNArtsNum(*unknown90);
  _gfbbt::initBTL_HanaBaseCircuit1Num(*unknown90);
  _gfbbt::initBTL_HanaBaseCircuit2Num(*unknown90);
  _gfbbt::initBTL_HanaBaseCircuit3Num(*unknown90);
  _gfbbt::initBTL_HanaBaseCircuit4Num(*unknown90);
  _gfbbt::initBTL_HanaBaseCircuit5Num(*unknown90);
  _gfbbt::initBTL_HanaBaseCircuit6Num(*unknown90);
  _gfbbt::initBTL_HanaBaseUI(*unknown90);
  _gfbbt::initBTL_HanaPowerPowerNum1(*unknown98);
  _gfbbt::initBTL_HanaPowerPowerNum2(*unknown98);
  _gfbbt::initBTL_HanaPowerPowerNum3(*unknown98);
  _gfbbt::initBTL_HanaPowerEtherNum1(*unknown98);
  _gfbbt::initBTL_HanaPowerEtherNum2(*unknown98);
  _gfbbt::initBTL_HanaPowerEtherNum3(*unknown98);
  _gfbbt::initBTL_HanaChipsetRoleParts(*unknowna0);
  _gfbbt::initBTL_HanaChipsetAtrParts(*unknowna0);
  _gfbbt::initBTL_HanaChipsetNArtsParts1(*unknowna0);
  _gfbbt::initBTL_HanaChipsetNArtsParts2(*unknowna0);
  _gfbbt::initBTL_HanaChipsetNArtsParts3(*unknowna0);
  _gfbbt::initBTL_HanaChipsetNCondParts1(*unknowna0);
  _gfbbt::initBTL_HanaChipsetNCondParts2(*unknowna0);
  _gfbbt::initBTL_HanaChipsetNCondParts3(*unknowna0);
  _gfbbt::initBTL_HanaChipsetUI(*unknowna0);
  _gfbbt::initWildcardDatavalueF4(*unknowna8);
  _gfbbt::initWildcardDatavalueU2(*unknowna8);
  _gfbbt::initVo_Field_FilterTargetFile(*unknownb0);
  _gfbbt::initVo_Field_FilterCondition(*unknownb0);
  _gfbbt::initVo_Field_FilterChangeFile(*unknownb0);
}

u32 GfBdatBtl::getArtsDrStart() const { return Bdat::getIdTop(unknown10->data); }

u32 GfBdatBtl::getArtsDrEnd() const { return Bdat::getIdTop(unknown10->data) + Bdat::getIdCount(unknown10->data); }

u32 GfBdatBtl::getArtsDrName(u32 id) const { return _gfbbt::getArtsDrName(*unknown10, id); }

const char *GfBdatBtl::getArtsDrDebugName(u32 id) const { return _gfbbt::getArtsDrDebugName(*unknown10, id); }

u32 GfBdatBtl::getArtsDrCaption(u32 id) const { return _gfbbt::getArtsDrCaption(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDriver(u32 id) const { return _gfbbt::getArtsDrDriver(*unknown10, id); }

u32 GfBdatBtl::getArtsDrWpnType(u32 id) const { return _gfbbt::getArtsDrWpnType(*unknown10, id); }

u32 GfBdatBtl::getArtsDrActNo(u32 id) const { return _gfbbt::getArtsDrActNo(*unknown10, id); }

u32 GfBdatBtl::getArtsDrArtsType(u32 id) const { return _gfbbt::getArtsDrArtsType(*unknown10, id); }

u32 GfBdatBtl::getArtsDrArtsBuff(u32 id) const { return _gfbbt::getArtsDrArtsBuff(*unknown10, id); }

u32 GfBdatBtl::getArtsDrAtrType(u32 id) const { return _gfbbt::getArtsDrAtrType(*unknown10, id); }

bool GfBdatBtl::isArtsDrFlagNormal(u32 id) const { return _gfbbt::isArtsDrFlagNormal(*unknown10, id); }

bool GfBdatBtl::isArtsDrFlagPierce(u32 id) const { return _gfbbt::isArtsDrFlagPierce(*unknown10, id); }

bool GfBdatBtl::isArtsDrFlagNoRepelled(u32 id) const { return _gfbbt::isArtsDrFlagNoRepelled(*unknown10, id); }

u32 GfBdatBtl::getArtsDrNextArts(u32 id) const { return _gfbbt::getArtsDrNextArts(*unknown10, id); }

u32 GfBdatBtl::getArtsDrTarget(u32 id) const { return _gfbbt::getArtsDrTarget(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDistance(u32 id) const { return _gfbbt::getArtsDrDistance(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRangeType(u32 id) const { return _gfbbt::getArtsDrRangeType(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRadius(u32 id) const { return _gfbbt::getArtsDrRadius(*unknown10, id); }

u32 GfBdatBtl::getArtsDrLength(u32 id) const { return _gfbbt::getArtsDrLength(*unknown10, id); }

s32 GfBdatBtl::getArtsDrHate(u32 id) const { return _gfbbt::getArtsDrHate(*unknown10, id); }

s32 GfBdatBtl::getArtsDrHitRevise(u32 id) const { return _gfbbt::getArtsDrHitRevise(*unknown10, id); }

s32 GfBdatBtl::getArtsDrCriRevise(u32 id) const { return _gfbbt::getArtsDrCriRevise(*unknown10, id); }

u32 GfBdatBtl::getArtsDrBulletID(u32 id) const { return _gfbbt::getArtsDrBulletID(*unknown10, id); }

u32 GfBdatBtl::getArtsDrBulletNum(u32 id) const { return _gfbbt::getArtsDrBulletNum(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm1(u32 id) const { return _gfbbt::getArtsDrHitFrm1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm2(u32 id) const { return _gfbbt::getArtsDrHitFrm2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm3(u32 id) const { return _gfbbt::getArtsDrHitFrm3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm4(u32 id) const { return _gfbbt::getArtsDrHitFrm4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm5(u32 id) const { return _gfbbt::getArtsDrHitFrm5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm6(u32 id) const { return _gfbbt::getArtsDrHitFrm6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm7(u32 id) const { return _gfbbt::getArtsDrHitFrm7(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm8(u32 id) const { return _gfbbt::getArtsDrHitFrm8(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm9(u32 id) const { return _gfbbt::getArtsDrHitFrm9(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm10(u32 id) const { return _gfbbt::getArtsDrHitFrm10(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm11(u32 id) const { return _gfbbt::getArtsDrHitFrm11(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm12(u32 id) const { return _gfbbt::getArtsDrHitFrm12(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm13(u32 id) const { return _gfbbt::getArtsDrHitFrm13(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm14(u32 id) const { return _gfbbt::getArtsDrHitFrm14(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm15(u32 id) const { return _gfbbt::getArtsDrHitFrm15(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm16(u32 id) const { return _gfbbt::getArtsDrHitFrm16(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp1(u32 id) const { return _gfbbt::getArtsDrEfp1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp2(u32 id) const { return _gfbbt::getArtsDrEfp2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp3(u32 id) const { return _gfbbt::getArtsDrEfp3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp4(u32 id) const { return _gfbbt::getArtsDrEfp4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp5(u32 id) const { return _gfbbt::getArtsDrEfp5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp6(u32 id) const { return _gfbbt::getArtsDrEfp6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp7(u32 id) const { return _gfbbt::getArtsDrEfp7(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp8(u32 id) const { return _gfbbt::getArtsDrEfp8(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp9(u32 id) const { return _gfbbt::getArtsDrEfp9(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp10(u32 id) const { return _gfbbt::getArtsDrEfp10(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp11(u32 id) const { return _gfbbt::getArtsDrEfp11(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp12(u32 id) const { return _gfbbt::getArtsDrEfp12(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp13(u32 id) const { return _gfbbt::getArtsDrEfp13(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp14(u32 id) const { return _gfbbt::getArtsDrEfp14(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp15(u32 id) const { return _gfbbt::getArtsDrEfp15(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEfp16(u32 id) const { return _gfbbt::getArtsDrEfp16(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID1(u32 id) const { return _gfbbt::getArtsDrHitDirID1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID2(u32 id) const { return _gfbbt::getArtsDrHitDirID2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID3(u32 id) const { return _gfbbt::getArtsDrHitDirID3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID4(u32 id) const { return _gfbbt::getArtsDrHitDirID4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID5(u32 id) const { return _gfbbt::getArtsDrHitDirID5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID6(u32 id) const { return _gfbbt::getArtsDrHitDirID6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID7(u32 id) const { return _gfbbt::getArtsDrHitDirID7(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID8(u32 id) const { return _gfbbt::getArtsDrHitDirID8(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID9(u32 id) const { return _gfbbt::getArtsDrHitDirID9(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID10(u32 id) const { return _gfbbt::getArtsDrHitDirID10(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID11(u32 id) const { return _gfbbt::getArtsDrHitDirID11(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID12(u32 id) const { return _gfbbt::getArtsDrHitDirID12(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID13(u32 id) const { return _gfbbt::getArtsDrHitDirID13(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID14(u32 id) const { return _gfbbt::getArtsDrHitDirID14(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID15(u32 id) const { return _gfbbt::getArtsDrHitDirID15(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitDirID16(u32 id) const { return _gfbbt::getArtsDrHitDirID16(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt1(u32 id) const { return _gfbbt::getArtsDrDmgRt1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt2(u32 id) const { return _gfbbt::getArtsDrDmgRt2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt3(u32 id) const { return _gfbbt::getArtsDrDmgRt3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt4(u32 id) const { return _gfbbt::getArtsDrDmgRt4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt5(u32 id) const { return _gfbbt::getArtsDrDmgRt5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt6(u32 id) const { return _gfbbt::getArtsDrDmgRt6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt7(u32 id) const { return _gfbbt::getArtsDrDmgRt7(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt8(u32 id) const { return _gfbbt::getArtsDrDmgRt8(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt9(u32 id) const { return _gfbbt::getArtsDrDmgRt9(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt10(u32 id) const { return _gfbbt::getArtsDrDmgRt10(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt11(u32 id) const { return _gfbbt::getArtsDrDmgRt11(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt12(u32 id) const { return _gfbbt::getArtsDrDmgRt12(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt13(u32 id) const { return _gfbbt::getArtsDrDmgRt13(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt14(u32 id) const { return _gfbbt::getArtsDrDmgRt14(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt15(u32 id) const { return _gfbbt::getArtsDrDmgRt15(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgRt16(u32 id) const { return _gfbbt::getArtsDrDmgRt16(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct1(u32 id) const { return _gfbbt::getArtsDrReAct1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct2(u32 id) const { return _gfbbt::getArtsDrReAct2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct3(u32 id) const { return _gfbbt::getArtsDrReAct3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct4(u32 id) const { return _gfbbt::getArtsDrReAct4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct5(u32 id) const { return _gfbbt::getArtsDrReAct5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct6(u32 id) const { return _gfbbt::getArtsDrReAct6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct7(u32 id) const { return _gfbbt::getArtsDrReAct7(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct8(u32 id) const { return _gfbbt::getArtsDrReAct8(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct9(u32 id) const { return _gfbbt::getArtsDrReAct9(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct10(u32 id) const { return _gfbbt::getArtsDrReAct10(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct11(u32 id) const { return _gfbbt::getArtsDrReAct11(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct12(u32 id) const { return _gfbbt::getArtsDrReAct12(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct13(u32 id) const { return _gfbbt::getArtsDrReAct13(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct14(u32 id) const { return _gfbbt::getArtsDrReAct14(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct15(u32 id) const { return _gfbbt::getArtsDrReAct15(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReAct16(u32 id) const { return _gfbbt::getArtsDrReAct16(*unknown10, id); }

u32 GfBdatBtl::getArtsDrMoveCancelFrm(u32 id) const { return _gfbbt::getArtsDrMoveCancelFrm(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgMgn1(u32 id) const { return _gfbbt::getArtsDrDmgMgn1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgMgn2(u32 id) const { return _gfbbt::getArtsDrDmgMgn2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgMgn3(u32 id) const { return _gfbbt::getArtsDrDmgMgn3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgMgn4(u32 id) const { return _gfbbt::getArtsDrDmgMgn4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgMgn5(u32 id) const { return _gfbbt::getArtsDrDmgMgn5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrDmgMgn6(u32 id) const { return _gfbbt::getArtsDrDmgMgn6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRecast1(u32 id) const { return _gfbbt::getArtsDrRecast1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRecast2(u32 id) const { return _gfbbt::getArtsDrRecast2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRecast3(u32 id) const { return _gfbbt::getArtsDrRecast3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRecast4(u32 id) const { return _gfbbt::getArtsDrRecast4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRecast5(u32 id) const { return _gfbbt::getArtsDrRecast5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrRecast6(u32 id) const { return _gfbbt::getArtsDrRecast6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrAtrNum(u32 id) const { return _gfbbt::getArtsDrAtrNum(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEnhance1(u32 id) const { return _gfbbt::getArtsDrEnhance1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEnhance2(u32 id) const { return _gfbbt::getArtsDrEnhance2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEnhance3(u32 id) const { return _gfbbt::getArtsDrEnhance3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEnhance4(u32 id) const { return _gfbbt::getArtsDrEnhance4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEnhance5(u32 id) const { return _gfbbt::getArtsDrEnhance5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrEnhance6(u32 id) const { return _gfbbt::getArtsDrEnhance6(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReleaseLv1(u32 id) const { return _gfbbt::getArtsDrReleaseLv1(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReleaseLv2(u32 id) const { return _gfbbt::getArtsDrReleaseLv2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReleaseLv3(u32 id) const { return _gfbbt::getArtsDrReleaseLv3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReleaseLv4(u32 id) const { return _gfbbt::getArtsDrReleaseLv4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrReleaseLv5(u32 id) const { return _gfbbt::getArtsDrReleaseLv5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrNeedWP2(u32 id) const { return _gfbbt::getArtsDrNeedWP2(*unknown10, id); }

u32 GfBdatBtl::getArtsDrNeedWP3(u32 id) const { return _gfbbt::getArtsDrNeedWP3(*unknown10, id); }

u32 GfBdatBtl::getArtsDrNeedWP4(u32 id) const { return _gfbbt::getArtsDrNeedWP4(*unknown10, id); }

u32 GfBdatBtl::getArtsDrNeedWP5(u32 id) const { return _gfbbt::getArtsDrNeedWP5(*unknown10, id); }

u32 GfBdatBtl::getArtsDrUI(u32 id) const { return _gfbbt::getArtsDrUI(*unknown10, id); }

u32 GfBdatBtl::getArtsDrPriority(u32 id) const { return _gfbbt::getArtsDrPriority(*unknown10, id); }

u32 GfBdatBtl::getArtsDrHitFrm(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrHitFrm1,
                                                              _gfbbt::getArtsDrHitFrm2,
                                                              _gfbbt::getArtsDrHitFrm3,
                                                              _gfbbt::getArtsDrHitFrm4,
                                                              _gfbbt::getArtsDrHitFrm5,
                                                              _gfbbt::getArtsDrHitFrm6,
                                                              _gfbbt::getArtsDrHitFrm7,
                                                              _gfbbt::getArtsDrHitFrm8,
                                                              _gfbbt::getArtsDrHitFrm9,
                                                              _gfbbt::getArtsDrHitFrm10,
                                                              _gfbbt::getArtsDrHitFrm11,
                                                              _gfbbt::getArtsDrHitFrm12,
                                                              _gfbbt::getArtsDrHitFrm13,
                                                              _gfbbt::getArtsDrHitFrm14,
                                                              _gfbbt::getArtsDrHitFrm15,
                                                              _gfbbt::getArtsDrHitFrm16};
  return getters[index](*unknown10, id);
}

u32 GfBdatBtl::getArtsDrEfp(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrEfp1,
                                                              _gfbbt::getArtsDrEfp2,
                                                              _gfbbt::getArtsDrEfp3,
                                                              _gfbbt::getArtsDrEfp4,
                                                              _gfbbt::getArtsDrEfp5,
                                                              _gfbbt::getArtsDrEfp6,
                                                              _gfbbt::getArtsDrEfp7,
                                                              _gfbbt::getArtsDrEfp8,
                                                              _gfbbt::getArtsDrEfp9,
                                                              _gfbbt::getArtsDrEfp10,
                                                              _gfbbt::getArtsDrEfp11,
                                                              _gfbbt::getArtsDrEfp12,
                                                              _gfbbt::getArtsDrEfp13,
                                                              _gfbbt::getArtsDrEfp14,
                                                              _gfbbt::getArtsDrEfp15,
                                                              _gfbbt::getArtsDrEfp16};
  return getters[index](*unknown10, id);
}

u32 GfBdatBtl::getArtsDrHitDirID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrHitDirID1,
                                                              _gfbbt::getArtsDrHitDirID2,
                                                              _gfbbt::getArtsDrHitDirID3,
                                                              _gfbbt::getArtsDrHitDirID4,
                                                              _gfbbt::getArtsDrHitDirID5,
                                                              _gfbbt::getArtsDrHitDirID6,
                                                              _gfbbt::getArtsDrHitDirID7,
                                                              _gfbbt::getArtsDrHitDirID8,
                                                              _gfbbt::getArtsDrHitDirID9,
                                                              _gfbbt::getArtsDrHitDirID10,
                                                              _gfbbt::getArtsDrHitDirID11,
                                                              _gfbbt::getArtsDrHitDirID12,
                                                              _gfbbt::getArtsDrHitDirID13,
                                                              _gfbbt::getArtsDrHitDirID14,
                                                              _gfbbt::getArtsDrHitDirID15,
                                                              _gfbbt::getArtsDrHitDirID16};
  return getters[index](*unknown10, id);
}

u32 GfBdatBtl::getArtsDrDmgRt(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrDmgRt1,
                                                              _gfbbt::getArtsDrDmgRt2,
                                                              _gfbbt::getArtsDrDmgRt3,
                                                              _gfbbt::getArtsDrDmgRt4,
                                                              _gfbbt::getArtsDrDmgRt5,
                                                              _gfbbt::getArtsDrDmgRt6,
                                                              _gfbbt::getArtsDrDmgRt7,
                                                              _gfbbt::getArtsDrDmgRt8,
                                                              _gfbbt::getArtsDrDmgRt9,
                                                              _gfbbt::getArtsDrDmgRt10,
                                                              _gfbbt::getArtsDrDmgRt11,
                                                              _gfbbt::getArtsDrDmgRt12,
                                                              _gfbbt::getArtsDrDmgRt13,
                                                              _gfbbt::getArtsDrDmgRt14,
                                                              _gfbbt::getArtsDrDmgRt15,
                                                              _gfbbt::getArtsDrDmgRt16};
  return getters[index](*unknown10, id);
}

u32 GfBdatBtl::getArtsDrReAct(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrReAct1,
                                                              _gfbbt::getArtsDrReAct2,
                                                              _gfbbt::getArtsDrReAct3,
                                                              _gfbbt::getArtsDrReAct4,
                                                              _gfbbt::getArtsDrReAct5,
                                                              _gfbbt::getArtsDrReAct6,
                                                              _gfbbt::getArtsDrReAct7,
                                                              _gfbbt::getArtsDrReAct8,
                                                              _gfbbt::getArtsDrReAct9,
                                                              _gfbbt::getArtsDrReAct10,
                                                              _gfbbt::getArtsDrReAct11,
                                                              _gfbbt::getArtsDrReAct12,
                                                              _gfbbt::getArtsDrReAct13,
                                                              _gfbbt::getArtsDrReAct14,
                                                              _gfbbt::getArtsDrReAct15,
                                                              _gfbbt::getArtsDrReAct16};
  return getters[level](*unknown10, arts);
}

u32 GfBdatBtl::getArtsDrDmgMgn(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrDmgMgn1,
                                                              _gfbbt::getArtsDrDmgMgn2,
                                                              _gfbbt::getArtsDrDmgMgn3,
                                                              _gfbbt::getArtsDrDmgMgn4,
                                                              _gfbbt::getArtsDrDmgMgn5,
                                                              _gfbbt::getArtsDrDmgMgn6};
  return getters[level](*unknown10, arts);
}

u32 GfBdatBtl::getArtsDrRecast(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrRecast1,
                                                              _gfbbt::getArtsDrRecast2,
                                                              _gfbbt::getArtsDrRecast3,
                                                              _gfbbt::getArtsDrRecast4,
                                                              _gfbbt::getArtsDrRecast5,
                                                              _gfbbt::getArtsDrRecast6};
  return getters[level](*unknown10, arts);
}

u32 GfBdatBtl::getArtsDrEnhance(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrEnhance1,
                                                              _gfbbt::getArtsDrEnhance2,
                                                              _gfbbt::getArtsDrEnhance3,
                                                              _gfbbt::getArtsDrEnhance4,
                                                              _gfbbt::getArtsDrEnhance5,
                                                              _gfbbt::getArtsDrEnhance6};
  return getters[level](*unknown10, arts);
}

u32 GfBdatBtl::getArtsDrReleaseLv(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrReleaseLv1,
                                                              _gfbbt::getArtsDrReleaseLv1,
                                                              _gfbbt::getArtsDrReleaseLv2,
                                                              _gfbbt::getArtsDrReleaseLv3,
                                                              _gfbbt::getArtsDrReleaseLv4,
                                                              _gfbbt::getArtsDrReleaseLv5};
  return getters[level](*unknown10, arts);
}

u32 GfBdatBtl::getArtsDrNeedWP(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsDrNeedWP2,
                                                              _gfbbt::getArtsDrNeedWP2,
                                                              _gfbbt::getArtsDrNeedWP2,
                                                              _gfbbt::getArtsDrNeedWP3,
                                                              _gfbbt::getArtsDrNeedWP4,
                                                              _gfbbt::getArtsDrNeedWP5};
  return getters[level](*unknown10, arts);
}

u32 GfBdatBtl::getArtsBlStart() const { return Bdat::getIdTop(unknown18->data); }

u32 GfBdatBtl::getArtsBlEnd() const { return Bdat::getIdTop(unknown18->data) + Bdat::getIdCount(unknown18->data); }

u32 GfBdatBtl::getArtsBlName(u32 id) const { return _gfbbt::getArtsBlName(*unknown18, id); }

const char *GfBdatBtl::getArtsBlDebugName(u32 id) const { return _gfbbt::getArtsBlDebugName(*unknown18, id); }

u32 GfBdatBtl::getArtsBlCaption(u32 id) const { return _gfbbt::getArtsBlCaption(*unknown18, id); }

u32 GfBdatBtl::getArtsBlWpnType(u32 id) const { return _gfbbt::getArtsBlWpnType(*unknown18, id); }

u32 GfBdatBtl::getArtsBlCmnBlType(u32 id) const { return _gfbbt::getArtsBlCmnBlType(*unknown18, id); }

u32 GfBdatBtl::getArtsBlSpLv(u32 id) const { return _gfbbt::getArtsBlSpLv(*unknown18, id); }

u32 GfBdatBtl::getArtsBlActNo(u32 id) const { return _gfbbt::getArtsBlActNo(*unknown18, id); }

u32 GfBdatBtl::getArtsBlArtsType(u32 id) const { return _gfbbt::getArtsBlArtsType(*unknown18, id); }

u32 GfBdatBtl::getArtsBlArtsBuff(u32 id) const { return _gfbbt::getArtsBlArtsBuff(*unknown18, id); }

bool GfBdatBtl::isArtsBlFlagcommon(u32 id) const { return _gfbbt::isArtsBlFlagcommon(*unknown18, id); }

bool GfBdatBtl::isArtsBlFlagPierce(u32 id) const { return _gfbbt::isArtsBlFlagPierce(*unknown18, id); }

u32 GfBdatBtl::getArtsBlTarget(u32 id) const { return _gfbbt::getArtsBlTarget(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDistance(u32 id) const { return _gfbbt::getArtsBlDistance(*unknown18, id); }

u32 GfBdatBtl::getArtsBlRangeType(u32 id) const { return _gfbbt::getArtsBlRangeType(*unknown18, id); }

u32 GfBdatBtl::getArtsBlRadius(u32 id) const { return _gfbbt::getArtsBlRadius(*unknown18, id); }

u32 GfBdatBtl::getArtsBlLength(u32 id) const { return _gfbbt::getArtsBlLength(*unknown18, id); }

u32 GfBdatBtl::getArtsBlAtr(u32 id) const { return _gfbbt::getArtsBlAtr(*unknown18, id); }

s32 GfBdatBtl::getArtsBlHate(u32 id) const { return _gfbbt::getArtsBlHate(*unknown18, id); }

s32 GfBdatBtl::getArtsBlHitRevise(u32 id) const { return _gfbbt::getArtsBlHitRevise(*unknown18, id); }

s32 GfBdatBtl::getArtsBlCriRevise(u32 id) const { return _gfbbt::getArtsBlCriRevise(*unknown18, id); }

u32 GfBdatBtl::getArtsBlBulletID(u32 id) const { return _gfbbt::getArtsBlBulletID(*unknown18, id); }

u32 GfBdatBtl::getArtsBlBulletNum(u32 id) const { return _gfbbt::getArtsBlBulletNum(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm1(u32 id) const { return _gfbbt::getArtsBlHitFrm1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm2(u32 id) const { return _gfbbt::getArtsBlHitFrm2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm3(u32 id) const { return _gfbbt::getArtsBlHitFrm3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm4(u32 id) const { return _gfbbt::getArtsBlHitFrm4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm5(u32 id) const { return _gfbbt::getArtsBlHitFrm5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm6(u32 id) const { return _gfbbt::getArtsBlHitFrm6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm7(u32 id) const { return _gfbbt::getArtsBlHitFrm7(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm8(u32 id) const { return _gfbbt::getArtsBlHitFrm8(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm9(u32 id) const { return _gfbbt::getArtsBlHitFrm9(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm10(u32 id) const { return _gfbbt::getArtsBlHitFrm10(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm11(u32 id) const { return _gfbbt::getArtsBlHitFrm11(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm12(u32 id) const { return _gfbbt::getArtsBlHitFrm12(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm13(u32 id) const { return _gfbbt::getArtsBlHitFrm13(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm14(u32 id) const { return _gfbbt::getArtsBlHitFrm14(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm15(u32 id) const { return _gfbbt::getArtsBlHitFrm15(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm16(u32 id) const { return _gfbbt::getArtsBlHitFrm16(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp1(u32 id) const { return _gfbbt::getArtsBlEfp1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp2(u32 id) const { return _gfbbt::getArtsBlEfp2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp3(u32 id) const { return _gfbbt::getArtsBlEfp3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp4(u32 id) const { return _gfbbt::getArtsBlEfp4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp5(u32 id) const { return _gfbbt::getArtsBlEfp5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp6(u32 id) const { return _gfbbt::getArtsBlEfp6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp7(u32 id) const { return _gfbbt::getArtsBlEfp7(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp8(u32 id) const { return _gfbbt::getArtsBlEfp8(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp9(u32 id) const { return _gfbbt::getArtsBlEfp9(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp10(u32 id) const { return _gfbbt::getArtsBlEfp10(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp11(u32 id) const { return _gfbbt::getArtsBlEfp11(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp12(u32 id) const { return _gfbbt::getArtsBlEfp12(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp13(u32 id) const { return _gfbbt::getArtsBlEfp13(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp14(u32 id) const { return _gfbbt::getArtsBlEfp14(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp15(u32 id) const { return _gfbbt::getArtsBlEfp15(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEfp16(u32 id) const { return _gfbbt::getArtsBlEfp16(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID1(u32 id) const { return _gfbbt::getArtsBlHitDirID1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID2(u32 id) const { return _gfbbt::getArtsBlHitDirID2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID3(u32 id) const { return _gfbbt::getArtsBlHitDirID3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID4(u32 id) const { return _gfbbt::getArtsBlHitDirID4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID5(u32 id) const { return _gfbbt::getArtsBlHitDirID5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID6(u32 id) const { return _gfbbt::getArtsBlHitDirID6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID7(u32 id) const { return _gfbbt::getArtsBlHitDirID7(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID8(u32 id) const { return _gfbbt::getArtsBlHitDirID8(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID9(u32 id) const { return _gfbbt::getArtsBlHitDirID9(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID10(u32 id) const { return _gfbbt::getArtsBlHitDirID10(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID11(u32 id) const { return _gfbbt::getArtsBlHitDirID11(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID12(u32 id) const { return _gfbbt::getArtsBlHitDirID12(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID13(u32 id) const { return _gfbbt::getArtsBlHitDirID13(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID14(u32 id) const { return _gfbbt::getArtsBlHitDirID14(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID15(u32 id) const { return _gfbbt::getArtsBlHitDirID15(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitDirID16(u32 id) const { return _gfbbt::getArtsBlHitDirID16(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt1(u32 id) const { return _gfbbt::getArtsBlDmgRt1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt2(u32 id) const { return _gfbbt::getArtsBlDmgRt2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt3(u32 id) const { return _gfbbt::getArtsBlDmgRt3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt4(u32 id) const { return _gfbbt::getArtsBlDmgRt4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt5(u32 id) const { return _gfbbt::getArtsBlDmgRt5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt6(u32 id) const { return _gfbbt::getArtsBlDmgRt6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt7(u32 id) const { return _gfbbt::getArtsBlDmgRt7(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt8(u32 id) const { return _gfbbt::getArtsBlDmgRt8(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt9(u32 id) const { return _gfbbt::getArtsBlDmgRt9(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt10(u32 id) const { return _gfbbt::getArtsBlDmgRt10(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt11(u32 id) const { return _gfbbt::getArtsBlDmgRt11(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt12(u32 id) const { return _gfbbt::getArtsBlDmgRt12(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt13(u32 id) const { return _gfbbt::getArtsBlDmgRt13(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt14(u32 id) const { return _gfbbt::getArtsBlDmgRt14(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt15(u32 id) const { return _gfbbt::getArtsBlDmgRt15(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgRt16(u32 id) const { return _gfbbt::getArtsBlDmgRt16(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct1(u32 id) const { return _gfbbt::getArtsBlReAct1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct2(u32 id) const { return _gfbbt::getArtsBlReAct2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct3(u32 id) const { return _gfbbt::getArtsBlReAct3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct4(u32 id) const { return _gfbbt::getArtsBlReAct4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct5(u32 id) const { return _gfbbt::getArtsBlReAct5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct6(u32 id) const { return _gfbbt::getArtsBlReAct6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct7(u32 id) const { return _gfbbt::getArtsBlReAct7(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct8(u32 id) const { return _gfbbt::getArtsBlReAct8(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct9(u32 id) const { return _gfbbt::getArtsBlReAct9(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct10(u32 id) const { return _gfbbt::getArtsBlReAct10(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct11(u32 id) const { return _gfbbt::getArtsBlReAct11(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct12(u32 id) const { return _gfbbt::getArtsBlReAct12(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct13(u32 id) const { return _gfbbt::getArtsBlReAct13(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct14(u32 id) const { return _gfbbt::getArtsBlReAct14(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct15(u32 id) const { return _gfbbt::getArtsBlReAct15(*unknown18, id); }

u32 GfBdatBtl::getArtsBlReAct16(u32 id) const { return _gfbbt::getArtsBlReAct16(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgMgn1(u32 id) const { return _gfbbt::getArtsBlDmgMgn1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgMgn2(u32 id) const { return _gfbbt::getArtsBlDmgMgn2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgMgn3(u32 id) const { return _gfbbt::getArtsBlDmgMgn3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgMgn4(u32 id) const { return _gfbbt::getArtsBlDmgMgn4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgMgn5(u32 id) const { return _gfbbt::getArtsBlDmgMgn5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlDmgMgn6(u32 id) const { return _gfbbt::getArtsBlDmgMgn6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlAtrNum(u32 id) const { return _gfbbt::getArtsBlAtrNum(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEnhance1(u32 id) const { return _gfbbt::getArtsBlEnhance1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEnhance2(u32 id) const { return _gfbbt::getArtsBlEnhance2(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEnhance3(u32 id) const { return _gfbbt::getArtsBlEnhance3(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEnhance4(u32 id) const { return _gfbbt::getArtsBlEnhance4(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEnhance5(u32 id) const { return _gfbbt::getArtsBlEnhance5(*unknown18, id); }

u32 GfBdatBtl::getArtsBlEnhance6(u32 id) const { return _gfbbt::getArtsBlEnhance6(*unknown18, id); }

u32 GfBdatBtl::getArtsBlBtnType(u32 id) const { return _gfbbt::getArtsBlBtnType(*unknown18, id); }

u32 GfBdatBtl::getArtsBlBtnChal1(u32 id) const { return _gfbbt::getArtsBlBtnChal1(*unknown18, id); }

u32 GfBdatBtl::getArtsBlUI(u32 id) const { return _gfbbt::getArtsBlUI(*unknown18, id); }

u32 GfBdatBtl::getArtsBlHitFrm(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlHitFrm1,
                                                              _gfbbt::getArtsBlHitFrm2,
                                                              _gfbbt::getArtsBlHitFrm3,
                                                              _gfbbt::getArtsBlHitFrm4,
                                                              _gfbbt::getArtsBlHitFrm5,
                                                              _gfbbt::getArtsBlHitFrm6,
                                                              _gfbbt::getArtsBlHitFrm7,
                                                              _gfbbt::getArtsBlHitFrm8,
                                                              _gfbbt::getArtsBlHitFrm9,
                                                              _gfbbt::getArtsBlHitFrm10,
                                                              _gfbbt::getArtsBlHitFrm11,
                                                              _gfbbt::getArtsBlHitFrm12,
                                                              _gfbbt::getArtsBlHitFrm13,
                                                              _gfbbt::getArtsBlHitFrm14,
                                                              _gfbbt::getArtsBlHitFrm15,
                                                              _gfbbt::getArtsBlHitFrm16};
  return getters[index](*unknown18, id);
}

u32 GfBdatBtl::getArtsBlEfp(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlEfp1,
                                                              _gfbbt::getArtsBlEfp2,
                                                              _gfbbt::getArtsBlEfp3,
                                                              _gfbbt::getArtsBlEfp4,
                                                              _gfbbt::getArtsBlEfp5,
                                                              _gfbbt::getArtsBlEfp6,
                                                              _gfbbt::getArtsBlEfp7,
                                                              _gfbbt::getArtsBlEfp8,
                                                              _gfbbt::getArtsBlEfp9,
                                                              _gfbbt::getArtsBlEfp10,
                                                              _gfbbt::getArtsBlEfp11,
                                                              _gfbbt::getArtsBlEfp12,
                                                              _gfbbt::getArtsBlEfp13,
                                                              _gfbbt::getArtsBlEfp14,
                                                              _gfbbt::getArtsBlEfp15,
                                                              _gfbbt::getArtsBlEfp16};
  return getters[index](*unknown18, id);
}

u32 GfBdatBtl::getArtsBlHitDirID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlHitDirID1,
                                                              _gfbbt::getArtsBlHitDirID2,
                                                              _gfbbt::getArtsBlHitDirID3,
                                                              _gfbbt::getArtsBlHitDirID4,
                                                              _gfbbt::getArtsBlHitDirID5,
                                                              _gfbbt::getArtsBlHitDirID6,
                                                              _gfbbt::getArtsBlHitDirID7,
                                                              _gfbbt::getArtsBlHitDirID8,
                                                              _gfbbt::getArtsBlHitDirID9,
                                                              _gfbbt::getArtsBlHitDirID10,
                                                              _gfbbt::getArtsBlHitDirID11,
                                                              _gfbbt::getArtsBlHitDirID12,
                                                              _gfbbt::getArtsBlHitDirID13,
                                                              _gfbbt::getArtsBlHitDirID14,
                                                              _gfbbt::getArtsBlHitDirID15,
                                                              _gfbbt::getArtsBlHitDirID16};
  return getters[index](*unknown18, id);
}

u32 GfBdatBtl::getArtsBlDmgRt(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlDmgRt1,
                                                              _gfbbt::getArtsBlDmgRt2,
                                                              _gfbbt::getArtsBlDmgRt3,
                                                              _gfbbt::getArtsBlDmgRt4,
                                                              _gfbbt::getArtsBlDmgRt5,
                                                              _gfbbt::getArtsBlDmgRt6,
                                                              _gfbbt::getArtsBlDmgRt7,
                                                              _gfbbt::getArtsBlDmgRt8,
                                                              _gfbbt::getArtsBlDmgRt9,
                                                              _gfbbt::getArtsBlDmgRt10,
                                                              _gfbbt::getArtsBlDmgRt11,
                                                              _gfbbt::getArtsBlDmgRt12,
                                                              _gfbbt::getArtsBlDmgRt13,
                                                              _gfbbt::getArtsBlDmgRt14,
                                                              _gfbbt::getArtsBlDmgRt15,
                                                              _gfbbt::getArtsBlDmgRt16};
  return getters[index](*unknown18, id);
}

u32 GfBdatBtl::getArtsBlReAct(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlReAct1,
                                                              _gfbbt::getArtsBlReAct2,
                                                              _gfbbt::getArtsBlReAct3,
                                                              _gfbbt::getArtsBlReAct4,
                                                              _gfbbt::getArtsBlReAct5,
                                                              _gfbbt::getArtsBlReAct6,
                                                              _gfbbt::getArtsBlReAct7,
                                                              _gfbbt::getArtsBlReAct8,
                                                              _gfbbt::getArtsBlReAct9,
                                                              _gfbbt::getArtsBlReAct10,
                                                              _gfbbt::getArtsBlReAct11,
                                                              _gfbbt::getArtsBlReAct12,
                                                              _gfbbt::getArtsBlReAct13,
                                                              _gfbbt::getArtsBlReAct14,
                                                              _gfbbt::getArtsBlReAct15,
                                                              _gfbbt::getArtsBlReAct16};
  return getters[index](*unknown18, id);
}

u32 GfBdatBtl::getArtsBlDmgMgn(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlDmgMgn1,
                                                              _gfbbt::getArtsBlDmgMgn2,
                                                              _gfbbt::getArtsBlDmgMgn3,
                                                              _gfbbt::getArtsBlDmgMgn4,
                                                              _gfbbt::getArtsBlDmgMgn5,
                                                              _gfbbt::getArtsBlDmgMgn6};
  return getters[index](*unknown18, id);
}

u32 GfBdatBtl::getArtsBlEnhance(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlEnhance1,
                                                              _gfbbt::getArtsBlEnhance2,
                                                              _gfbbt::getArtsBlEnhance3,
                                                              _gfbbt::getArtsBlEnhance4,
                                                              _gfbbt::getArtsBlEnhance5,
                                                              _gfbbt::getArtsBlEnhance6};
  return getters[level](*unknown18, arts);
}

u32 GfBdatBtl::getArtsBlSpStart() const { return Bdat::getIdTop(unknown20->data); }

u32 GfBdatBtl::getArtsBlSpEnd() const { return Bdat::getIdTop(unknown20->data) + Bdat::getIdCount(unknown20->data); }

u32 GfBdatBtl::getArtsBlSpName(u32 id) const { return _gfbbt::getArtsBlSpName(*unknown20, id); }

const char *GfBdatBtl::getArtsBlSpDebugName(u32 id) const { return _gfbbt::getArtsBlSpDebugName(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpCaption(u32 id) const { return _gfbbt::getArtsBlSpCaption(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpWpnType(u32 id) const { return _gfbbt::getArtsBlSpWpnType(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpCmnBlType(u32 id) const { return _gfbbt::getArtsBlSpCmnBlType(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpActNoDr(u32 id) const { return _gfbbt::getArtsBlSpActNoDr(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpActNoBl(u32 id) const { return _gfbbt::getArtsBlSpActNoBl(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpActNoBl2(u32 id) const { return _gfbbt::getArtsBlSpActNoBl2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpBuddyDr(u32 id) const { return _gfbbt::getArtsBlSpBuddyDr(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpAddBl(u32 id) const { return _gfbbt::getArtsBlSpAddBl(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpActType(u32 id) const { return _gfbbt::getArtsBlSpActType(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpPC01(u32 id) const { return _gfbbt::getArtsBlSpPC01(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpPC02(u32 id) const { return _gfbbt::getArtsBlSpPC02(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpPC03(u32 id) const { return _gfbbt::getArtsBlSpPC03(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpPC06(u32 id) const { return _gfbbt::getArtsBlSpPC06(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpArtsType(u32 id) const { return _gfbbt::getArtsBlSpArtsType(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpArtsBuff(u32 id) const { return _gfbbt::getArtsBlSpArtsBuff(*unknown20, id); }

bool GfBdatBtl::isArtsBlSpFlagPierce(u32 id) const { return _gfbbt::isArtsBlSpFlagPierce(*unknown20, id); }

bool GfBdatBtl::isArtsBlSpFlagNoMove(u32 id) const { return _gfbbt::isArtsBlSpFlagNoMove(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpTarget(u32 id) const { return _gfbbt::getArtsBlSpTarget(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDistance(u32 id) const { return _gfbbt::getArtsBlSpDistance(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpRangeType(u32 id) const { return _gfbbt::getArtsBlSpRangeType(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpRadius(u32 id) const { return _gfbbt::getArtsBlSpRadius(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpLength(u32 id) const { return _gfbbt::getArtsBlSpLength(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpAtr(u32 id) const { return _gfbbt::getArtsBlSpAtr(*unknown20, id); }

s32 GfBdatBtl::getArtsBlSpHate(u32 id) const { return _gfbbt::getArtsBlSpHate(*unknown20, id); }

s32 GfBdatBtl::getArtsBlSpHitRevise(u32 id) const { return _gfbbt::getArtsBlSpHitRevise(*unknown20, id); }

s32 GfBdatBtl::getArtsBlSpCriRevise(u32 id) const { return _gfbbt::getArtsBlSpCriRevise(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpBulletID(u32 id) const { return _gfbbt::getArtsBlSpBulletID(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpBulletEffID(u32 id) const { return _gfbbt::getArtsBlSpBulletEffID(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpBulletNum(u32 id) const { return _gfbbt::getArtsBlSpBulletNum(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm1(u32 id) const { return _gfbbt::getArtsBlSpHitFrm1(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm2(u32 id) const { return _gfbbt::getArtsBlSpHitFrm2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm3(u32 id) const { return _gfbbt::getArtsBlSpHitFrm3(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm4(u32 id) const { return _gfbbt::getArtsBlSpHitFrm4(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm5(u32 id) const { return _gfbbt::getArtsBlSpHitFrm5(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm6(u32 id) const { return _gfbbt::getArtsBlSpHitFrm6(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm7(u32 id) const { return _gfbbt::getArtsBlSpHitFrm7(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm8(u32 id) const { return _gfbbt::getArtsBlSpHitFrm8(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm9(u32 id) const { return _gfbbt::getArtsBlSpHitFrm9(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm10(u32 id) const { return _gfbbt::getArtsBlSpHitFrm10(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm11(u32 id) const { return _gfbbt::getArtsBlSpHitFrm11(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm12(u32 id) const { return _gfbbt::getArtsBlSpHitFrm12(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm13(u32 id) const { return _gfbbt::getArtsBlSpHitFrm13(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm14(u32 id) const { return _gfbbt::getArtsBlSpHitFrm14(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm15(u32 id) const { return _gfbbt::getArtsBlSpHitFrm15(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm16(u32 id) const { return _gfbbt::getArtsBlSpHitFrm16(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp1(u32 id) const { return _gfbbt::getArtsBlSpEfp1(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp2(u32 id) const { return _gfbbt::getArtsBlSpEfp2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp3(u32 id) const { return _gfbbt::getArtsBlSpEfp3(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp4(u32 id) const { return _gfbbt::getArtsBlSpEfp4(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp5(u32 id) const { return _gfbbt::getArtsBlSpEfp5(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp6(u32 id) const { return _gfbbt::getArtsBlSpEfp6(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp7(u32 id) const { return _gfbbt::getArtsBlSpEfp7(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp8(u32 id) const { return _gfbbt::getArtsBlSpEfp8(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp9(u32 id) const { return _gfbbt::getArtsBlSpEfp9(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp10(u32 id) const { return _gfbbt::getArtsBlSpEfp10(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp11(u32 id) const { return _gfbbt::getArtsBlSpEfp11(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp12(u32 id) const { return _gfbbt::getArtsBlSpEfp12(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp13(u32 id) const { return _gfbbt::getArtsBlSpEfp13(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp14(u32 id) const { return _gfbbt::getArtsBlSpEfp14(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp15(u32 id) const { return _gfbbt::getArtsBlSpEfp15(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEfp16(u32 id) const { return _gfbbt::getArtsBlSpEfp16(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID1(u32 id) const { return _gfbbt::getArtsBlSpHitDirID1(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID2(u32 id) const { return _gfbbt::getArtsBlSpHitDirID2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID3(u32 id) const { return _gfbbt::getArtsBlSpHitDirID3(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID4(u32 id) const { return _gfbbt::getArtsBlSpHitDirID4(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID5(u32 id) const { return _gfbbt::getArtsBlSpHitDirID5(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID6(u32 id) const { return _gfbbt::getArtsBlSpHitDirID6(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID7(u32 id) const { return _gfbbt::getArtsBlSpHitDirID7(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID8(u32 id) const { return _gfbbt::getArtsBlSpHitDirID8(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID9(u32 id) const { return _gfbbt::getArtsBlSpHitDirID9(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID10(u32 id) const { return _gfbbt::getArtsBlSpHitDirID10(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID11(u32 id) const { return _gfbbt::getArtsBlSpHitDirID11(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID12(u32 id) const { return _gfbbt::getArtsBlSpHitDirID12(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID13(u32 id) const { return _gfbbt::getArtsBlSpHitDirID13(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID14(u32 id) const { return _gfbbt::getArtsBlSpHitDirID14(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID15(u32 id) const { return _gfbbt::getArtsBlSpHitDirID15(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID16(u32 id) const { return _gfbbt::getArtsBlSpHitDirID16(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt1(u32 id) const { return _gfbbt::getArtsBlSpDmgRt1(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt2(u32 id) const { return _gfbbt::getArtsBlSpDmgRt2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt3(u32 id) const { return _gfbbt::getArtsBlSpDmgRt3(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt4(u32 id) const { return _gfbbt::getArtsBlSpDmgRt4(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt5(u32 id) const { return _gfbbt::getArtsBlSpDmgRt5(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt6(u32 id) const { return _gfbbt::getArtsBlSpDmgRt6(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt7(u32 id) const { return _gfbbt::getArtsBlSpDmgRt7(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt8(u32 id) const { return _gfbbt::getArtsBlSpDmgRt8(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt9(u32 id) const { return _gfbbt::getArtsBlSpDmgRt9(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt10(u32 id) const { return _gfbbt::getArtsBlSpDmgRt10(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt11(u32 id) const { return _gfbbt::getArtsBlSpDmgRt11(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt12(u32 id) const { return _gfbbt::getArtsBlSpDmgRt12(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt13(u32 id) const { return _gfbbt::getArtsBlSpDmgRt13(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt14(u32 id) const { return _gfbbt::getArtsBlSpDmgRt14(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt15(u32 id) const { return _gfbbt::getArtsBlSpDmgRt15(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt16(u32 id) const { return _gfbbt::getArtsBlSpDmgRt16(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct1(u32 id) const { return _gfbbt::getArtsBlSpReAct1(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct2(u32 id) const { return _gfbbt::getArtsBlSpReAct2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct3(u32 id) const { return _gfbbt::getArtsBlSpReAct3(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct4(u32 id) const { return _gfbbt::getArtsBlSpReAct4(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct5(u32 id) const { return _gfbbt::getArtsBlSpReAct5(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct6(u32 id) const { return _gfbbt::getArtsBlSpReAct6(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct7(u32 id) const { return _gfbbt::getArtsBlSpReAct7(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct8(u32 id) const { return _gfbbt::getArtsBlSpReAct8(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct9(u32 id) const { return _gfbbt::getArtsBlSpReAct9(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct10(u32 id) const { return _gfbbt::getArtsBlSpReAct10(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct11(u32 id) const { return _gfbbt::getArtsBlSpReAct11(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct12(u32 id) const { return _gfbbt::getArtsBlSpReAct12(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct13(u32 id) const { return _gfbbt::getArtsBlSpReAct13(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct14(u32 id) const { return _gfbbt::getArtsBlSpReAct14(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct15(u32 id) const { return _gfbbt::getArtsBlSpReAct15(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpReAct16(u32 id) const { return _gfbbt::getArtsBlSpReAct16(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpDmgMgn(u32 id) const { return _gfbbt::getArtsBlSpDmgMgn(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpRecast(u32 id) const { return _gfbbt::getArtsBlSpRecast(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpAtrNum(u32 id) const { return _gfbbt::getArtsBlSpAtrNum(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpEnhance(u32 id) const { return _gfbbt::getArtsBlSpEnhance(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpBtnType(u32 id) const { return _gfbbt::getArtsBlSpBtnType(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpBtnChal1(u32 id) const { return _gfbbt::getArtsBlSpBtnChal1(*unknown20, id); }

const char *GfBdatBtl::getArtsBlSpCamera1(u32 id) const { return _gfbbt::getArtsBlSpCamera1(*unknown20, id); }

const char *GfBdatBtl::getArtsBlSpCamera2(u32 id) const { return _gfbbt::getArtsBlSpCamera2(*unknown20, id); }

const char *GfBdatBtl::getArtsBlSpCamera3(u32 id) const { return _gfbbt::getArtsBlSpCamera3(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpCameraCT1(u32 id) const { return _gfbbt::getArtsBlSpCameraCT1(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpCameraCT2(u32 id) const { return _gfbbt::getArtsBlSpCameraCT2(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpCameraEndf(u32 id) const { return _gfbbt::getArtsBlSpCameraEndf(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitEff(u32 id) const { return _gfbbt::getArtsBlSpHitEff(*unknown20, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlSpHitFrm1,
                                                              _gfbbt::getArtsBlSpHitFrm2,
                                                              _gfbbt::getArtsBlSpHitFrm3,
                                                              _gfbbt::getArtsBlSpHitFrm4,
                                                              _gfbbt::getArtsBlSpHitFrm5,
                                                              _gfbbt::getArtsBlSpHitFrm6,
                                                              _gfbbt::getArtsBlSpHitFrm7,
                                                              _gfbbt::getArtsBlSpHitFrm8,
                                                              _gfbbt::getArtsBlSpHitFrm9,
                                                              _gfbbt::getArtsBlSpHitFrm10,
                                                              _gfbbt::getArtsBlSpHitFrm11,
                                                              _gfbbt::getArtsBlSpHitFrm12,
                                                              _gfbbt::getArtsBlSpHitFrm13,
                                                              _gfbbt::getArtsBlSpHitFrm14,
                                                              _gfbbt::getArtsBlSpHitFrm15,
                                                              _gfbbt::getArtsBlSpHitFrm16};
  return getters[index](*unknown20, id);
}

u32 GfBdatBtl::getArtsBlSpEfp(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlSpEfp1,
                                                              _gfbbt::getArtsBlSpEfp2,
                                                              _gfbbt::getArtsBlSpEfp3,
                                                              _gfbbt::getArtsBlSpEfp4,
                                                              _gfbbt::getArtsBlSpEfp5,
                                                              _gfbbt::getArtsBlSpEfp6,
                                                              _gfbbt::getArtsBlSpEfp7,
                                                              _gfbbt::getArtsBlSpEfp8,
                                                              _gfbbt::getArtsBlSpEfp9,
                                                              _gfbbt::getArtsBlSpEfp10,
                                                              _gfbbt::getArtsBlSpEfp11,
                                                              _gfbbt::getArtsBlSpEfp12,
                                                              _gfbbt::getArtsBlSpEfp13,
                                                              _gfbbt::getArtsBlSpEfp14,
                                                              _gfbbt::getArtsBlSpEfp15,
                                                              _gfbbt::getArtsBlSpEfp16};
  return getters[index](*unknown20, id);
}

u32 GfBdatBtl::getArtsBlSpHitDirID(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlSpHitDirID1,
                                                              _gfbbt::getArtsBlSpHitDirID2,
                                                              _gfbbt::getArtsBlSpHitDirID3,
                                                              _gfbbt::getArtsBlSpHitDirID4,
                                                              _gfbbt::getArtsBlSpHitDirID5,
                                                              _gfbbt::getArtsBlSpHitDirID6,
                                                              _gfbbt::getArtsBlSpHitDirID7,
                                                              _gfbbt::getArtsBlSpHitDirID8,
                                                              _gfbbt::getArtsBlSpHitDirID9,
                                                              _gfbbt::getArtsBlSpHitDirID10,
                                                              _gfbbt::getArtsBlSpHitDirID11,
                                                              _gfbbt::getArtsBlSpHitDirID12,
                                                              _gfbbt::getArtsBlSpHitDirID13,
                                                              _gfbbt::getArtsBlSpHitDirID14,
                                                              _gfbbt::getArtsBlSpHitDirID15,
                                                              _gfbbt::getArtsBlSpHitDirID16};
  return getters[index](*unknown20, id);
}

u32 GfBdatBtl::getArtsBlSpDmgRt(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlSpDmgRt1,
                                                              _gfbbt::getArtsBlSpDmgRt2,
                                                              _gfbbt::getArtsBlSpDmgRt3,
                                                              _gfbbt::getArtsBlSpDmgRt4,
                                                              _gfbbt::getArtsBlSpDmgRt5,
                                                              _gfbbt::getArtsBlSpDmgRt6,
                                                              _gfbbt::getArtsBlSpDmgRt7,
                                                              _gfbbt::getArtsBlSpDmgRt8,
                                                              _gfbbt::getArtsBlSpDmgRt9,
                                                              _gfbbt::getArtsBlSpDmgRt10,
                                                              _gfbbt::getArtsBlSpDmgRt11,
                                                              _gfbbt::getArtsBlSpDmgRt12,
                                                              _gfbbt::getArtsBlSpDmgRt13,
                                                              _gfbbt::getArtsBlSpDmgRt14,
                                                              _gfbbt::getArtsBlSpDmgRt15,
                                                              _gfbbt::getArtsBlSpDmgRt16};
  return getters[index](*unknown20, id);
}

u32 GfBdatBtl::getArtsBlSpReAct(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getArtsBlSpReAct1,
                                                              _gfbbt::getArtsBlSpReAct2,
                                                              _gfbbt::getArtsBlSpReAct3,
                                                              _gfbbt::getArtsBlSpReAct4,
                                                              _gfbbt::getArtsBlSpReAct5,
                                                              _gfbbt::getArtsBlSpReAct6,
                                                              _gfbbt::getArtsBlSpReAct7,
                                                              _gfbbt::getArtsBlSpReAct8,
                                                              _gfbbt::getArtsBlSpReAct9,
                                                              _gfbbt::getArtsBlSpReAct10,
                                                              _gfbbt::getArtsBlSpReAct11,
                                                              _gfbbt::getArtsBlSpReAct12,
                                                              _gfbbt::getArtsBlSpReAct13,
                                                              _gfbbt::getArtsBlSpReAct14,
                                                              _gfbbt::getArtsBlSpReAct15,
                                                              _gfbbt::getArtsBlSpReAct16};
  return getters[index](*unknown20, id);
}

u32 GfBdatBtl::getGrowStart() const { return Bdat::getIdTop(unknown28->data); }

u32 GfBdatBtl::getGrowEnd() const { return Bdat::getIdTop(unknown28->data) + Bdat::getIdCount(unknown28->data); }

u32 GfBdatBtl::getGrowLevelExp(u32 id) const { return _gfbbt::getGrowLevelExp(*unknown28, id); }

u32 GfBdatBtl::getGrowEnemyExp(u32 id) const { return _gfbbt::getGrowEnemyExp(*unknown28, id); }

u32 GfBdatBtl::getGrowEnemyWP(u32 id) const { return _gfbbt::getGrowEnemyWP(*unknown28, id); }

u32 GfBdatBtl::getGrowEnemySP(u32 id) const { return _gfbbt::getGrowEnemySP(*unknown28, id); }

u32 GfBdatBtl::getGrowEnemyGold(u32 id) const { return _gfbbt::getGrowEnemyGold(*unknown28, id); }

u32 GfBdatBtl::getGrowGoldDivide(u32 id) const { return _gfbbt::getGrowGoldDivide(*unknown28, id); }

u32 GfBdatBtl::getLv_RevStart() const { return Bdat::getIdTop(unknown30->data); }

u32 GfBdatBtl::getLv_RevEnd() const { return Bdat::getIdTop(unknown30->data) + Bdat::getIdCount(unknown30->data); }

u32 GfBdatBtl::getLv_RevExpRevHigh(u32 id) const { return _gfbbt::getLv_RevExpRevHigh(*unknown30, id); }

u32 GfBdatBtl::getLv_RevExpRevLow(u32 id) const { return _gfbbt::getLv_RevExpRevLow(*unknown30, id); }

u32 GfBdatBtl::getLv_RevDamageRevHigh(u32 id) const { return _gfbbt::getLv_RevDamageRevHigh(*unknown30, id); }

u32 GfBdatBtl::getLv_RevDamageRevLow(u32 id) const { return _gfbbt::getLv_RevDamageRevLow(*unknown30, id); }

u32 GfBdatBtl::getWpn_EnStart() const { return Bdat::getIdTop(unknown38->data); }

u32 GfBdatBtl::getWpn_EnEnd() const { return Bdat::getIdTop(unknown38->data) + Bdat::getIdCount(unknown38->data); }

u32 GfBdatBtl::getWpn_EnRscR(u32 id) const { return _gfbbt::getWpn_EnRscR(*unknown38, id); }

u32 GfBdatBtl::getWpn_EnRscL(u32 id) const { return _gfbbt::getWpn_EnRscL(*unknown38, id); }

u32 GfBdatBtl::getWpn_EnTypeRange(u32 id) const { return _gfbbt::getWpn_EnTypeRange(*unknown38, id); }

u32 GfBdatBtl::getWpn_EnDamage(u32 id) const { return _gfbbt::getWpn_EnDamage(*unknown38, id); }

u32 GfBdatBtl::getWpn_EnStability(u32 id) const { return _gfbbt::getWpn_EnStability(*unknown38, id); }

u32 GfBdatBtl::getBTL_ClassStart() const { return Bdat::getIdTop(unknown40->data); }

u32 GfBdatBtl::getBTL_ClassEnd() const { return Bdat::getIdTop(unknown40->data) + Bdat::getIdCount(unknown40->data); }

u32 GfBdatBtl::getBTL_ClassName(u32 id) const { return _gfbbt::getBTL_ClassName(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassRole1(u32 id) const { return _gfbbt::getBTL_ClassRole1(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassRole2(u32 id) const { return _gfbbt::getBTL_ClassRole2(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassRole3(u32 id) const { return _gfbbt::getBTL_ClassRole3(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassDamageDown(u32 id) const { return _gfbbt::getBTL_ClassDamageDown(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassDamageUP(u32 id) const { return _gfbbt::getBTL_ClassDamageUP(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassHealUP(u32 id) const { return _gfbbt::getBTL_ClassHealUP(*unknown40, id); }

s32 GfBdatBtl::getBTL_ClassAutoHate(u32 id) const { return _gfbbt::getBTL_ClassAutoHate(*unknown40, id); }

s32 GfBdatBtl::getBTL_ClassArtsHate(u32 id) const { return _gfbbt::getBTL_ClassArtsHate(*unknown40, id); }

u32 GfBdatBtl::getBTL_ClassRole(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_ClassRole1, _gfbbt::getBTL_ClassRole2, _gfbbt::getBTL_ClassRole3};
  return getters[index](*unknown40, id);
}

u32 GfBdatBtl::getBTL_EnhanceStart() const { return Bdat::getIdTop(unknown48->data); }

u32 GfBdatBtl::getBTL_EnhanceEnd() const { return Bdat::getIdTop(unknown48->data) + Bdat::getIdCount(unknown48->data); }

u32 GfBdatBtl::getBTL_EnhanceEnhanceEffect(u32 id) const { return _gfbbt::getBTL_EnhanceEnhanceEffect(*unknown48, id); }

f32 GfBdatBtl::getBTL_EnhanceParam1(u32 id) const { return _gfbbt::getBTL_EnhanceParam1(*unknown48, id); }

f32 GfBdatBtl::getBTL_EnhanceParam2(u32 id) const { return _gfbbt::getBTL_EnhanceParam2(*unknown48, id); }

u32 GfBdatBtl::getBTL_EnhanceCaption(u32 id) const { return _gfbbt::getBTL_EnhanceCaption(*unknown48, id); }

u32 GfBdatBtl::getBTL_EnhanceEffStart() const { return Bdat::getIdTop(unknown50->data); }

u32 GfBdatBtl::getBTL_EnhanceEffEnd() const { return Bdat::getIdTop(unknown50->data) + Bdat::getIdCount(unknown50->data); }

u32 GfBdatBtl::getBTL_EnhanceEffCategory(u32 id) const { return _gfbbt::getBTL_EnhanceEffCategory(*unknown50, id); }

u32 GfBdatBtl::getBTL_EnhanceEffIcon(u32 id) const { return _gfbbt::getBTL_EnhanceEffIcon(*unknown50, id); }

bool GfBdatBtl::isBTL_EnhanceEffFlagCondition(u32 id) const { return _gfbbt::isBTL_EnhanceEffFlagCondition(*unknown50, id); }

bool GfBdatBtl::isBTL_EnhanceEffFlagUI(u32 id) const { return _gfbbt::isBTL_EnhanceEffFlagUI(*unknown50, id); }

u32 GfBdatBtl::getBTL_EnhanceEffParam(u32 id) const { return _gfbbt::getBTL_EnhanceEffParam(*unknown50, id); }

u32 GfBdatBtl::getBTL_EnhanceEffName(u32 id) const { return _gfbbt::getBTL_EnhanceEffName(*unknown50, id); }

u32 GfBdatBtl::getBTL_EnhanceEffDirect(u32 id) const { return _gfbbt::getBTL_EnhanceEffDirect(*unknown50, id); }

u32 GfBdatBtl::getBTL_Skill_BlStart() const { return Bdat::getIdTop(unknown58->data); }

u32 GfBdatBtl::getBTL_Skill_BlEnd() const { return Bdat::getIdTop(unknown58->data) + Bdat::getIdCount(unknown58->data); }

u32 GfBdatBtl::getBTL_Skill_BlName(u32 id) const { return _gfbbt::getBTL_Skill_BlName(*unknown58, id); }

const char *GfBdatBtl::getBTL_Skill_BlDebugName(u32 id) const { return _gfbbt::getBTL_Skill_BlDebugName(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance1(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance1(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance2(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance2(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance3(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance3(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance4(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance4(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance5(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance5(*unknown58, id); }

bool GfBdatBtl::isBTL_Skill_BlFlagcommon(u32 id) const { return _gfbbt::isBTL_Skill_BlFlagcommon(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlTank(u32 id) const { return _gfbbt::getBTL_Skill_BlTank(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlAttacker(u32 id) const { return _gfbbt::getBTL_Skill_BlAttacker(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlHealer(u32 id) const { return _gfbbt::getBTL_Skill_BlHealer(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlUI(u32 id) const { return _gfbbt::getBTL_Skill_BlUI(*unknown58, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance(u32 skill, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_Skill_BlEnhance1,
                                                              _gfbbt::getBTL_Skill_BlEnhance2,
                                                              _gfbbt::getBTL_Skill_BlEnhance3,
                                                              _gfbbt::getBTL_Skill_BlEnhance4,
                                                              _gfbbt::getBTL_Skill_BlEnhance5};
  return getters[level](*unknown58, skill);
}

u32 GfBdatBtl::getBTL_Skill_DrStart() const { return Bdat::getIdTop(unknown60->data); }

u32 GfBdatBtl::getBTL_Skill_DrEnd() const { return Bdat::getIdTop(unknown60->data) + Bdat::getIdCount(unknown60->data); }

u32 GfBdatBtl::getBTL_Skill_DrName(u32 id) const { return _gfbbt::getBTL_Skill_DrName(*unknown60, id); }

const char *GfBdatBtl::getBTL_Skill_DrDebugName(u32 id) const { return _gfbbt::getBTL_Skill_DrDebugName(*unknown60, id); }

u32 GfBdatBtl::getBTL_Skill_DrEnhance(u32 id) const { return _gfbbt::getBTL_Skill_DrEnhance(*unknown60, id); }

u32 GfBdatBtl::getBTL_Skill_DrUI(u32 id) const { return _gfbbt::getBTL_Skill_DrUI(*unknown60, id); }

u32 GfBdatBtl::getBTL_BuffStart() const { return Bdat::getIdTop(unknown68->data); }

u32 GfBdatBtl::getBTL_BuffEnd() const { return Bdat::getIdTop(unknown68->data) + Bdat::getIdCount(unknown68->data); }

u32 GfBdatBtl::getBTL_BuffName(u32 id) const { return _gfbbt::getBTL_BuffName(*unknown68, id); }

const char *GfBdatBtl::getBTL_BuffDebugName(u32 id) const { return _gfbbt::getBTL_BuffDebugName(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffCaption(u32 id) const { return _gfbbt::getBTL_BuffCaption(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffBaseNum(u32 id) const { return _gfbbt::getBTL_BuffBaseNum(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffBaseTime(u32 id) const { return _gfbbt::getBTL_BuffBaseTime(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffBaseRecast(u32 id) const { return _gfbbt::getBTL_BuffBaseRecast(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffBaseProb(u32 id) const { return _gfbbt::getBTL_BuffBaseProb(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffInterval(u32 id) const { return _gfbbt::getBTL_BuffInterval(*unknown68, id); }

const char *GfBdatBtl::getBTL_BuffEffect(u32 id) const { return _gfbbt::getBTL_BuffEffect(*unknown68, id); }

u32 GfBdatBtl::getBTL_BuffIcon(u32 id) const { return _gfbbt::getBTL_BuffIcon(*unknown68, id); }

u32 GfBdatBtl::getBTL_Bl_PersonalityStart() const { return Bdat::getIdTop(unknown70->data); }

u32 GfBdatBtl::getBTL_Bl_PersonalityEnd() const { return Bdat::getIdTop(unknown70->data) + Bdat::getIdCount(unknown70->data); }

bool GfBdatBtl::isBTL_Bl_PersonalityFlagcommon(u32 id) const { return _gfbbt::isBTL_Bl_PersonalityFlagcommon(*unknown70, id); }

u32 GfBdatBtl::getBTL_Bl_PersonalityKizunaBase(u32 id) const { return _gfbbt::getBTL_Bl_PersonalityKizunaBase(*unknown70, id); }

u32 GfBdatBtl::getBTL_Bl_PersonalityVoiceID(u32 id) const { return _gfbbt::getBTL_Bl_PersonalityVoiceID(*unknown70, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkStart() const { return Bdat::getIdTop(unknown78->data); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkEnd() const { return Bdat::getIdTop(unknown78->data) + Bdat::getIdCount(unknown78->data); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkLinkNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkLinkNum(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkDeadNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkDeadNum(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppStNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppStNum(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppEndNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppEndNum(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppCond(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppCond(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppCondNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppCondNum(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkReJudgef(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkReJudgef(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSpActType(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSpActType(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSpActNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSpActNum(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSpActf(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSpActf(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkStandDir(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkStandDir(*unknown78, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetStart() const { return Bdat::getIdTop(unknown80->data); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetEnd() const { return Bdat::getIdTop(unknown80->data) + Bdat::getIdCount(unknown80->data); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetKizunaLink1(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetKizunaLink1(*unknown80, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetKizunaLink2(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetKizunaLink2(*unknown80, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChType(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetLinkChType(*unknown80, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetLinkChNum(*unknown80, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetVoiceID(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetVoiceID(*unknown80, id); }

u32 GfBdatBtl::getBTL_TestSettingStart() const { return Bdat::getIdTop(unknown88->data); }

u32 GfBdatBtl::getBTL_TestSettingEnd() const { return Bdat::getIdTop(unknown88->data) + Bdat::getIdCount(unknown88->data); }

u32 GfBdatBtl::getBTL_TestSettingDr1(u32 id) const { return _gfbbt::getBTL_TestSettingDr1(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Lv(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Lv(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Bl1(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Bl1(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Bl2(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Bl2(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Bl3(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Bl3(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2(u32 id) const { return _gfbbt::getBTL_TestSettingDr2(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Lv(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Lv(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Bl1(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Bl1(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Bl2(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Bl2(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Bl3(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Bl3(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3(u32 id) const { return _gfbbt::getBTL_TestSettingDr3(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Lv(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Lv(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Bl1(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Bl1(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Bl2(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Bl2(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Bl3(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Bl3(*unknown88, id); }

u32 GfBdatBtl::getBTL_TestSettingDr(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_TestSettingDr1, _gfbbt::getBTL_TestSettingDr2, _gfbbt::getBTL_TestSettingDr3};
  return getters[index](*unknown88, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrLv(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_TestSettingDr1Lv, _gfbbt::getBTL_TestSettingDr2Lv, _gfbbt::getBTL_TestSettingDr3Lv};
  return getters[index](*unknown88, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrBl1(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_TestSettingDr1Bl1, _gfbbt::getBTL_TestSettingDr2Bl1, _gfbbt::getBTL_TestSettingDr3Bl1};
  return getters[index](*unknown88, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrBl2(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_TestSettingDr1Bl2, _gfbbt::getBTL_TestSettingDr2Bl2, _gfbbt::getBTL_TestSettingDr3Bl2};
  return getters[index](*unknown88, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrBl3(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_TestSettingDr1Bl3, _gfbbt::getBTL_TestSettingDr2Bl3, _gfbbt::getBTL_TestSettingDr3Bl3};
  return getters[index](*unknown88, id);
}

u32 GfBdatBtl::getBTL_HanaBaseStart() const { return Bdat::getIdTop(unknown90->data); }

u32 GfBdatBtl::getBTL_HanaBaseEnd() const { return Bdat::getIdTop(unknown90->data) + Bdat::getIdCount(unknown90->data); }

u32 GfBdatBtl::getBTL_HanaBaseNCondNum(u32 id) const { return _gfbbt::getBTL_HanaBaseNCondNum(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseECondNum(u32 id) const { return _gfbbt::getBTL_HanaBaseECondNum(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseNArtsNum(u32 id) const { return _gfbbt::getBTL_HanaBaseNArtsNum(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit1Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit1Num(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit2Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit2Num(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit3Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit3Num(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit4Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit4Num(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit5Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit5Num(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit6Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit6Num(*unknown90, id); }

const char *GfBdatBtl::getBTL_HanaBaseUI(u32 id) const { return _gfbbt::getBTL_HanaBaseUI(*unknown90, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuitNum(u32 hana, u32 circuit) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_HanaBaseCircuit1Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit2Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit3Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit4Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit5Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit6Num};
  return getters[circuit](*unknown90, hana);
}

u32 GfBdatBtl::getBTL_HanaPowerStart() const { return Bdat::getIdTop(unknown98->data); }

u32 GfBdatBtl::getBTL_HanaPowerEnd() const { return Bdat::getIdTop(unknown98->data) + Bdat::getIdCount(unknown98->data); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum1(u32 id) const { return _gfbbt::getBTL_HanaPowerPowerNum1(*unknown98, id); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum2(u32 id) const { return _gfbbt::getBTL_HanaPowerPowerNum2(*unknown98, id); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum3(u32 id) const { return _gfbbt::getBTL_HanaPowerPowerNum3(*unknown98, id); }

u32 GfBdatBtl::getBTL_HanaPowerEtherNum1(u32 id) const { return _gfbbt::getBTL_HanaPowerEtherNum1(*unknown98, id); }

u32 GfBdatBtl::getBTL_HanaPowerEtherNum2(u32 id) const { return _gfbbt::getBTL_HanaPowerEtherNum2(*unknown98, id); }

u32 GfBdatBtl::getBTL_HanaPowerEtherNum3(u32 id) const { return _gfbbt::getBTL_HanaPowerEtherNum3(*unknown98, id); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum(u32 rank, u32 hana) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_HanaPowerPowerNum1, _gfbbt::getBTL_HanaPowerPowerNum2, _gfbbt::getBTL_HanaPowerPowerNum3};
  return getters[hana](*unknown98, rank);
}

u32 GfBdatBtl::getBTL_HanaPowerEtherNum(u32 rank, u32 hana) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getBTL_HanaPowerEtherNum1, _gfbbt::getBTL_HanaPowerEtherNum2, _gfbbt::getBTL_HanaPowerEtherNum3};
  return getters[hana](*unknown98, rank);
}

u32 GfBdatBtl::getBTL_HanaChipsetStart() const { return Bdat::getIdTop(unknowna0->data); }

u32 GfBdatBtl::getBTL_HanaChipsetEnd() const { return Bdat::getIdTop(unknowna0->data) + Bdat::getIdCount(unknowna0->data); }

u32 GfBdatBtl::getBTL_HanaChipsetRoleParts(u32 id) const { return _gfbbt::getBTL_HanaChipsetRoleParts(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetAtrParts(u32 id) const { return _gfbbt::getBTL_HanaChipsetAtrParts(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts1(u32 id) const { return _gfbbt::getBTL_HanaChipsetNArtsParts1(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts2(u32 id) const { return _gfbbt::getBTL_HanaChipsetNArtsParts2(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts3(u32 id) const { return _gfbbt::getBTL_HanaChipsetNArtsParts3(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts1(u32 id) const { return _gfbbt::getBTL_HanaChipsetNCondParts1(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts2(u32 id) const { return _gfbbt::getBTL_HanaChipsetNCondParts2(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts3(u32 id) const { return _gfbbt::getBTL_HanaChipsetNCondParts3(*unknowna0, id); }

const char *GfBdatBtl::getBTL_HanaChipsetUI(u32 id) const { return _gfbbt::getBTL_HanaChipsetUI(*unknowna0, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts(u32 hana, u32 slot) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbt::getBTL_HanaChipsetNArtsParts1, _gfbbt::getBTL_HanaChipsetNArtsParts2, _gfbbt::getBTL_HanaChipsetNArtsParts3};
  return getters[slot](*unknowna0, hana);
}

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts(u32 hana, u32 slot) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbt::getBTL_HanaChipsetNCondParts1, _gfbbt::getBTL_HanaChipsetNCondParts2, _gfbbt::getBTL_HanaChipsetNCondParts3};
  return getters[slot](*unknowna0, hana);
}

u32 GfBdatBtl::getWildcardDataStart() const { return Bdat::getIdTop(unknowna8->data); }

u32 GfBdatBtl::getWildcardDataEnd() const { return Bdat::getIdTop(unknowna8->data) + Bdat::getIdCount(unknowna8->data); }

f32 GfBdatBtl::getWildcardDatavalueF4(u32 id) const { return _gfbbt::getWildcardDatavalueF4(*unknowna8, id); }

u32 GfBdatBtl::getWildcardDatavalueU2(u32 id) const { return _gfbbt::getWildcardDatavalueU2(*unknowna8, id); }

u32 GfBdatBtl::getVo_Field_FilterStart() const { return Bdat::getIdTop(unknownb0->data); }

u32 GfBdatBtl::getVo_Field_FilterEnd() const { return Bdat::getIdTop(unknownb0->data) + Bdat::getIdCount(unknownb0->data); }

const char *GfBdatBtl::getVo_Field_FilterTargetFile(u32 id) const { return _gfbbt::getVo_Field_FilterTargetFile(*unknownb0, id); }

u32 GfBdatBtl::getVo_Field_FilterCondition(u32 id) const { return _gfbbt::getVo_Field_FilterCondition(*unknownb0, id); }

const char *GfBdatBtl::getVo_Field_FilterChangeFile(u32 id) const { return _gfbbt::getVo_Field_FilterChangeFile(*unknownb0, id); }

} // namespace gf
