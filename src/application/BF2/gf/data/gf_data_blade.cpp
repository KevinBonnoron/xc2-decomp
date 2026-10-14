#include "gf/data/gf_data_blade.h"
#include "bdat.h"
#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/event/gf_event.h"

namespace gf {

enum {
  FLAG_BLADE_HOMURI_NAME_HIKARI = 0x89fb,
};

enum {
  BLADE_HOMURA = 1001,
  BLADE_HIKARI = 1002,
};

enum {
  BLADE_REGULAR_FIRST = 1001,
  BLADE_REGULAR_END = 1014,
  BLADE_RARE_FIRST = 1014,
  BLADE_COMMON_FIRST = 1197,
  BLADE_COMMON_END = 1397,
  BLADE_UI_COMMON_FIRST = 1397,
  BLADE_UI_COMMON_END = 1401,
  BLADE_ACT_COMMON_FIRST = 1401,
  BLADE_ACT_COMMON_END = 1423,
};

enum {
  BLADE_ACT_FIRST = 1051,
  BLADE_CHANGE_WEAPON = 1039,
  BLADE_CHANGE_WEAPON_RANGE_FIRST = 1043,
};

enum {
  DEBUG_CHANGE_IDEA_TRUST = 4,
};

enum {
  BLADE_DUMMY_REGULAR_FIRST = 1012,
  BLADE_DUMMY_REGULAR_SECOND = 1013,
  BLADE_DUMMY_RARE = 1073,
  BLADE_REAL_ALIAS = 1050,
  BLADE_REAL_ALIAS_TARGET = 1022,
};

constexpr u32 BLADE_REGULAR_COUNT = BLADE_REGULAR_END - BLADE_REGULAR_FIRST;
constexpr u32 BLADE_RARE_COUNT = 176;
constexpr u32 BLADE_RARE_INDEX = 20;
constexpr u32 BLADE_COMMON_COUNT = BLADE_ACT_COMMON_END - BLADE_COMMON_FIRST;
constexpr u32 BLADE_COUNT = 422;
constexpr u32 BLADE_ACT_COUNT = BLADE_ACT_COMMON_END - BLADE_ACT_COMMON_FIRST;
constexpr u32 BLADE_HANA_COUNT = BLADE_HANA_JD - BLADE_HANA_JS + 1;
constexpr u32 BLADE_CHANGE_WEAPON_RANGE_COUNT = 8;
constexpr f32 SCALE_PERCENT = 0.01f;
constexpr u32 CROWN_POINT_MAX = 5;
constexpr u32 CROWN_POINT_MIN = 1;
constexpr u32 PERSONALITY_VOICE_FIRST = 61;
constexpr u32 NORMAL_TALK_COUNT = 32;
constexpr u32 CHIP_CREATE_WEAPON_TYPE_COUNT = 16;
constexpr u32 BDAT_COMMON_BLADE_NAME = 0x14e;
constexpr u32 BDAT_BLADE_NAME = 0x168;

void GfDataBlade::setCreator(u32 blade, u32 creator) {
  if (blade != 0) {
    getSDataBlade(blade)->creator = creator;
  }
}

u16 GfDataBlade::getCreator(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->creator;
}

SDataBlade *GfDataBlade::getSDataBlade(u32 blade) {
  u32 index = getBladeRelativeID(blade);
  return &GfDataManager::getDataGame()->blades[index];
}

u32 GfDataBlade::getBladeID(u32 index) {
  if (index < BLADE_RARE_INDEX) {
    u32 blade = index + BLADE_REGULAR_FIRST;
    if (blade >= BLADE_REGULAR_END) {
      blade = 0;
    }

    return blade;
  }

  if (index < BLADE_RARE_INDEX + BLADE_RARE_COUNT) {
    u32 blade = index - BLADE_RARE_INDEX + BLADE_RARE_FIRST;
    return blade < GfBdatChrBl::get()->getChrBlEnd() ? blade : 0;
  }

  return index < BLADE_COUNT ? index + BLADE_REGULAR_FIRST : 0;
}

u8 GfDataBlade::getBladeWpnType(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->weaponType;
}

bool GfDataBlade::isDisableHomuraHikari(u32 blade) {
  if (GfDataParty::isExistBlade(BLADE_HOMURA) != GfDataParty::isExistBlade(BLADE_HIKARI)) {
    return false;
  }

  SDataGame *dataGame = GfDataManager::getDataGame();
  if (blade == BLADE_HIKARI) {
    if (!isHikariCurrent()) {
      return true;
    }
  } else if (blade == BLADE_HOMURA) {
    if (isHikariCurrent()) {
      return true;
    }
  }

  return false;
}

bool GfDataBlade::isHikariCurrent() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->hikariCurrent != 0;
}

