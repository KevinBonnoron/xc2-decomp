#include "gf/menu/object/gf_menu_obj_dummy_tutorial.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x79;

GfMenuObjDummyTutorial::GfMenuObjDummyTutorial(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDummyTutorial::~GfMenuObjDummyTutorial() { unknown28 = nullptr; }

void GfMenuObjDummyTutorial::initialize() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  unknown28 = unknown160();
  unknown28->unknown162(-1);
  GfMenuReferenceAdapter::create(acc.searchChild("IMG_tutorial"), unknown28, false);
  attachExternalCall(unknown001, acc.unknown10);
// __LINE__ must be 79 as in the original file: it is the line argument of operator new.
#line 79
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(acc.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjDummyTutorial::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDummyTutorial::update() { GfMenuObject::update(); }

void GfMenuObjDummyTutorial::open(GfMenuCallContext *context, const OpenParam &param) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown08_u16 = param.unknown00;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    }
  }
}

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
