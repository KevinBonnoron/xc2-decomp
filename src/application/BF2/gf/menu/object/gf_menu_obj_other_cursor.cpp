#include "gf/menu/object/gf_menu_obj_other_cursor.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_pos_adapter.h"
#include "gf/object/gf_obj_handle.h"
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
    MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    unknown24 = main;
    unknown30 = GfMenuPosAdapter::create(acc.searchChild("LAY_main"), INVALID_HANDLE, nullptr);
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

} // namespace gf
