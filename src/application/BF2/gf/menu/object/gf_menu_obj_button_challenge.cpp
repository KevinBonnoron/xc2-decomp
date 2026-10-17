#include "gf/menu/object/gf_menu_obj_button_challenge.h"

namespace gf {

GfMenuObjButtonChallenge::GfMenuObjButtonChallenge(u32 handle) : GfMenuObject(handle) {}

GfMenuObjButtonChallenge::~GfMenuObjButtonChallenge() { ; }

void GfMenuObjButtonChallenge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjButtonChallenge::update() { GfMenuObject::update(); }

} // namespace gf
