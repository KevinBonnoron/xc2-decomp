#include "gf/menu/object/gf_menu_obj_blade_name.h"

#include "gf/data/gf_data_blade.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x81;

GfMenuObjBladeName::GfMenuObjBladeName(u32 handle) : GfMenuObject(handle), unknown28(this), unknown2b8(false) {}

GfMenuObjBladeName::~GfMenuObjBladeName() {}

void GfMenuObjBladeName::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeName::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeName::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBladeName::open(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    }
  }
}

void GfMenuObjBladeName::pause(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, 0x101);
  }
}

bool GfMenuObjBladeName::seqApperNormal() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_name_base");
  acc.setDisp(true);
  acc.startAnimation("common", false);
  return true;
}

bool GfMenuObjBladeName::seqApperRare() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_name_base");
  acc.setDisp(true);
  acc.startAnimation("rare", false);
  unknown002();
  return true;
}

bool GfMenuObjBladeName::seqApperName() {
  unknown002();
  return true;
}

bool GfMenuObjBladeName::seqLeave() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown2b8) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.2f;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown2b8 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    unknown2b8 = false;
    {
      ui::UIObjectAcc base(unknown18, "IMG_bl_name_base");
      base.setDisp(false);
    }
    acc.setDisp(false);
    GfMenuObject::termCallContext(acc.unknown10);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeName::seqStart() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  if (blade == 0) {
    termCallContext(main.unknown10);
  }
  if (GfDataBlade::isRareBlade(blade)) {
    unknown28.unknown002(&GfMenuObjBladeName::seqApperRare);
    unknown28.unknown004(25);
    unknown28.unknown002(&GfMenuObjBladeName::seqApperWait);
  } else {
    unknown28.unknown002(&GfMenuObjBladeName::seqApperNormal);
    unknown28.unknown002(&GfMenuObjBladeName::seqApperWait);
  }
  main.setDisp(true);
  return true;
}

bool GfMenuObjBladeName::seqApperWait() {
  ui::UIObjectAcc base(unknown18, "IMG_bl_name_base");
  bool isEnd;
  if (!base.isPlayingAnimation()) {
    unknown28.unknown004(30);
    unknown28.unknown002(&GfMenuObjBladeName::seqLeave);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

void GfMenuObjBladeName::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33:
    unknown20->unknown28.unknown005();
    unknown20->unknown28.unknown002(&GfMenuObjBladeName::seqStart);
    break;
  case GfMenuTypes::unknown003_34: {
    unknown20->unknown28.unknown005();
    {
      ui::UIObjectAcc base(acc.unknown10, "IMG_bl_name_base");
      base.stopAnimation();
      base.setDisp(false);
    }
    {
      ui::UIObjectAcc name(acc.unknown10, "TXT_bl_name");
      ui::UIObjectAcc shadow(acc.unknown10, "TXT_bl_name_shadow");
      GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(name.unknown10));
      name.setDisp(false);
      GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(shadow.unknown10));
      shadow.setDisp(false);
    }
    {
      ui::UIObjectAcc self(acc.unknown10);
      GfMenuObjUtil::stopCtrl(GfMenuObjUtil::getCtrlID(self.unknown10));
      self.setDisp(false);
    }
    break;
  }
  case GfMenuTypes::unknown003_257:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
