#include "gf/data/gf_bdat_msg.h"

#include "bdat.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"

namespace gf {
namespace _gfbms {

const char *szEmpty = "";

} // namespace _gfbms

enum {
  BDAT_BLD_BLADENAME = 0x14e,
  BDAT_BLD_MERCENAME = 0x14f,
  BDAT_BTL_ARTS_BL_MS = 0x150,
  BDAT_BTL_ARTS_BLSP_MS = 0x151,
  BDAT_BTL_ARTS_DR_MS = 0x152,
  BDAT_BTL_BUFF_CAP = 0x157,
  BDAT_BTL_BUFF_MS = 0x158,
  BDAT_BTL_CLASS_MS = 0x159,
  BDAT_BTL_ENGENUS_MS = 0x15c,
  BDAT_BTL_ENHANCE_CAP = 0x15d,
  BDAT_BTL_SKILL_DR_NAME = 0x15f,
  BDAT_BTL_SKILL_BL_NAME = 0x160,
  BDAT_ITM_HANA_ROLE_MS = 0x163,
  BDAT_ITM_HANA_NARTS_SET_MS = 0x164,
  BDAT_ITM_HANA_ATR_MS = 0x165,
  BDAT_ITM_HANA_ASSIST_MS = 0x166,
  BDAT_ITM_HANA_ARTS_ENH_MS = 0x167,
  BDAT_CHR_BL_MS = 0x168,
  BDAT_CHR_DR_MS = 0x169,
  BDAT_FLD_ACHIEVEMENTTXT = 0x16b,
  BDAT_FLD_ENEMYNAME = 0x16e,
  BDAT_FLD_FIELDSKILLTXT = 0x170,
  BDAT_FLD_LANDMARK = 0x174,
  BDAT_FLD_MAPINFO = 0x175,
  BDAT_FLD_NPCNAME = 0x176,
  BDAT_FLD_QUEST = 0x177,
  BDAT_FLD_QUEST_NORMAL = 0x178,
  BDAT_FLD_QUEST_MINI = 0x179,
  BDAT_FLD_QUEST_BLADE = 0x17a,
  BDAT_FLD_QUEST_ACHIEVEMENT = 0x17b,
  BDAT_FLD_QUEST_MERCENARIES = 0x17c,
  BDAT_ITM_BOOSTER = 0x182,
  BDAT_ITM_COLLECTION = 0x183,
  BDAT_ITM_CRYSTAL = 0x184,
  BDAT_ITM_EVT = 0x185,
  BDAT_ITM_FAVORITE = 0x186,
  BDAT_ITM_INFO = 0x187,
  BDAT_ITM_ORB = 0x188,
  BDAT_ITM_PCEQUIP = 0x189,
  BDAT_ITM_PCWPN_MS = 0x18a,
  BDAT_ITM_PCWPNCHIP_MS = 0x18b,
  BDAT_ITM_PCWPNTYPE_MS = 0x18c,
  BDAT_ITM_PRECIOUS = 0x18d,
  BDAT_ITM_SALVAGE = 0x18e,
  BDAT_ITM_TRESURE = 0x18f,
};

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

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
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
  m_fpItmOrb = NEW_BDAT_WRAPPER(BDAT_ITM_ORB);
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
  if (id < Bdat::getIdTop(m_fpFldEnemyName->data) || id >= Bdat::getIdTop(m_fpFldEnemyName->data) + Bdat::getIdCount(m_fpFldEnemyName->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldEnemyName->data, id);
}

u8 *GfBdatMsg::getFpEnemy() { return m_fpFldEnemyName->data; }

const char *GfBdatMsg::getNameNpc(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldNpcName->data) || id >= Bdat::getIdTop(m_fpFldNpcName->data) + Bdat::getIdCount(m_fpFldNpcName->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldNpcName->data, id);
}

u8 *GfBdatMsg::getFpNpc() { return m_fpFldNpcName->data; }

const char *GfBdatMsg::getNameQuest(QuestID quest, u32 line) { return Bdat::getMSText(getFpQuest(quest), line); }

