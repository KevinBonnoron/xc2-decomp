#include "gf/menu/object/gf_menu_obj_quest_order.h"

#include "gf/game/quest/gf_quest_id.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1e;

GfMenuObjQuestOrder::GfMenuObjQuestOrder(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestOrder::~GfMenuObjQuestOrder() { ; }

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

void GfMenuObjQuestOrder::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
