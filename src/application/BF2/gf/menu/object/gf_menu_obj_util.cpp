#include "gf/menu/object/gf_menu_obj_util.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_pad.h"
#include "fw/fw_param_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_battle.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/gf_info.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_util.h"
#include "ml/dev_pad.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_manager.h"
#include "ui/input/ui_input_layer.h"
#include "ui/input/ui_input_manager.h"
#include "ui/input/ui_input_pointer.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/motion/ui_motion_data.h"
#include "ui/motion/ui_motion_library.h"
#include "ui/plugin/ui_object_disp_plugin.h"
#include "ui/plugin/ui_object_dock_plugin.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_scroll_bar_plugin.h"
#include "ui/plugin/ui_object_sync_plugin.h"
#include "ui/ui_color_library.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"
#include "ui/ui_util.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: icon table; original type name unknown.
struct unknown078 {
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

static const unknown078 s_buttonIcons[] = {
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

static const unknown078 s_padSelectIcons[] = {
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

// Inferred role: bdat columns of the class buff types; original name unknown.
static const char *unknown079[] = {"DamageDown", "DamageUP", "HealUP", "AutoHate", "ArtsHate"};

// Inferred role: bdat columns of the class buff levels; original name unknown.
static const char *unknown080[] = {"DamageDownNum", "DamageUPNum", "HealUPNum", "AutoHateNum", "ArtsHateNum"};

s16 GfMenuObjUtil::getBtnIconNumber(u32 button) {
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

bool GfMenuObjUtil::checkMissionCond(u32 mission, const GfMenuBladeList *list) {
  GfRequestBladeData data = {};
  if (GfGameMercenaries::getMissionFlag(mission) != 1) {
    return false;
  }
  for (u32 task = 0; task < 3; task++) {
    if (GfDataMercenaries::getRequestCondition(data, mission, task) && list != nullptr) {
      u32 count = getMissionCondBladeCount(data, list);
      u32 need = data.unknown0c == 0 ? 1 : data.unknown0c;
      if (count < need) {
        return false;
      }
    }
  }
  return true;
}

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

bool GfMenuObjUtil::isInBattle(GF_OBJ_HANDLE *handle) {
  if (GfObjAcc(handle).getType() == OBJECT_TYPE_ENEMY) {
    GfObjProperty *property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
      return false;
    }
    if (property->unknown10 != nullptr) {
      return property->unknown10->unknown30;
    }
  }
  return false;
}

int GfMenuObjUtil::convMenuDriverID(u32 driver) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_DR_IMAGE_ID);
  DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  int index = 0;
  if (acc.isValid()) {
    int top = Bdat::getIdTop(bdat);
    u32 icon = getFaceIconID(acc);
    index = 0;
    do {
      if (index >= Bdat::getIdCount(bdat)) {
        index = 0;
        break;
      }
      u32 iconId = Bdat::getVal(bdat, "icon_id", top + index).valueU16;
      index++;
      if (icon == iconId) {
        break;
      }
    } while (true);
  }
  return index;
}

int GfMenuObjUtil::convMenuBladeID(u32 blade) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_BL_IMAGE_ID);
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  int index = 0;
  if (acc.isValid()) {
    int top = Bdat::getIdTop(bdat);
    u32 icon = getFaceIconID(acc);
    index = 0;
    do {
      if (index >= Bdat::getIdCount(bdat)) {
        return 0;
      }
      u32 iconId = Bdat::getVal(bdat, "icon_id", top + index).valueU16;
      index++;
      if (icon == iconId) {
        break;
      }
    } while (true);
    if (GfDataBlade::isCommonBlade(acc.getValidBdatId())) {
      for (u32 type = 10; type <= 16; type++) {
        if (acc.getWeaponType(-1, false) == type) {
          index += (type - 10) * 4;
        }
      }
    }
  }
  return index;
}

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

