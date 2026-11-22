#include "gf/data/gf_data_blade.h"

#include <math.h>
#include <string.h>

#include "bdat.h"
#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_blade_skill.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_field.h"
#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  BLADE_UNKNOWN_1001 = 1001,   // Inferred role: blade regular first; original name unknown.
  BLADE_UNKNOWN_1014 = 1014,   // Inferred role: blade regular end; original name unknown.
  BLADE_UNKNOWN_1014_2 = 1014, // Inferred role: blade rare first; original name unknown.
  BLADE_UNKNOWN_1197 = 1197,   // Inferred role: blade common first; original name unknown.
  BLADE_UNKNOWN_1397 = 1397,   // Inferred role: blade common end; original name unknown.
  BLADE_UNKNOWN_1397_2 = 1397, // Inferred role: blade ui common first; original name unknown.
  BLADE_UNKNOWN_1401 = 1401,   // Inferred role: blade ui common end; original name unknown.
  BLADE_UNKNOWN_1401_2 = 1401, // Inferred role: blade act common first; original name unknown.
  BLADE_UNKNOWN_1423 = 1423,   // Inferred role: blade act common end; original name unknown.
};

enum {
  BLADE_UNKNOWN_1039 = 1039, // Inferred role: blade change weapon; original name unknown.
};

enum {
  BLADE_DUMMY_UNKNOWN_1012 = 1012, // Inferred role: blade dummy regular first; original name unknown.
  BLADE_DUMMY_UNKNOWN_1013 = 1013, // Inferred role: blade dummy regular second; original name unknown.
  BLADE_DUMMY_UNKNOWN_1073 = 1073, // Inferred role: blade dummy rare; original name unknown.
};

constexpr u32 BLADE_UNKNOWN_13 = BLADE_UNKNOWN_1014 - BLADE_UNKNOWN_1001;         // Inferred role: blade regular count; original name unknown.
constexpr u32 BLADE_UNKNOWN_176 = 176;                                            // Inferred role: blade rare count; original name unknown.
constexpr u32 BLADE_UNKNOWN_20 = 20;                                              // Inferred role: blade rare index; original name unknown.
constexpr u32 BLADE_COMMON_UNKNOWN_226 = BLADE_UNKNOWN_1423 - BLADE_UNKNOWN_1197; // Inferred role: blade common count; original name unknown.
constexpr u32 BLADE_ACT_UNKNOWN_22 = BLADE_UNKNOWN_1423 - BLADE_UNKNOWN_1401_2;   // Inferred role: blade act count; original name unknown.
constexpr u32 BLADE_HANA_UNKNOWN_3 = BLADE_UNKNOWN_1007 - BLADE_UNKNOWN_1005 + 1; // Inferred role: blade hana count; original name unknown.
constexpr u32 BLADE_UNKNOWN_8 = 8;                                                // Inferred role: blade change weapon range count; original name unknown.
constexpr f32 unknown021 = 0.01f;                                                 // Inferred role: scale percent; original name unknown.
constexpr u32 CROWN_POINT_UNKNOWN_5 = 5;                                          // Inferred role: crown point max; original name unknown.
constexpr u32 CROWN_POINT_UNKNOWN_1 = 1;                                          // Inferred role: crown point min; original name unknown.
constexpr u32 TALK_UNKNOWN_32 = 32;                                               // Inferred role: normal talk count; original name unknown.
constexpr u32 PARTY_UNKNOWN_8 = 8;                                                // Inferred role: party members scanned for field skills; original name unknown.

namespace {

// Inferred role: lists the named blades of a condition; original name unknown.
template <typename Condition> bool unknown001(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades, Condition condition) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = GfDataBlade::getBladeID(i);
    if (blade != 0) {
      DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
      if (acc.isValid() && condition(blade)) {
        const char *name = acc.getName();
        if (name != nullptr && name[0] != '\0') {
          blades.push_back(blade);
        }
      }
    }
  }

  return !blades.empty();
}

// Defined in gf_data_driver.cpp.
void unknown006(u32 driver, u32 blade, bool isNew);

// Inferred role: activates the weapon type of a blade for a driver and releases its driver arts; original name unknown.
void unknown005(u32 driver, u32 blade) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  GfDataDriver::setActivateWeaponType(driver, acc.getWeaponType(-1, false));
  unknown006(driver, blade, false);
}

// Inferred role: resource name suffix of a weapon type; original name unknown.
const char *const unknown002[] = {
    "", "_01", "_02", "_03", "_04", "_05", "_06", "_07", "_08", "_09", "_10", "_11", "_12", "_13", "_14", "_15", "_16", "_17", "_18", "_19", "_20",
};

// Inferred role: last blade id before the blades named with a weapon type suffix; original name unknown.
constexpr u32 unknown990 = 0x439;
// Inferred role: blade id named without a weapon type suffix; original name unknown.
constexpr u32 unknown991 = 0x44f;

// Inferred role: resolves the blade whose menu texts a common blade uses; original name unknown.
// Ruling 5 (P3) and P2: the three menu name getters (0x710029b408, 0x710029b4bc, 0x710029b570) hold this loop: for a
// common blade it reads the se pack once before the loop (the call getDataGame at +0x30 of each function), then walks
// the 22 act blades from 1051 and, each round, reads the se pack of the SAME blade again (second getDataGame call in
// the loop, the loop variable is never read) and compares both with strcmp; the first round compares equal and returns
// the blade, a full miss returns 1051. The original expression cannot be checked.
u32 unknown004(u32 blade) {
  if (blade - BLADE_UNKNOWN_1197 < BLADE_COMMON_UNKNOWN_226) {
    const char *sePack = GfDataBlade::getSePack(blade);
    for (u32 act = BLADE_UNKNOWN_1051; act < BLADE_UNKNOWN_1051 + BLADE_ACT_UNKNOWN_22; act++) {
      if (strcmp(GfDataBlade::getSePack(blade), sePack) == 0) {
        return blade;
      }
    }
    return BLADE_UNKNOWN_1051;
  }

  return blade;
}

} // namespace

void GfDataBlade::initSaveData(SDataGame &dataGame) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      u32 index = getBladeRelativeID(blade);
      SDataBlade dataBlade;
      setupSDataBlade(dataBlade, blade, false);
      dataGame.unknown5a2c[index] = dataBlade;
      setupSDataBladeAchievement(getSDataBlade(blade), true);
    }
  }
}

void GfDataBlade::setCreator(u32 blade, u32 creator) {
  if (blade != 0) {
    getSDataBlade(blade).unknown02 = creator;
  }
}

u32 GfDataBlade::getCreator(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown02;
}

SDataBlade &GfDataBlade::getSDataBlade(u32 blade) {
  u32 index = getBladeRelativeID(blade);
  return GfDataManager::getDataGame()->unknown5a2c[index];
}

u32 GfDataBlade::getBladeID(u32 index) {
  if (index < BLADE_UNKNOWN_20) {
    u32 blade = index + BLADE_UNKNOWN_1001;
    if (blade >= BLADE_UNKNOWN_1014) {
      blade = 0;
    }

    return blade;
  }

  if (index < BLADE_UNKNOWN_20 + BLADE_UNKNOWN_176) {
    u32 blade = index - BLADE_UNKNOWN_20 + BLADE_UNKNOWN_1014_2;
    return blade < GfBdatChrBl::get()->getChrBlEnd() ? blade : 0;
  }

  return index < BLADE_UNKNOWN_422 ? index + BLADE_UNKNOWN_1001 : 0;
}

u32 GfDataBlade::getBladeWpnType(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).m_weaponType;
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
  return dataGame->unknown10ae7d != 0;
}

bool GfDataBlade::isEnableEngageRex(u32 blade) { return getSDataBlade(blade).unknown89e != 0; }

void GfDataBlade::setEnableEngageRex(u32 blade, bool enableEngageRex) {
  SDataBlade &dataBlade = getSDataBlade(blade);
  dataBlade.unknown89e = enableEngageRex;
}

