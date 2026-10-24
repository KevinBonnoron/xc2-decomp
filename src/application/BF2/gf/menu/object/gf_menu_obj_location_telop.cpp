#include "gf/menu/object/gf_menu_obj_location_telop.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_order_mgr.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 CALL_LOCATION_TELOP = 37;
constexpr u32 CALL_LOCATION_TELOP_SUB = 38;
constexpr int ORDER_LOCATION_TELOP = 2;
constexpr u16 EVENT_OPEN_TELOP = 0x100;
constexpr u16 EVENT_CLOSE_TELOP = 0x101;
constexpr u32 TELOP_FRAME = 200;

GfMenuObjLocationTelop::GfMenuObjLocationTelop(u32 handle) : GfMenuObject(handle) {}

GfMenuObjLocationTelop::~GfMenuObjLocationTelop() { ; }

void GfMenuObjLocationTelop::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
// __LINE__ must be 62 as in the original file: it is the line argument of operator new.
#line 62
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.handle, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(CALL_LOCATION_TELOP, main.handle);
  attachExternalCall(CALL_LOCATION_TELOP_SUB, main.handle);
  GfMenuObject::initialize();
}

void GfMenuObjLocationTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjLocationTelop::update() { GfMenuObject::update(); }

void GfMenuObjLocationTelop::open(const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(CALL_LOCATION_TELOP));
  if (acc.isValid() && !acc.isTerm() && param.unknown10) {
    u16 text = registString(ui::UIStr(param.unknown00, param.unknown08));
    ui::EventData event;
    event.type = EVENT_OPEN_TELOP;
    event.param0 = text;
    event.param1 = TELOP_FRAME;
    event.param2 = param.unknown0c;
    event.param3 = param.unknown10;
    GfMenuOrderMgr::setOrder(ORDER_LOCATION_TELOP, acc.handle, event);
  }
}

void GfMenuObjLocationTelop::close() {
  ui::UIObjectAcc acc(getAttachedObject(CALL_LOCATION_TELOP));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.type = EVENT_CLOSE_TELOP;
    ui::UIManager::get()->requestObjectEvent(acc.handle, event, 0.0f);
  }
}

void GfMenuObjLocationTelop::cancel() {
  ui::UIObjectAcc acc(getAttachedObject(CALL_LOCATION_TELOP));
  if (acc.isValid() && !acc.isTerm()) {
    GfMenuOrderMgr::cancelOrder(ORDER_LOCATION_TELOP);
  }
}

} // namespace gf
