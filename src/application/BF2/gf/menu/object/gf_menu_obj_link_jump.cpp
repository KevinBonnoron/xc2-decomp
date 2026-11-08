#include "gf/menu/object/gf_menu_obj_link_jump.h"

#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h" // IWYU pragma: keep
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x49;

GfMenuObjLinkJump::GfMenuObjLinkJump(u32 handle) : GfMenuObject(handle), unknown28(), unknown68(nullptr), unknown70(nullptr), unknown78(false) {}

GfMenuObjLinkJump::~GfMenuObjLinkJump() {
  for (int i = 0; i < 2; i++) {
    mm::mtl::safeRelease(unknown28[i].unknown18);
    mm::mtl::safeRelease(unknown28[i].unknown08);
    mm::mtl::safeRelease(unknown28[i].unknown10);
  }
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
}

void GfMenuObjLinkJump::finalize() {
  GfMenuReference::clearLinkList();
  GfMenuObject::finalize();
}

void GfMenuObjLinkJump::update() { GfMenuObject::update(); }

void GfMenuObjLinkJump::close() {}

void GfMenuObjLinkJump::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
