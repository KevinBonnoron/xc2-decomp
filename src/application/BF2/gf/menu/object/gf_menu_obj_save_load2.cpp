#include "gf/menu/object/gf_menu_obj_save_load2.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

// Inferred role: menu id; original name unknown.
constexpr u32 unknown001 = 0x35;

void GfMenuObjSaveLoad2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSaveLoad2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown001), layerParam);
}

void GfMenuObjSaveLoad2::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
