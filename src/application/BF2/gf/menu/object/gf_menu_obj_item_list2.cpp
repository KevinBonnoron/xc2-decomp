#include "gf/menu/object/gf_menu_obj_item_list2.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjItemList2::GfMenuObjItemList2(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown98(0), unknowna0(true) {}

GfMenuObjItemList2::~GfMenuObjItemList2() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjItemList2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemList2::update() { GfMenuObject::update(); }

void GfMenuObjItemList2::setFadeOutSub(u32 handle) { GfMenuObjUtil::setCommonFadeOut(handle, 2, 0); }

void GfMenuObjItemList2::sendEvent(u32 handle, u32 type, u32 param, u32 delay) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, static_cast<f32>(delay) * 0.033333335f);
}

int GfMenuObjItemList2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjItemList2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
