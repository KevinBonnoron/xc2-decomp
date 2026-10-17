#include "gf/menu/object/gf_menu_obj_target_info.h"

namespace gf {

GfMenuObjTargetInfo::GfMenuObjTargetInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjTargetInfo::~GfMenuObjTargetInfo() { ; }

void GfMenuObjTargetInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetInfo::update() { GfMenuObject::update(); }

} // namespace gf
