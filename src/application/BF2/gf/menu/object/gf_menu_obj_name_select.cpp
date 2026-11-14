#include "gf/menu/object/gf_menu_obj_name_select.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjNameSelect::GfMenuObjNameSelect(u32 handle) : GfMenuObject(handle), unknown28(nullptr) { unknown28 = GfMenuCallContext::create(); }

GfMenuObjNameSelect::~GfMenuObjNameSelect() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjNameSelect::initialize() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
// __LINE__ must be 52 as in the original file: it is the line argument of operator new.
#line 52
  MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(acc.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjNameSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjNameSelect::update() { GfMenuObject::update(); }

} // namespace gf
