#include "gf/menu/object/gf_menu_obj_dummy_tutorial.h"

#include "gf/menu/gf_menu_reference_number.h"

namespace gf {

GfMenuObjDummyTutorial::GfMenuObjDummyTutorial(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDummyTutorial::~GfMenuObjDummyTutorial() { unknown28 = nullptr; }

void GfMenuObjDummyTutorial::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDummyTutorial::update() { GfMenuObject::update(); }

} // namespace gf
