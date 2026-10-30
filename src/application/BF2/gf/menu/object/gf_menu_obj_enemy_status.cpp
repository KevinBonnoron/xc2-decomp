#include "gf/menu/object/gf_menu_obj_enemy_status.h"

#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x10;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjEnemyStatus::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnemyStatus::close() { unknown142(unknown001, unknown002); }

} // namespace gf
