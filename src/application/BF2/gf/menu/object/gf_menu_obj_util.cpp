#include "gf/menu/object/gf_menu_obj_util.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_battle.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/util/gf_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {
struct GF_OBJ_HANDLE;

struct IconTable {
  u32 unknown00; // Inferred role: key; original member name unknown.
  u32 unknown04; // Inferred role: icon; original member name unknown.
};

enum MENU_SE {
  MENU_SE_DECIDE = 1,
  MENU_SE_CANCEL = 2,
  MENU_SE_TAB = 5,
  MENU_SE_CURSOR = 6,
  MENU_SE_INVALID = 7,
  MENU_SE_SORT = 11,
  MENU_SE_OPEN_SUB_MENU = 12,
  MENU_SE_CLOSE_SUB_MENU = 14,
};

constexpr u32 ICON_NONE = 0xffff;
constexpr u32 POINTER_SELECT_ICON = 17;
constexpr u32 PARTY_DRIVER_MAX = 3;
constexpr u16 SCENARIO_CUSTOM_ENABLE = 2000;
constexpr u32 BLADE_EXTRA_FIRST = 1043;
constexpr u32 BLADE_EXTRA_COUNT = 7;
constexpr u32 BLADE_RANK_MAX = 5;
constexpr u32 BLADE_RARITY_SCENARIO = 2;
constexpr int FLAG_BLADE_SLOT_2_OPEN = 0x89ff;
constexpr int FLAG_BLADE_SLOT_3_OPEN = 0x8a00;
constexpr u32 ICON_WEAPON_TYPE_BASE = 0x8a;
constexpr u32 ICON_WEAPON_TYPE_NONE = 0x8b;
constexpr u32 ICON_ATTRIBUTE_BASE = 0x9e;
constexpr u32 ICON_TRUST_RANK_BASE = 0x83;

static const IconTable s_buttonIcons[] = {
    {0x1000, 26},
    {0x2000, 29},
    {0x4000, 27},
    {0x8000, 28},
    {0x8, 10},
    {0x4, 12},
    {0x2, 13},
    {0x1, 11},
    {0x20, 19},
    {0x80, 25},
    {0x800, 15},
    {0x10, 18},
    {0x40, 24},
    {0x400, 14},
    {0x200, 9},
    {0x100, 8},
};

static const IconTable s_padSelectIcons[] = {
    {1, 30},
    {2, 31},
    {6, 5},
    {3, 19},
    {5, 16},
    {4, 16},
    {9, 17},
    {8, 17},
};

static const u32 s_ideaLevelPoints[] = {500, 1500, 3500, 7000, 10000};

static const u16 s_commonSes[] = {MENU_SE_DECIDE, MENU_SE_CANCEL, MENU_SE_INVALID};

u32 GfMenuObjUtil::getBtnIconNumber(u32 button) {
  for (u32 i = 0; i < sizeof(s_buttonIcons) / sizeof(s_buttonIcons[0]); i++) {
    if ((button & s_buttonIcons[i].unknown00) != 0) {
      return s_buttonIcons[i].unknown04;
    }
  }
  return ICON_NONE;
}

u32 GfMenuObjUtil::getPadSelectIconNumber(u32 select) {
  for (u32 i = 0; i < sizeof(s_padSelectIcons) / sizeof(s_padSelectIcons[0]); i++) {
    if (s_padSelectIcons[i].unknown00 == select) {
      return s_padSelectIcons[i].unknown04;
    }
  }
  return ICON_NONE;
}

u32 GfMenuObjUtil::getPointerSelectIconNumber() { return POINTER_SELECT_ICON; }

void GfMenuObjUtil::setChildDisp(u32 handle, const char *name, bool disp) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjUtil::setChildMulColor(u32 handle, const char *name, const char *color) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    acc.setMulColor(color);
  }
}

void GfMenuObjUtil::setChildAddColor(u32 handle, const char *name, const char *color) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    acc.setAddColor(color);
  }
}

void GfMenuObjUtil::setChildText(u32 handle, const char *name, u16 id) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    GfMenuObject::setText(acc.unknown10, id);
  }
}

