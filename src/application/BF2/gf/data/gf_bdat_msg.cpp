#include "gf/data/gf_bdat_msg.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbms {

const char *szEmpty = "";

} // namespace _gfbms

CBdatWrapper *GfBdatMsg::m_fpBldBladeName;
CBdatWrapper *GfBdatMsg::m_fpBldMerceName;
CBdatWrapper *GfBdatMsg::m_fpFldEnemyName;
CBdatWrapper *GfBdatMsg::m_fpFldNpcName;
CBdatWrapper *GfBdatMsg::m_fpFldQuest;
CBdatWrapper *GfBdatMsg::m_fpFldMapInfo;
CBdatWrapper *GfBdatMsg::m_fpFldLandmark;
CBdatWrapper *GfBdatMsg::m_fpFldFieldSkill;
CBdatWrapper *GfBdatMsg::m_fpItmCollection;
CBdatWrapper *GfBdatMsg::m_fpItmCrystal;
CBdatWrapper *GfBdatMsg::m_fpItmPrecious;
CBdatWrapper *GfBdatMsg::m_fpItmInfo;
CBdatWrapper *GfBdatMsg::m_fpItmEvent;
CBdatWrapper *GfBdatMsg::m_fpItmPcWpn;
CBdatWrapper *GfBdatMsg::m_fpItmPcWpnChip;
CBdatWrapper *GfBdatMsg::m_fpItmPcWpnType;
CBdatWrapper *GfBdatMsg::m_fpItmSalvage;
CBdatWrapper *GfBdatMsg::m_fpItmTresure;
CBdatWrapper *GfBdatMsg::m_fpItmFavorite;
CBdatWrapper *GfBdatMsg::m_fpItmBooster;
CBdatWrapper *GfBdatMsg::m_fpItmOrb;
CBdatWrapper *GfBdatMsg::m_fpItmPcEquip;
CBdatWrapper *GfBdatMsg::m_fpChrDr;
CBdatWrapper *GfBdatMsg::m_fpChrBl;
CBdatWrapper *GfBdatMsg::m_fpBtlClass;
CBdatWrapper *GfBdatMsg::m_fpBlArtsMs;
CBdatWrapper *GfBdatMsg::m_fpBlSpArtsMs;
CBdatWrapper *GfBdatMsg::m_fpBlSkill;
CBdatWrapper *GfBdatMsg::m_fpDrArtsMs;
CBdatWrapper *GfBdatMsg::m_fpBtlEnhanceCap;
CBdatWrapper *GfBdatMsg::m_fpFldQuestNormal;
CBdatWrapper *GfBdatMsg::m_fpFldQuestMini;
CBdatWrapper *GfBdatMsg::m_fpFldQuestBlade;
CBdatWrapper *GfBdatMsg::m_fpFldQuestAchievement;
CBdatWrapper *GfBdatMsg::m_fpFldQuestMercenaries;
CBdatWrapper *GfBdatMsg::m_fpBtlBuffMs;
CBdatWrapper *GfBdatMsg::m_fpBtlBuffCap;
CBdatWrapper *GfBdatMsg::m_fpFldAchievement;
CBdatWrapper *GfBdatMsg::m_fpBtlHanaRole;
CBdatWrapper *GfBdatMsg::m_fpBtlHanaNArts;
CBdatWrapper *GfBdatMsg::m_fpBtlHanaArts;
CBdatWrapper *GfBdatMsg::m_fpBtlHanaAtr;
CBdatWrapper *GfBdatMsg::m_fpBtlHanaAssist;
CBdatWrapper *GfBdatMsg::m_fpBtlSkillDr;
CBdatWrapper *GfBdatMsg::m_fpBtlEnGenus;

