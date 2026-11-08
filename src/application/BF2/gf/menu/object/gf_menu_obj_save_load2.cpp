#include "gf/menu/object/gf_menu_obj_save_load2.h"

#include "gf/data/gf_data_save.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/plugin/ui_object_text_plugin.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x35;

GfMenuObjSaveLoad2::GfMenuObjSaveLoad2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(this), unknown2c0(-1), unknown2c4(0), unknown2c8(nullptr), unknown2d0(nullptr), unknown2d8(nullptr), unknown2e0(nullptr), unknown2e8(nullptr),
      unknown2f0(nullptr), unknown2f8(nullptr), unknown300(nullptr) {
  for (int i = 0; i < 3; i++) {
    unknown308[i] = nullptr;
  }
}

GfMenuObjSaveLoad2::~GfMenuObjSaveLoad2() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown2c8);
  mm::mtl::safeRelease(unknown2d0);
  mm::mtl::safeRelease(unknown2d8);
  mm::mtl::safeRelease(unknown2e0);
  mm::mtl::safeRelease(unknown2e8);
  mm::mtl::safeRelease(unknown2f0);
  mm::mtl::safeRelease(unknown2f8);
  mm::mtl::safeRelease(unknown300);
  for (int i = 0; i < 3; i++) {
    unknown308[i] = nullptr;
  }
}

void GfMenuObjSaveLoad2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSaveLoad2::update() {
  unknown30.unknown003();
  GfMenuObject::update();
}

void GfMenuObjSaveLoad2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown001), layerParam);
}

void GfMenuObjSaveLoad2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

bool GfMenuObjSaveLoad2::seqSave() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  disableInput(main.unknown10);
  GfMenuObjMainMenu2::setCloseKeyEnable(false);
  unknown2c0 = GfReqCommand::reqSave(SAVESLOT_DEFAULT);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjSaveLoad2::seqSaveWait() {
  if (GfReqManager::isValid(unknown2c0)) {
    return false;
  }
  GfMenuObjUtil::playSE(8);
  GfMenuObjFade::dispSaving(false, 0);
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_main"));
  refreshSave(main, 1);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  ui::UIObjectAcc input(unknown18, "LAY_main");
  enableInput(input.unknown10);
  unknown2c0 = -1;
  return true;
}

bool GfMenuObjSaveLoad2::seqSaveWaitToClose() {
  if (GfReqManager::isValid(unknown2c0)) {
    return false;
  }
  GfMenuObjUtil::playSE(8);
  GfMenuObjFade::dispSaving(false, 0);
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_main"));
  refreshSave(main, 1);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  unknown140(main.unknown10, GfMenuTypes::unknown003_34, 0, 0.0f);
  unknown2c0 = -1;
  return true;
}

int GfMenuObjSaveLoad2::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown002(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r_early");
    param.unknown04 = 1;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjSaveLoad2::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  switch (type) {
  case 0:
    ctrl = GfMenuObjUtil::unknown003(handle);
    break;
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_r_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    param.unknown11 = true;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
    break;
  }
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjSaveLoad2>(const mm::mtl::Delegate<bool()> *);
