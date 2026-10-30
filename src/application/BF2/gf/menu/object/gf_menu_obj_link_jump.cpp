#include "gf/menu/object/gf_menu_obj_link_jump.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x49;

void GfMenuObjLinkJump::update() { GfMenuObject::update(); }

void GfMenuObjLinkJump::close() {}

void GfMenuObjLinkJump::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
