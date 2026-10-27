#include "gf/menu/object/gf_menu_obj_chain_icon.h"
#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjChainIcon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainIcon::update() { GfMenuObject::update(); }

void GfMenuObjChainIcon::setupScreen(u32 handle, int, int, int, int) { GfMenuObjUtil::setChildDisp(handle, "LAY_main", true); }

} // namespace gf
