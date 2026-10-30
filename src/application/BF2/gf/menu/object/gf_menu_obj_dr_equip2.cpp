#include "gf/menu/object/gf_menu_obj_dr_equip2.h"

namespace gf {

void GfMenuObjDrEquip2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip2::update() { GfMenuObject::update(); }

void GfMenuObjDrEquip2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