void GfMenuObjUtil::setChildText(u32 handle, const char *name, const ui::UIStr &text) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    acc.setText(text);
  }
}

void GfMenuObjUtil::setChildIcon(u32 handle, const char *name, u16 icon) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    acc.setImageIndex(GfMenuBdat::getIconImageIndex(icon));
  }
}

u32 GfMenuObjUtil::playAnime(u32 handle, const char *name, const char *anime) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    acc.setDisp(true);
    acc.startAnimation(anime, false);
    return acc.unknown10;
  }
  return 0;
}

u32 GfMenuObjUtil::getMenuIcon(u32 id) { return Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_ICON_LIST), "icon_index", id).valueU8; }

void GfMenuObjUtil::setDockPos(u32 handle, u32 target, u8 dock, bool global) { ui::UIUtil::setDockPos(handle, target, dock, global); }

void GfMenuObjUtil::addPos(u32 handle, s16 x, s16 y) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    mm::Pnt<s16> pos;
    acc.getPos(pos);
    pos.x += x;
    pos.y += y;
    acc.setPos(pos);
  }
}

bool GfMenuObjUtil::isMenuObjectFull() {
  if (ui::UIEventManager::get()->isObjectListenerFull()) {
    return true;
  }
  return GfMenuAdapterManager::isAdapterFull();
}

int GfMenuObjUtil::getCtrlID(u32 handle) { return ui::UICtrlManager::get()->getCtrlSlot(handle); }

void GfMenuObjUtil::stopCtrl(int ctrl) {
  if (ctrl != -1) {
    ui::UICtrlManager::get()->stopCtrl(ctrl, true, false);
  }
}

void GfMenuObjUtil::suspendCtrl(int ctrl) {
  if (ctrl != -1) {
    ui::UICtrlManager::get()->stopCtrl(ctrl, false, false);
  }
}

void GfMenuObjUtil::releaseCtrl(int ctrl) {
  if (ctrl != -1) {
    ui::UICtrlManager::get()->releaseCtrlSlot(ctrl);
  }
}

bool GfMenuObjUtil::isBusyCtrl(int ctrl) {
  if (ctrl != -1) {
    return ui::UICtrlManager::get()->isBusyCtrl(ctrl);
  }
  return false;
}

void GfMenuObjUtil::setCtrlDefault(int ctrl) {
  if (ctrl != -1) {
    ui::UICtrlManager::get()->setDefault(ctrl);
  }
}

void GfMenuObjUtil::setCtrlSpeedFactor(int ctrl, f32 speedFactor) {
  if (ctrl != -1) {
    ui::UICtrlManager::get()->setSpeedFactor(ctrl, speedFactor);
  }
}

u32 GfMenuObjUtil::getPresetCtrlCurve(u32 preset) { return 1; }

const char *GfMenuObjUtil::getMenuMS(u32 id) {
  if (id != 0) {
    return Bdat::getMSText(GfDataBdat::getFP(BDAT_MENU_MS), id);
  }
  return nullptr;
}

u32 GfMenuObjUtil::getLeaderPartyID() { return 0; }

int GfMenuObjUtil::getLeaderPartyType() {
  GF_OBJ_HANDLE *leader = GfGameParty::getLeader();
  if (leader != INVALID_HANDLE) {
    return GfObjAcc(leader).getType();
  }
  return -1;
}

bool GfMenuObjUtil::isExitDriver(u32 partyId) {
  if (partyId >= PARTY_DRIVER_MAX) {
    partyId %= PARTY_DRIVER_MAX;
  }
  return GfGameParty::getHandleDriver(partyId) != INVALID_HANDLE;
}

bool GfMenuObjUtil::isLeaderBladeEnable() {
  u32 blade = GfDataDriver::getBlade(GfDataParty::getDriver(0), -1);
  return blade != 0 && !GfDataBlade::isDummyBlade(blade);
}

bool GfMenuObjUtil::isBladeEnable(u32 partyId, int slot) {
  u32 blade = GfDataDriver::getBlade(GfDataParty::getDriver(partyId), -1);
  return blade != 0 && !GfDataBlade::isDummyBlade(blade);
}

