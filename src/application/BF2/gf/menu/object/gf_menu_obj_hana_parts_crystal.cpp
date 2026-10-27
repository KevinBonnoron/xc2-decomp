#include "gf/menu/object/gf_menu_obj_hana_parts_crystal.h"

#include "gf/util/gf_item_util.h"

namespace gf {

void GfMenuObjHanaPartsCrystal::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsCrystal::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsCrystal::getCrystalItemCount(u32 item) { return GfItemUtil::getItemBoxCount(item); }

} // namespace gf
