#include "gf/menu/object/gf_menu_obj_special_gauge.h"

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x29;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

void GfMenuObjSpecialGauge::push() { unknown144(unknown001, unknown002); }

void GfMenuObjSpecialGauge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSpecialGauge::close() { unknown145(unknown001, unknown003); }

void GfMenuObjSpecialGauge::open() { unknown145(unknown001, unknown004); }

} // namespace gf
