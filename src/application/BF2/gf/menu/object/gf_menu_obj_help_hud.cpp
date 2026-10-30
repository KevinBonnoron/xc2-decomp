#include "gf/menu/object/gf_menu_obj_help_hud.h"

#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x84;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

void GfMenuObjHelpHud::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHelpHud::enable() { unknown144(unknown001, unknown002); }

void GfMenuObjHelpHud::disable() { unknown144(unknown001, unknown003); }

} // namespace gf
