#include "gf/menu/object/gf_menu_obj_blade_switch.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x22;

void GfMenuObjBladeSwitch::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSwitch::open() { unknown144(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjBladeSwitch::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
