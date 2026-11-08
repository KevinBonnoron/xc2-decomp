#include "gf/menu/object/gf_menu_obj_mainmenu.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMainMenu::GfMenuObjMainMenu(u32 handle)
    : GfMenuObject(handle), unknown68(this), unknown300(nullptr), unknown308(0), unknown310(0), unknown318(nullptr), unknown320(nullptr), unknown328(0), unknown350(0xffffffff), unknown354(0) {}

GfMenuObjMainMenu::~GfMenuObjMainMenu() { ; }

void GfMenuObjMainMenu::finalize() {
  mm::mtl::safeRelease(unknown320);
  mm::mtl::safeRelease(unknown318);
  mm::mtl::safeRelease(unknown300);
  GfMenuObject::finalize();
}

void GfMenuObjMainMenu::update() {
  unknown68.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjMainMenu::seqStartOpen() {
  unknown2f8 = -1;
  suspendInput();
  return true;
}

bool GfMenuObjMainMenu::seqAppearPhase1() {
  if (unknown2f8 == -1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    ui::UIObjectAcc acc(unknown18);
    unknown2f8 = GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2f8)) {
    return false;
  }
  unknown2f8 = -1;
  return true;
}

bool GfMenuObjMainMenu::seqAppearPhase2() {
  if (unknown2f8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_title");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2f8 = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2f8)) {
    return false;
  }
  unknown2f8 = -1;
  return true;
}

bool GfMenuObjMainMenu::seqAppearPhase3() {
  if (unknown300 == nullptr) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam param;
    if (unknown300 == nullptr) {
      unknown300 = GfMenuCallContext::create();
    }
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      param.unknown04 = layerParam.get<unknown001>().unknown00;
      removeFSLayerParam(unknown20);
    }
    param.unknown00 = 1;
    GfMenuObjCommonJog::open(unknown300, param);
    GfMenuObject::setCallContextEventHandler(unknown300, acc.unknown10);
  }
  GfMenuCallContext::GfMenuResult result;
  return !unknown300->unknown18.empty() && unknown300->popResult(result) && result.unknown04 == 0;
}

bool GfMenuObjMainMenu::seqAppearPhase4() {
  if (unknown2f8 == -1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    ui::UIObjectAcc acc(unknown18);
    unknown2f8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_info_top"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2f8)) {
    return false;
  }
  unknown2f8 = -1;
  return true;
}

bool GfMenuObjMainMenu::seqEndCommon() {
  resumeInput();
  return true;
}

void GfMenuObjMainMenu::suspendInput() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::disableInput(acc.unknown10);
  GfMenuObject::disableFSSwitching();
  if (unknown300 != nullptr) {
    GfMenuObjCommonJog::disable(unknown300);
  }
}

void GfMenuObjMainMenu::resumeInput() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::enableInput(acc.unknown10);
  GfMenuObject::enableFSSwitching();
  if (unknown300 != nullptr) {
    GfMenuObjCommonJog::enable(unknown300);
  }
}

bool GfMenuObjMainMenu::seqStartCommon() {
  suspendInput();
  return true;
}

bool GfMenuObjMainMenu::seqCloseJog() {
  if (unknown300 != nullptr) {
    GfMenuObjCommonJog::close(unknown300);
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown300->unknown18.empty() && unknown300->popResult(result) && result.unknown04 == 1) {
    unknown300->reset();
    return true;
  }
  return false;
}

bool GfMenuObjMainMenu::seqOpenJog() {
  if (!unknown300->isActive()) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam param;
    param.unknown00 = unknown310;
    GfMenuObjCommonJog::open(unknown300, param);
    GfMenuObject::setCallContextEventHandler(unknown300, acc.unknown10);
  }
  GfMenuCallContext::GfMenuResult result;
  return !unknown300->unknown18.empty() && unknown300->popResult(result) && result.unknown04 == 0;
}

bool GfMenuObjMainMenu::seqSwapPhase2() { return true; }

} // namespace gf