GfBdatMsg::GfBdatMsg() {
  m_fpBldBladeName = nullptr;
  m_fpBldMerceName = nullptr;
  m_fpFldEnemyName = nullptr;
  m_fpFldNpcName = nullptr;
  m_fpFldQuest = nullptr;
  m_fpFldMapInfo = nullptr;
  m_fpFldLandmark = nullptr;
  m_fpFldFieldSkill = nullptr;
  m_fpFldAchievement = nullptr;
  m_fpItmCollection = nullptr;
  m_fpItmCrystal = nullptr;
  m_fpItmPrecious = nullptr;
  m_fpItmInfo = nullptr;
  m_fpItmEvent = nullptr;
  m_fpItmPcWpn = nullptr;
  m_fpItmPcWpnChip = nullptr;
  m_fpItmPcWpnType = nullptr;
  m_fpItmSalvage = nullptr;
  m_fpItmTresure = nullptr;
  m_fpItmFavorite = nullptr;
  m_fpItmBooster = nullptr;
  m_fpItmOrb = nullptr;
  m_fpItmPcEquip = nullptr;
  m_fpChrDr = nullptr;
  m_fpChrBl = nullptr;
  m_fpBtlClass = nullptr;
  m_fpBlArtsMs = nullptr;
  m_fpBlSpArtsMs = nullptr;
  m_fpBlSkill = nullptr;
  m_fpDrArtsMs = nullptr;
  m_fpBtlEnhanceCap = nullptr;
  m_fpFldQuestNormal = nullptr;
  m_fpFldQuestMini = nullptr;
  m_fpFldQuestBlade = nullptr;
  m_fpFldQuestAchievement = nullptr;
  m_fpFldQuestMercenaries = nullptr;
  m_fpBtlBuffMs = nullptr;
  m_fpBtlBuffCap = nullptr;
  m_fpBtlHanaRole = nullptr;
  m_fpBtlHanaNArts = nullptr;
  m_fpBtlHanaArts = nullptr;
  m_fpBtlHanaAtr = nullptr;
  m_fpBtlHanaAssist = nullptr;
  m_fpBtlSkillDr = nullptr;
  m_fpBtlEnGenus = nullptr;
  bdatRefresh();
}

GfBdatMsg::~GfBdatMsg() { destroyFP(); }

