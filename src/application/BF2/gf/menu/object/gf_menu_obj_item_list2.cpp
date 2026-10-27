#include "gf/menu/object/gf_menu_obj_item_list2.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjItemList2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemList2::update() { GfMenuObject::update(); }

void GfMenuObjItemList2::setFadeOutSub(u32 handle) { GfMenuObjUtil::setCommonFadeOut(handle, 2, 0); }

} // namespace gf
