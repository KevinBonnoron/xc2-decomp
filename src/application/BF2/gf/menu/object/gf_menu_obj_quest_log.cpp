#include "gf/menu/object/gf_menu_obj_quest_log.h"

#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/reference_object.h"
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
// Inferred role: ui event type closing the complete telop; original name unknown.
constexpr u16 unknown006 = 0x103;

GfMenuObjQuestLog::GfMenuObjQuestLog(u32 handle)
    : GfMenuObject(handle), unknown58(false), unknown59(false), unknown5a(false), unknown5b(false), unknown60(this), unknown2f0(this), unknown580(this), unknown810(false), unknown818(false),
      unknown820(nullptr), unknown828(0), unknown82c(0) {}

GfMenuObjQuestLog::~GfMenuObjQuestLog() {
  unknown28 = nullptr;
  unknown30 = nullptr;
  unknown38 = nullptr;
  unknown40 = nullptr;
  unknown48 = nullptr;
  unknown50 = nullptr;
  mm::mtl::safeRelease(unknown820);
}

void GfMenuObjQuestLog::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestLog::lockLogOpen() { GfMenuFlag::set1(0x20, 1); }

void GfMenuObjQuestLog::unlockLogOpen() { GfMenuFlag::set1(0x20, 0); }

bool GfMenuObjQuestLog::seqLogNextEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

bool GfMenuObjQuestLog::seqLogNextWaitInfo() {
  ui::UIObjectAcc acc(unknown18, "LAY_log_info");
  return !GfMenuObjUtil::isBusyCtrl(unknown814);
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

bool GfMenuObjQuestLog::seqLogTaskComplete() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  GfMenuObjUtil::CtrlParam param;
  param.unknown004("fade_in_r");
  GfMenuObjUtil::startCtrl(acc.unknown10, param, "TXT_log_complete");
  unknown2f0.addAnimJob(acc.searchChild("IMG_log_complete_eff"), "clear");
  return true;
}

bool GfMenuObjQuestLog::seqLogOpen() {
  ui::UIObjectAcc base(unknown18, "IMG_log_base");
  if (!unknown810) {
    ui::UIObjectAcc log(unknown18, "LAY_log");
    unknown2f0.addAnimJob(base.unknown10, "info_fade_in");
    log.setDispChild(true, "LAY_log_info");
    log.setDispChild(true, "LAY_log_index@02");
    if (unknown5b) {
      log.setDispChild(true, "LAY_log_to_detail");
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_r");
    param.unknown11 = true;
    param.unknown14 = 8;
    GfMenuObjUtil::startCtrl(unknown18, param, "LAY_log_info");
    GfMenuObjUtil::startCtrl(unknown18, param, "LAY_log_index@02");
    if (!unknown5b) {
      ui::UIObjectAcc(unknown18, "LAY_log_to_detail").setDisp(false);
    } else {
      GfMenuObjUtil::startCtrl(unknown18, param, "LAY_log_to_detail");
    }
    setupLogClear();
    setupLogItem();
    log.setDispChild(false, "LAY_log_index@01");
    unknown810 = true;
  } else if (!base.isPlayingAnimation()) {
    unknown59 = true;
    unknown810 = false;
    ui::UIObjectAcc log(unknown18, "LAY_log");
    enableInput(log.unknown10);
    return true;
  }
  return false;
}

bool GfMenuObjQuestLog::seqLogClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  acc.setDispChild(false, "LAY_log_info");
  acc.setDispChild(false, "LAY_log_to_detail");
  acc.setDispChild(false, "LAY_log_index@02");
  acc.setDispChild(true, "LAY_log_index@01");
  GfMenuObjUtil::CtrlParam param;
  param.unknown004("fade_in_r");
  param.unknown11 = true;
  param.unknown14 = 8;
  unknown814 = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_log_index@01");
  unknown2f0.addAnimJob(acc.searchChild("IMG_log_base"), "info_fade_out");
  unknown2f0.unknown002(&GfMenuObjQuestLog::seqLogCloseEnd);
  return true;
}

bool GfMenuObjQuestLog::seqLogCloseEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  if (!unknown5a) {
    enableInput(acc.unknown10);
  } else {
    unknown2f0.unknown002(&GfMenuObjQuestLog::seqLogOut);
  }
  unknown59 = false;
  return true;
}

bool GfMenuObjQuestLog::seqOrderStart() {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "sample";
  param.unknown58 = "fadein";
  GfMenuObjUtil::startCtrl(unknown18, param, "TXT_order");
  unknown580.unknown004(55);
  unknown580.unknown002(&GfMenuObjQuestLog::seqOrderWaitCtrl);
  GfMenuObjUtil::playJingle(6);
  return true;
}

