#include "gf/menu/object/gf_menu_obj_inn.h"

namespace gf {

void GfMenuObjInn::finalize() { GfMenuObject::finalize(); }

void GfMenuObjInn::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
