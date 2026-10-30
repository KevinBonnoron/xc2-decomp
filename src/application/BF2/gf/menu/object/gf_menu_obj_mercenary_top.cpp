#include "gf/menu/object/gf_menu_obj_mercenary_top.h"

#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x34;

void GfMenuObjMercenaryTop::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjMercenaryTop::sendOpenEvent(u32 handle, int type) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaryTop::sendCloseEvent(u32 handle, int type) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaryTop::finalize() { GfMenuObject::finalize(); }

} // namespace gf
