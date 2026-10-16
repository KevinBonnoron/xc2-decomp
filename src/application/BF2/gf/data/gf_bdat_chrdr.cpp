#include "gf/data/gf_bdat_chrdr.h"
#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbcd {

enum {
  ChrDrName,
  ChrDrDebugName,
  ChrDrRace,
  ChrDrRotateLimitPitch,
  ChrDrRotateLimitRoll,
  ChrDrGender,
  ChrDrModel,
  ChrDrCondition,
  ChrDrModel2,
  ChrDrMotion,
  ChrDrStill,
  ChrDrOffsetID,
  ChrDrEyeRot,
  ChrDrVoice,
  ChrDrClipEvent,
  ChrDrCom_SE,
  ChrDrCom_Eff,
  ChrDrCom_Vo,
  ChrDrAiID,
  ChrDrChestHeight,
  ChrDrLandingHeight,
  ChrDrFootStep,
  ChrDrFootStepEffect,
  ChrDrDefBlade1,
  ChrDrDefBlade2,
  ChrDrDefBlade3,
  ChrDrDefLvType,
  ChrDrDefLv,
  ChrDrDefWPType,
  ChrDrDefWP,
  ChrDrDefSPType,
  ChrDrDefSP,
  ChrDrDefAcce,
  ChrDrDefIdeaBlue,
  ChrDrDefIdeaRed,
  ChrDrDefIdeaWhite,
  ChrDrDefIdeaBlack,
  ChrDrHpMaxLv1,
  ChrDrStrengthLv1,
  ChrDrPowEtherLv1,
  ChrDrDexLv1,
  ChrDrAgilityLv1,
  ChrDrLuckLv1,
  ChrDrHpMaxLv99,
  ChrDrStrengthLv99,
  ChrDrPowEtherLv99,
  ChrDrDexLv99,
  ChrDrAgilityLv99,
  ChrDrLuckLv99,
  ChrDrWpnType,
  ChrDrWpRate,
  ChrDrFavoriteCategory1,
  ChrDrFavoriteCategory2,
  ChrDrFavoriteItem1,
  ChrDrFavoriteItem2,
  ChrDrCollisionId,
  ChrDrCenterBone,
  ChrDrCamBone,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initChrDrName(const CBdatWrapper &wrapper) { s_members[ChrDrName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getChrDrName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrName] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrName], id, 2).valueU16;
}

void initChrDrDebugName(const CBdatWrapper &wrapper) { s_members[ChrDrDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getChrDrDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrDebugName], id, 7).valueString;
}

void initChrDrRace(const CBdatWrapper &wrapper) { s_members[ChrDrRace] = Bdat::getMember(wrapper.data, "Race"); }

u32 getChrDrRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrRace] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrRace], id, 1).valueU8;
}

void initChrDrRotateLimitPitch(const CBdatWrapper &wrapper) { s_members[ChrDrRotateLimitPitch] = Bdat::getMember(wrapper.data, "RotateLimitPitch"); }

u32 getChrDrRotateLimitPitch(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrRotateLimitPitch] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrRotateLimitPitch], id, 1).valueU8;
}

void initChrDrRotateLimitRoll(const CBdatWrapper &wrapper) { s_members[ChrDrRotateLimitRoll] = Bdat::getMember(wrapper.data, "RotateLimitRoll"); }

u32 getChrDrRotateLimitRoll(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrRotateLimitRoll] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrRotateLimitRoll], id, 1).valueU8;
}

void initChrDrGender(const CBdatWrapper &wrapper) { s_members[ChrDrGender] = Bdat::getMember(wrapper.data, "Gender"); }

u32 getChrDrGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrGender] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrGender], id, 1).valueU8;
}

void initChrDrModel(const CBdatWrapper &wrapper) { s_members[ChrDrModel] = Bdat::getMember(wrapper.data, "Model"); }

const char *getChrDrModel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrModel] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrModel], id, 7).valueString;
}

void initChrDrCondition(const CBdatWrapper &wrapper) { s_members[ChrDrCondition] = Bdat::getMember(wrapper.data, "Condition"); }

u32 getChrDrCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrCondition], id, 2).valueU16;
}

void initChrDrModel2(const CBdatWrapper &wrapper) { s_members[ChrDrModel2] = Bdat::getMember(wrapper.data, "Model2"); }