u32 GfMenuObjUtil::setupPartyDriver(const mm::mtl::FixedVector<u16, 16> &drivers) {
  RQ_SETUP_PARTY_DRIVER info = RQ_SETUP_PARTY_DRIVER();
  if (drivers.size() == 0) {
    return 0;
  }
  GfGameParty::getCurrentPartyInfo(info);
  for (u32 i = 0; i < 10; i++) {
    info.unknown00[i] = 0;
  }
  for (u32 i = 0; i < drivers.size(); i++) {
    info.unknown00[i] = *drivers.at(i);
  }
  info.unknown14 = info.unknown00[0];
  return GfReqCommand::reqChangeParty(info);
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

int GfMenuObjUtil::getSetBladeID(u32 partyId, int offset, bool isVirtual) {
  DataParamAcc acc(OBJECT_TYPE_DRIVER, GfDataParty::getDriver(partyId), GIMMICK_TYPE_NONE);
  int setId = 0;
  if (acc.isValid()) {
    if (offset == -1) {
      setId = acc.getBladeSet(false);
    } else if (offset < static_cast<int>(getBladeSlotMax())) {
      setId = acc.getBladeSet(false);
      if (isVirtual && (GfMenuManager::isBattleState(0) || GfMenuManager::isBattleState(1))) {
        setId = GfSelectBlade::getStartBattleSetId(partyId);
      }
      int slot = setId;
      if (acc.getValidDriverId() == DRIVER_REX && setId - 3U < 2) {
        if (acc.getBlade(0, false) == BLADE_HOMURA) {
          slot = 0;
        } else if (acc.getBlade(1, false) == BLADE_HOMURA) {
          slot = 1;
        } else if (acc.getBlade(2, false) == BLADE_HOMURA) {
          slot = 2;
        }
      }
      slot += offset;
      if (slot >= static_cast<int>(getBladeSlotMax())) {
        slot -= getBladeSlotMax();
      }
      setId = slot;
      if (acc.getValidDriverId() == DRIVER_REX && acc.getBlade(slot, false) == BLADE_HOMURA) {
        setId = acc.getBladeSet(false);
        if (setId == 4) {
          setId = 4;
        } else if (isVirtual) {
          setId = GfMenuReference::getHomuraModeInBattle() == GfMenuReference::HOMURA_MODE_UNKNOWN_1 ? 3 : slot;
        } else {
          setId = GfDataBlade::isHikariCurrent() ? 3 : slot;
        }
      }
    } else {
      setId = -1;
    }
  }
  return setId;
}

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

bool GfMenuObjUtil::isBladeSelectable(u32 blade, const GfMenuBladeList *list) {
  if (blade == 0 || GfDataBlade::isActivateDriver(blade) || GfDataMercenaries::getTeamID(blade) != 0) {
    return false;
  }
  if (list == nullptr || list->getSize() == 0) {
    return true;
  }
  u32 i = 0;
  do {
    if (list->getContents(i).unknown00 == blade) {
      return false;
    }
    i++;
  } while (i < list->getSize());
  return true;
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

u32 GfMenuObjUtil::canRemoveBladeEx(u32 blade, u32 driver, const mm::mtl::FixedVector<u16, 422> *candidates) {
  if (blade == 0) {
    return 0;
  }
  u32 setDriver = GfDataBlade::getSetDriver(blade);
  u32 isAwakening = 0;
  if (driver == 1) {
    isAwakening = GfGameManager::isRexAwakening();
  }
  if (isScenarioBlade(blade) && !GfGameManager::isClearGame() && isAwakening == 0) {
    if (blade == 0x3f0) {
      if (GfDataBlade::getSetDriver(0x3f0) == 5) {
        return 1;
      }
    } else {
      if (setDriver == 0) {
        return 0;
      }
      if (blade != 0x3f3 && blade != 0x3f6 && setDriver == GfDataBlade::getCreator(blade)) {
        return 1;
      }
    }
  }
  if (setDriver == 0) {
    return 0;
  }
  if (driver != 0 && GfDataBlade::getSetDriver(blade) != driver && GfDataDriver::getBlade(setDriver, -1) == blade) {
    return 2;
  }
  mm::mtl::FixedVector<u16, 422> blades;
  if (!GfDataDriver::getListBlade(blades, setDriver)) {
    return 0;
  }
  for (u16 *it = blades.begin(); it != blades.end();) {
    if ((*it == 0x3eb && GfDataBlade::getDriverSetID(0x3ea) == 4) || (*it == 0x3ea && GfDataBlade::getDriverSetID(0x3ea) == 3)) {
      it = blades.erase(it);
    } else {
      it++;
    }
  }
  if (candidates != nullptr) {
    for (u16 *it = blades.begin(); it != blades.end();) {
      if (mm::mtl::find(candidates->begin(), candidates->end(), *it) != candidates->end()) {
        it = blades.erase(it);
      } else {
        it++;
      }
    }
  }
  return blades.size() < 2 ? 3 : 0;
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

bool GfMenuObjUtil::getImageParam(u32 type, u32 id, ImageParam &param, u32 index) {
  if (index >= 5) {
    return false;
  }
  u8 *bdat = GfDataBdat::getFP(type != 0 ? BDAT_MNU_BL_IMAGE_ID : BDAT_MNU_DR_IMAGE_ID);
  mm::mtl::FixStr<32> offsetX;
  mm::mtl::FixStr<32> offsetY;
  mm::mtl::FixStr<32> scale;
  if (index == 0) {
    offsetX = "offs_x";
    offsetY = "offs_y";
    scale = "scale";
  } else {
    offsetX.format("offs_x%1d", index + 1);
    offsetY.format("offs_y%1d", index + 1);
    scale.format("scale%1d", index + 1);
  }
  u32 row;
  if (type == 0) {
    u8 *list = GfDataBdat::getFP(BDAT_CHR_DR);
    if (id < static_cast<u32>(Bdat::getIdTop(list)) || id > static_cast<u32>(Bdat::getIdEnd(list))) {
      return false;
    }
    u16 still = Bdat::getVal(list, "Still", id).valueU16;
    row = Bdat::getIdTop(bdat);
    if (row > static_cast<u32>(Bdat::getIdEnd(bdat))) {
      return false;
    }
    do {
      if (Bdat::getVal(bdat, "icon_id", row).valueU16 == still) {
        break;
      }
      row++;
      if (row > static_cast<u32>(Bdat::getIdEnd(bdat))) {
        return false;
      }
    } while (true);
  } else {
    row = convMenuBladeID(id);
  }
  param.unknown00 = Bdat::getVal(bdat, offsetX.c_str(), row).valueS16;
  param.unknown02 = Bdat::getVal(bdat, offsetY.c_str(), row).valueS16;
  param.unknown04 = Bdat::getVal(bdat, scale.c_str(), row).valueF32;
  return true;
}

ui::UIStr GfMenuObjUtil::getName(const DataParamAcc &acc) {
  ui::UIStr name;
  u8 *bdat;
  u32 textId = 0;
  switch (acc.getObjType()) {
  case OBJECT_TYPE_DRIVER:
    if (GfDataDriver::getName(bdat, textId, acc.getValidDriverId())) {
      name.setupMstxt(bdat, textId);
    }
    break;
  case OBJECT_TYPE_BLADE:
    if (GfDataBlade::getName(bdat, textId, acc.getValidBdatId())) {
      name.setupMstxt(bdat, textId);
    }
    break;
  case OBJECT_TYPE_ENEMY:
    if (GfDataEnemy::getName(bdat, textId, acc.getValidBdatId())) {
      name.setupMstxt(bdat, textId);
    }
    break;
  case OBJECT_TYPE_NPC:
    if (GfDataNpc::getName(bdat, textId, acc.getValidBdatId())) {
      name.setupMstxt(bdat, textId);
    }
    break;
  }
  return name;
}

u16 GfMenuObjUtil::getMsgIDFromList(u32 bdat, u16 id) {
  u8 *list = GfDataBdat::getFP(bdat);
  if (list != nullptr) {
    return Bdat::getVal(list, "name", id).valueU16;
  }
  return 0;
}

bool GfMenuObjUtil::isBladeAchivementReleased(u32 blade) {
  if (blade != 0 && !GfDataBlade::isDummyBlade(blade)) {
    u32 level = 1;
    do {
      for (u32 line = 0; line < 10; line++) {
        if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 3) {
          return true;
        }
      }
    } while (level++ < 5);
  }
  return false;
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

SoundHandle GfMenuObjUtil::playJingle(u32 id) { return GfMenuSoundManager::playJingle(id); }

void GfMenuObjUtil::playVibration(fw::VibrationID id, f32 amplitude) { fw::PadManager::playVibration(ml::PadVibrationInfo(id, amplitude)); }

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

mm::Col3 GfMenuObjUtil::getElementColor(u32 combo) {
  u8 *bdat = Bdat::getFP("BTL_ElementalCombo");
  if (GfMenuBdat::isValidBdatID(bdat, combo)) {
    switch (Bdat::getVal(bdat, "Atr", combo).valueU8) {
    case 1:
      return mm::Col3(1.0f, 0.0f, 0.0f);
    case 2:
      return mm::Col3(0.0f, 96.0f / 255.0f, 1.0f);
    case 3:
      return mm::Col3(0.0f, 1.0f, 30.0f / 255.0f);
    case 4:
      return mm::Col3(151.0f / 255.0f, 64.0f / 255.0f, 6.0f / 255.0f);
    case 5:
      return mm::Col3(1.0f, 252.0f / 255.0f, 0.0f);
    case 6:
      return mm::Col3(0.0f, 1.0f, 216.0f / 255.0f);
    case 7:
      return mm::Col3(1.0f, 222.0f / 255.0f, 0.0f);
    case 8:
      return mm::Col3(144.0f / 255.0f, 0.0f, 1.0f);
    }
  }
  return mm::Col3::black;
}

int GfMenuObjUtil::getDriverClassBuffRatio(u32 driverClass, u32 index) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_CLASS);
  if (bdat == nullptr) {
    return 0;
  }
  u32 count = 0;
  u32 i = 0;
  int value;
  do {
    do {
      if (i >= sizeof(unknown079) / sizeof(unknown079[0])) {
        return 0;
      }
      if (i == 3 || i == 4) {
        value = Bdat::getVal(bdat, unknown079[i], driverClass).valueS8;
      } else {
        value = Bdat::getVal(bdat, unknown079[i], driverClass).valueU8;
      }
      i++;
    } while (value == 0);
  } while (count++ != index);
  return value < 0 ? 0 : value;
}

u32 GfMenuObjUtil::getDriverClassBuffType(u32 driverClass, u32 index) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_CLASS);
  if (bdat == nullptr) {
    return 0;
  }
  u32 count = 0;
  u32 i = 0;
  int value;
  do {
    do {
      if (i >= sizeof(unknown079) / sizeof(unknown079[0])) {
        return 0;
      }
      if (i == 3 || i == 4) {
        value = Bdat::getVal(bdat, unknown079[i], driverClass).valueS8;
      } else {
        value = Bdat::getVal(bdat, unknown079[i], driverClass).valueU8;
      }
      i++;
    } while (value == 0);
  } while (count++ != index);
  return value < 0 && i - 4 < 2 ? i + 2 : i;
}

