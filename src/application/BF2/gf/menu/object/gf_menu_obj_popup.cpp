#include "gf/menu/object/gf_menu_obj_popup.h"

#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x76;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjPopup::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPopup::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjPopup::pausePickup() { unknown142(unknown001, unknown002); }

} // namespace gf
