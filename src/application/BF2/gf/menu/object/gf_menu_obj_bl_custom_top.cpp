#include "gf/menu/object/gf_menu_obj_bl_custom_top.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_bl_orb.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjBlCustomTop::GfMenuObjBlCustomTop(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(nullptr), unknown58(this) {}

GfMenuObjBlCustomTop::~GfMenuObjBlCustomTop() {
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjBlCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40 != nullptr) {
    GfMenuObjCommonJog::disable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_bl_select"));
}

void GfMenuObjBlCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40 != nullptr && unknown40->isActive()) {
    GfMenuObjCommonJog::enable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
}

bool GfMenuObjBlCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAppearPhase1() {
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

bool GfMenuObjBlCustomTop::seqAppearPhase2() {
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

bool GfMenuObjBlCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_blade"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase2() {
  GfMenuObject::enableFSSwitching();
  GfMenuObject::changeFSSubLayer(unknown18, 2, unknown2ec, true);
  if (unknown50 == nullptr) {
    unknown50 = GfMenuCallContext::create();
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlWeapon() { return GfMenuObjBlWeapon::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlOrb() { return GfMenuObjBlOrb::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

bool GfMenuObjBlCustomTop::seqEndAddLayer() {
  mm::mtl::safeRelease(unknown50);
  resumeInput();
  return true;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlCustomTop>(const mm::mtl::Delegate<bool()> *);
