#include "gf/menu/object/gf_menu_obj_event_skip.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_EVENT_SKIP = 47;

GfMenuObjEventSkip::GfMenuObjEventSkip(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEventSkip::~GfMenuObjEventSkip() { ; }

void GfMenuObjEventSkip::initialize() {
  ui::UIObjectAcc acc(handle);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 72 as in the original file: it is the line argument of operator new.
#line 72
    ListListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(CALL_EVENT_SKIP, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjEventSkip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEventSkip::update() { GfMenuObject::update(); }

void GfMenuObjEventSkip::close() {
  u32 object = getAttachedObject(CALL_EVENT_SKIP);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      ui::EventData event;
      event.type = GfMenuTypes::UI_EVENT_CLOSE;
      sendEvent(object, event, 0.0f);
    }
  }
}

u32 GfMenuObjEventSkip::setupScreen(u32 screen) { return screen; }

void GfMenuObjEventSkip::open(GfMenuCallContext *context) {
  u32 object = getAttachedObject(CALL_EVENT_SKIP);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      startCallContext(context, CALL_EVENT_SKIP, object);
      ui::EventData event;
      event.type = GfMenuTypes::UI_EVENT_OPEN;
      sendEvent(object, event, 0.0f);
      GfMenuObjUtil::playSE(3);
    }
  }
}

} // namespace gf
