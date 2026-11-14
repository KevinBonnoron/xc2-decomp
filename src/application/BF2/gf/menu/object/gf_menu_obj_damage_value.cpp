#include "gf/menu/object/gf_menu_obj_damage_value.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"

namespace gf {

// Inferred role: call id of the damage value object; original name unknown.
constexpr u32 unknown001 = 0x2c;

GfMenuObjDamageValue::GfMenuObjDamageValue(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDamageValue::~GfMenuObjDamageValue() { GfMenuManyObjects::destroy<DamageInfo>(GfMenuManyObjects::unknown001_0); }

void GfMenuObjDamageValue::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDamageValue::update() { GfMenuObject::update(); }

void GfMenuObjDamageValue::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
    attachExternalCall(unknown001, main);
// __LINE__ must be 84 as in the original file: it is the line argument of operator new.
#line 84
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
  }
  ui::UIObjectAcc(unknown18).setTerm();
  GfMenuObject::initialize();
  GfMenuManyObjects::unknown002<DamageInfo>(GfMenuManyObjects::unknown001_0, 32);
}

void GfMenuObjDamageValue::removeObject(ui::UIObjectAcc acc) {
  GfMenuManyObjects::remove<DamageInfo>(GfMenuManyObjects::unknown001_0, acc.unknown10);
  acc.setDisp(false);
  acc.setTerm();
}

void GfMenuObjDamageValue::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (root.isValid() && !root.isTerm()) {
    ui::UIObjectAcc acc(handle);
    if (acc.isValid() && acc.isDuplicate()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      event.unknown08_u16 = acc.getDuplicateIndex();
      sendEvent(root.unknown10, event, 0.0f);
    }
  }
}

void GfMenuObjDamageValue::closeAll() {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      GfMenuManyObjects::closeAll<DamageInfo>(GfMenuManyObjects::unknown001_0, close);
    }
  }
}

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDamageValue::DamageInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::push_back(const gf::GfMenuObjDamageValue::DamageInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDamageValue::DamageInfo>::expand(size_t, size_t);