const char *getChrDrModel2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrModel2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrModel2], id, 7).valueString;
}

void initChrDrMotion(const CBdatWrapper &wrapper) { s_members[ChrDrMotion] = Bdat::getMember(wrapper.data, "Motion"); }

const char *getChrDrMotion(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrMotion] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrMotion], id, 7).valueString;
}

void initChrDrStill(const CBdatWrapper &wrapper) { s_members[ChrDrStill] = Bdat::getMember(wrapper.data, "Still"); }

u32 getChrDrStill(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrStill] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrStill], id, 2).valueU16;
}

void initChrDrOffsetID(const CBdatWrapper &wrapper) { s_members[ChrDrOffsetID] = Bdat::getMember(wrapper.data, "OffsetID"); }

u32 getChrDrOffsetID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrOffsetID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrOffsetID], id, 2).valueU16;
}

void initChrDrEyeRot(const CBdatWrapper &wrapper) { s_members[ChrDrEyeRot] = Bdat::getMember(wrapper.data, "EyeRot"); }

u32 getChrDrEyeRot(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrEyeRot] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrEyeRot], id, 1).valueU8;
}

void initChrDrVoice(const CBdatWrapper &wrapper) { s_members[ChrDrVoice] = Bdat::getMember(wrapper.data, "Voice"); }

const char *getChrDrVoice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrVoice] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrVoice], id, 7).valueString;
}

void initChrDrClipEvent(const CBdatWrapper &wrapper) { s_members[ChrDrClipEvent] = Bdat::getMember(wrapper.data, "ClipEvent"); }

const char *getChrDrClipEvent(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrClipEvent] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrClipEvent], id, 7).valueString;
}

void initChrDrCom_SE(const CBdatWrapper &wrapper) { s_members[ChrDrCom_SE] = Bdat::getMember(wrapper.data, "Com_SE"); }

const char *getChrDrCom_SE(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCom_SE] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrCom_SE], id, 7).valueString;
}

void initChrDrCom_Eff(const CBdatWrapper &wrapper) { s_members[ChrDrCom_Eff] = Bdat::getMember(wrapper.data, "Com_Eff"); }

const char *getChrDrCom_Eff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCom_Eff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrCom_Eff], id, 7).valueString;
}

void initChrDrCom_Vo(const CBdatWrapper &wrapper) { s_members[ChrDrCom_Vo] = Bdat::getMember(wrapper.data, "Com_Vo"); }

const char *getChrDrCom_Vo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCom_Vo] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrCom_Vo], id, 7).valueString;
}

void initChrDrAiID(const CBdatWrapper &wrapper) { s_members[ChrDrAiID] = Bdat::getMember(wrapper.data, "AiID"); }

u32 getChrDrAiID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrAiID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrAiID], id, 2).valueU16;
}

void initChrDrChestHeight(const CBdatWrapper &wrapper) { s_members[ChrDrChestHeight] = Bdat::getMember(wrapper.data, "ChestHeight"); }

u32 getChrDrChestHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrChestHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrChestHeight], id, 2).valueU16;
}

void initChrDrLandingHeight(const CBdatWrapper &wrapper) { s_members[ChrDrLandingHeight] = Bdat::getMember(wrapper.data, "LandingHeight"); }

u32 getChrDrLandingHeight(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrLandingHeight] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrLandingHeight], id, 2).valueU16;
}

void initChrDrFootStep(const CBdatWrapper &wrapper) { s_members[ChrDrFootStep] = Bdat::getMember(wrapper.data, "FootStep"); }

u32 getChrDrFootStep(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrFootStep] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrFootStep], id, 1).valueU8;
}

void initChrDrFootStepEffect(const CBdatWrapper &wrapper) { s_members[ChrDrFootStepEffect] = Bdat::getMember(wrapper.data, "FootStepEffect"); }

u32 getChrDrFootStepEffect(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrFootStepEffect] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrFootStepEffect], id, 1).valueU8;
}

void initChrDrDefBlade1(const CBdatWrapper &wrapper) { s_members[ChrDrDefBlade1] = Bdat::getMember(wrapper.data, "DefBlade1"); }

u32 getChrDrDefBlade1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefBlade1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefBlade1], id, 2).valueU16;
}