u32 GfMenuObjUtil::getDriverClassBuffLv(u32 driverClass, u32 index) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_CLASS);
  if (bdat == nullptr) {
    return 0;
  }
  u32 count = 0;
  for (u32 i = 0; i < sizeof(unknown079) / sizeof(unknown079[0]); i++) {
    if (Bdat::getVal(bdat, unknown079[i], driverClass).valueS8 != 0) {
      if (count == index) {
        return Bdat::getVal(bdat, unknown080[i], driverClass).valueU8;
      }
      count++;
    }
  }
  return 0;
}

bool GfMenuObjUtil::isQuestCompleted(QuestID quest) { return GfQuestInfo::isQuestFin(quest); }

bool GfMenuObjUtil::getMissionInfo(u32 mission, MissionInfo &info) {
  if (mission == 0) {
    return false;
  }
  info.unknown00 = GfDataMercenaries::getMissionCategory(mission);
  info.unknown08 = GfDataMercenaries::getMissionMapID(mission);
  info.unknown10 = GfDataMercenaries::getTeamIDByMissionID(mission);
  info.unknown04 = GfDataMercenaries::getMissionRewardID(mission);
  info.unknown0c = 0;
  switch (GfDataMercenaries::getMissionFlag(mission)) {
  case 1:
    info.unknown0c |= 2;
    break;
  case 2:
    info.unknown0c |= 4;
    break;
  case 3:
    info.unknown0c |= 8;
    break;
  }
  if (GfDataMercenaries::isNewMission(mission)) {
    info.unknown0c |= 1;
  }
  info.unknown14 = GfDataMercenaries::getFieldSkill1(mission);
  info.unknown18 = GfDataMercenaries::getFieldSkill2(mission);
  info.unknown1c = GfDataMercenaries::getFieldSkill3(mission);
  return true;
}

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

