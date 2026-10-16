#include "gf/game/quest/gf_quest_manager.h"
#include "gf/data/gf_data_quest.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_event.h"
#include "gf/game/quest/gf_quest_target.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/request/gf_req_scom.h"

namespace gf {

GfBdatQuest *GfQuestManager::s_bdat;
GfQuestEvent *GfQuestManager::s_event;
GfQuestTarget *GfQuestManager::s_target;
GfQuestManager *GfQuestManager::s_pThis;

void GfQuestManager::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfQuestManager(param); }

void GfQuestManager::destroy() {
  GfQuestManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfQuestManager::finalize() {
  destroyEvent();
  if (s_target != nullptr) {
    delete s_target;
    s_target = nullptr;
  }

  if (s_event != nullptr) {
    delete s_event;
    s_event = nullptr;
  }

  s_bdat = nullptr;
  isInitialize = false;
}

bool GfQuestManager::isInitialized() {
  if (s_pThis == nullptr) {
    return false;
  }

  return s_pThis->isInitialize;
}

mm::mtl::FixedQueue<QuestData, 15000> *GfQuestManager::getOrderAchievementQuest() { return &get()->orderAchievementQuests; }

mm::mtl::FixedQueue<QuestData, 8000> *GfQuestManager::getOrderQuest() { return &get()->orderQuests; }

void GfQuestManager::update(const fw::UpdateInfo &info) {
  GfQuestManager *manager = get();
  if (manager == nullptr) {
    return;
  }

  manager->updateOrderQuest();
  updateCurrentTaskCondition();
  GfQuestTarget *target = GfQuestTarget::get();
  if (target != nullptr) {
    target->update(info);
  }
}

void GfQuestManager::updateQuestProgress(const QuestData &data) {
  if (GfQuestInfo::getState(data.quest) == QSTATE_ORDER) {
    cancelCondition(GfQuestInfo::getParentQuest(data.quest));
  }
}

void GfQuestManager::applyQuestComplete(const CompQuest &compQuest) { checkQuestComplete(compQuest.quest, compQuest.state); }

void GfQuestManager::requestRefreshQuestTaskState() {
  if (s_pThis != nullptr) {
    s_pThis->isRequestRefreshQuestTaskState = true;
  }
}

QuestID GfQuestManager::getCurrentQuestSelect() { return GfDataQuest::getSelect(); }

QuestID GfQuestManager::getCurrentQuestScenario() { return GfDataQuest::getScenario(); }

void GfQuestManager::setCurrentQuestForScenario() {
  QuestID quest = GfQuestUtil::getLastOrderCategoryQuest(QTYPE_MAIN);
  if (!quest.empty()) {
    setCurrentQuest(quest);
  }
}

void GfQuestManager::eventCheckTask(QuestID quest) { GfQuestTask::updateQuestTask(quest); }

u32 GfQuestManager::getOrderQuestMax() {
  if (s_pThis == nullptr) {
    return 0;
  }

  return s_pThis->orderQuests.size();
}

u32 GfQuestManager::getReduceHpQuestMax() {
  if (s_pThis == nullptr) {
    return 0;
  }

  return s_pThis->reduceHpQuests.size();
}

QuestID GfQuestManager::getLastOrder() { return s_pThis->lastOrder; }

void GfQuestManager::eventCheckTaskAll() {
  if (s_pThis == nullptr) {
    return;
  }

  QuestID quest = GfDataQuest::getSelect();
  if (!quest.empty()) {
    GfQuestTask::updateQuestTask(quest);
  }

  QuestID scenario = GfDataQuest::getScenario();
  quest.id = scenario.id;
  quest.variant = scenario.variant;
  if (!quest.empty()) {
    GfQuestTask::updateQuestTask(quest);
  }

  eventCheckTaskAllParallel();
  s_pThis->setupAchievementTaskCheck();
  GfGameMercenaries::updateMissionAutoStart();
}

QuestID GfQuestManager::getCurrentQuestNormal() { return GfDataQuest::getSelect(); }

void GfQuestManager::eventCheckTaskAllParallel() {
  if (s_pThis != nullptr) {
    s_pThis->setupParallelTaskCheck();
  }

  SCOM_REFRESH_COMPASS::create();
}

void GfQuestManager::gevReloadBdat(RELOAD_BDAT reload, u32) {
  if (reload == RELOAD_BDAT_ALL) {
    s_pThis->refreshOrderQuestList();
    GfQuestTask::refreshTaskCounters();
  }
}

void GfQuestManager::requestOrderAchievementQuestForce() {
  GfQuestManager *manager = get();
  if (manager != nullptr) {
    manager->isRequestOrderAchievementQuestForce = true;
  }
}

void GfQuestManager::requestOrderQuestForce() {
  GfQuestManager *manager = get();
  if (manager != nullptr) {
    manager->isRequestOrderQuestForce = true;
    manager->setupParallelTaskCheck();
  }
}

void GfQuestManager::gevBattleEnd() { SCOM_BATTLE_TASK_RESET::create(); }

void GfQuestManager::gevPlayEvent(GEV event, u32 eventId) {
  if (event == GEV_EVENT_END) {
    GfQuestTask::completeEventTask(eventId);
  }
}

void GfQuestManager::gevItemAdd(u32 item, int count) {
  u32 itemCount = count < 0 ? -count : count;
  for (u32 index = 0; index < itemCount; index++) {
    GfQuestTask::applyGetItem(item, count >= 0);
  }

  eventCheckTaskAll();
}

void GfQuestManager::gevChangeWeather(u32, u32) { eventCheckTaskAll(); }

void GfQuestManager::gevChangeTimeRange(u32) { eventCheckTaskAll(); }

void GfQuestManager::gevMercenariesMissionFlag(u32, u32, u32) { eventCheckTaskAll(); }

void GfQuestManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  if (event == GEV_MAPJUMP_FADEIN && s_pThis != nullptr) {
    refreshQuestTaskState();
  }

  GfQuestTarget *target = GfQuestTarget::get();
  if (target != nullptr) {
    target->gevMapjump(event, info);
  }
}

} // namespace gf
