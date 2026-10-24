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

void initArtsDrName(const CBdatWrapper &wrapper) { s_members[ArtsDrName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getArtsDrName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrName], id, 2).valueU16;
}

void initArtsDrDebugName(const CBdatWrapper &wrapper) { s_members[ArtsDrDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getArtsDrDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsDrDebugName], id, 7).valueString;
}

void initArtsDrCaption(const CBdatWrapper &wrapper) { s_members[ArtsDrCaption] = Bdat::getMember(wrapper.unknown00, "Caption"); }

u32 getArtsDrCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrCaption] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrCaption], id, 2).valueU16;
}

void initArtsDrDriver(const CBdatWrapper &wrapper) { s_members[ArtsDrDriver] = Bdat::getMember(wrapper.unknown00, "Driver"); }

u32 getArtsDrDriver(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDriver] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDriver], id, 1).valueU8;
}

void initArtsDrWpnType(const CBdatWrapper &wrapper) { s_members[ArtsDrWpnType] = Bdat::getMember(wrapper.unknown00, "WpnType"); }

u32 getArtsDrWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrWpnType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrWpnType], id, 1).valueU8;
}

void initArtsDrActNo(const CBdatWrapper &wrapper) { s_members[ArtsDrActNo] = Bdat::getMember(wrapper.unknown00, "ActNo"); }

u32 getArtsDrActNo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrActNo] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrActNo], id, 1).valueU8;
}

void initArtsDrArtsType(const CBdatWrapper &wrapper) { s_members[ArtsDrArtsType] = Bdat::getMember(wrapper.unknown00, "ArtsType"); }

u32 getArtsDrArtsType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrArtsType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrArtsType], id, 1).valueU8;
}

void initArtsDrArtsBuff(const CBdatWrapper &wrapper) { s_members[ArtsDrArtsBuff] = Bdat::getMember(wrapper.unknown00, "ArtsBuff"); }

u32 getArtsDrArtsBuff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrArtsBuff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrArtsBuff], id, 1).valueU8;
}

void initArtsDrAtrType(const CBdatWrapper &wrapper) { s_members[ArtsDrAtrType] = Bdat::getMember(wrapper.unknown00, "AtrType"); }

u32 getArtsDrAtrType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrAtrType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrAtrType], id, 1).valueU8;
}

void initArtsDrFlagNormal(const CBdatWrapper &wrapper) {
  s_members[ArtsDrFlagNormal] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsDrFlagNormalFlag] = Bdat::getMember(wrapper.unknown00, "Normal");
}

bool isArtsDrFlagNormal(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrFlagNormal] == nullptr || s_members[ArtsDrFlagNormalFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsDrFlagNormal], id, s_members[ArtsDrFlagNormalFlag]) != 0;
}

void initArtsDrFlagPierce(const CBdatWrapper &wrapper) {
  s_members[ArtsDrFlagPierce] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsDrFlagPierceFlag] = Bdat::getMember(wrapper.unknown00, "Pierce");
}

bool isArtsDrFlagPierce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrFlagPierce] == nullptr || s_members[ArtsDrFlagPierceFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsDrFlagPierce], id, s_members[ArtsDrFlagPierceFlag]) != 0;
}

void initArtsDrFlagNoRepelled(const CBdatWrapper &wrapper) {
  s_members[ArtsDrFlagNoRepelled] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsDrFlagNoRepelledFlag] = Bdat::getMember(wrapper.unknown00, "NoRepelled");
}

bool isArtsDrFlagNoRepelled(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrFlagNoRepelled] == nullptr || s_members[ArtsDrFlagNoRepelledFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsDrFlagNoRepelled], id, s_members[ArtsDrFlagNoRepelledFlag]) != 0;
}

void initArtsDrNextArts(const CBdatWrapper &wrapper) { s_members[ArtsDrNextArts] = Bdat::getMember(wrapper.unknown00, "NextArts"); }

u32 getArtsDrNextArts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNextArts] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNextArts], id, 2).valueU16;
}

void initArtsDrTarget(const CBdatWrapper &wrapper) { s_members[ArtsDrTarget] = Bdat::getMember(wrapper.unknown00, "Target"); }

u32 getArtsDrTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrTarget] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrTarget], id, 1).valueU8;
}

void initArtsDrDistance(const CBdatWrapper &wrapper) { s_members[ArtsDrDistance] = Bdat::getMember(wrapper.unknown00, "Distance"); }

u32 getArtsDrDistance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDistance] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDistance], id, 2).valueU16;
}

void initArtsDrRangeType(const CBdatWrapper &wrapper) { s_members[ArtsDrRangeType] = Bdat::getMember(wrapper.unknown00, "RangeType"); }

u32 getArtsDrRangeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRangeType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRangeType], id, 1).valueU8;
}

void initArtsDrRadius(const CBdatWrapper &wrapper) { s_members[ArtsDrRadius] = Bdat::getMember(wrapper.unknown00, "Radius"); }

u32 getArtsDrRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRadius] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRadius], id, 2).valueU16;
}

void initArtsDrLength(const CBdatWrapper &wrapper) { s_members[ArtsDrLength] = Bdat::getMember(wrapper.unknown00, "Length"); }

u32 getArtsDrLength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrLength] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrLength], id, 2).valueU16;
}

void initArtsDrHate(const CBdatWrapper &wrapper) { s_members[ArtsDrHate] = Bdat::getMember(wrapper.unknown00, "Hate"); }

s32 getArtsDrHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHate] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHate], id, 4).valueS8;
}

void initArtsDrHitRevise(const CBdatWrapper &wrapper) { s_members[ArtsDrHitRevise] = Bdat::getMember(wrapper.unknown00, "HitRevise"); }

s32 getArtsDrHitRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitRevise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitRevise], id, 4).valueS8;
}

void initArtsDrCriRevise(const CBdatWrapper &wrapper) { s_members[ArtsDrCriRevise] = Bdat::getMember(wrapper.unknown00, "CriRevise"); }

s32 getArtsDrCriRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrCriRevise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrCriRevise], id, 4).valueS8;
}

void initArtsDrBulletID(const CBdatWrapper &wrapper) { s_members[ArtsDrBulletID] = Bdat::getMember(wrapper.unknown00, "BulletID"); }

u32 getArtsDrBulletID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrBulletID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrBulletID], id, 2).valueU16;
}

void initArtsDrBulletNum(const CBdatWrapper &wrapper) { s_members[ArtsDrBulletNum] = Bdat::getMember(wrapper.unknown00, "BulletNum"); }

u32 getArtsDrBulletNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrBulletNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrBulletNum], id, 1).valueU8;
}

void initArtsDrHitFrm1(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm1] = Bdat::getMember(wrapper.unknown00, "HitFrm1"); }

u32 getArtsDrHitFrm1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm1], id, 1).valueU8;
}

void initArtsDrHitFrm2(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm2] = Bdat::getMember(wrapper.unknown00, "HitFrm2"); }

u32 getArtsDrHitFrm2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm2], id, 1).valueU8;
}

void initArtsDrHitFrm3(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm3] = Bdat::getMember(wrapper.unknown00, "HitFrm3"); }

u32 getArtsDrHitFrm3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm3], id, 1).valueU8;
}

void initArtsDrHitFrm4(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm4] = Bdat::getMember(wrapper.unknown00, "HitFrm4"); }

u32 getArtsDrHitFrm4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm4], id, 1).valueU8;
}

void initArtsDrHitFrm5(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm5] = Bdat::getMember(wrapper.unknown00, "HitFrm5"); }

u32 getArtsDrHitFrm5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm5], id, 1).valueU8;
}

void initArtsDrHitFrm6(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm6] = Bdat::getMember(wrapper.unknown00, "HitFrm6"); }

u32 getArtsDrHitFrm6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm6], id, 1).valueU8;
}

void initArtsDrHitFrm7(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm7] = Bdat::getMember(wrapper.unknown00, "HitFrm7"); }

u32 getArtsDrHitFrm7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm7], id, 1).valueU8;
}

void initArtsDrHitFrm8(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm8] = Bdat::getMember(wrapper.unknown00, "HitFrm8"); }

u32 getArtsDrHitFrm8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm8], id, 1).valueU8;
}

void initArtsDrHitFrm9(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm9] = Bdat::getMember(wrapper.unknown00, "HitFrm9"); }

u32 getArtsDrHitFrm9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm9], id, 1).valueU8;
}

void initArtsDrHitFrm10(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm10] = Bdat::getMember(wrapper.unknown00, "HitFrm10"); }

u32 getArtsDrHitFrm10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm10], id, 1).valueU8;
}

void initArtsDrHitFrm11(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm11] = Bdat::getMember(wrapper.unknown00, "HitFrm11"); }

u32 getArtsDrHitFrm11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm11], id, 1).valueU8;
}

void initArtsDrHitFrm12(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm12] = Bdat::getMember(wrapper.unknown00, "HitFrm12"); }

u32 getArtsDrHitFrm12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm12], id, 1).valueU8;
}

void initArtsDrHitFrm13(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm13] = Bdat::getMember(wrapper.unknown00, "HitFrm13"); }

u32 getArtsDrHitFrm13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm13], id, 1).valueU8;
}

void initArtsDrHitFrm14(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm14] = Bdat::getMember(wrapper.unknown00, "HitFrm14"); }

u32 getArtsDrHitFrm14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm14], id, 1).valueU8;
}

void initArtsDrHitFrm15(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm15] = Bdat::getMember(wrapper.unknown00, "HitFrm15"); }

u32 getArtsDrHitFrm15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm15], id, 1).valueU8;
}

void initArtsDrHitFrm16(const CBdatWrapper &wrapper) { s_members[ArtsDrHitFrm16] = Bdat::getMember(wrapper.unknown00, "HitFrm16"); }

u32 getArtsDrHitFrm16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitFrm16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitFrm16], id, 1).valueU8;
}

void initArtsDrEfp1(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp1] = Bdat::getMember(wrapper.unknown00, "Efp1"); }

u32 getArtsDrEfp1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp1], id, 1).valueU8;
}

void initArtsDrEfp2(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp2] = Bdat::getMember(wrapper.unknown00, "Efp2"); }

u32 getArtsDrEfp2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp2], id, 1).valueU8;
}

void initArtsDrEfp3(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp3] = Bdat::getMember(wrapper.unknown00, "Efp3"); }

u32 getArtsDrEfp3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp3], id, 1).valueU8;
}

void initArtsDrEfp4(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp4] = Bdat::getMember(wrapper.unknown00, "Efp4"); }

u32 getArtsDrEfp4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp4], id, 1).valueU8;
}

void initArtsDrEfp5(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp5] = Bdat::getMember(wrapper.unknown00, "Efp5"); }

u32 getArtsDrEfp5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp5], id, 1).valueU8;
}

void initArtsDrEfp6(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp6] = Bdat::getMember(wrapper.unknown00, "Efp6"); }

u32 getArtsDrEfp6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp6], id, 1).valueU8;
}

void initArtsDrEfp7(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp7] = Bdat::getMember(wrapper.unknown00, "Efp7"); }

u32 getArtsDrEfp7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp7], id, 1).valueU8;
}

void initArtsDrEfp8(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp8] = Bdat::getMember(wrapper.unknown00, "Efp8"); }

u32 getArtsDrEfp8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp8], id, 1).valueU8;
}

void initArtsDrEfp9(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp9] = Bdat::getMember(wrapper.unknown00, "Efp9"); }

u32 getArtsDrEfp9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp9], id, 1).valueU8;
}

void initArtsDrEfp10(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp10] = Bdat::getMember(wrapper.unknown00, "Efp10"); }

u32 getArtsDrEfp10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp10], id, 1).valueU8;
}

void initArtsDrEfp11(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp11] = Bdat::getMember(wrapper.unknown00, "Efp11"); }

u32 getArtsDrEfp11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp11], id, 1).valueU8;
}

void initArtsDrEfp12(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp12] = Bdat::getMember(wrapper.unknown00, "Efp12"); }

u32 getArtsDrEfp12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp12], id, 1).valueU8;
}

void initArtsDrEfp13(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp13] = Bdat::getMember(wrapper.unknown00, "Efp13"); }

u32 getArtsDrEfp13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp13], id, 1).valueU8;
}

void initArtsDrEfp14(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp14] = Bdat::getMember(wrapper.unknown00, "Efp14"); }

u32 getArtsDrEfp14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp14], id, 1).valueU8;
}

void initArtsDrEfp15(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp15] = Bdat::getMember(wrapper.unknown00, "Efp15"); }

u32 getArtsDrEfp15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp15], id, 1).valueU8;
}

void initArtsDrEfp16(const CBdatWrapper &wrapper) { s_members[ArtsDrEfp16] = Bdat::getMember(wrapper.unknown00, "Efp16"); }

u32 getArtsDrEfp16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEfp16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEfp16], id, 1).valueU8;
}

void initArtsDrHitDirID1(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID1] = Bdat::getMember(wrapper.unknown00, "HitDirID1"); }

u32 getArtsDrHitDirID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID1], id, 1).valueU8;
}

void initArtsDrHitDirID2(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID2] = Bdat::getMember(wrapper.unknown00, "HitDirID2"); }

u32 getArtsDrHitDirID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID2], id, 1).valueU8;
}

void initArtsDrHitDirID3(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID3] = Bdat::getMember(wrapper.unknown00, "HitDirID3"); }

u32 getArtsDrHitDirID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID3], id, 1).valueU8;
}

void initArtsDrHitDirID4(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID4] = Bdat::getMember(wrapper.unknown00, "HitDirID4"); }

u32 getArtsDrHitDirID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID4], id, 1).valueU8;
}

void initArtsDrHitDirID5(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID5] = Bdat::getMember(wrapper.unknown00, "HitDirID5"); }

u32 getArtsDrHitDirID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID5], id, 1).valueU8;
}

void initArtsDrHitDirID6(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID6] = Bdat::getMember(wrapper.unknown00, "HitDirID6"); }

u32 getArtsDrHitDirID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID6], id, 1).valueU8;
}

void initArtsDrHitDirID7(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID7] = Bdat::getMember(wrapper.unknown00, "HitDirID7"); }

u32 getArtsDrHitDirID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID7], id, 1).valueU8;
}

void initArtsDrHitDirID8(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID8] = Bdat::getMember(wrapper.unknown00, "HitDirID8"); }

u32 getArtsDrHitDirID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID8], id, 1).valueU8;
}

void initArtsDrHitDirID9(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID9] = Bdat::getMember(wrapper.unknown00, "HitDirID9"); }

u32 getArtsDrHitDirID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID9], id, 1).valueU8;
}

void initArtsDrHitDirID10(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID10] = Bdat::getMember(wrapper.unknown00, "HitDirID10"); }

u32 getArtsDrHitDirID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID10], id, 1).valueU8;
}

void initArtsDrHitDirID11(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID11] = Bdat::getMember(wrapper.unknown00, "HitDirID11"); }

u32 getArtsDrHitDirID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID11], id, 1).valueU8;
}

void initArtsDrHitDirID12(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID12] = Bdat::getMember(wrapper.unknown00, "HitDirID12"); }

u32 getArtsDrHitDirID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID12], id, 1).valueU8;
}

void initArtsDrHitDirID13(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID13] = Bdat::getMember(wrapper.unknown00, "HitDirID13"); }

u32 getArtsDrHitDirID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID13], id, 1).valueU8;
}

void initArtsDrHitDirID14(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID14] = Bdat::getMember(wrapper.unknown00, "HitDirID14"); }

u32 getArtsDrHitDirID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID14], id, 1).valueU8;
}

void initArtsDrHitDirID15(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID15] = Bdat::getMember(wrapper.unknown00, "HitDirID15"); }

u32 getArtsDrHitDirID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID15], id, 1).valueU8;
}

void initArtsDrHitDirID16(const CBdatWrapper &wrapper) { s_members[ArtsDrHitDirID16] = Bdat::getMember(wrapper.unknown00, "HitDirID16"); }

u32 getArtsDrHitDirID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrHitDirID16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrHitDirID16], id, 1).valueU8;
}

void initArtsDrDmgRt1(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt1] = Bdat::getMember(wrapper.unknown00, "DmgRt1"); }

u32 getArtsDrDmgRt1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt1], id, 1).valueU8;
}

void initArtsDrDmgRt2(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt2] = Bdat::getMember(wrapper.unknown00, "DmgRt2"); }

u32 getArtsDrDmgRt2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt2], id, 1).valueU8;
}

void initArtsDrDmgRt3(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt3] = Bdat::getMember(wrapper.unknown00, "DmgRt3"); }

u32 getArtsDrDmgRt3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt3], id, 1).valueU8;
}

void initArtsDrDmgRt4(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt4] = Bdat::getMember(wrapper.unknown00, "DmgRt4"); }

u32 getArtsDrDmgRt4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt4], id, 1).valueU8;
}

void initArtsDrDmgRt5(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt5] = Bdat::getMember(wrapper.unknown00, "DmgRt5"); }

u32 getArtsDrDmgRt5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt5], id, 1).valueU8;
}

void initArtsDrDmgRt6(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt6] = Bdat::getMember(wrapper.unknown00, "DmgRt6"); }

u32 getArtsDrDmgRt6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt6], id, 1).valueU8;
}

void initArtsDrDmgRt7(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt7] = Bdat::getMember(wrapper.unknown00, "DmgRt7"); }

u32 getArtsDrDmgRt7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt7], id, 1).valueU8;
}

void initArtsDrDmgRt8(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt8] = Bdat::getMember(wrapper.unknown00, "DmgRt8"); }

u32 getArtsDrDmgRt8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt8], id, 1).valueU8;
}

void initArtsDrDmgRt9(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt9] = Bdat::getMember(wrapper.unknown00, "DmgRt9"); }

u32 getArtsDrDmgRt9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt9], id, 1).valueU8;
}

void initArtsDrDmgRt10(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt10] = Bdat::getMember(wrapper.unknown00, "DmgRt10"); }

u32 getArtsDrDmgRt10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt10], id, 1).valueU8;
}

void initArtsDrDmgRt11(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt11] = Bdat::getMember(wrapper.unknown00, "DmgRt11"); }

u32 getArtsDrDmgRt11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt11], id, 1).valueU8;
}

void initArtsDrDmgRt12(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt12] = Bdat::getMember(wrapper.unknown00, "DmgRt12"); }

u32 getArtsDrDmgRt12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt12], id, 1).valueU8;
}

void initArtsDrDmgRt13(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt13] = Bdat::getMember(wrapper.unknown00, "DmgRt13"); }

u32 getArtsDrDmgRt13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt13], id, 1).valueU8;
}

void initArtsDrDmgRt14(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt14] = Bdat::getMember(wrapper.unknown00, "DmgRt14"); }

u32 getArtsDrDmgRt14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt14], id, 1).valueU8;
}

void initArtsDrDmgRt15(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt15] = Bdat::getMember(wrapper.unknown00, "DmgRt15"); }

u32 getArtsDrDmgRt15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt15], id, 1).valueU8;
}

void initArtsDrDmgRt16(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgRt16] = Bdat::getMember(wrapper.unknown00, "DmgRt16"); }

u32 getArtsDrDmgRt16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgRt16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgRt16], id, 1).valueU8;
}

void initArtsDrReAct1(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct1] = Bdat::getMember(wrapper.unknown00, "ReAct1"); }

u32 getArtsDrReAct1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct1], id, 1).valueU8;
}

void initArtsDrReAct2(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct2] = Bdat::getMember(wrapper.unknown00, "ReAct2"); }

u32 getArtsDrReAct2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct2], id, 1).valueU8;
}

void initArtsDrReAct3(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct3] = Bdat::getMember(wrapper.unknown00, "ReAct3"); }

u32 getArtsDrReAct3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct3], id, 1).valueU8;
}

void initArtsDrReAct4(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct4] = Bdat::getMember(wrapper.unknown00, "ReAct4"); }

u32 getArtsDrReAct4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct4], id, 1).valueU8;
}

void initArtsDrReAct5(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct5] = Bdat::getMember(wrapper.unknown00, "ReAct5"); }

u32 getArtsDrReAct5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct5], id, 1).valueU8;
}

void initArtsDrReAct6(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct6] = Bdat::getMember(wrapper.unknown00, "ReAct6"); }

u32 getArtsDrReAct6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct6], id, 1).valueU8;
}

void initArtsDrReAct7(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct7] = Bdat::getMember(wrapper.unknown00, "ReAct7"); }

u32 getArtsDrReAct7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct7], id, 1).valueU8;
}

void initArtsDrReAct8(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct8] = Bdat::getMember(wrapper.unknown00, "ReAct8"); }

u32 getArtsDrReAct8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct8], id, 1).valueU8;
}

void initArtsDrReAct9(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct9] = Bdat::getMember(wrapper.unknown00, "ReAct9"); }

u32 getArtsDrReAct9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct9], id, 1).valueU8;
}

void initArtsDrReAct10(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct10] = Bdat::getMember(wrapper.unknown00, "ReAct10"); }

u32 getArtsDrReAct10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct10], id, 1).valueU8;
}

void initArtsDrReAct11(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct11] = Bdat::getMember(wrapper.unknown00, "ReAct11"); }

u32 getArtsDrReAct11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct11], id, 1).valueU8;
}

void initArtsDrReAct12(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct12] = Bdat::getMember(wrapper.unknown00, "ReAct12"); }

u32 getArtsDrReAct12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct12], id, 1).valueU8;
}

void initArtsDrReAct13(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct13] = Bdat::getMember(wrapper.unknown00, "ReAct13"); }

u32 getArtsDrReAct13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct13], id, 1).valueU8;
}

void initArtsDrReAct14(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct14] = Bdat::getMember(wrapper.unknown00, "ReAct14"); }

u32 getArtsDrReAct14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct14], id, 1).valueU8;
}

void initArtsDrReAct15(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct15] = Bdat::getMember(wrapper.unknown00, "ReAct15"); }

u32 getArtsDrReAct15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct15], id, 1).valueU8;
}

void initArtsDrReAct16(const CBdatWrapper &wrapper) { s_members[ArtsDrReAct16] = Bdat::getMember(wrapper.unknown00, "ReAct16"); }

u32 getArtsDrReAct16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReAct16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReAct16], id, 1).valueU8;
}

void initArtsDrMoveCancelFrm(const CBdatWrapper &wrapper) { s_members[ArtsDrMoveCancelFrm] = Bdat::getMember(wrapper.unknown00, "MoveCancelFrm"); }

u32 getArtsDrMoveCancelFrm(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrMoveCancelFrm] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrMoveCancelFrm], id, 1).valueU8;
}

void initArtsDrDmgMgn1(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn1] = Bdat::getMember(wrapper.unknown00, "DmgMgn1"); }

u32 getArtsDrDmgMgn1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn1], id, 2).valueU16;
}

void initArtsDrDmgMgn2(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn2] = Bdat::getMember(wrapper.unknown00, "DmgMgn2"); }

u32 getArtsDrDmgMgn2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn2], id, 2).valueU16;
}

void initArtsDrDmgMgn3(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn3] = Bdat::getMember(wrapper.unknown00, "DmgMgn3"); }

u32 getArtsDrDmgMgn3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn3], id, 2).valueU16;
}

void initArtsDrDmgMgn4(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn4] = Bdat::getMember(wrapper.unknown00, "DmgMgn4"); }

u32 getArtsDrDmgMgn4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn4], id, 2).valueU16;
}

void initArtsDrDmgMgn5(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn5] = Bdat::getMember(wrapper.unknown00, "DmgMgn5"); }

u32 getArtsDrDmgMgn5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn5], id, 2).valueU16;
}

void initArtsDrDmgMgn6(const CBdatWrapper &wrapper) { s_members[ArtsDrDmgMgn6] = Bdat::getMember(wrapper.unknown00, "DmgMgn6"); }

u32 getArtsDrDmgMgn6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrDmgMgn6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrDmgMgn6], id, 2).valueU16;
}

void initArtsDrRecast1(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast1] = Bdat::getMember(wrapper.unknown00, "Recast1"); }

u32 getArtsDrRecast1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast1], id, 2).valueU16;
}

void initArtsDrRecast2(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast2] = Bdat::getMember(wrapper.unknown00, "Recast2"); }

u32 getArtsDrRecast2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast2], id, 2).valueU16;
}

void initArtsDrRecast3(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast3] = Bdat::getMember(wrapper.unknown00, "Recast3"); }

u32 getArtsDrRecast3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast3], id, 2).valueU16;
}

void initArtsDrRecast4(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast4] = Bdat::getMember(wrapper.unknown00, "Recast4"); }

u32 getArtsDrRecast4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast4], id, 2).valueU16;
}

void initArtsDrRecast5(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast5] = Bdat::getMember(wrapper.unknown00, "Recast5"); }

u32 getArtsDrRecast5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast5], id, 2).valueU16;
}

void initArtsDrRecast6(const CBdatWrapper &wrapper) { s_members[ArtsDrRecast6] = Bdat::getMember(wrapper.unknown00, "Recast6"); }

u32 getArtsDrRecast6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrRecast6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrRecast6], id, 2).valueU16;
}

void initArtsDrAtrNum(const CBdatWrapper &wrapper) { s_members[ArtsDrAtrNum] = Bdat::getMember(wrapper.unknown00, "AtrNum"); }

u32 getArtsDrAtrNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrAtrNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrAtrNum], id, 1).valueU8;
}

void initArtsDrEnhance1(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance1] = Bdat::getMember(wrapper.unknown00, "Enhance1"); }

u32 getArtsDrEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance1], id, 2).valueU16;
}

void initArtsDrEnhance2(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance2] = Bdat::getMember(wrapper.unknown00, "Enhance2"); }

u32 getArtsDrEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance2], id, 2).valueU16;
}

void initArtsDrEnhance3(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance3] = Bdat::getMember(wrapper.unknown00, "Enhance3"); }

u32 getArtsDrEnhance3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance3], id, 2).valueU16;
}

void initArtsDrEnhance4(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance4] = Bdat::getMember(wrapper.unknown00, "Enhance4"); }

u32 getArtsDrEnhance4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance4], id, 2).valueU16;
}

void initArtsDrEnhance5(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance5] = Bdat::getMember(wrapper.unknown00, "Enhance5"); }

u32 getArtsDrEnhance5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance5], id, 2).valueU16;
}