const mm::Col3 &GfMenuObjUtil::getPresetColor(const char *name) {
  static mm::Col3 color;
  color = mm::Col3(0.0f, 0.0f, 0.0f);
  mm::Col4 libraryColor;
  if (ui::UIColorLibrary::get()->find(name, libraryColor)) {
    color.r = libraryColor.r;
    color.g = libraryColor.g;
    color.b = libraryColor.b;
  }
  return color;
}

void GfMenuObjUtil::setColMulandAdd(u32 handle, const char *color) {
  ui::UIObjectAcc objectAcc(handle);
  if (objectAcc.isValid()) {
    mm::mtl::FixStr<64> name;
    name.format("%s_mul", color);
    objectAcc.setMulColor(name.c_str());
    name.format("%s_add", color);
    objectAcc.setAddColor(name.c_str());
  }
}

void GfMenuObjUtil::setColDefault(u32 handle) {
  ui::UIObjectAcc objectAcc(handle);
  if (objectAcc.isValid()) {
    objectAcc.loadDefColor();
  }
}

void GfMenuObjUtil::createDockPlugin(u32 handle, u32 target, u32 dockType, const mm::Pnt<s16> &offset, u32 alignType) {
  ui::UIObjectDockPlugin *plugin = ui::UIObjectDockPlugin::create(handle, offset.x, offset.y, target);
  if (plugin != nullptr) {
    plugin->unknown24 = dockType;
    plugin->unknown28 = alignType;
    plugin->release();
  }
}

