#include "gf/menu/object/gf_menu_obj_arts_palette2.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x28;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjArtsPalette2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette2::close() { unknown146(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjArtsPalette2::open() { unknown146(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjArtsPalette2::resetSelection() { unknown146(unknown001, unknown002); }

} // namespace gf