bool GfDataBlade::isEnableEngageRex(u32 blade) { return getSDataBlade(blade)->enableEngageRex != 0; }

void GfDataBlade::setEnableEngageRex(u32 blade, bool enableEngageRex) {
  SDataBlade *dataBlade = getSDataBlade(blade);
  dataBlade->enableEngageRex = enableEngageRex;
}

u32 GfDataBlade::getBLD_NameList(u32 blade) {
  if (!isCommonBlade(blade)) {
    return 0;
  }

  u16 &nameListCategory = getSDataBlade(blade)->nameListCategory;
  if (nameListCategory == 0) {
    return 0;
  }

  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  u32 nameList = bdatBlade->getNameListStart();
  u32 end = bdatBlade->getNameListEnd();
  for (; nameList < end; nameList++) {
    if (bdatBlade->getNameListCategory(nameList) == nameListCategory) {
      return nameList;
    }
  }

  return 0;
}

bool GfDataBlade::isCommonBlade(u32 blade) { return blade - BLADE_COMMON_FIRST < BLADE_COMMON_COUNT; }

u32 GfDataBlade::getCrownPoint(u32 blade) {
  static const u16 crownPointWildcards[] = {63, 64, 65, 66};

  if (isRegularBlade(blade)) {
    return CROWN_POINT_MAX;
  }

  if (isRareBlade(blade)) {
    return CROWN_POINT_MAX;
  }

  if (isCommonBlade(blade)) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    u32 kizunaringMax = getKizunaringMax(blade);
    for (u32 i = 0; i < sizeof(crownPointWildcards) / sizeof(crownPointWildcards[0]); i++) {
      if (kizunaringMax <= bdatBattle->getWildcardDatavalueU2(crownPointWildcards[i])) {
        return i + 1;
      }
    }
  }

  return CROWN_POINT_MIN;
}

bool GfDataBlade::isRegularBlade(u32 blade) { return blade - BLADE_REGULAR_FIRST < BLADE_REGULAR_COUNT; }

bool GfDataBlade::isRareBlade(u32 blade) {
  if (blade >= BLADE_RARE_FIRST) {
    return blade < GfBdatChrBl::get()->getChrBlEnd();
  }

  return false;
}

u32 GfDataBlade::getBornTime(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->bornTime;
}

u8 GfDataBlade::getEyeRotControl(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->eyeRotControl;
}

void GfDataBlade::setHikariCurrent(bool hikariCurrent) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->hikariCurrent = hikariCurrent;
}

bool GfDataBlade::isHomuriNameHikari() {
  u32 flag = GfGameFlag::getLocal(1, FLAG_BLADE_HOMURI_NAME_HIKARI);
  return flag != 0;
}

void GfDataBlade::setHomuriNameHikari(bool homuriNameHikari) { GfGameFlag::setLocal(1, FLAG_BLADE_HOMURI_NAME_HIKARI, homuriNameHikari); }

u16 GfDataBlade::makeNormalTalkByPersonality(u32 personality) {
  static const u16 normalTalks[NORMAL_TALK_COUNT] = {
      41525, 41525, 41526, 41527, 41528, 41528, 41529, 41529, 41530, 41530, 41531, 41531, 41532, 41532, 41533, 41533,
      41534, 41534, 41535, 41535, 41536, 41536, 41537, 41537, 41538, 41538, 41539, 41539, 41540, 41540, 41541, 41542,
  };

  u32 voice = GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
  u16 normalTalk = 0;
  u32 index = 0;
  if (voice != 0) {
    index = voice - PERSONALITY_VOICE_FIRST;
  }

  if (index < NORMAL_TALK_COUNT) {
    normalTalk = normalTalks[index];
  }

  return normalTalk;
}

