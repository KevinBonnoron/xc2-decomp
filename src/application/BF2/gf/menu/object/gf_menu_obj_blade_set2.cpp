#include "gf/menu/object/gf_menu_obj_blade_set2.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

// Inferred role: layer close destination parameter; original name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: destination; original member name unknown.
};

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x1e;

void GfMenuObjBladeSet2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSet2::sendEvent(u32 handle, u32 type, u32 param, f32 delay) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, delay);
}

void GfMenuObjBladeSet2::setCloseToFSClose() {
  unknown001 value;
  value.unknown00 = 2;
  GfMenuTypes::Param layerParam;
  layerParam.set(value);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBladeSet2::setCloseToReturn() {
  unknown001 value;
  value.unknown00 = 1;
  GfMenuTypes::Param layerParam;
  layerParam.set(value);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

} // namespace gf
