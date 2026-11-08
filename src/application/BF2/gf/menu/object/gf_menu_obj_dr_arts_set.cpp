#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5b;

GfMenuObjDrArtsSet::GfMenuObjDrArtsSet(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown48(nullptr), unknownc8(nullptr) {}

GfMenuObjDrArtsSet::~GfMenuObjDrArtsSet() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  unknown38 = nullptr;
  unknown40 = nullptr;
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknownc8);
}

void GfMenuObjDrArtsSet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrArtsSet::update() { GfMenuObject::update(); }

void GfMenuObjDrArtsSet::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrArtsSet::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 0, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrArtsSet::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjDrArtsSet::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

} // namespace gf
