#include "gf/menu/object/gf_menu_obj_event_skip.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the event skip layout; original name unknown.
constexpr u32 CALL_UNKNOWN_47 = 47;

GfMenuObjEventSkip::GfMenuObjEventSkip(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEventSkip::~GfMenuObjEventSkip() { ; }

void GfMenuObjEventSkip::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 72 as in the original file: it is the line argument of operator new.
#line 72
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(CALL_UNKNOWN_47, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjEventSkip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEventSkip::update() { GfMenuObject::update(); }

void GfMenuObjEventSkip::close() { unknown143(CALL_UNKNOWN_47, GfMenuTypes::unknown003_34); }

u32 GfMenuObjEventSkip::setupScreen(u32 screen) { return screen; }

void GfMenuObjEventSkip::open(GfMenuCallContext *context) {
  u32 object = getAttachedObject(CALL_UNKNOWN_47);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      startCallContext(context, CALL_UNKNOWN_47, object);
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      sendEvent(object, event, 0.0f);
      GfMenuObjUtil::playSE(3);
    }
  }
}

void GfMenuObjEventSkip::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::UIObjectAcc text(handle, "TXT_pause");
    GfMenuObjUtil::setDockPos(acc.searchChild("IMG_accent_l"), text.unknown10, 1, false);
    GfMenuObjUtil::addPos(acc.searchChild("IMG_accent_l"), -16, 0);
    GfMenuObjUtil::setDockPos(acc.searchChild("IMG_accent_r"), text.unknown10, 2, false);
    GfMenuObjUtil::addPos(acc.searchChild("IMG_accent_r"), 16, 0);
    acc.setDisp(false);
    disableInput(acc.unknown10);
    break;
  }
  case 2:
    termCallContext(handle);
    acc.setDisp(false);
    acc.setTerm();
    break;
  case 3:
    switch (unknown0c) {
    case 0: {
      ui::UIObjectAcc pause(handle, "LAY_pause");
      if (pause.isValid()) {
        pause.setAlpha(0.0f);
        GfMenuObjUtil::CtrlParam param;
        param.unknown00 = 1.0f;
        param.unknown08 = 1;
        int ctrl = GfMenuObjUtil::startCtrl(pause.unknown10, param, nullptr);
        if (ctrl >= 0) {
          hookCtrlEvent(handle, ctrl);
        }
        unknown0c = 1;
      }
      break;
    }
    case 1: {
      ui::UIObjectAcc pause(handle, "LAY_pause");
      if (pause.isValid()) {
        pause.setAlpha(1.0f);
        GfMenuObjUtil::CtrlParam param;
        param.unknown00 = 1.0f;
        param.unknown08 = 2;
        int ctrl = GfMenuObjUtil::startCtrl(pause.unknown10, param, nullptr);
        if (ctrl >= 0) {
          hookCtrlEvent(handle, ctrl);
        }
        unknown0c = 0;
      }
      break;
    }
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      addResultCallContext(handle, 0, 0);
      GfMenuObjEventSkip::close();
    } else if (event.unknown0c == 9 || event.unknown0c == 2) {
      addResultCallContext(handle, 1, 0);
      GfMenuObjEventSkip::close();
    }
    GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    break;
  case 0x21: {
    acc.setDisp(true);
    unknown0c = 1;
    ui::EventData sendData;
    sendData.unknown00 = 3;
    sendEvent(handle, sendData, 0.0f);
    enableInput(acc.unknown10);
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideDisp(false);
    break;
  }
  case 0x22:
    termCallContext(handle);
    disableInput(acc.unknown10);
    GfMenuObjOperationInfo::close();
    acc.setDisp(false);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
