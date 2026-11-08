#include "gf/menu/object/gf_menu_obj_bl_weapon.h"

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7c;

GfMenuObjBlWeapon::GfMenuObjBlWeapon(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(0), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(this), unknown2e0(-1), unknown2e8(nullptr) {}

GfMenuObjBlWeapon::~GfMenuObjBlWeapon() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown2e8);
  unknown48 = nullptr;
}

void GfMenuObjBlWeapon::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjBlWeapon::isSameWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip);
  return acc.getEquipWeapon(-1, false) == weapon;
}

bool GfMenuObjBlWeapon::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjBlWeapon::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlWeapon::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
}

void GfMenuObjBlWeapon::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
}

bool GfMenuObjBlWeapon::seqStartOpen() {
  suspendInput();
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjBlWeapon::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlWeapon::seqStartClose() {
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjBlWeapon::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjBlWeapon::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjBlWeapon::seqLeavePhase1() { return unknown002(2); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlWeapon>(const mm::mtl::Delegate<bool()> *);