void GfMenuObjUtil::createDockPluginEx(u32 handle, u32 target, u32 dockType, const DockingOption &option) {
  ui::UIObjectDockPlugin *plugin = ui::UIObjectDockPlugin::create(handle, option.unknown04.x, option.unknown04.y, target);
  if (plugin != nullptr) {
    plugin->unknown24 = dockType;
    plugin->unknown28 = option.unknown00;
    plugin->unknown30 = option.unknown08;
    plugin->release();
  }
}

void GfMenuObjUtil::createVScrollBarPlugin(u32 handle, ui::UIListInfoBase *list, const char *barName, bool isScaleEnable) {
  ui::UIObjectScrollBarPlugin *plugin = ui::UIObjectScrollBarPlugin::create(handle, 0, list, barName);
  if (plugin != nullptr) {
    plugin->setScaleEnable(isScaleEnable);
    plugin->release();
  }
}

void GfMenuObjUtil::createHScrollBarPlugin(u32 handle, ui::UIListInfoBase *list, const char *barName) {
  ui::UIObjectScrollBarPlugin *plugin = ui::UIObjectScrollBarPlugin::create(handle, 1, list, barName);
  if (plugin != nullptr) {
    plugin->release();
  }
}

void GfMenuObjUtil::createFollowDispPlugin(u32 handle, u32 target) {
  ui::UIObjectDispPlugin *plugin = ui::UIObjectDispPlugin::create(handle);
  if (plugin != nullptr) {
    plugin->setFollowObjHandle(target);
    plugin->release();
  }
}

void GfMenuObjUtil::createSyncPlugin(u32 handle, u32 target, u32 flags) {
  ui::UIObjectSyncPlugin *plugin = ui::UIObjectSyncPlugin::create(handle);
  if (plugin != nullptr) {
    plugin->setTargetObject(target);
    plugin->setTargetFlag(flags);
    plugin->release();
  }
}

void GfMenuObjUtil::createNumberPlugin(u32 handle, int number) {
  ui::UIObjectNumberPlugin *plugin = ui::UIObjectNumberPlugin::create(handle);
  if (plugin != nullptr) {
    plugin->setMin(number);
    plugin->setMax(number);
    plugin->setNumber(number);
    plugin->release();
  }
}

const GfMenuObjUtil::unknown001 *GfMenuObjUtil::getParamMenu() {
  fw::ParamManager *manager = fw::ParamManager::get();
  if (manager != nullptr) {
    const fw::ParamList *list = manager->unknown408[20].operator->();
    if (list->unknown0c != 0 && list->unknown10 != nullptr) {
      return static_cast<const unknown001 *>(list->unknown10[0].param);
    }
  }
  return nullptr;
}