void initArtsDrEnhance6(const CBdatWrapper &wrapper) { s_members[ArtsDrEnhance6] = Bdat::getMember(wrapper.unknown00, "Enhance6"); }

u32 getArtsDrEnhance6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrEnhance6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrEnhance6], id, 2).valueU16;
}

void initArtsDrReleaseLv1(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv1] = Bdat::getMember(wrapper.unknown00, "ReleaseLv1"); }

u32 getArtsDrReleaseLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv1], id, 1).valueU8;
}

void initArtsDrReleaseLv2(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv2] = Bdat::getMember(wrapper.unknown00, "ReleaseLv2"); }

u32 getArtsDrReleaseLv2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv2], id, 1).valueU8;
}

void initArtsDrReleaseLv3(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv3] = Bdat::getMember(wrapper.unknown00, "ReleaseLv3"); }

u32 getArtsDrReleaseLv3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv3], id, 1).valueU8;
}

void initArtsDrReleaseLv4(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv4] = Bdat::getMember(wrapper.unknown00, "ReleaseLv4"); }

u32 getArtsDrReleaseLv4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv4], id, 1).valueU8;
}

void initArtsDrReleaseLv5(const CBdatWrapper &wrapper) { s_members[ArtsDrReleaseLv5] = Bdat::getMember(wrapper.unknown00, "ReleaseLv5"); }

u32 getArtsDrReleaseLv5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrReleaseLv5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrReleaseLv5], id, 1).valueU8;
}

void initArtsDrNeedWP2(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP2] = Bdat::getMember(wrapper.unknown00, "NeedWP2"); }

u32 getArtsDrNeedWP2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP2], id, 2).valueU16;
}

void initArtsDrNeedWP3(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP3] = Bdat::getMember(wrapper.unknown00, "NeedWP3"); }

u32 getArtsDrNeedWP3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP3], id, 2).valueU16;
}

void initArtsDrNeedWP4(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP4] = Bdat::getMember(wrapper.unknown00, "NeedWP4"); }

u32 getArtsDrNeedWP4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP4], id, 2).valueU16;
}

void initArtsDrNeedWP5(const CBdatWrapper &wrapper) { s_members[ArtsDrNeedWP5] = Bdat::getMember(wrapper.unknown00, "NeedWP5"); }

u32 getArtsDrNeedWP5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrNeedWP5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrNeedWP5], id, 2).valueU16;
}

void initArtsDrUI(const CBdatWrapper &wrapper) { s_members[ArtsDrUI] = Bdat::getMember(wrapper.unknown00, "UI"); }

u32 getArtsDrUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrUI] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrUI], id, 2).valueU16;
}

void initArtsDrPriority(const CBdatWrapper &wrapper) { s_members[ArtsDrPriority] = Bdat::getMember(wrapper.unknown00, "Priority"); }

u32 getArtsDrPriority(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsDrPriority] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsDrPriority], id, 1).valueU8;
}

void initArtsBlName(const CBdatWrapper &wrapper) { s_members[ArtsBlName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getArtsBlName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlName], id, 2).valueU16;
}

void initArtsBlDebugName(const CBdatWrapper &wrapper) { s_members[ArtsBlDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getArtsBlDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlDebugName], id, 7).valueString;
}

void initArtsBlCaption(const CBdatWrapper &wrapper) { s_members[ArtsBlCaption] = Bdat::getMember(wrapper.unknown00, "Caption"); }

u32 getArtsBlCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlCaption] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlCaption], id, 2).valueU16;
}

void initArtsBlWpnType(const CBdatWrapper &wrapper) { s_members[ArtsBlWpnType] = Bdat::getMember(wrapper.unknown00, "WpnType"); }

u32 getArtsBlWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlWpnType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlWpnType], id, 1).valueU8;
}

void initArtsBlCmnBlType(const CBdatWrapper &wrapper) { s_members[ArtsBlCmnBlType] = Bdat::getMember(wrapper.unknown00, "CmnBlType"); }

u32 getArtsBlCmnBlType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlCmnBlType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlCmnBlType], id, 1).valueU8;
}

void initArtsBlSpLv(const CBdatWrapper &wrapper) { s_members[ArtsBlSpLv] = Bdat::getMember(wrapper.unknown00, "SpLv"); }

u32 getArtsBlSpLv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpLv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpLv], id, 1).valueU8;
}

void initArtsBlActNo(const CBdatWrapper &wrapper) { s_members[ArtsBlActNo] = Bdat::getMember(wrapper.unknown00, "ActNo"); }

u32 getArtsBlActNo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlActNo] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlActNo], id, 1).valueU8;
}

void initArtsBlArtsType(const CBdatWrapper &wrapper) { s_members[ArtsBlArtsType] = Bdat::getMember(wrapper.unknown00, "ArtsType"); }

u32 getArtsBlArtsType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlArtsType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlArtsType], id, 1).valueU8;
}

void initArtsBlArtsBuff(const CBdatWrapper &wrapper) { s_members[ArtsBlArtsBuff] = Bdat::getMember(wrapper.unknown00, "ArtsBuff"); }

u32 getArtsBlArtsBuff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlArtsBuff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlArtsBuff], id, 1).valueU8;
}

void initArtsBlFlagcommon(const CBdatWrapper &wrapper) {
  s_members[ArtsBlFlagcommon] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsBlFlagcommonFlag] = Bdat::getMember(wrapper.unknown00, "common");
}

bool isArtsBlFlagcommon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlFlagcommon] == nullptr || s_members[ArtsBlFlagcommonFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlFlagcommon], id, s_members[ArtsBlFlagcommonFlag]) != 0;
}

void initArtsBlFlagPierce(const CBdatWrapper &wrapper) {
  s_members[ArtsBlFlagPierce] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsBlFlagPierceFlag] = Bdat::getMember(wrapper.unknown00, "Pierce");
}

bool isArtsBlFlagPierce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlFlagPierce] == nullptr || s_members[ArtsBlFlagPierceFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlFlagPierce], id, s_members[ArtsBlFlagPierceFlag]) != 0;
}

void initArtsBlTarget(const CBdatWrapper &wrapper) { s_members[ArtsBlTarget] = Bdat::getMember(wrapper.unknown00, "Target"); }

u32 getArtsBlTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlTarget] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlTarget], id, 1).valueU8;
}

void initArtsBlDistance(const CBdatWrapper &wrapper) { s_members[ArtsBlDistance] = Bdat::getMember(wrapper.unknown00, "Distance"); }

u32 getArtsBlDistance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDistance] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDistance], id, 2).valueU16;
}

void initArtsBlRangeType(const CBdatWrapper &wrapper) { s_members[ArtsBlRangeType] = Bdat::getMember(wrapper.unknown00, "RangeType"); }

u32 getArtsBlRangeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlRangeType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlRangeType], id, 1).valueU8;
}

void initArtsBlRadius(const CBdatWrapper &wrapper) { s_members[ArtsBlRadius] = Bdat::getMember(wrapper.unknown00, "Radius"); }

u32 getArtsBlRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlRadius] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlRadius], id, 2).valueU16;
}

void initArtsBlLength(const CBdatWrapper &wrapper) { s_members[ArtsBlLength] = Bdat::getMember(wrapper.unknown00, "Length"); }

u32 getArtsBlLength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlLength] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlLength], id, 2).valueU16;
}

void initArtsBlAtr(const CBdatWrapper &wrapper) { s_members[ArtsBlAtr] = Bdat::getMember(wrapper.unknown00, "Atr"); }

u32 getArtsBlAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlAtr] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlAtr], id, 1).valueU8;
}

void initArtsBlHate(const CBdatWrapper &wrapper) { s_members[ArtsBlHate] = Bdat::getMember(wrapper.unknown00, "Hate"); }

s32 getArtsBlHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHate] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHate], id, 4).valueS8;
}

void initArtsBlHitRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlHitRevise] = Bdat::getMember(wrapper.unknown00, "HitRevise"); }

s32 getArtsBlHitRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitRevise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitRevise], id, 4).valueS8;
}

void initArtsBlCriRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlCriRevise] = Bdat::getMember(wrapper.unknown00, "CriRevise"); }

s32 getArtsBlCriRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlCriRevise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlCriRevise], id, 4).valueS8;
}

void initArtsBlBulletID(const CBdatWrapper &wrapper) { s_members[ArtsBlBulletID] = Bdat::getMember(wrapper.unknown00, "BulletID"); }

u32 getArtsBlBulletID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBulletID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBulletID], id, 2).valueU16;
}

void initArtsBlBulletNum(const CBdatWrapper &wrapper) { s_members[ArtsBlBulletNum] = Bdat::getMember(wrapper.unknown00, "BulletNum"); }

u32 getArtsBlBulletNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBulletNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBulletNum], id, 1).valueU8;
}

void initArtsBlHitFrm1(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm1] = Bdat::getMember(wrapper.unknown00, "HitFrm1"); }

u32 getArtsBlHitFrm1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm1], id, 1).valueU8;
}

void initArtsBlHitFrm2(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm2] = Bdat::getMember(wrapper.unknown00, "HitFrm2"); }

u32 getArtsBlHitFrm2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm2], id, 1).valueU8;
}

void initArtsBlHitFrm3(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm3] = Bdat::getMember(wrapper.unknown00, "HitFrm3"); }

u32 getArtsBlHitFrm3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm3], id, 1).valueU8;
}

void initArtsBlHitFrm4(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm4] = Bdat::getMember(wrapper.unknown00, "HitFrm4"); }

u32 getArtsBlHitFrm4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm4], id, 1).valueU8;
}

void initArtsBlHitFrm5(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm5] = Bdat::getMember(wrapper.unknown00, "HitFrm5"); }

u32 getArtsBlHitFrm5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm5], id, 1).valueU8;
}

void initArtsBlHitFrm6(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm6] = Bdat::getMember(wrapper.unknown00, "HitFrm6"); }

u32 getArtsBlHitFrm6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm6], id, 1).valueU8;
}

void initArtsBlHitFrm7(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm7] = Bdat::getMember(wrapper.unknown00, "HitFrm7"); }

u32 getArtsBlHitFrm7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm7], id, 1).valueU8;
}

void initArtsBlHitFrm8(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm8] = Bdat::getMember(wrapper.unknown00, "HitFrm8"); }

u32 getArtsBlHitFrm8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm8], id, 1).valueU8;
}

void initArtsBlHitFrm9(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm9] = Bdat::getMember(wrapper.unknown00, "HitFrm9"); }

u32 getArtsBlHitFrm9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm9], id, 1).valueU8;
}

void initArtsBlHitFrm10(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm10] = Bdat::getMember(wrapper.unknown00, "HitFrm10"); }

u32 getArtsBlHitFrm10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm10], id, 1).valueU8;
}

void initArtsBlHitFrm11(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm11] = Bdat::getMember(wrapper.unknown00, "HitFrm11"); }

u32 getArtsBlHitFrm11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm11], id, 1).valueU8;
}

void initArtsBlHitFrm12(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm12] = Bdat::getMember(wrapper.unknown00, "HitFrm12"); }

u32 getArtsBlHitFrm12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm12], id, 1).valueU8;
}

void initArtsBlHitFrm13(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm13] = Bdat::getMember(wrapper.unknown00, "HitFrm13"); }

u32 getArtsBlHitFrm13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm13], id, 1).valueU8;
}

void initArtsBlHitFrm14(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm14] = Bdat::getMember(wrapper.unknown00, "HitFrm14"); }

u32 getArtsBlHitFrm14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm14], id, 1).valueU8;
}

void initArtsBlHitFrm15(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm15] = Bdat::getMember(wrapper.unknown00, "HitFrm15"); }

u32 getArtsBlHitFrm15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm15], id, 1).valueU8;
}

void initArtsBlHitFrm16(const CBdatWrapper &wrapper) { s_members[ArtsBlHitFrm16] = Bdat::getMember(wrapper.unknown00, "HitFrm16"); }

u32 getArtsBlHitFrm16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitFrm16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitFrm16], id, 1).valueU8;
}

void initArtsBlEfp1(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp1] = Bdat::getMember(wrapper.unknown00, "Efp1"); }

u32 getArtsBlEfp1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp1], id, 1).valueU8;
}

void initArtsBlEfp2(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp2] = Bdat::getMember(wrapper.unknown00, "Efp2"); }

u32 getArtsBlEfp2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp2], id, 1).valueU8;
}

void initArtsBlEfp3(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp3] = Bdat::getMember(wrapper.unknown00, "Efp3"); }

u32 getArtsBlEfp3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp3], id, 1).valueU8;
}

void initArtsBlEfp4(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp4] = Bdat::getMember(wrapper.unknown00, "Efp4"); }

u32 getArtsBlEfp4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp4], id, 1).valueU8;
}

void initArtsBlEfp5(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp5] = Bdat::getMember(wrapper.unknown00, "Efp5"); }

u32 getArtsBlEfp5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp5], id, 1).valueU8;
}

void initArtsBlEfp6(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp6] = Bdat::getMember(wrapper.unknown00, "Efp6"); }

u32 getArtsBlEfp6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp6], id, 1).valueU8;
}

void initArtsBlEfp7(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp7] = Bdat::getMember(wrapper.unknown00, "Efp7"); }

u32 getArtsBlEfp7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp7], id, 1).valueU8;
}

void initArtsBlEfp8(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp8] = Bdat::getMember(wrapper.unknown00, "Efp8"); }

u32 getArtsBlEfp8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp8], id, 1).valueU8;
}

void initArtsBlEfp9(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp9] = Bdat::getMember(wrapper.unknown00, "Efp9"); }

u32 getArtsBlEfp9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp9], id, 1).valueU8;
}

void initArtsBlEfp10(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp10] = Bdat::getMember(wrapper.unknown00, "Efp10"); }

u32 getArtsBlEfp10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp10], id, 1).valueU8;
}

void initArtsBlEfp11(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp11] = Bdat::getMember(wrapper.unknown00, "Efp11"); }

u32 getArtsBlEfp11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp11], id, 1).valueU8;
}

void initArtsBlEfp12(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp12] = Bdat::getMember(wrapper.unknown00, "Efp12"); }

u32 getArtsBlEfp12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp12], id, 1).valueU8;
}

void initArtsBlEfp13(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp13] = Bdat::getMember(wrapper.unknown00, "Efp13"); }

u32 getArtsBlEfp13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp13], id, 1).valueU8;
}

void initArtsBlEfp14(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp14] = Bdat::getMember(wrapper.unknown00, "Efp14"); }

u32 getArtsBlEfp14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp14], id, 1).valueU8;
}

void initArtsBlEfp15(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp15] = Bdat::getMember(wrapper.unknown00, "Efp15"); }

u32 getArtsBlEfp15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp15], id, 1).valueU8;
}

void initArtsBlEfp16(const CBdatWrapper &wrapper) { s_members[ArtsBlEfp16] = Bdat::getMember(wrapper.unknown00, "Efp16"); }

u32 getArtsBlEfp16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEfp16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEfp16], id, 1).valueU8;
}

void initArtsBlHitDirID1(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID1] = Bdat::getMember(wrapper.unknown00, "HitDirID1"); }

u32 getArtsBlHitDirID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID1], id, 1).valueU8;
}

void initArtsBlHitDirID2(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID2] = Bdat::getMember(wrapper.unknown00, "HitDirID2"); }

u32 getArtsBlHitDirID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID2], id, 1).valueU8;
}

void initArtsBlHitDirID3(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID3] = Bdat::getMember(wrapper.unknown00, "HitDirID3"); }

u32 getArtsBlHitDirID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID3], id, 1).valueU8;
}

void initArtsBlHitDirID4(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID4] = Bdat::getMember(wrapper.unknown00, "HitDirID4"); }

u32 getArtsBlHitDirID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID4], id, 1).valueU8;
}

void initArtsBlHitDirID5(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID5] = Bdat::getMember(wrapper.unknown00, "HitDirID5"); }

u32 getArtsBlHitDirID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID5], id, 1).valueU8;
}

void initArtsBlHitDirID6(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID6] = Bdat::getMember(wrapper.unknown00, "HitDirID6"); }

u32 getArtsBlHitDirID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID6], id, 1).valueU8;
}

void initArtsBlHitDirID7(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID7] = Bdat::getMember(wrapper.unknown00, "HitDirID7"); }

u32 getArtsBlHitDirID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID7], id, 1).valueU8;
}

void initArtsBlHitDirID8(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID8] = Bdat::getMember(wrapper.unknown00, "HitDirID8"); }

u32 getArtsBlHitDirID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID8], id, 1).valueU8;
}

void initArtsBlHitDirID9(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID9] = Bdat::getMember(wrapper.unknown00, "HitDirID9"); }

u32 getArtsBlHitDirID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID9], id, 1).valueU8;
}

void initArtsBlHitDirID10(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID10] = Bdat::getMember(wrapper.unknown00, "HitDirID10"); }

u32 getArtsBlHitDirID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID10], id, 1).valueU8;
}

void initArtsBlHitDirID11(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID11] = Bdat::getMember(wrapper.unknown00, "HitDirID11"); }

u32 getArtsBlHitDirID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID11], id, 1).valueU8;
}

void initArtsBlHitDirID12(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID12] = Bdat::getMember(wrapper.unknown00, "HitDirID12"); }

u32 getArtsBlHitDirID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID12], id, 1).valueU8;
}

void initArtsBlHitDirID13(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID13] = Bdat::getMember(wrapper.unknown00, "HitDirID13"); }

u32 getArtsBlHitDirID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID13], id, 1).valueU8;
}

void initArtsBlHitDirID14(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID14] = Bdat::getMember(wrapper.unknown00, "HitDirID14"); }

u32 getArtsBlHitDirID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID14], id, 1).valueU8;
}

void initArtsBlHitDirID15(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID15] = Bdat::getMember(wrapper.unknown00, "HitDirID15"); }

u32 getArtsBlHitDirID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID15], id, 1).valueU8;
}

void initArtsBlHitDirID16(const CBdatWrapper &wrapper) { s_members[ArtsBlHitDirID16] = Bdat::getMember(wrapper.unknown00, "HitDirID16"); }

u32 getArtsBlHitDirID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlHitDirID16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlHitDirID16], id, 1).valueU8;
}

void initArtsBlDmgRt1(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt1] = Bdat::getMember(wrapper.unknown00, "DmgRt1"); }

u32 getArtsBlDmgRt1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt1], id, 1).valueU8;
}

void initArtsBlDmgRt2(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt2] = Bdat::getMember(wrapper.unknown00, "DmgRt2"); }

u32 getArtsBlDmgRt2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt2], id, 1).valueU8;
}

void initArtsBlDmgRt3(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt3] = Bdat::getMember(wrapper.unknown00, "DmgRt3"); }

u32 getArtsBlDmgRt3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt3], id, 1).valueU8;
}

void initArtsBlDmgRt4(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt4] = Bdat::getMember(wrapper.unknown00, "DmgRt4"); }

u32 getArtsBlDmgRt4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt4], id, 1).valueU8;
}

void initArtsBlDmgRt5(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt5] = Bdat::getMember(wrapper.unknown00, "DmgRt5"); }

u32 getArtsBlDmgRt5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt5], id, 1).valueU8;
}

void initArtsBlDmgRt6(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt6] = Bdat::getMember(wrapper.unknown00, "DmgRt6"); }

u32 getArtsBlDmgRt6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt6], id, 1).valueU8;
}

void initArtsBlDmgRt7(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt7] = Bdat::getMember(wrapper.unknown00, "DmgRt7"); }

u32 getArtsBlDmgRt7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt7], id, 1).valueU8;
}

void initArtsBlDmgRt8(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt8] = Bdat::getMember(wrapper.unknown00, "DmgRt8"); }

u32 getArtsBlDmgRt8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt8], id, 1).valueU8;
}

void initArtsBlDmgRt9(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt9] = Bdat::getMember(wrapper.unknown00, "DmgRt9"); }

u32 getArtsBlDmgRt9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt9], id, 1).valueU8;
}

void initArtsBlDmgRt10(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt10] = Bdat::getMember(wrapper.unknown00, "DmgRt10"); }

u32 getArtsBlDmgRt10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt10], id, 1).valueU8;
}

void initArtsBlDmgRt11(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt11] = Bdat::getMember(wrapper.unknown00, "DmgRt11"); }

u32 getArtsBlDmgRt11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt11], id, 1).valueU8;
}

void initArtsBlDmgRt12(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt12] = Bdat::getMember(wrapper.unknown00, "DmgRt12"); }

u32 getArtsBlDmgRt12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt12], id, 1).valueU8;
}

void initArtsBlDmgRt13(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt13] = Bdat::getMember(wrapper.unknown00, "DmgRt13"); }

u32 getArtsBlDmgRt13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt13], id, 1).valueU8;
}

void initArtsBlDmgRt14(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt14] = Bdat::getMember(wrapper.unknown00, "DmgRt14"); }

u32 getArtsBlDmgRt14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt14], id, 1).valueU8;
}

void initArtsBlDmgRt15(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt15] = Bdat::getMember(wrapper.unknown00, "DmgRt15"); }

u32 getArtsBlDmgRt15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt15], id, 1).valueU8;
}

void initArtsBlDmgRt16(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgRt16] = Bdat::getMember(wrapper.unknown00, "DmgRt16"); }

u32 getArtsBlDmgRt16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgRt16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgRt16], id, 1).valueU8;
}

void initArtsBlReAct1(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct1] = Bdat::getMember(wrapper.unknown00, "ReAct1"); }

u32 getArtsBlReAct1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct1], id, 1).valueU8;
}

void initArtsBlReAct2(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct2] = Bdat::getMember(wrapper.unknown00, "ReAct2"); }

u32 getArtsBlReAct2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct2], id, 1).valueU8;
}

void initArtsBlReAct3(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct3] = Bdat::getMember(wrapper.unknown00, "ReAct3"); }

u32 getArtsBlReAct3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct3], id, 1).valueU8;
}

void initArtsBlReAct4(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct4] = Bdat::getMember(wrapper.unknown00, "ReAct4"); }

u32 getArtsBlReAct4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct4], id, 1).valueU8;
}

void initArtsBlReAct5(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct5] = Bdat::getMember(wrapper.unknown00, "ReAct5"); }

u32 getArtsBlReAct5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct5], id, 1).valueU8;
}

void initArtsBlReAct6(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct6] = Bdat::getMember(wrapper.unknown00, "ReAct6"); }

u32 getArtsBlReAct6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct6], id, 1).valueU8;
}

void initArtsBlReAct7(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct7] = Bdat::getMember(wrapper.unknown00, "ReAct7"); }

u32 getArtsBlReAct7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct7], id, 1).valueU8;
}

void initArtsBlReAct8(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct8] = Bdat::getMember(wrapper.unknown00, "ReAct8"); }

u32 getArtsBlReAct8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct8], id, 1).valueU8;
}

void initArtsBlReAct9(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct9] = Bdat::getMember(wrapper.unknown00, "ReAct9"); }

u32 getArtsBlReAct9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct9], id, 1).valueU8;
}

void initArtsBlReAct10(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct10] = Bdat::getMember(wrapper.unknown00, "ReAct10"); }

u32 getArtsBlReAct10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct10], id, 1).valueU8;
}

void initArtsBlReAct11(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct11] = Bdat::getMember(wrapper.unknown00, "ReAct11"); }

u32 getArtsBlReAct11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct11], id, 1).valueU8;
}

void initArtsBlReAct12(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct12] = Bdat::getMember(wrapper.unknown00, "ReAct12"); }

u32 getArtsBlReAct12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct12], id, 1).valueU8;
}

void initArtsBlReAct13(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct13] = Bdat::getMember(wrapper.unknown00, "ReAct13"); }

u32 getArtsBlReAct13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct13], id, 1).valueU8;
}

void initArtsBlReAct14(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct14] = Bdat::getMember(wrapper.unknown00, "ReAct14"); }

u32 getArtsBlReAct14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct14], id, 1).valueU8;
}

void initArtsBlReAct15(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct15] = Bdat::getMember(wrapper.unknown00, "ReAct15"); }

u32 getArtsBlReAct15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct15], id, 1).valueU8;
}

void initArtsBlReAct16(const CBdatWrapper &wrapper) { s_members[ArtsBlReAct16] = Bdat::getMember(wrapper.unknown00, "ReAct16"); }

u32 getArtsBlReAct16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlReAct16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlReAct16], id, 1).valueU8;
}

void initArtsBlDmgMgn1(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn1] = Bdat::getMember(wrapper.unknown00, "DmgMgn1"); }

u32 getArtsBlDmgMgn1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn1], id, 2).valueU16;
}

void initArtsBlDmgMgn2(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn2] = Bdat::getMember(wrapper.unknown00, "DmgMgn2"); }

u32 getArtsBlDmgMgn2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn2], id, 2).valueU16;
}

void initArtsBlDmgMgn3(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn3] = Bdat::getMember(wrapper.unknown00, "DmgMgn3"); }

u32 getArtsBlDmgMgn3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn3], id, 2).valueU16;
}

void initArtsBlDmgMgn4(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn4] = Bdat::getMember(wrapper.unknown00, "DmgMgn4"); }

u32 getArtsBlDmgMgn4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn4], id, 2).valueU16;
}

void initArtsBlDmgMgn5(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn5] = Bdat::getMember(wrapper.unknown00, "DmgMgn5"); }

u32 getArtsBlDmgMgn5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn5], id, 2).valueU16;
}

void initArtsBlDmgMgn6(const CBdatWrapper &wrapper) { s_members[ArtsBlDmgMgn6] = Bdat::getMember(wrapper.unknown00, "DmgMgn6"); }

u32 getArtsBlDmgMgn6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlDmgMgn6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlDmgMgn6], id, 2).valueU16;
}

void initArtsBlAtrNum(const CBdatWrapper &wrapper) { s_members[ArtsBlAtrNum] = Bdat::getMember(wrapper.unknown00, "AtrNum"); }

u32 getArtsBlAtrNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlAtrNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlAtrNum], id, 1).valueU8;
}

void initArtsBlEnhance1(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance1] = Bdat::getMember(wrapper.unknown00, "Enhance1"); }

u32 getArtsBlEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance1], id, 2).valueU16;
}

void initArtsBlEnhance2(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance2] = Bdat::getMember(wrapper.unknown00, "Enhance2"); }

u32 getArtsBlEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance2], id, 2).valueU16;
}

