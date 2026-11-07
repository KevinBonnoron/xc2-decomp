#include "gf/menu/object/gf_menu_obj_chain_attack.h"

#include <string.h>

#include "gf/menu/gf_menu_reference.h"
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

void GfMenuObjChainAttack::openStatus(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc child(acc.searchChild("LAY_status"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
    GfMenuObjArtsPalette::startChainAttack();
    GfMenuObjBladeChange::startChainAttack(context);
  }
}

void GfMenuObjChainAttack::openStart(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc child(acc.searchChild("LAY_start"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, child.unknown10);
  }
}

void GfMenuObjChainAttack::openFullBurst(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc child(acc.searchChild("LAY_full_burst"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, child.unknown10);
  }
}

void GfMenuObjChainAttack::closeTurnSelect(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc child(acc.searchChild("LAY_turn_sel"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

bool GfMenuObjChainAttack::isEnableSelect(u32 handle, int index) {
  ui::UIObjectAcc acc(handle);
  if (strcmp(acc.getName(), "LAY_turn_sel") == 0) {
    return GfMenuReference::getReferenceNumber(index) == 0;
  }

  return true;
}

} // namespace gf