bool GfMenuObjUtil::isValidBlade(u32 blade) { return blade != 0 && !GfDataBlade::isDummyBlade(blade); }

bool GfMenuObjUtil::isBladeEnableOffset(u32 partyId, int offset) {
  int slot = getSetBladeID(partyId, offset, false);
  if (slot == -1) {
    return false;
  }
  u32 driver = GfDataParty::getDriver(partyId);
  if (driver == 0) {
    return false;
  }
  u32 blade = GfDataDriver::getBlade(driver, slot);
  return blade != 0 && !GfDataBlade::isDummyBlade(blade);
}

bool GfMenuObjUtil::isBladeContorolable(u32 blade) {
  if (blade != 0) {
    return GfDataBlade::isOperable(blade);
  }
  return false;
}

bool GfMenuObjUtil::isBladeContorolable(u32 partyId, int slot) {
  if (!isBladeEnable(partyId, slot)) {
    return false;
  }
  u32 driver = GfDataParty::getDriver(partyId);
  if (driver == 0) {
    return false;
  }
  return isBladeContorolable(GfDataDriver::getBlade(driver, slot));
}

GF_OBJ_HANDLE *GfMenuObjUtil::getLeaderBladeHandle(bool isVirtual) {
  int bladeSet = 0;
  {
    DataParamAcc acc(OBJECT_TYPE_DRIVER, GfDataParty::getDriver(0), GIMMICK_TYPE_NONE);
    if (acc.isValid()) {
      bladeSet = acc.getBladeSet(false);
    }
  }
  if (bladeSet == -1) {
    return INVALID_HANDLE;
  }
  return GfGameParty::getHandleBlade(0, bladeSet);
}

GF_OBJ_HANDLE *GfMenuObjUtil::getBladeHandle(u32 partyId, u32 slot) { return GfGameParty::getHandleBlade(partyId, slot); }

u32 GfMenuObjUtil::getBladeIDFromPartySlot(u32 partyId, int offset, bool isVirtual) {
  if (partyId >= 10) {
    return 0;
  }

  DataParamAcc acc(OBJECT_TYPE_DRIVER, GfDataParty::getDriver(partyId), GIMMICK_TYPE_NONE);
  int slot = getSetBladeID(partyId, offset, isVirtual);
  u32 blade = 0;
  if (slot != -1) {
    blade = acc.getBlade(slot, false);
  }
  return blade;
}

GF_OBJ_HANDLE *GfMenuObjUtil::getBladeHandleFromPartySlot(u32 partyId, int offset, bool isVirtual) {
  int slot = getSetBladeID(partyId, offset, isVirtual);
  if (slot == -1) {
    return INVALID_HANDLE;
  }
  return GfGameParty::getHandleBlade(partyId, slot);
}

GF_OBJ_HANDLE *GfMenuObjUtil::getBladeHandleFromPartyBackSlot(u32 partyId, int offset, bool isVirtual) {
  return GfGameParty::getHandleBladeByBdatID(getBladeIDFromPartyBackSlot(partyId, offset, isVirtual));
}

GF_OBJ_HANDLE *GfMenuObjUtil::getBladeHandleOffset(u32 partyId, int offset) {
  int slot = getSetBladeID(partyId, offset, false);
  if (slot == -1) {
    return INVALID_HANDLE;
  }
  return GfGameParty::getHandleBlade(partyId, slot);
}

u32 GfMenuObjUtil::getBladeSlotMax() {
  u32 slotMax = 1;
  if (GfGameFlag::getLocal(1, FLAG_BLADE_SLOT_2_OPEN) == 1) {
    slotMax++;
  }
  if (GfGameFlag::getLocal(1, FLAG_BLADE_SLOT_3_OPEN) == 1) {
    slotMax = 3;
  }
  return slotMax;
}

