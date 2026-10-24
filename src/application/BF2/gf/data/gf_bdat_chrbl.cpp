#include "gf/data/gf_bdat_chrbl.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbcb {

enum {
  ChrBlName,
  ChrBlDebugName,
  ChrBlRace,
  ChrBlRotateLimitPitch,
  ChrBlRotateLimitRoll,
  ChrBlGender,
  ChrBlQuestRace,
  ChrBlModel,
  ChrBlMotion,
  ChrBlAddMotion,
  ChrBlCondition,
  ChrBlModel2,
  ChrBlMotion2,
  ChrBlStill,
  ChrBlVoice,
  ChrBlClipEvent,
  ChrBlCom_SE,
  ChrBlSePack,
  ChrBlCom_Eff,
  ChrBlCom_Vo,
  ChrBlOffsetID,
  ChrBlEyeRot,
  ChrBlChestHeight,
  ChrBlLandingHeight,
  ChrBlFootStep,
  ChrBlFootStepEffect,
  ChrBlWeaponType,
  ChrBlScale,
  ChrBlWpnScale,
  ChrBlFlagOnlyWpn,
  ChrBlFlagOnlyWpnFlag,
  ChrBlPrivateWpnR,
  ChrBlPrivateWpnL,
  ChrBlPrivateWpnR_Driver,
  ChrBlPrivateWpnL_Driver,
  ChrBlWpnrOut,
  ChrBlWpnlOut,
  ChrBlOrbNum,
  ChrBlAtr,
  ChrBlPersonality,
  ChrBlCoolTime,
  ChrBlDefWeapon,
  ChrBlBArts1,
  ChrBlBArts2,
  ChrBlBArts3,
  ChrBlBartsEx,
  ChrBlBartsEx2,
  ChrBlNArts1,
  ChrBlNArtsRecastRev1,
  ChrBlNArts2,
  ChrBlNArtsRecastRev2,
  ChrBlNArts3,
  ChrBlNArtsRecastRev3,
  ChrBlBSkill1,
  ChrBlBSkill2,
  ChrBlBSkill3,
  ChrBlPArmor,
  ChrBlEArmor,
  ChrBlHpMaxRev,
  ChrBlStrengthRev,
  ChrBlPowEtherRev,
  ChrBlDexRev,
  ChrBlAgilityRev,
  ChrBlLuckRev,
  ChrBlBKLSet,
  ChrBlFSkill1,
  ChrBlFSkill2,
  ChrBlFSkill3,
  ChrBlArtsAchievement1,
  ChrBlArtsAchievement2,
  ChrBlArtsAchievement3,
  ChrBlSkillAchievement1,
  ChrBlSkillAchievement2,
  ChrBlSkillAchievement3,
  ChrBlFskillAchivement1,
  ChrBlFskillAchivement2,
  ChrBlFskillAchivement3,
  ChrBlKeyAchievement,
  ChrBlIdeaBlue,
  ChrBlIdeaRed,
  ChrBlIdeaWhite,
  ChrBlIdeaBlack,
  ChrBlFavoriteCategory1,
  ChrBlFavoriteCategory2,
  ChrBlFavoriteItem1,
  ChrBlFavoriteItem2,
  ChrBlCreateEventID,
  ChrBlNormalTalk,
  ChrBlCollisionId,
  ChrBlBladeSize,
  ChrBlMemorySlot,
  ChrBlEventAsset,
  ChrBlCenterBone,
  ChrBlCamBone,
  ChrBlMerceName,
  ChrBlReleaseLock,
  ChrBlCreateInfo,
  ChrBlExtraParts1,
  ChrBlExtraParts2,
  ChrBlExtraParts3,
  ChrBlExtraParts4,
  ChrBlMnuCastName,
  ChrBlMnuIlustName,
  ChrBlMnuVoice1,
  ChrBlMnuVoice2,
  ChrBlMnuVoice3,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initChrBlName(const CBdatWrapper &wrapper) { s_members[ChrBlName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getChrBlName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlName], id, 2).valueU16;
}

void initChrBlDebugName(const CBdatWrapper &wrapper) { s_members[ChrBlDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getChrBlDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlDebugName], id, 7).valueString;
}

void initChrBlRace(const CBdatWrapper &wrapper) { s_members[ChrBlRace] = Bdat::getMember(wrapper.data, "Race"); }

u32 getChrBlRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlRace] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlRace], id, 1).valueU8;
}

void initChrBlRotateLimitPitch(const CBdatWrapper &wrapper) { s_members[ChrBlRotateLimitPitch] = Bdat::getMember(wrapper.data, "RotateLimitPitch"); }

u32 getChrBlRotateLimitPitch(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlRotateLimitPitch] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlRotateLimitPitch], id, 1).valueU8;
}

void initChrBlRotateLimitRoll(const CBdatWrapper &wrapper) { s_members[ChrBlRotateLimitRoll] = Bdat::getMember(wrapper.data, "RotateLimitRoll"); }

u32 getChrBlRotateLimitRoll(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlRotateLimitRoll] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlRotateLimitRoll], id, 1).valueU8;
}

void initChrBlGender(const CBdatWrapper &wrapper) { s_members[ChrBlGender] = Bdat::getMember(wrapper.data, "Gender"); }

u32 getChrBlGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlGender] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlGender], id, 1).valueU8;
}

void initChrBlQuestRace(const CBdatWrapper &wrapper) { s_members[ChrBlQuestRace] = Bdat::getMember(wrapper.data, "QuestRace"); }

u32 getChrBlQuestRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlQuestRace] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlQuestRace], id, 1).valueU8;
}

void initChrBlModel(const CBdatWrapper &wrapper) { s_members[ChrBlModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getChrBlModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlModel] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlModel], id, 7).valueString;
}

void initChrBlMotion(const CBdatWrapper &wrapper) { s_members[ChrBlMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getChrBlMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlMotion], id, 7).valueString;
}

void initChrBlAddMotion(const CBdatWrapper &wrapper) { s_members[ChrBlAddMotion] = Bdat::getMember(wrapper.data, "AddMotion"); }

const char *getChrBlAddMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlAddMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlAddMotion], id, 7).valueString;
}

void initChrBlCondition(const CBdatWrapper &wrapper) { s_members[ChrBlCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getChrBlCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlCondition], id, 2).valueU16;
}

void initChrBlModel2(const CBdatWrapper &wrapper) { s_members[ChrBlModel2] = Bdat::getMember(wrapper.data, "Model2"); }

const char *getChrBlModel2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlModel2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlModel2], id, 7).valueString;
}

void initChrBlMotion2(const CBdatWrapper &wrapper) { s_members[ChrBlMotion2] = Bdat::getMember(wrapper.data, "Motion2"); }