u32 GfDataBlade::getBladeRelativeID(u32 blade) {
  if (isRegularBlade(blade)) {
    return blade - BLADE_REGULAR_FIRST;
  }

  if (blade - BLADE_RARE_FIRST < BLADE_RARE_COUNT) {
    return blade - BLADE_RARE_FIRST + BLADE_RARE_INDEX;
  }

  if (isCommonBlade(blade)) {
    return blade - BLADE_REGULAR_FIRST;
  }

  return 0;
}

bool GfDataBlade::getNameWithMsgID(u8 *&bdat, u32 &textId, u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getNameWithMsgID(bdat, textId, *getSDataBlade(blade));
}

bool GfDataBlade::getNameWithMsgID(u8 *&bdat, u32 &textId, const SDataBlade &dataBlade) {
  if (dataBlade.id == 0) {
    return false;
  }

  if (textId == 0) {
    u32 nameId = dataBlade.name;
    if (nameId == 0) {
      nameId = dataBlade.nameListCategory;
    }
    textId = nameId;
    if (dataBlade.name != 0) {
      bdat = GfDataBdat::getFP(BDAT_BLADE_NAME);
    } else {
      bdat = GfDataBdat::getFP(BDAT_COMMON_BLADE_NAME);
    }
    return textId != 0;
  }

  if (dataBlade.id < GfBdatChrBl::get()->getChrBlEnd()) {
    bdat = GfDataBdat::getFP(BDAT_BLADE_NAME);
  } else {
    bdat = GfDataBdat::getFP(BDAT_COMMON_BLADE_NAME);
  }
  return true;
}

bool GfDataBlade::getName(u8 *&bdat, u32 &textId, u32 blade) {
  textId = 0;
  return getNameWithMsgID(bdat, textId, blade);
}

const char *GfDataBlade::getCommonBladeName(u32 nameList) {
  u32 textId = GfBdatBlade::get()->getNameListCategory(nameList);
  u8 *bdat = GfBdatMsg::getFpCommonBladeName();
  const char *name = textId == 0 ? nullptr : Bdat::getMSText(bdat, textId);
  if (name == nullptr) {
    name = "";
  }

  return name;
}

bool GfDataBlade::getCommonBladeName(u8 *&bdat, u32 &textId, u32 nameList) {
  textId = GfBdatBlade::get()->getNameListCategory(nameList);
  bdat = GfBdatMsg::getFpCommonBladeName();
  return textId != 0;
}

u16 GfDataBlade::getFavorite(u32 blade, FAVORITE favorite) {
  if (blade == 0) {
    return 0;
  }

  SDataBlade *dataBlade = getSDataBlade(blade);
  if (favorite >= FAVORITE_ITEM_0 && favorite <= FAVORITE_ITEM_1) {
    return dataBlade->favorites[favorite - FAVORITE_ITEM_0].item;
  }
  if (favorite >= FAVORITE_CATEGORY_0 && favorite <= FAVORITE_CATEGORY_1) {
    return dataBlade->favorites[favorite - FAVORITE_CATEGORY_0].category;
  }

  return 0;
}

u32 GfDataBlade::getAchievementQuestPrefix(u32 blade, u32 line, u32 level) {
  return getBladeRelativeID(blade) * ACHIEVEMENT_PER_BLADE + line * ACHIEVEMENT_LEVEL_COUNT + level;
}

bool GfDataBlade::isValid(u32 blade) { return blade - BLADE_REGULAR_FIRST < BLADE_COUNT; }

bool GfDataBlade::isActivateDriver(u32 blade) { return getSDataBlade(blade)->setDriver != 0; }

