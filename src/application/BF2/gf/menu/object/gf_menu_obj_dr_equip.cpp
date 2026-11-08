#include "gf/menu/object/gf_menu_obj_dr_equip.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7b;

GfMenuObjDrEquip::GfMenuObjDrEquip(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(this), unknown2e0(-1) {}

GfMenuObjDrEquip::~GfMenuObjDrEquip() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  unknown2e8 = nullptr;
}

void GfMenuObjDrEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjDrEquip::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjDrEquip::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item"));
}

void GfMenuObjDrEquip::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item"));
}

bool GfMenuObjDrEquip::seqStartOpen() {
  suspendInput();
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjDrEquip::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjDrEquip::seqStartClose() {
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjDrEquip::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjDrEquip::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjDrEquip::seqLeavePhase1() { return unknown002(2); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrEquip>(const mm::mtl::Delegate<bool()> *);
