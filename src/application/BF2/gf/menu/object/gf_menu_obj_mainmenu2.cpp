#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/gf_menu_object.h"

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
    unknown140(handle, type, param, 0.0f);
  }
}

} // namespace gf