const char *getChrBlMotion2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMotion2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlMotion2], id, 7).valueString;
}

void initChrBlStill(const CBdatWrapper &wrapper) { s_members[ChrBlStill] = Bdat::getMember(wrapper.data, "Still"); }

u32 getChrBlStill(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlStill] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlStill], id, 2).valueU16;
}

void initChrBlVoice(const CBdatWrapper &wrapper) { s_members[ChrBlVoice] = Bdat::getMember(wrapper.data, "Voice"); }

const char *getChrBlVoice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlVoice] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlVoice], id, 7).valueString;
}

void initChrBlClipEvent(const CBdatWrapper &wrapper) { s_members[ChrBlClipEvent] = Bdat::getMember(wrapper.data, "ClipEvent"); }

const char *getChrBlClipEvent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlClipEvent] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlClipEvent], id, 7).valueString;
}

void initChrBlCom_SE(const CBdatWrapper &wrapper) { s_members[ChrBlCom_SE] = Bdat::getMember(wrapper.data, "Com_SE"); }

const char *getChrBlCom_SE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCom_SE] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlCom_SE], id, 7).valueString;
}

void initChrBlSePack(const CBdatWrapper &wrapper) { s_members[ChrBlSePack] = Bdat::getMember(wrapper.data, "SePack"); }

const char *getChrBlSePack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlSePack] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlSePack], id, 7).valueString;
}

void initChrBlCom_Eff(const CBdatWrapper &wrapper) { s_members[ChrBlCom_Eff] = Bdat::getMember(wrapper.data, "Com_Eff"); }

const char *getChrBlCom_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCom_Eff] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlCom_Eff], id, 7).valueString;
}

void initChrBlCom_Vo(const CBdatWrapper &wrapper) { s_members[ChrBlCom_Vo] = Bdat::getMember(wrapper.data, "Com_Vo"); }

const char *getChrBlCom_Vo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCom_Vo] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlCom_Vo], id, 7).valueString;
}

void initChrBlOffsetID(const CBdatWrapper &wrapper) { s_members[ChrBlOffsetID] = Bdat::getMember(wrapper.data, "OffsetID"); }

u32 getChrBlOffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlOffsetID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlOffsetID], id, 2).valueU16;
}

void initChrBlEyeRot(const CBdatWrapper &wrapper) { s_members[ChrBlEyeRot] = Bdat::getMember(wrapper.data, "EyeRot"); }

u32 getChrBlEyeRot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlEyeRot] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlEyeRot], id, 1).valueU8;
}

void initChrBlChestHeight(const CBdatWrapper &wrapper) { s_members[ChrBlChestHeight] = Bdat::getMember(wrapper.data, "ChestHeight"); }

u32 getChrBlChestHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlChestHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlChestHeight], id, 2).valueU16;
}

void initChrBlLandingHeight(const CBdatWrapper &wrapper) { s_members[ChrBlLandingHeight] = Bdat::getMember(wrapper.data, "LandingHeight"); }

u32 getChrBlLandingHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlLandingHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlLandingHeight], id, 2).valueU16;
}

void initChrBlFootStep(const CBdatWrapper &wrapper) { s_members[ChrBlFootStep] = Bdat::getMember(wrapper.data, "FootStep"); }

u32 getChrBlFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFootStep] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFootStep], id, 1).valueU8;
}

void initChrBlFootStepEffect(const CBdatWrapper &wrapper) { s_members[ChrBlFootStepEffect] = Bdat::getMember(wrapper.data, "FootStepEffect"); }

u32 getChrBlFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFootStepEffect], id, 1).valueU8;
}

void initChrBlWeaponType(const CBdatWrapper &wrapper) { s_members[ChrBlWeaponType] = Bdat::getMember(wrapper.data, "WeaponType"); }

u32 getChrBlWeaponType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlWeaponType] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlWeaponType], id, 1).valueU8;
}

void initChrBlScale(const CBdatWrapper &wrapper) { s_members[ChrBlScale] = Bdat::getMember(wrapper.data, "Scale"); }

u32 getChrBlScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlScale] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlScale], id, 2).valueU16;
}

void initChrBlWpnScale(const CBdatWrapper &wrapper) { s_members[ChrBlWpnScale] = Bdat::getMember(wrapper.data, "WpnScale"); }

u32 getChrBlWpnScale(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlWpnScale] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlWpnScale], id, 2).valueU16;
}

void initChrBlFlagOnlyWpn(const CBdatWrapper &wrapper) {
  s_members[ChrBlFlagOnlyWpn] = Bdat::getMember(wrapper.data, "Flag");
  s_members[ChrBlFlagOnlyWpnFlag] = Bdat::getMember(wrapper.data, "OnlyWpn");
}

bool isChrBlFlagOnlyWpn(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFlagOnlyWpn] == nullptr || s_members[ChrBlFlagOnlyWpnFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return false;
  }

  return wrapper.getFlagVal(s_members[ChrBlFlagOnlyWpn], id, s_members[ChrBlFlagOnlyWpnFlag]) != 0;
}

void initChrBlPrivateWpnR(const CBdatWrapper &wrapper) { s_members[ChrBlPrivateWpnR] = Bdat::getMember(wrapper.data, "PrivateWpnR"); }

u32 getChrBlPrivateWpnR(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPrivateWpnR] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPrivateWpnR], id, 2).valueU16;
}

void initChrBlPrivateWpnL(const CBdatWrapper &wrapper) { s_members[ChrBlPrivateWpnL] = Bdat::getMember(wrapper.data, "PrivateWpnL"); }

u32 getChrBlPrivateWpnL(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPrivateWpnL] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPrivateWpnL], id, 2).valueU16;
}

void initChrBlPrivateWpnR_Driver(const CBdatWrapper &wrapper) { s_members[ChrBlPrivateWpnR_Driver] = Bdat::getMember(wrapper.data, "PrivateWpnR_Driver"); }

u32 getChrBlPrivateWpnR_Driver(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPrivateWpnR_Driver] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPrivateWpnR_Driver], id, 2).valueU16;
}

void initChrBlPrivateWpnL_Driver(const CBdatWrapper &wrapper) { s_members[ChrBlPrivateWpnL_Driver] = Bdat::getMember(wrapper.data, "PrivateWpnL_Driver"); }

u32 getChrBlPrivateWpnL_Driver(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPrivateWpnL_Driver] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPrivateWpnL_Driver], id, 2).valueU16;
}

void initChrBlWpnrOut(const CBdatWrapper &wrapper) { s_members[ChrBlWpnrOut] = Bdat::getMember(wrapper.data, "WpnrOut"); }

const char *getChrBlWpnrOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlWpnrOut] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlWpnrOut], id, 7).valueString;
}

