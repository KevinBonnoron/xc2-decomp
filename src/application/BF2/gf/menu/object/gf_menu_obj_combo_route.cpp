#include "gf/menu/object/gf_menu_obj_combo_route.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5e;

GfMenuObjComboRoute::GfMenuObjComboRoute(u32 handle) : GfMenuObject(handle) {
  for (u32 i = 0; i < 8; i++) {
    unknown24[i] = -1;
  }
}

GfMenuObjComboRoute::~GfMenuObjComboRoute() { ; }

void GfMenuObjComboRoute::finalize() { GfMenuObject::finalize(); }

void GfMenuObjComboRoute::update() { GfMenuObject::update(); }

void GfMenuObjComboRoute::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjComboRoute::disp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjComboRoute::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
