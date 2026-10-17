#include "gf/menu/object/gf_menu_obj_common_list.h"

namespace gf {

GfMenuObjCommonList::GfMenuObjCommonList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonList::~GfMenuObjCommonList() { ; }

void GfMenuObjCommonList::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonList::update() { GfMenuObject::update(); }

} // namespace gf