u32 GfMenuObjUtil::getBladeCorrectiveType(u32 blade) {
  if (!GfDataBlade::isValid(blade)) {
    return 0;
  }
  if (GfDataBlade::getHpMaxRev(blade) * 0.01f > 0.0f) {
    return 1;
  }
  if (GfDataBlade::getStrengthRev(blade) * 0.01f > 0.0f) {
    return 2;
  }
  if (GfDataBlade::getPowerEtherRev(blade) * 0.01f > 0.0f) {
    return 3;
  }
  if (GfDataBlade::getDexRev(blade) * 0.01f > 0.0f) {
    return 4;
  }
  if (GfDataBlade::getAgilityRev(blade) != 0) {
    return 5;
  }
  if (GfDataBlade::getLuckRev(blade) != 0) {
    return 6;
  }

  return 0;
}

u32 GfMenuObjUtil::getBladeCorrectiveRatio(u32 blade) {
  if (!GfDataBlade::isValid(blade)) {
    return 0;
  }

  u32 rev;
  if (GfDataBlade::getHpMaxRev(blade) * 0.01f > 0.0f) {
    rev = GfDataBlade::getHpMaxRev(blade);
  } else if (GfDataBlade::getStrengthRev(blade) * 0.01f > 0.0f) {
    rev = GfDataBlade::getStrengthRev(blade);
  } else if (GfDataBlade::getPowerEtherRev(blade) * 0.01f > 0.0f) {
    rev = GfDataBlade::getPowerEtherRev(blade);
  } else if (GfDataBlade::getDexRev(blade) * 0.01f > 0.0f) {
    rev = GfDataBlade::getDexRev(blade);
  } else if (GfDataBlade::getAgilityRev(blade) != 0) {
    rev = GfDataBlade::getAgilityRev(blade);
  } else if (GfDataBlade::getLuckRev(blade) != 0) {
    rev = GfDataBlade::getLuckRev(blade);
  } else {
    return 0;
  }

  f32 percent = rev * 0.01f * 100.0f;
  f32 half;
  if (percent > 0.0f) {
    half = 0.5f;
  } else {
    half = -0.5f;
  }

  return static_cast<int>(percent + half);
}

bool GfMenuObjUtil::isBladeDifferentImage(u32 blade, u32 other) { return convMenuBladeID(blade) != convMenuBladeID(other); }

void GfMenuObjUtil::getIdeagramDriver(u32 driver, SDataIdea &idea) { idea = *GfDataDriver::getSDataIdea(driver); }

void GfMenuObjUtil::getIdeagramBlade(u32 blade, SDataIdea &idea) {
  if (blade != 0) {
    idea = *GfDataBlade::getSDataIdea(blade);
  }
}

void GfMenuObjUtil::getIdeagramDriverFromHandle(GF_OBJ_HANDLE *handle, SDataIdea &idea) {
  u32 driver = GfObjAcc(handle).getBdatId();
  if (driver != 0) {
    idea = *GfDataDriver::getSDataIdea(driver);
  } else {
    idea = SDataIdea();
  }
}

int GfMenuObjUtil::getDriverPartyID(u32 driver) {
  for (u32 member = 0; member < 10; member++) {
    if (GfDataParty::getDriver(member) == driver) {
      return member;
    }
  }

  return -1;
}

u16 GfMenuObjUtil::getBladeFaceIconID(GF_OBJ_HANDLE *handle) {
  u32 blade = GfObjAcc(handle).getBdatId();
  if (GfDataBlade::isValid(blade)) {
    return GfDataBlade::getSDataBlade(blade)->unknown70a;
  }
  return GfMenuBdat::getTopBladeIconID();
}

u16 GfMenuObjUtil::getBladeFaceIconID(u32 blade) {
  if (GfDataBlade::isValid(blade)) {
    return GfDataBlade::getSDataBlade(blade)->unknown70a;
  }
  return GfMenuBdat::getTopBladeIconID();
}

u32 GfMenuObjUtil::getBladeWeaponTypeIconID(u32 blade) {
  if (GfDataBlade::isValid(blade)) {
    return GfDataBlade::getSDataBlade(blade)->unknown821 + ICON_WEAPON_TYPE_BASE;
  }
  return ICON_WEAPON_TYPE_NONE;
}

