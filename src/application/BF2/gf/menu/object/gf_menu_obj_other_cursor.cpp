#include "gf/menu/object/gf_menu_obj_other_cursor.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the cursor; original name unknown.
constexpr u32 unknown001 = 0x13;

GfMenuObjOtherCursor::GfMenuObjOtherCursor(u32 handle) : GfMenuObject(handle), unknown24(0), unknown30(nullptr) {}

GfMenuObjOtherCursor::~GfMenuObjOtherCursor() { ; }

void GfMenuObjOtherCursor::initialize() {
  ui::UIObjectAcc acc(unknown18);
  attachExternalCall(unknown001, unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 86 as in the original file: it is the line argument of operator new.
#line 86
    MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    unknown24 = main;
    unknown30 = GfMenuPosAdapter::create(acc.searchChild("LAY_main"), unknown020, nullptr);
    unknown30->setPosOffsMode(1);
  }
  GfMenuObject::initialize();
}

void GfMenuObjOtherCursor::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOtherCursor::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x13));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjOtherCursor::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
  case GfMenuTypes::unknown003_257:
    acc.setDisp(false);
    break;
  case 0x100: {
    u32 param = event.unknown08;
    if (param == 0) {
      ui::UIObjectAcc child(acc.unknown10, "IMG_other_cursor");
      child.startAnimation("focus_s", false);
    } else if (param == 1) {
      ui::UIObjectAcc child(acc.unknown10, "IMG_symbol_cursor");
      child.startAnimation("focus_l", false);
    }
    GfMenuObjUtil::playSE(0x1c);
    acc.setDispChild(param == 0, "LAY_other_cursor");
    acc.setDispChild(param == 1, "LAY_symbol_cursor");
    acc.setDisp(true);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