void initChrDrDefBlade2(const CBdatWrapper &wrapper) { s_members[ChrDrDefBlade2] = Bdat::getMember(wrapper.data, "DefBlade2"); }

u32 getChrDrDefBlade2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefBlade2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefBlade2], id, 2).valueU16;
}

void initChrDrDefBlade3(const CBdatWrapper &wrapper) { s_members[ChrDrDefBlade3] = Bdat::getMember(wrapper.data, "DefBlade3"); }

u32 getChrDrDefBlade3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefBlade3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefBlade3], id, 2).valueU16;
}

void initChrDrDefLvType(const CBdatWrapper &wrapper) { s_members[ChrDrDefLvType] = Bdat::getMember(wrapper.data, "DefLvType"); }

u32 getChrDrDefLvType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefLvType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefLvType], id, 1).valueU8;
}

void initChrDrDefLv(const CBdatWrapper &wrapper) { s_members[ChrDrDefLv] = Bdat::getMember(wrapper.data, "DefLv"); }

u32 getChrDrDefLv(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefLv] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefLv], id, 1).valueU8;
}

void initChrDrDefWPType(const CBdatWrapper &wrapper) { s_members[ChrDrDefWPType] = Bdat::getMember(wrapper.data, "DefWPType"); }

u32 getChrDrDefWPType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefWPType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefWPType], id, 1).valueU8;
}

void initChrDrDefWP(const CBdatWrapper &wrapper) { s_members[ChrDrDefWP] = Bdat::getMember(wrapper.data, "DefWP"); }

u32 getChrDrDefWP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefWP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefWP], id, 2).valueU16;
}

void initChrDrDefSPType(const CBdatWrapper &wrapper) { s_members[ChrDrDefSPType] = Bdat::getMember(wrapper.data, "DefSPType"); }

u32 getChrDrDefSPType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefSPType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefSPType], id, 1).valueU8;
}

void initChrDrDefSP(const CBdatWrapper &wrapper) { s_members[ChrDrDefSP] = Bdat::getMember(wrapper.data, "DefSP"); }

u32 getChrDrDefSP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefSP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefSP], id, 2).valueU16;
}

void initChrDrDefAcce(const CBdatWrapper &wrapper) { s_members[ChrDrDefAcce] = Bdat::getMember(wrapper.data, "DefAcce"); }

u32 getChrDrDefAcce(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefAcce] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefAcce], id, 2).valueU16;
}

void initChrDrDefIdeaBlue(const CBdatWrapper &wrapper) { s_members[ChrDrDefIdeaBlue] = Bdat::getMember(wrapper.data, "DefIdeaBlue"); }

u32 getChrDrDefIdeaBlue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefIdeaBlue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefIdeaBlue], id, 1).valueU8;
}

void initChrDrDefIdeaRed(const CBdatWrapper &wrapper) { s_members[ChrDrDefIdeaRed] = Bdat::getMember(wrapper.data, "DefIdeaRed"); }

u32 getChrDrDefIdeaRed(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefIdeaRed] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefIdeaRed], id, 1).valueU8;
}

void initChrDrDefIdeaWhite(const CBdatWrapper &wrapper) { s_members[ChrDrDefIdeaWhite] = Bdat::getMember(wrapper.data, "DefIdeaWhite"); }

u32 getChrDrDefIdeaWhite(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefIdeaWhite] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefIdeaWhite], id, 1).valueU8;
}

void initChrDrDefIdeaBlack(const CBdatWrapper &wrapper) { s_members[ChrDrDefIdeaBlack] = Bdat::getMember(wrapper.data, "DefIdeaBlack"); }

u32 getChrDrDefIdeaBlack(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDefIdeaBlack] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDefIdeaBlack], id, 1).valueU8;
}

void initChrDrHpMaxLv1(const CBdatWrapper &wrapper) { s_members[ChrDrHpMaxLv1] = Bdat::getMember(wrapper.data, "HpMaxLv1"); }

u32 getChrDrHpMaxLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrHpMaxLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrHpMaxLv1], id, 2).valueU16;
}

void initChrDrStrengthLv1(const CBdatWrapper &wrapper) { s_members[ChrDrStrengthLv1] = Bdat::getMember(wrapper.data, "StrengthLv1"); }