void initArtsBlEnhance3(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance3] = Bdat::getMember(wrapper.unknown00, "Enhance3"); }

u32 getArtsBlEnhance3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance3], id, 2).valueU16;
}

void initArtsBlEnhance4(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance4] = Bdat::getMember(wrapper.unknown00, "Enhance4"); }

u32 getArtsBlEnhance4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance4], id, 2).valueU16;
}

void initArtsBlEnhance5(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance5] = Bdat::getMember(wrapper.unknown00, "Enhance5"); }

u32 getArtsBlEnhance5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance5], id, 2).valueU16;
}

void initArtsBlEnhance6(const CBdatWrapper &wrapper) { s_members[ArtsBlEnhance6] = Bdat::getMember(wrapper.unknown00, "Enhance6"); }

u32 getArtsBlEnhance6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlEnhance6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlEnhance6], id, 2).valueU16;
}

void initArtsBlBtnType(const CBdatWrapper &wrapper) { s_members[ArtsBlBtnType] = Bdat::getMember(wrapper.unknown00, "BtnType"); }

u32 getArtsBlBtnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBtnType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBtnType], id, 1).valueU8;
}

void initArtsBlBtnChal1(const CBdatWrapper &wrapper) { s_members[ArtsBlBtnChal1] = Bdat::getMember(wrapper.unknown00, "BtnChal1"); }

u32 getArtsBlBtnChal1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlBtnChal1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlBtnChal1], id, 2).valueU16;
}

void initArtsBlUI(const CBdatWrapper &wrapper) { s_members[ArtsBlUI] = Bdat::getMember(wrapper.unknown00, "UI"); }

u32 getArtsBlUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlUI] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlUI], id, 2).valueU16;
}

void initArtsBlSpName(const CBdatWrapper &wrapper) { s_members[ArtsBlSpName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getArtsBlSpName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpName], id, 2).valueU16;
}

void initArtsBlSpDebugName(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getArtsBlSpDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDebugName], id, 7).valueString;
}

void initArtsBlSpCaption(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCaption] = Bdat::getMember(wrapper.unknown00, "Caption"); }

u32 getArtsBlSpCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCaption] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCaption], id, 2).valueU16;
}

void initArtsBlSpWpnType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpWpnType] = Bdat::getMember(wrapper.unknown00, "WpnType"); }

u32 getArtsBlSpWpnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpWpnType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpWpnType], id, 1).valueU8;
}

void initArtsBlSpCmnBlType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCmnBlType] = Bdat::getMember(wrapper.unknown00, "CmnBlType"); }

u32 getArtsBlSpCmnBlType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCmnBlType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCmnBlType], id, 1).valueU8;
}

void initArtsBlSpActNoDr(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActNoDr] = Bdat::getMember(wrapper.unknown00, "ActNoDr"); }

u32 getArtsBlSpActNoDr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActNoDr] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActNoDr], id, 1).valueU8;
}

void initArtsBlSpActNoBl(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActNoBl] = Bdat::getMember(wrapper.unknown00, "ActNoBl"); }

u32 getArtsBlSpActNoBl(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActNoBl] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActNoBl], id, 1).valueU8;
}

void initArtsBlSpActNoBl2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActNoBl2] = Bdat::getMember(wrapper.unknown00, "ActNoBl2"); }

u32 getArtsBlSpActNoBl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActNoBl2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActNoBl2], id, 1).valueU8;
}

void initArtsBlSpBuddyDr(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBuddyDr] = Bdat::getMember(wrapper.unknown00, "BuddyDr"); }

u32 getArtsBlSpBuddyDr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBuddyDr] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBuddyDr], id, 1).valueU8;
}

void initArtsBlSpAddBl(const CBdatWrapper &wrapper) { s_members[ArtsBlSpAddBl] = Bdat::getMember(wrapper.unknown00, "AddBl"); }

u32 getArtsBlSpAddBl(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpAddBl] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpAddBl], id, 1).valueU8;
}

void initArtsBlSpActType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpActType] = Bdat::getMember(wrapper.unknown00, "ActType"); }

u32 getArtsBlSpActType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpActType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpActType], id, 1).valueU8;
}

void initArtsBlSpPC01(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC01] = Bdat::getMember(wrapper.unknown00, "PC01"); }

u32 getArtsBlSpPC01(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC01] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC01], id, 1).valueU8;
}

void initArtsBlSpPC02(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC02] = Bdat::getMember(wrapper.unknown00, "PC02"); }

u32 getArtsBlSpPC02(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC02] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC02], id, 1).valueU8;
}

void initArtsBlSpPC03(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC03] = Bdat::getMember(wrapper.unknown00, "PC03"); }

u32 getArtsBlSpPC03(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC03] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC03], id, 1).valueU8;
}

void initArtsBlSpPC06(const CBdatWrapper &wrapper) { s_members[ArtsBlSpPC06] = Bdat::getMember(wrapper.unknown00, "PC06"); }

u32 getArtsBlSpPC06(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpPC06] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpPC06], id, 1).valueU8;
}

void initArtsBlSpArtsType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpArtsType] = Bdat::getMember(wrapper.unknown00, "ArtsType"); }

u32 getArtsBlSpArtsType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpArtsType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpArtsType], id, 1).valueU8;
}

void initArtsBlSpArtsBuff(const CBdatWrapper &wrapper) { s_members[ArtsBlSpArtsBuff] = Bdat::getMember(wrapper.unknown00, "ArtsBuff"); }

u32 getArtsBlSpArtsBuff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpArtsBuff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpArtsBuff], id, 1).valueU8;
}

void initArtsBlSpFlagPierce(const CBdatWrapper &wrapper) {
  s_members[ArtsBlSpFlagPierce] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsBlSpFlagPierceFlag] = Bdat::getMember(wrapper.unknown00, "Pierce");
}

bool isArtsBlSpFlagPierce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpFlagPierce] == nullptr || s_members[ArtsBlSpFlagPierceFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlSpFlagPierce], id, s_members[ArtsBlSpFlagPierceFlag]) != 0;
}

void initArtsBlSpFlagNoMove(const CBdatWrapper &wrapper) {
  s_members[ArtsBlSpFlagNoMove] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[ArtsBlSpFlagNoMoveFlag] = Bdat::getMember(wrapper.unknown00, "NoMove");
}

bool isArtsBlSpFlagNoMove(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpFlagNoMove] == nullptr || s_members[ArtsBlSpFlagNoMoveFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ArtsBlSpFlagNoMove], id, s_members[ArtsBlSpFlagNoMoveFlag]) != 0;
}

void initArtsBlSpTarget(const CBdatWrapper &wrapper) { s_members[ArtsBlSpTarget] = Bdat::getMember(wrapper.unknown00, "Target"); }

u32 getArtsBlSpTarget(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpTarget] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpTarget], id, 1).valueU8;
}

void initArtsBlSpDistance(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDistance] = Bdat::getMember(wrapper.unknown00, "Distance"); }

u32 getArtsBlSpDistance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDistance] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDistance], id, 2).valueU16;
}

void initArtsBlSpRangeType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpRangeType] = Bdat::getMember(wrapper.unknown00, "RangeType"); }

u32 getArtsBlSpRangeType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpRangeType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpRangeType], id, 1).valueU8;
}

void initArtsBlSpRadius(const CBdatWrapper &wrapper) { s_members[ArtsBlSpRadius] = Bdat::getMember(wrapper.unknown00, "Radius"); }

u32 getArtsBlSpRadius(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpRadius] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpRadius], id, 2).valueU16;
}

void initArtsBlSpLength(const CBdatWrapper &wrapper) { s_members[ArtsBlSpLength] = Bdat::getMember(wrapper.unknown00, "Length"); }

u32 getArtsBlSpLength(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpLength] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpLength], id, 2).valueU16;
}

void initArtsBlSpAtr(const CBdatWrapper &wrapper) { s_members[ArtsBlSpAtr] = Bdat::getMember(wrapper.unknown00, "Atr"); }

u32 getArtsBlSpAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpAtr] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpAtr], id, 1).valueU8;
}

void initArtsBlSpHate(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHate] = Bdat::getMember(wrapper.unknown00, "Hate"); }

s32 getArtsBlSpHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHate] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHate], id, 4).valueS8;
}

void initArtsBlSpHitRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitRevise] = Bdat::getMember(wrapper.unknown00, "HitRevise"); }

s32 getArtsBlSpHitRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitRevise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitRevise], id, 4).valueS8;
}

void initArtsBlSpCriRevise(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCriRevise] = Bdat::getMember(wrapper.unknown00, "CriRevise"); }

s32 getArtsBlSpCriRevise(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCriRevise] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCriRevise], id, 4).valueS8;
}

void initArtsBlSpBulletID(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBulletID] = Bdat::getMember(wrapper.unknown00, "BulletID"); }

u32 getArtsBlSpBulletID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBulletID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBulletID], id, 2).valueU16;
}

void initArtsBlSpBulletEffID(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBulletEffID] = Bdat::getMember(wrapper.unknown00, "BulletEffID"); }

u32 getArtsBlSpBulletEffID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBulletEffID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBulletEffID], id, 2).valueU16;
}

void initArtsBlSpBulletNum(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBulletNum] = Bdat::getMember(wrapper.unknown00, "BulletNum"); }

u32 getArtsBlSpBulletNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBulletNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBulletNum], id, 1).valueU8;
}

void initArtsBlSpHitFrm1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm1] = Bdat::getMember(wrapper.unknown00, "HitFrm1"); }

u32 getArtsBlSpHitFrm1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm1], id, 1).valueU8;
}

void initArtsBlSpHitFrm2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm2] = Bdat::getMember(wrapper.unknown00, "HitFrm2"); }

u32 getArtsBlSpHitFrm2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm2], id, 1).valueU8;
}

void initArtsBlSpHitFrm3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm3] = Bdat::getMember(wrapper.unknown00, "HitFrm3"); }

u32 getArtsBlSpHitFrm3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm3], id, 1).valueU8;
}

void initArtsBlSpHitFrm4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm4] = Bdat::getMember(wrapper.unknown00, "HitFrm4"); }

u32 getArtsBlSpHitFrm4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm4], id, 1).valueU8;
}

void initArtsBlSpHitFrm5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm5] = Bdat::getMember(wrapper.unknown00, "HitFrm5"); }

u32 getArtsBlSpHitFrm5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm5], id, 1).valueU8;
}

void initArtsBlSpHitFrm6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm6] = Bdat::getMember(wrapper.unknown00, "HitFrm6"); }

u32 getArtsBlSpHitFrm6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm6], id, 1).valueU8;
}

void initArtsBlSpHitFrm7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm7] = Bdat::getMember(wrapper.unknown00, "HitFrm7"); }

u32 getArtsBlSpHitFrm7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm7], id, 1).valueU8;
}

void initArtsBlSpHitFrm8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm8] = Bdat::getMember(wrapper.unknown00, "HitFrm8"); }

u32 getArtsBlSpHitFrm8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm8], id, 1).valueU8;
}

void initArtsBlSpHitFrm9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm9] = Bdat::getMember(wrapper.unknown00, "HitFrm9"); }

u32 getArtsBlSpHitFrm9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm9], id, 1).valueU8;
}

void initArtsBlSpHitFrm10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm10] = Bdat::getMember(wrapper.unknown00, "HitFrm10"); }

u32 getArtsBlSpHitFrm10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm10], id, 1).valueU8;
}

void initArtsBlSpHitFrm11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm11] = Bdat::getMember(wrapper.unknown00, "HitFrm11"); }

u32 getArtsBlSpHitFrm11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm11], id, 1).valueU8;
}

void initArtsBlSpHitFrm12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm12] = Bdat::getMember(wrapper.unknown00, "HitFrm12"); }

u32 getArtsBlSpHitFrm12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm12], id, 1).valueU8;
}

void initArtsBlSpHitFrm13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm13] = Bdat::getMember(wrapper.unknown00, "HitFrm13"); }

u32 getArtsBlSpHitFrm13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm13], id, 1).valueU8;
}

void initArtsBlSpHitFrm14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm14] = Bdat::getMember(wrapper.unknown00, "HitFrm14"); }

u32 getArtsBlSpHitFrm14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm14], id, 1).valueU8;
}

void initArtsBlSpHitFrm15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm15] = Bdat::getMember(wrapper.unknown00, "HitFrm15"); }

u32 getArtsBlSpHitFrm15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm15], id, 1).valueU8;
}

void initArtsBlSpHitFrm16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitFrm16] = Bdat::getMember(wrapper.unknown00, "HitFrm16"); }

u32 getArtsBlSpHitFrm16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitFrm16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitFrm16], id, 1).valueU8;
}

void initArtsBlSpEfp1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp1] = Bdat::getMember(wrapper.unknown00, "Efp1"); }

u32 getArtsBlSpEfp1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp1], id, 1).valueU8;
}

void initArtsBlSpEfp2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp2] = Bdat::getMember(wrapper.unknown00, "Efp2"); }

u32 getArtsBlSpEfp2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp2], id, 1).valueU8;
}

void initArtsBlSpEfp3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp3] = Bdat::getMember(wrapper.unknown00, "Efp3"); }

u32 getArtsBlSpEfp3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp3], id, 1).valueU8;
}

void initArtsBlSpEfp4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp4] = Bdat::getMember(wrapper.unknown00, "Efp4"); }

u32 getArtsBlSpEfp4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp4], id, 1).valueU8;
}

void initArtsBlSpEfp5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp5] = Bdat::getMember(wrapper.unknown00, "Efp5"); }

u32 getArtsBlSpEfp5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp5], id, 1).valueU8;
}

void initArtsBlSpEfp6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp6] = Bdat::getMember(wrapper.unknown00, "Efp6"); }

u32 getArtsBlSpEfp6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp6], id, 1).valueU8;
}

void initArtsBlSpEfp7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp7] = Bdat::getMember(wrapper.unknown00, "Efp7"); }

u32 getArtsBlSpEfp7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp7], id, 1).valueU8;
}

void initArtsBlSpEfp8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp8] = Bdat::getMember(wrapper.unknown00, "Efp8"); }

u32 getArtsBlSpEfp8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp8], id, 1).valueU8;
}

void initArtsBlSpEfp9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp9] = Bdat::getMember(wrapper.unknown00, "Efp9"); }

u32 getArtsBlSpEfp9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp9], id, 1).valueU8;
}

void initArtsBlSpEfp10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp10] = Bdat::getMember(wrapper.unknown00, "Efp10"); }

u32 getArtsBlSpEfp10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp10], id, 1).valueU8;
}

void initArtsBlSpEfp11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp11] = Bdat::getMember(wrapper.unknown00, "Efp11"); }

u32 getArtsBlSpEfp11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp11], id, 1).valueU8;
}

void initArtsBlSpEfp12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp12] = Bdat::getMember(wrapper.unknown00, "Efp12"); }

u32 getArtsBlSpEfp12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp12], id, 1).valueU8;
}

void initArtsBlSpEfp13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp13] = Bdat::getMember(wrapper.unknown00, "Efp13"); }

u32 getArtsBlSpEfp13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp13], id, 1).valueU8;
}

void initArtsBlSpEfp14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp14] = Bdat::getMember(wrapper.unknown00, "Efp14"); }

u32 getArtsBlSpEfp14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp14], id, 1).valueU8;
}

void initArtsBlSpEfp15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp15] = Bdat::getMember(wrapper.unknown00, "Efp15"); }

u32 getArtsBlSpEfp15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp15], id, 1).valueU8;
}

void initArtsBlSpEfp16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEfp16] = Bdat::getMember(wrapper.unknown00, "Efp16"); }

u32 getArtsBlSpEfp16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEfp16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEfp16], id, 1).valueU8;
}

void initArtsBlSpHitDirID1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID1] = Bdat::getMember(wrapper.unknown00, "HitDirID1"); }

u32 getArtsBlSpHitDirID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID1], id, 1).valueU8;
}

void initArtsBlSpHitDirID2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID2] = Bdat::getMember(wrapper.unknown00, "HitDirID2"); }

u32 getArtsBlSpHitDirID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID2], id, 1).valueU8;
}

void initArtsBlSpHitDirID3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID3] = Bdat::getMember(wrapper.unknown00, "HitDirID3"); }

u32 getArtsBlSpHitDirID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID3], id, 1).valueU8;
}

void initArtsBlSpHitDirID4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID4] = Bdat::getMember(wrapper.unknown00, "HitDirID4"); }

u32 getArtsBlSpHitDirID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID4], id, 1).valueU8;
}

void initArtsBlSpHitDirID5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID5] = Bdat::getMember(wrapper.unknown00, "HitDirID5"); }

u32 getArtsBlSpHitDirID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID5], id, 1).valueU8;
}

void initArtsBlSpHitDirID6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID6] = Bdat::getMember(wrapper.unknown00, "HitDirID6"); }

u32 getArtsBlSpHitDirID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID6], id, 1).valueU8;
}

void initArtsBlSpHitDirID7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID7] = Bdat::getMember(wrapper.unknown00, "HitDirID7"); }

u32 getArtsBlSpHitDirID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID7], id, 1).valueU8;
}

void initArtsBlSpHitDirID8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID8] = Bdat::getMember(wrapper.unknown00, "HitDirID8"); }

u32 getArtsBlSpHitDirID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID8], id, 1).valueU8;
}

void initArtsBlSpHitDirID9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID9] = Bdat::getMember(wrapper.unknown00, "HitDirID9"); }

u32 getArtsBlSpHitDirID9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID9], id, 1).valueU8;
}

void initArtsBlSpHitDirID10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID10] = Bdat::getMember(wrapper.unknown00, "HitDirID10"); }

u32 getArtsBlSpHitDirID10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID10], id, 1).valueU8;
}

void initArtsBlSpHitDirID11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID11] = Bdat::getMember(wrapper.unknown00, "HitDirID11"); }

u32 getArtsBlSpHitDirID11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID11], id, 1).valueU8;
}

void initArtsBlSpHitDirID12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID12] = Bdat::getMember(wrapper.unknown00, "HitDirID12"); }

u32 getArtsBlSpHitDirID12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID12], id, 1).valueU8;
}

void initArtsBlSpHitDirID13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID13] = Bdat::getMember(wrapper.unknown00, "HitDirID13"); }

u32 getArtsBlSpHitDirID13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID13], id, 1).valueU8;
}

void initArtsBlSpHitDirID14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID14] = Bdat::getMember(wrapper.unknown00, "HitDirID14"); }

u32 getArtsBlSpHitDirID14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID14], id, 1).valueU8;
}

void initArtsBlSpHitDirID15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID15] = Bdat::getMember(wrapper.unknown00, "HitDirID15"); }

u32 getArtsBlSpHitDirID15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID15], id, 1).valueU8;
}

void initArtsBlSpHitDirID16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitDirID16] = Bdat::getMember(wrapper.unknown00, "HitDirID16"); }

u32 getArtsBlSpHitDirID16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitDirID16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitDirID16], id, 1).valueU8;
}

void initArtsBlSpDmgRt1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt1] = Bdat::getMember(wrapper.unknown00, "DmgRt1"); }

u32 getArtsBlSpDmgRt1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt1], id, 1).valueU8;
}

void initArtsBlSpDmgRt2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt2] = Bdat::getMember(wrapper.unknown00, "DmgRt2"); }

u32 getArtsBlSpDmgRt2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt2], id, 1).valueU8;
}

void initArtsBlSpDmgRt3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt3] = Bdat::getMember(wrapper.unknown00, "DmgRt3"); }

u32 getArtsBlSpDmgRt3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt3], id, 1).valueU8;
}

void initArtsBlSpDmgRt4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt4] = Bdat::getMember(wrapper.unknown00, "DmgRt4"); }

u32 getArtsBlSpDmgRt4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt4], id, 1).valueU8;
}

void initArtsBlSpDmgRt5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt5] = Bdat::getMember(wrapper.unknown00, "DmgRt5"); }

u32 getArtsBlSpDmgRt5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt5], id, 1).valueU8;
}

void initArtsBlSpDmgRt6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt6] = Bdat::getMember(wrapper.unknown00, "DmgRt6"); }

u32 getArtsBlSpDmgRt6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt6], id, 1).valueU8;
}

void initArtsBlSpDmgRt7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt7] = Bdat::getMember(wrapper.unknown00, "DmgRt7"); }

u32 getArtsBlSpDmgRt7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt7], id, 1).valueU8;
}

void initArtsBlSpDmgRt8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt8] = Bdat::getMember(wrapper.unknown00, "DmgRt8"); }

u32 getArtsBlSpDmgRt8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt8], id, 1).valueU8;
}

void initArtsBlSpDmgRt9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt9] = Bdat::getMember(wrapper.unknown00, "DmgRt9"); }

u32 getArtsBlSpDmgRt9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt9], id, 1).valueU8;
}

void initArtsBlSpDmgRt10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt10] = Bdat::getMember(wrapper.unknown00, "DmgRt10"); }

u32 getArtsBlSpDmgRt10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt10], id, 1).valueU8;
}

void initArtsBlSpDmgRt11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt11] = Bdat::getMember(wrapper.unknown00, "DmgRt11"); }

u32 getArtsBlSpDmgRt11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt11], id, 1).valueU8;
}

void initArtsBlSpDmgRt12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt12] = Bdat::getMember(wrapper.unknown00, "DmgRt12"); }

u32 getArtsBlSpDmgRt12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt12], id, 1).valueU8;
}

void initArtsBlSpDmgRt13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt13] = Bdat::getMember(wrapper.unknown00, "DmgRt13"); }

u32 getArtsBlSpDmgRt13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt13], id, 1).valueU8;
}

void initArtsBlSpDmgRt14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt14] = Bdat::getMember(wrapper.unknown00, "DmgRt14"); }

u32 getArtsBlSpDmgRt14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt14], id, 1).valueU8;
}

void initArtsBlSpDmgRt15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt15] = Bdat::getMember(wrapper.unknown00, "DmgRt15"); }

u32 getArtsBlSpDmgRt15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt15], id, 1).valueU8;
}

void initArtsBlSpDmgRt16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgRt16] = Bdat::getMember(wrapper.unknown00, "DmgRt16"); }

u32 getArtsBlSpDmgRt16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgRt16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgRt16], id, 1).valueU8;
}

void initArtsBlSpReAct1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct1] = Bdat::getMember(wrapper.unknown00, "ReAct1"); }

u32 getArtsBlSpReAct1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct1], id, 1).valueU8;
}

void initArtsBlSpReAct2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct2] = Bdat::getMember(wrapper.unknown00, "ReAct2"); }

u32 getArtsBlSpReAct2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct2], id, 1).valueU8;
}

void initArtsBlSpReAct3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct3] = Bdat::getMember(wrapper.unknown00, "ReAct3"); }

u32 getArtsBlSpReAct3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct3], id, 1).valueU8;
}

void initArtsBlSpReAct4(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct4] = Bdat::getMember(wrapper.unknown00, "ReAct4"); }

u32 getArtsBlSpReAct4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct4], id, 1).valueU8;
}

void initArtsBlSpReAct5(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct5] = Bdat::getMember(wrapper.unknown00, "ReAct5"); }

u32 getArtsBlSpReAct5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct5], id, 1).valueU8;
}

void initArtsBlSpReAct6(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct6] = Bdat::getMember(wrapper.unknown00, "ReAct6"); }

u32 getArtsBlSpReAct6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct6] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct6], id, 1).valueU8;
}

void initArtsBlSpReAct7(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct7] = Bdat::getMember(wrapper.unknown00, "ReAct7"); }

u32 getArtsBlSpReAct7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct7] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct7], id, 1).valueU8;
}

void initArtsBlSpReAct8(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct8] = Bdat::getMember(wrapper.unknown00, "ReAct8"); }

u32 getArtsBlSpReAct8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct8] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct8], id, 1).valueU8;
}

void initArtsBlSpReAct9(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct9] = Bdat::getMember(wrapper.unknown00, "ReAct9"); }

u32 getArtsBlSpReAct9(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct9] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct9], id, 1).valueU8;
}

void initArtsBlSpReAct10(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct10] = Bdat::getMember(wrapper.unknown00, "ReAct10"); }

u32 getArtsBlSpReAct10(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct10] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct10], id, 1).valueU8;
}

void initArtsBlSpReAct11(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct11] = Bdat::getMember(wrapper.unknown00, "ReAct11"); }

u32 getArtsBlSpReAct11(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct11] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct11], id, 1).valueU8;
}

void initArtsBlSpReAct12(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct12] = Bdat::getMember(wrapper.unknown00, "ReAct12"); }

u32 getArtsBlSpReAct12(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct12] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct12], id, 1).valueU8;
}

void initArtsBlSpReAct13(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct13] = Bdat::getMember(wrapper.unknown00, "ReAct13"); }

u32 getArtsBlSpReAct13(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct13] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct13], id, 1).valueU8;
}

void initArtsBlSpReAct14(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct14] = Bdat::getMember(wrapper.unknown00, "ReAct14"); }

u32 getArtsBlSpReAct14(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct14] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct14], id, 1).valueU8;
}

void initArtsBlSpReAct15(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct15] = Bdat::getMember(wrapper.unknown00, "ReAct15"); }

u32 getArtsBlSpReAct15(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct15] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct15], id, 1).valueU8;
}

void initArtsBlSpReAct16(const CBdatWrapper &wrapper) { s_members[ArtsBlSpReAct16] = Bdat::getMember(wrapper.unknown00, "ReAct16"); }

u32 getArtsBlSpReAct16(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpReAct16] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpReAct16], id, 1).valueU8;
}

void initArtsBlSpDmgMgn(const CBdatWrapper &wrapper) { s_members[ArtsBlSpDmgMgn] = Bdat::getMember(wrapper.unknown00, "DmgMgn"); }

u32 getArtsBlSpDmgMgn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpDmgMgn] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpDmgMgn], id, 2).valueU16;
}

void initArtsBlSpRecast(const CBdatWrapper &wrapper) { s_members[ArtsBlSpRecast] = Bdat::getMember(wrapper.unknown00, "Recast"); }

u32 getArtsBlSpRecast(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpRecast] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpRecast], id, 2).valueU16;
}

void initArtsBlSpAtrNum(const CBdatWrapper &wrapper) { s_members[ArtsBlSpAtrNum] = Bdat::getMember(wrapper.unknown00, "AtrNum"); }

u32 getArtsBlSpAtrNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpAtrNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpAtrNum], id, 1).valueU8;
}

