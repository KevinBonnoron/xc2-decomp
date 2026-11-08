#include "gf/menu/object/gf_menu_obj_char_select.h"

#include "gf/game/gf_game_util.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x61;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: customize layer; original name unknown.
constexpr u16 unknown004 = 0x27;
// Inferred role: busy flags of the stream waits; original type name unknown.
struct unknown006 {
  bool unknown00; // Inferred role: character stream wait busy flag; original member name unknown.
  bool unknown01; // Inferred role: selection stream wait busy flag; original member name unknown.
};
// Inferred role: busy flags of the stream waits; original name unknown.
static unknown006 unknown007;
// Inferred role: layer names of the driver and the three blades of the character select; original name unknown.
static const char *const unknown008[4] = {"LAY_char_dr", "LAY_char_bl@01", "LAY_char_bl@02", "LAY_char_bl@03"};

GfMenuObjCharSelect::GfMenuObjCharSelect(u32 handle)
    : GfMenuObject(handle), unknown48(nullptr), unknown3f8(0), unknown3fc(0), unknown428(0), unknown430(this), unknown6c0(false), unknown6d8(0), unknown6e8(-1), unknown740(true), unknown741(false),
      unknown742(0), unknown744(0), unknown748(0xff), unknown768(false) {
  unknown400.assign(-1);
  unknown28 = nullptr;
  unknown30.assign(nullptr);
  unknown6e0 = GfMenuCallContext::create();
  unknown750.assign(-1);
  unknown007.unknown00 = false;
  unknown007.unknown01 = false;
}

GfMenuObjCharSelect::~GfMenuObjCharSelect() {
  mm::mtl::safeRelease(unknown6e0);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown30[0]);
  mm::mtl::safeRelease(unknown30[1]);
  mm::mtl::safeRelease(unknown30[2]);
}

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

void GfMenuObjCharSelect::setupCharSubMenuBl(ui::UIObjectAcc &acc, u32 blade, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_sub_menu_icon_bl@%02d", index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  icon.setImageIndex(getMenuIconID(blade));
  icon.setDisp(true);
}

void GfMenuObjCharSelect::setupCharSubMenuHana(ui::UIObjectAcc &acc, u32 blade, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_sub_menu_icon_hana@%02d", index + 1);
  ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
  icon.setImageIndex(getMenuIconID(blade));
  icon.setDisp(true);
}

void GfMenuObjCharSelect::setupCharSelectCopy(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild("IMG_char_dr_move_img"), 0x1c, 0, false);
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_char_bl_move_img"), 0x36, 0, false);
  ui::UIObjectAcc(acc.searchChild("IMG_char_bl_move_img")).setStreamImage2nd();
  GfMenuAdapterManager::endAddAfter();
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

int GfMenuObjCharSelect::getEquipBladeNum(u32 driver, const mm::mtl::FixedArray<DriverData, 5> &party) {
  int num = 0;
  for (u32 i = 0; i < 5; i++) {
    if (party[i].unknown00 == driver) {
      for (u32 j = 0; j < 3; j++) {
        num += GfMenuObjUtil::isValidBlade(party[i].unknown04[j]);
      }
    }
  }
  return num;
}

int GfMenuObjCharSelect::setDriverPos(ui::UIObjectAcc &acc, mm::mtl::FixedArray<DriverData, 5> &party, u32 driver) {
  int bladeNum = getEquipBladeNum(driver, party);
  ui::UIObjectAcc status(acc.searchChild("LAY_status_dr"));
  ui::UIObjectAcc normal(acc.searchChild("LAY_char_dr"));
  ui::UIObjectAcc solo(acc.searchChild("LAY_char_dr_solo"));
  if (bladeNum == 0) {
    normal.setDisp(false);
    solo.setDisp(true);
    acc.setLayout(status.unknown10, "driver_index_layout_solo");
  } else {
    normal.setDisp(true);
    solo.setDisp(false);
    acc.setLayout(status.unknown10, "driver_index_layout_normal");
  }
  return bladeNum;
}

void GfMenuObjCharSelect::setCharOffset(ui::UIObjectAcc &acc, const mm::mtl::FixedArray<DriverData, 5> &party, u32 driver) {
  for (u32 i = 0; i < 5; i++) {
    if (party[i].unknown00 == driver) {
      setCharPosScale(0, driver, 0, getEquipBladeNum(driver, party) == 0);
      for (u32 j = 0; j < 3; j++) {
        u32 blade = party[i].unknown04[j];
        if (GfMenuObjUtil::isValidBlade(blade)) {
          setCharPosScale(1, blade, j + 1, false);
        }
      }
    }
  }
}

