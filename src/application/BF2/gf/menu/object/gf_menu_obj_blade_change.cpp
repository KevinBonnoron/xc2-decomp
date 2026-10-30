#include "gf/menu/object/gf_menu_obj_blade_change.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x3c;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

void GfMenuObjBladeChange::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeChange::enableAwakening(bool) {}

void GfMenuObjBladeChange::close() { unknown146(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeChange::exitChainAttack() { unknown146(unknown001, unknown002); }

void GfMenuObjBladeChange::open() { unknown146(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjBladeChange::pushGroupUp() { unknown146(unknown001, unknown003); }

} // namespace gf
