#include "gf/menu/object/gf_menu_obj_char_select.h"

#include "gf/game/gf_game_util.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x61;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: customize layer; original name unknown.
constexpr u16 unknown004 = 0x27;

void GfMenuObjCharSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCharSelect::registOpenCustomizeParam(const OpenCustomizeParam &param) {
  GfMenuTypes::Param layerParam;
  unknown003 &data = layerParam.get<unknown003>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(unknown004, layerParam);
}

void GfMenuObjCharSelect::openBladeCustomize(u32 handle, u32 blade, u16 group) {
  OpenCustomizeParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenCustomizeParam(param);
  changeFSSubLayer(handle, group, unknown004, true);
}

void GfMenuObjCharSelect::openDriverCustomize(u32 handle, u32 driver, u16 group) {
  OpenCustomizeParam param;
  param.unknown00 = 0;
  param.unknown04 = driver;
  registOpenCustomizeParam(param);
  changeFSSubLayer(handle, group, unknown004, true);
}

bool GfMenuObjCharSelect::seqSpHikariToHomura() {
  GfGameUtil::changeHikariCurrent(false);
  return true;
}

bool GfMenuObjCharSelect::seqSpHomuraToHikari() {
  GfGameUtil::changeHikariCurrent(true);
  return true;
}

void GfMenuObjCharSelect::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjCharSelect::returnSubMenu() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

bool GfMenuObjCharSelect::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

int GfMenuObjCharSelect::setFadeOut(u32 handle, u32 type) {
  int ctrl = unknown005(handle, type);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCharSelect::setFadeOutSub(u32 handle, u32 type) { unknown005(handle, type); }

int GfMenuObjCharSelect::setFadeIn(u32 handle, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  if (type == 0) {
    param.unknown08 = 1;
    param.unknown00 = GfMenuObjUtil::getPresetCtrlTime(6);
    param.unknown0c = 1;
  } else {
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_lr";
    param.unknown58 = type == 2 ? "fade_in_r_early" : "fade_in_l_early";
    param.unknown11 = true;
  }
  param.unknown04 = 1;
  int ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCharSelect::dispOnCopyChar(ui::UIObjectAcc &acc, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  if (type == 0) {
    u32 handle = acc.searchChild("LAY_char_dr_move");
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::openDrStatus(1, -1);
  } else {
    u32 handle = acc.searchChild("LAY_char_bl_move");
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::openBlStatus(1, -1);
  }
}

void GfMenuObjCharSelect::dispOffCopyChar(ui::UIObjectAcc &acc, u32 type) {
  GfMenuObjUtil::CtrlParam param;
  if (type == 0) {
    u32 handle = acc.searchChild("LAY_char_dr_move");
    param.unknown004("warp_r");
    param.unknown11 = true;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::closeDrStatus();
  } else {
    u32 handle = acc.searchChild("LAY_char_bl_move");
    param.unknown004("warp_r");
    param.unknown11 = true;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(handle, param, nullptr);
    GfMenuObjCmnStatus::closeBlStatus();
  }
}

void GfMenuObjCharSelect::update() {
  unknown430.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjCharSelect::seqStreamWaitStatDrBefore() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
  int ctrl = GfMenuObjUtil::getCtrlID(move.unknown10);
  if (ctrl != -1) {
    GfMenuObjUtil::stopCtrl(ctrl);
  }
  return true;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBlBefore() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
  int ctrl = GfMenuObjUtil::getCtrlID(move.unknown10);
  if (ctrl != -1) {
    GfMenuObjUtil::stopCtrl(ctrl);
  }
  return true;
}

bool GfMenuObjCharSelect::seqConfSpecialWaitError() {
  if (!GfMenuManager::isOpenCommonWindow()) {
    unknown430.unknown002(&GfMenuObjCharSelect::seqReturn);
    unknown6c0 = false;
    return true;
  }
  return false;
}

bool GfMenuObjCharSelect::seqReturn() {
  ui::UIObjectAcc acc(unknown18, "LAY_char");
  unknown140(acc.unknown10, 0x107, 0, 0.0f);
  return true;
}

bool GfMenuObjCharSelect::seqReturnChange() {
  ui::UIObjectAcc acc(unknown18, "LAY_char");
  unknown158(acc.unknown10, 0x107, 1, 0.0f);
  return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeDr() {
  SCOM_NIA_BLADE::create(false);
  return true;
}

void GfMenuObjCharSelect::dispOnChar(u32 type) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    dispOnCopyChar(acc, type);
  }
}

void GfMenuObjCharSelect::dispOffChar(u32 type) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid()) {
    dispOffCopyChar(acc, type);
  }
}

void GfMenuObjCharSelect::execCharPosScale(u32 type) { unknown159(unknown001, 0x109, type); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjCharSelect, 8>>(const mm::mtl::Delegate<bool()> *);