u16 GfDataBlade::getSetDriver(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->setDriver;
}

bool GfDataBlade::isDummyBlade(u32 blade) {
  return (blade == BLADE_DUMMY_REGULAR_FIRST || blade == BLADE_DUMMY_REGULAR_SECOND) || blade == BLADE_DUMMY_RARE;
}

bool GfDataBlade::isUnselect(u32 blade) { return getSDataBlade(blade)->unselect != 0; }

bool GfDataBlade::isActivateUnuse(u32 blade) {
  if (blade == 0) {
    return true;
  }

  return getSDataBlade(blade)->activate == BLADE_ACTIVATE_UNUSE;
}

bool GfDataBlade::isActivateMercenaryTeam(u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getSDataBlade(blade)->activate == BLADE_ACTIVATE_MERCENARY_TEAM;
}

bool GfDataBlade::isAttachedParty(u32 blade) { return getSDataBlade(blade)->attachedParty != 0; }

u32 GfDataBlade::getStartBlade() { return BLADE_REGULAR_FIRST; }

u32 GfDataBlade::getEndBlade() { return BLADE_REGULAR_END; }

u32 GfDataBlade::getStartRareBlade() { return BLADE_RARE_FIRST; }

u32 GfDataBlade::getStartCommonBlade() { return BLADE_COMMON_FIRST; }

u32 GfDataBlade::getEndCommonBlade() { return BLADE_COMMON_END; }

ActivateType GfDataBlade::getBladeActivateType(u32 blade) { return getBladeActivateType(*getSDataBlade(blade)); }

ActivateType GfDataBlade::getBladeActivateType(const SDataBlade &dataBlade) {
  if (dataBlade.activate == BLADE_ACTIVATE_MERCENARY_TEAM) {
    return ACTIVATE_TYPE_MERCENARY_TEAM;
  }

  ActivateType activateType = ACTIVATE_TYPE_UNUSE;
  if (dataBlade.activate == BLADE_ACTIVATE_DRIVER) {
    activateType = ACTIVATE_TYPE_RESERVER;
    if (dataBlade.setDriver != 0) {
      activateType = ACTIVATE_TYPE_PARTY;
    }
  }

  return activateType;
}

bool GfDataBlade::isBattleMember(u32 blade) {
  if (blade == 0) {
    return false;
  }

  u32 driver = getSDataBlade(blade)->setDriver;
  if (driver == 0) {
    return false;
  }

  if (GfDataDriver::getSDataDriver(driver)->activate != 1) {
    return false;
  }

  return static_cast<u32>(GfDataParty::getDriverPartyID(driver)) < 3;
}

void GfDataBlade::setKizunaringComplete(u32 blade) { getSDataBlade(blade)->kizunaringComplete = 1; }

bool GfDataBlade::isKizunaringComplete(u32 blade) { return getSDataBlade(blade)->kizunaringComplete == 1; }

bool GfDataBlade::getExtraParts(u32 blade, u32 index) { return getSDataBlade(blade)->extraParts[index] != 0; }

bool GfDataBlade::getExtraParts(const SDataBlade &dataBlade, u32 index) { return dataBlade.extraParts[index] != 0; }