void initChrBlWpnlOut(const CBdatWrapper &wrapper) { s_members[ChrBlWpnlOut] = Bdat::getMember(wrapper.data, "WpnlOut"); }

const char *getChrBlWpnlOut(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlWpnlOut] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlWpnlOut], id, 7).valueString;
}

void initChrBlOrbNum(const CBdatWrapper &wrapper) { s_members[ChrBlOrbNum] = Bdat::getMember(wrapper.data, "OrbNum"); }

u32 getChrBlOrbNum(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlOrbNum] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlOrbNum], id, 1).valueU8;
}

void initChrBlAtr(const CBdatWrapper &wrapper) { s_members[ChrBlAtr] = Bdat::getMember(wrapper.data, "Atr"); }

u32 getChrBlAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlAtr], id, 1).valueU8;
}

void initChrBlPersonality(const CBdatWrapper &wrapper) { s_members[ChrBlPersonality] = Bdat::getMember(wrapper.data, "Personality"); }

u32 getChrBlPersonality(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPersonality] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPersonality], id, 1).valueU8;
}

void initChrBlCoolTime(const CBdatWrapper &wrapper) { s_members[ChrBlCoolTime] = Bdat::getMember(wrapper.data, "CoolTime"); }

u32 getChrBlCoolTime(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCoolTime] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlCoolTime], id, 2).valueU16;
}

void initChrBlDefWeapon(const CBdatWrapper &wrapper) { s_members[ChrBlDefWeapon] = Bdat::getMember(wrapper.data, "DefWeapon"); }

u32 getChrBlDefWeapon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlDefWeapon] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlDefWeapon], id, 2).valueU16;
}

void initChrBlBArts1(const CBdatWrapper &wrapper) { s_members[ChrBlBArts1] = Bdat::getMember(wrapper.data, "BArts1"); }

u32 getChrBlBArts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBArts1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBArts1], id, 2).valueU16;
}

void initChrBlBArts2(const CBdatWrapper &wrapper) { s_members[ChrBlBArts2] = Bdat::getMember(wrapper.data, "BArts2"); }

u32 getChrBlBArts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBArts2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBArts2], id, 2).valueU16;
}

void initChrBlBArts3(const CBdatWrapper &wrapper) { s_members[ChrBlBArts3] = Bdat::getMember(wrapper.data, "BArts3"); }

u32 getChrBlBArts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBArts3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBArts3], id, 2).valueU16;
}

void initChrBlBartsEx(const CBdatWrapper &wrapper) { s_members[ChrBlBartsEx] = Bdat::getMember(wrapper.data, "BartsEx"); }

u32 getChrBlBartsEx(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBartsEx] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBartsEx], id, 2).valueU16;
}

void initChrBlBartsEx2(const CBdatWrapper &wrapper) { s_members[ChrBlBartsEx2] = Bdat::getMember(wrapper.data, "BartsEx2"); }

u32 getChrBlBartsEx2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBartsEx2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBartsEx2], id, 2).valueU16;
}

void initChrBlNArts1(const CBdatWrapper &wrapper) { s_members[ChrBlNArts1] = Bdat::getMember(wrapper.data, "NArts1"); }

u32 getChrBlNArts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNArts1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNArts1], id, 1).valueU8;
}

void initChrBlNArtsRecastRev1(const CBdatWrapper &wrapper) { s_members[ChrBlNArtsRecastRev1] = Bdat::getMember(wrapper.data, "NArtsRecastRev1"); }

u32 getChrBlNArtsRecastRev1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNArtsRecastRev1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNArtsRecastRev1], id, 1).valueU8;
}

void initChrBlNArts2(const CBdatWrapper &wrapper) { s_members[ChrBlNArts2] = Bdat::getMember(wrapper.data, "NArts2"); }

u32 getChrBlNArts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNArts2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNArts2], id, 1).valueU8;
}

void initChrBlNArtsRecastRev2(const CBdatWrapper &wrapper) { s_members[ChrBlNArtsRecastRev2] = Bdat::getMember(wrapper.data, "NArtsRecastRev2"); }

u32 getChrBlNArtsRecastRev2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNArtsRecastRev2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNArtsRecastRev2], id, 1).valueU8;
}

void initChrBlNArts3(const CBdatWrapper &wrapper) { s_members[ChrBlNArts3] = Bdat::getMember(wrapper.data, "NArts3"); }

u32 getChrBlNArts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNArts3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNArts3], id, 1).valueU8;
}

void initChrBlNArtsRecastRev3(const CBdatWrapper &wrapper) { s_members[ChrBlNArtsRecastRev3] = Bdat::getMember(wrapper.data, "NArtsRecastRev3"); }

u32 getChrBlNArtsRecastRev3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNArtsRecastRev3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNArtsRecastRev3], id, 1).valueU8;
}

void initChrBlBSkill1(const CBdatWrapper &wrapper) { s_members[ChrBlBSkill1] = Bdat::getMember(wrapper.data, "BSkill1"); }

u32 getChrBlBSkill1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBSkill1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBSkill1], id, 2).valueU16;
}

void initChrBlBSkill2(const CBdatWrapper &wrapper) { s_members[ChrBlBSkill2] = Bdat::getMember(wrapper.data, "BSkill2"); }

u32 getChrBlBSkill2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBSkill2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBSkill2], id, 2).valueU16;
}

void initChrBlBSkill3(const CBdatWrapper &wrapper) { s_members[ChrBlBSkill3] = Bdat::getMember(wrapper.data, "BSkill3"); }

u32 getChrBlBSkill3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBSkill3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBSkill3], id, 2).valueU16;
}

void initChrBlPArmor(const CBdatWrapper &wrapper) { s_members[ChrBlPArmor] = Bdat::getMember(wrapper.data, "PArmor"); }

u32 getChrBlPArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPArmor], id, 1).valueU8;
}

void initChrBlEArmor(const CBdatWrapper &wrapper) { s_members[ChrBlEArmor] = Bdat::getMember(wrapper.data, "EArmor"); }

u32 getChrBlEArmor(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlEArmor] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlEArmor], id, 1).valueU8;
}

void initChrBlHpMaxRev(const CBdatWrapper &wrapper) { s_members[ChrBlHpMaxRev] = Bdat::getMember(wrapper.data, "HpMaxRev"); }

u32 getChrBlHpMaxRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlHpMaxRev] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlHpMaxRev], id, 1).valueU8;
}

void initChrBlStrengthRev(const CBdatWrapper &wrapper) { s_members[ChrBlStrengthRev] = Bdat::getMember(wrapper.data, "StrengthRev"); }

u32 getChrBlStrengthRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlStrengthRev] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlStrengthRev], id, 1).valueU8;
}

void initChrBlPowEtherRev(const CBdatWrapper &wrapper) { s_members[ChrBlPowEtherRev] = Bdat::getMember(wrapper.data, "PowEtherRev"); }

