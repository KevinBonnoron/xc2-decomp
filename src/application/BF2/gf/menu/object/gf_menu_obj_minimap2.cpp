#include "gf/menu/object/gf_menu_obj_minimap2.h"
#include "gf/menu/gf_menu_flag.h"

namespace gf {

void GfMenuObjMinimap2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMinimap2::enable() { GfMenuFlag::set1(0x1f, 0); }

void GfMenuObjMinimap2::disable() { GfMenuFlag::set1(0x1f, 1); }

} // namespace gf
