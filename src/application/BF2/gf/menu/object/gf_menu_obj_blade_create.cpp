#include "gf/menu/object/gf_menu_obj_blade_create.h"

#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_blade_name.h"

namespace gf {

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x14;

void GfMenuObjBladeCreate::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjBladeCreate::openCreatedBladeName(GfMenuCallContext *context) { GfMenuObjBladeName::open(context); }

} // namespace gf