u32 GfDataBlade::getLinkChNum(u32 blade) {
  u32 kizunaLinkSet = getSDataBlade(blade)->kizunaLinkSet;
  if (kizunaLinkSet == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getBTL_Bl_KizunaLinkSetLinkChNum(kizunaLinkSet);
}

void GfDataBlade::setUnselect(u32 blade, bool unselect) {
  SDataBlade *dataBlade = getSDataBlade(blade);
  dataBlade->unselect = unselect;
  GfEvent::callBladeUnselect(blade, unselect);
}

bool GfDataBlade::isReleasedRareBlade(u32 blade) { return getSDataBlade(blade)->attachedParty == 2; }

void GfDataBlade::resetAttachedParty(u32 blade) {
  SDataBlade *dataBlade = getSDataBlade(blade);
  dataBlade->attachedParty = 2;
  if (isRareBlade(blade)) {
    dataBlade->weapon = GfBdatChrBl::get()->getChrBlDefWeapon(blade);
  }

  GfEvent::callBladeActivate(blade, ACTIVATE_TYPE_UNUSE, ACTIVATE_TYPE_UNUSE);
}

u32 GfDataBlade::getEndRareBlade() { return GfBdatChrBl::get()->getChrBlEnd(); }

u32 GfDataBlade::getStartUiCommonBlade() { return BLADE_UI_COMMON_FIRST; }

u32 GfDataBlade::getEndUiCommonBlade() { return BLADE_UI_COMMON_END; }

u32 GfDataBlade::getStartActCommonBlade() { return BLADE_ACT_COMMON_FIRST; }

u32 GfDataBlade::getEndActCommonBlade() { return BLADE_ACT_COMMON_END; }

bool GfDataBlade::isSetBlade(u32 blade) { return getSDataBlade(blade)->setDriver != 0; }

u32 GfDataBlade::getBladeWeaponWithChip(u32 blade, u32 chip) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = blade == 0 ? 0 : getSDataBlade(blade)->weapon;
  u32 weaponRank = bdatItem->getPcWpnRank(weapon);
  u32 chipRank = bdatItem->getPcWpnChipRank(chip);
  return weaponRank < chipRank ? weapon - weaponRank + chipRank : 0;
}

u16 GfDataBlade::getBladeWeapon(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->weapon;
}

u32 GfDataBlade::getBladeWeaponByRank(u32 blade, u32 chip) {
  if (blade == 0) {
    return 0;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weaponTypeIndex = getSDataBlade(blade)->weaponType - 1;
  if (weaponTypeIndex < CHIP_CREATE_WEAPON_TYPE_COUNT) {
    return bdatItem->getPcWpnChipCreateWpn(chip, weaponTypeIndex);
  }

  return 0;
}

const char *GfDataBlade::getResourceNameModel(u32 blade) { return getSDataBlade(blade)->resourceNameModel; }

const char *GfDataBlade::getResourceNameMotion(u32 blade) { return getSDataBlade(blade)->resourceNameMotion; }

const char *GfDataBlade::getResourceNameAddMotion(u32 blade) { return getSDataBlade(blade)->resourceNameAddMotion; }

const char *GfDataBlade::getDebugName(u32 blade) {
  if (isCommonBlade(blade)) {
    SDataBlade *dataBlade = getSDataBlade(blade);
    if (dataBlade->customNameLength != 0) {
      return dataBlade->customName;
    }

    return getName(blade, 0);
  }

  return GfBdatChrBl::get()->getChrBlDebugName(blade);
}

u8 GfDataBlade::getRace(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->race;
}

u8 GfDataBlade::getGender(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->gender;
}

u8 GfDataBlade::getQuestRace(u32 blade) {
  if (blade == 0) {
    return QUEST_RACE_HUMAN;
  }

  return getSDataBlade(blade)->questRace;
}

bool GfDataBlade::isOperable(u32 blade) {
  if (isRareBlade(blade)) {
    return true;
  }

  return isRegularBlade(blade);
}

bool GfDataBlade::isAnimal(u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getSDataBlade(blade)->questRace == QUEST_RACE_ANIMAL;
}

bool GfDataBlade::isMale(u32 blade) {
  if (blade == 0) {
    return false;
  }

  SDataBlade *dataBlade = getSDataBlade(blade);
  if (dataBlade->gender != GENDER_MALE) {
    return false;
  }

  return dataBlade->questRace == QUEST_RACE_HUMAN;
}

bool GfDataBlade::isFemale(u32 blade) {
  if (blade == 0) {
    return false;
  }

  SDataBlade *dataBlade = getSDataBlade(blade);
  if (dataBlade->gender != GENDER_FEMALE) {
    return false;
  }

  return dataBlade->questRace == QUEST_RACE_HUMAN;
}

bool GfDataBlade::getNameWithFieldSkillForDebug(mm::mtl::FixStr<128> &, u32) { return false; }

u16 GfDataBlade::getKeyReleaseLevel(u32 blade) { return getSDataBlade(blade)->keyReleaseLevel; }

u32 GfDataBlade::getRealBladeId(u32 blade) { return blade == BLADE_REAL_ALIAS ? BLADE_REAL_ALIAS_TARGET : blade; }

u8 GfDataBlade::getAttribute(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getAttribute(blade);
  }

  return getSDataBlade(blade)->attribute;
}

