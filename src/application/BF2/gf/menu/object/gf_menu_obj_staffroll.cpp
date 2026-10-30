#include "gf/menu/object/gf_menu_obj_staffroll.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x85;

void GfMenuObjStaffroll::fadeout() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
