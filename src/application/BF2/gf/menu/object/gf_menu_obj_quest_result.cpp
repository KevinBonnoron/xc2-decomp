#include "gf/menu/object/gf_menu_obj_quest_result.h"

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
constexpr u32 unknown001 = 0x1f;

// Inferred role: name and update kind of one text of the screen; original name unknown.
struct unknown002 {
  const char *unknown00;
  u32 unknown08;
};

// Inferred role: name and update kind of each text of the screen; original name unknown.
const unknown002 unknown003[] = {
    {"TXT_questname", 0},           {"TXT_summry_content", 1},      {"TXT_result_content", 2},      {"TXT_reward01_content", 0x1e}, {"TXT_reward02_content", 0x1f},
    {"TXT_reward03_content", 0x20}, {"TXT_reward04_content", 0x21}, {"TXT_reward05_content", 0x22}, {"TXT_reward06_content", 0x23}, {"TXT_reward07_content", 0x24},
    {"TXT_reward08_content", 0x25}, {"TXT_reward01_val", 0x26},     {"TXT_reward02_val", 0x27},     {"TXT_reward03_val", 0x28},     {"TXT_reward04_val", 0x29},
    {"TXT_reward05_val", 0x2a},     {"TXT_reward06_val", 0x2b},     {"TXT_reward07_val", 0x2c},     {"TXT_reward08_val", 0x2d},
};

namespace {

constexpr u32 EVENT_UNKNOWN_1 = 1;   // Inferred role: ui event ignored by the listener; original name unknown.
constexpr u32 EVENT_UNKNOWN_2 = 2;   // Inferred role: ui event terminating the call context; original name unknown.
constexpr u32 EVENT_UNKNOWN_3 = 3;   // Inferred role: ui event closing the result screen; original name unknown.
constexpr u32 EVENT_UNKNOWN_8 = 8;   // Inferred role: ui event of the confirm input; original name unknown.
constexpr u32 EVENT_UNKNOWN_11 = 11; // Inferred role: ui event of an elapsed timer; original name unknown.
constexpr u32 EVENT_UNKNOWN_33 = 33; // Inferred role: ui event opening the screen; original name unknown.
constexpr u32 EVENT_UNKNOWN_34 = 34; // Inferred role: ui event closing the screen; original name unknown.

constexpr u32 TIMER_UNKNOWN_1 = 1; // Inferred role: timer started when the screen opens; original name unknown.
constexpr u32 TIMER_UNKNOWN_2 = 2; // Inferred role: timer started after the first one; original name unknown.
constexpr u32 TIMER_UNKNOWN_3 = 3; // Inferred role: timer of the fade out before the result; original name unknown.
constexpr u32 TIMER_UNKNOWN_4 = 4; // Inferred role: timer started by the confirm input; original name unknown.

} // namespace

