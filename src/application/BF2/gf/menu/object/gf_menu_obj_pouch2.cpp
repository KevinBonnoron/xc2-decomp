#include "gf/menu/object/gf_menu_obj_pouch2.h"

namespace gf {

void GfMenuObjPouch2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
