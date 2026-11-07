#include "gf/menu/object/gf_menu_obj_combo_route.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5e;

void GfMenuObjComboRoute::finalize() { GfMenuObject::finalize(); }

void GfMenuObjComboRoute::update() { GfMenuObject::update(); }

void GfMenuObjComboRoute::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjComboRoute::disp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjComboRoute::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
