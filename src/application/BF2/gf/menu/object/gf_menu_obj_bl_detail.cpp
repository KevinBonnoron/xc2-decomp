#include "gf/menu/object/gf_menu_obj_bl_detail.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the blade detail layout; original name unknown.
constexpr u32 CALL_UNKNOWN_80 = 80;

GfMenuObjBlDetail::GfMenuObjBlDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjBlDetail::~GfMenuObjBlDetail() { ; }

void GfMenuObjBlDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_UNKNOWN_80, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjBlDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlDetail::update() { GfMenuObject::update(); }

void GfMenuObjBlDetail::open(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_80)) {
    ui::EventData event;
    event.unknown00 = 0x21;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjBlDetail::close(GfMenuCallContext *context, bool flag) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_80)) {
    ui::EventData event;
    event.unknown00 = 0x22;
    event.unknown08 = flag;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjBlDetail::nextPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_80)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjBlDetail::prevPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_80)) {
    ui::EventData event;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjBlDetail::disp(GfMenuCallContext *context, bool flag) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_80)) {
    ui::EventData event;
    event.unknown00 = 0x104;
    event.unknown08 = flag;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
