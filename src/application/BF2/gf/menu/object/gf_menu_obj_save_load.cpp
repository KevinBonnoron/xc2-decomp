#include "gf/menu/object/gf_menu_obj_save_load.h"

namespace gf {

GfMenuObjSaveLoad::GfMenuObjSaveLoad(u32 handle) : GfMenuObject(handle), unknown24(0) {}

GfMenuObjSaveLoad::~GfMenuObjSaveLoad() { ; }

void GfMenuObjSaveLoad::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSaveLoad::update() { GfMenuObject::update(); }

} // namespace gf
