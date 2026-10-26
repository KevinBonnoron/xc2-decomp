#include "gf/menu/object/gf_menu_obj_dr_detail.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_DR_DETAIL = 81;

GfMenuObjDrDetail::GfMenuObjDrDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDrDetail::~GfMenuObjDrDetail() { ; }

void GfMenuObjDrDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_DR_DETAIL, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjDrDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrDetail::update() { GfMenuObject::update(); }

void GfMenuObjDrDetail::open(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_DR_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x21;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjDrDetail::nextPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_DR_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjDrDetail::prevPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_DR_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