void GfBdatMsg::destroyFP() {
  if (m_fpBtlEnGenus != nullptr) {
    delete m_fpBtlEnGenus;
    m_fpBtlEnGenus = nullptr;
  }

  if (m_fpBldMerceName != nullptr) {
    delete m_fpBldMerceName;
    m_fpBldMerceName = nullptr;
  }

  if (m_fpBldBladeName != nullptr) {
    delete m_fpBldBladeName;
    m_fpBldBladeName = nullptr;
  }

  if (m_fpFldEnemyName != nullptr) {
    delete m_fpFldEnemyName;
    m_fpFldEnemyName = nullptr;
  }

  if (m_fpFldNpcName != nullptr) {
    delete m_fpFldNpcName;
    m_fpFldNpcName = nullptr;
  }

  if (m_fpFldQuest != nullptr) {
    delete m_fpFldQuest;
    m_fpFldQuest = nullptr;
  }

  if (m_fpFldMapInfo != nullptr) {
    delete m_fpFldMapInfo;
    m_fpFldMapInfo = nullptr;
  }

  if (m_fpFldLandmark != nullptr) {
    delete m_fpFldLandmark;
    m_fpFldLandmark = nullptr;
  }

  if (m_fpFldFieldSkill != nullptr) {
    delete m_fpFldFieldSkill;
    m_fpFldFieldSkill = nullptr;
  }

  if (m_fpFldAchievement != nullptr) {
    delete m_fpFldAchievement;
    m_fpFldAchievement = nullptr;
  }

  if (m_fpItmCollection != nullptr) {
    delete m_fpItmCollection;
    m_fpItmCollection = nullptr;
  }

  if (m_fpItmCrystal != nullptr) {
    delete m_fpItmCrystal;
    m_fpItmCrystal = nullptr;
  }

  if (m_fpItmPrecious != nullptr) {
    delete m_fpItmPrecious;
    m_fpItmPrecious = nullptr;
  }

  if (m_fpItmInfo != nullptr) {
    delete m_fpItmInfo;
    m_fpItmInfo = nullptr;
  }

  if (m_fpItmEvent != nullptr) {
    delete m_fpItmEvent;
    m_fpItmEvent = nullptr;
  }

  if (m_fpItmPcWpn != nullptr) {
    delete m_fpItmPcWpn;
    m_fpItmPcWpn = nullptr;
  }

  if (m_fpItmPcWpnChip != nullptr) {
    delete m_fpItmPcWpnChip;
    m_fpItmPcWpnChip = nullptr;
  }

  if (m_fpItmPcWpnType != nullptr) {
    delete m_fpItmPcWpnType;
    m_fpItmPcWpnType = nullptr;
  }

  if (m_fpItmSalvage != nullptr) {
    delete m_fpItmSalvage;
    m_fpItmSalvage = nullptr;
  }

  if (m_fpItmTresure != nullptr) {
    delete m_fpItmTresure;
    m_fpItmTresure = nullptr;
  }

  if (m_fpItmFavorite != nullptr) {
    delete m_fpItmFavorite;
    m_fpItmFavorite = nullptr;
  }

  if (m_fpItmBooster != nullptr) {
    delete m_fpItmBooster;
    m_fpItmBooster = nullptr;
  }

  if (m_fpItmOrb != nullptr) {
    delete m_fpItmOrb;
    m_fpItmOrb = nullptr;
  }

  if (m_fpItmPcEquip != nullptr) {
    delete m_fpItmPcEquip;
    m_fpItmPcEquip = nullptr;
  }

  if (m_fpChrDr != nullptr) {
    delete m_fpChrDr;
    m_fpChrDr = nullptr;
  }

  if (m_fpChrBl != nullptr) {
    delete m_fpChrBl;
    m_fpChrBl = nullptr;
  }

  if (m_fpBtlClass != nullptr) {
    delete m_fpBtlClass;
    m_fpBtlClass = nullptr;
  }

  if (m_fpBlArtsMs != nullptr) {
    delete m_fpBlArtsMs;
    m_fpBlArtsMs = nullptr;
  }

  if (m_fpBlSpArtsMs != nullptr) {
    delete m_fpBlSpArtsMs;
    m_fpBlSpArtsMs = nullptr;
  }

  if (m_fpBlSkill != nullptr) {
    delete m_fpBlSkill;
    m_fpBlSkill = nullptr;
  }

  if (m_fpDrArtsMs != nullptr) {
    delete m_fpDrArtsMs;
    m_fpDrArtsMs = nullptr;
  }

  if (m_fpBtlEnhanceCap != nullptr) {
    delete m_fpBtlEnhanceCap;
    m_fpBtlEnhanceCap = nullptr;
  }

  if (m_fpFldQuestNormal != nullptr) {
    delete m_fpFldQuestNormal;
    m_fpFldQuestNormal = nullptr;
  }

  if (m_fpFldQuestMini != nullptr) {
    delete m_fpFldQuestMini;
    m_fpFldQuestMini = nullptr;
  }

  if (m_fpFldQuestBlade != nullptr) {
    delete m_fpFldQuestBlade;
    m_fpFldQuestBlade = nullptr;
  }

  if (m_fpFldQuestAchievement != nullptr) {
    delete m_fpFldQuestAchievement;
    m_fpFldQuestAchievement = nullptr;
  }

  if (m_fpFldQuestMercenaries != nullptr) {
    delete m_fpFldQuestMercenaries;
    m_fpFldQuestMercenaries = nullptr;
  }

  if (m_fpBtlBuffMs != nullptr) {
    delete m_fpBtlBuffMs;
    m_fpBtlBuffMs = nullptr;
  }

  if (m_fpBtlBuffCap != nullptr) {
    delete m_fpBtlBuffCap;
    m_fpBtlBuffCap = nullptr;
  }

  if (m_fpBtlHanaRole != nullptr) {
    delete m_fpBtlHanaRole;
    m_fpBtlHanaRole = nullptr;
  }

  if (m_fpBtlHanaNArts != nullptr) {
    delete m_fpBtlHanaNArts;
    m_fpBtlHanaNArts = nullptr;
  }

  if (m_fpBtlHanaArts != nullptr) {
    delete m_fpBtlHanaArts;
    m_fpBtlHanaArts = nullptr;
  }

  if (m_fpBtlHanaAtr != nullptr) {
    delete m_fpBtlHanaAtr;
    m_fpBtlHanaAtr = nullptr;
  }

  if (m_fpBtlHanaAssist != nullptr) {
    delete m_fpBtlHanaAssist;
    m_fpBtlHanaAssist = nullptr;
  }

  if (m_fpBtlSkillDr != nullptr) {
    delete m_fpBtlSkillDr;
    m_fpBtlSkillDr = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                                                                         \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatMsg::createFP() {
// The line numbers passed to the allocator decide between mov and orr.
#line 188
  m_fpBldBladeName = NEW_BDAT_WRAPPER(BDAT_BLD_BLADENAME);
  m_fpBldMerceName = NEW_BDAT_WRAPPER(BDAT_BLD_MERCENAME);
  m_fpFldEnemyName = NEW_BDAT_WRAPPER(BDAT_FLD_ENEMYNAME);
  m_fpFldNpcName = NEW_BDAT_WRAPPER(BDAT_FLD_NPCNAME);
  m_fpFldQuest = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST);
  m_fpFldMapInfo = NEW_BDAT_WRAPPER(BDAT_FLD_MAPINFO);
  m_fpFldLandmark = NEW_BDAT_WRAPPER(BDAT_FLD_LANDMARK);
  m_fpFldFieldSkill = NEW_BDAT_WRAPPER(BDAT_FLD_FIELDSKILLTXT);
  m_fpFldAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENTTXT);
  m_fpItmCollection = NEW_BDAT_WRAPPER(BDAT_ITM_COLLECTION);
  m_fpItmCrystal = NEW_BDAT_WRAPPER(BDAT_ITM_CRYSTAL);
  m_fpItmPrecious = NEW_BDAT_WRAPPER(BDAT_ITM_PRECIOUS);
  m_fpItmInfo = NEW_BDAT_WRAPPER(BDAT_ITM_INFO);
  m_fpItmEvent = NEW_BDAT_WRAPPER(BDAT_ITM_EVT);
  m_fpItmPcWpn = NEW_BDAT_WRAPPER(BDAT_ITM_PCWPN_MS);
  m_fpItmPcWpnChip = NEW_BDAT_WRAPPER(BDAT_ITM_PCWPNCHIP_MS);
  m_fpItmPcWpnType = NEW_BDAT_WRAPPER(BDAT_ITM_PCWPNTYPE_MS);
  m_fpItmSalvage = NEW_BDAT_WRAPPER(BDAT_ITM_SALVAGE);
  m_fpItmTresure = NEW_BDAT_WRAPPER(BDAT_ITM_TRESURE);
  m_fpItmFavorite = NEW_BDAT_WRAPPER(BDAT_ITM_FAVORITE);
  m_fpItmBooster = NEW_BDAT_WRAPPER(BDAT_ITM_BOOSTER);
  m_fpItmOrb = NEW_BDAT_WRAPPER(BDAT_ITM_ORB_MS);
  m_fpItmPcEquip = NEW_BDAT_WRAPPER(BDAT_ITM_PCEQUIP);
  m_fpChrDr = NEW_BDAT_WRAPPER(BDAT_CHR_DR_MS);
  m_fpChrBl = NEW_BDAT_WRAPPER(BDAT_CHR_BL_MS);
  m_fpBtlClass = NEW_BDAT_WRAPPER(BDAT_BTL_CLASS_MS);
  m_fpBlArtsMs = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_BL_MS);
  m_fpBlSpArtsMs = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_BLSP_MS);
  m_fpBlSkill = NEW_BDAT_WRAPPER(BDAT_BTL_SKILL_BL_NAME);
  m_fpDrArtsMs = NEW_BDAT_WRAPPER(BDAT_BTL_ARTS_DR_MS);
  m_fpBtlEnhanceCap = NEW_BDAT_WRAPPER(BDAT_BTL_ENHANCE_CAP);
  m_fpFldQuestNormal = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_NORMAL);
  m_fpFldQuestMini = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_MINI);
  m_fpFldQuestBlade = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_BLADE);
  m_fpFldQuestAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_ACHIEVEMENT);
  m_fpFldQuestMercenaries = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_MERCENARIES);
  m_fpBtlBuffMs = NEW_BDAT_WRAPPER(BDAT_BTL_BUFF_MS);
  m_fpBtlBuffCap = NEW_BDAT_WRAPPER(BDAT_BTL_BUFF_CAP);
  m_fpBtlHanaRole = NEW_BDAT_WRAPPER(BDAT_ITM_HANA_ROLE_MS);
  m_fpBtlHanaNArts = NEW_BDAT_WRAPPER(BDAT_ITM_HANA_NARTS_SET_MS);
  m_fpBtlHanaArts = NEW_BDAT_WRAPPER(BDAT_ITM_HANA_ARTS_ENH_MS);
  m_fpBtlHanaAtr = NEW_BDAT_WRAPPER(BDAT_ITM_HANA_ATR_MS);
  m_fpBtlHanaAssist = NEW_BDAT_WRAPPER(BDAT_ITM_HANA_ASSIST_MS);
  m_fpBtlSkillDr = NEW_BDAT_WRAPPER(BDAT_BTL_SKILL_DR_NAME);
  m_fpBtlEnGenus = NEW_BDAT_WRAPPER(BDAT_BTL_ENGENUS_MS);
}

