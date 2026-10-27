#include "gf/menu/object/gf_menu_obj_item_list2.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

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

} // namespace gf
