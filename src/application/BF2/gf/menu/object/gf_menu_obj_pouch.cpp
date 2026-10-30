#include "gf/menu/object/gf_menu_obj_pouch.h"

namespace gf {

void GfMenuObjPouch::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch::update() { GfMenuObject::update(); }

void GfMenuObjPouch::setupPouch(ui::UIObjectAcc &) {}

void GfMenuObjPouch::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