u32 GfDataBlade::getBLD_NameList(u32 blade) {
  if (!isCommonBlade(blade)) {
    return 0;
  }

  u16 &nameListCategory = getSDataBlade(blade).unknown834;
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

bool GfDataBlade::isCommonBlade(u32 blade) { return blade - BLADE_UNKNOWN_1197 < BLADE_COMMON_UNKNOWN_226; }

u32 GfDataBlade::getCrownPoint(u32 blade) {
  static const u16 unknown022[] = {63, 64, 65, 66}; // Inferred role: crown point wildcards; original name unknown.

  if (isRegularBlade(blade)) {
    return CROWN_POINT_UNKNOWN_5;
  }

  if (isRareBlade(blade)) {
    return CROWN_POINT_UNKNOWN_5;
  }

  if (isCommonBlade(blade)) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    u32 kizunaringMax = getKizunaringMax(blade);
    for (u32 i = 0; i < sizeof(unknown022) / sizeof(unknown022[0]); i++) {
      if (kizunaringMax <= bdatBattle->getWildcardDatavalueU2(unknown022[i])) {
        return i + 1;
      }
    }
  }

  return CROWN_POINT_UNKNOWN_1;
}

bool GfDataBlade::isRegularBlade(u32 blade) { return blade - BLADE_UNKNOWN_1001 < BLADE_UNKNOWN_13; }

bool GfDataBlade::isRareBlade(u32 blade) {
  if (blade >= BLADE_UNKNOWN_1014_2) {
    return blade < GfBdatChrBl::get()->getChrBlEnd();
  }

  return false;
}

u32 GfDataBlade::getBornTime(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown08;
}

u32 GfDataBlade::getMenuCastName(u32 blade) {
  blade = unknown004(blade);
  return GfBdatChrBl::get()->getChrBlMnuCastName(blade);
}

u32 GfDataBlade::getMenuIlustName(u32 blade) {
  blade = unknown004(blade);
  return GfBdatChrBl::get()->getChrBlMnuIlustName(blade);
}

const char *GfDataBlade::getMenuVoiceName(u32 blade, u32 index) {
  blade = unknown004(blade);
  return GfBdatChrBl::get()->getChrBlMnuVoice(blade, index);
}

u8 GfDataBlade::getEyeRotControl(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).m_eyeRotControl;
}

void GfDataBlade::setHikariCurrent(bool hikariCurrent) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown10ae7d = hikariCurrent;
}

bool GfDataBlade::isHomuriNameHikari() {
  u32 flag = GfGameFlag::getLocal(1, FLAG_UNKNOWN_35323);
  return flag != 0;
}

void GfDataBlade::setHomuriNameHikari(bool homuriNameHikari) { GfGameFlag::setLocal(1, FLAG_UNKNOWN_35323, homuriNameHikari); }

u16 GfDataBlade::makeNormalTalkByPersonality(u32 personality) {
  static const u16 unknown023[TALK_UNKNOWN_32] = {
      // Inferred role: normal talks; original name unknown.
      41525, 41525, 41526, 41527, 41528, 41528, 41529, 41529, 41530, 41530, 41531, 41531, 41532, 41532, 41533, 41533,
      41534, 41534, 41535, 41535, 41536, 41536, 41537, 41537, 41538, 41538, 41539, 41539, 41540, 41540, 41541, 41542,
  };

  u32 voice = GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
  u16 normalTalk = 0;
  u32 index = 0;
  if (voice != 0) {
    index = voice - VOICE_UNKNOWN_61;
  }

  if (index < TALK_UNKNOWN_32) {
    normalTalk = unknown023[index];
  }

  return normalTalk;
}

u32 GfDataBlade::getBladeRelativeID(u32 blade) {
  if (isRegularBlade(blade)) {
    return blade - BLADE_UNKNOWN_1001;
  }

  if (blade - BLADE_UNKNOWN_1014_2 < BLADE_UNKNOWN_176) {
    return blade - BLADE_UNKNOWN_1014_2 + BLADE_UNKNOWN_20;
  }

  if (isCommonBlade(blade)) {
    return blade - BLADE_UNKNOWN_1001;
  }

  return 0;
}

bool GfDataBlade::getNameWithMsgID(u8 *&bdat, u32 &textId, u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getNameWithMsgID(bdat, textId, getSDataBlade(blade));
}

bool GfDataBlade::getNameWithMsgID(u8 *&bdat, u32 &textId, const SDataBlade &dataBlade) {
  if (dataBlade.unknown06 == 0) {
    return false;
  }

  if (textId == 0) {
    u32 nameId = dataBlade.unknown832;
    if (nameId == 0) {
      nameId = dataBlade.unknown834;
    }
    textId = nameId;
    if (dataBlade.unknown832 != 0) {
      bdat = GfDataBdat::getFP(BDAT_CHR_BL_MS);
    } else {
      bdat = GfDataBdat::getFP(BDAT_BLD_BLADENAME);
    }
    return textId != 0;
  }

  if (dataBlade.unknown06 < GfBdatChrBl::get()->getChrBlEnd()) {
    bdat = GfDataBdat::getFP(BDAT_CHR_BL_MS);
  } else {
    bdat = GfDataBdat::getFP(BDAT_BLD_BLADENAME);
  }
  return true;
}

int GfDataBlade::getDriverSetID(u32 blade) {
  if (blade != 0) {
    u32 driver = getSDataBlade(blade).m_driverBySetBlade;
    if (driver != 0) {
      return GfDataDriver::getSetIdByBlade(driver, blade);
    }
  }

  return -1;
}

bool GfDataBlade::getName(u8 *&bdat, u32 &textId, u32 blade) {
  textId = 0;
  return getNameWithMsgID(bdat, textId, blade);
}

u32 GfDataBlade::addRareBlade(const SDataBlade &dataBlade) {
  if (!isActivateUnuse(dataBlade.unknown06)) {
    return 0;
  }

  getSDataBlade(dataBlade.unknown06) = dataBlade;
  setupSDataBladeAchievement(getSDataBlade(dataBlade.unknown06), false);
  setActivateReserver(dataBlade.unknown06);
  unknown005(getCreator(dataBlade.unknown06), dataBlade.unknown06);
  return dataBlade.unknown06;
}

bool GfDataBlade::getCommonBladeName(const char *model) {
  if (model == nullptr || __builtin_strlen(model) < 6) {
    return false;
  }
  return __builtin_strncmp(model, "bl/bl2", 6) == 0;
}

u32 GfDataBlade::getEnableCountForCreateBlade() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  int max = GfDataMercenaries::getReserverMax();
  u32 count = 0;
  for (int i = 0; i < max; i++) {
    if (dataGame->m_sDataMercenaries.unknowne0[i] == 0) {
      count++;
    }
  }
  return count;
}

