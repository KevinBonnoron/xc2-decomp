#include "gf/menu/object/gf_menu_obj_hana_custom.h"

namespace gf {

void GfMenuObjHanaCustom::finalize() { GfMenuObject::finalize(); }

u32 GfMenuObjHanaCustom::convPartsId(u32 partsId) {
  if (partsId > 0xf) {
    return partsId - 7;
  }
  return partsId;
}

bool GfMenuObjHanaCustom::isExpandParts(u32 partsId) { return partsId - 9 < 6; }

void GfMenuObjHanaCustom::refreshPlanLine(ui::UIObjectAcc &) {}

void GfMenuObjHanaCustom::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
