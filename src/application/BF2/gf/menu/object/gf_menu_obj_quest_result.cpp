#include "gf/menu/object/gf_menu_obj_quest_result.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1f;

GfMenuObjQuestResult::GfMenuObjQuestResult(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestResult::~GfMenuObjQuestResult() { ; }

void GfMenuObjQuestResult::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestResult::update() { GfMenuObject::update(); }

void GfMenuObjQuestResult::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