f32 GfMenuObjUtil::getPresetCtrlTime(u32 preset) {
  const unknown001 *param = getParamMenu();
  if (param != nullptr) {
    switch (preset) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return param->unknown00;
    case 6:
      return param->unknown04;
    }
  }
  return 0.5f;
}

int GfMenuObjUtil::setCommonFadeIn(u32 handle, u32 fade, u8 type) {
  if (handle == 0) {
    return -1;
  }
  switch (type) {
  case 0: {
    CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = getPresetCtrlTime(6);
    param.unknown04 = fade;
    return startCtrl(handle, param, nullptr);
  }
  case 1: {
    CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = fade;
    param.unknown11 = true;
    return startCtrl(handle, param, nullptr);
  }
  case 2: {
    CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = fade;
    param.unknown11 = true;
    return startCtrl(handle, param, nullptr);
  }
  }
  return -1;
}

int GfMenuObjUtil::setCommonFadeOut(u32 handle, u32 fade, u8 type) {
  if (handle == 0) {
    return -1;
  }
  switch (type) {
  case 0: {
    CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = getPresetCtrlTime(6);
    param.unknown04 = fade;
    return startCtrl(handle, param, nullptr);
  }
  case 1: {
    CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = fade;
    param.unknown11 = true;
    return startCtrl(handle, param, nullptr);
  }
  case 2: {
    CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = fade;
    param.unknown11 = true;
    return startCtrl(handle, param, nullptr);
  }
  }
  return -1;
}

void GfMenuObjUtil::setPresetCtrl_Fadein(u32 preset, CtrlParam &param, int slot) {
  param.unknown00 = getPresetCtrlTime(preset);
  param.unknown08 |= 1;
  switch (preset) {
  case 0:
    param.unknown08 |= 0x100;
    break;
  case 1:
    param.unknown08 |= 0x200;
    break;
  case 2:
    param.unknown08 |= 0x400;
    break;
  case 3:
    param.unknown08 |= 0x800;
    break;
  case 5:
    param.unknown08 = 0x200000 | 1;
    // Falls through to case 6 in the original (the game stores the flags twice for preset 5).
  case 6:
    param.unknown08 |= 1;
    break;
  }
  param.unknown0c = getPresetCtrlCurve(preset);
  param.unknown11 = true;
  param.unknown18 = slot;
}

void GfMenuObjUtil::setPresetCtrl_Fadeout(u32 preset, CtrlParam &param, int slot) {
  param.unknown00 = getPresetCtrlTime(preset);
  param.unknown08 |= 2;
  switch (preset) {
  case 0:
    param.unknown08 |= 0x1000;
    break;
  case 1:
    param.unknown08 |= 0x2000;
    break;
  case 2:
    param.unknown08 |= 0x4000;
    break;
  case 3:
    param.unknown08 |= 0x8000;
    break;
  case 5:
    param.unknown08 = 0x400000 | 2;
    break;
  case 6:
    param.unknown08 |= 2;
    break;
  }
  param.unknown0c = getPresetCtrlCurve(preset);
  param.unknown14 |= 2;
  param.unknown18 = slot;
}

int GfMenuObjUtil::startPresetCtrl(u32 handle, const PresetCtrlParam &param) {
  CtrlParam ctrl;
  if (param.unknown04 == 0) {
    setPresetCtrl_Fadein(param.unknown00, ctrl, param.unknown08);
  } else if (param.unknown04 == 1) {
    setPresetCtrl_Fadeout(param.unknown00, ctrl, param.unknown08);
  } else {
    return -1;
  }
  if (param.unknown0d) {
    ctrl.unknown14 |= 4;
  }
  if (param.unknown0c) {
    ctrl.unknown14 &= ~4;
    ctrl.unknown14 |= 1;
  }
  ctrl.unknown04 = param.unknown10;
  return startCtrl(handle, ctrl, param.unknown18);
}

f32 GfMenuObjUtil::getCtrlMotionTime(const char *name, const char *motion) {
  if (name != nullptr && motion != nullptr) {
    ui::UIMotionData *data = ui::UIMotionLibrary::get()->find(name);
    if (data != nullptr) {
      return data->getMotionLength(data->searchMotion(motion));
    }
    return -1.0f;
  }
  return 0.0f;
}

