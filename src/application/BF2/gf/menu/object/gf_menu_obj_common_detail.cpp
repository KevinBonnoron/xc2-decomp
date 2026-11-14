#include "gf/menu/object/gf_menu_obj_common_detail.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the common detail layout; original name unknown.
constexpr u32 CALL_UNKNOWN_79 = 79;

GfMenuObjCommonDetail::GfMenuObjCommonDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonDetail::~GfMenuObjCommonDetail() { ; }

void GfMenuObjCommonDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_UNKNOWN_79, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjCommonDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonDetail::update() { GfMenuObject::update(); }

void GfMenuObjCommonDetail::open(GfMenuCallContext *context, const OpenParam &param) {
  ui::UIObjectAcc main(getAttachedObject(CALL_UNKNOWN_79));
  if (main.isValid() && param.unknown00.size() != 0) {
    u32 parent = main.unknown10;
    if (param.unknown2c != 0) {
      parent = param.unknown2c;
    }
    u32 object = 0;
    switch (param.unknown1c) {
    case 0:
      object = ui::UIObjectAcc(main.unknown10, "LAY_dr_root").duplicate(parent);
      break;
    case 1:
      object = ui::UIObjectAcc(main.unknown10, "LAY_bl_root").duplicate(parent);
      break;
    }
    if (object != 0) {
// __LINE__ must be 82 as in the original file: it is the line argument of operator new.
#line 82
      DetailListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DetailListener();
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(object, listener);
      if (listener != nullptr) {
        listener->release();
      }
// __LINE__ must be 85 as in the original file: it is the line argument of operator new.
#line 85
      OpenParam *copy = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OpenParam();
      *copy = param;
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown08_u64 = reinterpret_cast<u64>(copy);
      sendEvent(object, event, 0.0f);
      if (context != nullptr && GfMenuObjUtil::checkCCStart(context)) {
        startCallContext(context, CALL_UNKNOWN_79, object);
      }
    }
  }
}

void GfMenuObjCommonDetail::close(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_79)) {
    ui::EventData event;
    event.unknown00 = 0x22;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
