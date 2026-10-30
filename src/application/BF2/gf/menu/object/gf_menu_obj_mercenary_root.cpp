#include "gf/menu/object/gf_menu_obj_mercenary_root.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4d;

void GfMenuObjMercenaryRoot::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryRoot::closeBg() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
