#include "gf/menu/object/gf_menu_obj_location_telop.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_order_mgr.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: call id of the location telop layout; original name unknown.
constexpr u32 CALL_UNKNOWN_37 = 37;
// Inferred role: call id of the location telop sub layout; original name unknown.
constexpr u32 CALL_UNKNOWN_38 = 38;
// Inferred role: event that opens the telop; original name unknown.
constexpr u16 EVENT_UNKNOWN_256 = 0x100;
// Inferred role: event that closes the telop; original name unknown.
constexpr u16 EVENT_UNKNOWN_257 = 0x101;
// Inferred role: frames of the telop wait; original name unknown.
constexpr u32 FRAME_UNKNOWN_200 = 200;

// Inferred role: frame and flag of the telop when it is reset; original name unknown.
static const GfMenuObjLocationTelop::MainListener::unknown001 unknown002 = {0, 0};

GfMenuObjLocationTelop::GfMenuObjLocationTelop(u32 handle) : GfMenuObject(handle) {}

GfMenuObjLocationTelop::~GfMenuObjLocationTelop() { ; }

void GfMenuObjLocationTelop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
// __LINE__ must be 62 as in the original file: it is the line argument of operator new.
#line 62
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(CALL_UNKNOWN_37, main.unknown10);
  attachExternalCall(CALL_UNKNOWN_38, main.unknown10);
  GfMenuObject::initialize();
}

void GfMenuObjLocationTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjLocationTelop::update() { GfMenuObject::update(); }

void GfMenuObjLocationTelop::open(const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(CALL_UNKNOWN_37));
  if (acc.isValid() && !acc.isTerm() && param.unknown10) {
    u16 text = registString(ui::UIStr(param.unknown00, param.unknown08));
    ui::EventData event;
    event.unknown00 = EVENT_UNKNOWN_256;
    event.unknown08 = text;
    event.unknown0c = FRAME_UNKNOWN_200;
    event.unknown10 = param.unknown0c;
    event.unknown14 = param.unknown10;
    GfMenuOrderMgr::setOrder(ORDER_UNKNOWN_2, acc.unknown10, event);
  }
}

void GfMenuObjLocationTelop::close() { unknown145(CALL_UNKNOWN_37, EVENT_UNKNOWN_257); }

void GfMenuObjLocationTelop::cancel() {
  ui::UIObjectAcc acc(getAttachedObject(CALL_UNKNOWN_37));
  if (acc.isValid() && !acc.isTerm()) {
    GfMenuOrderMgr::cancelOrder(ORDER_UNKNOWN_2);
  }
}

void GfMenuObjLocationTelop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown0c = 0;
    unknown10 = unknown002;
    break;
  case 3:
    acc.setDisp(false);
    GfMenuOrderMgr::finishOrder(ORDER_UNKNOWN_2);
    break;
  case 0xc: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 1.0f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case EVENT_UNKNOWN_256: {
    acc.setDisp(true);
    const char *textName = "TXT_name_other";
    if (event.unknown10 == 2) {
      textName = "TXT_name_area";
    }
    ui::UIObjectAcc text(acc.unknown10, textName);
    GfMenuObject::setText(text.unknown10, event.unknown08);
    const char *animation;
    u32 jingle;
    if (event.unknown10 == 0) {
      jingle = 1;
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_landmark", true);
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_secret", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_area", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_name_other", true);
      GfMenuObjUtil::setChildDisp(handle, "TXT_name_area", false);
      animation = "landmark";
    } else if (event.unknown10 == 1) {
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_landmark", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_secret", true);
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_area", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_name_other", true);
      GfMenuObjUtil::setChildDisp(handle, "TXT_name_area", false);
      jingle = 3;
      animation = "secret";
    } else if (event.unknown10 == 2) {
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_landmark", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_secret", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_index_area", true);
      GfMenuObjUtil::setChildDisp(handle, "TXT_name_other", false);
      GfMenuObjUtil::setChildDisp(handle, "TXT_name_area", true);
      jingle = 2;
      animation = "area";
    } else {
      jingle = 0;
      animation = nullptr;
    }
    ui::UIObjectAcc background(acc.unknown10, "IMG_bg");
    background.startAnimation(animation, false);
    GfMenuObject::hookAnimationEvent(handle, background.unknown10);
    ui::UIObjectAcc index(acc.searchChild("LAY_index"));
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(index.unknown10, param, nullptr);
    ui::UIObjectAcc name(acc.searchChild("LAY_name"));
    param.unknown04 = 1;
    param.unknown004("fade_in_l");
    param.unknown11 = true;
    GfMenuObjUtil::startCtrl(name.unknown10, param, nullptr);
    ui::UIObjectAcc telop(handle);
    telop.setAlpha(1.0f);
    if (jingle != 0) {
      GfMenuObjUtil::playJingle(jingle);
    }
    unknown0c = 1;
    unknown10.unknown00 = event.unknown0c;
    break;
  }
  case EVENT_UNKNOWN_257:
    if (unknown0c != 0 && unknown0c != 3) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 2;
      param.unknown00 = 0.25f;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      unknown10.unknown04 = 0;
      unknown0c = 3;
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
