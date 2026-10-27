#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"

namespace gf {

// Inferred role: full screen layer index; original name unknown.
constexpr u32 unknown001 = 1;

void GfMenuObjMainMenu2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(unknown001), layerParam);
}

void GfMenuObjMainMenu2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = param;
    event.unknown0c = 0;
    event.unknown00 = type;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
  }
}

} // namespace gf