u8 *GfBdatMsg::getFpQuest(QuestID quest) {
  switch (GfDataQuest::getListQuestCategory(quest)) {
  case QTYPE_MAIN:
    return m_fpFldQuest->data;
  case QTYPE_BLADE:
    return m_fpFldQuestBlade->data;
  case QTYPE_NORMAL:
    if (quest.id < 2000) {
      return m_fpFldQuestMini->data;
    }

    return m_fpFldQuestNormal->data;
  case QTYPE_MERCENARIES:
    return m_fpFldQuestMercenaries->data;
  case QTYPE_ACHIEVEMENT:
    return m_fpFldQuestAchievement->data;
  }

  return m_fpFldQuest->data;
}

u8 *GfBdatMsg::getFpQuest(u32 quest) {
  if (quest < 1000) {
    return m_fpFldQuest->data;
  }

  if (quest < 2000) {
    return m_fpFldQuestMini->data;
  }

  if (quest < 4000) {
    return m_fpFldQuestNormal->data;
  }

  if (quest < 6000) {
    return m_fpFldQuestBlade->data;
  }

  if (quest < 7000) {
    return m_fpFldQuestMercenaries->data;
  }

  return m_fpFldQuest->data;
}

const char *GfBdatMsg::getNameMapInfo(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldMapInfo->data) || id >= Bdat::getIdTop(m_fpFldMapInfo->data) + Bdat::getIdCount(m_fpFldMapInfo->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldMapInfo->data, id);
}

u8 *GfBdatMsg::getFpMapInfo() { return m_fpFldMapInfo->data; }

const char *GfBdatMsg::getNameLandmark(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldLandmark->data) || id >= Bdat::getIdTop(m_fpFldLandmark->data) + Bdat::getIdCount(m_fpFldLandmark->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldLandmark->data, id);
}

u8 *GfBdatMsg::getFpLandmark() { return m_fpFldLandmark->data; }

const char *GfBdatMsg::getNameCollection(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmCollection->data) || id >= Bdat::getIdTop(m_fpItmCollection->data) + Bdat::getIdCount(m_fpItmCollection->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmCollection->data, id);
}

u8 *GfBdatMsg::getFpCollection() { return m_fpItmCollection->data; }

const char *GfBdatMsg::getNameCrystal(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmCrystal->data) || id >= Bdat::getIdTop(m_fpItmCrystal->data) + Bdat::getIdCount(m_fpItmCrystal->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmCrystal->data, id);
}

u8 *GfBdatMsg::getFpCrystal() { return m_fpItmCrystal->data; }

const char *GfBdatMsg::getNamePrecious(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmPrecious->data) || id >= Bdat::getIdTop(m_fpItmPrecious->data) + Bdat::getIdCount(m_fpItmPrecious->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmPrecious->data, id);
}

u8 *GfBdatMsg::getFpPrecious() { return m_fpItmPrecious->data; }

const char *GfBdatMsg::getNameInfo(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmInfo->data) || id >= Bdat::getIdTop(m_fpItmInfo->data) + Bdat::getIdCount(m_fpItmInfo->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmInfo->data, id);
}

u8 *GfBdatMsg::getFpInfo() { return m_fpItmInfo->data; }

