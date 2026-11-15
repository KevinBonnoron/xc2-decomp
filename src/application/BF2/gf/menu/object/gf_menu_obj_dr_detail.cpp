#include "gf/menu/object/gf_menu_obj_dr_detail.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the driver detail layout; original name unknown.
constexpr u32 CALL_UNKNOWN_81 = 81;

// Inferred role: layouts of the detail pages; original name unknown.
static const char *const unknown002[] = {
    "LAY_status_b",
    "LAY_status_a",
    "LAY_blade",
    "LAY_arts",
    "LAY_equip",
    "LAY_idea",
    "LAY_favorite",
};

GfMenuObjDrDetail::GfMenuObjDrDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDrDetail::~GfMenuObjDrDetail() { ; }

void GfMenuObjDrDetail::create(GfMenuCallContext *context, const CreateParam &param, bool isOpen) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc main(getAttachedObject(CALL_UNKNOWN_81));
    if (main.isValid() && param.unknown00 != 0 && param.unknown08.width != 0 && param.unknown08.height != 0) {
      u32 object;
      if (param.unknown14 == 0) {
        object = main.duplicateChild("LAY_dr_detail");
      } else {
        ui::UIObjectAcc detail(main.unknown10, "LAY_dr_detail");
        object = detail.duplicate(param.unknown14);
      }
      if (object != 0) {
// __LINE__ must be 120 as in the original file: it is the line argument of operator new.
#line 120
        DetailListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DetailListener();
        listener->addRef();
        ui::UIEventManager::get()->registObjectListener(object, listener);
        if (listener != nullptr) {
          listener->release();
        }
        u32 count = 0;
        // Ruling 3: name ends with this block; its stack slot (sp+0x70) is shared with the ui::EventData of the inlined open() (frame 0x110, not 0x120).
        {
          mm::mtl::FixStr<32> name;
          for (u32 i = 0; i < 7; i++) {
            if ((param.unknown00 & (1 << i)) != 0) {
              if (!param.unknown10) {
                name.format("LAY_index@%02d", i + 1);
                ui::UIObjectAcc(main.unknown10, name.c_str()).duplicate(object);
              }
              ui::UIObjectAcc(main.unknown10, unknown002[i]).duplicate(object);
              count++;
            }
          }
        }
        if (count > 1) {
          ui::UIObjectAcc(main.unknown10, "LAY_page").duplicate(object);
        }
        ui::EventData event;
// __LINE__ must be 157 as in the original file: it is the line argument of operator new.
#line 157
        CreateParam *copy = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CreateParam();
        *copy = param;
        event.unknown00 = GfMenuTypes::unknown003_257;
        event.unknown08_u64 = reinterpret_cast<u64>(copy);
        event.unknown10 = count;
        sendEvent(object, event, 0.0f);
        startCallContext(context, CALL_UNKNOWN_81, object);
        if (isOpen) {
          open(context);
        }
      }
    }
  }
}

void GfMenuObjDrDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_UNKNOWN_81, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjDrDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrDetail::update() { GfMenuObject::update(); }

void GfMenuObjDrDetail::open(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_81)) {
    ui::EventData event;
    event.unknown00 = 0x21;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjDrDetail::close(GfMenuCallContext *context, bool flag) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_81)) {
    ui::EventData event;
    event.unknown00 = 0x22;
    event.unknown08 = flag;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjDrDetail::nextPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_81)) {
    ui::EventData event;
    event.unknown00 = 0x102;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjDrDetail::prevPage(GfMenuCallContext *context) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_81)) {
    ui::EventData event;
    event.unknown00 = 0x103;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

void GfMenuObjDrDetail::disp(GfMenuCallContext *context, bool flag) {
  if (context != nullptr && GfMenuObjUtil::checkCCNext(context, CALL_UNKNOWN_81)) {
    ui::EventData event;
    event.unknown00 = 0x104;
    event.unknown08 = flag;
    GfMenuObject::sendEvent(context->unknown14, event, 0.0f);
  }
}

} // namespace gf
