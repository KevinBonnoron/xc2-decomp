#include "gf/menu/object/gf_menu_obj_battle_telop.h"

#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4e;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

GfMenuObjBattleTelop::GfMenuObjBattleTelop(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(this), unknown2b8(false) {
  for (int i = 0; i < 3; i++) {
    unknown2c0[i] = unknown160();
  }
}

GfMenuObjBattleTelop::~GfMenuObjBattleTelop() {
  for (int i = 0; i < 3; i++) {
    unknown2c0[i] = nullptr;
  }
}

void GfMenuObjBattleTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBattleTelop::update() { GfMenuObject::update(); }

void GfMenuObjBattleTelop::close() { unknown147(unknown001, "LAY_telop", GfMenuTypes::unknown003_34); }

void GfMenuObjBattleTelop::closeUniteCombo() { unknown147(unknown001, "LAY_fusion_combo", unknown002); }

} // namespace gf