const char *GfDataBlade::getDeathBlowWeaponName(u32 blade) {
  static const char *const deathBlowWeaponNames[] = {
      "", "_01", "_02", "_03", "_04", "_05", "_06", "_07", "_08", "_09", "_10", "_11", "_12", "_13", "_14", "_15", "_16", "_17", "_18", "_19", "_20",
  };

  u32 weaponType = blade == 0 ? 0 : getSDataBlade(blade)->weaponType;
  return deathBlowWeaponNames[weaponType];
}

u32 GfDataBlade::getBladePower(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getBladePower(*getSDataBlade(blade));
}

f32 GfDataBlade::getWpnScale(u32 blade) {
  if (blade == 0) {
    return 1.0f;
  }

  return getSDataBlade(blade)->wpnScale * SCALE_PERCENT;
}

f32 GfDataBlade::getScale(u32 blade) {
  if (blade == 0) {
    return 1.0f;
  }

  return getSDataBlade(blade)->scale * SCALE_PERCENT;
}

u16 GfDataBlade::getOffsetID(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->offsetID;
}

u16 GfDataBlade::getMountPoint(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->mountPoint;
}

u16 GfDataBlade::getMountObject(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->mountObject;
}

u8 GfDataBlade::getSize(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->size;
}

u16 GfDataBlade::getCollisionId(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->collisionId;
}

u32 GfDataBlade::getRoleByWpnType(u32 weaponType) {
  if (weaponType == 0) {
    return 1;
  }

  return GfBdatItem::get()->getPcWpnTypeRole(weaponType);
}

u32 GfDataBlade::getRole(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  SDataBlade *dataBlade = getSDataBlade(blade);
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getRole(blade);
  }

  return getRoleByWpnType(dataBlade->weaponType);
}

u8 GfDataBlade::getEquipOrbMax(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade)->equipOrbMax;
}

u16 GfDataBlade::getEquipOrb(u32 blade, u32 slot) {
  if (blade == 0) {
    return 0;
  }

  SDataBlade *dataBlade = getSDataBlade(blade);
  if (slot < getEquipOrbMax(blade)) {
    return dataBlade->equipOrbs[slot];
  }

  return 0;
}

bool GfDataBlade::getEquipOrb(mm::mtl::FixedArray<u16, 3> &equipOrbs, u32 blade) {
  if (blade == 0) {
    return false;
  }

  equipOrbs = getSDataBlade(blade)->equipOrbs;
  return true;
}

bool GfDataBlade::getEquipOrbHandle(mm::mtl::FixedArray<u32, 3> &equipOrbHandles, u32 blade) {
  if (blade == 0) {
    return false;
  }

  equipOrbHandles = getSDataBlade(blade)->equipOrbHandles;
  return true;
}

bool GfDataBlade::isEquipOrbFull(u32 blade) {
  if (blade == 0) {
    return false;
  }

  SDataBlade *dataBlade = getSDataBlade(blade);
  u32 equipOrbMax = getEquipOrbMax(blade);
  for (u32 slot = 0; slot < equipOrbMax; slot++) {
    if (dataBlade->equipOrbs[slot] == 0) {
      return false;
    }
  }

  return true;
}

bool GfDataBlade::getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getEquipOrbEnance(enhances, *getSDataBlade(blade));
}

u32 GfDataBlade::getBladeWeaponRank(u32 blade) {
  u32 weapon = getSDataBlade(blade)->weapon;
  if (weapon == 0) {
    return 0;
  }

  return GfBdatItem::get()->getPcWpnRank(weapon);
}

