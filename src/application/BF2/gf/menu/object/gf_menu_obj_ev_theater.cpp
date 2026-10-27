#include "gf/menu/object/gf_menu_obj_ev_theater.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x19;

void GfMenuObjEvTheater::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEvTheater::update() { GfMenuObject::update(); }

void GfMenuObjEvTheater::fadein(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjEvTheater::fadeout(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x101;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
