#include "gf/menu/object/gf_menu_obj_bl_detail.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_BL_DETAIL = 80;

GfMenuObjBlDetail::GfMenuObjBlDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjBlDetail::~GfMenuObjBlDetail() { ; }

void GfMenuObjBlDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_BL_DETAIL, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjBlDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlDetail::update() { GfMenuObject::update(); }

void GfMenuObjBlDetail::open(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_BL_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x21;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjBlDetail::nextPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_BL_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjBlDetail::prevPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_BL_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
