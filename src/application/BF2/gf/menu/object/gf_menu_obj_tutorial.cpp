#include "gf/menu/object/gf_menu_obj_tutorial.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7a;

void GfMenuObjTutorial::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTutorial::closeAll() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