u32 getChrDrStrengthLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrStrengthLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrStrengthLv1], id, 2).valueU16;
}

void initChrDrPowEtherLv1(const CBdatWrapper &wrapper) { s_members[ChrDrPowEtherLv1] = Bdat::getMember(wrapper.data, "PowEtherLv1"); }

u32 getChrDrPowEtherLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrPowEtherLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrPowEtherLv1], id, 2).valueU16;
}

void initChrDrDexLv1(const CBdatWrapper &wrapper) { s_members[ChrDrDexLv1] = Bdat::getMember(wrapper.data, "DexLv1"); }

u32 getChrDrDexLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDexLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDexLv1], id, 2).valueU16;
}

void initChrDrAgilityLv1(const CBdatWrapper &wrapper) { s_members[ChrDrAgilityLv1] = Bdat::getMember(wrapper.data, "AgilityLv1"); }

u32 getChrDrAgilityLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrAgilityLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrAgilityLv1], id, 2).valueU16;
}

void initChrDrLuckLv1(const CBdatWrapper &wrapper) { s_members[ChrDrLuckLv1] = Bdat::getMember(wrapper.data, "LuckLv1"); }

u32 getChrDrLuckLv1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrLuckLv1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrLuckLv1], id, 2).valueU16;
}

void initChrDrHpMaxLv99(const CBdatWrapper &wrapper) { s_members[ChrDrHpMaxLv99] = Bdat::getMember(wrapper.data, "HpMaxLv99"); }

u32 getChrDrHpMaxLv99(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrHpMaxLv99] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrHpMaxLv99], id, 2).valueU16;
}

void initChrDrStrengthLv99(const CBdatWrapper &wrapper) { s_members[ChrDrStrengthLv99] = Bdat::getMember(wrapper.data, "StrengthLv99"); }

u32 getChrDrStrengthLv99(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrStrengthLv99] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrStrengthLv99], id, 2).valueU16;
}

void initChrDrPowEtherLv99(const CBdatWrapper &wrapper) { s_members[ChrDrPowEtherLv99] = Bdat::getMember(wrapper.data, "PowEtherLv99"); }

u32 getChrDrPowEtherLv99(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrPowEtherLv99] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrPowEtherLv99], id, 2).valueU16;
}

void initChrDrDexLv99(const CBdatWrapper &wrapper) { s_members[ChrDrDexLv99] = Bdat::getMember(wrapper.data, "DexLv99"); }

u32 getChrDrDexLv99(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrDexLv99] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrDexLv99], id, 2).valueU16;
}

void initChrDrAgilityLv99(const CBdatWrapper &wrapper) { s_members[ChrDrAgilityLv99] = Bdat::getMember(wrapper.data, "AgilityLv99"); }

u32 getChrDrAgilityLv99(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrAgilityLv99] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrAgilityLv99], id, 2).valueU16;
}

void initChrDrLuckLv99(const CBdatWrapper &wrapper) { s_members[ChrDrLuckLv99] = Bdat::getMember(wrapper.data, "LuckLv99"); }

u32 getChrDrLuckLv99(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrLuckLv99] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrLuckLv99], id, 2).valueU16;
}

void initChrDrWpnType(const CBdatWrapper &wrapper) { s_members[ChrDrWpnType] = Bdat::getMember(wrapper.data, "WpnType"); }

u32 getChrDrWpnType(const CBdatWrapper &wrapper, u32 id, u32 index) {
  if (s_members[ChrDrWpnType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getArrayValCheck(s_members[ChrDrWpnType], id, index, 1).valueU8;
}

void initChrDrWpRate(const CBdatWrapper &wrapper) { s_members[ChrDrWpRate] = Bdat::getMember(wrapper.data, "WpRate"); }

u32 getChrDrWpRate(const CBdatWrapper &wrapper, u32 id, u32 index) {
  if (s_members[ChrDrWpRate] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getArrayValCheck(s_members[ChrDrWpRate], id, index, 1).valueU8;
}

void initChrDrFavoriteCategory1(const CBdatWrapper &wrapper) {
  s_members[ChrDrFavoriteCategory1] = Bdat::getMember(wrapper.data, "FavoriteCategory1");
}

u32 getChrDrFavoriteCategory1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrFavoriteCategory1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrFavoriteCategory1], id, 2).valueU16;
}