void initArtsBlSpEnhance(const CBdatWrapper &wrapper) { s_members[ArtsBlSpEnhance] = Bdat::getMember(wrapper.unknown00, "Enhance"); }

u32 getArtsBlSpEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpEnhance] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpEnhance], id, 2).valueU16;
}

void initArtsBlSpBtnType(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBtnType] = Bdat::getMember(wrapper.unknown00, "BtnType"); }

u32 getArtsBlSpBtnType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBtnType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBtnType], id, 1).valueU8;
}

void initArtsBlSpBtnChal1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpBtnChal1] = Bdat::getMember(wrapper.unknown00, "BtnChal1"); }

u32 getArtsBlSpBtnChal1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpBtnChal1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpBtnChal1], id, 2).valueU16;
}

void initArtsBlSpCamera1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCamera1] = Bdat::getMember(wrapper.unknown00, "Camera1"); }

const char *getArtsBlSpCamera1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCamera1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCamera1], id, 7).valueString;
}

void initArtsBlSpCamera2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCamera2] = Bdat::getMember(wrapper.unknown00, "Camera2"); }

const char *getArtsBlSpCamera2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCamera2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCamera2], id, 7).valueString;
}

void initArtsBlSpCamera3(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCamera3] = Bdat::getMember(wrapper.unknown00, "Camera3"); }

const char *getArtsBlSpCamera3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCamera3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCamera3], id, 7).valueString;
}

void initArtsBlSpCameraCT1(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCameraCT1] = Bdat::getMember(wrapper.unknown00, "CameraCT1"); }

u32 getArtsBlSpCameraCT1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCameraCT1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCameraCT1], id, 2).valueU16;
}

void initArtsBlSpCameraCT2(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCameraCT2] = Bdat::getMember(wrapper.unknown00, "CameraCT2"); }

u32 getArtsBlSpCameraCT2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCameraCT2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCameraCT2], id, 2).valueU16;
}

void initArtsBlSpCameraEndf(const CBdatWrapper &wrapper) { s_members[ArtsBlSpCameraEndf] = Bdat::getMember(wrapper.unknown00, "CameraEndf"); }

u32 getArtsBlSpCameraEndf(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpCameraEndf] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpCameraEndf], id, 1).valueU8;
}

void initArtsBlSpHitEff(const CBdatWrapper &wrapper) { s_members[ArtsBlSpHitEff] = Bdat::getMember(wrapper.unknown00, "HitEff"); }

u32 getArtsBlSpHitEff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ArtsBlSpHitEff] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ArtsBlSpHitEff], id, 2).valueU16;
}

void initGrowLevelExp(const CBdatWrapper &wrapper) { s_members[GrowLevelExp] = Bdat::getMember(wrapper.unknown00, "LevelExp"); }

u32 getGrowLevelExp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowLevelExp] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowLevelExp], id, 3).valueU32;
}

void initGrowEnemyExp(const CBdatWrapper &wrapper) { s_members[GrowEnemyExp] = Bdat::getMember(wrapper.unknown00, "EnemyExp"); }

u32 getGrowEnemyExp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemyExp] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemyExp], id, 2).valueU16;
}

void initGrowEnemyWP(const CBdatWrapper &wrapper) { s_members[GrowEnemyWP] = Bdat::getMember(wrapper.unknown00, "EnemyWP"); }

u32 getGrowEnemyWP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemyWP] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemyWP], id, 2).valueU16;
}

void initGrowEnemySP(const CBdatWrapper &wrapper) { s_members[GrowEnemySP] = Bdat::getMember(wrapper.unknown00, "EnemySP"); }

u32 getGrowEnemySP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemySP] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemySP], id, 2).valueU16;
}

void initGrowEnemyGold(const CBdatWrapper &wrapper) { s_members[GrowEnemyGold] = Bdat::getMember(wrapper.unknown00, "EnemyGold"); }

u32 getGrowEnemyGold(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowEnemyGold] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowEnemyGold], id, 3).valueU32;
}

void initGrowGoldDivide(const CBdatWrapper &wrapper) { s_members[GrowGoldDivide] = Bdat::getMember(wrapper.unknown00, "GoldDivide"); }

u32 getGrowGoldDivide(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GrowGoldDivide] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GrowGoldDivide], id, 1).valueU8;
}

void initLv_RevExpRevHigh(const CBdatWrapper &wrapper) { s_members[Lv_RevExpRevHigh] = Bdat::getMember(wrapper.unknown00, "ExpRevHigh"); }

u32 getLv_RevExpRevHigh(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevExpRevHigh] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevExpRevHigh], id, 2).valueU16;
}

void initLv_RevExpRevLow(const CBdatWrapper &wrapper) { s_members[Lv_RevExpRevLow] = Bdat::getMember(wrapper.unknown00, "ExpRevLow"); }

u32 getLv_RevExpRevLow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevExpRevLow] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevExpRevLow], id, 2).valueU16;
}

void initLv_RevDamageRevHigh(const CBdatWrapper &wrapper) { s_members[Lv_RevDamageRevHigh] = Bdat::getMember(wrapper.unknown00, "DamageRevHigh"); }

u32 getLv_RevDamageRevHigh(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevDamageRevHigh] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevDamageRevHigh], id, 2).valueU16;
}

void initLv_RevDamageRevLow(const CBdatWrapper &wrapper) { s_members[Lv_RevDamageRevLow] = Bdat::getMember(wrapper.unknown00, "DamageRevLow"); }

u32 getLv_RevDamageRevLow(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Lv_RevDamageRevLow] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Lv_RevDamageRevLow], id, 2).valueU16;
}

void initWpn_EnRscR(const CBdatWrapper &wrapper) { s_members[Wpn_EnRscR] = Bdat::getMember(wrapper.unknown00, "RscR"); }

u32 getWpn_EnRscR(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnRscR] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnRscR], id, 2).valueU16;
}

void initWpn_EnRscL(const CBdatWrapper &wrapper) { s_members[Wpn_EnRscL] = Bdat::getMember(wrapper.unknown00, "RscL"); }

u32 getWpn_EnRscL(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnRscL] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnRscL], id, 2).valueU16;
}

void initWpn_EnTypeRange(const CBdatWrapper &wrapper) { s_members[Wpn_EnTypeRange] = Bdat::getMember(wrapper.unknown00, "TypeRange"); }

u32 getWpn_EnTypeRange(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnTypeRange] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnTypeRange], id, 1).valueU8;
}

void initWpn_EnDamage(const CBdatWrapper &wrapper) { s_members[Wpn_EnDamage] = Bdat::getMember(wrapper.unknown00, "Damage"); }

u32 getWpn_EnDamage(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnDamage] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnDamage], id, 2).valueU16;
}

void initWpn_EnStability(const CBdatWrapper &wrapper) { s_members[Wpn_EnStability] = Bdat::getMember(wrapper.unknown00, "Stability"); }

u32 getWpn_EnStability(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Wpn_EnStability] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Wpn_EnStability], id, 1).valueU8;
}

void initBTL_ClassName(const CBdatWrapper &wrapper) { s_members[BTL_ClassName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getBTL_ClassName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassName], id, 2).valueU16;
}

void initBTL_ClassRole1(const CBdatWrapper &wrapper) { s_members[BTL_ClassRole1] = Bdat::getMember(wrapper.unknown00, "Role1"); }

u32 getBTL_ClassRole1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassRole1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassRole1], id, 1).valueU8;
}

void initBTL_ClassRole2(const CBdatWrapper &wrapper) { s_members[BTL_ClassRole2] = Bdat::getMember(wrapper.unknown00, "Role2"); }

u32 getBTL_ClassRole2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassRole2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassRole2], id, 1).valueU8;
}

void initBTL_ClassRole3(const CBdatWrapper &wrapper) { s_members[BTL_ClassRole3] = Bdat::getMember(wrapper.unknown00, "Role3"); }

u32 getBTL_ClassRole3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassRole3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassRole3], id, 1).valueU8;
}

void initBTL_ClassDamageDown(const CBdatWrapper &wrapper) { s_members[BTL_ClassDamageDown] = Bdat::getMember(wrapper.unknown00, "DamageDown"); }

u32 getBTL_ClassDamageDown(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassDamageDown] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassDamageDown], id, 1).valueU8;
}

void initBTL_ClassDamageUP(const CBdatWrapper &wrapper) { s_members[BTL_ClassDamageUP] = Bdat::getMember(wrapper.unknown00, "DamageUP"); }

u32 getBTL_ClassDamageUP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassDamageUP] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassDamageUP], id, 1).valueU8;
}

void initBTL_ClassHealUP(const CBdatWrapper &wrapper) { s_members[BTL_ClassHealUP] = Bdat::getMember(wrapper.unknown00, "HealUP"); }

u32 getBTL_ClassHealUP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassHealUP] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassHealUP], id, 1).valueU8;
}

void initBTL_ClassAutoHate(const CBdatWrapper &wrapper) { s_members[BTL_ClassAutoHate] = Bdat::getMember(wrapper.unknown00, "AutoHate"); }

s32 getBTL_ClassAutoHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassAutoHate] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassAutoHate], id, 4).valueS8;
}

void initBTL_ClassArtsHate(const CBdatWrapper &wrapper) { s_members[BTL_ClassArtsHate] = Bdat::getMember(wrapper.unknown00, "ArtsHate"); }

s32 getBTL_ClassArtsHate(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_ClassArtsHate] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_ClassArtsHate], id, 4).valueS8;
}

void initBTL_EnhanceEnhanceEffect(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEnhanceEffect] = Bdat::getMember(wrapper.unknown00, "EnhanceEffect"); }

u32 getBTL_EnhanceEnhanceEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEnhanceEffect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEnhanceEffect], id, 2).valueU16;
}

void initBTL_EnhanceParam1(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceParam1] = Bdat::getMember(wrapper.unknown00, "Param1"); }

f32 getBTL_EnhanceParam1(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BTL_EnhanceParam1] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[BTL_EnhanceParam1], id, 8).valueF32;
  }

  return value;
}

void initBTL_EnhanceParam2(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceParam2] = Bdat::getMember(wrapper.unknown00, "Param2"); }

f32 getBTL_EnhanceParam2(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[BTL_EnhanceParam2] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[BTL_EnhanceParam2], id, 8).valueF32;
  }

  return value;
}

void initBTL_EnhanceCaption(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceCaption] = Bdat::getMember(wrapper.unknown00, "Caption"); }

u32 getBTL_EnhanceCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceCaption] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceCaption], id, 2).valueU16;
}

void initBTL_EnhanceEffCategory(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffCategory] = Bdat::getMember(wrapper.unknown00, "Category"); }

u32 getBTL_EnhanceEffCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffCategory] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffCategory], id, 1).valueU8;
}

void initBTL_EnhanceEffIcon(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffIcon] = Bdat::getMember(wrapper.unknown00, "Icon"); }

u32 getBTL_EnhanceEffIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffIcon] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffIcon], id, 1).valueU8;
}

void initBTL_EnhanceEffFlagCondition(const CBdatWrapper &wrapper) {
  s_members[BTL_EnhanceEffFlagCondition] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[BTL_EnhanceEffFlagConditionFlag] = Bdat::getMember(wrapper.unknown00, "Condition");
}

bool isBTL_EnhanceEffFlagCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffFlagCondition] == nullptr || s_members[BTL_EnhanceEffFlagConditionFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_EnhanceEffFlagCondition], id, s_members[BTL_EnhanceEffFlagConditionFlag]) != 0;
}

void initBTL_EnhanceEffFlagUI(const CBdatWrapper &wrapper) {
  s_members[BTL_EnhanceEffFlagUI] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[BTL_EnhanceEffFlagUIFlag] = Bdat::getMember(wrapper.unknown00, "UI");
}

bool isBTL_EnhanceEffFlagUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffFlagUI] == nullptr || s_members[BTL_EnhanceEffFlagUIFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_EnhanceEffFlagUI], id, s_members[BTL_EnhanceEffFlagUIFlag]) != 0;
}

void initBTL_EnhanceEffParam(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffParam] = Bdat::getMember(wrapper.unknown00, "Param"); }

u32 getBTL_EnhanceEffParam(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffParam] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffParam], id, 2).valueU16;
}

void initBTL_EnhanceEffName(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getBTL_EnhanceEffName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffName], id, 2).valueU16;
}

void initBTL_EnhanceEffDirect(const CBdatWrapper &wrapper) { s_members[BTL_EnhanceEffDirect] = Bdat::getMember(wrapper.unknown00, "Direct"); }

u32 getBTL_EnhanceEffDirect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_EnhanceEffDirect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_EnhanceEffDirect], id, 1).valueU8;
}

void initBTL_Skill_BlName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getBTL_Skill_BlName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlName], id, 2).valueU16;
}

void initBTL_Skill_BlDebugName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getBTL_Skill_BlDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlDebugName], id, 7).valueString;
}

void initBTL_Skill_BlEnhance1(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance1] = Bdat::getMember(wrapper.unknown00, "Enhance1"); }

u32 getBTL_Skill_BlEnhance1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance1], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance2(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance2] = Bdat::getMember(wrapper.unknown00, "Enhance2"); }

u32 getBTL_Skill_BlEnhance2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance2], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance3(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance3] = Bdat::getMember(wrapper.unknown00, "Enhance3"); }

u32 getBTL_Skill_BlEnhance3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance3], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance4(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance4] = Bdat::getMember(wrapper.unknown00, "Enhance4"); }

u32 getBTL_Skill_BlEnhance4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance4] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance4], id, 2).valueU16;
}

void initBTL_Skill_BlEnhance5(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlEnhance5] = Bdat::getMember(wrapper.unknown00, "Enhance5"); }

u32 getBTL_Skill_BlEnhance5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlEnhance5] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlEnhance5], id, 2).valueU16;
}

void initBTL_Skill_BlFlagcommon(const CBdatWrapper &wrapper) {
  s_members[BTL_Skill_BlFlagcommon] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[BTL_Skill_BlFlagcommonFlag] = Bdat::getMember(wrapper.unknown00, "common");
}

bool isBTL_Skill_BlFlagcommon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlFlagcommon] == nullptr || s_members[BTL_Skill_BlFlagcommonFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_Skill_BlFlagcommon], id, s_members[BTL_Skill_BlFlagcommonFlag]) != 0;
}

void initBTL_Skill_BlTank(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlTank] = Bdat::getMember(wrapper.unknown00, "Tank"); }

u32 getBTL_Skill_BlTank(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlTank] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlTank], id, 1).valueU8;
}

void initBTL_Skill_BlAttacker(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlAttacker] = Bdat::getMember(wrapper.unknown00, "Attacker"); }

u32 getBTL_Skill_BlAttacker(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlAttacker] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlAttacker], id, 1).valueU8;
}

void initBTL_Skill_BlHealer(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlHealer] = Bdat::getMember(wrapper.unknown00, "Healer"); }

u32 getBTL_Skill_BlHealer(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlHealer] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlHealer], id, 1).valueU8;
}

void initBTL_Skill_BlUI(const CBdatWrapper &wrapper) { s_members[BTL_Skill_BlUI] = Bdat::getMember(wrapper.unknown00, "UI"); }

u32 getBTL_Skill_BlUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_BlUI] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_BlUI], id, 1).valueU8;
}

void initBTL_Skill_DrName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getBTL_Skill_DrName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrName], id, 2).valueU16;
}

void initBTL_Skill_DrDebugName(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getBTL_Skill_DrDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrDebugName], id, 7).valueString;
}

void initBTL_Skill_DrEnhance(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrEnhance] = Bdat::getMember(wrapper.unknown00, "Enhance"); }

u32 getBTL_Skill_DrEnhance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrEnhance] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrEnhance], id, 2).valueU16;
}

void initBTL_Skill_DrUI(const CBdatWrapper &wrapper) { s_members[BTL_Skill_DrUI] = Bdat::getMember(wrapper.unknown00, "UI"); }

u32 getBTL_Skill_DrUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Skill_DrUI] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Skill_DrUI], id, 2).valueU16;
}

void initBTL_BuffName(const CBdatWrapper &wrapper) { s_members[BTL_BuffName] = Bdat::getMember(wrapper.unknown00, "Name"); }

u32 getBTL_BuffName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffName], id, 1).valueU8;
}

void initBTL_BuffDebugName(const CBdatWrapper &wrapper) { s_members[BTL_BuffDebugName] = Bdat::getMember(wrapper.unknown00, "DebugName"); }

const char *getBTL_BuffDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffDebugName] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_BuffDebugName], id, 7).valueString;
}

void initBTL_BuffCaption(const CBdatWrapper &wrapper) { s_members[BTL_BuffCaption] = Bdat::getMember(wrapper.unknown00, "Caption"); }

u32 getBTL_BuffCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffCaption] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffCaption], id, 1).valueU8;
}

void initBTL_BuffBaseNum(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseNum] = Bdat::getMember(wrapper.unknown00, "BaseNum"); }

u32 getBTL_BuffBaseNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseNum], id, 2).valueU16;
}

void initBTL_BuffBaseTime(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseTime] = Bdat::getMember(wrapper.unknown00, "BaseTime"); }

u32 getBTL_BuffBaseTime(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseTime] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseTime], id, 2).valueU16;
}

void initBTL_BuffBaseRecast(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseRecast] = Bdat::getMember(wrapper.unknown00, "BaseRecast"); }

u32 getBTL_BuffBaseRecast(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseRecast] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseRecast], id, 2).valueU16;
}

void initBTL_BuffBaseProb(const CBdatWrapper &wrapper) { s_members[BTL_BuffBaseProb] = Bdat::getMember(wrapper.unknown00, "BaseProb"); }

u32 getBTL_BuffBaseProb(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffBaseProb] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffBaseProb], id, 1).valueU8;
}

void initBTL_BuffInterval(const CBdatWrapper &wrapper) { s_members[BTL_BuffInterval] = Bdat::getMember(wrapper.unknown00, "Interval"); }

u32 getBTL_BuffInterval(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffInterval] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffInterval], id, 2).valueU16;
}

void initBTL_BuffEffect(const CBdatWrapper &wrapper) { s_members[BTL_BuffEffect] = Bdat::getMember(wrapper.unknown00, "Effect"); }

const char *getBTL_BuffEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffEffect] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_BuffEffect], id, 7).valueString;
}

void initBTL_BuffIcon(const CBdatWrapper &wrapper) { s_members[BTL_BuffIcon] = Bdat::getMember(wrapper.unknown00, "Icon"); }

u32 getBTL_BuffIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_BuffIcon] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_BuffIcon], id, 2).valueU16;
}

void initBTL_Bl_PersonalityFlagcommon(const CBdatWrapper &wrapper) {
  s_members[BTL_Bl_PersonalityFlagcommon] = Bdat::getMember(wrapper.unknown00, "Flag");
  s_members[BTL_Bl_PersonalityFlagcommonFlag] = Bdat::getMember(wrapper.unknown00, "common");
}

bool isBTL_Bl_PersonalityFlagcommon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_PersonalityFlagcommon] == nullptr || s_members[BTL_Bl_PersonalityFlagcommonFlag] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) ||
      id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[BTL_Bl_PersonalityFlagcommon], id, s_members[BTL_Bl_PersonalityFlagcommonFlag]) != 0;
}

void initBTL_Bl_PersonalityKizunaBase(const CBdatWrapper &wrapper) { s_members[BTL_Bl_PersonalityKizunaBase] = Bdat::getMember(wrapper.unknown00, "KizunaBase"); }

u32 getBTL_Bl_PersonalityKizunaBase(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_PersonalityKizunaBase] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_PersonalityKizunaBase], id, 1).valueU8;
}

void initBTL_Bl_PersonalityVoiceID(const CBdatWrapper &wrapper) { s_members[BTL_Bl_PersonalityVoiceID] = Bdat::getMember(wrapper.unknown00, "VoiceID"); }

u32 getBTL_Bl_PersonalityVoiceID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_PersonalityVoiceID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_PersonalityVoiceID], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkLinkNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkLinkNum] = Bdat::getMember(wrapper.unknown00, "LinkNum"); }

u32 getBTL_Bl_KizunaLinkLinkNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkLinkNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkLinkNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkDeadNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkDeadNum] = Bdat::getMember(wrapper.unknown00, "DeadNum"); }

u32 getBTL_Bl_KizunaLinkDeadNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkDeadNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkDeadNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkAppStNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkAppStNum] = Bdat::getMember(wrapper.unknown00, "AppStNum"); }

u32 getBTL_Bl_KizunaLinkAppStNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppStNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppStNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkAppEndNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkAppEndNum] = Bdat::getMember(wrapper.unknown00, "AppEndNum"); }

u32 getBTL_Bl_KizunaLinkAppEndNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppEndNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppEndNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkAppCond(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkAppCond] = Bdat::getMember(wrapper.unknown00, "AppCond"); }

u32 getBTL_Bl_KizunaLinkAppCond(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppCond] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppCond], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkAppCondNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkAppCondNum] = Bdat::getMember(wrapper.unknown00, "AppCondNum"); }

u32 getBTL_Bl_KizunaLinkAppCondNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkAppCondNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkAppCondNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkReJudgef(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkReJudgef] = Bdat::getMember(wrapper.unknown00, "ReJudgef"); }

u32 getBTL_Bl_KizunaLinkReJudgef(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkReJudgef] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkReJudgef], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSpActType(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSpActType] = Bdat::getMember(wrapper.unknown00, "SpActType"); }

u32 getBTL_Bl_KizunaLinkSpActType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSpActType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSpActType], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSpActNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSpActNum] = Bdat::getMember(wrapper.unknown00, "SpActNum"); }

u32 getBTL_Bl_KizunaLinkSpActNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSpActNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSpActNum], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSpActf(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSpActf] = Bdat::getMember(wrapper.unknown00, "SpActf"); }

u32 getBTL_Bl_KizunaLinkSpActf(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSpActf] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSpActf], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkStandDir(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkStandDir] = Bdat::getMember(wrapper.unknown00, "StandDir"); }

u32 getBTL_Bl_KizunaLinkStandDir(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkStandDir] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkStandDir], id, 1).valueU8;
}

void initBTL_Bl_KizunaLinkSetKizunaLink1(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSetKizunaLink1] = Bdat::getMember(wrapper.unknown00, "KizunaLink1"); }

u32 getBTL_Bl_KizunaLinkSetKizunaLink1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetKizunaLink1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetKizunaLink1], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetKizunaLink2(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSetKizunaLink2] = Bdat::getMember(wrapper.unknown00, "KizunaLink2"); }

u32 getBTL_Bl_KizunaLinkSetKizunaLink2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetKizunaLink2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetKizunaLink2], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetLinkChType(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSetLinkChType] = Bdat::getMember(wrapper.unknown00, "LinkChType"); }

u32 getBTL_Bl_KizunaLinkSetLinkChType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetLinkChType] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetLinkChType], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetLinkChNum(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSetLinkChNum] = Bdat::getMember(wrapper.unknown00, "LinkChNum"); }

u32 getBTL_Bl_KizunaLinkSetLinkChNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetLinkChNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetLinkChNum], id, 2).valueU16;
}

void initBTL_Bl_KizunaLinkSetVoiceID(const CBdatWrapper &wrapper) { s_members[BTL_Bl_KizunaLinkSetVoiceID] = Bdat::getMember(wrapper.unknown00, "VoiceID"); }

u32 getBTL_Bl_KizunaLinkSetVoiceID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_Bl_KizunaLinkSetVoiceID] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_Bl_KizunaLinkSetVoiceID], id, 1).valueU8;
}

void initBTL_TestSettingDr1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1] = Bdat::getMember(wrapper.unknown00, "Dr1"); }

u32 getBTL_TestSettingDr1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1], id, 1).valueU8;
}

void initBTL_TestSettingDr1Lv(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Lv] = Bdat::getMember(wrapper.unknown00, "Dr1Lv"); }

u32 getBTL_TestSettingDr1Lv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Lv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Lv], id, 1).valueU8;
}

void initBTL_TestSettingDr1Bl1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Bl1] = Bdat::getMember(wrapper.unknown00, "Dr1Bl1"); }

u32 getBTL_TestSettingDr1Bl1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Bl1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Bl1], id, 2).valueU16;
}

void initBTL_TestSettingDr1Bl2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Bl2] = Bdat::getMember(wrapper.unknown00, "Dr1Bl2"); }

u32 getBTL_TestSettingDr1Bl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Bl2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Bl2], id, 2).valueU16;
}

void initBTL_TestSettingDr1Bl3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr1Bl3] = Bdat::getMember(wrapper.unknown00, "Dr1Bl3"); }

u32 getBTL_TestSettingDr1Bl3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr1Bl3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr1Bl3], id, 2).valueU16;
}

void initBTL_TestSettingDr2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2] = Bdat::getMember(wrapper.unknown00, "Dr2"); }

u32 getBTL_TestSettingDr2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2], id, 1).valueU8;
}

void initBTL_TestSettingDr2Lv(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Lv] = Bdat::getMember(wrapper.unknown00, "Dr2Lv"); }

u32 getBTL_TestSettingDr2Lv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Lv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Lv], id, 1).valueU8;
}

void initBTL_TestSettingDr2Bl1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Bl1] = Bdat::getMember(wrapper.unknown00, "Dr2Bl1"); }

u32 getBTL_TestSettingDr2Bl1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Bl1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Bl1], id, 2).valueU16;
}

void initBTL_TestSettingDr2Bl2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Bl2] = Bdat::getMember(wrapper.unknown00, "Dr2Bl2"); }

u32 getBTL_TestSettingDr2Bl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Bl2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Bl2], id, 2).valueU16;
}

void initBTL_TestSettingDr2Bl3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr2Bl3] = Bdat::getMember(wrapper.unknown00, "Dr2Bl3"); }

u32 getBTL_TestSettingDr2Bl3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr2Bl3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr2Bl3], id, 2).valueU16;
}

void initBTL_TestSettingDr3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3] = Bdat::getMember(wrapper.unknown00, "Dr3"); }

u32 getBTL_TestSettingDr3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3], id, 1).valueU8;
}

void initBTL_TestSettingDr3Lv(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Lv] = Bdat::getMember(wrapper.unknown00, "Dr3Lv"); }

u32 getBTL_TestSettingDr3Lv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Lv] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Lv], id, 1).valueU8;
}

void initBTL_TestSettingDr3Bl1(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Bl1] = Bdat::getMember(wrapper.unknown00, "Dr3Bl1"); }

