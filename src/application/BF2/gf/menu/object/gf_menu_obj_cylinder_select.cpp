#include "gf/menu/object/gf_menu_obj_cylinder_select.h"

#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x46;
// Inferred role: active adapter category; original name unknown.
constexpr u32 unknown002 = 2;

GfMenuObjCylinderSelect::GfMenuObjCylinderSelect(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr) {
  unknown40 = GfMenuCallContext::create();
}

GfMenuObjCylinderSelect::~GfMenuObjCylinderSelect() {
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjCylinderSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCylinderSelect::update() { GfMenuObject::update(); }

void GfMenuObjCylinderSelect::open(GfMenuCallContext *context, u32 cylinder) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown08 = cylinder;
    event.unknown0c = 0;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    acc.setSuspend(false);
    GfMenuAdapterManager::addActiveCategory(unknown002);
  }
}

void GfMenuObjCylinderSelect::close(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (!GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuAdapterManager::delActiveCategory(unknown002);
  }
}

} // namespace gf
