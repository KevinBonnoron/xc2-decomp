#include "gf/menu/object/gf_menu_obj_quest_order.h"

#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_quest_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1e;

// Inferred role: adapter shown by a child of the quest order layout; original name unknown.
struct unknown002 {
  const char *unknown00; // Inferred role: child name; original member name unknown.
  u32 unknown08;         // Inferred role: adapter parameter type; original member name unknown.
};

// Inferred role: adapters of the quest order layout; original name unknown.
static const unknown002 unknown003[21] = {
    {"TXT_questname", GfMenuQuestAdapter::unknown002_0},
    {"TXT_summry_content", GfMenuQuestAdapter::unknown002_1},
    {"IMG_people01", GfMenuQuestAdapter::unknown002_3},
    {"IMG_people02", GfMenuQuestAdapter::unknown002_3 + 1},
    {"IMG_people03", GfMenuQuestAdapter::unknown002_3 + 2},
    {"IMG_people04", GfMenuQuestAdapter::unknown002_3 + 3},
    {"TXT_skill01", GfMenuQuestAdapter::unknown002_15},
    {"TXT_skill02", GfMenuQuestAdapter::unknown002_16},
    {"TXT_taskconditions", GfMenuQuestAdapter::unknown002_17},
    {"TXT_task01_content", GfMenuQuestAdapter::unknown002_18},
    {"TXT_task02_content", GfMenuQuestAdapter::unknown002_18 + 1},
    {"TXT_task03_content", GfMenuQuestAdapter::unknown002_18 + 2},
    {"TXT_task04_content", GfMenuQuestAdapter::unknown002_18 + 3},
    {"TXT_task01_num", GfMenuQuestAdapter::unknown002_22},
    {"TXT_task02_num", GfMenuQuestAdapter::unknown002_22 + 1},
    {"TXT_task03_num", GfMenuQuestAdapter::unknown002_22 + 2},
    {"TXT_task04_num", GfMenuQuestAdapter::unknown002_22 + 3},
    {"TXT_task01_max", GfMenuQuestAdapter::unknown002_26},
    {"TXT_task02_max", GfMenuQuestAdapter::unknown002_26 + 1},
    {"TXT_task03_max", GfMenuQuestAdapter::unknown002_26 + 2},
    {"TXT_task04_max", GfMenuQuestAdapter::unknown002_26 + 3},
};

GfMenuObjQuestOrder::GfMenuObjQuestOrder(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestOrder::~GfMenuObjQuestOrder() { ; }

void GfMenuObjQuestOrder::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 121 as in the original file: it is the line argument of operator new.
#line 121
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
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

void GfMenuObjQuestOrder::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case 2:
    GfMenuObject::termCallContext(handle);
    acc.setTerm();
    break;
  case 8:
    if (event.unknown0c == 1 && unknown0c == 0) {
      GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", true);
      unknown30 = GfMenuCallContext::create();
      GfMenuObjCommonText::open(unknown30, 1, 0);
      GfMenuObject::setCallContextEventHandler(unknown30, handle);
      unknown0c = 1;
      GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    }
    break;
  case 0x21: {
    acc.setDisp(true);
    u32 quest = event.unknown08;
    for (u32 i = 0; i < 21; i++) {
      createAdapter(handle, unknown003[i].unknown00, toQuestID(quest), unknown003[i].unknown08);
    }
    GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", false);
    unknown0c = 0;
    unknown10 = event.unknown08;
    GfMenuObjOperationInfo::open(acc.unknown10, 0, 0, 0);
    break;
  }
  case 0x22:
    acc.setDisp(false);
    GfMenuObject::termCallContext(handle);
    GfMenuObjOperationInfo::close();
    break;
  case 0x41: {
    u32 result = event.unknown10;
    if (event.unknown14 == 0 && result == 0) {
      GfQuestManager::setCurrentQuest(toQuestID(unknown10));
    }
    mm::mtl::safeRelease(unknown30);
    GfMenuObject::addResultCallContext(handle, result, 0);
    close();
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjQuestOrder::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

} // namespace gf
