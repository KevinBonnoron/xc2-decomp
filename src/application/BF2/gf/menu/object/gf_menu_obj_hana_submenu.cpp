#include "gf/menu/object/gf_menu_obj_hana_submenu.h"

#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x71;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjHanaSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjHanaSubmenu::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjHanaSubmenu::returnHanaSubMenu() { unknown142(unknown001, unknown002); }

} // namespace gf