void GfBdatMsg::bdatRefresh() {
  destroyFP();
  createFP();
}

const char *GfBdatMsg::getNameEnemy(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldEnemyName->unknown00) || id >= Bdat::getIdTop(m_fpFldEnemyName->unknown00) + Bdat::getIdCount(m_fpFldEnemyName->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldEnemyName->unknown00, id);
}

u8 *GfBdatMsg::getFpEnemy() { return m_fpFldEnemyName->unknown00; }

const char *GfBdatMsg::getNameNpc(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldNpcName->unknown00) || id >= Bdat::getIdTop(m_fpFldNpcName->unknown00) + Bdat::getIdCount(m_fpFldNpcName->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldNpcName->unknown00, id);
}

u8 *GfBdatMsg::getFpNpc() { return m_fpFldNpcName->unknown00; }

const char *GfBdatMsg::getNameQuest(QuestID quest, u32 line) { return Bdat::getMSText(getFpQuest(quest), line); }

u8 *GfBdatMsg::getFpQuest(QuestID quest) {
  switch (GfDataQuest::getListQuestCategory(quest)) {
  case QTYPE_MAIN:
    return m_fpFldQuest->unknown00;
  case QTYPE_BLADE:
    return m_fpFldQuestBlade->unknown00;
  case QTYPE_NORMAL:
    if (quest.id < 2000) {
      return m_fpFldQuestMini->unknown00;
    }

    return m_fpFldQuestNormal->unknown00;
  case QTYPE_MERCENARIES:
    return m_fpFldQuestMercenaries->unknown00;
  case QTYPE_ACHIEVEMENT:
    return m_fpFldQuestAchievement->unknown00;
  }

  return m_fpFldQuest->unknown00;
}

