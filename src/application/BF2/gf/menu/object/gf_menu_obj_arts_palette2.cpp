#include "gf/menu/object/gf_menu_obj_arts_palette2.h"

#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x28;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

GfMenuObjArtsPalette2::GfMenuObjArtsPalette2(u32 handle) : GfMenuObject(handle), unknown24(-1), unknown28(nullptr), unknown30(nullptr), unknown38(0), unknown40(0), unknown48(0) {}

GfMenuObjArtsPalette2::~GfMenuObjArtsPalette2() {
  unknown50 = nullptr;
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
}

void GfMenuObjArtsPalette2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette2::update() {
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  acc.setAlpha(0.0f);
  GfMenuObject::update();
}

void GfMenuObjArtsPalette2::close() { unknown146(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjArtsPalette2::open() { unknown146(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjArtsPalette2::resetSelection() { unknown146(unknown001, unknown002); }

void GfMenuObjArtsPalette2::attachCallContext(GfMenuCallContext *context) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm() && GfMenuObjUtil::checkCCStart(context)) {
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
  }
}

void GfMenuObjArtsPalette2::setArtsSelection(GfMenuCallContext *context, bool isSelection) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm() && GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x100;
    event.unknown08 = isSelection;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
