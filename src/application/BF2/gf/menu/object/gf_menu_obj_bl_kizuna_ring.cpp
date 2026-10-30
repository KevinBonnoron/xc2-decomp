#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"

namespace gf {

void GfMenuObjBlKizunaRing::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjBlKizunaRing::isLockPos(int index) { return index % 10 == 0; }

bool GfMenuObjBlKizunaRing::isScreenLR(u32 screen) { return screen < 4; }

void GfMenuObjBlKizunaRing::setupCircle(ui::UIObjectAcc &) {}

void GfMenuObjBlKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

} // namespace gf