u32 getBTL_TestSettingDr3Bl1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Bl1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Bl1], id, 2).valueU16;
}

void initBTL_TestSettingDr3Bl2(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Bl2] = Bdat::getMember(wrapper.unknown00, "Dr3Bl2"); }

u32 getBTL_TestSettingDr3Bl2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Bl2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Bl2], id, 2).valueU16;
}

void initBTL_TestSettingDr3Bl3(const CBdatWrapper &wrapper) { s_members[BTL_TestSettingDr3Bl3] = Bdat::getMember(wrapper.unknown00, "Dr3Bl3"); }

u32 getBTL_TestSettingDr3Bl3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_TestSettingDr3Bl3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_TestSettingDr3Bl3], id, 2).valueU16;
}

void initBTL_HanaBaseNCondNum(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseNCondNum] = Bdat::getMember(wrapper.unknown00, "NCondNum"); }

u32 getBTL_HanaBaseNCondNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseNCondNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseNCondNum], id, 1).valueU8;
}

void initBTL_HanaBaseECondNum(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseECondNum] = Bdat::getMember(wrapper.unknown00, "ECondNum"); }

u32 getBTL_HanaBaseECondNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseECondNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseECondNum], id, 1).valueU8;
}

void initBTL_HanaBaseNArtsNum(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseNArtsNum] = Bdat::getMember(wrapper.unknown00, "NArtsNum"); }

u32 getBTL_HanaBaseNArtsNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseNArtsNum] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseNArtsNum], id, 1).valueU8;
}

void initBTL_HanaBaseCircuit1Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit1Num] = Bdat::getMember(wrapper.unknown00, "Circuit1Num"); }

u32 getBTL_HanaBaseCircuit1Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit1Num] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit1Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit2Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit2Num] = Bdat::getMember(wrapper.unknown00, "Circuit2Num"); }

u32 getBTL_HanaBaseCircuit2Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit2Num] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit2Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit3Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit3Num] = Bdat::getMember(wrapper.unknown00, "Circuit3Num"); }

u32 getBTL_HanaBaseCircuit3Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit3Num] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit3Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit4Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit4Num] = Bdat::getMember(wrapper.unknown00, "Circuit4Num"); }

u32 getBTL_HanaBaseCircuit4Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit4Num] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit4Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit5Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit5Num] = Bdat::getMember(wrapper.unknown00, "Circuit5Num"); }

u32 getBTL_HanaBaseCircuit5Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit5Num] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit5Num], id, 2).valueU16;
}

void initBTL_HanaBaseCircuit6Num(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseCircuit6Num] = Bdat::getMember(wrapper.unknown00, "Circuit6Num"); }

u32 getBTL_HanaBaseCircuit6Num(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseCircuit6Num] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseCircuit6Num], id, 2).valueU16;
}

void initBTL_HanaBaseUI(const CBdatWrapper &wrapper) { s_members[BTL_HanaBaseUI] = Bdat::getMember(wrapper.unknown00, "UI"); }

const char *getBTL_HanaBaseUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaBaseUI] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_HanaBaseUI], id, 7).valueString;
}

void initBTL_HanaPowerPowerNum1(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerPowerNum1] = Bdat::getMember(wrapper.unknown00, "PowerNum1"); }

u32 getBTL_HanaPowerPowerNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerPowerNum1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerPowerNum1], id, 2).valueU16;
}

void initBTL_HanaPowerPowerNum2(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerPowerNum2] = Bdat::getMember(wrapper.unknown00, "PowerNum2"); }

u32 getBTL_HanaPowerPowerNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerPowerNum2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerPowerNum2], id, 2).valueU16;
}

void initBTL_HanaPowerPowerNum3(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerPowerNum3] = Bdat::getMember(wrapper.unknown00, "PowerNum3"); }

u32 getBTL_HanaPowerPowerNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerPowerNum3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerPowerNum3], id, 2).valueU16;
}

void initBTL_HanaPowerEtherNum1(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerEtherNum1] = Bdat::getMember(wrapper.unknown00, "EtherNum1"); }

u32 getBTL_HanaPowerEtherNum1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerEtherNum1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerEtherNum1], id, 3).valueU32;
}

void initBTL_HanaPowerEtherNum2(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerEtherNum2] = Bdat::getMember(wrapper.unknown00, "EtherNum2"); }

u32 getBTL_HanaPowerEtherNum2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerEtherNum2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerEtherNum2], id, 3).valueU32;
}

void initBTL_HanaPowerEtherNum3(const CBdatWrapper &wrapper) { s_members[BTL_HanaPowerEtherNum3] = Bdat::getMember(wrapper.unknown00, "EtherNum3"); }

u32 getBTL_HanaPowerEtherNum3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaPowerEtherNum3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaPowerEtherNum3], id, 3).valueU32;
}

void initBTL_HanaChipsetRoleParts(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetRoleParts] = Bdat::getMember(wrapper.unknown00, "RoleParts"); }

u32 getBTL_HanaChipsetRoleParts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetRoleParts] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetRoleParts], id, 2).valueU16;
}

void initBTL_HanaChipsetAtrParts(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetAtrParts] = Bdat::getMember(wrapper.unknown00, "AtrParts"); }

u32 getBTL_HanaChipsetAtrParts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetAtrParts] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetAtrParts], id, 2).valueU16;
}

void initBTL_HanaChipsetNArtsParts1(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetNArtsParts1] = Bdat::getMember(wrapper.unknown00, "NArtsParts1"); }

u32 getBTL_HanaChipsetNArtsParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNArtsParts1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNArtsParts1], id, 2).valueU16;
}

void initBTL_HanaChipsetNArtsParts2(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetNArtsParts2] = Bdat::getMember(wrapper.unknown00, "NArtsParts2"); }

u32 getBTL_HanaChipsetNArtsParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNArtsParts2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNArtsParts2], id, 2).valueU16;
}

void initBTL_HanaChipsetNArtsParts3(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetNArtsParts3] = Bdat::getMember(wrapper.unknown00, "NArtsParts3"); }

u32 getBTL_HanaChipsetNArtsParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNArtsParts3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNArtsParts3], id, 2).valueU16;
}

void initBTL_HanaChipsetNCondParts1(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetNCondParts1] = Bdat::getMember(wrapper.unknown00, "NCondParts1"); }

u32 getBTL_HanaChipsetNCondParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNCondParts1] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNCondParts1], id, 2).valueU16;
}

void initBTL_HanaChipsetNCondParts2(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetNCondParts2] = Bdat::getMember(wrapper.unknown00, "NCondParts2"); }

u32 getBTL_HanaChipsetNCondParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNCondParts2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNCondParts2], id, 2).valueU16;
}

void initBTL_HanaChipsetNCondParts3(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetNCondParts3] = Bdat::getMember(wrapper.unknown00, "NCondParts3"); }

u32 getBTL_HanaChipsetNCondParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetNCondParts3] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetNCondParts3], id, 2).valueU16;
}

void initBTL_HanaChipsetUI(const CBdatWrapper &wrapper) { s_members[BTL_HanaChipsetUI] = Bdat::getMember(wrapper.unknown00, "UI"); }

const char *getBTL_HanaChipsetUI(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BTL_HanaChipsetUI] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[BTL_HanaChipsetUI], id, 7).valueString;
}

void initWildcardDatavalueF4(const CBdatWrapper &wrapper) { s_members[WildcardDatavalueF4] = Bdat::getMember(wrapper.unknown00, "valueF4"); }

f32 getWildcardDatavalueF4(const CBdatWrapper &wrapper, u32 id) {
  f32 value = 0.0f;
  if (s_members[WildcardDatavalueF4] != nullptr && id >= Bdat::getIdTop(wrapper.unknown00) && id < Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    value = wrapper.getValCheck(s_members[WildcardDatavalueF4], id, 8).valueF32;
  }

  return value;
}

void initWildcardDatavalueU2(const CBdatWrapper &wrapper) { s_members[WildcardDatavalueU2] = Bdat::getMember(wrapper.unknown00, "valueU2"); }

u32 getWildcardDatavalueU2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[WildcardDatavalueU2] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[WildcardDatavalueU2], id, 2).valueU16;
}

void initVo_Field_FilterTargetFile(const CBdatWrapper &wrapper) { s_members[Vo_Field_FilterTargetFile] = Bdat::getMember(wrapper.unknown00, "TargetFile"); }

const char *getVo_Field_FilterTargetFile(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Vo_Field_FilterTargetFile] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[Vo_Field_FilterTargetFile], id, 7).valueString;
}

void initVo_Field_FilterCondition(const CBdatWrapper &wrapper) { s_members[Vo_Field_FilterCondition] = Bdat::getMember(wrapper.unknown00, "Condition"); }

u32 getVo_Field_FilterCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[Vo_Field_FilterCondition] == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[Vo_Field_FilterCondition], id, 2).valueU16;
}

void initVo_Field_FilterChangeFile(const CBdatWrapper &wrapper) { s_Vo_Field_FilterChangeFile = Bdat::getMember(wrapper.unknown00, "ChangeFile"); }

const char *getVo_Field_FilterChangeFile(const CBdatWrapper &wrapper, u32 id) {
  if (s_Vo_Field_FilterChangeFile == nullptr || id < Bdat::getIdTop(wrapper.unknown00) || id >= Bdat::getIdTop(wrapper.unknown00) + Bdat::getIdCount(wrapper.unknown00)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_Vo_Field_FilterChangeFile, id, 7).valueString;
}

} // namespace _gfbbt

GfBdatBtl::GfBdatBtl()
    : m_artsDr(nullptr), m_artsBl(nullptr), m_artsBlSp(nullptr), m_grow(nullptr), m_lv_Rev(nullptr), m_wpn_En(nullptr), m_BTL_Class(nullptr), m_BTL_Enhance(nullptr), m_BTL_EnhanceEff(nullptr),
      m_BTL_Skill_Bl(nullptr), m_BTL_Skill_Dr(nullptr), m_BTL_Buff(nullptr), m_BTL_Bl_Personality(nullptr), m_BTL_Bl_KizunaLink(nullptr), m_BTL_Bl_KizunaLinkSet(nullptr), m_BTL_TestSetting(nullptr),
      m_BTL_HanaBase(nullptr), m_BTL_HanaPower(nullptr), m_BTL_HanaChipset(nullptr), m_wildcardData(nullptr), m_vo_Field_Filter(nullptr) {
  bdatRefresh();
}

GfBdatBtl::~GfBdatBtl() { destroyFP(); }

void GfBdatBtl::destroyFP() {
  if (m_artsDr != nullptr) {
    delete m_artsDr;
    m_artsDr = nullptr;
  }

  if (m_artsBl != nullptr) {
    delete m_artsBl;
    m_artsBl = nullptr;
  }

  if (m_artsBlSp != nullptr) {
    delete m_artsBlSp;
    m_artsBlSp = nullptr;
  }

  if (m_grow != nullptr) {
    delete m_grow;
    m_grow = nullptr;
  }

  if (m_lv_Rev != nullptr) {
    delete m_lv_Rev;
    m_lv_Rev = nullptr;
  }

  if (m_wpn_En != nullptr) {
    delete m_wpn_En;
    m_wpn_En = nullptr;
  }

  if (m_BTL_Class != nullptr) {
    delete m_BTL_Class;
    m_BTL_Class = nullptr;
  }

  if (m_BTL_Enhance != nullptr) {
    delete m_BTL_Enhance;
    m_BTL_Enhance = nullptr;
  }

  if (m_BTL_EnhanceEff != nullptr) {
    delete m_BTL_EnhanceEff;
    m_BTL_EnhanceEff = nullptr;
  }

  if (m_BTL_Skill_Bl != nullptr) {
    delete m_BTL_Skill_Bl;
    m_BTL_Skill_Bl = nullptr;
  }

  if (m_BTL_Skill_Dr != nullptr) {
    delete m_BTL_Skill_Dr;
    m_BTL_Skill_Dr = nullptr;
  }

  if (m_BTL_Buff != nullptr) {
    delete m_BTL_Buff;
    m_BTL_Buff = nullptr;
  }

  if (m_BTL_Bl_Personality != nullptr) {
    delete m_BTL_Bl_Personality;
    m_BTL_Bl_Personality = nullptr;
  }

  if (m_BTL_Bl_KizunaLink != nullptr) {
    delete m_BTL_Bl_KizunaLink;
    m_BTL_Bl_KizunaLink = nullptr;
  }

  if (m_BTL_Bl_KizunaLinkSet != nullptr) {
    delete m_BTL_Bl_KizunaLinkSet;
    m_BTL_Bl_KizunaLinkSet = nullptr;
  }

  if (m_BTL_TestSetting != nullptr) {
    delete m_BTL_TestSetting;
    m_BTL_TestSetting = nullptr;
  }

  if (m_BTL_HanaBase != nullptr) {
    delete m_BTL_HanaBase;
    m_BTL_HanaBase = nullptr;
  }

  if (m_BTL_HanaPower != nullptr) {
    delete m_BTL_HanaPower;
    m_BTL_HanaPower = nullptr;
  }

  if (m_BTL_HanaChipset != nullptr) {
    delete m_BTL_HanaChipset;
    m_BTL_HanaChipset = nullptr;
  }

  if (m_wildcardData != nullptr) {
    delete m_wildcardData;
    m_wildcardData = nullptr;
  }

  if (m_vo_Field_Filter != nullptr) {
    delete m_vo_Field_Filter;
    m_vo_Field_Filter = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                                                                         \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatBtl::createFP() {
  m_artsDr = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_DR);
  m_artsBl = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_BL);
  m_artsBlSp = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_BL_SP);
  m_grow = NEW_BDAT_WRAPPER(BDAT_BTL_GROW);
  m_lv_Rev = NEW_BDAT_WRAPPER(BDAT_BTL_LV_REV);
  m_wpn_En = NEW_BDAT_WRAPPER(BDAT_BTL_WPN_EN);
  m_BTL_Class = NEW_BDAT_WRAPPER(BDAT_BTL_CLASS);
  m_BTL_Enhance = NEW_BDAT_WRAPPER(BDAT_BTL_ENHANCE);
  m_BTL_EnhanceEff = NEW_BDAT_WRAPPER(BDAT_BTL_ENHANCE_EFF);
  m_BTL_Skill_Bl = NEW_BDAT_WRAPPER(BDAT_BTL_SKILL_BL);
  m_BTL_Skill_Dr = NEW_BDAT_WRAPPER(BDAT_BTL_SKILL_DR);
  m_BTL_Buff = NEW_BDAT_WRAPPER(BDAT_BTL_BUFF);
  m_BTL_Bl_Personality = NEW_BDAT_WRAPPER(BDAT_BTL_BL_PERSONALITY);
  m_BTL_Bl_KizunaLink = NEW_BDAT_WRAPPER(BDAT_BTL_BL_KIZUNA_LINK);
  m_BTL_Bl_KizunaLinkSet = NEW_BDAT_WRAPPER(BDAT_BTL_BL_KIZUNA_LINK_SET);
  m_BTL_TestSetting = NEW_BDAT_WRAPPER(BDAT_BTL_TEST_SETTING);
  m_BTL_HanaBase = NEW_BDAT_WRAPPER(BDAT_BTL_HANA_BASE);
  m_BTL_HanaPower = NEW_BDAT_WRAPPER(BDAT_BTL_HANA_POWER);
  m_BTL_HanaChipset = NEW_BDAT_WRAPPER(BDAT_BTL_HANA_CHIPSET);
  m_wildcardData = NEW_BDAT_WRAPPER(BDAT_FLD_WILDCARD_DATA);
  m_vo_Field_Filter = NEW_BDAT_WRAPPER(BDAT_VO_FIELD_FILTER);
}

