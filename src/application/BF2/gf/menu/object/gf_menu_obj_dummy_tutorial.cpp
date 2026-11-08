#include "gf/menu/object/gf_menu_obj_dummy_tutorial.h"

#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjDummyTutorial::GfMenuObjDummyTutorial(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDummyTutorial::~GfMenuObjDummyTutorial() { unknown28 = nullptr; }

void GfMenuObjDummyTutorial::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDummyTutorial::update() { GfMenuObject::update(); }

void GfMenuObjDummyTutorial::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::disableInput(acc.unknown10);
    acc.setDispChild(false, "IMG_tutorial");
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      GfMenuObject::termCallContext(acc.unknown10);
    }
    break;
  case 8: {
    ui::UIObjectAcc image(acc.unknown10, "IMG_tutorial");
    if (event.unknown0c == 1) {
      GfMenuObject::disableInput(acc.unknown10);
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = 0.25f;
      param.unknown04 = 2;
      param.unknown08 = 2;
      param.unknown14 = 2;
      int ctrl = GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    }
    break;
  }
  case 0x21: {
    ui::UIObjectAcc image(acc.unknown10, "IMG_tutorial");
    unknown20->unknown28->unknown0c = event.unknown08_u16;
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.25f;
    param.unknown04 = 1;
    param.unknown08 = 1;
    int ctrl = GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    if (image.isStreamImage()) {
      image.setDisp(false);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
