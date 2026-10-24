#include "gf/menu/object/gf_menu_obj_chain_count.h"

#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_battle_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_CHAIN_COUNT = 64;

GfMenuObjChainCount::GfMenuObjChainCount(u32 handle) : GfMenuObject(handle) {}

GfMenuObjChainCount::~GfMenuObjChainCount() { ; }

void GfMenuObjChainCount::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (!main.isValid()) {
    return;
  }
// __LINE__ must be 58 as in the original file: it is the line argument of operator new.
#line 58
  MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
  listener->addRef();
  ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
  if (listener != nullptr) {
    listener->release();
  }
  attachExternalCall(CALL_CHAIN_COUNT, main.unknown10);
  GfMenuBattleAdapter::create(main.searchChild("TXT_num"), 11);
  addNumberEventCondition(main.unknown10, "TXT_num", 0, 0, 0.0f);
  GfMenuObject::initialize();
}

void GfMenuObjChainCount::finalize() { GfMenuObject::finalize(); }

void GfMenuObjChainCount::update() { GfMenuObject::update(); }

void GfMenuObjChainCount::open() {
  ui::UIObjectAcc acc(getAttachedObject(CALL_CHAIN_COUNT));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::UI_EVENT_OPEN;
    sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjChainCount::close() {
  ui::UIObjectAcc acc(getAttachedObject(CALL_CHAIN_COUNT));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::UI_EVENT_CLOSE;
    sendEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