bool GfMenuObjCharSelect::seqStreamWaitStatDr() {
  unknown007.unknown00 = true;
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc image(acc.searchChild("IMG_char_dr_move_img"));
  if (image.isStreaming()) {
    return false;
  }
  ui::UIObjectAcc move(acc.searchChild("LAY_char_dr_move"));
  setFadeIn(move.unknown10, 0);
  return true;
}

bool GfMenuObjCharSelect::seqStreamWaitStatBl() {
  unknown007.unknown00 = true;
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_move_img"));
  if (image.isStreaming()) {
    return false;
  }
  ui::UIObjectAcc move(acc.searchChild("LAY_char_bl_move"));
  setFadeIn(move.unknown10, 0);
  return true;
}

bool GfMenuObjCharSelect::seqSpNiaChangeBl() {
  SCOM_NIA_BLADE::create(true);
  for (u32 i = 0; i < unknown28->getSize(); i++) {
    if (unknown28->getContents(i).unknown00 == 2 && i < 3) {
      GfMenuObjPartyStatus::memberChange(i + 1, 0);
      break;
    }
  }
  return true;
}

void GfMenuObjCharSelect::adjustBladeList(mm::mtl::FixedArray<DriverData, 5> &party, mm::mtl::FixedVector<u16, 422> &blades, mm::mtl::FixedArray<GfMenuBladeList *, 3> &lists, u32 driver) {
  u32 index = 0;
  while (party[index].unknown00 != driver) {
    if (++index == 5) {
      return;
    }
  }
  for (u32 i = 0; i < 3; i++) {
    u32 blade = party[index].unknown04[i];
    lists[i]->clear();
    if (blade != 0 && GfMenuObjUtil::isValidBlade(blade)) {
      MenuBladeInfo info;
      info.unknown00 = blade;
      info.unknown04 = driver;
      lists[i]->addContents(info);
      lists[i]->setIndex(0);
    }
  }
}

bool GfMenuObjCharSelect::seqStreamWaitSelectBefore() {
  ui::UIObjectAcc acc(unknown18);
  int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), unknown3a8);
  for (u32 i = 0; i < 4; i++) {
    const char *name = "LAY_char_dr_solo";
    if (i != 0 || bladeNum != 0) {
      name = unknown008[i];
    }
    ui::UIObjectAcc layer(acc.searchChild(name));
    int ctrl = GfMenuObjUtil::getCtrlID(layer.unknown10);
    if (ctrl != -1) {
      GfMenuObjUtil::stopCtrl(ctrl);
    }
  }
  return true;
}

bool GfMenuObjCharSelect::seqStreamWaitSelect() {
  unknown007.unknown01 = true;
  ui::UIObjectAcc acc(unknown18);
  int bladeNum = getEquipBladeNum(GfMenuReference::getReferenceDriverID(0), unknown3a8);
  {
    ui::UIObjectAcc image(acc.searchChild(bladeNum == 0 ? "IMG_char_dr_img_solo" : "IMG_char_dr_img"));
    if (image.isStreaming()) {
      return false;
    }
  }
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_img@01"));
    if (image.isStreaming()) {
      return false;
    }
  }
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_img@02"));
    if (image.isStreaming()) {
      return false;
    }
  }
  {
    ui::UIObjectAcc image(acc.searchChild("IMG_char_bl_img@03"));
    if (image.isStreaming()) {
      return false;
    }
  }
  for (u32 i = 0; i < 4; i++) {
    const char *name = "LAY_char_dr_solo";
    if (i != 0 || bladeNum != 0) {
      name = unknown008[i];
    }
    ui::UIObjectAcc layer(acc.searchChild(name));
    setFadeIn(layer.unknown10, 0);
  }
  return true;
}

bool GfMenuObjCharSelect::seqWaitSelect() {
  if (unknown007.unknown01) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc layer(acc.searchChild("LAY_char"));
  if (!unknown741) {
    GfMenuObjMainMenu2::openCharChange(layer.unknown10, 3, false);
  }
  enableInput(layer.unknown10);
  GfMenuObjMainMenu2::setSystemKeyEnable(true);
  return true;
}

bool GfMenuObjCharSelect::getCharBusy() { return unknown007.unknown00; }

bool GfMenuObjCharSelect::getSelectBusy() { return unknown007.unknown01; }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjCharSelect, 8>>(const mm::mtl::Delegate<bool()> *);
