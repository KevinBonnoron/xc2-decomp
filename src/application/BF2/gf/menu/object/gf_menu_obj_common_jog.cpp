#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x4a;

GfMenuObjCommonJog::GfMenuObjCommonJog(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(0), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown5c(false), unknown5e(0),
      unknown60(0), unknown64(-1) {}

GfMenuObjCommonJog::~GfMenuObjCommonJog() { ; }

void GfMenuObjCommonJog::update() { GfMenuObject::update(); }

void GfMenuObjCommonJog::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x22;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::disable(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::enable(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x101;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjCommonJog::pop(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
