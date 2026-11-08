#include "gf/menu/object/gf_menu_obj_staffroll.h"

#include "framework/resource/common_resource.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"

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

void GfMenuObjStaffroll::fadeout() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
