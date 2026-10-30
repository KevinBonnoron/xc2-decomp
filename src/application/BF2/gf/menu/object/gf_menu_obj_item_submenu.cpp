#include "gf/menu/object/gf_menu_obj_item_submenu.h"

#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6e;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjItemSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjItemSubmenu::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjItemSubmenu::returnItemSubMenu() { unknown142(unknown001, unknown002); }

} // namespace gf
