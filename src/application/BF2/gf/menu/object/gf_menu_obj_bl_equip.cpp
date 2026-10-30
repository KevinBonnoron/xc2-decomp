#include "gf/menu/object/gf_menu_obj_bl_equip.h"

namespace gf {

void GfMenuObjBlEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlEquip::update() { GfMenuObject::update(); }

void GfMenuObjBlEquip::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
