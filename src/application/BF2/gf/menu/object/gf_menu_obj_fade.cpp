#include "gf/menu/object/gf_menu_obj_fade.h"

namespace gf {

GfMenuObjFade::GfMenuObjFade(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(false) {}

GfMenuObjFade::~GfMenuObjFade() { ; }

void GfMenuObjFade::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFade::update() { GfMenuObject::update(); }

} // namespace gf
