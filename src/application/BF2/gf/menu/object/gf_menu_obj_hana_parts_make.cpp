#include "gf/menu/object/gf_menu_obj_hana_parts_make.h"

#include "gf/game/gf_game_util_hana.h"

namespace gf {

void GfMenuObjHanaPartsMake::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsMake::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsMake::getCrystalItemCount(u32 item) { return GfGameUtilHana::getConvertToEther(item); }

} // namespace gf
