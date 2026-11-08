#include "gf/menu/object/gf_menu_obj_staffroll.h"

#include "framework/resource/common_resource.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x85;

GfMenuObjStaffroll::GfMenuObjStaffroll(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown64(0.0f), unknown68(0.0f), unknown6c(false) {
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_DEFAULT);
  unknown70 = ui::UISelectObjList::create(param);
}

GfMenuObjStaffroll::~GfMenuObjStaffroll() {
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjStaffroll::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
// __LINE__ must be 107 as in the original file: it is the line argument of operator new.
#line 107
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(unknown001, main.unknown10);
  const char *path = GfMenuManager::isRegionJP() ? "/menu/credit/endroll.crt" : "/menu/credit/endroll_us.crt";
  unknown28 = fw::CommonResource::request(ui::UIUtil::getResourceAllocator(), path, 10, false);
  GfMenuObject::initialize();
}

void GfMenuObjStaffroll::finalize() {
  if (unknown78.capacity() != 0) {
    unknown78.destroy();
  }
  GfMenuObject::finalize();
}

void GfMenuObjStaffroll::fadeout() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