u16 GfMenuObjUtil::getBladeAttributeIconID(u32 blade) {
  if (GfDataBlade::isValid(blade)) {
    return GfDataBlade::getAttribute(blade) + ICON_ATTRIBUTE_BASE;
  }
  return ICON_ATTRIBUTE_BASE;
}

u16 GfMenuObjUtil::getBladeCompatibilityIconID(u32 driver, u32 blade) {
  if (GfDataBlade::isValid(blade)) {
    return GfGameUtil::getTrustRank(blade) + ICON_TRUST_RANK_BASE;
  }
  return ICON_TRUST_RANK_BASE;
}

u16 GfMenuObjUtil::getBladeAttributeID(u32 blade) {
  if (GfDataBlade::isValid(blade)) {
    return GfDataBlade::getSDataBlade(blade)->unknown823;
  }
  return 0;
}

u32 GfMenuObjUtil::getBladeRank(u32 blade) {
  if (isScenarioBlade(blade)) {
    return BLADE_RANK_MAX;
  }
  if (GfDataBlade::isRareBlade(blade)) {
    return BLADE_RANK_MAX;
  }
  u32 kizunaringMax = GfDataBlade::getKizunaringMax(blade);
  if (kizunaringMax > 37) {
    return 4;
  }
  if (kizunaringMax > 28) {
    return 3;
  }
  return kizunaringMax > 18 ? 2 : 1;
}

bool GfMenuObjUtil::isScenarioBlade(u32 blade) { return GfDataBlade::isRegularBlade(blade) || blade == BLADE_WADATSUMI; }

u32 GfMenuObjUtil::getBladeRarity(u32 blade) {
  if (isScenarioBlade(blade)) {
    return BLADE_RARITY_SCENARIO;
  }
  return GfDataBlade::isRareBlade(blade);
}

bool GfMenuObjUtil::isExtraBlade(u32 blade) { return blade - BLADE_EXTRA_FIRST < BLADE_EXTRA_COUNT; }

bool GfMenuObjUtil::isBladeNoBuildWeapon(u32 blade) { return blade - BLADE_EXTRA_FIRST < BLADE_EXTRA_COUNT; }

bool GfMenuObjUtil::isBladeCurrent(u32 blade) {
  u32 driver = GfDataBlade::getSetDriver(blade);
  if (driver == 0) {
    return false;
  }
  return GfDataDriver::getBlade(driver, -1) == blade;
}

bool GfMenuObjUtil::canRemoveBlade(u32 blade, const mm::mtl::FixedVector<u16, 422> *blades) { return canRemoveBladeEx(blade, 0, blades) == 0; }

bool GfMenuObjUtil::hasHomura(u32 driver) {
  bool hasHomura = false;
  DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    if (GfDataBlade::getCreator(BLADE_HOMURA) == driver) {
      hasHomura = !GfDataBlade::isActivateUnuse(BLADE_HOMURA);
    }
  }
  return hasHomura;
}

u16 GfMenuObjUtil::getMsgIDFromList(u32 bdat, u16 id) {
  u8 *list = GfDataBdat::getFP(bdat);
  if (list != nullptr) {
    return Bdat::getVal(list, "name", id).valueU16;
  }
  return 0;
}

int GfMenuObjUtil::getEnableArts(mm::mtl::FixedArray<u32, 4> &arts, u32 driver, u32 weaponType) {
  mm::mtl::FixedArray<u32, 3> slotArts;
  GfDataDriverArts::getSlotArts(slotArts, driver, weaponType);
  mm::mtl::FixedArray<u32, 4> enableArts;
  GfDataDriverArts::getEnableArts(enableArts, driver, weaponType);

  int count = 0;
  for (u32 i = 0; i < slotArts.size(); i++) {
    arts[i] = slotArts[i];
    if (slotArts[i] != 0) {
      count++;
    }
  }
  arts[3] = 0;

  for (u32 i = 0; i < enableArts.size(); i++) {
    if (enableArts[i] != 0 && GfDataDriverArts::getArtsLevel(driver, enableArts[i]) != 0 && enableArts[i] != arts[0] && enableArts[i] != arts[1] && enableArts[i] != arts[2] &&
        enableArts[i] != arts[3]) {
      arts[3] = enableArts[i];
      count++;
      break;
    }
  }
  return count;
}

