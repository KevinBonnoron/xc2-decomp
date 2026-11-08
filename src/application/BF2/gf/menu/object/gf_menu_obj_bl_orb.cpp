#include "gf/menu/object/gf_menu_obj_bl_orb.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7d;

GfMenuObjBlOrb::GfMenuObjBlOrb(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown58(this), unknown2e8(-1), unknown2f0(nullptr) {}

GfMenuObjBlOrb::~GfMenuObjBlOrb() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown2f0);
  unknown50 = nullptr;
}

void GfMenuObjBlOrb::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlOrb::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjBlOrb::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjBlOrb::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_slot"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
}

void GfMenuObjBlOrb::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_slot"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
}

bool GfMenuObjBlOrb::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlOrb::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlOrb::seqStartClose() {
  GfMenuObjOperationInfo::close();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlOrb::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjBlOrb::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjBlOrb::seqLeavePhase1() { return unknown002(2); }

void GfMenuObjBlOrb::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqStartOpen);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqAppearPhase1);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqEndOpen);
    break;
  case 2:
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqStartClose);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqLeavePhase1);
    unknown20->unknown58.unknown002(&GfMenuObjBlOrb::seqEndClose);
    break;
  case 8: {
    int result = event.unknown0c;
    GfMenuReference::getReferenceBladeID(unknown20->unknown24);
    if (result == 2) {
      GfMenuObject::returnFSSubLayer(acc.unknown10, 2);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlOrb>(const mm::mtl::Delegate<bool()> *);
