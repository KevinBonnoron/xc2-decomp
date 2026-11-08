#include "gf/menu/object/gf_menu_obj_common_jog.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id; original name unknown.
constexpr u32 unknown001 = 0x4a;

GfMenuObjCommonJog::GfMenuObjCommonJog(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(0), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown5c(false), unknown5e(0),
      unknown60(0), unknown64(-1) {}

GfMenuObjCommonJog::~GfMenuObjCommonJog() { ; }

void GfMenuObjCommonJog::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
#line 74
    MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main.unknown10);
    main.setDisp(false);
    disableInput(main.unknown10);
    ui::UISelectObjList::CreateParam param;
    param.allocator = getAllocator(ALLOCATOR_DEFAULT);
    unknown28 = ui::UISelectObjList::create(param);
    unknown30 = ui::UISelectObjList::create(param);
    GfMenuObject::initialize();
  }
}

void GfMenuObjCommonJog::finalize() {
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  GfMenuObject::finalize();
}

void GfMenuObjCommonJog::update() { GfMenuObject::update(); }

void GfMenuObjCommonJog::open(GfMenuCallContext *context, const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = 0x21;
    event.unknown08 = param.unknown00;
    event.unknown0c = param.unknown04;
    sendEvent(acc.unknown10, event, 0.0f);
    if (context != nullptr) {
      startCallContext(context, unknown001, acc.unknown10);
    }
  }
}

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