void GfDataBlade::setBladeWeapon(u32 blade, u32 weapon) {
  if (blade != 0) {
    getSDataBlade(blade)->weapon = weapon;
  }
}

void GfDataBlade::setAttributeForDebug(u32 blade, u8 attribute) {
  if (blade != 0) {
    getSDataBlade(blade)->attribute = attribute;
  }
}

SDataBladeArts *GfDataBlade::getArts(u32 blade, u32 slot) { return &getSDataBlade(blade)->arts[slot]; }

u16 GfDataBlade::getArtsEnhance(u32 blade, u32 slot) {
  if (blade - BLADE_HANA_JS < BLADE_HANA_COUNT) {
    return getSDataBlade(blade)->equipHana.arts[slot].enhance;
  }

  return 0;
}

SDataBladeSkill *GfDataBlade::getSkill(u32 blade, u32 slot) { return &getSDataBlade(blade)->skills[slot]; }

u32 GfDataBlade::getCreateEvent(u32 blade) { return getSDataBlade(blade)->createEvent; }

u16 GfDataBlade::getNormalTalk(u32 blade) { return getSDataBlade(blade)->normalTalk; }

u32 GfDataBlade::getActBlade2CommonBlade(u32 blade) {
  return blade - BLADE_ACT_FIRST >= BLADE_ACT_COUNT ? blade : blade + (BLADE_ACT_COMMON_FIRST - BLADE_ACT_FIRST);
}

bool GfDataBlade::isNeedAttributeResource(u32 blade) {
  return isCommonBlade(blade) || blade - BLADE_ACT_FIRST < BLADE_ACT_COUNT || blade - BLADE_HANA_JS < BLADE_HANA_COUNT;
}

u32 GfDataBlade::getTrustPoint(u32 blade) { return getSDataBlade(blade)->trustPoint; }

GfIdea GfDataBlade::getTrustRank(u32 blade) { return getSDataBlade(blade)->trustRank; }

void GfDataBlade::setTrustPoint(u32 blade, u32 trustPoint) {
  getSDataBlade(blade)->trustPoint = trustPoint;
  GfEvent::callDebugChangeIdea(DEBUG_CHANGE_IDEA_TRUST, blade, 0, 0);
}

void GfDataBlade::setTrustRank(u32 blade, GfIdea trustRank) {
  getSDataBlade(blade)->trustRank = trustRank;
  GfEvent::callDebugChangeIdea(DEBUG_CHANGE_IDEA_TRUST, blade, 0, 0);
}

u32 GfDataBlade::getParmor(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getParmor(blade);
  }

  return getSDataBlade(blade)->pArmor;
}

u32 GfDataBlade::getEarmor(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getEarmor(blade);
  }

  return getSDataBlade(blade)->eArmor;
}

u32 GfDataBlade::getHpMaxRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getHpMaxRev(blade);
  }

  return getSDataBlade(blade)->hpMaxRev;
}

u32 GfDataBlade::getStrengthRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getStrengthRev(blade);
  }

  return getSDataBlade(blade)->strengthRev;
}

u32 GfDataBlade::getPowerEtherRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getPowerEtherRev(blade);
  }

  return getSDataBlade(blade)->powerEtherRev;
}

u32 GfDataBlade::getDexRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getDexRev(blade);
  }

  return getSDataBlade(blade)->dexRev;
}

u32 GfDataBlade::getAgilityRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getAgilityRev(blade);
  }

  return getSDataBlade(blade)->agilityRev;
}

u32 GfDataBlade::getLuckRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getLuckRev(blade);
  }

  return getSDataBlade(blade)->luckRev;
}

u32 GfDataBlade::getBookedItemInfo(u32 blade) {
  GfBdatChrBl *bdatBlade = GfBdatChrBl::get();
  if (bdatBlade != nullptr && blade >= bdatBlade->getChrBlStart() && blade < bdatBlade->getChrBlEnd()) {
    return bdatBlade->getChrBlCreateInfo(blade);
  }

  return 0;
}

