#include "gf/menu/object/gf_menu_obj_blade_name.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x81;

void GfMenuObjBladeName::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeName::finalize() { GfMenuObject::finalize(); }

} // namespace gf