bool GfMenuObjUtil::checkCCStart(GfMenuCallContext *context) { return context != nullptr && !context->isActive(); }

bool GfMenuObjUtil::checkCCNext(GfMenuCallContext *context, u32 menu) { return context != nullptr && context->unknown10 == menu; }

u32 GfMenuObjUtil::convIdeaPointToLevel(u32 point) {
  for (u32 level = 0; level < sizeof(s_ideaLevelPoints) / sizeof(s_ideaLevelPoints[0]); level++) {
    if (point < s_ideaLevelPoints[level]) {
      return level;
    }
  }
  return sizeof(s_ideaLevelPoints) / sizeof(s_ideaLevelPoints[0]);
}

u32 GfMenuObjUtil::playSE(u32 id) {
  if (fw::SoundManager::get() != nullptr) {
    u16 se = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_SOUND_SE), "resource_id", id).valueU16;
    if (se != 0) {
      return fw::SoundManager::get()->playSe(se, nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
    }
  }
  return 0;
}

u32 GfMenuObjUtil::playSE(const char *name) {
  if (fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->playSe(name, nullptr, 1.0f, static_cast<fw::SoundCategory>(3));
  }
  return 0;
}

u32 GfMenuObjUtil::playSECommonDecide() { return playSE(MENU_SE_DECIDE); }

u32 GfMenuObjUtil::playSECommon(u32 type) {
  if (type < sizeof(s_commonSes) / sizeof(s_commonSes[0])) {
    return playSE(s_commonSes[type]);
  }
  return 0;
}

u32 GfMenuObjUtil::playSECommonCancel() { return playSE(MENU_SE_CANCEL); }

u32 GfMenuObjUtil::playSECommonCursor() { return playSE(MENU_SE_CURSOR); }

u32 GfMenuObjUtil::playSECommonTab() { return playSE(MENU_SE_TAB); }

u32 GfMenuObjUtil::playSECommonSort() { return playSE(MENU_SE_SORT); }

u32 GfMenuObjUtil::playSECommonOpenSubMenu() { return playSE(MENU_SE_OPEN_SUB_MENU); }

u32 GfMenuObjUtil::playSECommonCloseSubMenu() { return playSE(MENU_SE_CLOSE_SUB_MENU); }

void GfMenuObjUtil::stopSE(u32 handle, f32 time) {
  if (fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopSe(handle, time);
  }
}

bool GfMenuObjUtil::startBGM(u32 handle) {
  if (handle != 0 && fw::SoundManager::get() != nullptr) {
    return fw::SoundManager::get()->startBgm(handle);
  }
  return false;
}

bool GfMenuObjUtil::isValidSoundHandle(u32 handle) { return handle != 0; }

void GfMenuObjUtil::stopBGM(u32 handle, f32 time) {
  if (handle != 0 && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->stopBgm(handle, time);
  }
}

u32 GfMenuObjUtil::playJingle(u32 id) { return GfMenuSoundManager::playJingle(id); }

ui::UIStr GfMenuObjUtil::getElementComboName(u32 combo) {
  u8 *bdat = Bdat::getFP("BTL_ElementalCombo");
  if (!GfMenuBdat::isValidBdatID(bdat, combo)) {
    return ui::UIStr();
  }

  u8 name = Bdat::getVal(bdat, "Name", combo).valueU8;
  if (name != 0) {
    return ui::UIStr(Bdat::getFP("btl_elementalcombo_ms"), name);
  }

  return ui::UIStr(Bdat::getVal(bdat, "DebugName", combo).valueString, false);
}

