#include "gf/menu/object/gf_menu_obj_common_text.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x64;

void GfMenuObjCommonText::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonText::update() { GfMenuObject::update(); }

void GfMenuObjCommonText::sendEvent(u32 handle, u32 type, u32 param, f32 delay) { unknown140(handle, type, param, delay); }

void GfMenuObjCommonText::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