u32 getChrBlPowEtherRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlPowEtherRev] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlPowEtherRev], id, 1).valueU8;
}

void initChrBlDexRev(const CBdatWrapper &wrapper) { s_members[ChrBlDexRev] = Bdat::getMember(wrapper.data, "DexRev"); }

u32 getChrBlDexRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlDexRev] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlDexRev], id, 1).valueU8;
}

void initChrBlAgilityRev(const CBdatWrapper &wrapper) { s_members[ChrBlAgilityRev] = Bdat::getMember(wrapper.data, "AgilityRev"); }

u32 getChrBlAgilityRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlAgilityRev] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlAgilityRev], id, 1).valueU8;
}

void initChrBlLuckRev(const CBdatWrapper &wrapper) { s_members[ChrBlLuckRev] = Bdat::getMember(wrapper.data, "LuckRev"); }

u32 getChrBlLuckRev(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlLuckRev] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlLuckRev], id, 1).valueU8;
}

void initChrBlBKLSet(const CBdatWrapper &wrapper) { s_members[ChrBlBKLSet] = Bdat::getMember(wrapper.data, "BKLSet"); }

u32 getChrBlBKLSet(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBKLSet] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBKLSet], id, 2).valueU16;
}

void initChrBlFSkill1(const CBdatWrapper &wrapper) { s_members[ChrBlFSkill1] = Bdat::getMember(wrapper.data, "FSkill1"); }

u32 getChrBlFSkill1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFSkill1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFSkill1], id, 2).valueU16;
}

void initChrBlFSkill2(const CBdatWrapper &wrapper) { s_members[ChrBlFSkill2] = Bdat::getMember(wrapper.data, "FSkill2"); }

u32 getChrBlFSkill2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFSkill2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFSkill2], id, 2).valueU16;
}

void initChrBlFSkill3(const CBdatWrapper &wrapper) { s_members[ChrBlFSkill3] = Bdat::getMember(wrapper.data, "FSkill3"); }

u32 getChrBlFSkill3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFSkill3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFSkill3], id, 2).valueU16;
}

void initChrBlArtsAchievement1(const CBdatWrapper &wrapper) { s_members[ChrBlArtsAchievement1] = Bdat::getMember(wrapper.data, "ArtsAchievement1"); }

u32 getChrBlArtsAchievement1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlArtsAchievement1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlArtsAchievement1], id, 2).valueU16;
}

void initChrBlArtsAchievement2(const CBdatWrapper &wrapper) { s_members[ChrBlArtsAchievement2] = Bdat::getMember(wrapper.data, "ArtsAchievement2"); }

u32 getChrBlArtsAchievement2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlArtsAchievement2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlArtsAchievement2], id, 2).valueU16;
}

void initChrBlArtsAchievement3(const CBdatWrapper &wrapper) { s_members[ChrBlArtsAchievement3] = Bdat::getMember(wrapper.data, "ArtsAchievement3"); }

u32 getChrBlArtsAchievement3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlArtsAchievement3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlArtsAchievement3], id, 2).valueU16;
}

void initChrBlSkillAchievement1(const CBdatWrapper &wrapper) { s_members[ChrBlSkillAchievement1] = Bdat::getMember(wrapper.data, "SkillAchievement1"); }

u32 getChrBlSkillAchievement1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlSkillAchievement1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlSkillAchievement1], id, 2).valueU16;
}

void initChrBlSkillAchievement2(const CBdatWrapper &wrapper) { s_members[ChrBlSkillAchievement2] = Bdat::getMember(wrapper.data, "SkillAchievement2"); }

u32 getChrBlSkillAchievement2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlSkillAchievement2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlSkillAchievement2], id, 2).valueU16;
}

void initChrBlSkillAchievement3(const CBdatWrapper &wrapper) { s_members[ChrBlSkillAchievement3] = Bdat::getMember(wrapper.data, "SkillAchievement3"); }

u32 getChrBlSkillAchievement3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlSkillAchievement3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlSkillAchievement3], id, 2).valueU16;
}

void initChrBlFskillAchivement1(const CBdatWrapper &wrapper) { s_members[ChrBlFskillAchivement1] = Bdat::getMember(wrapper.data, "FskillAchivement1"); }

u32 getChrBlFskillAchivement1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFskillAchivement1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFskillAchivement1], id, 2).valueU16;
}

void initChrBlFskillAchivement2(const CBdatWrapper &wrapper) { s_members[ChrBlFskillAchivement2] = Bdat::getMember(wrapper.data, "FskillAchivement2"); }

u32 getChrBlFskillAchivement2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFskillAchivement2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFskillAchivement2], id, 2).valueU16;
}

void initChrBlFskillAchivement3(const CBdatWrapper &wrapper) { s_members[ChrBlFskillAchivement3] = Bdat::getMember(wrapper.data, "FskillAchivement3"); }

u32 getChrBlFskillAchivement3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFskillAchivement3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFskillAchivement3], id, 2).valueU16;
}

void initChrBlKeyAchievement(const CBdatWrapper &wrapper) { s_members[ChrBlKeyAchievement] = Bdat::getMember(wrapper.data, "KeyAchievement"); }

u32 getChrBlKeyAchievement(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlKeyAchievement] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlKeyAchievement], id, 2).valueU16;
}

void initChrBlIdeaBlue(const CBdatWrapper &wrapper) { s_members[ChrBlIdeaBlue] = Bdat::getMember(wrapper.data, "IdeaBlue"); }

u32 getChrBlIdeaBlue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlIdeaBlue] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlIdeaBlue], id, 1).valueU8;
}

void initChrBlIdeaRed(const CBdatWrapper &wrapper) { s_members[ChrBlIdeaRed] = Bdat::getMember(wrapper.data, "IdeaRed"); }

u32 getChrBlIdeaRed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlIdeaRed] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlIdeaRed], id, 1).valueU8;
}

void initChrBlIdeaWhite(const CBdatWrapper &wrapper) { s_members[ChrBlIdeaWhite] = Bdat::getMember(wrapper.data, "IdeaWhite"); }

u32 getChrBlIdeaWhite(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlIdeaWhite] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlIdeaWhite], id, 1).valueU8;
}

void initChrBlIdeaBlack(const CBdatWrapper &wrapper) { s_members[ChrBlIdeaBlack] = Bdat::getMember(wrapper.data, "IdeaBlack"); }

u32 getChrBlIdeaBlack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlIdeaBlack] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlIdeaBlack], id, 1).valueU8;
}

void initChrBlFavoriteCategory1(const CBdatWrapper &wrapper) { s_members[ChrBlFavoriteCategory1] = Bdat::getMember(wrapper.data, "FavoriteCategory1"); }