ui::UIStr GfMenuObjUtil::getElementComboEffectName(u32 combo) {
  u8 *bdat = Bdat::getFP("BTL_ElementalCombo");
  if (GfMenuBdat::isValidBdatID(bdat, combo)) {
    u8 atr = Bdat::getVal(bdat, "Atr", combo).valueU8;
    u8 name = Bdat::getVal(Bdat::getFP("BTL_ElementalEffect"), "Name", atr).valueU8;
    if (name != 0) {
      return ui::UIStr(Bdat::getFP("btl_elementaleffect_ms"), name);
    }
  }

  return ui::UIStr();
}

ui::UIStr GfMenuObjUtil::getEnemyArtsName(u32 arts) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_ARTS_EN);
  u8 *msBdat = GfDataBdat::getFP(BDAT_BTL_ARTS_EN_MS);
  if (GfMenuBdat::isValidBdatID(bdat, arts)) {
    u16 name = Bdat::getVal(bdat, "Name", arts).valueU16;
    if (name != 0) {
      return ui::UIStr(msBdat, name);
    }
  }

  return ui::UIStr();
}

ui::UIStr GfMenuObjUtil::getDriverClassName(u32 driver) {
  u32 battleClass = GfDataDriver::getClass(driver);
  if (battleClass != 0) {
    u8 *bdat;
    u32 textId;
    if (GfDataBattle::getClassName(bdat, textId, battleClass)) {
      return ui::UIStr(bdat, textId);
    }
    return ui::UIStr();
  }

  return ui::UIStr();
}

u8 GfMenuObjUtil::getElementComboAtr(u32 combo) {
  u8 *bdat = Bdat::getFP("BTL_ElementalCombo");
  if (GfMenuBdat::isValidBdatID(bdat, combo)) {
    return Bdat::getVal(bdat, "Atr", combo).valueU8;
  }
  return 0;
}

u8 GfMenuObjUtil::getElementComboEffect(u32 combo) { return 1; }

u8 GfMenuObjUtil::getElementComboStage(u32 combo) {
  u8 *bdat = Bdat::getFP("BTL_ElementalCombo");
  if (GfMenuBdat::isValidBdatID(bdat, combo)) {
    return Bdat::getVal(bdat, "ComboStage", combo).valueU8;
  }
  return 0;
}

bool GfMenuObjUtil::isQuestCompleted(QuestID quest) { return GfQuestInfo::isQuestFin(quest); }

bool GfMenuObjUtil::getMenuCondition(u32 id) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_CONDITION);
  if (id < static_cast<u32>(Bdat::getIdTop(bdat)) || id > static_cast<u32>(Bdat::getIdEnd(bdat))) {
    return false;
  }
  return GfGameCond::isGameCond(Bdat::getVal(bdat, "cond", id).valueU16);
}

bool GfMenuObjUtil::getMenuFullOpenFlag() { return false; }

bool GfMenuObjUtil::isCustomEnableBlade(u32 blade) { return GfDataUtil::getScenarioFlag() > SCENARIO_CUSTOM_ENABLE; }

u16 GfMenuObjUtil::getBladeRareIconID(u32 blade) {
  u32 icon = ICON_WEAPON_TYPE_BASE - 1;
  if (GfDataBlade::isValid(blade)) {
    icon += GfDataBlade::isRareBlade(blade);
  }
  return icon;
}

bool GfMenuObjUtil::isEnemyBoss(GF_OBJ_HANDLE *handle) {
  DataParamAcc dataParamAcc(handle);
  const SDataEnemy *dataEnemy = dataParamAcc.getSDataEnemy();
  if (dataEnemy == nullptr) {
    return false;
  }
  return dataEnemy->unknown04_1;
}

bool GfMenuObjUtil::isEnemyNamed(GF_OBJ_HANDLE *handle) {
  DataParamAcc dataParamAcc(handle);
  const SDataEnemy *dataEnemy = dataParamAcc.getSDataEnemy();
  if (dataEnemy == nullptr) {
    return false;
  }
  return dataEnemy->unknown04_0;
}

void GfMenuObjUtil::setColDefault(u32 handle) {
  ui::UIObjectAcc objectAcc(handle);
  if (objectAcc.isValid()) {
    objectAcc.loadDefColor();
  }
}

bool GfMenuObjUtil::getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &position) { return util::getScreenPos(screenPos, position); }

} // namespace gf
