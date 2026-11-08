#include "gf/menu/object/gf_menu_obj_bl_equip.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjBlEquip::GfMenuObjBlEquip(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown58(nullptr), unknown60(0) {
  unknown58 = GfMenuCallContext::create();
}

GfMenuObjBlEquip::~GfMenuObjBlEquip() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
}

void GfMenuObjBlEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlEquip::update() { GfMenuObject::update(); }

void GfMenuObjBlEquip::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlEquip::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlEquip::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
