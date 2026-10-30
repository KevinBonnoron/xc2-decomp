#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"

namespace gf {

void GfMenuObjBlWeapon2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlWeapon2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
