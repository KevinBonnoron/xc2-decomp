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

GfMenuObjChainAttack::GfMenuObjChainAttack(u32 handle) : GfMenuObject(handle), unknown30(0), unknown38(0), unknown40(0), unknown48(0), unknown50(0) {}

GfMenuObjChainAttack::~GfMenuObjChainAttack() { ; }

void GfMenuObjChainAttack::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainAttack::update() { GfMenuObject::update(); }

void GfMenuObjChainAttack::changeCharacter(u32) { GfMenuObjUtil::playSE(0x34); }

void GfMenuObjChainAttack::openResult(const ResultParam &param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc child(acc.searchChild("LAY_result"));
    ui::EventData event;
    event.unknown08 = 0;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08_u16 = param.unknown00;
    event.unknown0c = param.unknown04;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

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

void GfMenuObjChainAttack::StartListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::termCallContext(acc.unknown10);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    ui::UIObjectAcc base(acc.unknown10, "IMG_start_base");
    base.startAnimationFromID(1, false);
    GfMenuObject::hookAnimationEvent(acc.unknown10, base.unknown10);
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    param.unknown14 = 8;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, "TXT_start_caption");
    GfMenuObjUtil::playSE(0x33);
    acc.setDisp(true);
    break;
  }
  case 0xc: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown11 = true;
    param.unknown14 = 10;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjChainAttack::ExtendListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case 3:
    break;
  case GfMenuTypes::unknown003_33:
    if (unknown0c == 0) {
      acc.setDisp(true);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_l_early");
      param.unknown04 = 1;
      param.unknown11 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown0c = 1;
    }
    break;
  case GfMenuTypes::unknown003_34:
    if (unknown0c == 1) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_out_r_early");
      param.unknown11 = true;
      param.unknown04 = 2;
      param.unknown14 = 10;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown0c = 0;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