u8 *GfBdatMsg::getFpQuest(u32 quest) {
  if (quest < 1000) {
    return m_fpFldQuest->unknown00;
  }

  if (quest < 2000) {
    return m_fpFldQuestMini->unknown00;
  }

  if (quest < 4000) {
    return m_fpFldQuestNormal->unknown00;
  }

  if (quest < 6000) {
    return m_fpFldQuestBlade->unknown00;
  }

  if (quest < 7000) {
    return m_fpFldQuestMercenaries->unknown00;
  }

  return m_fpFldQuest->unknown00;
}

const char *GfBdatMsg::getNameMapInfo(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldMapInfo->unknown00) || id >= Bdat::getIdTop(m_fpFldMapInfo->unknown00) + Bdat::getIdCount(m_fpFldMapInfo->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldMapInfo->unknown00, id);
}

u8 *GfBdatMsg::getFpMapInfo() { return m_fpFldMapInfo->unknown00; }

const char *GfBdatMsg::getNameLandmark(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldLandmark->unknown00) || id >= Bdat::getIdTop(m_fpFldLandmark->unknown00) + Bdat::getIdCount(m_fpFldLandmark->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldLandmark->unknown00, id);
}

u8 *GfBdatMsg::getFpLandmark() { return m_fpFldLandmark->unknown00; }