u32 GfDataBlade::addCommonBlade(const SDataBlade &dataBlade) {
  for (u32 blade = BLADE_UNKNOWN_1197; blade < BLADE_UNKNOWN_1397; blade++) {
    if (isActivateUnuse(blade)) {
      getSDataBlade(blade) = dataBlade;
      getSDataBlade(blade).unknown06 = blade;
      setupSDataBladeAchievement(getSDataBlade(blade), false);
      setActivateReserver(blade);
      unknown005(getCreator(blade), blade);
      return blade;
    }
  }

  return 0;
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

u32 GfDataBlade::getFavorite(u32 blade, FAVORITE favorite) {
  if (blade == 0) {
    return 0;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  if (favorite >= FAVORITE_UNKNOWN_2 && favorite <= FAVORITE_UNKNOWN_3) {
    return dataBlade.unknown666[favorite - FAVORITE_UNKNOWN_2].unknown02;
  }
  if (favorite >= FAVORITE_UNKNOWN_0 && favorite <= FAVORITE_UNKNOWN_1) {
    return dataBlade.unknown666[favorite - FAVORITE_UNKNOWN_0].unknown00;
  }

  return 0;
}

bool GfDataBlade::isFavoriteItem(u32 blade, u32 item) {
  if (item == 0) {
    return false;
  }

  for (u32 favorite = FAVORITE_UNKNOWN_2; favorite <= FAVORITE_UNKNOWN_3; favorite++) {
    if (getFavorite(blade, static_cast<FAVORITE>(favorite)) == item) {
      return true;
    }
  }

  return false;
}

// The game (0x71002a5f64) reads the pouch item again for each use (reference to the pouch, item not kept in a local) and inlines the driver's isFavoriteItem and isFavoriteCategory, while the
// blade's two functions stay calls (0x710029bee4, 0x710029be10: isFavoriteCategory is not matched yet and stays declared only). `bdatItem` places the item table load before the loop, as the game
// does (0x71002a5ff4; the call in the loop gives 128 instructions without it). The driver state is set to 0, then to 2 or 1: the game has no separate zero store (its state register holds the item,
// known to be 0, on the path where the item is 0); this form gives 129 instructions, a ternary 130, an if/else chain with a final else 143 (a local holding the state also gives 129, but adds a
// variable).
bool GfDataBlade::getPouchEnhanceFavorite(mm::mtl::FixedVector<EnhanceFavorite, 64> &favorites, u32 blade) {
  if (blade != 0) {
    u32 driver = getSDataBlade(blade).m_driverBySetBlade;
    if (driver != 0) {
      GfBdatItem *bdatItem = GfBdatItem::get();
      for (u32 slot = 0; slot < POUCH_UNKNOWN_3; slot++) {
        SDataPouch &pouch = GfDataDriver::getSDataDriver(driver).m_pouchData[slot];
        if (pouch.unknown04 != 0) {
          u32 enhance = bdatItem->getFavoriteType(pouch.unknown04);
          if (enhance != 0) {
            EnhanceFavorite favorite;
            favorite.unknown00 = 1.0f;
            favorite.unknown04 = enhance;
            favorite.unknown06 = 0;
            if (GfDataDriver::isFavoriteItem(driver, pouch.unknown04)) {
              favorite.unknown06 = 2;
            } else if (GfDataDriver::isFavoriteCategory(driver, pouch.unknown04)) {
              favorite.unknown06 = 1;
            }
            favorite.unknown08 = isFavoriteItem(blade, pouch.unknown04) ? 2 : isFavoriteCategory(blade, pouch.unknown04);
            favorites.push_back(favorite);
          }
        }
      }

      return !favorites.empty();
    }
  }

  return false;
}

u32 GfDataBlade::getAchievementQuestPrefix(u32 blade, u32 line, u32 level) { return getBladeRelativeID(blade) * ACHIEVEMENT_UNKNOWN_50 + line * ACHIEVEMENT_UNKNOWN_5 + level; }

// Inferred role: gets the data of a blade and the type and index of an achievement line in it; original name unknown. Written out in each function the three statements give the same
// code; they are shared because ten functions below start with them.
static bool unknown003(SDataBlade *&dataBlade, ACHIEVEMENT_TYPE &type, u32 &index, u32 blade, u32 line) {
  dataBlade = &GfDataBlade::getSDataBlade(blade);
  return GfDataAchievement::getAchievementType(type, index, line);
}

SDataBladeAchievement *GfDataBlade::getAchievInfo(u32 blade, u32 line) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (unknown003(dataBlade, type, index, blade, line)) {
    switch (type) {
    case ACHIEVEMENT_TYPE_UNKNOWN_3:
      return &dataBlade->m_achievInfo;
    case ACHIEVEMENT_TYPE_UNKNOWN_2:
      return &dataBlade->unknown424[index];
    case ACHIEVEMENT_TYPE_UNKNOWN_1:
      return &dataBlade->unknown274[index];
    default:
      return &dataBlade->unknownc4[index];
    }
  }
  return &dataBlade->unknownc4[0];
}

u32 GfDataBlade::getKizunaringMax(u32 blade) {
  u32 count = 0;
  for (u32 line = 0; line < ACHIEVEMENT_UNKNOWN_10; line++) {
    SDataBladeAchievement *achievInfo = getAchievInfo(blade, line);
    if (achievInfo->unknown00 != 0) {
      for (u32 level = 0; level < ACHIEVEMENT_UNKNOWN_5; level++) {
        if (achievInfo->m_achievQuest[level].unknown18 != 0) {
          count++;
        }
      }
    }
  }
  return count;
}

u32 GfDataBlade::getKizunaringCompleteNum(u32 blade) {
  u32 count = 0;
  for (u32 line = 0; line < ACHIEVEMENT_UNKNOWN_10; line++) {
    SDataBladeAchievement *achievInfo = getAchievInfo(blade, line);
    if (achievInfo->unknown00 != 0) {
      for (u32 level = 0; level < ACHIEVEMENT_UNKNOWN_5; level++) {
        AchievQuest &achievQuest = achievInfo->m_achievQuest[level];
        if (achievQuest.unknown18 != 0) {
          count += achievQuest.unknown0c & 1;
        }
      }
    }
  }
  return count;
}

bool GfDataBlade::getTaskSkillMessage(u8 *&bdat, u32 &textId, u32 blade, u32 line) {
  textId = 0;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (GfDataAchievement::getAchievementType(type, index, line)) {
    SDataBlade &dataBlade = getSDataBlade(blade);
    switch (type) {
    case ACHIEVEMENT_TYPE_UNKNOWN_3:
      textId = 1;
      bdat = GfBdatMsg::getFpAchievement();
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_2:
      GfDataFieldSkill::getName(bdat, textId, dataBlade.unknownae[index].m_fieldSkill);
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_1:
      GfDataBladeSkill::getName(bdat, textId, dataBlade.unknown9c[index].unknown00);
      break;
    default:
      GfDataBladeArts::getName(bdat, textId, dataBlade.unknown3c[index].unknown00);
      break;
    }
  }
  return textId != 0;
}

// The `achievInfo` local places the call before the `level - 1` index: clang evaluates the index of a subscript first, the game computes it after the inlined getAchievInfo.
bool GfDataBlade::getTaskTitleMessage(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level) {
  SDataBladeAchievement *achievInfo = getAchievInfo(blade, line);
  AchievQuest &achievQuest = achievInfo->m_achievQuest[level - 1];
  if (achievQuest.m_questID.empty()) {
    return false;
  }
  QuestID quest = GfDataQuest::getListNextQuestA(achievQuest.m_questID);
  if (quest.empty() || GfDataQuest::getListPurposeID(quest) == 0) {
    return false;
  }
  textId = QuestListAcc::get()->getTaskTaskLog(GfDataQuest::getListPurposeID(quest), 0);
  bdat = GfBdatMsg::getFpQuest(quest);
  return textId != 0;
}

// Same `achievInfo` local as getTaskTitleMessage (0x71002a2f98: the call comes before the `level - 1` index).
bool GfDataBlade::getTaskResultMessage(u8 *&bdat, u32 &textId, u32 blade, u32 line, u32 level) {
  SDataBladeAchievement *achievInfo = getAchievInfo(blade, line);
  AchievQuest &achievQuest = achievInfo->m_achievQuest[level - 1];
  if (achievQuest.m_questID.empty()) {
    return false;
  }
  textId = QuestListAcc::get()->getListResultA(achievQuest.m_questID);
  bdat = GfBdatMsg::getFpQuest(achievQuest.m_questID);
  return textId != 0;
}

// The functions by achievement line (getAchievInfo, getSkillLine*, setSkillLevel, getTask*Message, setAchievReleaseLevel, getAchievementID, the getKizunaring* loops) inline
// GfDataAchievement::getAchievementType: the game tests `line - 3` in the entry block (subs/b.hs), which only that helper gives (a plain if chain on `line` gives cmp #2/b.hi),
// and a line past the key line fails the helper (getAchievInfo then returns the first arts entry, getSkillLineLevel returns 0).
// Case order (ruling 4): the source order of the switch cases fixes the block layout, and only one order matches the eleven functions: the key case first (`default` in the nine
// functions where the key is the default, `case ACHIEVEMENT_TYPE_UNKNOWN_3` in getAchievInfo and getTaskSkillMessage), then field skill, skill, arts. Measured on the
// branch: with `default` first and the others ascending (0, 1, 2) only getSkillLineLevel, getSkillLineLevelMax, getSkillLineId and getAchievReleaseLevel match, getAchievementID,
// getSkillLineName (first difference at +0xec) and the three setters do not (62 against 61 instructions; first difference at +0x48 and +0x4c); with `default` last and ascending cases
// getSkillLineLevel and getAchievReleaseLevel also fail (53 against 51); with the key case after the others getAchievInfo fails (first difference at +0x78).
u32 GfDataBlade::getSkillLineLevel(u32 blade, u32 line) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  u32 level = 0;
  if (unknown003(dataBlade, type, index, blade, line)) {
    switch (type) {
    default:
      level = dataBlade->unknown664;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_2:
      level = dataBlade->unknownae[index].m_fieldSkillLevel;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_1:
      level = dataBlade->unknown9c[index].unknown03;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_0:
      level = dataBlade->unknown3c[index].m_bladeArtsLevel;
      break;
    }
  }
  return level;
}

u32 GfDataBlade::getSkillLineLevelMax(u32 blade, u32 line) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  u32 levelMax = 0;
  if (unknown003(dataBlade, type, index, blade, line)) {
    switch (type) {
    default:
      levelMax = ACHIEVEMENT_UNKNOWN_5;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_2:
      levelMax = dataBlade->unknownae[index].unknown04;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_1:
      levelMax = dataBlade->unknown9c[index].unknown04;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_0:
      levelMax = dataBlade->unknown3c[index].unknown08;
      break;
    }
  }
  return levelMax;
}