GfMenuObjQuestResult::GfMenuObjQuestResult(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestResult::~GfMenuObjQuestResult() { ; }

void GfMenuObjQuestResult::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestResult::update() { GfMenuObject::update(); }

void GfMenuObjQuestResult::ListListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case EVENT_UNKNOWN_1:
    break;
  case EVENT_UNKNOWN_2:
    GfMenuObject::termCallContext(handle);
    acc.setTerm();
    break;
  case EVENT_UNKNOWN_3:
    if (unknown0c == 3) {
      GfMenuObject::addResultCallContext(handle, 0, 0);
      unknown0c = 4;
      close();
    }
    break;
  case EVENT_UNKNOWN_8:
    if (event.unknown0c == 1 && unknown0c == 1) {
      GfMenuObjUtil::setChildDisp(handle, "LAY_comp", false);
      GfMenuObjUtil::setChildDisp(handle, "LAY_result", true);
      GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", true);
      GfMenuObject::registTimer(handle, TIMER_UNKNOWN_4, 0.3f, false);
      unknown0c = 2;
      GfMenuObjUtil::playSECommonFromInput(event.unknown0c);
    }
    break;
  case EVENT_UNKNOWN_11:
    switch (event.unknown08) {
    case TIMER_UNKNOWN_1:
      GfMenuObject::releaseTimer(handle);
      GfMenuObject::registTimer(handle, TIMER_UNKNOWN_2, 1.0f, false);
      break;
    case TIMER_UNKNOWN_2:
      GfMenuObject::releaseTimer(handle);
      unknown28 = GfMenuObject::registTimer(handle, TIMER_UNKNOWN_3, 0.5f, false);
      fadeOut(handle);
      break;
    case TIMER_UNKNOWN_3:
      GfMenuObject::releaseTimer(handle);
      GfMenuObjUtil::setChildDisp(handle, "LAY_comp", false);
      GfMenuObjUtil::setChildDisp(handle, "LAY_result", true);
      GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", false);
      fadeIn(handle);
      unknown0c = 1;
      break;
    case TIMER_UNKNOWN_4:
      GfMenuObject::releaseTimer(handle);
      fadeOut(handle);
      unknown0c = 3;
      break;
    }
    break;
  case EVENT_UNKNOWN_33: {
    acc.setDisp(true);
    u32 quest = event.unknown08;
    for (int i = 0; i < 19; i++) {
      createAdapter(handle, unknown003[i].unknown00, toQuestID(quest), unknown003[i].unknown08);
    }
    GfMenuObjUtil::setChildDisp(handle, "LAY_comp", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_result", false);
    GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", false);
    unknown28 = GfMenuObject::registTimer(handle, TIMER_UNKNOWN_1, 0.5f, false);
    fadeIn(handle);
    unknown0c = 0;
    break;
  }
  case EVENT_UNKNOWN_34:
    acc.setDisp(false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_comp", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_result", false);
    GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", false);
    GfMenuObject::termCallContext(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjQuestResult::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjQuestResult::fadeOut(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown00 = 0.5f;
  param.unknown08 = 2;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjQuestResult::fadeIn(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown00 = 0.5f;
  param.unknown08 = 1;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjQuestResult::setScreenMode(u32 handle, u32 mode) {
  bool comp = false;
  bool result = false;
  bool check = false;
  switch (mode) {
  case 0:
    comp = true;
    break;
  case 1:
    result = true;
    break;
  case 3:
    result = true;
    check = true;
    break;
  }
  GfMenuObjUtil::setChildDisp(handle, "LAY_comp", comp);
  GfMenuObjUtil::setChildDisp(handle, "LAY_result", result);
  GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", check);
}

void GfMenuObjQuestResult::setupScreen(u32 handle, QuestID quest) {
  for (int i = 0; i < 19; i++) {
    createAdapter(handle, unknown003[i].unknown00, quest, unknown003[i].unknown08);
  }
  GfMenuObjUtil::setChildDisp(handle, "LAY_comp", true);
  GfMenuObjUtil::setChildDisp(handle, "LAY_result", false);
  GfMenuObjUtil::setChildDisp(handle, "IMG_chkbtn02", false);
}

void GfMenuObjQuestResult::open(GfMenuCallContext *context, QuestID quest) {
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

void GfMenuObjQuestResult::createAdapter(u32 handle, const char *name, QuestID quest, u32 type) {
  ui::UIObjectAcc acc(handle, name);
  if (acc.isValid()) {
    GfMenuQuestAdapter *adapter = GfMenuQuestAdapter::create(acc.unknown10, quest, type, false);
    acc.setDisp(adapter != nullptr);
    switch (type) {
    case 0x1e:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward01", adapter != nullptr);
      break;
    case 0x1f:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward02", adapter != nullptr);
      break;
    case 0x20:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward03", adapter != nullptr);
      break;
    case 0x21:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward04", adapter != nullptr);
      break;
    case 0x22:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward05", adapter != nullptr);
      break;
    case 0x23:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward06", adapter != nullptr);
      break;
    case 0x24:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward07", adapter != nullptr);
      break;
    case 0x25:
      GfMenuObjUtil::setChildDisp(handle, "LAY_reward08", adapter != nullptr);
      break;
    }
  }
}

void GfMenuObjQuestResult::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 126 as in the original file: it is the line argument of operator new.
#line 126
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
    migrateInput(acc.searchChild("LAY_result"), main);
  }
  GfMenuObject::initialize();
}

} // namespace gf
