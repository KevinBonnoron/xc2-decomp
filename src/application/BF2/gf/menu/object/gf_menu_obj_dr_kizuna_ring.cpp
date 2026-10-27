#include "gf/menu/object/gf_menu_obj_dr_kizuna_ring.h"

namespace gf {

void GfMenuObjDrKizunaRing::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjDrKizunaRing::isLockPos(int index) { return index % 6 == 0; }

bool GfMenuObjDrKizunaRing::isScreenLR(u32 screen) { return screen < 3; }

} // namespace gf