bool GfDataBlade::isUsedFavorite(u32 blade, FAVORITE favorite) {
  SDataBlade *dataBlade = getSDataBlade(blade);
  switch (favorite) {
  case FAVORITE_CATEGORY_0:
    return dataBlade->favorites[0].usedCategory != 0;
  case FAVORITE_CATEGORY_1:
    return dataBlade->favorites[1].usedCategory != 0;
  case FAVORITE_ITEM_0:
    return dataBlade->favorites[0].usedItem != 0;
  case FAVORITE_ITEM_1:
    return dataBlade->favorites[1].usedItem != 0;
  default:
    return false;
  }
}

u8 GfDataBlade::getFootStep(u32 blade) { return getSDataBlade(blade)->footStep; }

u8 GfDataBlade::getFootStepEffect(u32 blade) { return getSDataBlade(blade)->footStepEffect; }

bool GfDataBlade::isBladeID(u32 blade) { return blade - BLADE_REGULAR_FIRST < BLADE_COUNT; }

bool GfDataBlade::isReleaseLock(u32 blade) { return getSDataBlade(blade)->releaseLock != 0; }

bool GfDataBlade::getMercenaryName(u8 *&bdat, u32 &textId, u32 blade) {
  if (isCommonBlade(blade)) {
    return false;
  }

  textId = GfBdatChrBl::get()->getChrBlMerceName(blade);
  bdat = GfBdatMsg::getFpMerceName();
  return textId != 0;
}

u8 GfDataBlade::getPersonality(u32 blade) { return getSDataBlade(blade)->personality; }

u32 GfDataBlade::getVoiceID(u32 blade) {
  u32 personality = getSDataBlade(blade)->personality;
  if (personality == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
}

const char *GfDataBlade::getVoiceStr(u32 blade) { return getSDataBlade(blade)->voiceStr; }

const char *GfDataBlade::getSePack(u32 blade) { return getSDataBlade(blade)->sePack; }

u32 GfDataBlade::getBladeNum() {
  mm::mtl::FixedVector<u16, 422> blades;
  getListParty(blades);
  getListReserver(blades);
  return blades.size();
}

u32 GfDataBlade::getBladeNumForMale() {
  mm::mtl::FixedVector<u16, 422> blades;
  getListParty(blades);
  getListReserver(blades);

  u32 count = 0;
  if (blades.size() != 0) {
    u16 *it = blades.begin();
    do {
      if (getGender(*it) == GENDER_MALE) {
        count++;
      }
    } while (++it != blades.end());
  }

  return count;
}

u32 GfDataBlade::getBladeNumForFemale() {
  mm::mtl::FixedVector<u16, 422> blades;
  getListParty(blades);
  getListReserver(blades);

  u32 count = 0;
  if (blades.size() != 0) {
    u16 *it = blades.begin();
    do {
      if (getGender(*it) == GENDER_FEMALE) {
        count++;
      }
    } while (++it != blades.end());
  }

  return count;
}

u32 GfDataBlade::getBladeNumForAnimal() {
  mm::mtl::FixedVector<u16, 422> blades;
  getListParty(blades);
  getListReserver(blades);

  u32 count = 0;
  if (blades.size() != 0) {
    u16 *it = blades.begin();
    do {
      if (getQuestRace(*it) == QUEST_RACE_ANIMAL) {
        count++;
      }
    } while (++it != blades.end());
  }

  return count;
}

u32 GfDataBlade::getBladeNumForWeapon(u32 weaponType) {
  mm::mtl::FixedVector<u16, 422> blades;
  getListParty(blades);
  getListReserver(blades);

  u32 count = 0;
  if (blades.size() != 0) {
    u16 *it = blades.begin();
    do {
      if (getBladeWpnType(*it) == weaponType) {
        count++;
      }
    } while (++it != blades.end());
  }

  return count;
}

bool GfDataBlade::isNeedChangeWeapon(u32 blade) {
  return blade - BLADE_CHANGE_WEAPON_RANGE_FIRST < BLADE_CHANGE_WEAPON_RANGE_COUNT || blade == BLADE_CHANGE_WEAPON;
}

} // namespace gf
