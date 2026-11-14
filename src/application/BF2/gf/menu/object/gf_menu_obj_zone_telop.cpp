#include "gf/menu/object/gf_menu_obj_zone_telop.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_order_mgr.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: call id of the zone telop; original name unknown.
constexpr u32 unknown001 = 0x45;
// Inferred role: frames of the fade in and fade out wait; original name unknown.
constexpr u32 FRAME_UNKNOWN_120 = 0x78;
// Inferred role: event that opens the telop; original name unknown.
constexpr u16 EVENT_UNKNOWN_33 = 0x21;
// Inferred role: event that closes the telop; original name unknown.
constexpr u16 EVENT_UNKNOWN_34 = 0x22;

GfMenuObjZoneTelop::GfMenuObjZoneTelop(u32 handle) : GfMenuObject(handle), unknown28(this), unknown188(false), unknown18c(0.0f) {}

GfMenuObjZoneTelop::~GfMenuObjZoneTelop() {}

void GfMenuObjZoneTelop::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 70 as in the original file: it is the line argument of operator new.
#line 70
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjZoneTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjZoneTelop::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

void GfMenuObjZoneTelop::open(GfMenuCallContext *context, u16 zone) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      if (context) {
        startCallContext(context, unknown001, handle);
      }
      ui::EventData event;
      event.unknown00 = EVENT_UNKNOWN_33;
      event.unknown08 = zone;
      GfMenuOrderMgr::setOrder(1, handle, event);
    }
  }
}

void GfMenuObjZoneTelop::close(f32 wait) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = EVENT_UNKNOWN_34;
      event.unknown08_f32 = wait;
      sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjZoneTelop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 2:
    termCallContext(handle);
    acc.setTerm();
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  case EVENT_UNKNOWN_33: {
    ui::UIObjectAcc title(acc.unknown10, "TXT_title");
    title.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_ZONE_TELOP_MS), event.unknown08));
    unknown20->unknown18c = 0.5f;
    unknown20->unknown188 = false;
    unknown20->unknown28.unknown005();
    unknown20->unknown28.unknown002(&GfMenuObjZoneTelop::seqFadeIn);
    unknown20->unknown28.unknown004(FRAME_UNKNOWN_120);
    unknown20->unknown28.unknown002(&GfMenuObjZoneTelop::seqFadeOut);
    break;
  }
  case EVENT_UNKNOWN_34:
    if (event.unknown08_f32 == 0.0f) {
      unknown20->unknown188 = false;
      unknown20->unknown28.unknown005();
    } else {
      unknown20->unknown18c = event.unknown08_f32;
      unknown20->unknown188 = false;
      unknown20->unknown28.unknown005();
      unknown20->unknown28.unknown002(&GfMenuObjZoneTelop::seqFadeOut);
      break;
    }
  case 1:
    acc.setDisp(false);
  }
}

bool GfMenuObjZoneTelop::seqFadeIn() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown188) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown188 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    isEnd = true;
    unknown188 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjZoneTelop::seqFadeOut() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown188) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = unknown18c;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown188 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    unknown188 = false;
    termCallContext(acc.unknown10);
    isEnd = true;
    GfMenuOrderMgr::finishOrder(1);
  } else {
    isEnd = false;
  }
  return isEnd;
}

} // namespace gf
