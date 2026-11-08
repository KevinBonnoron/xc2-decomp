#include "gf/menu/object/gf_menu_obj_ev_theater.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_msg_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x19;

// Inferred role: off screen call id; original name unknown.
constexpr u32 unknown002 = 0x1a;

GfMenuObjEvTheater::GfMenuObjEvTheater(u32 handle) : GfMenuObject(handle), unknown24(1), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr) {
  unknown28 = GfMenuMsgList::create();
  unknown38 = GfMenuIDList::create();
}

GfMenuObjEvTheater::~GfMenuObjEvTheater() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjEvTheater::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEvTheater::update() { GfMenuObject::update(); }

bool GfMenuObjEvTheater::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

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

void GfMenuObjEvTheater::dispOffScreen(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = isDisp ? GfMenuTypes::unknown003_33 : GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
