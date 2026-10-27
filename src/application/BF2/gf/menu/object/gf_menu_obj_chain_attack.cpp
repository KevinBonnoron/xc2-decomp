#include "gf/menu/object/gf_menu_obj_chain_attack.h"
#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjChainAttack::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainAttack::update() { GfMenuObject::update(); }

void GfMenuObjChainAttack::changeCharacter(u32) { GfMenuObjUtil::playSE(0x34); }

} // namespace gf