const char *GfBdatMsg::getNameEvent(u32 id) {
  if (id < Bdat::getIdTop(m_fpItmEvent->data) || id >= Bdat::getIdTop(m_fpItmEvent->data) + Bdat::getIdCount(m_fpItmEvent->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpItmEvent->data, id);
}

u8 *GfBdatMsg::getFpEvent() { return m_fpItmEvent->data; }

u8 *GfBdatMsg::getFpPcWpn() { return m_fpItmPcWpn->data; }

u8 *GfBdatMsg::getFpPcWpnChip() { return m_fpItmPcWpnChip->data; }

u8 *GfBdatMsg::getFpPcWpnType() { return m_fpItmPcWpnType->data; }

u8 *GfBdatMsg::getFpSalvage() { return m_fpItmSalvage->data; }

u8 *GfBdatMsg::getFpTresure() { return m_fpItmTresure->data; }

u8 *GfBdatMsg::getFpBooster() { return m_fpItmBooster->data; }

u8 *GfBdatMsg::getFpFavorite() { return m_fpItmFavorite->data; }

u8 *GfBdatMsg::getFpOrb() { return m_fpItmOrb->data; }

u8 *GfBdatMsg::getFpPcEquip() { return m_fpItmPcEquip->data; }

const char *GfBdatMsg::getNameBladeName(u32 id) {
  if (id < Bdat::getIdTop(m_fpBldBladeName->data) || id >= Bdat::getIdTop(m_fpBldBladeName->data) + Bdat::getIdCount(m_fpBldBladeName->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpBldBladeName->data, id);
}

u8 *GfBdatMsg::getFpCommonBladeName() { return m_fpBldBladeName->data; }

u8 *GfBdatMsg::getFpMerceName() { return m_fpBldMerceName->data; }

const char *GfBdatMsg::getNameFieldSkill(u32 id) {
  if (id < Bdat::getIdTop(m_fpFldFieldSkill->data) || id >= Bdat::getIdTop(m_fpFldFieldSkill->data) + Bdat::getIdCount(m_fpFldFieldSkill->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpFldFieldSkill->data, id);
}

u8 *GfBdatMsg::getFpFieldSkill() { return m_fpFldFieldSkill->data; }

u8 *GfBdatMsg::getFpAchievement() { return m_fpFldAchievement->data; }

const char *GfBdatMsg::getNameChrDr(u32 id) {
  if (id < Bdat::getIdTop(m_fpChrDr->data) || id >= Bdat::getIdTop(m_fpChrDr->data) + Bdat::getIdCount(m_fpChrDr->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpChrDr->data, id);
}

u8 *GfBdatMsg::getFpChrDr() { return m_fpChrDr->data; }

const char *GfBdatMsg::getNameChrBl(u32 id) {
  if (id < Bdat::getIdTop(m_fpChrBl->data) || id >= Bdat::getIdTop(m_fpChrBl->data) + Bdat::getIdCount(m_fpChrBl->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpChrBl->data, id);
}

u8 *GfBdatMsg::getFpChrBl() { return m_fpChrBl->data; }

const char *GfBdatMsg::getNameEnGenus(u32 id) {
  if (id < Bdat::getIdTop(m_fpBtlEnGenus->data) || id >= Bdat::getIdTop(m_fpBtlEnGenus->data) + Bdat::getIdCount(m_fpBtlEnGenus->data)) {
    return _gfbms::szEmpty;
  }

  return Bdat::getMSText(m_fpChrBl->data, id);
}

u8 *GfBdatMsg::getFpBtlClass() { return m_fpBtlClass->data; }

u8 *GfBdatMsg::getFpBlArtsMs() { return m_fpBlArtsMs->data; }

u8 *GfBdatMsg::getFpBlSpArtsMs() { return m_fpBlSpArtsMs->data; }

u8 *GfBdatMsg::getFpBlSkill() { return m_fpBlSkill->data; }

u8 *GfBdatMsg::getFpDrArtsMs() { return m_fpDrArtsMs->data; }

u8 *GfBdatMsg::getFpBtlEnhanceCap() { return m_fpBtlEnhanceCap->data; }

u8 *GfBdatMsg::getFpBlBuffMs() { return m_fpBtlBuffMs->data; }

u8 *GfBdatMsg::getFpBlBuffCap() { return m_fpBtlBuffCap->data; }

u8 *GfBdatMsg::getFpBtlHanaRole() { return m_fpBtlHanaRole->data; }

u8 *GfBdatMsg::getFpBtlHanaNArts() { return m_fpBtlHanaNArts->data; }

u8 *GfBdatMsg::getFpBtlHanaArts() { return m_fpBtlHanaArts->data; }

u8 *GfBdatMsg::getFpBtlHanaAtr() { return m_fpBtlHanaAtr->data; }

u8 *GfBdatMsg::getFpBtlHanaAssist() { return m_fpBtlHanaAssist->data; }

u8 *GfBdatMsg::getFpBtlSkillDr() { return m_fpBtlSkillDr->data; }

u8 *GfBdatMsg::getFpRscEnGenus() { return m_fpBtlEnGenus->data; }

} // namespace gf
