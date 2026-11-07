#include "gf/menu/object/gf_menu_obj_blade_change.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x3c;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

void GfMenuObjBladeChange::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeChange::update() {
  ui::UIObjectAcc(unknown18).setAlpha(1.0f);
  GfMenuObject::update();
}

void GfMenuObjBladeChange::enableAwakening(bool) {}

void GfMenuObjBladeChange::close() { unknown146(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeChange::startChainAttack(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    event.unknown08 = 1;
    GfMenuObject::sendEvent(acc.unknown10, event, GfMenuObjUtil::getParamMenu()->unknown18);
    if (context != nullptr && GfMenuObjUtil::checkCCStart(context)) {
      GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    }
  }
}

void GfMenuObjBladeChange::exitChainAttack() { unknown146(unknown001, unknown002); }

void GfMenuObjBladeChange::open() { unknown146(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjBladeChange::pushGroupUp() { unknown146(unknown001, unknown003); }

void GfMenuObjBladeChange::dispInfo(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDispChild(isDisp, "LAY_info");
  }
}

void GfMenuObjBladeChange::pushBladeChange(unsigned int blade) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown08 = blade;
    event.unknown0c = 0;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
