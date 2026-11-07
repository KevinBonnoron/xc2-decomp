#include "gf/menu/object/gf_menu_obj_sort.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x83;

GfMenuObjSort::GfMenuObjSort(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(0) {}

void GfMenuObjSort::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSort::update() {
  if (unknown24 != 0) {
    ui::UIObjectAcc acc(unknown24);
    if (!acc.isValid() || acc.isTerm()) {
      unknown155(unknown001, GfMenuTypes::unknown003_34);
    }
  }
  GfMenuObject::update();
}

void GfMenuObjSort::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