const char *GfDataBlade::getSkillLineName(u32 blade, u32 line) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (!unknown003(dataBlade, type, index, blade, line)) {
    return "";
  }
  const char *name;
  switch (type) {
  default:
    return "";
  case ACHIEVEMENT_TYPE_UNKNOWN_2:
    name = GfDataFieldSkill::getName(dataBlade->unknownae[index].m_fieldSkill);
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_1:
    name = GfDataBladeSkill::getName(dataBlade->unknown9c[index].unknown00);
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_0:
    name = GfDataBladeArts::getName(dataBlade->unknown3c[index].unknown00);
    break;
  }
  return name == nullptr ? "" : name;
}

u32 GfDataBlade::getSkillLineId(u32 blade, u32 line) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (!unknown003(dataBlade, type, index, blade, line)) {
    return 0;
  }
  u32 skill = 0;
  switch (type) {
  default:
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_2:
    skill = dataBlade->unknownae[index].m_fieldSkill;
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_1:
    skill = dataBlade->unknown9c[index].unknown00;
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_0:
    skill = dataBlade->unknown3c[index].unknown00;
    break;
  }
  return skill;
}

u32 GfDataBlade::getAchievReleaseLevel(u32 blade, u32 line) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  u32 releaseLevel = 0;
  if (unknown003(dataBlade, type, index, blade, line)) {
    switch (type) {
    default:
      releaseLevel = dataBlade->unknown664;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_2:
      releaseLevel = dataBlade->unknownae[index].unknown02;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_1:
      releaseLevel = dataBlade->unknown9c[index].unknown02;
      break;
    case ACHIEVEMENT_TYPE_UNKNOWN_0:
      releaseLevel = dataBlade->unknown3c[index].unknown06;
      break;
    }
  }
  return releaseLevel;
}

bool GfDataBlade::setAchievReleaseLevel(u32 blade, u32 line, u32 level) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  u32 releaseLevel;
  if (!unknown003(dataBlade, type, index, blade, line)) {
    return false;
  }
  switch (type) {
  default:
    releaseLevel = dataBlade->unknown664;
    if (releaseLevel < level) {
      dataBlade->unknown664 = level;
    }
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_2: {
    unknown110 &skill = dataBlade->unknownae[index];
    releaseLevel = skill.unknown02;
    if (level > releaseLevel) {
      skill.unknown02 = level;
      if (skill.unknown04 > skill.m_fieldSkillLevel) {
        skill.m_fieldSkillLevel++;
      }
    }
    break;
  }
  case ACHIEVEMENT_TYPE_UNKNOWN_1: {
    unknown109 &skill = dataBlade->unknown9c[index];
    releaseLevel = skill.unknown02;
    if (level > releaseLevel) {
      skill.unknown02 = level;
      if (skill.unknown04 > skill.unknown03) {
        skill.unknown03++;
      }
    }
    break;
  }
  case ACHIEVEMENT_TYPE_UNKNOWN_0: {
    unknown108 &arts = dataBlade->unknown3c[index];
    releaseLevel = arts.unknown06;
    if (level > releaseLevel) {
      arts.unknown06 = level;
      if (arts.unknown08 > arts.m_bladeArtsLevel) {
        arts.m_bladeArtsLevel++;
      }
    }
    break;
  }
  }
  return releaseLevel < level;
}

void GfDataBlade::setSkillLineLevel(u32 blade, u32 line, u32 level) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (!unknown003(dataBlade, type, index, blade, line)) {
    return;
  }
  switch (type) {
  default:
    dataBlade->unknown664 = level;
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_2: {
    unknown110 &skill = dataBlade->unknownae[index];
    skill.m_fieldSkillLevel = level;
    if (level == 0) {
      skill.unknown02 = 0;
    }
    break;
  }
  case ACHIEVEMENT_TYPE_UNKNOWN_1: {
    unknown109 &skill = dataBlade->unknown9c[index];
    skill.unknown03 = level;
    if (level == 0) {
      skill.unknown02 = 0;
    }
    break;
  }
  case ACHIEVEMENT_TYPE_UNKNOWN_0: {
    unknown108 &arts = dataBlade->unknown3c[index];
    arts.m_bladeArtsLevel = level;
    if (level == 0) {
      arts.unknown06 = 0;
    }
    break;
  }
  }
}

void GfDataBlade::setSkillLevel(u32 blade, u32 line, u32 level) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (!unknown003(dataBlade, type, index, blade, line)) {
    return;
  }
  switch (type) {
  default:
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_2: {
    unknown110 &skill = dataBlade->unknownae[index];
    skill.m_fieldSkillLevel = level;
    if (level == 0) {
      skill.unknown02 = 0;
    }
    break;
  }
  case ACHIEVEMENT_TYPE_UNKNOWN_1: {
    unknown109 &skill = dataBlade->unknown9c[index];
    skill.unknown03 = level;
    if (level == 0) {
      skill.unknown02 = 0;
    }
    break;
  }
  case ACHIEVEMENT_TYPE_UNKNOWN_0: {
    unknown108 &arts = dataBlade->unknown3c[index];
    arts.m_bladeArtsLevel = level;
    if (level == 0) {
      arts.unknown06 = 0;
    }
    break;
  }
  }
}

u32 GfDataBlade::getAchievementID(u32 blade, u32 line, u32 level) {
  SDataBlade *dataBlade;
  ACHIEVEMENT_TYPE type;
  u32 index;
  if (!unknown003(dataBlade, type, index, blade, line)) {
    return 0;
  }
  const u16 *achievementSet;
  switch (type) {
  default:
    achievementSet = &dataBlade->m_achievInfo.unknown00;
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_2:
    achievementSet = &dataBlade->unknownae[index].m_fieldSkill;
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_1:
    achievementSet = &dataBlade->unknown9c[index].unknown00;
    break;
  case ACHIEVEMENT_TYPE_UNKNOWN_0:
    achievementSet = &dataBlade->unknown3c[index].unknown00;
    break;
  }
  u32 achievement = *achievementSet;
  if (achievement == 0) {
    return 0;
  }
  return QuestListAcc::get()->getFLD_AchievementSetAchievementID(achievement, level - 1);
}

void GfDataBlade::setupAchievQuest(AchievQuest &achievQuest) {
  achievQuest.unknown04 = 0;
  achievQuest.unknown08 = 0;
  achievQuest.unknown0e = 0;
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 purpose = GfDataQuest::getListPurposeID(GfDataQuest::getListNextQuestA(achievQuest.m_questID));
  if (purpose == 0) {
    return;
  }

  u32 taskType = questListAcc->getTaskTaskType(purpose, 0);
  u32 taskId = questListAcc->getTaskTaskID(purpose, 0);
  if (taskType == 0) {
    return;
  }

  achievQuest.unknown10 = taskType;
  u32 count;
  switch (taskType) {
  case TASK_TYPE_UNKNOWN_1:
    count = questListAcc->getBattleCount(taskId);
    break;
  case TASK_TYPE_UNKNOWN_3:
    count = questListAcc->getCollectCount(taskId);
    break;
  case TASK_TYPE_UNKNOWN_4:
    count = questListAcc->getUseItemNumber(taskId);
    break;
  case TASK_TYPE_UNKNOWN_11:
    count = questListAcc->getFieldSkillCountCount(taskId);
    break;
  case TASK_TYPE_UNKNOWN_12:
    achievQuest.unknown08 = questListAcc->getAchievementCount(taskId);
    achievQuest.unknown0e = questListAcc->getAchievementStatsID(taskId);
    return;
  default:
    return;
  }

  achievQuest.unknown08 = count;
}

void SDataIdea::setLevel(u32 idea, int level) {
  unknown00[idea].unknown04 = level;
  unknown00[idea].unknown00 = level >= 0 && static_cast<u32>(level) <= IDEA_LEVEL_UNKNOWN_10 ? GfBdatBlade::get()->getBLD_IdeaNeedPoint(level) : 0;
}

bool GfDataBlade::isValid(u32 blade) { return blade - BLADE_UNKNOWN_1001 < BLADE_UNKNOWN_422; }

bool GfDataBlade::isActivateDriver(u32 blade) { return getSDataBlade(blade).m_driverBySetBlade != 0; }

u32 GfDataBlade::getSetDriver(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).m_driverBySetBlade;
}

bool GfDataBlade::isDummyBlade(u32 blade) { return (blade == BLADE_DUMMY_UNKNOWN_1012 || blade == BLADE_DUMMY_UNKNOWN_1013) || blade == BLADE_DUMMY_UNKNOWN_1073; }

