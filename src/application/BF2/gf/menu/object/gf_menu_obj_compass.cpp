#include "gf/menu/object/gf_menu_obj_compass.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x42;
// Inferred role: second attached call id; original name unknown.
constexpr u32 unknown002 = 0x43;

mm::mtl::FixedVector<GfMenuObjCompass::unknown004, 32> GfMenuObjCompass::m_IconObjList;

GfMenuObjCompass::GfMenuObjCompass(u32 handle) : GfMenuObject(handle) { m_IconObjList.clear(); }

GfMenuObjCompass::~GfMenuObjCompass() { ; }

void GfMenuObjCompass::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCompass::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCompass::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

void GfMenuObjCompass::dispInBattle(bool isDisp) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = 0x101;
      event.unknown08 = isDisp;
      sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjCompass::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  attachExternalCall(unknown001, main.unknown10);
  attachExternalCall(unknown002, main.unknown10);
// __LINE__ must be 83 as in the original file: it is the line argument of operator new.
#line 83
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  GfMenuObject::initialize();
}

} // namespace gf