void initChrDrFavoriteCategory2(const CBdatWrapper &wrapper) {
  s_members[ChrDrFavoriteCategory2] = Bdat::getMember(wrapper.data, "FavoriteCategory2");
}

u32 getChrDrFavoriteCategory2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrFavoriteCategory2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrFavoriteCategory2], id, 2).valueU16;
}

void initChrDrFavoriteItem1(const CBdatWrapper &wrapper) { s_members[ChrDrFavoriteItem1] = Bdat::getMember(wrapper.data, "FavoriteItem1"); }

u32 getChrDrFavoriteItem1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrFavoriteItem1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrFavoriteItem1], id, 2).valueU16;
}

void initChrDrFavoriteItem2(const CBdatWrapper &wrapper) { s_members[ChrDrFavoriteItem2] = Bdat::getMember(wrapper.data, "FavoriteItem2"); }

u32 getChrDrFavoriteItem2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrFavoriteItem2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrFavoriteItem2], id, 2).valueU16;
}

void initChrDrCollisionId(const CBdatWrapper &wrapper) { s_members[ChrDrCollisionId] = Bdat::getMember(wrapper.data, "CollisionId"); }

u32 getChrDrCollisionId(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCollisionId] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ChrDrCollisionId], id, 2).valueU16;
}

void initChrDrCenterBone(const CBdatWrapper &wrapper) { s_members[ChrDrCenterBone] = Bdat::getMember(wrapper.data, "CenterBone"); }

const char *getChrDrCenterBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCenterBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrCenterBone], id, 7).valueString;
}

void initChrDrCamBone(const CBdatWrapper &wrapper) { s_members[ChrDrCamBone] = Bdat::getMember(wrapper.data, "CamBone"); }

const char *getChrDrCamBone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ChrDrCamBone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[ChrDrCamBone], id, 7).valueString;
}

} // namespace _gfbcd

GfBdatChrDr::GfBdatChrDr() : mChrDr(nullptr) { bdatRefresh(); }

GfBdatChrDr::~GfBdatChrDr() { destroyFP(); }