bool GfDataBlade::setActivateMercenaryTeam(u32 blade) {
  getSDataBlade(blade).m_dataType = 2;
  return true;
}

bool GfDataBlade::isUnselect(u32 blade) { return getSDataBlade(blade).unknown8a0 != 0; }

bool GfDataBlade::isActivateUnuse(u32 blade) {
  if (blade == 0) {
    return true;
  }

  return getSDataBlade(blade).m_dataType == BLADE_ACTIVATE_UNKNOWN_0;
}

bool GfDataBlade::isActivateMercenaryTeam(u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getSDataBlade(blade).m_dataType == BLADE_ACTIVATE_UNKNOWN_2;
}

bool GfDataBlade::isAttachedParty(u32 blade) { return getSDataBlade(blade).unknown89f != 0; }

u32 GfDataBlade::getStartBlade() { return BLADE_UNKNOWN_1001; }

u32 GfDataBlade::getEndBlade() { return BLADE_UNKNOWN_1014; }

u32 GfDataBlade::getStartRareBlade() { return BLADE_UNKNOWN_1014_2; }

u32 GfDataBlade::getStartCommonBlade() { return BLADE_UNKNOWN_1197; }

u32 GfDataBlade::getEndCommonBlade() { return BLADE_UNKNOWN_1397; }

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Its user unknown007 (0x710029f01c, 88 instructions) matches only with the search loop and the erase in a helper that returns after the erase. Written inline in
// unknown007 the loop gives 94 instructions with break (it hoists the line constant 345 where the game hoists the file string), the search followed by a plain
// erase(it) gives 93 (it hoists the message, the line and the file string, so the group base and the end of the outer loop are spilled) and the erase behind an
// `it != blades.end()` test gives 92 (the test stays after the loop).
static void eraseFirst(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades, u16 value) {
  for (u16 *it = blades.begin(); it != blades.end(); ++it) {
    if (*it == value) {
      blades.erase(it);
      return;
    }
  }
}

// Inferred role: removes from the list the other blades of a group when the list holds one of them; no symbol (0x710029f01c); original name unknown.
static void unknown007(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades, const mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &group) {
  for (u16 blade : group) {
    if (mm::mtl::find(blades.begin(), blades.end(), blade) != blades.end()) {
      for (u16 other : group) {
        if (other == blade) {
          continue;
        }
        eraseFirst(blades, other);
      }
    }
  }
}

// Inferred helper with two users; original name unknown. It pushes a group of three blades and removes the duplicates among them from the list (removeSameBlade,
// 0x710029ef44). The three groups written out with repeated pushes give the same 54 instructions, so the helper replaces the repeat (ruling 8); a loop over an
// initializer_list of each group gives 30 instructions and a loop over a table of groups 163, hence the three blades as arguments.
static void unknown008(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades, mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &group, u16 first, u16 second, u16 third) {
  group.push_back(first);
  group.push_back(second);
  group.push_back(third);
  unknown007(blades, group);
}

void GfDataBlade::removeSameBlade(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> group;
  unknown008(blades, group, BLADE_HOMURA, BLADE_HIKARI, BLADE_HOMURI);
  group.clear();
  unknown008(blades, group, BLADE_UNKNOWN_1005, BLADE_UNKNOWN_1006, BLADE_UNKNOWN_1007);
  group.clear();
  group.push_back(BLADE_UNKNOWN_1022);
  group.push_back(BLADE_UNKNOWN_1050);
  unknown007(blades, group);
}

ActivateType GfDataBlade::getBladeActivateType(u32 blade) { return getBladeActivateType(getSDataBlade(blade)); }

ActivateType GfDataBlade::getBladeActivateType(const SDataBlade &dataBlade) {
  ActivateType activateType = ACTIVATE_TYPE_UNKNOWN_0;
  switch (dataBlade.m_dataType) {
  case BLADE_ACTIVATE_UNKNOWN_1:
    activateType = ACTIVATE_TYPE_UNKNOWN_1;
    if (dataBlade.m_driverBySetBlade != 0) {
      activateType = ACTIVATE_TYPE_UNKNOWN_2;
    }
    break;
  case BLADE_ACTIVATE_UNKNOWN_2:
    activateType = ACTIVATE_TYPE_UNKNOWN_3;
    break;
  default:
    break;
  }

  return activateType;
}

void GfDataBlade::setKizunaringComplete(u32 blade) { getSDataBlade(blade).m_kizunaringComplete = 1; }

bool GfDataBlade::isKizunaringComplete(u32 blade) { return getSDataBlade(blade).m_kizunaringComplete == 1; }

bool GfDataBlade::getExtraParts(u32 blade, u32 index) { return getSDataBlade(blade).unknownc0[index] != 0; }

bool GfDataBlade::getExtraParts(const SDataBlade &dataBlade, u32 index) { return dataBlade.unknownc0[index] != 0; }

u32 GfDataBlade::getLinkChNum(u32 blade) {
  u32 kizunaLinkSet = getSDataBlade(blade).unknown84a;
  if (kizunaLinkSet == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getBTL_Bl_KizunaLinkSetLinkChNum(kizunaLinkSet);
}

void GfDataBlade::setUnselect(u32 blade, bool unselect) {
  SDataBlade &dataBlade = getSDataBlade(blade);
  dataBlade.unknown8a0 = unselect;
  GfEvent::callBladeUnselect(blade, unselect);
}

bool GfDataBlade::isReleasedRareBlade(u32 blade) { return getSDataBlade(blade).unknown89f == 2; }

void GfDataBlade::resetAttachedParty(u32 blade) {
  SDataBlade &dataBlade = getSDataBlade(blade);
  dataBlade.unknown89f = 2;
  if (isRareBlade(blade)) {
    dataBlade.m_equipWeapon = GfBdatChrBl::get()->getChrBlDefWeapon(blade);
  }

  GfEvent::callBladeActivate(blade, ACTIVATE_TYPE_UNKNOWN_0, ACTIVATE_TYPE_UNKNOWN_0);
}

u32 GfDataBlade::getEndRareBlade() { return GfBdatChrBl::get()->getChrBlEnd(); }

u32 GfDataBlade::addCommonBladeWithPos(const SDataBlade &dataBlade, u32 pos) {
  u32 blade = BLADE_UNKNOWN_1197 + pos;
  getSDataBlade(blade) = dataBlade;
  getSDataBlade(blade).unknown06 = blade;
  setActivateReserver(blade);
  return blade;
}

u32 GfDataBlade::getStartUiCommonBlade() { return BLADE_UNKNOWN_1397_2; }

u32 GfDataBlade::getEndUiCommonBlade() { return BLADE_UNKNOWN_1401; }

u32 GfDataBlade::getStartActCommonBlade() { return BLADE_UNKNOWN_1401_2; }

u32 GfDataBlade::getEndActCommonBlade() { return BLADE_UNKNOWN_1423; }

bool GfDataBlade::isSetBlade(u32 blade) { return getSDataBlade(blade).m_driverBySetBlade != 0; }

u32 GfDataBlade::getBladeWeaponWithChip(u32 blade, u32 chip) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = blade == 0 ? 0 : getSDataBlade(blade).m_equipWeapon;
  u32 weaponRank = bdatItem->getPcWpnRank(weapon);
  u32 chipRank = bdatItem->getPcWpnChipRank(chip);
  return weaponRank < chipRank ? weapon - weaponRank + chipRank : 0;
}

u32 GfDataBlade::getBladeWeapon(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).m_equipWeapon;
}

u32 GfDataBlade::getBladeWeaponByRank(u32 blade, u32 chip) {
  if (blade == 0) {
    return 0;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weaponTypeIndex = getSDataBlade(blade).m_weaponType - 1;
  if (weaponTypeIndex < CHIP_CREATE_WEAPON_TYPE_UNKNOWN_16) {
    return bdatItem->getPcWpnChipCreateWpn(chip, weaponTypeIndex);
  }

  return 0;
}

const char *GfDataBlade::getResourceNameModel(u32 blade) { return getSDataBlade(blade).unknown70c.c_str(); }

const char *GfDataBlade::getResourceNameMotion(u32 blade) { return getSDataBlade(blade).unknown734.c_str(); }

const char *GfDataBlade::getResourceNameAddMotion(u32 blade) { return getSDataBlade(blade).unknown75c.c_str(); }

bool GfDataBlade::getBladeAddAnim(mm::mtl::FixStr<128> &animName, u32 blade, u32 weaponType) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  if (!dataParamAcc.isValid()) {
    return false;
  }

  if (dataParamAcc.getWeaponType(-1, false) == 0) {
    return false;
  }

  const char *modelName = dataParamAcc.getModelResourceName();
  if (weaponType >= 10) {
    animName.format("%s_%d", modelName, weaponType);
  } else {
    animName.format("%s_0%d", modelName, weaponType);
  }

  return true;
}

