#include "gf/menu/object/gf_menu_obj_common_detail.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_COMMON_DETAIL = 79;

GfMenuObjCommonDetail::GfMenuObjCommonDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonDetail::~GfMenuObjCommonDetail() { ; }

void GfMenuObjCommonDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_COMMON_DETAIL, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjCommonDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonDetail::update() { GfMenuObject::update(); }

void GfMenuObjCommonDetail::close(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_COMMON_DETAIL)) {
    ui::EventData event;
    event.unknown00 = 0x22;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