u32 getChrBlFavoriteCategory1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFavoriteCategory1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFavoriteCategory1], id, 2).valueU16;
}

void initChrBlFavoriteCategory2(const CBdatWrapper &wrapper) { s_members[ChrBlFavoriteCategory2] = Bdat::getMember(wrapper.data, "FavoriteCategory2"); }

u32 getChrBlFavoriteCategory2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFavoriteCategory2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFavoriteCategory2], id, 2).valueU16;
}

void initChrBlFavoriteItem1(const CBdatWrapper &wrapper) { s_members[ChrBlFavoriteItem1] = Bdat::getMember(wrapper.data, "FavoriteItem1"); }

u32 getChrBlFavoriteItem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFavoriteItem1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFavoriteItem1], id, 2).valueU16;
}

void initChrBlFavoriteItem2(const CBdatWrapper &wrapper) { s_members[ChrBlFavoriteItem2] = Bdat::getMember(wrapper.data, "FavoriteItem2"); }

u32 getChrBlFavoriteItem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlFavoriteItem2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlFavoriteItem2], id, 2).valueU16;
}

void initChrBlCreateEventID(const CBdatWrapper &wrapper) { s_members[ChrBlCreateEventID] = Bdat::getMember(wrapper.data, "CreateEventID"); }

u32 getChrBlCreateEventID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCreateEventID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlCreateEventID], id, 2).valueU16;
}

void initChrBlNormalTalk(const CBdatWrapper &wrapper) { s_members[ChrBlNormalTalk] = Bdat::getMember(wrapper.data, "NormalTalk"); }

u32 getChrBlNormalTalk(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlNormalTalk] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlNormalTalk], id, 2).valueU16;
}

void initChrBlCollisionId(const CBdatWrapper &wrapper) { s_members[ChrBlCollisionId] = Bdat::getMember(wrapper.data, "CollisionId"); }

u32 getChrBlCollisionId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCollisionId] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlCollisionId], id, 2).valueU16;
}

void initChrBlBladeSize(const CBdatWrapper &wrapper) { s_members[ChrBlBladeSize] = Bdat::getMember(wrapper.data, "BladeSize"); }

u32 getChrBlBladeSize(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlBladeSize] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlBladeSize], id, 1).valueU8;
}

void initChrBlMemorySlot(const CBdatWrapper &wrapper) { s_members[ChrBlMemorySlot] = Bdat::getMember(wrapper.data, "MemorySlot"); }

u32 getChrBlMemorySlot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMemorySlot] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlMemorySlot], id, 1).valueU8;
}

void initChrBlEventAsset(const CBdatWrapper &wrapper) { s_members[ChrBlEventAsset] = Bdat::getMember(wrapper.data, "EventAsset"); }

u32 getChrBlEventAsset(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlEventAsset] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlEventAsset], id, 2).valueU16;
}

void initChrBlCenterBone(const CBdatWrapper &wrapper) { s_members[ChrBlCenterBone] = Bdat::getMember(wrapper.data, "CenterBone"); }

const char *getChrBlCenterBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCenterBone] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlCenterBone], id, 7).valueString;
}

void initChrBlCamBone(const CBdatWrapper &wrapper) { s_members[ChrBlCamBone] = Bdat::getMember(wrapper.data, "CamBone"); }

const char *getChrBlCamBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCamBone] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlCamBone], id, 7).valueString;
}

void initChrBlMerceName(const CBdatWrapper &wrapper) { s_members[ChrBlMerceName] = Bdat::getMember(wrapper.data, "MerceName"); }

u32 getChrBlMerceName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMerceName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlMerceName], id, 2).valueU16;
}

void initChrBlReleaseLock(const CBdatWrapper &wrapper) { s_members[ChrBlReleaseLock] = Bdat::getMember(wrapper.data, "ReleaseLock"); }

u32 getChrBlReleaseLock(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlReleaseLock] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlReleaseLock], id, 1).valueU8;
}

void initChrBlCreateInfo(const CBdatWrapper &wrapper) { s_members[ChrBlCreateInfo] = Bdat::getMember(wrapper.data, "CreateInfo"); }

u32 getChrBlCreateInfo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlCreateInfo] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlCreateInfo], id, 2).valueU16;
}

void initChrBlExtraParts1(const CBdatWrapper &wrapper) { s_members[ChrBlExtraParts1] = Bdat::getMember(wrapper.data, "ExtraParts1"); }

u32 getChrBlExtraParts1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlExtraParts1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlExtraParts1], id, 1).valueU8;
}

void initChrBlExtraParts2(const CBdatWrapper &wrapper) { s_members[ChrBlExtraParts2] = Bdat::getMember(wrapper.data, "ExtraParts2"); }

u32 getChrBlExtraParts2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlExtraParts2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlExtraParts2], id, 1).valueU8;
}

void initChrBlExtraParts3(const CBdatWrapper &wrapper) { s_members[ChrBlExtraParts3] = Bdat::getMember(wrapper.data, "ExtraParts3"); }

u32 getChrBlExtraParts3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlExtraParts3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlExtraParts3], id, 1).valueU8;
}

void initChrBlExtraParts4(const CBdatWrapper &wrapper) { s_members[ChrBlExtraParts4] = Bdat::getMember(wrapper.data, "ExtraParts4"); }

u32 getChrBlExtraParts4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlExtraParts4] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlExtraParts4], id, 1).valueU8;
}

void initChrBlMnuCastName(const CBdatWrapper &wrapper) { s_members[ChrBlMnuCastName] = Bdat::getMember(wrapper.data, "MnuCastName"); }

u32 getChrBlMnuCastName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMnuCastName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlMnuCastName], id, 2).valueU16;
}

void initChrBlMnuIlustName(const CBdatWrapper &wrapper) { s_members[ChrBlMnuIlustName] = Bdat::getMember(wrapper.data, "MnuIlustName"); }

u32 getChrBlMnuIlustName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMnuIlustName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrBlMnuIlustName], id, 2).valueU16;
}

void initChrBlMnuVoice1(const CBdatWrapper &wrapper) { s_members[ChrBlMnuVoice1] = Bdat::getMember(wrapper.data, "MnuVoice1"); }

const char *getChrBlMnuVoice1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMnuVoice1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlMnuVoice1], id, 7).valueString;
}

void initChrBlMnuVoice2(const CBdatWrapper &wrapper) { s_members[ChrBlMnuVoice2] = Bdat::getMember(wrapper.data, "MnuVoice2"); }

const char *getChrBlMnuVoice2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMnuVoice2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlMnuVoice2], id, 7).valueString;
}

void initChrBlMnuVoice3(const CBdatWrapper &wrapper) { s_members[ChrBlMnuVoice3] = Bdat::getMember(wrapper.data, "MnuVoice3"); }