const char *GfBdatMsg::getNameCollection(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmCollection->unknown00) || id >= Bdat::getIdTop(m_fpItmCollection->unknown00) + Bdat::getIdCount(m_fpItmCollection->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmCollection->unknown00, id);
}

u8 *GfBdatMsg::getFpCollection() { return m_fpItmCollection->unknown00; }

const char *GfBdatMsg::getNameCrystal(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmCrystal->unknown00) || id >= Bdat::getIdTop(m_fpItmCrystal->unknown00) + Bdat::getIdCount(m_fpItmCrystal->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmCrystal->unknown00, id);
}

u8 *GfBdatMsg::getFpCrystal() { return m_fpItmCrystal->unknown00; }

const char *GfBdatMsg::getNamePrecious(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmPrecious->unknown00) || id >= Bdat::getIdTop(m_fpItmPrecious->unknown00) + Bdat::getIdCount(m_fpItmPrecious->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmPrecious->unknown00, id);
}

u8 *GfBdatMsg::getFpPrecious() { return m_fpItmPrecious->unknown00; }

const char *GfBdatMsg::getNameInfo(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmInfo->unknown00) || id >= Bdat::getIdTop(m_fpItmInfo->unknown00) + Bdat::getIdCount(m_fpItmInfo->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmInfo->unknown00, id);
}

u8 *GfBdatMsg::getFpInfo() { return m_fpItmInfo->unknown00; }

const char *GfBdatMsg::getNameEvent(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmEvent->unknown00) || id >= Bdat::getIdTop(m_fpItmEvent->unknown00) + Bdat::getIdCount(m_fpItmEvent->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmEvent->unknown00, id);
}

u8 *GfBdatMsg::getFpEvent() { return m_fpItmEvent->unknown00; }

u8 *GfBdatMsg::getFpPcWpn() { return m_fpItmPcWpn->unknown00; }

u8 *GfBdatMsg::getFpPcWpnChip() { return m_fpItmPcWpnChip->unknown00; }

u8 *GfBdatMsg::getFpPcWpnType() { return m_fpItmPcWpnType->unknown00; }

u8 *GfBdatMsg::getFpSalvage() { return m_fpItmSalvage->unknown00; }

u8 *GfBdatMsg::getFpTresure() { return m_fpItmTresure->unknown00; }

u8 *GfBdatMsg::getFpBooster() { return m_fpItmBooster->unknown00; }

u8 *GfBdatMsg::getFpFavorite() { return m_fpItmFavorite->unknown00; }

u8 *GfBdatMsg::getFpOrb() { return m_fpItmOrb->unknown00; }

u8 *GfBdatMsg::getFpPcEquip() { return m_fpItmPcEquip->unknown00; }

