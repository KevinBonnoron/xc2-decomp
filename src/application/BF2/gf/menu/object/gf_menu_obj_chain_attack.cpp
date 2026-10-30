#include "gf/menu/object/gf_menu_obj_chain_attack.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_arts_palette.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x54;

void GfMenuObjChainAttack::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainAttack::update() { GfMenuObject::update(); }

void GfMenuObjChainAttack::changeCharacter(u32) { GfMenuObjUtil::playSE(0x34); }

void GfMenuObjChainAttack::closeResult() { unknown148(unknown001, "LAY_result", GfMenuTypes::unknown003_34); }

void GfMenuObjChainAttack::closeRoundExtend() { unknown148(unknown001, "LAY_extend", GfMenuTypes::unknown003_34); }

void GfMenuObjChainAttack::openRoundExtend() { unknown148(unknown001, "LAY_extend", GfMenuTypes::unknown003_33); }

void GfMenuObjChainAttack::closeStatus() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc child(acc.searchChild("LAY_status"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
    GfMenuObjArtsPalette::exitChainAttack();
    GfMenuObjBladeChange::exitChainAttack();
  }
}

} // namespace gf
