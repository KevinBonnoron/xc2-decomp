#include "gf/menu/object/gf_menu_obj_dr_custom_top.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"
#include "gf/menu/object/gf_menu_obj_dr_equip.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace ui {
struct EventData;
} // namespace ui

namespace gf {

GfMenuObjDrCustomTop::GfMenuObjDrCustomTop(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(nullptr), unknown58(this) {}

GfMenuObjDrCustomTop::~GfMenuObjDrCustomTop() {
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjDrCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjDrCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40 != nullptr) {
    GfMenuObjCommonJog::disable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_dr_select"));
}

void GfMenuObjDrCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40 != nullptr && unknown40->isActive()) {
    GfMenuObjCommonJog::enable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_dr_select"));
}

bool GfMenuObjDrCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase1() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase2() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_index");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2e8 = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase3() {
  if (unknown40 == nullptr) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjCommonJog::OpenParam jog;
    jog.unknown04 = -1;
    unknown40 = GfMenuCallContext::create();
    jog.unknown00 = 5;
    GfMenuObjCommonJog::open(unknown40, jog);
    GfMenuObject::setCallContextEventHandler(unknown40, acc.unknown10);
    GfMenuObjCommonDetail::OpenParam detail;
    unknown48 = GfMenuCallContext::create();
    detail.unknown00.push_back(0x1ec);
    detail.unknown18 = 0;
    detail.unknown1c = 0;
    detail.unknown2c = acc.searchChild("LAY_dr_detail");
    acc.getLayoutRect("driver_detail", detail.unknown20);
    GfMenuObjCommonDetail::open(unknown48, detail);
  }
  GfMenuCallContext::GfMenuResult result;
  if (!unknown40->isActive()) {
    return true;
  }
  if (!unknown40->unknown18.empty() && unknown40->popResult(result) && result.unknown04 == 0) {
    return true;
  }
  return false;
}

bool GfMenuObjDrCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_driver"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjDrCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

void GfMenuObjDrCustomTop::receiveRevolveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  if (ui::UICtrlObject::getEventType(event) == 0) {
    ui::uiEventParam param;
    ui::UICtrlObject::getEventParam(event, 1, param);
    if (param.valueF32 != 0.0f) {
      ui::UIObjectAcc spot(acc.unknown10, "IMG_dr_spot");
      spot.setAlpha(1.0f);
      GfMenuObjUtil::CtrlParam ctrl;
      ctrl.unknown08 = 2;
      ctrl.unknown0c = 4;
      ctrl.unknown00 = param.valueF32;
      GfMenuObjUtil::startCtrl(acc.searchChild("IMG_dr_spot"), ctrl, nullptr);
    }
  }
}

bool GfMenuObjDrCustomTop::seqAddLayerPhase2() {
  GfMenuObject::enableFSSwitching();
  GfMenuObject::changeFSSubLayer(unknown18, 2, unknown2ec, true);
  if (unknown50 == nullptr) {
    unknown50 = GfMenuCallContext::create();
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_dr_select"));
  return true;
}

bool GfMenuObjDrCustomTop::seqAddLayerPhase3_DrEquip() { return GfMenuObjDrEquip::attach(unknown50); }

bool GfMenuObjDrCustomTop::seqAddLayerPhase3_DrArtsSet() { return GfMenuObjDrArtsSet::attach(unknown50); }

bool GfMenuObjDrCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

bool GfMenuObjDrCustomTop::seqEndAddLayer() {
  mm::mtl::safeRelease(unknown50);
  resumeInput();
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrCustomTop>(const mm::mtl::Delegate<bool()> *);