const char *GfBdatMsg::getNameBladeName(u32 id) {
  if (id < Bdat::getIdTop(m_fpBldBladeName->unknown00) || id >= Bdat::getIdTop(m_fpBldBladeName->unknown00) + Bdat::getIdCount(m_fpBldBladeName->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpBldBladeName->unknown00, id);
}

u8 *GfBdatMsg::getFpCommonBladeName() { return m_fpBldBladeName->unknown00; }

u8 *GfBdatMsg::getFpMerceName() { return m_fpBldMerceName->unknown00; }

const char *GfBdatMsg::getNameFieldSkill(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldFieldSkill->unknown00) || id >= Bdat::getIdTop(m_fpFldFieldSkill->unknown00) + Bdat::getIdCount(m_fpFldFieldSkill->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldFieldSkill->unknown00, id);
}

u8 *GfBdatMsg::getFpFieldSkill() { return m_fpFldFieldSkill->unknown00; }

u8 *GfBdatMsg::getFpAchievement() { return m_fpFldAchievement->unknown00; }

const char *GfBdatMsg::getNameChrDr(u32 id) {
  if (id < Bdat::getIdTop(m_fpChrDr->unknown00) || id >= Bdat::getIdTop(m_fpChrDr->unknown00) + Bdat::getIdCount(m_fpChrDr->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpChrDr->unknown00, id);
}

u8 *GfBdatMsg::getFpChrDr() { return m_fpChrDr->unknown00; }

const char *GfBdatMsg::getNameChrBl(u32 id) {
  if (id < Bdat::getIdTop(m_fpChrBl->unknown00) || id >= Bdat::getIdTop(m_fpChrBl->unknown00) + Bdat::getIdCount(m_fpChrBl->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpChrBl->unknown00, id);
}

u8 *GfBdatMsg::getFpChrBl() { return m_fpChrBl->unknown00; }

const char *GfBdatMsg::getNameEnGenus(u32 id) {
  if (id < Bdat::getIdTop(m_fpBtlEnGenus->unknown00) || id >= Bdat::getIdTop(m_fpBtlEnGenus->unknown00) + Bdat::getIdCount(m_fpBtlEnGenus->unknown00)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpChrBl->unknown00, id);
}

u8 *GfBdatMsg::getFpBtlClass() { return m_fpBtlClass->unknown00; }

u8 *GfBdatMsg::getFpBlArtsMs() { return m_fpBlArtsMs->unknown00; }

u8 *GfBdatMsg::getFpBlSpArtsMs() { return m_fpBlSpArtsMs->unknown00; }

u8 *GfBdatMsg::getFpBlSkill() { return m_fpBlSkill->unknown00; }

u8 *GfBdatMsg::getFpDrArtsMs() { return m_fpDrArtsMs->unknown00; }

u8 *GfBdatMsg::getFpBtlEnhanceCap() { return m_fpBtlEnhanceCap->unknown00; }

u8 *GfBdatMsg::getFpBlBuffMs() { return m_fpBtlBuffMs->unknown00; }

u8 *GfBdatMsg::getFpBlBuffCap() { return m_fpBtlBuffCap->unknown00; }

u8 *GfBdatMsg::getFpBtlHanaRole() { return m_fpBtlHanaRole->unknown00; }

u8 *GfBdatMsg::getFpBtlHanaNArts() { return m_fpBtlHanaNArts->unknown00; }

u8 *GfBdatMsg::getFpBtlHanaArts() { return m_fpBtlHanaArts->unknown00; }

u8 *GfBdatMsg::getFpBtlHanaAtr() { return m_fpBtlHanaAtr->unknown00; }

u8 *GfBdatMsg::getFpBtlHanaAssist() { return m_fpBtlHanaAssist->unknown00; }

u8 *GfBdatMsg::getFpBtlSkillDr() { return m_fpBtlSkillDr->unknown00; }

u8 *GfBdatMsg::getFpRscEnGenus() { return m_fpBtlEnGenus->unknown00; }

} // namespace gf