void GfBdatChrDr::destroyFP() {
  if (mChrDr != nullptr) {
    delete mChrDr;
    mChrDr = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatChrDr::createFP() { mChrDr = NEW_BDAT_WRAPPER(BDAT_CHR_DR); }

void GfBdatChrDr::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbcd::initChrDrName(*mChrDr);
  _gfbcd::initChrDrDebugName(*mChrDr);
  _gfbcd::initChrDrRace(*mChrDr);
  _gfbcd::initChrDrRotateLimitPitch(*mChrDr);
  _gfbcd::initChrDrRotateLimitRoll(*mChrDr);
  _gfbcd::initChrDrGender(*mChrDr);
  _gfbcd::initChrDrModel(*mChrDr);
  _gfbcd::initChrDrCondition(*mChrDr);
  _gfbcd::initChrDrModel2(*mChrDr);
  _gfbcd::initChrDrMotion(*mChrDr);
  _gfbcd::initChrDrStill(*mChrDr);
  _gfbcd::initChrDrOffsetID(*mChrDr);
  _gfbcd::initChrDrEyeRot(*mChrDr);
  _gfbcd::initChrDrVoice(*mChrDr);
  _gfbcd::initChrDrClipEvent(*mChrDr);
  _gfbcd::initChrDrCom_SE(*mChrDr);
  _gfbcd::initChrDrCom_Eff(*mChrDr);
  _gfbcd::initChrDrCom_Vo(*mChrDr);
  _gfbcd::initChrDrAiID(*mChrDr);
  _gfbcd::initChrDrChestHeight(*mChrDr);
  _gfbcd::initChrDrLandingHeight(*mChrDr);
  _gfbcd::initChrDrFootStep(*mChrDr);
  _gfbcd::initChrDrFootStepEffect(*mChrDr);
  _gfbcd::initChrDrDefBlade1(*mChrDr);
  _gfbcd::initChrDrDefBlade2(*mChrDr);
  _gfbcd::initChrDrDefBlade3(*mChrDr);
  _gfbcd::initChrDrDefLvType(*mChrDr);
  _gfbcd::initChrDrDefLv(*mChrDr);
  _gfbcd::initChrDrDefWPType(*mChrDr);
  _gfbcd::initChrDrDefWP(*mChrDr);
  _gfbcd::initChrDrDefSPType(*mChrDr);
  _gfbcd::initChrDrDefSP(*mChrDr);
  _gfbcd::initChrDrDefAcce(*mChrDr);
  _gfbcd::initChrDrDefIdeaBlue(*mChrDr);
  _gfbcd::initChrDrDefIdeaRed(*mChrDr);
  _gfbcd::initChrDrDefIdeaWhite(*mChrDr);
  _gfbcd::initChrDrDefIdeaBlack(*mChrDr);
  _gfbcd::initChrDrHpMaxLv1(*mChrDr);
  _gfbcd::initChrDrStrengthLv1(*mChrDr);
  _gfbcd::initChrDrPowEtherLv1(*mChrDr);
  _gfbcd::initChrDrDexLv1(*mChrDr);
  _gfbcd::initChrDrAgilityLv1(*mChrDr);
  _gfbcd::initChrDrLuckLv1(*mChrDr);
  _gfbcd::initChrDrHpMaxLv99(*mChrDr);
  _gfbcd::initChrDrStrengthLv99(*mChrDr);
  _gfbcd::initChrDrPowEtherLv99(*mChrDr);
  _gfbcd::initChrDrDexLv99(*mChrDr);
  _gfbcd::initChrDrAgilityLv99(*mChrDr);
  _gfbcd::initChrDrLuckLv99(*mChrDr);
  _gfbcd::initChrDrWpnType(*mChrDr);
  _gfbcd::initChrDrWpRate(*mChrDr);
  _gfbcd::initChrDrFavoriteCategory1(*mChrDr);
  _gfbcd::initChrDrFavoriteCategory2(*mChrDr);
  _gfbcd::initChrDrFavoriteItem1(*mChrDr);
  _gfbcd::initChrDrFavoriteItem2(*mChrDr);
  _gfbcd::initChrDrCollisionId(*mChrDr);
  _gfbcd::initChrDrCenterBone(*mChrDr);
  _gfbcd::initChrDrCamBone(*mChrDr);
}

u32 GfBdatChrDr::getChrDrStart() const { return Bdat::getIdTop(mChrDr->data); }

u32 GfBdatChrDr::getChrDrEnd() const { return Bdat::getIdTop(mChrDr->data) + Bdat::getIdCount(mChrDr->data); }

u32 GfBdatChrDr::getChrDrName(u32 id) const { return _gfbcd::getChrDrName(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrDebugName(u32 id) const { return _gfbcd::getChrDrDebugName(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrRace(u32 id) const { return _gfbcd::getChrDrRace(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrRotateLimitPitch(u32 id) const { return _gfbcd::getChrDrRotateLimitPitch(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrRotateLimitRoll(u32 id) const { return _gfbcd::getChrDrRotateLimitRoll(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrGender(u32 id) const { return _gfbcd::getChrDrGender(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrModel(u32 id) const { return _gfbcd::getChrDrModel(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrCondition(u32 id) const { return _gfbcd::getChrDrCondition(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrModel2(u32 id) const { return _gfbcd::getChrDrModel2(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrMotion(u32 id) const { return _gfbcd::getChrDrMotion(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrStill(u32 id) const { return _gfbcd::getChrDrStill(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrOffsetID(u32 id) const { return _gfbcd::getChrDrOffsetID(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrEyeRot(u32 id) const { return _gfbcd::getChrDrEyeRot(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrVoice(u32 id) const { return _gfbcd::getChrDrVoice(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrClipEvent(u32 id) const { return _gfbcd::getChrDrClipEvent(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrCom_SE(u32 id) const { return _gfbcd::getChrDrCom_SE(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrCom_Eff(u32 id) const { return _gfbcd::getChrDrCom_Eff(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrCom_Vo(u32 id) const { return _gfbcd::getChrDrCom_Vo(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrAiID(u32 id) const { return _gfbcd::getChrDrAiID(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrChestHeight(u32 id) const { return _gfbcd::getChrDrChestHeight(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrLandingHeight(u32 id) const { return _gfbcd::getChrDrLandingHeight(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrFootStep(u32 id) const { return _gfbcd::getChrDrFootStep(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrFootStepEffect(u32 id) const { return _gfbcd::getChrDrFootStepEffect(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefBlade1(u32 id) const { return _gfbcd::getChrDrDefBlade1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefBlade2(u32 id) const { return _gfbcd::getChrDrDefBlade2(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefBlade3(u32 id) const { return _gfbcd::getChrDrDefBlade3(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefLvType(u32 id) const { return _gfbcd::getChrDrDefLvType(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefLv(u32 id) const { return _gfbcd::getChrDrDefLv(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefWPType(u32 id) const { return _gfbcd::getChrDrDefWPType(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefWP(u32 id) const { return _gfbcd::getChrDrDefWP(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefSPType(u32 id) const { return _gfbcd::getChrDrDefSPType(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefSP(u32 id) const { return _gfbcd::getChrDrDefSP(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefAcce(u32 id) const { return _gfbcd::getChrDrDefAcce(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefIdeaBlue(u32 id) const { return _gfbcd::getChrDrDefIdeaBlue(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefIdeaRed(u32 id) const { return _gfbcd::getChrDrDefIdeaRed(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefIdeaWhite(u32 id) const { return _gfbcd::getChrDrDefIdeaWhite(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDefIdeaBlack(u32 id) const { return _gfbcd::getChrDrDefIdeaBlack(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrHpMaxLv1(u32 id) const { return _gfbcd::getChrDrHpMaxLv1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrStrengthLv1(u32 id) const { return _gfbcd::getChrDrStrengthLv1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrPowEtherLv1(u32 id) const { return _gfbcd::getChrDrPowEtherLv1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDexLv1(u32 id) const { return _gfbcd::getChrDrDexLv1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrAgilityLv1(u32 id) const { return _gfbcd::getChrDrAgilityLv1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrLuckLv1(u32 id) const { return _gfbcd::getChrDrLuckLv1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrHpMaxLv99(u32 id) const { return _gfbcd::getChrDrHpMaxLv99(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrStrengthLv99(u32 id) const { return _gfbcd::getChrDrStrengthLv99(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrPowEtherLv99(u32 id) const { return _gfbcd::getChrDrPowEtherLv99(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrDexLv99(u32 id) const { return _gfbcd::getChrDrDexLv99(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrAgilityLv99(u32 id) const { return _gfbcd::getChrDrAgilityLv99(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrLuckLv99(u32 id) const { return _gfbcd::getChrDrLuckLv99(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrFavoriteCategory1(u32 id) const { return _gfbcd::getChrDrFavoriteCategory1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrFavoriteCategory2(u32 id) const { return _gfbcd::getChrDrFavoriteCategory2(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrFavoriteItem1(u32 id) const { return _gfbcd::getChrDrFavoriteItem1(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrFavoriteItem2(u32 id) const { return _gfbcd::getChrDrFavoriteItem2(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrCollisionId(u32 id) const { return _gfbcd::getChrDrCollisionId(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrCenterBone(u32 id) const { return _gfbcd::getChrDrCenterBone(*mChrDr, id); }

const char *GfBdatChrDr::getChrDrCamBone(u32 id) const { return _gfbcd::getChrDrCamBone(*mChrDr, id); }

u32 GfBdatChrDr::getChrDrWpnType(u32 driver, u32 slot) const { return _gfbcd::getChrDrWpnType(*mChrDr, driver, slot); }

u32 GfBdatChrDr::getChrDrWpRate(u32 id, u32 index) const { return _gfbcd::getChrDrWpRate(*mChrDr, id, index); }

u32 GfBdatChrDr::getChrDrDefBlade(u32 driver, u32 slot) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcd::getChrDrDefBlade1, _gfbcd::getChrDrDefBlade2, _gfbcd::getChrDrDefBlade3};
  return getters[slot](*mChrDr, driver);
}

u32 GfBdatChrDr::getChrDrFavoriteCategory(u32 driver, u32 favorite) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcd::getChrDrFavoriteCategory1, _gfbcd::getChrDrFavoriteCategory2};
  return getters[favorite](*mChrDr, driver);
}

u32 GfBdatChrDr::getChrDrFavoriteItem(u32 driver, u32 favorite) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcd::getChrDrFavoriteItem1, _gfbcd::getChrDrFavoriteItem2};
  return getters[favorite](*mChrDr, driver);
}

} // namespace gf