const char *GfDataBlade::getDebugName(u32 blade) {
  if (isCommonBlade(blade)) {
    SDataBlade &dataBlade = getSDataBlade(blade);
    if (dataBlade.unknown858.length() != 0) {
      return dataBlade.unknown858.c_str();
    }

    return getName(blade, 0);
  }

  return GfBdatChrBl::get()->getChrBlDebugName(blade);
}

u32 GfDataBlade::getRace(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).m_race;
}

u32 GfDataBlade::getGender(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).m_gender;
}

u32 GfDataBlade::getQuestRace(u32 blade) {
  if (blade == 0) {
    return QUEST_RACE_UNKNOWN_1;
  }

  return getSDataBlade(blade).unknown846;
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

  return getSDataBlade(blade).unknown846 == QUEST_RACE_UNKNOWN_2;
}

bool GfDataBlade::isMale(u32 blade) {
  if (blade == 0) {
    return false;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  if (dataBlade.m_gender != GENDER_UNKNOWN_1) {
    return false;
  }

  return dataBlade.unknown846 == QUEST_RACE_UNKNOWN_1;
}

bool GfDataBlade::isFemale(u32 blade) {
  if (blade == 0) {
    return false;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  if (dataBlade.m_gender != GENDER_UNKNOWN_2) {
    return false;
  }

  return dataBlade.unknown846 == QUEST_RACE_UNKNOWN_1;
}

bool GfDataBlade::getNameWithFieldSkillForDebug(mm::mtl::FixStr<128> &, u32) { return false; }

u32 GfDataBlade::getKeyReleaseLevel(u32 blade) { return getSDataBlade(blade).unknown664; }

u32 GfDataBlade::getRealBladeId(u32 blade) { return blade == BLADE_UNKNOWN_1050 ? BLADE_UNKNOWN_1022 : blade; }

const char *GfDataBlade::getBaseEabWeaponName(u32 blade) {
  if (blade == 0) {
    return "";
  }

  u32 weaponType = getBladeWpnType(blade);
  if (GfDataHana::isValid(blade) || isCommonBlade(blade)) {
    return unknown002[weaponType];
  }
  if (blade - BLADE_UNKNOWN_1051 < BLADE_ACT_UNKNOWN_22) {
    return unknown002[weaponType];
  }
  if (blade > unknown990 && blade != unknown991) {
    return unknown002[weaponType];
  }

  return "";
}

const char *GfDataBlade::getBaseEfbWeaponName(u32 blade) {
  if (blade == 0) {
    return "";
  }

  u32 weaponType = getBladeWpnType(blade);
  if (blade == BLADE_BYAKKO || GfDataHana::isValid(blade) || blade == BLADE_SAIKA || isCommonBlade(blade)) {
    return unknown002[weaponType];
  }
  if (blade - BLADE_UNKNOWN_1051 < BLADE_ACT_UNKNOWN_22) {
    return unknown002[weaponType];
  }
  if (blade > unknown990 && blade != unknown991) {
    return unknown002[weaponType];
  }

  return "";
}

u8 GfDataBlade::getAttribute(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getAttribute(blade);
  }

  return getSDataBlade(blade).unknown823;
}

bool GfDataBlade::isMatchIdeaAttribute(u32 blade, u32 idea) {
  switch (getAttribute(blade)) {
  case 1:
  case 2:
    return idea == 0;
  case 3:
  case 6:
    return idea == 1;
  case 4:
  case 5:
    return idea == 2;
  case 7:
  case 8:
    return idea == 3;
  default:
    return false;
  }
}

const char *GfDataBlade::getDeathBlowWeaponName(u32 blade) {
  u32 weaponType = blade == 0 ? 0 : getSDataBlade(blade).m_weaponType;
  return unknown002[weaponType];
}

u32 GfDataBlade::getBladePower(SDataBlade &dataBlade) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  DataIdeaAcc dataIdeaAcc(dataBlade.m_idea, false);
  f32 power = static_cast<u32>(dataIdeaAcc.getLevel(0));
  power += static_cast<u32>(dataIdeaAcc.getLevel(1));
  power += static_cast<u32>(dataIdeaAcc.getLevel(2));
  power += static_cast<u32>(dataIdeaAcc.getLevel(3));
  for (u32 i = 0; i < 3; i++) {
    if (dataBlade.unknown3c[i].unknown00 != 0) {
      u32 level = dataBlade.unknown3c[i].m_bladeArtsLevel;
      if (level != 0) {
        u32 difficulty = 0;
        if (dataBlade.unknownc4[i].unknown00 != 0) {
          u32 achievement = questListAcc->getFLD_AchievementSetAchievementID(dataBlade.unknownc4[i].unknown00, level - 1);
          if (achievement != 0) {
            difficulty = questListAcc->getFLD_AchievementListDifficulty(achievement);
          }
        }
        power += (level * 2.5f + difficulty) * 0.5f;
      }
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (dataBlade.unknown9c[i].unknown00 != 0) {
      u32 level = dataBlade.unknown9c[i].unknown03;
      if (level != 0) {
        u32 difficulty = 0;
        if (dataBlade.unknown274[i].unknown00 != 0) {
          u32 achievement = questListAcc->getFLD_AchievementSetAchievementID(dataBlade.unknown274[i].unknown00, level - 1);
          if (achievement != 0) {
            difficulty = questListAcc->getFLD_AchievementListDifficulty(achievement);
          }
        }
        power += (level * 2.5f + difficulty) * 0.5f;
      }
    }
  }
  for (u32 i = 0; i < 3; i++) {
    if (dataBlade.unknownae[i].m_fieldSkill != 0) {
      u32 level = dataBlade.unknownae[i].m_fieldSkillLevel;
      if (level != 0) {
        u32 difficulty = 0;
        if (dataBlade.unknown424[i].unknown00 != 0) {
          u32 achievement = questListAcc->getFLD_AchievementSetAchievementID(dataBlade.unknown424[i].unknown00, level - 1);
          if (achievement != 0) {
            difficulty = questListAcc->getFLD_AchievementListDifficulty(achievement);
          }
        }
        power += (level * 2.5f + difficulty) * 0.5f;
      }
    }
  }

  f32 rounded = ceilf(power);
  return rounded > 99.0f ? 99.0f : rounded;
}

u32 GfDataBlade::getBladePower(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getBladePower(getSDataBlade(blade));
}

f32 GfDataBlade::getWpnScale(u32 blade) {
  if (blade == 0) {
    return 1.0f;
  }

  return getSDataBlade(blade).unknown838 * unknown021;
}

f32 GfDataBlade::getScale(u32 blade) {
  if (blade == 0) {
    return 1.0f;
  }

  return getSDataBlade(blade).unknown836 * unknown021;
}

u32 GfDataBlade::getOffsetID(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown83a;
}

u16 GfDataBlade::getMountPoint(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown854;
}

u16 GfDataBlade::getMountObject(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown856;
}

u8 GfDataBlade::getSize(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown820;
}

u16 GfDataBlade::getCollisionId(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown83c;
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

  SDataBlade &dataBlade = getSDataBlade(blade);
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getRole(blade);
  }

  return getRoleByWpnType(dataBlade.m_weaponType);
}

u32 GfDataBlade::getEquipOrbMax(u32 blade) {
  if (blade == 0) {
    return 0;
  }

  return getSDataBlade(blade).unknown822;
}

