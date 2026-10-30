#include "gf/menu/object/gf_menu_obj_blade_kizuna_ring.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5a;

void GfMenuObjBladeKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjBladeKizunaRing::close() { unknown142(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeKizunaRing::open() { unknown142(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