bool GfMenuObjQuestLog::seqCompleteStart() {
  ui::UIObjectAcc(unknown18, "IMG_complete_base").startAnimation("start", false);
  ui::UIObjectAcc(unknown18, "IMG_complete_eff").startAnimation("start", false);
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "sample";
  param.unknown58 = "fadein";
  GfMenuObjUtil::startCtrl(unknown18, param, "TXT_complete");
  unknown580.unknown004(54);
  unknown580.unknown002(&GfMenuObjQuestLog::seqCompleteWaitCtrl);
  return true;
}

bool GfMenuObjQuestLog::seqLogIn() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  bool isEnd;
  if (!unknown810) {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 0;
    param.unknown04 = 0;
    param.unknown0d = true;
    param.unknown08 = GfMenuObjUtil::getCtrlID(acc.unknown10);
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    isEnd = false;
    unknown810 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    unknown810 = false;
    unknown2f0.unknown002(&GfMenuObjQuestLog::seqLogStart);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjQuestLog::seqOrderWaitCtrl() {
  ui::UIObjectAcc acc(unknown18, "TXT_order");
  if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    return false;
  }
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_zoom";
  param.unknown58 = "fade_out";
  param.unknown14 = 10;
  GfMenuObjUtil::startCtrl(unknown18, param, "TXT_order");
  unknown580.unknown002(&GfMenuObjQuestLog::seqOrderWait);
  return true;
}

bool GfMenuObjQuestLog::seqCompleteWaitCtrl() {
  ui::UIObjectAcc acc(unknown18, "TXT_complete");
  if (GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    return false;
  }
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_zoom";
  param.unknown58 = "fade_out";
  param.unknown14 = 10;
  GfMenuObjUtil::startCtrl(unknown18, param, "TXT_complete");
  unknown580.unknown002(&GfMenuObjQuestLog::seqCompleteWait);
  return true;
}

bool GfMenuObjQuestLog::seqCompleteWait() {
  if (ui::UIObjectAcc(unknown18, "IMG_complete_baae").isPlayingAnimation()) {
    return false;
  }
  if (ui::UIObjectAcc(unknown18, "IMG_complete_eff").isPlayingAnimation()) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_complete");
  ui::EventData event;
  event.unknown00 = unknown006;
  sendEvent(acc.unknown10, event, 0.0f);
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInScenario() {
  unknown005("TXT_title_sub_scenario");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInText() {
  unknown005("TXT_title");
  if (!unknown818) {
    GfMenuObjUtil::playJingle(7);
  }
  return true;
}

bool GfMenuObjQuestLog::seqLogOut() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  bool isEnd;
  if (!unknown810) {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown0d = true;
    param.unknown08 = GfMenuObjUtil::getCtrlID(acc.unknown10);
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    isEnd = false;
    unknown810 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    isEnd = true;
    unknown810 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjQuestLog::seqTitleFadeOutScenario() {
  unknown004("TXT_title_sub_scenario");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInNormal() {
  unknown005("TXT_title_sub_normal");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeOutNormal() {
  unknown004("TXT_title_sub_normal");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeOutText() {
  unknown004(nullptr);
  return true;
}

void GfMenuObjQuestLog::changeActiveQuest() { unknown147(unknown001, "LAY_log", unknown002); }

void GfMenuObjQuestLog::updateTask() { unknown147(unknown001, "LAY_log", unknown003); }

void GfMenuObjQuestLog::closeLog() { unknown148(unknown001, "LAY_log", GfMenuTypes::unknown003_34); }

void GfMenuObjQuestLog::openLog() { unknown148(unknown001, "LAY_log", GfMenuTypes::unknown003_33); }

u32 GfMenuObjQuestLog::nextTaskIndex(u32 index) {
  QuestID quest;
  unknown30->getQuest(quest);
  for (u32 next = index + 1; next < unknown828; next++) {
    QuestTaskParam param(quest, next, TASK_STATE_NONE);
    if (GfQuestInfo::getTaskHide(param) == 0) {
      return next;
    }
  }
  return index;
}

void GfMenuObjQuestLog::order(GfMenuCallContext *context, QuestID quest) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::UIObjectAcc order(acc.searchChild("LAY_order"));
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown08 = quest.unknown00;
      event.unknown0c = 0;
      sendEvent(order.unknown10, event, 0.0f);
      startCallContext(context, unknown001, order.unknown10);
    }
  }
}

void GfMenuObjQuestLog::complete(GfMenuCallContext *context, QuestID quest) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::UIObjectAcc complete(acc.searchChild("LAY_complete"));
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      event.unknown08 = quest.unknown00;
      event.unknown0c = 0;
      sendEvent(complete.unknown10, event, 0.0f);
      startCallContext(context, unknown001, complete.unknown10);
    }
  }
}

void GfMenuObjQuestLog::completeTask(const QuestTaskParam &param) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::UIObjectAcc log(acc.searchChild("LAY_log"));
    ui::EventData event;
    event.unknown00 = 0x102;
    event.unknown08 = param.unknown04.unknown00;
    event.unknown0c = param.unknown0c;
    sendEvent(log.unknown10, event, 0.0f);
  }
}

} // namespace gf
