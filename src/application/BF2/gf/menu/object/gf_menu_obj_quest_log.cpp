#include "gf/menu/object/gf_menu_obj_quest_log.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/adapter/gf_menu_quest_adapter.h"
#include "gf/menu/adapter/gf_menu_reference_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_quest_reward.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
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

void GfMenuObjQuestLog::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(unknown001, main.unknown10);
    unknown28 = unknown161();
    unknown30 = unknown161();
    unknown38 = unknown161();
    unknown40 = unknown160();
    unknown48 = unknown160();
    unknown50 = GfMenuReferenceItem::unknown001();
    unknown38->unknown0c = QuestID();
    {
      ui::UIObjectAcc title(main.unknown10, "LAY_title");
      GfMenuQuestAdapter::createFromReference(title.searchChild("TXT_title"), unknown28, 0, false);
// The four listener registrations of this function (here and at lines 175, 197 and 217 of the original file) repeat the same statements
// (add a reference, register, release): written out because a file-local helper taking the listener compiles to 1023 instructions
// against the game's 1019 (ruling 8; the same block is written out in the other menu objects' initialize).
// __LINE__ must be 138 as in the original file: it is the line argument of operator new.
#line 138
      TitleListener *titleListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) TitleListener(this);
      titleListener->addRef();
      ui::UIEventManager::get()->registObjectListener(title.unknown10, titleListener);
      if (titleListener != nullptr) {
        titleListener->release();
      }
    }
    {
      ui::UIObjectAcc log(main.unknown10, "LAY_log");
      GfMenuQuestAdapter *adapter = GfMenuQuestAdapter::createFromReference(log.searchChild("TXT_log_info_task"), unknown30, 0x2e, false);
      if (adapter != nullptr) {
        adapter->unknown008(unknown40);
      }
      adapter = GfMenuQuestAdapter::createFromReference(log.searchChild("TXT_log_info_task_item_num"), unknown30, 0x2f, true);
      if (adapter != nullptr) {
        adapter->unknown008(unknown40);
      }
      adapter = GfMenuQuestAdapter::createFromReference(log.searchChild("TXT_log_info_task_item_max"), unknown30, 0x30, false);
      if (adapter != nullptr) {
        adapter->unknown008(unknown40);
      }
      adapter = GfMenuQuestAdapter::createFromReference(log.searchChild("IMG_log_cond"), unknown30, 0x35, false);
      if (adapter != nullptr) {
        adapter->unknown008(unknown40);
      }
      GfMenuItemAdapter::createFromReference(log.searchChild("TXT_log_info_task_item"), 0, unknown50.get(), false);
      GfMenuReferenceAdapter *pageAdapter = GfMenuReferenceAdapter::create(log.searchChild("TXT_log_info_task_page_num"), unknown40, true);
      if (pageAdapter != nullptr) {
        pageAdapter->unknown44 = 1;
      }
      GfMenuReferenceAdapter::create(log.searchChild("TXT_log_info_task_page_max"), unknown48, true);
// __LINE__ must be 175 as in the original file: it is the line argument of operator new.
#line 175
      LogListener *logListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) LogListener(this);
      logListener->addRef();
      ui::UIEventManager::get()->registObjectListener(log.unknown10, logListener);
      if (logListener != nullptr) {
        logListener->release();
      }
      addNumberEventCondition(log.unknown10, "TXT_log_info_task_item_num", 1, 0);
      ui::UIObjectAcc base(log.unknown10, "IMG_log_base");
      base.startAnimation("log_fade_in", false);
      log.setDispChild(true, "LAY_log_index@01");
    }
    {
      ui::UIObjectAcc order(main.unknown10, "LAY_order");
// __LINE__ must be 197 as in the original file: it is the line argument of operator new.
#line 197
      OrderListener *orderListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) OrderListener(this);
      orderListener->addRef();
      ui::UIEventManager::get()->registObjectListener(order.unknown10, orderListener);
      if (orderListener != nullptr) {
        orderListener->release();
      }
    }
    {
      ui::UIObjectAcc complete(main.unknown10, "LAY_complete");
      GfMenuQuestAdapter::createFromReference(complete.searchChild("TXT_comp_ret_win_title"), unknown38, 0, false);
      GfMenuQuestAdapter::createFromReference(complete.searchChild("TXT_comp_ret_win_result"), unknown38, 2, false);
      GfMenuQuestAdapter::createFromReference(complete.searchChild("IMG_comp_ret_thumb"), unknown38, 0x39, false);
// __LINE__ must be 217 as in the original file: it is the line argument of operator new.
#line 217
      CompleteListener *completeListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) CompleteListener(this);
      completeListener->addRef();
      ui::UIEventManager::get()->registObjectListener(complete.unknown10, completeListener);
      if (completeListener != nullptr) {
        completeListener->release();
      }
    }
    GfMenuObject::initialize();
  }
}

void GfMenuObjQuestLog::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestLog::lockLogOpen() { GfMenuFlag::set1(0x20, 1); }

void GfMenuObjQuestLog::unlockLogOpen() { GfMenuFlag::set1(0x20, 0); }

bool GfMenuObjQuestLog::seqOrderActivation() {
  if (!unknown810) {
    GfMenuManager::openCommonWindow(1);
    unknown810 = true;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result == 0) {
    QuestID quest;
    unknown38->getQuest(quest);
    GfQuestManager::setCurrentQuest(quest);
  }
  ui::UIObjectAcc acc(unknown18, "LAY_order");
  ui::EventData event;
  event.unknown00 = unknown006;
  sendEvent(acc.unknown10, event, 0.0f);
  unknown810 = false;
  return true;
}

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

