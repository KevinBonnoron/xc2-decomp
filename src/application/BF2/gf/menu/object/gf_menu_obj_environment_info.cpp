#include "gf/menu/object/gf_menu_obj_environment_info.h"

namespace gf {

GfMenuObjEnvironmentInfo::GfMenuObjEnvironmentInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEnvironmentInfo::~GfMenuObjEnvironmentInfo() { ; }

void GfMenuObjEnvironmentInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnvironmentInfo::update() { GfMenuObject::update(); }

} // namespace gf