const char *getChrBlMnuVoice3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrBlMnuVoice3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrBlMnuVoice3], id, 7).valueString;
}

} // namespace _gfbcb

GfBdatChrBl::GfBdatChrBl() : m_chrBl(nullptr) { bdatRefresh(); }

GfBdatChrBl::~GfBdatChrBl() { destroyFP(); }

void GfBdatChrBl::destroyFP() {
  if (m_chrBl != nullptr) {
    delete m_chrBl;
    m_chrBl = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                                                                         \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatChrBl::createFP() { m_chrBl = NEW_BDAT_WRAPPER(BDAT_CHR_BL); }

void GfBdatChrBl::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbcb::initChrBlName(*m_chrBl);
  _gfbcb::initChrBlDebugName(*m_chrBl);
  _gfbcb::initChrBlRace(*m_chrBl);
  _gfbcb::initChrBlRotateLimitPitch(*m_chrBl);
  _gfbcb::initChrBlRotateLimitRoll(*m_chrBl);
  _gfbcb::initChrBlGender(*m_chrBl);
  _gfbcb::initChrBlQuestRace(*m_chrBl);
  _gfbcb::initChrBlModel(*m_chrBl);
  _gfbcb::initChrBlMotion(*m_chrBl);
  _gfbcb::initChrBlAddMotion(*m_chrBl);
  _gfbcb::initChrBlCondition(*m_chrBl);
  _gfbcb::initChrBlModel2(*m_chrBl);
  _gfbcb::initChrBlMotion2(*m_chrBl);
  _gfbcb::initChrBlStill(*m_chrBl);
  _gfbcb::initChrBlVoice(*m_chrBl);
  _gfbcb::initChrBlClipEvent(*m_chrBl);
  _gfbcb::initChrBlCom_SE(*m_chrBl);
  _gfbcb::initChrBlSePack(*m_chrBl);
  _gfbcb::initChrBlCom_Eff(*m_chrBl);
  _gfbcb::initChrBlCom_Vo(*m_chrBl);
  _gfbcb::initChrBlOffsetID(*m_chrBl);
  _gfbcb::initChrBlEyeRot(*m_chrBl);
  _gfbcb::initChrBlChestHeight(*m_chrBl);
  _gfbcb::initChrBlLandingHeight(*m_chrBl);
  _gfbcb::initChrBlFootStep(*m_chrBl);
  _gfbcb::initChrBlFootStepEffect(*m_chrBl);
  _gfbcb::initChrBlWeaponType(*m_chrBl);
  _gfbcb::initChrBlScale(*m_chrBl);
  _gfbcb::initChrBlWpnScale(*m_chrBl);
  _gfbcb::initChrBlFlagOnlyWpn(*m_chrBl);
  _gfbcb::initChrBlPrivateWpnR(*m_chrBl);
  _gfbcb::initChrBlPrivateWpnL(*m_chrBl);
  _gfbcb::initChrBlPrivateWpnR_Driver(*m_chrBl);
  _gfbcb::initChrBlPrivateWpnL_Driver(*m_chrBl);
  _gfbcb::initChrBlWpnrOut(*m_chrBl);
  _gfbcb::initChrBlWpnlOut(*m_chrBl);
  _gfbcb::initChrBlOrbNum(*m_chrBl);
  _gfbcb::initChrBlAtr(*m_chrBl);
  _gfbcb::initChrBlPersonality(*m_chrBl);
  _gfbcb::initChrBlCoolTime(*m_chrBl);
  _gfbcb::initChrBlDefWeapon(*m_chrBl);
  _gfbcb::initChrBlBArts1(*m_chrBl);
  _gfbcb::initChrBlBArts2(*m_chrBl);
  _gfbcb::initChrBlBArts3(*m_chrBl);
  _gfbcb::initChrBlBartsEx(*m_chrBl);
  _gfbcb::initChrBlBartsEx2(*m_chrBl);
  _gfbcb::initChrBlNArts1(*m_chrBl);
  _gfbcb::initChrBlNArtsRecastRev1(*m_chrBl);
  _gfbcb::initChrBlNArts2(*m_chrBl);
  _gfbcb::initChrBlNArtsRecastRev2(*m_chrBl);
  _gfbcb::initChrBlNArts3(*m_chrBl);
  _gfbcb::initChrBlNArtsRecastRev3(*m_chrBl);
  _gfbcb::initChrBlBSkill1(*m_chrBl);
  _gfbcb::initChrBlBSkill2(*m_chrBl);
  _gfbcb::initChrBlBSkill3(*m_chrBl);
  _gfbcb::initChrBlPArmor(*m_chrBl);
  _gfbcb::initChrBlEArmor(*m_chrBl);
  _gfbcb::initChrBlHpMaxRev(*m_chrBl);
  _gfbcb::initChrBlStrengthRev(*m_chrBl);
  _gfbcb::initChrBlPowEtherRev(*m_chrBl);
  _gfbcb::initChrBlDexRev(*m_chrBl);
  _gfbcb::initChrBlAgilityRev(*m_chrBl);
  _gfbcb::initChrBlLuckRev(*m_chrBl);
  _gfbcb::initChrBlBKLSet(*m_chrBl);
  _gfbcb::initChrBlFSkill1(*m_chrBl);
  _gfbcb::initChrBlFSkill2(*m_chrBl);
  _gfbcb::initChrBlFSkill3(*m_chrBl);
  _gfbcb::initChrBlArtsAchievement1(*m_chrBl);
  _gfbcb::initChrBlArtsAchievement2(*m_chrBl);
  _gfbcb::initChrBlArtsAchievement3(*m_chrBl);
  _gfbcb::initChrBlSkillAchievement1(*m_chrBl);
  _gfbcb::initChrBlSkillAchievement2(*m_chrBl);
  _gfbcb::initChrBlSkillAchievement3(*m_chrBl);
  _gfbcb::initChrBlFskillAchivement1(*m_chrBl);
  _gfbcb::initChrBlFskillAchivement2(*m_chrBl);
  _gfbcb::initChrBlFskillAchivement3(*m_chrBl);
  _gfbcb::initChrBlKeyAchievement(*m_chrBl);
  _gfbcb::initChrBlIdeaBlue(*m_chrBl);
  _gfbcb::initChrBlIdeaRed(*m_chrBl);
  _gfbcb::initChrBlIdeaWhite(*m_chrBl);
  _gfbcb::initChrBlIdeaBlack(*m_chrBl);
  _gfbcb::initChrBlFavoriteCategory1(*m_chrBl);
  _gfbcb::initChrBlFavoriteCategory2(*m_chrBl);
  _gfbcb::initChrBlFavoriteItem1(*m_chrBl);
  _gfbcb::initChrBlFavoriteItem2(*m_chrBl);
  _gfbcb::initChrBlCreateEventID(*m_chrBl);
  _gfbcb::initChrBlNormalTalk(*m_chrBl);
  _gfbcb::initChrBlCollisionId(*m_chrBl);
  _gfbcb::initChrBlBladeSize(*m_chrBl);
  _gfbcb::initChrBlMemorySlot(*m_chrBl);
  _gfbcb::initChrBlEventAsset(*m_chrBl);
  _gfbcb::initChrBlCenterBone(*m_chrBl);
  _gfbcb::initChrBlCamBone(*m_chrBl);
  _gfbcb::initChrBlMerceName(*m_chrBl);
  _gfbcb::initChrBlReleaseLock(*m_chrBl);
  _gfbcb::initChrBlCreateInfo(*m_chrBl);
  _gfbcb::initChrBlExtraParts1(*m_chrBl);
  _gfbcb::initChrBlExtraParts2(*m_chrBl);
  _gfbcb::initChrBlExtraParts3(*m_chrBl);
  _gfbcb::initChrBlExtraParts4(*m_chrBl);
  _gfbcb::initChrBlMnuCastName(*m_chrBl);
  _gfbcb::initChrBlMnuIlustName(*m_chrBl);
  _gfbcb::initChrBlMnuVoice1(*m_chrBl);
  _gfbcb::initChrBlMnuVoice2(*m_chrBl);
  _gfbcb::initChrBlMnuVoice3(*m_chrBl);
}

u32 GfBdatChrBl::getChrBlStart() const { return Bdat::getIdTop(m_chrBl->data); }

u32 GfBdatChrBl::getChrBlEnd() const { return Bdat::getIdTop(m_chrBl->data) + Bdat::getIdCount(m_chrBl->data); }

u32 GfBdatChrBl::getChrBlName(u32 id) const { return _gfbcb::getChrBlName(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlDebugName(u32 id) const { return _gfbcb::getChrBlDebugName(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlRace(u32 id) const { return _gfbcb::getChrBlRace(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlRotateLimitPitch(u32 id) const { return _gfbcb::getChrBlRotateLimitPitch(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlRotateLimitRoll(u32 id) const { return _gfbcb::getChrBlRotateLimitRoll(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlGender(u32 id) const { return _gfbcb::getChrBlGender(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlQuestRace(u32 id) const { return _gfbcb::getChrBlQuestRace(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlModel(u32 id) const { return _gfbcb::getChrBlModel(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlMotion(u32 id) const { return _gfbcb::getChrBlMotion(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlAddMotion(u32 id) const { return _gfbcb::getChrBlAddMotion(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlCondition(u32 id) const { return _gfbcb::getChrBlCondition(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlModel2(u32 id) const { return _gfbcb::getChrBlModel2(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlMotion2(u32 id) const { return _gfbcb::getChrBlMotion2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlStill(u32 id) const { return _gfbcb::getChrBlStill(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlVoice(u32 id) const { return _gfbcb::getChrBlVoice(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlClipEvent(u32 id) const { return _gfbcb::getChrBlClipEvent(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlCom_SE(u32 id) const { return _gfbcb::getChrBlCom_SE(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlSePack(u32 id) const { return _gfbcb::getChrBlSePack(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlCom_Eff(u32 id) const { return _gfbcb::getChrBlCom_Eff(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlCom_Vo(u32 id) const { return _gfbcb::getChrBlCom_Vo(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlOffsetID(u32 id) const { return _gfbcb::getChrBlOffsetID(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlEyeRot(u32 id) const { return _gfbcb::getChrBlEyeRot(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlChestHeight(u32 id) const { return _gfbcb::getChrBlChestHeight(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlLandingHeight(u32 id) const { return _gfbcb::getChrBlLandingHeight(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFootStep(u32 id) const { return _gfbcb::getChrBlFootStep(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFootStepEffect(u32 id) const { return _gfbcb::getChrBlFootStepEffect(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlWeaponType(u32 id) const { return _gfbcb::getChrBlWeaponType(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlScale(u32 id) const { return _gfbcb::getChrBlScale(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlWpnScale(u32 id) const { return _gfbcb::getChrBlWpnScale(*m_chrBl, id); }

bool GfBdatChrBl::isChrBlFlagOnlyWpn(u32 id) const { return _gfbcb::isChrBlFlagOnlyWpn(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPrivateWpnR(u32 id) const { return _gfbcb::getChrBlPrivateWpnR(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPrivateWpnL(u32 id) const { return _gfbcb::getChrBlPrivateWpnL(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPrivateWpnR_Driver(u32 id) const { return _gfbcb::getChrBlPrivateWpnR_Driver(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPrivateWpnL_Driver(u32 id) const { return _gfbcb::getChrBlPrivateWpnL_Driver(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlWpnrOut(u32 id) const { return _gfbcb::getChrBlWpnrOut(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlWpnlOut(u32 id) const { return _gfbcb::getChrBlWpnlOut(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlOrbNum(u32 id) const { return _gfbcb::getChrBlOrbNum(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlAtr(u32 id) const { return _gfbcb::getChrBlAtr(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPersonality(u32 id) const { return _gfbcb::getChrBlPersonality(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlCoolTime(u32 id) const { return _gfbcb::getChrBlCoolTime(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlDefWeapon(u32 id) const { return _gfbcb::getChrBlDefWeapon(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBArts1(u32 id) const { return _gfbcb::getChrBlBArts1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBArts2(u32 id) const { return _gfbcb::getChrBlBArts2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBArts3(u32 id) const { return _gfbcb::getChrBlBArts3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBartsEx(u32 id) const { return _gfbcb::getChrBlBartsEx(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBartsEx2(u32 id) const { return _gfbcb::getChrBlBartsEx2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNArts1(u32 id) const { return _gfbcb::getChrBlNArts1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNArtsRecastRev1(u32 id) const { return _gfbcb::getChrBlNArtsRecastRev1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNArts2(u32 id) const { return _gfbcb::getChrBlNArts2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNArtsRecastRev2(u32 id) const { return _gfbcb::getChrBlNArtsRecastRev2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNArts3(u32 id) const { return _gfbcb::getChrBlNArts3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNArtsRecastRev3(u32 id) const { return _gfbcb::getChrBlNArtsRecastRev3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBSkill1(u32 id) const { return _gfbcb::getChrBlBSkill1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBSkill2(u32 id) const { return _gfbcb::getChrBlBSkill2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBSkill3(u32 id) const { return _gfbcb::getChrBlBSkill3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPArmor(u32 id) const { return _gfbcb::getChrBlPArmor(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlEArmor(u32 id) const { return _gfbcb::getChrBlEArmor(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlHpMaxRev(u32 id) const { return _gfbcb::getChrBlHpMaxRev(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlStrengthRev(u32 id) const { return _gfbcb::getChrBlStrengthRev(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlPowEtherRev(u32 id) const { return _gfbcb::getChrBlPowEtherRev(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlDexRev(u32 id) const { return _gfbcb::getChrBlDexRev(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlAgilityRev(u32 id) const { return _gfbcb::getChrBlAgilityRev(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlLuckRev(u32 id) const { return _gfbcb::getChrBlLuckRev(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBKLSet(u32 id) const { return _gfbcb::getChrBlBKLSet(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFSkill1(u32 id) const { return _gfbcb::getChrBlFSkill1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFSkill2(u32 id) const { return _gfbcb::getChrBlFSkill2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFSkill3(u32 id) const { return _gfbcb::getChrBlFSkill3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlArtsAchievement1(u32 id) const { return _gfbcb::getChrBlArtsAchievement1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlArtsAchievement2(u32 id) const { return _gfbcb::getChrBlArtsAchievement2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlArtsAchievement3(u32 id) const { return _gfbcb::getChrBlArtsAchievement3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlSkillAchievement1(u32 id) const { return _gfbcb::getChrBlSkillAchievement1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlSkillAchievement2(u32 id) const { return _gfbcb::getChrBlSkillAchievement2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlSkillAchievement3(u32 id) const { return _gfbcb::getChrBlSkillAchievement3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFskillAchivement1(u32 id) const { return _gfbcb::getChrBlFskillAchivement1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFskillAchivement2(u32 id) const { return _gfbcb::getChrBlFskillAchivement2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFskillAchivement3(u32 id) const { return _gfbcb::getChrBlFskillAchivement3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlKeyAchievement(u32 id) const { return _gfbcb::getChrBlKeyAchievement(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlIdeaBlue(u32 id) const { return _gfbcb::getChrBlIdeaBlue(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlIdeaRed(u32 id) const { return _gfbcb::getChrBlIdeaRed(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlIdeaWhite(u32 id) const { return _gfbcb::getChrBlIdeaWhite(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlIdeaBlack(u32 id) const { return _gfbcb::getChrBlIdeaBlack(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFavoriteCategory1(u32 id) const { return _gfbcb::getChrBlFavoriteCategory1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFavoriteCategory2(u32 id) const { return _gfbcb::getChrBlFavoriteCategory2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFavoriteItem1(u32 id) const { return _gfbcb::getChrBlFavoriteItem1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlFavoriteItem2(u32 id) const { return _gfbcb::getChrBlFavoriteItem2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlCreateEventID(u32 id) const { return _gfbcb::getChrBlCreateEventID(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlNormalTalk(u32 id) const { return _gfbcb::getChrBlNormalTalk(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlCollisionId(u32 id) const { return _gfbcb::getChrBlCollisionId(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlBladeSize(u32 id) const { return _gfbcb::getChrBlBladeSize(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlMemorySlot(u32 id) const { return _gfbcb::getChrBlMemorySlot(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlEventAsset(u32 id) const { return _gfbcb::getChrBlEventAsset(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlCenterBone(u32 id) const { return _gfbcb::getChrBlCenterBone(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlCamBone(u32 id) const { return _gfbcb::getChrBlCamBone(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlMerceName(u32 id) const { return _gfbcb::getChrBlMerceName(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlReleaseLock(u32 id) const { return _gfbcb::getChrBlReleaseLock(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlCreateInfo(u32 id) const { return _gfbcb::getChrBlCreateInfo(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlExtraParts1(u32 id) const { return _gfbcb::getChrBlExtraParts1(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlExtraParts2(u32 id) const { return _gfbcb::getChrBlExtraParts2(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlExtraParts3(u32 id) const { return _gfbcb::getChrBlExtraParts3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlExtraParts4(u32 id) const { return _gfbcb::getChrBlExtraParts4(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlMnuCastName(u32 id) const { return _gfbcb::getChrBlMnuCastName(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlMnuIlustName(u32 id) const { return _gfbcb::getChrBlMnuIlustName(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlMnuVoice1(u32 id) const { return _gfbcb::getChrBlMnuVoice1(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlMnuVoice2(u32 id) const { return _gfbcb::getChrBlMnuVoice2(*m_chrBl, id); }

const char *GfBdatChrBl::getChrBlMnuVoice3(u32 id) const { return _gfbcb::getChrBlMnuVoice3(*m_chrBl, id); }

u32 GfBdatChrBl::getChrBlIdea(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlIdeaBlue, _gfbcb::getChrBlIdeaRed, _gfbcb::getChrBlIdeaWhite, _gfbcb::getChrBlIdeaBlack};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlBArts(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlBArts1, _gfbcb::getChrBlBArts2, _gfbcb::getChrBlBArts3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlBSkill(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlBSkill1, _gfbcb::getChrBlBSkill2, _gfbcb::getChrBlBSkill3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlFSkill(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlFSkill1, _gfbcb::getChrBlFSkill2, _gfbcb::getChrBlFSkill3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlNArts(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlNArts1, _gfbcb::getChrBlNArts2, _gfbcb::getChrBlNArts3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlNArtsRecastRev(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlNArtsRecastRev1, _gfbcb::getChrBlNArtsRecastRev2, _gfbcb::getChrBlNArtsRecastRev3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlArtsAchievement(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlArtsAchievement1, _gfbcb::getChrBlArtsAchievement2, _gfbcb::getChrBlArtsAchievement3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlSkillAchievement(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlSkillAchievement1, _gfbcb::getChrBlSkillAchievement2, _gfbcb::getChrBlSkillAchievement3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlFskillAchievement(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlFskillAchivement1, _gfbcb::getChrBlFskillAchivement2, _gfbcb::getChrBlFskillAchivement3};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlFavoriteCategory(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlFavoriteCategory1, _gfbcb::getChrBlFavoriteCategory2};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlFavoriteItem(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlFavoriteItem1, _gfbcb::getChrBlFavoriteItem2};
  return getters[index](*m_chrBl, id);
}

u32 GfBdatChrBl::getChrBlExtraParts(u32 id, u32 index) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlExtraParts1, _gfbcb::getChrBlExtraParts2, _gfbcb::getChrBlExtraParts3, _gfbcb::getChrBlExtraParts4};
  return getters[index](*m_chrBl, id);
}

const char *GfBdatChrBl::getChrBlMnuVoice(u32 id, u32 index) const {
  static const char *(*const getters[])(const CBdatWrapper &, u32) = {_gfbcb::getChrBlMnuVoice1, _gfbcb::getChrBlMnuVoice2, _gfbcb::getChrBlMnuVoice3};
  return getters[index](*m_chrBl, id);
}

} // namespace gf
