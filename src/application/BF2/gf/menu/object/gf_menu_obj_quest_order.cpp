#include "gf/menu/object/gf_menu_obj_quest_order.h"

#include "gf/game/quest/gf_quest_id.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_quest_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1e;

GfMenuObjQuestOrder::GfMenuObjQuestOrder(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestOrder::~GfMenuObjQuestOrder() { ; }

void GfMenuObjQuestOrder::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 121 as in the original file: it is the line argument of operator new.
#line 121
    ListListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjQuestOrder::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestOrder::update() { GfMenuObject::update(); }

void GfMenuObjQuestOrder::open(GfMenuCallContext *context, QuestID quest) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      startCallContext(context, unknown001, handle);
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown08 = quest.unknown00 | (quest.unknown02 << 16);
      sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjQuestOrder::createAdapter(u32 handle, const char *name, QuestID quest, u32 type) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    GfMenuQuestAdapter *adapter = GfMenuQuestAdapter::create(acc.unknown10, quest, type, false);
    acc.setDisp(adapter != nullptr);
    switch (type) {
    case GfMenuQuestAdapter::unknown002_18:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task01", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_18 + 1:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task02", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_18 + 2:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task03", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_18 + 3:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task04", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_26:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task01_count", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_26 + 1:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task02_count", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_26 + 2:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task03_count", adapter != nullptr);
      break;
    case GfMenuQuestAdapter::unknown002_26 + 3:
      GfMenuObjUtil::setChildDisp(handle, "LAY_task04_count", adapter != nullptr);
      break;
    }
  }
}

void GfMenuObjQuestOrder::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