void GfMenuObjUtil::changeCursorTarget(ui::UICtrlCursorSelect *cursor, u32 handle, const char *format) {
  if (cursor != nullptr && cursor->unknown58 != nullptr) {
    ui::UISelectObjList *list = cursor->unknown58;
    list->clear();
    list->pickupObject(handle, format, 1);
    list->getSize();
  }
}

void GfMenuObjUtil::changeCursorTarget(ui::UICtrlCursorSelect *cursor, u32 handle, const char **names, u16 count) {
  if (cursor != nullptr && cursor->unknown58 != nullptr) {
    ui::UISelectObjList *list = cursor->unknown58;
    list->clear();
    if (names != nullptr) {
      ui::UIObjectAcc objectAcc(handle);
      for (u16 i = 0; i < count; i++) {
        u32 child = objectAcc.searchChild(names[i]);
        if (child != 0) {
          list->addContents(child);
        }
      }
    }
    list->getSize();
  }
}

bool GfMenuObjUtil::getScreenPos(mm::Vec3 &screenPos, const mm::Vec3 &position) { return util::getScreenPos(screenPos, position); }

void GfMenuObjUtil::convViewSpace(mm::Vec3 &viewPos, const mm::Vec3 &position) {
  const mm::Mat44 &view = GfInfo::m_viewMat;
  mm::Vec3 result;
  result.x = position.x * view.rows[0][0] + position.y * view.rows[1][0] + position.z * view.rows[2][0] + view.rows[3][0];
  result.y = position.x * view.rows[0][1] + position.y * view.rows[1][1] + position.z * view.rows[2][1] + view.rows[3][1];
  result.z = position.x * view.rows[0][2] + position.y * view.rows[1][2] + position.z * view.rows[2][2] + view.rows[3][2];
  viewPos = result;
}

void GfMenuObjUtil::placeObjectHLeft(u32 handle, const char *format, u32 count, const mm::Pnt<s16> &pos, u32 interval) {
  mm::mtl::FixStr<32> name;
  u32 x = static_cast<u16>(pos.x);
  s16 y = pos.y;
  for (int i = 0; i < static_cast<int>(count); i++, x += interval) {
    name.format(format, i + 1);
    ui::UIObjectAcc acc(handle, name.c_str());
    acc.setPosCenter(mm::Pnt<s16>(x, y));
  }
}

void GfMenuObjUtil::placeObjectHRatio(u32 handle, u32 target, f32 ratio, s16 margin) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc targetAcc(target);
  mm::Rect<s16> rect;
  mm::Rect<s16> targetRect;
  acc.getRect(rect, ui::UIObjectAcc::RECT_SCALED);
  targetAcc.getRect(targetRect, ui::UIObjectAcc::RECT_SCALED);
  targetRect.width += margin;
  mm::Pnt<s16> pos;
  targetAcc.getPosCenter(pos);
  if (rect.width < targetRect.width) {
    pos.x = rect.x + rect.width / 2;
  } else {
    pos.x = rect.x + targetRect.width / 2 + static_cast<int>((rect.width - targetRect.width) * ratio);
  }
  targetAcc.setPosCenter(pos);
}

QuestID GfMenuObjUtil::getCurrentQuest(u32 type) {
  QuestID quest;
  switch (type) {
  case 0:
    quest = GfQuestManager::getProgressCurrentQuest(QTYPE_MAIN);
    break;
  case 1:
    quest = GfQuestManager::getProgressCurrentQuest(QTYPE_NORMAL);
    if (quest.empty()) {
      quest = GfQuestManager::getProgressCurrentQuest(QTYPE_BLADE);
    }
    break;
  }

  if (!quest.empty() && GfQuestInfo::isQuestOrder(quest)) {
    return quest;
  }
  return QuestID();
}

bool GfMenuObjUtil::setPointSpeedRate(ui::UIObjectAcc acc, f32 rate) {
  u32 input = ui::UIInputManager::get()->searchInputHandle(acc.unknown10);
  if (input != 0) {
    ui::UIInputLayer *layer = ui::UIInputManager::get()->getInputLayer(input);
    if (layer != nullptr) {
      ui::UIInputPointer *pointer = layer->castUIInputPointer();
      if (pointer != nullptr) {
        pointer->unknown258 = rate;
        return true;
      }
    }
  }
  return false;
}

} // namespace gf