void GfMenuObjQuestLog::setupLog() {
  QuestID quest;
  unknown30->getQuest(quest);
  unknown5b = QuestListAcc::get()->getListVisible(quest) == 1;
  if (unknown59) {
    ui::UIObjectAcc acc(unknown18, "LAY_log_to_detail");
    acc.setDisp(unknown5b);
    GfMenuManager::setEnableQuestOpen(unknown5b);
  }
  u32 taskCount;
  u32 completeCount;
  GfQuestInfo::getQuestTaskInfo(taskCount, completeCount, quest);
  unknown828 = taskCount;
  for (u32 index = 0; index < unknown828; index++) {
    QuestTaskParam param(quest, index, TASK_STATE_UNKNOWN_0);
    if (GfQuestInfo::getTaskHide(param) == 1) {
      taskCount--;
    }
  }
  unknown40->unknown162(0);
  unknown48->unknown162(taskCount);
}

void GfMenuObjQuestLog::setupLogClear() {
  QuestID quest;
  unknown30->getQuest(quest);
  QuestTaskParam param(quest, unknown40->unknown0c, TASK_STATE_UNKNOWN_0);
  bool isComplete = GfQuestTask::isCompleteFlag(param);
  ui::UIObjectAcc acc(unknown18, "IMG_log_complete");
  acc.setImageIndex(!isComplete);
}

void GfMenuObjQuestLog::setupLogItem() {
  QuestID quest;
  GfQuestTaskLogResult result;
  unknown30->getQuest(quest);
  QuestTaskParam param(quest, unknown40->unknown0c, TASK_STATE_UNKNOWN_0);
  GfQuestUtil::getMsgQuestTaskLog(result, param);
  u32 item = result.unknown1c;
  ItemType::Type type = GfItemUtil::getType(item);
  MenuItemInfo &info = unknown50->unknown0c;
  info.unknown04 = item;
  info.unknown00 = type;
  info.unknown08 = 1;
  info.unknown0c = GfItemHandle(0);
  ui::UIObjectAcc acc(unknown18, "LAY_log_info_task_item");
  acc.setDisp(result.unknown14 != 0);
}

u32 GfMenuObjQuestLog::nextTaskIndex(u32 index) {
  QuestID quest;
  unknown30->getQuest(quest);
  for (u32 next = index + 1; next < unknown828; next++) {
    QuestTaskParam param(quest, next, TASK_STATE_UNKNOWN_0);
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

void GfMenuObjQuestLog::CompleteListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    disableInput(acc.unknown10);
    break;
  case 3:
    if (event.unknown08 == 1) {
      enableInput(acc.unknown10);
    } else if (event.unknown08 == 2) {
      unknown20->unknown38->unknown0c = QuestID();
      termCallContext(acc.unknown10);
      acc.setDisp(false);
    }
    break;
  case 8:
    if (event.unknown0c == 1) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_out_l");
      param.unknown14 = 10;
      param.unknown04 = 2;
      int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_comp_result");
      hookCtrlEvent(acc.unknown10, ctrl);
      disableInput(acc.unknown10);
      GfMenuObjUtil::playSECommonDecide();
    }
    break;
  case GfMenuTypes::unknown003_33: {
    if (unknown20->unknown820 == nullptr) {
      unknown20->unknown820 = GfMenuCallContext::create();
      GfMenuObjQuestReward::OpenParam param;
      param.unknown00 = unknown20->unknown38;
      param.unknown08 = acc.searchChild("LAY_comp_ret_reward");
      GfMenuObjQuestReward::create(unknown20->unknown820, param, false);
    }
    unknown20->unknown818 = false;
    ui::EventData title;
    title.unknown0c = 0;
    title.unknown00 = GfMenuTypes::unknown003_33;
    title.unknown08 = event.unknown08;
    sendEvent(acc.searchSibiling("LAY_title"), title, 0.0f);
    unknown20->unknown38->unknown0c = toQuestID(event.unknown08);
    unknown20->unknown580.unknown005();
    unknown20->unknown580.unknown004(75);
    unknown20->unknown580.unknown002(&GfMenuObjQuestLog::seqCompleteStart);
    GfMenuObjQuestReward::open(unknown20->unknown820, false);
    acc.setDisp(true);
    break;
  }
  case unknown006: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l");
    param.unknown11 = true;
    param.unknown04 = 1;
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_comp_result");
    hookCtrlEvent(acc.unknown10, ctrl);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjQuestLog::TitleListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    break;
  case GfMenuTypes::unknown003_33: {
    QuestID quest = toQuestID(event.unknown08);
    unknown20->unknown28->unknown0c = quest;
    unknown20->unknown60.unknown005();
    unknown20->unknown60.unknown002(&GfMenuObjQuestLog::seqTitleStart);
    acc.setDisp(true);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjQuestLog::OrderListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    disableInput(acc.unknown10);
    break;
  case unknown006:
    unknown20->unknown38->unknown0c = QuestID();
    termCallContext(acc.unknown10);
    break;
  case GfMenuTypes::unknown003_33: {
    unknown20->unknown818 = true;
    ui::EventData title;
    title.unknown0c = 0;
    title.unknown00 = GfMenuTypes::unknown003_33;
    title.unknown08 = event.unknown08;
    sendEvent(acc.searchSibiling("LAY_title"), title, 0.0f);
    unknown20->unknown38->unknown0c = toQuestID(event.unknown08);
    unknown20->unknown580.unknown005();
    unknown20->unknown580.unknown004(75);
    unknown20->unknown580.unknown002(&GfMenuObjQuestLog::seqOrderStart);
    acc.setDisp(true);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
