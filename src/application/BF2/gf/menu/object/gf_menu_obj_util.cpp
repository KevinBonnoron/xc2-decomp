#include "gf/menu/object/gf_menu_obj_util.h"

#include "bdat.h"
#include "framework/sound/sound_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_party.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_pnt.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {
struct GF_OBJ_HANDLE;

struct IconTable {
  u32 key;
  u32 icon;
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

static const u16 s_commonSes[] = {MENU_SE_DECIDE, MENU_SE_CANCEL, MENU_SE_INVALID};

u32 GfMenuObjUtil::getBtnIconNumber(u32 button) {
  for (u32 i = 0; i < sizeof(s_buttonIcons) / sizeof(s_buttonIcons[0]); i++) {
    if ((button & s_buttonIcons[i].key) != 0) {
      return s_buttonIcons[i].icon;
    }
  }
  return ICON_NONE;
}

u32 GfMenuObjUtil::getPadSelectIconNumber(u32 select) {
  for (u32 i = 0; i < sizeof(s_padSelectIcons) / sizeof(s_padSelectIcons[0]); i++) {
    if (s_padSelectIcons[i].key == select) {
      return s_padSelectIcons[i].icon;
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
    GfMenuObject::setText(acc.handle, id);
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
    return acc.handle;
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

u16 GfMenuObjUtil::getMsgIDFromList(u32 bdat, u16 id) {
  u8 *list = GfDataBdat::getFP(bdat);
  if (list != nullptr) {
    return Bdat::getVal(list, "name", id).valueU16;
  }
  return 0;
}

bool GfMenuObjUtil::checkCCStart(GfMenuCallContext *context) { return context != nullptr && !context->isActive(); }

bool GfMenuObjUtil::checkCCNext(GfMenuCallContext *context, u32 menu) { return context != nullptr && context->menu == menu; }

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

} // namespace gf
