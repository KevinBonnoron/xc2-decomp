#include "gf/menu/object/gf_menu_obj_quest_log.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x20;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x104;

void GfMenuObjQuestLog::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestLog::lockLogOpen() { GfMenuFlag::set1(0x20, 1); }

void GfMenuObjQuestLog::unlockLogOpen() { GfMenuFlag::set1(0x20, 0); }

bool GfMenuObjQuestLog::seqLogNextEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

bool GfMenuObjQuestLog::seqLogStart() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

bool GfMenuObjQuestLog::seqTitleEndWait() {
  ui::UIObjectAcc acc(unknown18, "IMG_title_base");
  bool isEnd;
  if (acc.isPlayingAnimation()) {
    isEnd = false;
  } else {
    acc.setDisp(false);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjQuestLog::seqOrderWait() {
  ui::UIObjectAcc acc(unknown18, "TXT_order");
  return !GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10));
}

void GfMenuObjQuestLog::changeActiveQuest() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.searchChild("LAY_log"), event, 0.0f);
  }
}

void GfMenuObjQuestLog::updateTask() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = unknown003;
    GfMenuObject::sendEvent(acc.searchChild("LAY_log"), event, 0.0f);
  }
}

void GfMenuObjQuestLog::closeLog() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc child(acc.searchChild("LAY_log"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

void GfMenuObjQuestLog::openLog() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc child(acc.searchChild("LAY_log"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

} // namespace gf