u16 GfDataBlade::getEquipOrb(u32 blade, u32 slot) {
  if (blade == 0) {
    return 0;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  if (slot < getEquipOrbMax(blade)) {
    return dataBlade.unknown678[slot];
  }

  return 0;
}

GfItemHandle GfDataBlade::getEquipOrbHandle(u32 blade, u32 slot) {
  if (blade == 0) {
    return GfItemHandle(0);
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  if (slot < getEquipOrbMax(blade)) {
    return dataBlade.unknown680[slot];
  }

  return GfItemHandle(0);
}

bool GfDataBlade::getEquipOrb(mm::mtl::FixedArray<u16, 3> &equipOrbs, u32 blade) {
  if (blade == 0) {
    return false;
  }

  equipOrbs = getSDataBlade(blade).unknown678;
  return true;
}

bool GfDataBlade::getEquipOrbHandle(mm::mtl::FixedArray<u32, 3> &equipOrbHandles, u32 blade) {
  if (blade == 0) {
    return false;
  }

  equipOrbHandles = getSDataBlade(blade).unknown680;
  return true;
}

bool GfDataBlade::setEquipOrb(u32 blade, u16 orb, u32 slot) {
  if (blade == 0) {
    return false;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  // Ruling 5 (P3): the game calls GfDataManager::getDataGame() a second time after the one of
  // getSDataBlade and discards the result (0x71002a4510); the call is the getSDataBlade inside
  // getEquipOrbMax, whose value is dead. Probably the operand of a compiled-out assertion on
  // slot; the original expression cannot be checked.
  getEquipOrbMax(blade);
  dataBlade.unknown678[slot] = orb;
  return true;
}

bool GfDataBlade::setEquipOrbHandle(u32 blade, GfItemHandle handle, u32 slot) {
  if (blade == 0) {
    return false;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  // Ruling 5 (P3): same discarded getEquipOrbMax call as setEquipOrb (second getDataGame call
  // at 0x71002a45a8).
  getEquipOrbMax(blade);
  dataBlade.unknown680[slot] = handle.value;
  return true;
}

bool GfDataBlade::isEquipOrbFull(u32 blade) {
  if (blade == 0) {
    return false;
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  u32 equipOrbMax = getEquipOrbMax(blade);
  for (u32 slot = 0; slot < equipOrbMax; slot++) {
    if (dataBlade.unknown678[slot] == 0) {
      return false;
    }
  }

  return true;
}

bool GfDataBlade::getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, u32 blade) {
  if (blade == 0) {
    return false;
  }

  return getEquipOrbEnance(enhances, getSDataBlade(blade));
}

bool GfDataBlade::getEquipOrbEnance(mm::mtl::FixedVector<u16, 64> &enhances, SDataBlade &dataBlade) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 equipOrbMax = dataBlade.unknown822;
  for (u32 slot = 0; slot < equipOrbMax; slot++) {
    u32 orb = dataBlade.unknown678[slot];
    if (orb != 0) {
      u16 enhance = bdatItem->getEquipOrbEnhance(orb);
      if (enhance != 0) {
        enhances.push_back(enhance);
      }
    }
  }

  if (dataBlade.unknown06 - BLADE_UNKNOWN_1005 < BLADE_HANA_UNKNOWN_3) {
    u32 condenserNum = GfDataHana::getCondenserNum(dataBlade.unknown06);
    for (u32 slot = 0; slot < condenserNum; slot++) {
      u16 enhance = GfDataHana::getEquipParts(dataBlade)->getCondenserEnahnce(slot);
      if (enhance != 0) {
        enhances.push_back(enhance);
      }
    }

    u32 extendCondenserNum = GfDataHana::getExtendCondenserNum(dataBlade.unknown06);
    for (u32 slot = 0; slot < extendCondenserNum; slot++) {
      if (GfDataHana::isOpenCircuit(dataBlade, slot + 3)) {
        u16 enhance = GfDataHana::getEquipParts(dataBlade)->getExtendCondenserEnahnce(slot);
        if (enhance != 0) {
          enhances.push_back(enhance);
        }
      }
    }
  }

  return !enhances.empty();
}

u32 GfDataBlade::getBladeWeaponRank(u32 blade) {
  u32 weapon = getSDataBlade(blade).m_equipWeapon;
  if (weapon == 0) {
    return 0;
  }

  return GfBdatItem::get()->getPcWpnRank(weapon);
}

void GfDataBlade::setBladeWeapon(u32 blade, u32 weapon) {
  if (blade != 0) {
    getSDataBlade(blade).m_equipWeapon = weapon;
  }
}

void GfDataBlade::setAttributeForDebug(u32 blade, u8 attribute) {
  if (blade != 0) {
    getSDataBlade(blade).unknown823 = attribute;
  }
}

unknown108 *GfDataBlade::getArts(u32 blade, u32 slot) { return &getSDataBlade(blade).unknown3c[slot]; }

u32 GfDataBlade::getArtsEnhance(u32 blade, u32 slot) {
  if (blade - BLADE_UNKNOWN_1005 < BLADE_HANA_UNKNOWN_3) {
    return getSDataBlade(blade).m_equipParts.unknown04[slot].m_artsEnhance;
  }

  return 0;
}

unknown109 *GfDataBlade::getSkill(u32 blade, u32 slot) { return &getSDataBlade(blade).unknown9c[slot]; }

bool GfDataBlade::getListRegular(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 blade = BLADE_UNKNOWN_1001; blade < BLADE_UNKNOWN_1014; blade++) {
    if (!isDummyBlade(blade)) {
      blades.push_back(blade);
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListRare(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 blade = BLADE_UNKNOWN_1014_2; blade < BLADE_UNKNOWN_1051; blade++) {
    blades.push_back(blade);
  }

  return !blades.empty();
}

bool GfDataBlade::getListParty(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      if (isActivateDriver(blade) && GfDataDriver::isActivateParty(getSetDriver(blade)) && GfDataParty::isExistBlade(blade) && !isDummyBlade(blade) && !isUnselect(blade)) {
        blades.push_back(blade);
      }
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListReserver(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      if (!isActivateUnuse(blade) && !isActivateMercenaryTeam(blade) && !GfDataDriver::isActivateParty(getSetDriver(blade)) && !isDummyBlade(blade) && !isUnselect(blade)) {
        blades.push_back(blade);
      }
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListUnuse(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  return unknown001(blades, [](u32 blade) { return isActivateUnuse(blade) && !isDummyBlade(blade); });
}

bool GfDataBlade::getListUse(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  return unknown001(blades, [](u32 blade) { return !isActivateUnuse(blade) && !isDummyBlade(blade) && !isUnselect(blade); });
}

bool GfDataBlade::getListForAchievement(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  return unknown001(blades, [](u32 blade) { return (!isActivateUnuse(blade) || isAttachedParty(blade)) && !isDummyBlade(blade) && !isUnselect(blade); });
}

bool GfDataBlade::getListForFieldSkill(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  blades.clear();
  for (u32 member = 0; member < PARTY_UNKNOWN_8; member++) {
    u32 driver = GfDataParty::getDriver(member);
    if (driver != 0) {
      int slotNum = GfDataDriver::getMaxSetBladeNum(GfDataDriver::getSDataDriver(driver));
      for (int slot = 0; slot < slotNum; slot++) {
        u32 blade = GfDataDriver::getBlade(driver, slot);
        if (blade != 0 && !isDummyBlade(blade) && !isUnselect(blade)) {
          blades.push_back(blade);
        }
      }
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListParty(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades, bool unknown001, bool unknown002) {
  blades.clear();
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      if (!unknown001 && (blade == BLADE_HIKARI || blade == BLADE_HOMURI)) {
        continue;
      }
      if (isActivateDriver(blade) && (unknown002 || !isDummyBlade(blade)) && !isUnselect(blade)) {
        blades.push_back(blade);
      }
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListReserverWithSolo(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  getListReserver(blades);
  for (u16 *it = blades.begin(); it != blades.end();) {
    if (getSetDriver(*it) != 0) {
      it = blades.erase(it);
    } else {
      it++;
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getlistCommon(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 blade = BLADE_UNKNOWN_1197; blade < BLADE_UNKNOWN_1397; blade++) {
    if (!isActivateUnuse(blade) || isUnselect(blade)) {
      blades.push_back(blade);
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListLeave(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      if (!isActivateUnuse(blade) && isUnselect(blade) && !isDummyBlade(blade)) {
        if (mm::mtl::find(blades.begin(), blades.end(), static_cast<u16>(blade)) == blades.end()) {
          blades.push_back(blade);
        }
      }
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListReserverAndUnuse(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      if (!isActivateDriver(blade) && !isDummyBlade(blade)) {
        blades.push_back(blade);
      }
    }
  }

  return !blades.empty();
}

bool GfDataBlade::getListPartyAll(mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  for (u32 i = 0; i < BLADE_UNKNOWN_422; i++) {
    u32 blade = getBladeID(i);
    if (blade != 0) {
      if (isActivateDriver(blade) && GfDataDriver::isActivatePartyAll(getSetDriver(blade)) && !isDummyBlade(blade) && !isUnselect(blade)) {
        blades.push_back(blade);
      }
    }
  }

  return !blades.empty();
}

u32 GfDataBlade::getCreateEvent(u32 blade) { return getSDataBlade(blade).m_createEvent; }

u16 GfDataBlade::getNormalTalk(u32 blade) { return getSDataBlade(blade).m_normalTalk; }

u32 GfDataBlade::getActBlade2CommonBlade(u32 blade) { return blade - BLADE_UNKNOWN_1051 >= BLADE_ACT_UNKNOWN_22 ? blade : blade + (BLADE_UNKNOWN_1401_2 - BLADE_UNKNOWN_1051); }

bool GfDataBlade::isNeedAttributeResource(u32 blade) { return isCommonBlade(blade) || blade - BLADE_UNKNOWN_1051 < BLADE_ACT_UNKNOWN_22 || blade - BLADE_UNKNOWN_1005 < BLADE_HANA_UNKNOWN_3; }

u32 GfDataBlade::getTrustPoint(u32 blade) { return getSDataBlade(blade).m_trustPoint; }

GfIdea GfDataBlade::getTrustRank(u32 blade) { return getSDataBlade(blade).m_trustRank; }

void GfDataBlade::setTrustPoint(u32 blade, u32 trustPoint) {
  getSDataBlade(blade).m_trustPoint = trustPoint;
  GfEvent::callDebugChangeIdea(DEBUG_UNKNOWN_4, blade, 0, 0);
}

void GfDataBlade::setTrustRank(u32 blade, GfIdea trustRank) {
  getSDataBlade(blade).m_trustRank = trustRank;
  GfEvent::callDebugChangeIdea(DEBUG_UNKNOWN_4, blade, 0, 0);
}

u32 GfDataBlade::getParmor(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getParmor(blade);
  }

  return getSDataBlade(blade).unknown83e;
}

u32 GfDataBlade::getEarmor(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getEarmor(blade);
  }

  return getSDataBlade(blade).unknown83f;
}

u32 GfDataBlade::getHpMaxRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getHpMaxRev(blade);
  }

  return getSDataBlade(blade).unknown840;
}

u32 GfDataBlade::getStrengthRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getStrengthRev(blade);
  }

  return getSDataBlade(blade).unknown841;
}

u32 GfDataBlade::getPowerEtherRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getPowerEtherRev(blade);
  }

  return getSDataBlade(blade).unknown842;
}

u32 GfDataBlade::getDexRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getDexRev(blade);
  }

  return getSDataBlade(blade).unknown843;
}

u32 GfDataBlade::getAgilityRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getAgilityRev(blade);
  }

  return getSDataBlade(blade).unknown844;
}

u32 GfDataBlade::getLuckRev(u32 blade) {
  if (GfDataHana::isValid(blade)) {
    return GfDataHana::getLuckRev(blade);
  }

  return getSDataBlade(blade).unknown845;
}

u32 GfDataBlade::getBookedItemInfo(u32 blade) {
  GfBdatChrBl *bdatBlade = GfBdatChrBl::get();
  if (bdatBlade != nullptr && blade >= bdatBlade->getChrBlStart() && blade < bdatBlade->getChrBlEnd()) {
    return bdatBlade->getChrBlCreateInfo(blade);
  }

  return 0;
}

void GfDataBlade::setUsedFavoriteItemForPouch(u32 blade, u32 item) {
  if (blade == 0 || isDummyBlade(blade)) {
    return;
  }

  if (blade == BLADE_HOMURA) {
    if (isHikariCurrent()) {
      return;
    }
  } else if (blade == BLADE_HIKARI) {
    if (!isHikariCurrent()) {
      return;
    }
  }

  SDataBlade &dataBlade = getSDataBlade(blade);
  for (u32 i = 0; i < 2; i++) {
    unknown112 &favorite = dataBlade.unknown666[i];
    if (favorite.unknown06 == 0 && favorite.unknown02 == item) {
      favorite.unknown06 = 1;
    }
    if (favorite.unknown04 == 0) {
      u32 category = GfDataItem::getCategory(item);
      if (favorite.unknown00 == category) {
        favorite.unknown04 = 1;
      }
    }
  }
}

bool GfDataBlade::isUsedFavorite(u32 blade, FAVORITE favorite) {
  SDataBlade &dataBlade = getSDataBlade(blade);
  switch (favorite) {
  case FAVORITE_UNKNOWN_0:
    return dataBlade.unknown666[0].unknown04 != 0;
  case FAVORITE_UNKNOWN_1:
    return dataBlade.unknown666[1].unknown04 != 0;
  case FAVORITE_UNKNOWN_2:
    return dataBlade.unknown666[0].unknown06 != 0;
  case FAVORITE_UNKNOWN_3:
    return dataBlade.unknown666[1].unknown06 != 0;
  default:
    return false;
  }
}

u32 GfDataBlade::getFootStep(u32 blade) { return getSDataBlade(blade).m_footStep; }

u32 GfDataBlade::getFootStepEffect(u32 blade) { return getSDataBlade(blade).m_footStepEffect; }

bool GfDataBlade::isBladeID(u32 blade) { return blade - BLADE_UNKNOWN_1001 < BLADE_UNKNOWN_422; }

bool GfDataBlade::isReleaseLock(u32 blade) { return getSDataBlade(blade).unknown847 != 0; }

bool GfDataBlade::getMercenaryName(u8 *&bdat, u32 &textId, u32 blade) {
  if (isCommonBlade(blade)) {
    return false;
  }

  textId = GfBdatChrBl::get()->getChrBlMerceName(blade);
  bdat = GfBdatMsg::getFpMerceName();
  return textId != 0;
}

u8 GfDataBlade::getPersonality(u32 blade) { return getSDataBlade(blade).m_personality; }

u32 GfDataBlade::getVoiceID(u32 blade) {
  u32 personality = getSDataBlade(blade).m_personality;
  if (personality == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
}

const char *GfDataBlade::getVoiceStr(u32 blade) { return getSDataBlade(blade).unknown770.c_str(); }

const char *GfDataBlade::getSePack(u32 blade) { return getSDataBlade(blade).unknown7fc.c_str(); }

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
      if (getGender(*it) == GENDER_UNKNOWN_1) {
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
      if (getGender(*it) == GENDER_UNKNOWN_2) {
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
      if (getQuestRace(*it) == QUEST_RACE_UNKNOWN_2) {
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

const char *GfDataBlade::getFieldSkillVoice(u32 blade, u32 skill) {
  QuestListAcc *questList = QuestListAcc::get();
  SDataBlade &dataBlade = getSDataBlade(blade);
  if (dataBlade.unknownae[0].m_fieldSkill == skill || dataBlade.unknownae[1].m_fieldSkill == skill || dataBlade.unknownae[2].m_fieldSkill == skill) {
    u32 category = questList->getFLD_FieldSkillListVoiceCategory(skill);
    if (category != 0) {
      return GfDataField::getFieldSkillVoice(blade, category);
    }
  }
  return nullptr;
}

bool GfDataBlade::isNeedChangeWeapon(u32 blade) { return blade - BLADE_UNKNOWN_1043 < BLADE_UNKNOWN_8 || blade == BLADE_UNKNOWN_1039; }

bool GfDataBlade::isActivateParty(u32 blade) {
  if (blade == 0) {
    return false;
  }

  if (getSDataBlade(blade).m_dataType != BLADE_ACTIVATE_UNKNOWN_1) {
    return false;
  }

  return static_cast<u32>(GfDataParty::getDriverPartyID(getSDataBlade(blade).m_driverBySetBlade)) < 3;
}

bool GfDataBlade::isActivateReserver(u32 blade) {
  if (getSDataBlade(blade).m_dataType != BLADE_ACTIVATE_UNKNOWN_1) {
    return false;
  }

  u32 driver = getSetDriver(blade);
  if (driver != 0) {
    u32 partyId = GfDataParty::getDriverPartyID(driver);
    return partyId > 2 && partyId != static_cast<u32>(-1);
  }

  return true;
}

SDataIdea *GfDataBlade::getSDataIdea(u32 blade) { return &getSDataBlade(blade).m_idea; }

void GfDataBlade::setUiCommonBlade(const SDataBlade &dataBlade, u32 blade) {
  SDataBlade &uiCommonBlade = getSDataBlade(blade);
  uiCommonBlade = dataBlade;
  uiCommonBlade.unknown06 = blade;
}

void GfDataBlade::setActCommonBlade(const SDataBlade &dataBlade, u32 blade) {
  getSDataBlade(blade) = dataBlade;
  getSDataBlade(blade).unknown06 = blade;
}

} // namespace gf