void GfBdatBtl::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbbt::initArtsDrName(*m_artsDr);
  _gfbbt::initArtsDrDebugName(*m_artsDr);
  _gfbbt::initArtsDrCaption(*m_artsDr);
  _gfbbt::initArtsDrDriver(*m_artsDr);
  _gfbbt::initArtsDrWpnType(*m_artsDr);
  _gfbbt::initArtsDrActNo(*m_artsDr);
  _gfbbt::initArtsDrArtsType(*m_artsDr);
  _gfbbt::initArtsDrArtsBuff(*m_artsDr);
  _gfbbt::initArtsDrAtrType(*m_artsDr);
  _gfbbt::initArtsDrFlagNormal(*m_artsDr);
  _gfbbt::initArtsDrFlagPierce(*m_artsDr);
  _gfbbt::initArtsDrFlagNoRepelled(*m_artsDr);
  _gfbbt::initArtsDrNextArts(*m_artsDr);
  _gfbbt::initArtsDrTarget(*m_artsDr);
  _gfbbt::initArtsDrDistance(*m_artsDr);
  _gfbbt::initArtsDrRangeType(*m_artsDr);
  _gfbbt::initArtsDrRadius(*m_artsDr);
  _gfbbt::initArtsDrLength(*m_artsDr);
  _gfbbt::initArtsDrHate(*m_artsDr);
  _gfbbt::initArtsDrHitRevise(*m_artsDr);
  _gfbbt::initArtsDrCriRevise(*m_artsDr);
  _gfbbt::initArtsDrBulletID(*m_artsDr);
  _gfbbt::initArtsDrBulletNum(*m_artsDr);
  _gfbbt::initArtsDrHitFrm1(*m_artsDr);
  _gfbbt::initArtsDrHitFrm2(*m_artsDr);
  _gfbbt::initArtsDrHitFrm3(*m_artsDr);
  _gfbbt::initArtsDrHitFrm4(*m_artsDr);
  _gfbbt::initArtsDrHitFrm5(*m_artsDr);
  _gfbbt::initArtsDrHitFrm6(*m_artsDr);
  _gfbbt::initArtsDrHitFrm7(*m_artsDr);
  _gfbbt::initArtsDrHitFrm8(*m_artsDr);
  _gfbbt::initArtsDrHitFrm9(*m_artsDr);
  _gfbbt::initArtsDrHitFrm10(*m_artsDr);
  _gfbbt::initArtsDrHitFrm11(*m_artsDr);
  _gfbbt::initArtsDrHitFrm12(*m_artsDr);
  _gfbbt::initArtsDrHitFrm13(*m_artsDr);
  _gfbbt::initArtsDrHitFrm14(*m_artsDr);
  _gfbbt::initArtsDrHitFrm15(*m_artsDr);
  _gfbbt::initArtsDrHitFrm16(*m_artsDr);
  _gfbbt::initArtsDrEfp1(*m_artsDr);
  _gfbbt::initArtsDrEfp2(*m_artsDr);
  _gfbbt::initArtsDrEfp3(*m_artsDr);
  _gfbbt::initArtsDrEfp4(*m_artsDr);
  _gfbbt::initArtsDrEfp5(*m_artsDr);
  _gfbbt::initArtsDrEfp6(*m_artsDr);
  _gfbbt::initArtsDrEfp7(*m_artsDr);
  _gfbbt::initArtsDrEfp8(*m_artsDr);
  _gfbbt::initArtsDrEfp9(*m_artsDr);
  _gfbbt::initArtsDrEfp10(*m_artsDr);
  _gfbbt::initArtsDrEfp11(*m_artsDr);
  _gfbbt::initArtsDrEfp12(*m_artsDr);
  _gfbbt::initArtsDrEfp13(*m_artsDr);
  _gfbbt::initArtsDrEfp14(*m_artsDr);
  _gfbbt::initArtsDrEfp15(*m_artsDr);
  _gfbbt::initArtsDrEfp16(*m_artsDr);
  _gfbbt::initArtsDrHitDirID1(*m_artsDr);
  _gfbbt::initArtsDrHitDirID2(*m_artsDr);
  _gfbbt::initArtsDrHitDirID3(*m_artsDr);
  _gfbbt::initArtsDrHitDirID4(*m_artsDr);
  _gfbbt::initArtsDrHitDirID5(*m_artsDr);
  _gfbbt::initArtsDrHitDirID6(*m_artsDr);
  _gfbbt::initArtsDrHitDirID7(*m_artsDr);
  _gfbbt::initArtsDrHitDirID8(*m_artsDr);
  _gfbbt::initArtsDrHitDirID9(*m_artsDr);
  _gfbbt::initArtsDrHitDirID10(*m_artsDr);
  _gfbbt::initArtsDrHitDirID11(*m_artsDr);
  _gfbbt::initArtsDrHitDirID12(*m_artsDr);
  _gfbbt::initArtsDrHitDirID13(*m_artsDr);
  _gfbbt::initArtsDrHitDirID14(*m_artsDr);
  _gfbbt::initArtsDrHitDirID15(*m_artsDr);
  _gfbbt::initArtsDrHitDirID16(*m_artsDr);
  _gfbbt::initArtsDrDmgRt1(*m_artsDr);
  _gfbbt::initArtsDrDmgRt2(*m_artsDr);
  _gfbbt::initArtsDrDmgRt3(*m_artsDr);
  _gfbbt::initArtsDrDmgRt4(*m_artsDr);
  _gfbbt::initArtsDrDmgRt5(*m_artsDr);
  _gfbbt::initArtsDrDmgRt6(*m_artsDr);
  _gfbbt::initArtsDrDmgRt7(*m_artsDr);
  _gfbbt::initArtsDrDmgRt8(*m_artsDr);
  _gfbbt::initArtsDrDmgRt9(*m_artsDr);
  _gfbbt::initArtsDrDmgRt10(*m_artsDr);
  _gfbbt::initArtsDrDmgRt11(*m_artsDr);
  _gfbbt::initArtsDrDmgRt12(*m_artsDr);
  _gfbbt::initArtsDrDmgRt13(*m_artsDr);
  _gfbbt::initArtsDrDmgRt14(*m_artsDr);
  _gfbbt::initArtsDrDmgRt15(*m_artsDr);
  _gfbbt::initArtsDrDmgRt16(*m_artsDr);
  _gfbbt::initArtsDrReAct1(*m_artsDr);
  _gfbbt::initArtsDrReAct2(*m_artsDr);
  _gfbbt::initArtsDrReAct3(*m_artsDr);
  _gfbbt::initArtsDrReAct4(*m_artsDr);
  _gfbbt::initArtsDrReAct5(*m_artsDr);
  _gfbbt::initArtsDrReAct6(*m_artsDr);
  _gfbbt::initArtsDrReAct7(*m_artsDr);
  _gfbbt::initArtsDrReAct8(*m_artsDr);
  _gfbbt::initArtsDrReAct9(*m_artsDr);
  _gfbbt::initArtsDrReAct10(*m_artsDr);
  _gfbbt::initArtsDrReAct11(*m_artsDr);
  _gfbbt::initArtsDrReAct12(*m_artsDr);
  _gfbbt::initArtsDrReAct13(*m_artsDr);
  _gfbbt::initArtsDrReAct14(*m_artsDr);
  _gfbbt::initArtsDrReAct15(*m_artsDr);
  _gfbbt::initArtsDrReAct16(*m_artsDr);
  _gfbbt::initArtsDrMoveCancelFrm(*m_artsDr);
  _gfbbt::initArtsDrDmgMgn1(*m_artsDr);
  _gfbbt::initArtsDrDmgMgn2(*m_artsDr);
  _gfbbt::initArtsDrDmgMgn3(*m_artsDr);
  _gfbbt::initArtsDrDmgMgn4(*m_artsDr);
  _gfbbt::initArtsDrDmgMgn5(*m_artsDr);
  _gfbbt::initArtsDrDmgMgn6(*m_artsDr);
  _gfbbt::initArtsDrRecast1(*m_artsDr);
  _gfbbt::initArtsDrRecast2(*m_artsDr);
  _gfbbt::initArtsDrRecast3(*m_artsDr);
  _gfbbt::initArtsDrRecast4(*m_artsDr);
  _gfbbt::initArtsDrRecast5(*m_artsDr);
  _gfbbt::initArtsDrRecast6(*m_artsDr);
  _gfbbt::initArtsDrAtrNum(*m_artsDr);
  _gfbbt::initArtsDrEnhance1(*m_artsDr);
  _gfbbt::initArtsDrEnhance2(*m_artsDr);
  _gfbbt::initArtsDrEnhance3(*m_artsDr);
  _gfbbt::initArtsDrEnhance4(*m_artsDr);
  _gfbbt::initArtsDrEnhance5(*m_artsDr);
  _gfbbt::initArtsDrEnhance6(*m_artsDr);
  _gfbbt::initArtsDrReleaseLv1(*m_artsDr);
  _gfbbt::initArtsDrReleaseLv2(*m_artsDr);
  _gfbbt::initArtsDrReleaseLv3(*m_artsDr);
  _gfbbt::initArtsDrReleaseLv4(*m_artsDr);
  _gfbbt::initArtsDrReleaseLv5(*m_artsDr);
  _gfbbt::initArtsDrNeedWP2(*m_artsDr);
  _gfbbt::initArtsDrNeedWP3(*m_artsDr);
  _gfbbt::initArtsDrNeedWP4(*m_artsDr);
  _gfbbt::initArtsDrNeedWP5(*m_artsDr);
  _gfbbt::initArtsDrUI(*m_artsDr);
  _gfbbt::initArtsDrPriority(*m_artsDr);
  _gfbbt::initArtsBlName(*m_artsBl);
  _gfbbt::initArtsBlDebugName(*m_artsBl);
  _gfbbt::initArtsBlCaption(*m_artsBl);
  _gfbbt::initArtsBlWpnType(*m_artsBl);
  _gfbbt::initArtsBlCmnBlType(*m_artsBl);
  _gfbbt::initArtsBlSpLv(*m_artsBl);
  _gfbbt::initArtsBlActNo(*m_artsBl);
  _gfbbt::initArtsBlArtsType(*m_artsBl);
  _gfbbt::initArtsBlArtsBuff(*m_artsBl);
  _gfbbt::initArtsBlFlagcommon(*m_artsBl);
  _gfbbt::initArtsBlFlagPierce(*m_artsBl);
  _gfbbt::initArtsBlTarget(*m_artsBl);
  _gfbbt::initArtsBlDistance(*m_artsBl);
  _gfbbt::initArtsBlRangeType(*m_artsBl);
  _gfbbt::initArtsBlRadius(*m_artsBl);
  _gfbbt::initArtsBlLength(*m_artsBl);
  _gfbbt::initArtsBlAtr(*m_artsBl);
  _gfbbt::initArtsBlHate(*m_artsBl);
  _gfbbt::initArtsBlHitRevise(*m_artsBl);
  _gfbbt::initArtsBlCriRevise(*m_artsBl);
  _gfbbt::initArtsBlBulletID(*m_artsBl);
  _gfbbt::initArtsBlBulletNum(*m_artsBl);
  _gfbbt::initArtsBlHitFrm1(*m_artsBl);
  _gfbbt::initArtsBlHitFrm2(*m_artsBl);
  _gfbbt::initArtsBlHitFrm3(*m_artsBl);
  _gfbbt::initArtsBlHitFrm4(*m_artsBl);
  _gfbbt::initArtsBlHitFrm5(*m_artsBl);
  _gfbbt::initArtsBlHitFrm6(*m_artsBl);
  _gfbbt::initArtsBlHitFrm7(*m_artsBl);
  _gfbbt::initArtsBlHitFrm8(*m_artsBl);
  _gfbbt::initArtsBlHitFrm9(*m_artsBl);
  _gfbbt::initArtsBlHitFrm10(*m_artsBl);
  _gfbbt::initArtsBlHitFrm11(*m_artsBl);
  _gfbbt::initArtsBlHitFrm12(*m_artsBl);
  _gfbbt::initArtsBlHitFrm13(*m_artsBl);
  _gfbbt::initArtsBlHitFrm14(*m_artsBl);
  _gfbbt::initArtsBlHitFrm15(*m_artsBl);
  _gfbbt::initArtsBlHitFrm16(*m_artsBl);
  _gfbbt::initArtsBlEfp1(*m_artsBl);
  _gfbbt::initArtsBlEfp2(*m_artsBl);
  _gfbbt::initArtsBlEfp3(*m_artsBl);
  _gfbbt::initArtsBlEfp4(*m_artsBl);
  _gfbbt::initArtsBlEfp5(*m_artsBl);
  _gfbbt::initArtsBlEfp6(*m_artsBl);
  _gfbbt::initArtsBlEfp7(*m_artsBl);
  _gfbbt::initArtsBlEfp8(*m_artsBl);
  _gfbbt::initArtsBlEfp9(*m_artsBl);
  _gfbbt::initArtsBlEfp10(*m_artsBl);
  _gfbbt::initArtsBlEfp11(*m_artsBl);
  _gfbbt::initArtsBlEfp12(*m_artsBl);
  _gfbbt::initArtsBlEfp13(*m_artsBl);
  _gfbbt::initArtsBlEfp14(*m_artsBl);
  _gfbbt::initArtsBlEfp15(*m_artsBl);
  _gfbbt::initArtsBlEfp16(*m_artsBl);
  _gfbbt::initArtsBlHitDirID1(*m_artsBl);
  _gfbbt::initArtsBlHitDirID2(*m_artsBl);
  _gfbbt::initArtsBlHitDirID3(*m_artsBl);
  _gfbbt::initArtsBlHitDirID4(*m_artsBl);
  _gfbbt::initArtsBlHitDirID5(*m_artsBl);
  _gfbbt::initArtsBlHitDirID6(*m_artsBl);
  _gfbbt::initArtsBlHitDirID7(*m_artsBl);
  _gfbbt::initArtsBlHitDirID8(*m_artsBl);
  _gfbbt::initArtsBlHitDirID9(*m_artsBl);
  _gfbbt::initArtsBlHitDirID10(*m_artsBl);
  _gfbbt::initArtsBlHitDirID11(*m_artsBl);
  _gfbbt::initArtsBlHitDirID12(*m_artsBl);
  _gfbbt::initArtsBlHitDirID13(*m_artsBl);
  _gfbbt::initArtsBlHitDirID14(*m_artsBl);
  _gfbbt::initArtsBlHitDirID15(*m_artsBl);
  _gfbbt::initArtsBlHitDirID16(*m_artsBl);
  _gfbbt::initArtsBlDmgRt1(*m_artsBl);
  _gfbbt::initArtsBlDmgRt2(*m_artsBl);
  _gfbbt::initArtsBlDmgRt3(*m_artsBl);
  _gfbbt::initArtsBlDmgRt4(*m_artsBl);
  _gfbbt::initArtsBlDmgRt5(*m_artsBl);
  _gfbbt::initArtsBlDmgRt6(*m_artsBl);
  _gfbbt::initArtsBlDmgRt7(*m_artsBl);
  _gfbbt::initArtsBlDmgRt8(*m_artsBl);
  _gfbbt::initArtsBlDmgRt9(*m_artsBl);
  _gfbbt::initArtsBlDmgRt10(*m_artsBl);
  _gfbbt::initArtsBlDmgRt11(*m_artsBl);
  _gfbbt::initArtsBlDmgRt12(*m_artsBl);
  _gfbbt::initArtsBlDmgRt13(*m_artsBl);
  _gfbbt::initArtsBlDmgRt14(*m_artsBl);
  _gfbbt::initArtsBlDmgRt15(*m_artsBl);
  _gfbbt::initArtsBlDmgRt16(*m_artsBl);
  _gfbbt::initArtsBlReAct1(*m_artsBl);
  _gfbbt::initArtsBlReAct2(*m_artsBl);
  _gfbbt::initArtsBlReAct3(*m_artsBl);
  _gfbbt::initArtsBlReAct4(*m_artsBl);
  _gfbbt::initArtsBlReAct5(*m_artsBl);
  _gfbbt::initArtsBlReAct6(*m_artsBl);
  _gfbbt::initArtsBlReAct7(*m_artsBl);
  _gfbbt::initArtsBlReAct8(*m_artsBl);
  _gfbbt::initArtsBlReAct9(*m_artsBl);
  _gfbbt::initArtsBlReAct10(*m_artsBl);
  _gfbbt::initArtsBlReAct11(*m_artsBl);
  _gfbbt::initArtsBlReAct12(*m_artsBl);
  _gfbbt::initArtsBlReAct13(*m_artsBl);
  _gfbbt::initArtsBlReAct14(*m_artsBl);
  _gfbbt::initArtsBlReAct15(*m_artsBl);
  _gfbbt::initArtsBlReAct16(*m_artsBl);
  _gfbbt::initArtsBlDmgMgn1(*m_artsBl);
  _gfbbt::initArtsBlDmgMgn2(*m_artsBl);
  _gfbbt::initArtsBlDmgMgn3(*m_artsBl);
  _gfbbt::initArtsBlDmgMgn4(*m_artsBl);
  _gfbbt::initArtsBlDmgMgn5(*m_artsBl);
  _gfbbt::initArtsBlDmgMgn6(*m_artsBl);
  _gfbbt::initArtsBlAtrNum(*m_artsBl);
  _gfbbt::initArtsBlEnhance1(*m_artsBl);
  _gfbbt::initArtsBlEnhance2(*m_artsBl);
  _gfbbt::initArtsBlEnhance3(*m_artsBl);
  _gfbbt::initArtsBlEnhance4(*m_artsBl);
  _gfbbt::initArtsBlEnhance5(*m_artsBl);
  _gfbbt::initArtsBlEnhance6(*m_artsBl);
  _gfbbt::initArtsBlBtnType(*m_artsBl);
  _gfbbt::initArtsBlBtnChal1(*m_artsBl);
  _gfbbt::initArtsBlUI(*m_artsBl);
  _gfbbt::initArtsBlSpName(*m_artsBlSp);
  _gfbbt::initArtsBlSpDebugName(*m_artsBlSp);
  _gfbbt::initArtsBlSpCaption(*m_artsBlSp);
  _gfbbt::initArtsBlSpWpnType(*m_artsBlSp);
  _gfbbt::initArtsBlSpCmnBlType(*m_artsBlSp);
  _gfbbt::initArtsBlSpActNoDr(*m_artsBlSp);
  _gfbbt::initArtsBlSpActNoBl(*m_artsBlSp);
  _gfbbt::initArtsBlSpActNoBl2(*m_artsBlSp);
  _gfbbt::initArtsBlSpBuddyDr(*m_artsBlSp);
  _gfbbt::initArtsBlSpAddBl(*m_artsBlSp);
  _gfbbt::initArtsBlSpActType(*m_artsBlSp);
  _gfbbt::initArtsBlSpPC01(*m_artsBlSp);
  _gfbbt::initArtsBlSpPC02(*m_artsBlSp);
  _gfbbt::initArtsBlSpPC03(*m_artsBlSp);
  _gfbbt::initArtsBlSpPC06(*m_artsBlSp);
  _gfbbt::initArtsBlSpArtsType(*m_artsBlSp);
  _gfbbt::initArtsBlSpArtsBuff(*m_artsBlSp);
  _gfbbt::initArtsBlSpFlagPierce(*m_artsBlSp);
  _gfbbt::initArtsBlSpFlagNoMove(*m_artsBlSp);
  _gfbbt::initArtsBlSpTarget(*m_artsBlSp);
  _gfbbt::initArtsBlSpDistance(*m_artsBlSp);
  _gfbbt::initArtsBlSpRangeType(*m_artsBlSp);
  _gfbbt::initArtsBlSpRadius(*m_artsBlSp);
  _gfbbt::initArtsBlSpLength(*m_artsBlSp);
  _gfbbt::initArtsBlSpAtr(*m_artsBlSp);
  _gfbbt::initArtsBlSpHate(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitRevise(*m_artsBlSp);
  _gfbbt::initArtsBlSpCriRevise(*m_artsBlSp);
  _gfbbt::initArtsBlSpBulletID(*m_artsBlSp);
  _gfbbt::initArtsBlSpBulletEffID(*m_artsBlSp);
  _gfbbt::initArtsBlSpBulletNum(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm1(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm2(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm3(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm4(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm5(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm6(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm7(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm8(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm9(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm10(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm11(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm12(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm13(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm14(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm15(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitFrm16(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp1(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp2(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp3(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp4(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp5(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp6(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp7(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp8(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp9(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp10(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp11(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp12(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp13(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp14(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp15(*m_artsBlSp);
  _gfbbt::initArtsBlSpEfp16(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID1(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID2(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID3(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID4(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID5(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID6(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID7(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID8(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID9(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID10(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID11(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID12(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID13(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID14(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID15(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitDirID16(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt1(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt2(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt3(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt4(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt5(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt6(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt7(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt8(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt9(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt10(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt11(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt12(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt13(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt14(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt15(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgRt16(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct1(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct2(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct3(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct4(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct5(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct6(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct7(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct8(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct9(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct10(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct11(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct12(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct13(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct14(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct15(*m_artsBlSp);
  _gfbbt::initArtsBlSpReAct16(*m_artsBlSp);
  _gfbbt::initArtsBlSpDmgMgn(*m_artsBlSp);
  _gfbbt::initArtsBlSpRecast(*m_artsBlSp);
  _gfbbt::initArtsBlSpAtrNum(*m_artsBlSp);
  _gfbbt::initArtsBlSpEnhance(*m_artsBlSp);
  _gfbbt::initArtsBlSpBtnType(*m_artsBlSp);
  _gfbbt::initArtsBlSpBtnChal1(*m_artsBlSp);
  _gfbbt::initArtsBlSpCamera1(*m_artsBlSp);
  _gfbbt::initArtsBlSpCamera2(*m_artsBlSp);
  _gfbbt::initArtsBlSpCamera3(*m_artsBlSp);
  _gfbbt::initArtsBlSpCameraCT1(*m_artsBlSp);
  _gfbbt::initArtsBlSpCameraCT2(*m_artsBlSp);
  _gfbbt::initArtsBlSpCameraEndf(*m_artsBlSp);
  _gfbbt::initArtsBlSpHitEff(*m_artsBlSp);
  _gfbbt::initGrowLevelExp(*m_grow);
  _gfbbt::initGrowEnemyExp(*m_grow);
  _gfbbt::initGrowEnemyWP(*m_grow);
  _gfbbt::initGrowEnemySP(*m_grow);
  _gfbbt::initGrowEnemyGold(*m_grow);
  _gfbbt::initGrowGoldDivide(*m_grow);
  _gfbbt::initLv_RevExpRevHigh(*m_lv_Rev);
  _gfbbt::initLv_RevExpRevLow(*m_lv_Rev);
  _gfbbt::initLv_RevDamageRevHigh(*m_lv_Rev);
  _gfbbt::initLv_RevDamageRevLow(*m_lv_Rev);
  _gfbbt::initWpn_EnRscR(*m_wpn_En);
  _gfbbt::initWpn_EnRscL(*m_wpn_En);
  _gfbbt::initWpn_EnTypeRange(*m_wpn_En);
  _gfbbt::initWpn_EnDamage(*m_wpn_En);
  _gfbbt::initWpn_EnStability(*m_wpn_En);
  _gfbbt::initBTL_ClassName(*m_BTL_Class);
  _gfbbt::initBTL_ClassRole1(*m_BTL_Class);
  _gfbbt::initBTL_ClassRole2(*m_BTL_Class);
  _gfbbt::initBTL_ClassRole3(*m_BTL_Class);
  _gfbbt::initBTL_ClassDamageDown(*m_BTL_Class);
  _gfbbt::initBTL_ClassDamageUP(*m_BTL_Class);
  _gfbbt::initBTL_ClassHealUP(*m_BTL_Class);
  _gfbbt::initBTL_ClassAutoHate(*m_BTL_Class);
  _gfbbt::initBTL_ClassArtsHate(*m_BTL_Class);
  _gfbbt::initBTL_EnhanceEnhanceEffect(*m_BTL_Enhance);
  _gfbbt::initBTL_EnhanceParam1(*m_BTL_Enhance);
  _gfbbt::initBTL_EnhanceParam2(*m_BTL_Enhance);
  _gfbbt::initBTL_EnhanceCaption(*m_BTL_Enhance);
  _gfbbt::initBTL_EnhanceEffCategory(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_EnhanceEffIcon(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_EnhanceEffFlagCondition(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_EnhanceEffFlagUI(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_EnhanceEffParam(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_EnhanceEffName(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_EnhanceEffDirect(*m_BTL_EnhanceEff);
  _gfbbt::initBTL_Skill_BlName(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlDebugName(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlEnhance1(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlEnhance2(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlEnhance3(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlEnhance4(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlEnhance5(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlFlagcommon(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlTank(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlAttacker(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlHealer(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_BlUI(*m_BTL_Skill_Bl);
  _gfbbt::initBTL_Skill_DrName(*m_BTL_Skill_Dr);
  _gfbbt::initBTL_Skill_DrDebugName(*m_BTL_Skill_Dr);
  _gfbbt::initBTL_Skill_DrEnhance(*m_BTL_Skill_Dr);
  _gfbbt::initBTL_Skill_DrUI(*m_BTL_Skill_Dr);
  _gfbbt::initBTL_BuffName(*m_BTL_Buff);
  _gfbbt::initBTL_BuffDebugName(*m_BTL_Buff);
  _gfbbt::initBTL_BuffCaption(*m_BTL_Buff);
  _gfbbt::initBTL_BuffBaseNum(*m_BTL_Buff);
  _gfbbt::initBTL_BuffBaseTime(*m_BTL_Buff);
  _gfbbt::initBTL_BuffBaseRecast(*m_BTL_Buff);
  _gfbbt::initBTL_BuffBaseProb(*m_BTL_Buff);
  _gfbbt::initBTL_BuffInterval(*m_BTL_Buff);
  _gfbbt::initBTL_BuffEffect(*m_BTL_Buff);
  _gfbbt::initBTL_BuffIcon(*m_BTL_Buff);
  _gfbbt::initBTL_Bl_PersonalityFlagcommon(*m_BTL_Bl_Personality);
  _gfbbt::initBTL_Bl_PersonalityKizunaBase(*m_BTL_Bl_Personality);
  _gfbbt::initBTL_Bl_PersonalityVoiceID(*m_BTL_Bl_Personality);
  _gfbbt::initBTL_Bl_KizunaLinkLinkNum(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkDeadNum(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkAppStNum(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkAppEndNum(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkAppCond(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkAppCondNum(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkReJudgef(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkSpActType(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkSpActNum(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkSpActf(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkStandDir(*m_BTL_Bl_KizunaLink);
  _gfbbt::initBTL_Bl_KizunaLinkSetKizunaLink1(*m_BTL_Bl_KizunaLinkSet);
  _gfbbt::initBTL_Bl_KizunaLinkSetKizunaLink2(*m_BTL_Bl_KizunaLinkSet);
  _gfbbt::initBTL_Bl_KizunaLinkSetLinkChType(*m_BTL_Bl_KizunaLinkSet);
  _gfbbt::initBTL_Bl_KizunaLinkSetLinkChNum(*m_BTL_Bl_KizunaLinkSet);
  _gfbbt::initBTL_Bl_KizunaLinkSetVoiceID(*m_BTL_Bl_KizunaLinkSet);
  _gfbbt::initBTL_TestSettingDr1(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr1Lv(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr1Bl1(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr1Bl2(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr1Bl3(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr2(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr2Lv(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr2Bl1(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr2Bl2(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr2Bl3(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr3(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr3Lv(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr3Bl1(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr3Bl2(*m_BTL_TestSetting);
  _gfbbt::initBTL_TestSettingDr3Bl3(*m_BTL_TestSetting);
  _gfbbt::initBTL_HanaBaseNCondNum(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseECondNum(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseNArtsNum(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseCircuit1Num(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseCircuit2Num(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseCircuit3Num(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseCircuit4Num(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseCircuit5Num(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseCircuit6Num(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaBaseUI(*m_BTL_HanaBase);
  _gfbbt::initBTL_HanaPowerPowerNum1(*m_BTL_HanaPower);
  _gfbbt::initBTL_HanaPowerPowerNum2(*m_BTL_HanaPower);
  _gfbbt::initBTL_HanaPowerPowerNum3(*m_BTL_HanaPower);
  _gfbbt::initBTL_HanaPowerEtherNum1(*m_BTL_HanaPower);
  _gfbbt::initBTL_HanaPowerEtherNum2(*m_BTL_HanaPower);
  _gfbbt::initBTL_HanaPowerEtherNum3(*m_BTL_HanaPower);
  _gfbbt::initBTL_HanaChipsetRoleParts(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetAtrParts(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetNArtsParts1(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetNArtsParts2(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetNArtsParts3(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetNCondParts1(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetNCondParts2(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetNCondParts3(*m_BTL_HanaChipset);
  _gfbbt::initBTL_HanaChipsetUI(*m_BTL_HanaChipset);
  _gfbbt::initWildcardDatavalueF4(*m_wildcardData);
  _gfbbt::initWildcardDatavalueU2(*m_wildcardData);
  _gfbbt::initVo_Field_FilterTargetFile(*m_vo_Field_Filter);
  _gfbbt::initVo_Field_FilterCondition(*m_vo_Field_Filter);
  _gfbbt::initVo_Field_FilterChangeFile(*m_vo_Field_Filter);
}

u32 GfBdatBtl::getArtsDrStart() const { return Bdat::getIdTop(m_artsDr->unknown00); }

u32 GfBdatBtl::getArtsDrEnd() const { return Bdat::getIdTop(m_artsDr->unknown00) + Bdat::getIdCount(m_artsDr->unknown00); }

u32 GfBdatBtl::getArtsDrName(u32 id) const { return _gfbbt::getArtsDrName(*m_artsDr, id); }

const char *GfBdatBtl::getArtsDrDebugName(u32 id) const { return _gfbbt::getArtsDrDebugName(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrCaption(u32 id) const { return _gfbbt::getArtsDrCaption(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDriver(u32 id) const { return _gfbbt::getArtsDrDriver(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrWpnType(u32 id) const { return _gfbbt::getArtsDrWpnType(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrActNo(u32 id) const { return _gfbbt::getArtsDrActNo(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrArtsType(u32 id) const { return _gfbbt::getArtsDrArtsType(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrArtsBuff(u32 id) const { return _gfbbt::getArtsDrArtsBuff(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrAtrType(u32 id) const { return _gfbbt::getArtsDrAtrType(*m_artsDr, id); }

bool GfBdatBtl::isArtsDrFlagNormal(u32 id) const { return _gfbbt::isArtsDrFlagNormal(*m_artsDr, id); }

bool GfBdatBtl::isArtsDrFlagPierce(u32 id) const { return _gfbbt::isArtsDrFlagPierce(*m_artsDr, id); }

bool GfBdatBtl::isArtsDrFlagNoRepelled(u32 id) const { return _gfbbt::isArtsDrFlagNoRepelled(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrNextArts(u32 id) const { return _gfbbt::getArtsDrNextArts(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrTarget(u32 id) const { return _gfbbt::getArtsDrTarget(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDistance(u32 id) const { return _gfbbt::getArtsDrDistance(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRangeType(u32 id) const { return _gfbbt::getArtsDrRangeType(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRadius(u32 id) const { return _gfbbt::getArtsDrRadius(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrLength(u32 id) const { return _gfbbt::getArtsDrLength(*m_artsDr, id); }

s32 GfBdatBtl::getArtsDrHate(u32 id) const { return _gfbbt::getArtsDrHate(*m_artsDr, id); }

s32 GfBdatBtl::getArtsDrHitRevise(u32 id) const { return _gfbbt::getArtsDrHitRevise(*m_artsDr, id); }

s32 GfBdatBtl::getArtsDrCriRevise(u32 id) const { return _gfbbt::getArtsDrCriRevise(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrBulletID(u32 id) const { return _gfbbt::getArtsDrBulletID(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrBulletNum(u32 id) const { return _gfbbt::getArtsDrBulletNum(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm1(u32 id) const { return _gfbbt::getArtsDrHitFrm1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm2(u32 id) const { return _gfbbt::getArtsDrHitFrm2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm3(u32 id) const { return _gfbbt::getArtsDrHitFrm3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm4(u32 id) const { return _gfbbt::getArtsDrHitFrm4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm5(u32 id) const { return _gfbbt::getArtsDrHitFrm5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm6(u32 id) const { return _gfbbt::getArtsDrHitFrm6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm7(u32 id) const { return _gfbbt::getArtsDrHitFrm7(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm8(u32 id) const { return _gfbbt::getArtsDrHitFrm8(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm9(u32 id) const { return _gfbbt::getArtsDrHitFrm9(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm10(u32 id) const { return _gfbbt::getArtsDrHitFrm10(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm11(u32 id) const { return _gfbbt::getArtsDrHitFrm11(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm12(u32 id) const { return _gfbbt::getArtsDrHitFrm12(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm13(u32 id) const { return _gfbbt::getArtsDrHitFrm13(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm14(u32 id) const { return _gfbbt::getArtsDrHitFrm14(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm15(u32 id) const { return _gfbbt::getArtsDrHitFrm15(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitFrm16(u32 id) const { return _gfbbt::getArtsDrHitFrm16(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp1(u32 id) const { return _gfbbt::getArtsDrEfp1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp2(u32 id) const { return _gfbbt::getArtsDrEfp2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp3(u32 id) const { return _gfbbt::getArtsDrEfp3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp4(u32 id) const { return _gfbbt::getArtsDrEfp4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp5(u32 id) const { return _gfbbt::getArtsDrEfp5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp6(u32 id) const { return _gfbbt::getArtsDrEfp6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp7(u32 id) const { return _gfbbt::getArtsDrEfp7(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp8(u32 id) const { return _gfbbt::getArtsDrEfp8(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp9(u32 id) const { return _gfbbt::getArtsDrEfp9(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp10(u32 id) const { return _gfbbt::getArtsDrEfp10(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp11(u32 id) const { return _gfbbt::getArtsDrEfp11(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp12(u32 id) const { return _gfbbt::getArtsDrEfp12(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp13(u32 id) const { return _gfbbt::getArtsDrEfp13(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp14(u32 id) const { return _gfbbt::getArtsDrEfp14(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp15(u32 id) const { return _gfbbt::getArtsDrEfp15(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEfp16(u32 id) const { return _gfbbt::getArtsDrEfp16(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID1(u32 id) const { return _gfbbt::getArtsDrHitDirID1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID2(u32 id) const { return _gfbbt::getArtsDrHitDirID2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID3(u32 id) const { return _gfbbt::getArtsDrHitDirID3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID4(u32 id) const { return _gfbbt::getArtsDrHitDirID4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID5(u32 id) const { return _gfbbt::getArtsDrHitDirID5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID6(u32 id) const { return _gfbbt::getArtsDrHitDirID6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID7(u32 id) const { return _gfbbt::getArtsDrHitDirID7(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID8(u32 id) const { return _gfbbt::getArtsDrHitDirID8(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID9(u32 id) const { return _gfbbt::getArtsDrHitDirID9(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID10(u32 id) const { return _gfbbt::getArtsDrHitDirID10(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID11(u32 id) const { return _gfbbt::getArtsDrHitDirID11(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID12(u32 id) const { return _gfbbt::getArtsDrHitDirID12(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID13(u32 id) const { return _gfbbt::getArtsDrHitDirID13(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID14(u32 id) const { return _gfbbt::getArtsDrHitDirID14(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID15(u32 id) const { return _gfbbt::getArtsDrHitDirID15(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrHitDirID16(u32 id) const { return _gfbbt::getArtsDrHitDirID16(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt1(u32 id) const { return _gfbbt::getArtsDrDmgRt1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt2(u32 id) const { return _gfbbt::getArtsDrDmgRt2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt3(u32 id) const { return _gfbbt::getArtsDrDmgRt3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt4(u32 id) const { return _gfbbt::getArtsDrDmgRt4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt5(u32 id) const { return _gfbbt::getArtsDrDmgRt5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt6(u32 id) const { return _gfbbt::getArtsDrDmgRt6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt7(u32 id) const { return _gfbbt::getArtsDrDmgRt7(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt8(u32 id) const { return _gfbbt::getArtsDrDmgRt8(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt9(u32 id) const { return _gfbbt::getArtsDrDmgRt9(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt10(u32 id) const { return _gfbbt::getArtsDrDmgRt10(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt11(u32 id) const { return _gfbbt::getArtsDrDmgRt11(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt12(u32 id) const { return _gfbbt::getArtsDrDmgRt12(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt13(u32 id) const { return _gfbbt::getArtsDrDmgRt13(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt14(u32 id) const { return _gfbbt::getArtsDrDmgRt14(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt15(u32 id) const { return _gfbbt::getArtsDrDmgRt15(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgRt16(u32 id) const { return _gfbbt::getArtsDrDmgRt16(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct1(u32 id) const { return _gfbbt::getArtsDrReAct1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct2(u32 id) const { return _gfbbt::getArtsDrReAct2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct3(u32 id) const { return _gfbbt::getArtsDrReAct3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct4(u32 id) const { return _gfbbt::getArtsDrReAct4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct5(u32 id) const { return _gfbbt::getArtsDrReAct5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct6(u32 id) const { return _gfbbt::getArtsDrReAct6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct7(u32 id) const { return _gfbbt::getArtsDrReAct7(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct8(u32 id) const { return _gfbbt::getArtsDrReAct8(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct9(u32 id) const { return _gfbbt::getArtsDrReAct9(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct10(u32 id) const { return _gfbbt::getArtsDrReAct10(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct11(u32 id) const { return _gfbbt::getArtsDrReAct11(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct12(u32 id) const { return _gfbbt::getArtsDrReAct12(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct13(u32 id) const { return _gfbbt::getArtsDrReAct13(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct14(u32 id) const { return _gfbbt::getArtsDrReAct14(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct15(u32 id) const { return _gfbbt::getArtsDrReAct15(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReAct16(u32 id) const { return _gfbbt::getArtsDrReAct16(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrMoveCancelFrm(u32 id) const { return _gfbbt::getArtsDrMoveCancelFrm(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgMgn1(u32 id) const { return _gfbbt::getArtsDrDmgMgn1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgMgn2(u32 id) const { return _gfbbt::getArtsDrDmgMgn2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgMgn3(u32 id) const { return _gfbbt::getArtsDrDmgMgn3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgMgn4(u32 id) const { return _gfbbt::getArtsDrDmgMgn4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgMgn5(u32 id) const { return _gfbbt::getArtsDrDmgMgn5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrDmgMgn6(u32 id) const { return _gfbbt::getArtsDrDmgMgn6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRecast1(u32 id) const { return _gfbbt::getArtsDrRecast1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRecast2(u32 id) const { return _gfbbt::getArtsDrRecast2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRecast3(u32 id) const { return _gfbbt::getArtsDrRecast3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRecast4(u32 id) const { return _gfbbt::getArtsDrRecast4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRecast5(u32 id) const { return _gfbbt::getArtsDrRecast5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrRecast6(u32 id) const { return _gfbbt::getArtsDrRecast6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrAtrNum(u32 id) const { return _gfbbt::getArtsDrAtrNum(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEnhance1(u32 id) const { return _gfbbt::getArtsDrEnhance1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEnhance2(u32 id) const { return _gfbbt::getArtsDrEnhance2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEnhance3(u32 id) const { return _gfbbt::getArtsDrEnhance3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEnhance4(u32 id) const { return _gfbbt::getArtsDrEnhance4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEnhance5(u32 id) const { return _gfbbt::getArtsDrEnhance5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrEnhance6(u32 id) const { return _gfbbt::getArtsDrEnhance6(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReleaseLv1(u32 id) const { return _gfbbt::getArtsDrReleaseLv1(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReleaseLv2(u32 id) const { return _gfbbt::getArtsDrReleaseLv2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReleaseLv3(u32 id) const { return _gfbbt::getArtsDrReleaseLv3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReleaseLv4(u32 id) const { return _gfbbt::getArtsDrReleaseLv4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrReleaseLv5(u32 id) const { return _gfbbt::getArtsDrReleaseLv5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrNeedWP2(u32 id) const { return _gfbbt::getArtsDrNeedWP2(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrNeedWP3(u32 id) const { return _gfbbt::getArtsDrNeedWP3(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrNeedWP4(u32 id) const { return _gfbbt::getArtsDrNeedWP4(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrNeedWP5(u32 id) const { return _gfbbt::getArtsDrNeedWP5(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrUI(u32 id) const { return _gfbbt::getArtsDrUI(*m_artsDr, id); }

u32 GfBdatBtl::getArtsDrPriority(u32 id) const { return _gfbbt::getArtsDrPriority(*m_artsDr, id); }

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
  return getters[index](*m_artsDr, id);
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
  return getters[index](*m_artsDr, id);
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
  return getters[index](*m_artsDr, id);
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
  return getters[index](*m_artsDr, id);
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
  return getters[level](*m_artsDr, arts);
}

u32 GfBdatBtl::getArtsDrDmgMgn(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getArtsDrDmgMgn1, _gfbbt::getArtsDrDmgMgn2, _gfbbt::getArtsDrDmgMgn3, _gfbbt::getArtsDrDmgMgn4, _gfbbt::getArtsDrDmgMgn5, _gfbbt::getArtsDrDmgMgn6};
  return getters[level](*m_artsDr, arts);
}

u32 GfBdatBtl::getArtsDrRecast(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getArtsDrRecast1, _gfbbt::getArtsDrRecast2, _gfbbt::getArtsDrRecast3, _gfbbt::getArtsDrRecast4, _gfbbt::getArtsDrRecast5, _gfbbt::getArtsDrRecast6};
  return getters[level](*m_artsDr, arts);
}

u32 GfBdatBtl::getArtsDrEnhance(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbt::getArtsDrEnhance1, _gfbbt::getArtsDrEnhance2, _gfbbt::getArtsDrEnhance3, _gfbbt::getArtsDrEnhance4, _gfbbt::getArtsDrEnhance5, _gfbbt::getArtsDrEnhance6};
  return getters[level](*m_artsDr, arts);
}

u32 GfBdatBtl::getArtsDrReleaseLv(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbt::getArtsDrReleaseLv1, _gfbbt::getArtsDrReleaseLv1, _gfbbt::getArtsDrReleaseLv2, _gfbbt::getArtsDrReleaseLv3, _gfbbt::getArtsDrReleaseLv4, _gfbbt::getArtsDrReleaseLv5};
  return getters[level](*m_artsDr, arts);
}

u32 GfBdatBtl::getArtsDrNeedWP(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getArtsDrNeedWP2, _gfbbt::getArtsDrNeedWP2, _gfbbt::getArtsDrNeedWP2, _gfbbt::getArtsDrNeedWP3, _gfbbt::getArtsDrNeedWP4, _gfbbt::getArtsDrNeedWP5};
  return getters[level](*m_artsDr, arts);
}

u32 GfBdatBtl::getArtsBlStart() const { return Bdat::getIdTop(m_artsBl->unknown00); }

u32 GfBdatBtl::getArtsBlEnd() const { return Bdat::getIdTop(m_artsBl->unknown00) + Bdat::getIdCount(m_artsBl->unknown00); }

u32 GfBdatBtl::getArtsBlName(u32 id) const { return _gfbbt::getArtsBlName(*m_artsBl, id); }

const char *GfBdatBtl::getArtsBlDebugName(u32 id) const { return _gfbbt::getArtsBlDebugName(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlCaption(u32 id) const { return _gfbbt::getArtsBlCaption(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlWpnType(u32 id) const { return _gfbbt::getArtsBlWpnType(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlCmnBlType(u32 id) const { return _gfbbt::getArtsBlCmnBlType(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlSpLv(u32 id) const { return _gfbbt::getArtsBlSpLv(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlActNo(u32 id) const { return _gfbbt::getArtsBlActNo(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlArtsType(u32 id) const { return _gfbbt::getArtsBlArtsType(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlArtsBuff(u32 id) const { return _gfbbt::getArtsBlArtsBuff(*m_artsBl, id); }

bool GfBdatBtl::isArtsBlFlagcommon(u32 id) const { return _gfbbt::isArtsBlFlagcommon(*m_artsBl, id); }

bool GfBdatBtl::isArtsBlFlagPierce(u32 id) const { return _gfbbt::isArtsBlFlagPierce(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlTarget(u32 id) const { return _gfbbt::getArtsBlTarget(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDistance(u32 id) const { return _gfbbt::getArtsBlDistance(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlRangeType(u32 id) const { return _gfbbt::getArtsBlRangeType(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlRadius(u32 id) const { return _gfbbt::getArtsBlRadius(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlLength(u32 id) const { return _gfbbt::getArtsBlLength(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlAtr(u32 id) const { return _gfbbt::getArtsBlAtr(*m_artsBl, id); }

s32 GfBdatBtl::getArtsBlHate(u32 id) const { return _gfbbt::getArtsBlHate(*m_artsBl, id); }

s32 GfBdatBtl::getArtsBlHitRevise(u32 id) const { return _gfbbt::getArtsBlHitRevise(*m_artsBl, id); }

s32 GfBdatBtl::getArtsBlCriRevise(u32 id) const { return _gfbbt::getArtsBlCriRevise(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlBulletID(u32 id) const { return _gfbbt::getArtsBlBulletID(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlBulletNum(u32 id) const { return _gfbbt::getArtsBlBulletNum(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm1(u32 id) const { return _gfbbt::getArtsBlHitFrm1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm2(u32 id) const { return _gfbbt::getArtsBlHitFrm2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm3(u32 id) const { return _gfbbt::getArtsBlHitFrm3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm4(u32 id) const { return _gfbbt::getArtsBlHitFrm4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm5(u32 id) const { return _gfbbt::getArtsBlHitFrm5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm6(u32 id) const { return _gfbbt::getArtsBlHitFrm6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm7(u32 id) const { return _gfbbt::getArtsBlHitFrm7(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm8(u32 id) const { return _gfbbt::getArtsBlHitFrm8(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm9(u32 id) const { return _gfbbt::getArtsBlHitFrm9(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm10(u32 id) const { return _gfbbt::getArtsBlHitFrm10(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm11(u32 id) const { return _gfbbt::getArtsBlHitFrm11(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm12(u32 id) const { return _gfbbt::getArtsBlHitFrm12(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm13(u32 id) const { return _gfbbt::getArtsBlHitFrm13(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm14(u32 id) const { return _gfbbt::getArtsBlHitFrm14(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm15(u32 id) const { return _gfbbt::getArtsBlHitFrm15(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitFrm16(u32 id) const { return _gfbbt::getArtsBlHitFrm16(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp1(u32 id) const { return _gfbbt::getArtsBlEfp1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp2(u32 id) const { return _gfbbt::getArtsBlEfp2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp3(u32 id) const { return _gfbbt::getArtsBlEfp3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp4(u32 id) const { return _gfbbt::getArtsBlEfp4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp5(u32 id) const { return _gfbbt::getArtsBlEfp5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp6(u32 id) const { return _gfbbt::getArtsBlEfp6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp7(u32 id) const { return _gfbbt::getArtsBlEfp7(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp8(u32 id) const { return _gfbbt::getArtsBlEfp8(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp9(u32 id) const { return _gfbbt::getArtsBlEfp9(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp10(u32 id) const { return _gfbbt::getArtsBlEfp10(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp11(u32 id) const { return _gfbbt::getArtsBlEfp11(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp12(u32 id) const { return _gfbbt::getArtsBlEfp12(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp13(u32 id) const { return _gfbbt::getArtsBlEfp13(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp14(u32 id) const { return _gfbbt::getArtsBlEfp14(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp15(u32 id) const { return _gfbbt::getArtsBlEfp15(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEfp16(u32 id) const { return _gfbbt::getArtsBlEfp16(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID1(u32 id) const { return _gfbbt::getArtsBlHitDirID1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID2(u32 id) const { return _gfbbt::getArtsBlHitDirID2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID3(u32 id) const { return _gfbbt::getArtsBlHitDirID3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID4(u32 id) const { return _gfbbt::getArtsBlHitDirID4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID5(u32 id) const { return _gfbbt::getArtsBlHitDirID5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID6(u32 id) const { return _gfbbt::getArtsBlHitDirID6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID7(u32 id) const { return _gfbbt::getArtsBlHitDirID7(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID8(u32 id) const { return _gfbbt::getArtsBlHitDirID8(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID9(u32 id) const { return _gfbbt::getArtsBlHitDirID9(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID10(u32 id) const { return _gfbbt::getArtsBlHitDirID10(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID11(u32 id) const { return _gfbbt::getArtsBlHitDirID11(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID12(u32 id) const { return _gfbbt::getArtsBlHitDirID12(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID13(u32 id) const { return _gfbbt::getArtsBlHitDirID13(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID14(u32 id) const { return _gfbbt::getArtsBlHitDirID14(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID15(u32 id) const { return _gfbbt::getArtsBlHitDirID15(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlHitDirID16(u32 id) const { return _gfbbt::getArtsBlHitDirID16(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt1(u32 id) const { return _gfbbt::getArtsBlDmgRt1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt2(u32 id) const { return _gfbbt::getArtsBlDmgRt2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt3(u32 id) const { return _gfbbt::getArtsBlDmgRt3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt4(u32 id) const { return _gfbbt::getArtsBlDmgRt4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt5(u32 id) const { return _gfbbt::getArtsBlDmgRt5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt6(u32 id) const { return _gfbbt::getArtsBlDmgRt6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt7(u32 id) const { return _gfbbt::getArtsBlDmgRt7(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt8(u32 id) const { return _gfbbt::getArtsBlDmgRt8(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt9(u32 id) const { return _gfbbt::getArtsBlDmgRt9(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt10(u32 id) const { return _gfbbt::getArtsBlDmgRt10(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt11(u32 id) const { return _gfbbt::getArtsBlDmgRt11(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt12(u32 id) const { return _gfbbt::getArtsBlDmgRt12(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt13(u32 id) const { return _gfbbt::getArtsBlDmgRt13(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt14(u32 id) const { return _gfbbt::getArtsBlDmgRt14(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt15(u32 id) const { return _gfbbt::getArtsBlDmgRt15(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgRt16(u32 id) const { return _gfbbt::getArtsBlDmgRt16(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct1(u32 id) const { return _gfbbt::getArtsBlReAct1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct2(u32 id) const { return _gfbbt::getArtsBlReAct2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct3(u32 id) const { return _gfbbt::getArtsBlReAct3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct4(u32 id) const { return _gfbbt::getArtsBlReAct4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct5(u32 id) const { return _gfbbt::getArtsBlReAct5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct6(u32 id) const { return _gfbbt::getArtsBlReAct6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct7(u32 id) const { return _gfbbt::getArtsBlReAct7(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct8(u32 id) const { return _gfbbt::getArtsBlReAct8(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct9(u32 id) const { return _gfbbt::getArtsBlReAct9(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct10(u32 id) const { return _gfbbt::getArtsBlReAct10(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct11(u32 id) const { return _gfbbt::getArtsBlReAct11(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct12(u32 id) const { return _gfbbt::getArtsBlReAct12(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct13(u32 id) const { return _gfbbt::getArtsBlReAct13(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct14(u32 id) const { return _gfbbt::getArtsBlReAct14(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct15(u32 id) const { return _gfbbt::getArtsBlReAct15(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlReAct16(u32 id) const { return _gfbbt::getArtsBlReAct16(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgMgn1(u32 id) const { return _gfbbt::getArtsBlDmgMgn1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgMgn2(u32 id) const { return _gfbbt::getArtsBlDmgMgn2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgMgn3(u32 id) const { return _gfbbt::getArtsBlDmgMgn3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgMgn4(u32 id) const { return _gfbbt::getArtsBlDmgMgn4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgMgn5(u32 id) const { return _gfbbt::getArtsBlDmgMgn5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlDmgMgn6(u32 id) const { return _gfbbt::getArtsBlDmgMgn6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlAtrNum(u32 id) const { return _gfbbt::getArtsBlAtrNum(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEnhance1(u32 id) const { return _gfbbt::getArtsBlEnhance1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEnhance2(u32 id) const { return _gfbbt::getArtsBlEnhance2(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEnhance3(u32 id) const { return _gfbbt::getArtsBlEnhance3(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEnhance4(u32 id) const { return _gfbbt::getArtsBlEnhance4(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEnhance5(u32 id) const { return _gfbbt::getArtsBlEnhance5(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlEnhance6(u32 id) const { return _gfbbt::getArtsBlEnhance6(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlBtnType(u32 id) const { return _gfbbt::getArtsBlBtnType(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlBtnChal1(u32 id) const { return _gfbbt::getArtsBlBtnChal1(*m_artsBl, id); }

u32 GfBdatBtl::getArtsBlUI(u32 id) const { return _gfbbt::getArtsBlUI(*m_artsBl, id); }

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
  return getters[index](*m_artsBl, id);
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
  return getters[index](*m_artsBl, id);
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
  return getters[index](*m_artsBl, id);
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
  return getters[index](*m_artsBl, id);
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
  return getters[index](*m_artsBl, id);
}

u32 GfBdatBtl::getArtsBlDmgMgn(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &,
                                u32) = {_gfbbt::getArtsBlDmgMgn1, _gfbbt::getArtsBlDmgMgn2, _gfbbt::getArtsBlDmgMgn3, _gfbbt::getArtsBlDmgMgn4, _gfbbt::getArtsBlDmgMgn5, _gfbbt::getArtsBlDmgMgn6};
  return getters[index](*m_artsBl, id);
}

u32 GfBdatBtl::getArtsBlEnhance(u32 arts, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbt::getArtsBlEnhance1, _gfbbt::getArtsBlEnhance2, _gfbbt::getArtsBlEnhance3, _gfbbt::getArtsBlEnhance4, _gfbbt::getArtsBlEnhance5, _gfbbt::getArtsBlEnhance6};
  return getters[level](*m_artsBl, arts);
}

u32 GfBdatBtl::getArtsBlSpStart() const { return Bdat::getIdTop(m_artsBlSp->unknown00); }

u32 GfBdatBtl::getArtsBlSpEnd() const { return Bdat::getIdTop(m_artsBlSp->unknown00) + Bdat::getIdCount(m_artsBlSp->unknown00); }

u32 GfBdatBtl::getArtsBlSpName(u32 id) const { return _gfbbt::getArtsBlSpName(*m_artsBlSp, id); }

const char *GfBdatBtl::getArtsBlSpDebugName(u32 id) const { return _gfbbt::getArtsBlSpDebugName(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpCaption(u32 id) const { return _gfbbt::getArtsBlSpCaption(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpWpnType(u32 id) const { return _gfbbt::getArtsBlSpWpnType(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpCmnBlType(u32 id) const { return _gfbbt::getArtsBlSpCmnBlType(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpActNoDr(u32 id) const { return _gfbbt::getArtsBlSpActNoDr(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpActNoBl(u32 id) const { return _gfbbt::getArtsBlSpActNoBl(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpActNoBl2(u32 id) const { return _gfbbt::getArtsBlSpActNoBl2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpBuddyDr(u32 id) const { return _gfbbt::getArtsBlSpBuddyDr(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpAddBl(u32 id) const { return _gfbbt::getArtsBlSpAddBl(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpActType(u32 id) const { return _gfbbt::getArtsBlSpActType(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpPC01(u32 id) const { return _gfbbt::getArtsBlSpPC01(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpPC02(u32 id) const { return _gfbbt::getArtsBlSpPC02(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpPC03(u32 id) const { return _gfbbt::getArtsBlSpPC03(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpPC06(u32 id) const { return _gfbbt::getArtsBlSpPC06(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpArtsType(u32 id) const { return _gfbbt::getArtsBlSpArtsType(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpArtsBuff(u32 id) const { return _gfbbt::getArtsBlSpArtsBuff(*m_artsBlSp, id); }

bool GfBdatBtl::isArtsBlSpFlagPierce(u32 id) const { return _gfbbt::isArtsBlSpFlagPierce(*m_artsBlSp, id); }

bool GfBdatBtl::isArtsBlSpFlagNoMove(u32 id) const { return _gfbbt::isArtsBlSpFlagNoMove(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpTarget(u32 id) const { return _gfbbt::getArtsBlSpTarget(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDistance(u32 id) const { return _gfbbt::getArtsBlSpDistance(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpRangeType(u32 id) const { return _gfbbt::getArtsBlSpRangeType(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpRadius(u32 id) const { return _gfbbt::getArtsBlSpRadius(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpLength(u32 id) const { return _gfbbt::getArtsBlSpLength(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpAtr(u32 id) const { return _gfbbt::getArtsBlSpAtr(*m_artsBlSp, id); }

s32 GfBdatBtl::getArtsBlSpHate(u32 id) const { return _gfbbt::getArtsBlSpHate(*m_artsBlSp, id); }

s32 GfBdatBtl::getArtsBlSpHitRevise(u32 id) const { return _gfbbt::getArtsBlSpHitRevise(*m_artsBlSp, id); }

s32 GfBdatBtl::getArtsBlSpCriRevise(u32 id) const { return _gfbbt::getArtsBlSpCriRevise(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpBulletID(u32 id) const { return _gfbbt::getArtsBlSpBulletID(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpBulletEffID(u32 id) const { return _gfbbt::getArtsBlSpBulletEffID(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpBulletNum(u32 id) const { return _gfbbt::getArtsBlSpBulletNum(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm1(u32 id) const { return _gfbbt::getArtsBlSpHitFrm1(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm2(u32 id) const { return _gfbbt::getArtsBlSpHitFrm2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm3(u32 id) const { return _gfbbt::getArtsBlSpHitFrm3(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm4(u32 id) const { return _gfbbt::getArtsBlSpHitFrm4(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm5(u32 id) const { return _gfbbt::getArtsBlSpHitFrm5(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm6(u32 id) const { return _gfbbt::getArtsBlSpHitFrm6(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm7(u32 id) const { return _gfbbt::getArtsBlSpHitFrm7(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm8(u32 id) const { return _gfbbt::getArtsBlSpHitFrm8(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm9(u32 id) const { return _gfbbt::getArtsBlSpHitFrm9(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm10(u32 id) const { return _gfbbt::getArtsBlSpHitFrm10(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm11(u32 id) const { return _gfbbt::getArtsBlSpHitFrm11(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm12(u32 id) const { return _gfbbt::getArtsBlSpHitFrm12(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm13(u32 id) const { return _gfbbt::getArtsBlSpHitFrm13(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm14(u32 id) const { return _gfbbt::getArtsBlSpHitFrm14(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm15(u32 id) const { return _gfbbt::getArtsBlSpHitFrm15(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitFrm16(u32 id) const { return _gfbbt::getArtsBlSpHitFrm16(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp1(u32 id) const { return _gfbbt::getArtsBlSpEfp1(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp2(u32 id) const { return _gfbbt::getArtsBlSpEfp2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp3(u32 id) const { return _gfbbt::getArtsBlSpEfp3(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp4(u32 id) const { return _gfbbt::getArtsBlSpEfp4(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp5(u32 id) const { return _gfbbt::getArtsBlSpEfp5(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp6(u32 id) const { return _gfbbt::getArtsBlSpEfp6(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp7(u32 id) const { return _gfbbt::getArtsBlSpEfp7(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp8(u32 id) const { return _gfbbt::getArtsBlSpEfp8(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp9(u32 id) const { return _gfbbt::getArtsBlSpEfp9(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp10(u32 id) const { return _gfbbt::getArtsBlSpEfp10(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp11(u32 id) const { return _gfbbt::getArtsBlSpEfp11(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp12(u32 id) const { return _gfbbt::getArtsBlSpEfp12(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp13(u32 id) const { return _gfbbt::getArtsBlSpEfp13(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp14(u32 id) const { return _gfbbt::getArtsBlSpEfp14(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp15(u32 id) const { return _gfbbt::getArtsBlSpEfp15(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEfp16(u32 id) const { return _gfbbt::getArtsBlSpEfp16(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID1(u32 id) const { return _gfbbt::getArtsBlSpHitDirID1(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID2(u32 id) const { return _gfbbt::getArtsBlSpHitDirID2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID3(u32 id) const { return _gfbbt::getArtsBlSpHitDirID3(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID4(u32 id) const { return _gfbbt::getArtsBlSpHitDirID4(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID5(u32 id) const { return _gfbbt::getArtsBlSpHitDirID5(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID6(u32 id) const { return _gfbbt::getArtsBlSpHitDirID6(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID7(u32 id) const { return _gfbbt::getArtsBlSpHitDirID7(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID8(u32 id) const { return _gfbbt::getArtsBlSpHitDirID8(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID9(u32 id) const { return _gfbbt::getArtsBlSpHitDirID9(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID10(u32 id) const { return _gfbbt::getArtsBlSpHitDirID10(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID11(u32 id) const { return _gfbbt::getArtsBlSpHitDirID11(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID12(u32 id) const { return _gfbbt::getArtsBlSpHitDirID12(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID13(u32 id) const { return _gfbbt::getArtsBlSpHitDirID13(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID14(u32 id) const { return _gfbbt::getArtsBlSpHitDirID14(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID15(u32 id) const { return _gfbbt::getArtsBlSpHitDirID15(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitDirID16(u32 id) const { return _gfbbt::getArtsBlSpHitDirID16(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt1(u32 id) const { return _gfbbt::getArtsBlSpDmgRt1(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt2(u32 id) const { return _gfbbt::getArtsBlSpDmgRt2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt3(u32 id) const { return _gfbbt::getArtsBlSpDmgRt3(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt4(u32 id) const { return _gfbbt::getArtsBlSpDmgRt4(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt5(u32 id) const { return _gfbbt::getArtsBlSpDmgRt5(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt6(u32 id) const { return _gfbbt::getArtsBlSpDmgRt6(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt7(u32 id) const { return _gfbbt::getArtsBlSpDmgRt7(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt8(u32 id) const { return _gfbbt::getArtsBlSpDmgRt8(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt9(u32 id) const { return _gfbbt::getArtsBlSpDmgRt9(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt10(u32 id) const { return _gfbbt::getArtsBlSpDmgRt10(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt11(u32 id) const { return _gfbbt::getArtsBlSpDmgRt11(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt12(u32 id) const { return _gfbbt::getArtsBlSpDmgRt12(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt13(u32 id) const { return _gfbbt::getArtsBlSpDmgRt13(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt14(u32 id) const { return _gfbbt::getArtsBlSpDmgRt14(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt15(u32 id) const { return _gfbbt::getArtsBlSpDmgRt15(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgRt16(u32 id) const { return _gfbbt::getArtsBlSpDmgRt16(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct1(u32 id) const { return _gfbbt::getArtsBlSpReAct1(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct2(u32 id) const { return _gfbbt::getArtsBlSpReAct2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct3(u32 id) const { return _gfbbt::getArtsBlSpReAct3(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct4(u32 id) const { return _gfbbt::getArtsBlSpReAct4(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct5(u32 id) const { return _gfbbt::getArtsBlSpReAct5(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct6(u32 id) const { return _gfbbt::getArtsBlSpReAct6(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct7(u32 id) const { return _gfbbt::getArtsBlSpReAct7(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct8(u32 id) const { return _gfbbt::getArtsBlSpReAct8(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct9(u32 id) const { return _gfbbt::getArtsBlSpReAct9(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct10(u32 id) const { return _gfbbt::getArtsBlSpReAct10(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct11(u32 id) const { return _gfbbt::getArtsBlSpReAct11(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct12(u32 id) const { return _gfbbt::getArtsBlSpReAct12(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct13(u32 id) const { return _gfbbt::getArtsBlSpReAct13(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct14(u32 id) const { return _gfbbt::getArtsBlSpReAct14(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct15(u32 id) const { return _gfbbt::getArtsBlSpReAct15(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpReAct16(u32 id) const { return _gfbbt::getArtsBlSpReAct16(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpDmgMgn(u32 id) const { return _gfbbt::getArtsBlSpDmgMgn(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpRecast(u32 id) const { return _gfbbt::getArtsBlSpRecast(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpAtrNum(u32 id) const { return _gfbbt::getArtsBlSpAtrNum(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpEnhance(u32 id) const { return _gfbbt::getArtsBlSpEnhance(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpBtnType(u32 id) const { return _gfbbt::getArtsBlSpBtnType(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpBtnChal1(u32 id) const { return _gfbbt::getArtsBlSpBtnChal1(*m_artsBlSp, id); }

const char *GfBdatBtl::getArtsBlSpCamera1(u32 id) const { return _gfbbt::getArtsBlSpCamera1(*m_artsBlSp, id); }

const char *GfBdatBtl::getArtsBlSpCamera2(u32 id) const { return _gfbbt::getArtsBlSpCamera2(*m_artsBlSp, id); }

const char *GfBdatBtl::getArtsBlSpCamera3(u32 id) const { return _gfbbt::getArtsBlSpCamera3(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpCameraCT1(u32 id) const { return _gfbbt::getArtsBlSpCameraCT1(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpCameraCT2(u32 id) const { return _gfbbt::getArtsBlSpCameraCT2(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpCameraEndf(u32 id) const { return _gfbbt::getArtsBlSpCameraEndf(*m_artsBlSp, id); }

u32 GfBdatBtl::getArtsBlSpHitEff(u32 id) const { return _gfbbt::getArtsBlSpHitEff(*m_artsBlSp, id); }

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
  return getters[index](*m_artsBlSp, id);
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
  return getters[index](*m_artsBlSp, id);
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
  return getters[index](*m_artsBlSp, id);
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
  return getters[index](*m_artsBlSp, id);
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
  return getters[index](*m_artsBlSp, id);
}

u32 GfBdatBtl::getGrowStart() const { return Bdat::getIdTop(m_grow->unknown00); }

u32 GfBdatBtl::getGrowEnd() const { return Bdat::getIdTop(m_grow->unknown00) + Bdat::getIdCount(m_grow->unknown00); }

u32 GfBdatBtl::getGrowLevelExp(u32 id) const { return _gfbbt::getGrowLevelExp(*m_grow, id); }

u32 GfBdatBtl::getGrowEnemyExp(u32 id) const { return _gfbbt::getGrowEnemyExp(*m_grow, id); }

u32 GfBdatBtl::getGrowEnemyWP(u32 id) const { return _gfbbt::getGrowEnemyWP(*m_grow, id); }

u32 GfBdatBtl::getGrowEnemySP(u32 id) const { return _gfbbt::getGrowEnemySP(*m_grow, id); }

u32 GfBdatBtl::getGrowEnemyGold(u32 id) const { return _gfbbt::getGrowEnemyGold(*m_grow, id); }

u32 GfBdatBtl::getGrowGoldDivide(u32 id) const { return _gfbbt::getGrowGoldDivide(*m_grow, id); }

u32 GfBdatBtl::getLv_RevStart() const { return Bdat::getIdTop(m_lv_Rev->unknown00); }

u32 GfBdatBtl::getLv_RevEnd() const { return Bdat::getIdTop(m_lv_Rev->unknown00) + Bdat::getIdCount(m_lv_Rev->unknown00); }

u32 GfBdatBtl::getLv_RevExpRevHigh(u32 id) const { return _gfbbt::getLv_RevExpRevHigh(*m_lv_Rev, id); }

u32 GfBdatBtl::getLv_RevExpRevLow(u32 id) const { return _gfbbt::getLv_RevExpRevLow(*m_lv_Rev, id); }

u32 GfBdatBtl::getLv_RevDamageRevHigh(u32 id) const { return _gfbbt::getLv_RevDamageRevHigh(*m_lv_Rev, id); }

u32 GfBdatBtl::getLv_RevDamageRevLow(u32 id) const { return _gfbbt::getLv_RevDamageRevLow(*m_lv_Rev, id); }

u32 GfBdatBtl::getWpn_EnStart() const { return Bdat::getIdTop(m_wpn_En->unknown00); }

u32 GfBdatBtl::getWpn_EnEnd() const { return Bdat::getIdTop(m_wpn_En->unknown00) + Bdat::getIdCount(m_wpn_En->unknown00); }

u32 GfBdatBtl::getWpn_EnRscR(u32 id) const { return _gfbbt::getWpn_EnRscR(*m_wpn_En, id); }

u32 GfBdatBtl::getWpn_EnRscL(u32 id) const { return _gfbbt::getWpn_EnRscL(*m_wpn_En, id); }

u32 GfBdatBtl::getWpn_EnTypeRange(u32 id) const { return _gfbbt::getWpn_EnTypeRange(*m_wpn_En, id); }

u32 GfBdatBtl::getWpn_EnDamage(u32 id) const { return _gfbbt::getWpn_EnDamage(*m_wpn_En, id); }

u32 GfBdatBtl::getWpn_EnStability(u32 id) const { return _gfbbt::getWpn_EnStability(*m_wpn_En, id); }

u32 GfBdatBtl::getBTL_ClassStart() const { return Bdat::getIdTop(m_BTL_Class->unknown00); }

u32 GfBdatBtl::getBTL_ClassEnd() const { return Bdat::getIdTop(m_BTL_Class->unknown00) + Bdat::getIdCount(m_BTL_Class->unknown00); }

u32 GfBdatBtl::getBTL_ClassName(u32 id) const { return _gfbbt::getBTL_ClassName(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassRole1(u32 id) const { return _gfbbt::getBTL_ClassRole1(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassRole2(u32 id) const { return _gfbbt::getBTL_ClassRole2(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassRole3(u32 id) const { return _gfbbt::getBTL_ClassRole3(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassDamageDown(u32 id) const { return _gfbbt::getBTL_ClassDamageDown(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassDamageUP(u32 id) const { return _gfbbt::getBTL_ClassDamageUP(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassHealUP(u32 id) const { return _gfbbt::getBTL_ClassHealUP(*m_BTL_Class, id); }

s32 GfBdatBtl::getBTL_ClassAutoHate(u32 id) const { return _gfbbt::getBTL_ClassAutoHate(*m_BTL_Class, id); }

s32 GfBdatBtl::getBTL_ClassArtsHate(u32 id) const { return _gfbbt::getBTL_ClassArtsHate(*m_BTL_Class, id); }

u32 GfBdatBtl::getBTL_ClassRole(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_ClassRole1, _gfbbt::getBTL_ClassRole2, _gfbbt::getBTL_ClassRole3};
  return getters[index](*m_BTL_Class, id);
}

u32 GfBdatBtl::getBTL_EnhanceStart() const { return Bdat::getIdTop(m_BTL_Enhance->unknown00); }

u32 GfBdatBtl::getBTL_EnhanceEnd() const { return Bdat::getIdTop(m_BTL_Enhance->unknown00) + Bdat::getIdCount(m_BTL_Enhance->unknown00); }

u32 GfBdatBtl::getBTL_EnhanceEnhanceEffect(u32 id) const { return _gfbbt::getBTL_EnhanceEnhanceEffect(*m_BTL_Enhance, id); }

f32 GfBdatBtl::getBTL_EnhanceParam1(u32 id) const { return _gfbbt::getBTL_EnhanceParam1(*m_BTL_Enhance, id); }

f32 GfBdatBtl::getBTL_EnhanceParam2(u32 id) const { return _gfbbt::getBTL_EnhanceParam2(*m_BTL_Enhance, id); }

u32 GfBdatBtl::getBTL_EnhanceCaption(u32 id) const { return _gfbbt::getBTL_EnhanceCaption(*m_BTL_Enhance, id); }

u32 GfBdatBtl::getBTL_EnhanceEffStart() const { return Bdat::getIdTop(m_BTL_EnhanceEff->unknown00); }

u32 GfBdatBtl::getBTL_EnhanceEffEnd() const { return Bdat::getIdTop(m_BTL_EnhanceEff->unknown00) + Bdat::getIdCount(m_BTL_EnhanceEff->unknown00); }

u32 GfBdatBtl::getBTL_EnhanceEffCategory(u32 id) const { return _gfbbt::getBTL_EnhanceEffCategory(*m_BTL_EnhanceEff, id); }

u32 GfBdatBtl::getBTL_EnhanceEffIcon(u32 id) const { return _gfbbt::getBTL_EnhanceEffIcon(*m_BTL_EnhanceEff, id); }

bool GfBdatBtl::isBTL_EnhanceEffFlagCondition(u32 id) const { return _gfbbt::isBTL_EnhanceEffFlagCondition(*m_BTL_EnhanceEff, id); }

bool GfBdatBtl::isBTL_EnhanceEffFlagUI(u32 id) const { return _gfbbt::isBTL_EnhanceEffFlagUI(*m_BTL_EnhanceEff, id); }

u32 GfBdatBtl::getBTL_EnhanceEffParam(u32 id) const { return _gfbbt::getBTL_EnhanceEffParam(*m_BTL_EnhanceEff, id); }

u32 GfBdatBtl::getBTL_EnhanceEffName(u32 id) const { return _gfbbt::getBTL_EnhanceEffName(*m_BTL_EnhanceEff, id); }

u32 GfBdatBtl::getBTL_EnhanceEffDirect(u32 id) const { return _gfbbt::getBTL_EnhanceEffDirect(*m_BTL_EnhanceEff, id); }

u32 GfBdatBtl::getBTL_Skill_BlStart() const { return Bdat::getIdTop(m_BTL_Skill_Bl->unknown00); }

u32 GfBdatBtl::getBTL_Skill_BlEnd() const { return Bdat::getIdTop(m_BTL_Skill_Bl->unknown00) + Bdat::getIdCount(m_BTL_Skill_Bl->unknown00); }

u32 GfBdatBtl::getBTL_Skill_BlName(u32 id) const { return _gfbbt::getBTL_Skill_BlName(*m_BTL_Skill_Bl, id); }

const char *GfBdatBtl::getBTL_Skill_BlDebugName(u32 id) const { return _gfbbt::getBTL_Skill_BlDebugName(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance1(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance1(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance2(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance2(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance3(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance3(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance4(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance4(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance5(u32 id) const { return _gfbbt::getBTL_Skill_BlEnhance5(*m_BTL_Skill_Bl, id); }

bool GfBdatBtl::isBTL_Skill_BlFlagcommon(u32 id) const { return _gfbbt::isBTL_Skill_BlFlagcommon(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlTank(u32 id) const { return _gfbbt::getBTL_Skill_BlTank(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlAttacker(u32 id) const { return _gfbbt::getBTL_Skill_BlAttacker(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlHealer(u32 id) const { return _gfbbt::getBTL_Skill_BlHealer(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlUI(u32 id) const { return _gfbbt::getBTL_Skill_BlUI(*m_BTL_Skill_Bl, id); }

u32 GfBdatBtl::getBTL_Skill_BlEnhance(u32 skill, u32 level) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {
      _gfbbt::getBTL_Skill_BlEnhance1, _gfbbt::getBTL_Skill_BlEnhance2, _gfbbt::getBTL_Skill_BlEnhance3, _gfbbt::getBTL_Skill_BlEnhance4, _gfbbt::getBTL_Skill_BlEnhance5};
  return getters[level](*m_BTL_Skill_Bl, skill);
}

u32 GfBdatBtl::getBTL_Skill_DrStart() const { return Bdat::getIdTop(m_BTL_Skill_Dr->unknown00); }

u32 GfBdatBtl::getBTL_Skill_DrEnd() const { return Bdat::getIdTop(m_BTL_Skill_Dr->unknown00) + Bdat::getIdCount(m_BTL_Skill_Dr->unknown00); }

u32 GfBdatBtl::getBTL_Skill_DrName(u32 id) const { return _gfbbt::getBTL_Skill_DrName(*m_BTL_Skill_Dr, id); }

const char *GfBdatBtl::getBTL_Skill_DrDebugName(u32 id) const { return _gfbbt::getBTL_Skill_DrDebugName(*m_BTL_Skill_Dr, id); }

u32 GfBdatBtl::getBTL_Skill_DrEnhance(u32 id) const { return _gfbbt::getBTL_Skill_DrEnhance(*m_BTL_Skill_Dr, id); }

u32 GfBdatBtl::getBTL_Skill_DrUI(u32 id) const { return _gfbbt::getBTL_Skill_DrUI(*m_BTL_Skill_Dr, id); }

u32 GfBdatBtl::getBTL_BuffStart() const { return Bdat::getIdTop(m_BTL_Buff->unknown00); }

u32 GfBdatBtl::getBTL_BuffEnd() const { return Bdat::getIdTop(m_BTL_Buff->unknown00) + Bdat::getIdCount(m_BTL_Buff->unknown00); }

u32 GfBdatBtl::getBTL_BuffName(u32 id) const { return _gfbbt::getBTL_BuffName(*m_BTL_Buff, id); }

const char *GfBdatBtl::getBTL_BuffDebugName(u32 id) const { return _gfbbt::getBTL_BuffDebugName(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffCaption(u32 id) const { return _gfbbt::getBTL_BuffCaption(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffBaseNum(u32 id) const { return _gfbbt::getBTL_BuffBaseNum(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffBaseTime(u32 id) const { return _gfbbt::getBTL_BuffBaseTime(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffBaseRecast(u32 id) const { return _gfbbt::getBTL_BuffBaseRecast(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffBaseProb(u32 id) const { return _gfbbt::getBTL_BuffBaseProb(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffInterval(u32 id) const { return _gfbbt::getBTL_BuffInterval(*m_BTL_Buff, id); }

const char *GfBdatBtl::getBTL_BuffEffect(u32 id) const { return _gfbbt::getBTL_BuffEffect(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_BuffIcon(u32 id) const { return _gfbbt::getBTL_BuffIcon(*m_BTL_Buff, id); }

u32 GfBdatBtl::getBTL_Bl_PersonalityStart() const { return Bdat::getIdTop(m_BTL_Bl_Personality->unknown00); }

u32 GfBdatBtl::getBTL_Bl_PersonalityEnd() const { return Bdat::getIdTop(m_BTL_Bl_Personality->unknown00) + Bdat::getIdCount(m_BTL_Bl_Personality->unknown00); }

bool GfBdatBtl::isBTL_Bl_PersonalityFlagcommon(u32 id) const { return _gfbbt::isBTL_Bl_PersonalityFlagcommon(*m_BTL_Bl_Personality, id); }

u32 GfBdatBtl::getBTL_Bl_PersonalityKizunaBase(u32 id) const { return _gfbbt::getBTL_Bl_PersonalityKizunaBase(*m_BTL_Bl_Personality, id); }

u32 GfBdatBtl::getBTL_Bl_PersonalityVoiceID(u32 id) const { return _gfbbt::getBTL_Bl_PersonalityVoiceID(*m_BTL_Bl_Personality, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkStart() const { return Bdat::getIdTop(m_BTL_Bl_KizunaLink->unknown00); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkEnd() const { return Bdat::getIdTop(m_BTL_Bl_KizunaLink->unknown00) + Bdat::getIdCount(m_BTL_Bl_KizunaLink->unknown00); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkLinkNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkLinkNum(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkDeadNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkDeadNum(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppStNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppStNum(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppEndNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppEndNum(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppCond(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppCond(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkAppCondNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkAppCondNum(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkReJudgef(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkReJudgef(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSpActType(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSpActType(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSpActNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSpActNum(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSpActf(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSpActf(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkStandDir(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkStandDir(*m_BTL_Bl_KizunaLink, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetStart() const { return Bdat::getIdTop(m_BTL_Bl_KizunaLinkSet->unknown00); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetEnd() const { return Bdat::getIdTop(m_BTL_Bl_KizunaLinkSet->unknown00) + Bdat::getIdCount(m_BTL_Bl_KizunaLinkSet->unknown00); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetKizunaLink1(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetKizunaLink1(*m_BTL_Bl_KizunaLinkSet, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetKizunaLink2(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetKizunaLink2(*m_BTL_Bl_KizunaLinkSet, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChType(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetLinkChType(*m_BTL_Bl_KizunaLinkSet, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetLinkChNum(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetLinkChNum(*m_BTL_Bl_KizunaLinkSet, id); }

u32 GfBdatBtl::getBTL_Bl_KizunaLinkSetVoiceID(u32 id) const { return _gfbbt::getBTL_Bl_KizunaLinkSetVoiceID(*m_BTL_Bl_KizunaLinkSet, id); }

u32 GfBdatBtl::getBTL_TestSettingStart() const { return Bdat::getIdTop(m_BTL_TestSetting->unknown00); }

u32 GfBdatBtl::getBTL_TestSettingEnd() const { return Bdat::getIdTop(m_BTL_TestSetting->unknown00) + Bdat::getIdCount(m_BTL_TestSetting->unknown00); }

u32 GfBdatBtl::getBTL_TestSettingDr1(u32 id) const { return _gfbbt::getBTL_TestSettingDr1(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Lv(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Lv(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Bl1(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Bl1(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Bl2(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Bl2(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr1Bl3(u32 id) const { return _gfbbt::getBTL_TestSettingDr1Bl3(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2(u32 id) const { return _gfbbt::getBTL_TestSettingDr2(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Lv(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Lv(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Bl1(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Bl1(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Bl2(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Bl2(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr2Bl3(u32 id) const { return _gfbbt::getBTL_TestSettingDr2Bl3(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3(u32 id) const { return _gfbbt::getBTL_TestSettingDr3(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Lv(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Lv(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Bl1(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Bl1(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Bl2(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Bl2(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr3Bl3(u32 id) const { return _gfbbt::getBTL_TestSettingDr3Bl3(*m_BTL_TestSetting, id); }

u32 GfBdatBtl::getBTL_TestSettingDr(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_TestSettingDr1, _gfbbt::getBTL_TestSettingDr2, _gfbbt::getBTL_TestSettingDr3};
  return getters[index](*m_BTL_TestSetting, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrLv(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_TestSettingDr1Lv, _gfbbt::getBTL_TestSettingDr2Lv, _gfbbt::getBTL_TestSettingDr3Lv};
  return getters[index](*m_BTL_TestSetting, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrBl1(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_TestSettingDr1Bl1, _gfbbt::getBTL_TestSettingDr2Bl1, _gfbbt::getBTL_TestSettingDr3Bl1};
  return getters[index](*m_BTL_TestSetting, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrBl2(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_TestSettingDr1Bl2, _gfbbt::getBTL_TestSettingDr2Bl2, _gfbbt::getBTL_TestSettingDr3Bl2};
  return getters[index](*m_BTL_TestSetting, id);
}

u32 GfBdatBtl::getBTL_TestSettingDrBl3(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_TestSettingDr1Bl3, _gfbbt::getBTL_TestSettingDr2Bl3, _gfbbt::getBTL_TestSettingDr3Bl3};
  return getters[index](*m_BTL_TestSetting, id);
}

u32 GfBdatBtl::getBTL_HanaBaseStart() const { return Bdat::getIdTop(m_BTL_HanaBase->unknown00); }

u32 GfBdatBtl::getBTL_HanaBaseEnd() const { return Bdat::getIdTop(m_BTL_HanaBase->unknown00) + Bdat::getIdCount(m_BTL_HanaBase->unknown00); }

u32 GfBdatBtl::getBTL_HanaBaseNCondNum(u32 id) const { return _gfbbt::getBTL_HanaBaseNCondNum(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseECondNum(u32 id) const { return _gfbbt::getBTL_HanaBaseECondNum(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseNArtsNum(u32 id) const { return _gfbbt::getBTL_HanaBaseNArtsNum(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit1Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit1Num(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit2Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit2Num(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit3Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit3Num(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit4Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit4Num(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit5Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit5Num(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuit6Num(u32 id) const { return _gfbbt::getBTL_HanaBaseCircuit6Num(*m_BTL_HanaBase, id); }

const char *GfBdatBtl::getBTL_HanaBaseUI(u32 id) const { return _gfbbt::getBTL_HanaBaseUI(*m_BTL_HanaBase, id); }

u32 GfBdatBtl::getBTL_HanaBaseCircuitNum(u32 hana, u32 circuit) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_HanaBaseCircuit1Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit2Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit3Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit4Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit5Num,
                                                              _gfbbt::getBTL_HanaBaseCircuit6Num};
  return getters[circuit](*m_BTL_HanaBase, hana);
}

u32 GfBdatBtl::getBTL_HanaPowerStart() const { return Bdat::getIdTop(m_BTL_HanaPower->unknown00); }

u32 GfBdatBtl::getBTL_HanaPowerEnd() const { return Bdat::getIdTop(m_BTL_HanaPower->unknown00) + Bdat::getIdCount(m_BTL_HanaPower->unknown00); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum1(u32 id) const { return _gfbbt::getBTL_HanaPowerPowerNum1(*m_BTL_HanaPower, id); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum2(u32 id) const { return _gfbbt::getBTL_HanaPowerPowerNum2(*m_BTL_HanaPower, id); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum3(u32 id) const { return _gfbbt::getBTL_HanaPowerPowerNum3(*m_BTL_HanaPower, id); }

u32 GfBdatBtl::getBTL_HanaPowerEtherNum1(u32 id) const { return _gfbbt::getBTL_HanaPowerEtherNum1(*m_BTL_HanaPower, id); }

u32 GfBdatBtl::getBTL_HanaPowerEtherNum2(u32 id) const { return _gfbbt::getBTL_HanaPowerEtherNum2(*m_BTL_HanaPower, id); }

u32 GfBdatBtl::getBTL_HanaPowerEtherNum3(u32 id) const { return _gfbbt::getBTL_HanaPowerEtherNum3(*m_BTL_HanaPower, id); }

u32 GfBdatBtl::getBTL_HanaPowerPowerNum(u32 rank, u32 hana) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_HanaPowerPowerNum1, _gfbbt::getBTL_HanaPowerPowerNum2, _gfbbt::getBTL_HanaPowerPowerNum3};
  return getters[hana](*m_BTL_HanaPower, rank);
}

u32 GfBdatBtl::getBTL_HanaPowerEtherNum(u32 rank, u32 hana) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_HanaPowerEtherNum1, _gfbbt::getBTL_HanaPowerEtherNum2, _gfbbt::getBTL_HanaPowerEtherNum3};
  return getters[hana](*m_BTL_HanaPower, rank);
}

u32 GfBdatBtl::getBTL_HanaChipsetStart() const { return Bdat::getIdTop(m_BTL_HanaChipset->unknown00); }

u32 GfBdatBtl::getBTL_HanaChipsetEnd() const { return Bdat::getIdTop(m_BTL_HanaChipset->unknown00) + Bdat::getIdCount(m_BTL_HanaChipset->unknown00); }

u32 GfBdatBtl::getBTL_HanaChipsetRoleParts(u32 id) const { return _gfbbt::getBTL_HanaChipsetRoleParts(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetAtrParts(u32 id) const { return _gfbbt::getBTL_HanaChipsetAtrParts(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts1(u32 id) const { return _gfbbt::getBTL_HanaChipsetNArtsParts1(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts2(u32 id) const { return _gfbbt::getBTL_HanaChipsetNArtsParts2(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts3(u32 id) const { return _gfbbt::getBTL_HanaChipsetNArtsParts3(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts1(u32 id) const { return _gfbbt::getBTL_HanaChipsetNCondParts1(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts2(u32 id) const { return _gfbbt::getBTL_HanaChipsetNCondParts2(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts3(u32 id) const { return _gfbbt::getBTL_HanaChipsetNCondParts3(*m_BTL_HanaChipset, id); }

const char *GfBdatBtl::getBTL_HanaChipsetUI(u32 id) const { return _gfbbt::getBTL_HanaChipsetUI(*m_BTL_HanaChipset, id); }

u32 GfBdatBtl::getBTL_HanaChipsetNArtsParts(u32 hana, u32 slot) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_HanaChipsetNArtsParts1, _gfbbt::getBTL_HanaChipsetNArtsParts2, _gfbbt::getBTL_HanaChipsetNArtsParts3};
  return getters[slot](*m_BTL_HanaChipset, hana);
}

u32 GfBdatBtl::getBTL_HanaChipsetNCondParts(u32 hana, u32 slot) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbbt::getBTL_HanaChipsetNCondParts1, _gfbbt::getBTL_HanaChipsetNCondParts2, _gfbbt::getBTL_HanaChipsetNCondParts3};
  return getters[slot](*m_BTL_HanaChipset, hana);
}

u32 GfBdatBtl::getWildcardDataStart() const { return Bdat::getIdTop(m_wildcardData->unknown00); }

u32 GfBdatBtl::getWildcardDataEnd() const { return Bdat::getIdTop(m_wildcardData->unknown00) + Bdat::getIdCount(m_wildcardData->unknown00); }

f32 GfBdatBtl::getWildcardDatavalueF4(u32 id) const { return _gfbbt::getWildcardDatavalueF4(*m_wildcardData, id); }

u32 GfBdatBtl::getWildcardDatavalueU2(u32 id) const { return _gfbbt::getWildcardDatavalueU2(*m_wildcardData, id); }

u32 GfBdatBtl::getVo_Field_FilterStart() const { return Bdat::getIdTop(m_vo_Field_Filter->unknown00); }

u32 GfBdatBtl::getVo_Field_FilterEnd() const { return Bdat::getIdTop(m_vo_Field_Filter->unknown00) + Bdat::getIdCount(m_vo_Field_Filter->unknown00); }

const char *GfBdatBtl::getVo_Field_FilterTargetFile(u32 id) const { return _gfbbt::getVo_Field_FilterTargetFile(*m_vo_Field_Filter, id); }

u32 GfBdatBtl::getVo_Field_FilterCondition(u32 id) const { return _gfbbt::getVo_Field_FilterCondition(*m_vo_Field_Filter, id); }

const char *GfBdatBtl::getVo_Field_FilterChangeFile(u32 id) const { return _gfbbt::getVo_Field_FilterChangeFile(*m_vo_Field_Filter, id); }

} // namespace gf
