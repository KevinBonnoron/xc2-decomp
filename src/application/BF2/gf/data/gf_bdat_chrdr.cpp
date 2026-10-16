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

GfBdatChrDr::GfBdatChrDr() : unknown10(nullptr) { bdatRefresh(); }

GfBdatChrDr::~GfBdatChrDr() { destroyFP(); }

void GfBdatChrDr::destroyFP() {
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatChrDr::createFP() { unknown10 = NEW_BDAT_WRAPPER(BDAT_CHR_DR); }

void GfBdatChrDr::bdatRefresh() {
  destroyFP();
  createFP();
  _gfbcd::initChrDrName(*unknown10);
  _gfbcd::initChrDrDebugName(*unknown10);
  _gfbcd::initChrDrRace(*unknown10);
  _gfbcd::initChrDrRotateLimitPitch(*unknown10);
  _gfbcd::initChrDrRotateLimitRoll(*unknown10);
  _gfbcd::initChrDrGender(*unknown10);
  _gfbcd::initChrDrModel(*unknown10);
  _gfbcd::initChrDrCondition(*unknown10);
  _gfbcd::initChrDrModel2(*unknown10);
  _gfbcd::initChrDrMotion(*unknown10);
  _gfbcd::initChrDrStill(*unknown10);
  _gfbcd::initChrDrOffsetID(*unknown10);
  _gfbcd::initChrDrEyeRot(*unknown10);
  _gfbcd::initChrDrVoice(*unknown10);
  _gfbcd::initChrDrClipEvent(*unknown10);
  _gfbcd::initChrDrCom_SE(*unknown10);
  _gfbcd::initChrDrCom_Eff(*unknown10);
  _gfbcd::initChrDrCom_Vo(*unknown10);
  _gfbcd::initChrDrAiID(*unknown10);
  _gfbcd::initChrDrChestHeight(*unknown10);
  _gfbcd::initChrDrLandingHeight(*unknown10);
  _gfbcd::initChrDrFootStep(*unknown10);
  _gfbcd::initChrDrFootStepEffect(*unknown10);
  _gfbcd::initChrDrDefBlade1(*unknown10);
  _gfbcd::initChrDrDefBlade2(*unknown10);
  _gfbcd::initChrDrDefBlade3(*unknown10);
  _gfbcd::initChrDrDefLvType(*unknown10);
  _gfbcd::initChrDrDefLv(*unknown10);
  _gfbcd::initChrDrDefWPType(*unknown10);
  _gfbcd::initChrDrDefWP(*unknown10);
  _gfbcd::initChrDrDefSPType(*unknown10);
  _gfbcd::initChrDrDefSP(*unknown10);
  _gfbcd::initChrDrDefAcce(*unknown10);
  _gfbcd::initChrDrDefIdeaBlue(*unknown10);
  _gfbcd::initChrDrDefIdeaRed(*unknown10);
  _gfbcd::initChrDrDefIdeaWhite(*unknown10);
  _gfbcd::initChrDrDefIdeaBlack(*unknown10);
  _gfbcd::initChrDrHpMaxLv1(*unknown10);
  _gfbcd::initChrDrStrengthLv1(*unknown10);
  _gfbcd::initChrDrPowEtherLv1(*unknown10);
  _gfbcd::initChrDrDexLv1(*unknown10);
  _gfbcd::initChrDrAgilityLv1(*unknown10);
  _gfbcd::initChrDrLuckLv1(*unknown10);
  _gfbcd::initChrDrHpMaxLv99(*unknown10);
  _gfbcd::initChrDrStrengthLv99(*unknown10);
  _gfbcd::initChrDrPowEtherLv99(*unknown10);
  _gfbcd::initChrDrDexLv99(*unknown10);
  _gfbcd::initChrDrAgilityLv99(*unknown10);
  _gfbcd::initChrDrLuckLv99(*unknown10);
  _gfbcd::initChrDrWpnType(*unknown10);
  _gfbcd::initChrDrWpRate(*unknown10);
  _gfbcd::initChrDrFavoriteCategory1(*unknown10);
  _gfbcd::initChrDrFavoriteCategory2(*unknown10);
  _gfbcd::initChrDrFavoriteItem1(*unknown10);
  _gfbcd::initChrDrFavoriteItem2(*unknown10);
  _gfbcd::initChrDrCollisionId(*unknown10);
  _gfbcd::initChrDrCenterBone(*unknown10);
  _gfbcd::initChrDrCamBone(*unknown10);
}

u32 GfBdatChrDr::getChrDrStart() const { return Bdat::getIdTop(unknown10->data); }

u32 GfBdatChrDr::getChrDrEnd() const { return Bdat::getIdTop(unknown10->data) + Bdat::getIdCount(unknown10->data); }

u32 GfBdatChrDr::getChrDrName(u32 id) const { return _gfbcd::getChrDrName(*unknown10, id); }

const char *GfBdatChrDr::getChrDrDebugName(u32 id) const { return _gfbcd::getChrDrDebugName(*unknown10, id); }

u32 GfBdatChrDr::getChrDrRace(u32 id) const { return _gfbcd::getChrDrRace(*unknown10, id); }

u32 GfBdatChrDr::getChrDrRotateLimitPitch(u32 id) const { return _gfbcd::getChrDrRotateLimitPitch(*unknown10, id); }

u32 GfBdatChrDr::getChrDrRotateLimitRoll(u32 id) const { return _gfbcd::getChrDrRotateLimitRoll(*unknown10, id); }

u32 GfBdatChrDr::getChrDrGender(u32 id) const { return _gfbcd::getChrDrGender(*unknown10, id); }

const char *GfBdatChrDr::getChrDrModel(u32 id) const { return _gfbcd::getChrDrModel(*unknown10, id); }

u32 GfBdatChrDr::getChrDrCondition(u32 id) const { return _gfbcd::getChrDrCondition(*unknown10, id); }

const char *GfBdatChrDr::getChrDrModel2(u32 id) const { return _gfbcd::getChrDrModel2(*unknown10, id); }

const char *GfBdatChrDr::getChrDrMotion(u32 id) const { return _gfbcd::getChrDrMotion(*unknown10, id); }

u32 GfBdatChrDr::getChrDrStill(u32 id) const { return _gfbcd::getChrDrStill(*unknown10, id); }

u32 GfBdatChrDr::getChrDrOffsetID(u32 id) const { return _gfbcd::getChrDrOffsetID(*unknown10, id); }

u32 GfBdatChrDr::getChrDrEyeRot(u32 id) const { return _gfbcd::getChrDrEyeRot(*unknown10, id); }

const char *GfBdatChrDr::getChrDrVoice(u32 id) const { return _gfbcd::getChrDrVoice(*unknown10, id); }

const char *GfBdatChrDr::getChrDrClipEvent(u32 id) const { return _gfbcd::getChrDrClipEvent(*unknown10, id); }

const char *GfBdatChrDr::getChrDrCom_SE(u32 id) const { return _gfbcd::getChrDrCom_SE(*unknown10, id); }

const char *GfBdatChrDr::getChrDrCom_Eff(u32 id) const { return _gfbcd::getChrDrCom_Eff(*unknown10, id); }

const char *GfBdatChrDr::getChrDrCom_Vo(u32 id) const { return _gfbcd::getChrDrCom_Vo(*unknown10, id); }

u32 GfBdatChrDr::getChrDrAiID(u32 id) const { return _gfbcd::getChrDrAiID(*unknown10, id); }

u32 GfBdatChrDr::getChrDrChestHeight(u32 id) const { return _gfbcd::getChrDrChestHeight(*unknown10, id); }

u32 GfBdatChrDr::getChrDrLandingHeight(u32 id) const { return _gfbcd::getChrDrLandingHeight(*unknown10, id); }

u32 GfBdatChrDr::getChrDrFootStep(u32 id) const { return _gfbcd::getChrDrFootStep(*unknown10, id); }

u32 GfBdatChrDr::getChrDrFootStepEffect(u32 id) const { return _gfbcd::getChrDrFootStepEffect(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefBlade1(u32 id) const { return _gfbcd::getChrDrDefBlade1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefBlade2(u32 id) const { return _gfbcd::getChrDrDefBlade2(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefBlade3(u32 id) const { return _gfbcd::getChrDrDefBlade3(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefLvType(u32 id) const { return _gfbcd::getChrDrDefLvType(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefLv(u32 id) const { return _gfbcd::getChrDrDefLv(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefWPType(u32 id) const { return _gfbcd::getChrDrDefWPType(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefWP(u32 id) const { return _gfbcd::getChrDrDefWP(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefSPType(u32 id) const { return _gfbcd::getChrDrDefSPType(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefSP(u32 id) const { return _gfbcd::getChrDrDefSP(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefAcce(u32 id) const { return _gfbcd::getChrDrDefAcce(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefIdeaBlue(u32 id) const { return _gfbcd::getChrDrDefIdeaBlue(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefIdeaRed(u32 id) const { return _gfbcd::getChrDrDefIdeaRed(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefIdeaWhite(u32 id) const { return _gfbcd::getChrDrDefIdeaWhite(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDefIdeaBlack(u32 id) const { return _gfbcd::getChrDrDefIdeaBlack(*unknown10, id); }

u32 GfBdatChrDr::getChrDrHpMaxLv1(u32 id) const { return _gfbcd::getChrDrHpMaxLv1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrStrengthLv1(u32 id) const { return _gfbcd::getChrDrStrengthLv1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrPowEtherLv1(u32 id) const { return _gfbcd::getChrDrPowEtherLv1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDexLv1(u32 id) const { return _gfbcd::getChrDrDexLv1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrAgilityLv1(u32 id) const { return _gfbcd::getChrDrAgilityLv1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrLuckLv1(u32 id) const { return _gfbcd::getChrDrLuckLv1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrHpMaxLv99(u32 id) const { return _gfbcd::getChrDrHpMaxLv99(*unknown10, id); }

u32 GfBdatChrDr::getChrDrStrengthLv99(u32 id) const { return _gfbcd::getChrDrStrengthLv99(*unknown10, id); }

u32 GfBdatChrDr::getChrDrPowEtherLv99(u32 id) const { return _gfbcd::getChrDrPowEtherLv99(*unknown10, id); }

u32 GfBdatChrDr::getChrDrDexLv99(u32 id) const { return _gfbcd::getChrDrDexLv99(*unknown10, id); }

u32 GfBdatChrDr::getChrDrAgilityLv99(u32 id) const { return _gfbcd::getChrDrAgilityLv99(*unknown10, id); }

u32 GfBdatChrDr::getChrDrLuckLv99(u32 id) const { return _gfbcd::getChrDrLuckLv99(*unknown10, id); }

u32 GfBdatChrDr::getChrDrFavoriteCategory1(u32 id) const { return _gfbcd::getChrDrFavoriteCategory1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrFavoriteCategory2(u32 id) const { return _gfbcd::getChrDrFavoriteCategory2(*unknown10, id); }

u32 GfBdatChrDr::getChrDrFavoriteItem1(u32 id) const { return _gfbcd::getChrDrFavoriteItem1(*unknown10, id); }

u32 GfBdatChrDr::getChrDrFavoriteItem2(u32 id) const { return _gfbcd::getChrDrFavoriteItem2(*unknown10, id); }

u32 GfBdatChrDr::getChrDrCollisionId(u32 id) const { return _gfbcd::getChrDrCollisionId(*unknown10, id); }

const char *GfBdatChrDr::getChrDrCenterBone(u32 id) const { return _gfbcd::getChrDrCenterBone(*unknown10, id); }

const char *GfBdatChrDr::getChrDrCamBone(u32 id) const { return _gfbcd::getChrDrCamBone(*unknown10, id); }

u32 GfBdatChrDr::getChrDrWpnType(u32 driver, u32 slot) const { return _gfbcd::getChrDrWpnType(*unknown10, driver, slot); }

u32 GfBdatChrDr::getChrDrWpRate(u32 id, u32 index) const { return _gfbcd::getChrDrWpRate(*unknown10, id, index); }

u32 GfBdatChrDr::getChrDrDefBlade(u32 driver, u32 slot) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcd::getChrDrDefBlade1, _gfbcd::getChrDrDefBlade2, _gfbcd::getChrDrDefBlade3};
  return getters[slot](*unknown10, driver);
}

u32 GfBdatChrDr::getChrDrFavoriteCategory(u32 driver, u32 favorite) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcd::getChrDrFavoriteCategory1, _gfbcd::getChrDrFavoriteCategory2};
  return getters[favorite](*unknown10, driver);
}

u32 GfBdatChrDr::getChrDrFavoriteItem(u32 driver, u32 favorite) const {
  static u32 (*const getters[])(const CBdatWrapper &, u32) = {_gfbcd::getChrDrFavoriteItem1, _gfbcd::getChrDrFavoriteItem2};
  return getters[favorite](*unknown10, driver);
}

} // namespace gf
