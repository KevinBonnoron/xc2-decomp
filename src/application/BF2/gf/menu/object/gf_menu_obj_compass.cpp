#include "gf/menu/object/gf_menu_obj_compass.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x42;

void GfMenuObjCompass::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCompass::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCompass::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
