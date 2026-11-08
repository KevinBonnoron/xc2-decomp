#include "gf/menu/object/gf_menu_obj_element_eff.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x17;

GfMenuObjElementEff::GfMenuObjElementEff(u32 handle) : GfMenuObject(handle), unknown28(this), unknown2b8(-1), unknown2bc(0), unknown2c0(0) {}

GfMenuObjElementEff::~GfMenuObjElementEff() {}

void GfMenuObjElementEff::finalize() { GfMenuObject::finalize(); }

void GfMenuObjElementEff::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjElementEff::start(GfMenuCallContext *context, const StartParam &param) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    u32 handle = getAttachedObject(unknown001);
    if (ui::UIObjectAcc(handle).isValid()) {
      if (!ui::UIObjectAcc(handle).isTerm()) {
        ui::EventData event;
        event.unknown0c = 0;
        event.unknown00 = GfMenuTypes::unknown003_33;
        event.unknown08 = param.attribute;
        sendEvent(handle, event, 0.0f);
        startCallContext(context, unknown001, handle);
      }
    }
  }
}

void GfMenuObjElementEff::cancel(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown143(unknown001, GfMenuTypes::unknown003_34);
  }
}

bool GfMenuObjElementEff::seqInit() {
  unknown2b8 = -1;
  ui::UIObjectAcc top(unknown18, "IMG_top");
  if (top.isPlayingAnimation()) {
    top.stopAnimation();
  }
  ui::UIObjectAcc bottom(unknown18, "IMG_bottom");
  if (bottom.isPlayingAnimation()) {
    bottom.stopAnimation();
  }
  return true;
}

bool GfMenuObjElementEff::seqLoop() {
  ui::UIObjectAcc top(unknown18, "IMG_top");
  ui::UIObjectAcc bottom(unknown18, "IMG_bottom");
  bool isEnd;
  if (top.isPlayingAnimation() || bottom.isPlayingAnimation()) {
    isEnd = false;
  } else {
    top.startAnimation("loop", false);
    bottom.startAnimation("loop", false);
    unknown2b8 = -1;
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjElementEff::seqComboName() {
  if (unknown2b8 == -1) {
    unknown2b8 = 0;
    unknown2c0 = 0x25;
    return false;
  }
  if (--unknown2c0 != 0) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_combo_name_eff");
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_zoom";
  param.unknown58 = "fade_out";
  param.unknown14 = 10;
  GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
  return true;
}

bool GfMenuObjElementEff::seqClose() {
  ui::UIObjectAcc top(unknown18, "IMG_top");
  ui::UIObjectAcc bottom(unknown18, "IMG_bottom");
  bool isEnd;
  if (unknown2b8 == -1) {
    top.setDisp(true);
    top.startAnimation("end", false);
    bottom.setDisp(true);
    bottom.startAnimation("end", false);
    ui::UIObjectAcc name(unknown18, "LAY_combo_name");
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l");
    param.unknown14 = 10;
    unknown2b8 = GfMenuObjUtil::startCtrl(name.unknown10, param, nullptr);
    isEnd = false;
  } else if (top.isPlayingAnimation() || bottom.isPlayingAnimation() || GfMenuObjUtil::isBusyCtrl(unknown2b8)) {
    isEnd = false;
  } else {
    unknown2b8 = -1;
    top.setDisp(false);
    bottom.setDisp(false);
    ui::UIObjectAcc main(unknown18, "LAY_main");
    termCallContext(main.unknown10);
    isEnd = true;
  }
  return isEnd;
}

void GfMenuObjElementEff::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    unknown20->unknown2bc = event.unknown08;
    unknown20->unknown2b8 = -1;
    unknown20->unknown28.unknown005();
    unknown20->unknown28.unknown002(&GfMenuObjElementEff::seqInit);
    unknown20->unknown28.unknown002(&GfMenuObjElementEff::seqOpen);
    unknown20->unknown28.unknown002(&GfMenuObjElementEff::seqComboName);
    unknown20->unknown28.unknown002(&GfMenuObjElementEff::seqLoop);
    break;
  case GfMenuTypes::unknown003_34:
    unknown20->unknown2b8 = -1;
    unknown20->unknown28.unknown005();
    unknown20->unknown28.unknown002(&GfMenuObjElementEff::seqClose);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjElementEff>(const mm::mtl::Delegate<bool()> *);
