#include "gf/game/quest/gf_quest_manager.h"

#include "gf/data/gf_data_quest.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_event.h"
#include "gf/game/quest/gf_quest_target.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/algorithm.h"

namespace gf {

namespace {

enum {
  ACHIEVEMENT_TYPE_BLADE = 9,
};

constexpr u32 TASK_CHECK_COUNT = 8;

} // namespace

GfBdatQuest *GfQuestManager::s_bdat;
GfQuestEvent *GfQuestManager::s_event;
GfQuestTarget *GfQuestManager::s_target;
GfQuestManager *GfQuestManager::s_pThis;

GfQuestManager::GfQuestManager(const GfSetupParam &param) : isInitialize(false), lastOrder() {
  s_pThis = this;
  initialize(param);
}

void GfQuestManager::initialize(const GfSetupParam &) {
  s_bdat = GfBdatQuest::get();
  s_event = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfQuestEvent();
  s_target = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfQuestTarget();
  GfQuestUtil::clearOrderParentQuest();
  isRequestRefreshQuestTaskState = false;
  isRequestOrderAchievementQuestForce = false;
  isRequestOrderQuestForce = false;
  isInitialize = true;
}

GfQuestManager::~GfQuestManager() { s_pThis = nullptr; }

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

void GfQuestManager::setupGame() {
  GfQuestManager *manager = s_pThis;
  if (manager == nullptr) {
    return;
  }

  manager->orderQuests.clear();
  manager->orderAchievementQuests.clear();
  manager->prevCompleteQuests.clear();
  manager->achievementTaskChecks.clear();
  manager->parallelTaskChecks.clear();
  manager->reduceHpQuests.clear();
  manager->linkQuests.clear();
  manager->refreshOrderQuestList();
  s_pThis->destroyEvent();
  s_pThis->lastOrder.id = 0;
  s_pThis->lastOrder.variant = 0;
  GfQuestTask::initializeParams();
}

void GfQuestManager::destroyEvent() {
  while (!eventParams.empty()) {
    delete eventParams.front();
    eventParams.pop_front();
  }
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

void GfQuestManager::updateOrderQuest() {
  updateAchievementTask();
  updateParallelTask();
  if (!eventParams.empty() || !completeQuests.empty() || !removeQuests.empty()) {
    updateSortQuestTask();
    setupAchievementTaskCheck();
    GfGameMercenaries::updateMissionAutoStart();
  }

  mm::mtl::for_each(orderQuests.begin(), orderQuests.end(), updateQuestProgress);

  mm::mtl::for_each(orderAchievementQuests.begin(), orderAchievementQuests.end(), updateQuestProgress);

  mm::mtl::for_each(completeQuests.begin(), completeQuests.end(), applyQuestComplete);
  mm::mtl::for_each(removeQuests.begin(), removeQuests.end(), removeOrder);

  for (mm::mtl::FixedList<QuestParam *, 256>::iterator it = eventParams.begin(), last = eventParams.end(); it != last; ++it) {
    flushEventParam(*it);
  }

  if (!completeQuests.empty() && GfGameScene::get() != nullptr) {
    GfGameScene::get()->refreshGimmickFlag();
  }

  if (isRequestRefreshQuestTaskState) {
    isRequestRefreshQuestTaskState = false;
    refreshQuestTaskState();
  }

  removeQuests.clear();
  completeQuests.clear();
  destroyEvent();
}

void GfQuestManager::updateAchievementTask() {
  for (u32 count = 0; (count < TASK_CHECK_COUNT || isRequestOrderAchievementQuestForce) && !achievementTaskChecks.empty(); count++) {
    QuestData data = achievementTaskChecks.front();
    achievementTaskChecks.pop_front();
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(data.quest);
    if (achievQuest != nullptr && GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
      QSTATE state = GfQuestTask::updateQuestTask(data.quest);
      if (state >= QSTATE_FIN_A) {
        requestQuestComplete(data.quest, state);
      }
    }
  }

  isRequestOrderAchievementQuestForce = false;
}

void GfQuestManager::updateParallelTask() {
  for (u32 count = 0; (count < TASK_CHECK_COUNT || isRequestOrderQuestForce) && !parallelTaskChecks.empty(); count++) {
    QuestData data = parallelTaskChecks.front();
    parallelTaskChecks.pop_front();
    if (GfQuestInfo::getState(data.quest) < QSTATE_FIN_A) {
      QSTATE state = GfQuestTask::updateQuestTask(data.quest);
      if (state >= QSTATE_FIN_A) {
        requestQuestComplete(data.quest, state);
      }
    }
  }

  isRequestOrderQuestForce = false;
}

void GfQuestManager::updateSortQuestTask() {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = orderQuests.begin(), last = orderQuests.end(); it != last; ++it) {
    if (questListAcc->getListQuestCategory((*it).quest) == QTYPE_NORMAL) {
      updateQuestTask(*it);
    }
  }

  for (mm::mtl::FixedQueue<CompQuest, 128>::iterator it = completeQuests.begin(), last = completeQuests.end(); it != last; ++it) {
    applyQuestComplete(*it);
  }
  completeQuests.clear();

  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = orderQuests.begin(), last = orderQuests.end(); it != last; ++it) {
    if (questListAcc->getListQuestCategory((*it).quest) != QTYPE_NORMAL) {
      updateQuestTask(*it);
    }
  }

  for (mm::mtl::FixedQueue<CompQuest, 128>::iterator it = completeQuests.begin(), last = completeQuests.end(); it != last; ++it) {
    applyQuestComplete(*it);
  }
  completeQuests.clear();
}

void GfQuestManager::setupAchievementTaskCheck() {
  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = orderAchievementQuests.begin(), last = orderAchievementQuests.end(); it != last; ++it) {
    if (achievementTaskChecks.find(*it) == achievementTaskChecks.end()) {
      achievementTaskChecks.push(*it);
    }
  }
}

void GfQuestManager::updateQuestProgress(const QuestData &data) {
  if (GfQuestInfo::getState(data.quest) == QSTATE_ORDER) {
    cancelCondition(GfQuestInfo::getParentQuest(data.quest));
  }
}

void GfQuestManager::applyQuestComplete(const CompQuest &compQuest) { checkQuestComplete(compQuest.quest, compQuest.state); }

void GfQuestManager::flushEventParam(const QuestParam *param) {
  switch (param->type) {
  case QUEST_PARAM_TASK:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevChangeTaskState(*static_cast<const QuestTaskParam *>(param));
    });
    break;
  case QUEST_PARAM_COMPLETE:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevCompleteQuest(*static_cast<const QuestCompleteParam *>(param));
    });
    break;
  case QUEST_PARAM_CHANGE:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevChangeCurrentQuest(*static_cast<const QuestChangeParam *>(param));
    });
    break;
  case QUEST_PARAM_ORDER:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevOrderQuest(*static_cast<const QuestOrderParam *>(param));
    });
    break;
  case QUEST_PARAM_COMPLETE_CHILD:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevCompleteChildQuest(*static_cast<const QuestCompleteChildParam *>(param));
    });
    break;
  case QUEST_PARAM_PRE_COMPLETE:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevPreCompleteQuest(*static_cast<const QuestPreCompleteParam *>(param));
    });
    break;
  case QUEST_PARAM_STATE:
    mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [param](IQuestEvent *event) {
      event->qevChangeQuestState(*static_cast<const QuestStateParam *>(param));
    });
    break;
  }
}

void GfQuestManager::refreshQuestTaskState() {
  QuestID quest = getProgressCurrentQuest(QTYPE_NONE);
  if (quest.empty()) {
    return;
  }

  u32 id = quest.id;
  mm::mtl::for_each(s_pThis->events.begin(), s_pThis->events.end(), [id](IQuestEvent *event) { event->qevLoadTaskState(id); });
}

void GfQuestManager::requestQuestComplete(QuestID quest, QSTATE state) {
  GfQuestManager *manager = s_pThis;
  CompQuest compQuest = {quest, state};
  if (manager->completeQuests.find(compQuest) == manager->completeQuests.end()) {
    manager->completeQuests.push(compQuest);
  }
}

void GfQuestManager::requestRefreshQuestTaskState() {
  if (s_pThis != nullptr) {
    s_pThis->isRequestRefreshQuestTaskState = true;
  }
}

void GfQuestManager::checkQuestComplete(QuestID quest, QSTATE state) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent = GfQuestInfo::getParentQuest(quest);
  GfQuestInfo::setState(quest, state);
  GfQuestUtil::questCompleteItem(quest);
  s_pThis->removeQuests.push(QuestData(quest));
  eventCompleteChildQuest(quest);
  QuestID next = s_pThis->orderChildQuest(quest, state);
  u32 event = GfQuestInfo::getPlayEvent(quest, state);
  if (event != 0) {
    GfPlayFactory::createOneEvent(event);
  }

  if (!next.empty() && next.id < QUEST_ID_END) {
    return;
  }

  u32 visible = questListAcc->getListVisible(parent);
  QuestID parentQuest = GfQuestInfo::getParentQuest(quest);
  if (visible == 1) {
    GfPlayFactory::createQuestUIComplete(parentQuest, quest, state);
  } else {
    setCompleteQuest(parentQuest, quest, state);
  }

  if (GfQuestInfo::isScenarioQuest(parent)) {
    QuestID current = getCurrentQuest(QTYPE_NONE);
    if (current == parent) {
      s_pThis->setCurrentQuestScenario(toQuestID(0));
    }
  }
}

void GfQuestManager::eventCompleteChildQuest(QuestID quest) {
  if (!quest.empty()) {
    s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestCompleteChildParam(quest));
  }
}

QuestID GfQuestManager::orderChildQuest(QuestID quest, u32 state) {
  QuestID next = state == QSTATE_FIN_B ? GfDataQuest::getListNextQuestB(quest) : GfDataQuest::getListNextQuestA(quest);
  if (!next.empty() && next.id < QUEST_ID_END) {
    acceptOrder(next);
  }

  return next;
}

void GfQuestManager::setCompleteQuest(QuestID quest, QuestID child, QSTATE state) {
  if (!child.empty()) {
    setCompleteState(quest, child, state);
  }

  GfQuestUtil::questCompleteItem(quest);
  removeOrder(quest);
  if (!GfGameMercenaries::isQuestMission(quest)) {
    execReward(child);
  }
}

// Inlined into every caller: the game keeps an out-of-line copy this code does not match yet.
inline QuestID GfQuestManager::getCurrentQuest(QTYPE type) {
  QuestID quest;
  if (type == QTYPE_NONE) {
    QuestID select = GfDataQuest::getSelect();
    quest = select.empty() ? GfDataQuest::getScenario() : select;
  } else if (type == QTYPE_MAIN) {
    quest = GfDataQuest::getScenario();
  } else {
    quest = GfDataQuest::getSelect();
    if (GfDataQuest::getListQuestCategory(quest) != type) {
      quest.id = 0;
      quest.variant = 0;
    }
  }

  return quest;
}

void GfQuestManager::setCurrentQuestScenario(QuestID quest) {
  QuestID oldQuest = getCurrentQuest(QTYPE_NONE);
  GfDataQuest::setScenario(quest);
  GfDataQuest::setSelect(toQuestID(0));
  if (!quest.empty()) {
    GfQuestUtil::addOrderParentQuest(quest);
  }

  eventChangeCurrentQuest(oldQuest, quest);
}

void GfQuestManager::execReward(QuestID quest) {
  GfQuestReward reward;
  if (!getRewardItem(reward, quest, false)) {
    return;
  }

  if (quest.variant != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(quest);
    if (achievQuest != nullptr) {
      reward.blade = achievQuest->blade;
    }
  }

  GfQuestUtil::execReward(reward);
}

// Inlined into every caller: the game keeps an out-of-line copy this code does not match yet.
inline QuestID GfQuestManager::getProgressCurrentQuest(QTYPE type) {
  QuestID progress = GfQuestInfo::getProgressQuest(getCurrentQuest(type));
  return progress.empty() ? toQuestID(0) : progress;
}

void GfQuestManager::updateQuestTask(const QuestData &data) {
  if (GfQuestInfo::getState(data.quest) >= QSTATE_FIN_A) {
    return;
  }

  QSTATE state = GfQuestTask::updateQuestTask(data.quest);
  if (state >= QSTATE_FIN_A) {
    requestQuestComplete(data.quest, state);
  }
}

QuestID GfQuestManager::getCurrentQuestSelect() { return GfDataQuest::getSelect(); }

void GfQuestManager::setCurrentQuestSelect(QuestID quest) {
  QuestListAcc *questListAcc = s_bdat->mQuestListAcc;
  QuestID oldQuest = getCurrentQuest(QTYPE_NONE);
  GfDataQuest::setSelect(quest);
  if (quest.empty()) {
    QuestID last = GfQuestUtil::getLastOrderParentQuest();
    if (!last.empty() && GfDataQuest::getListQuestCategory(last) != QTYPE_MAIN && !(last == oldQuest)) {
      quest.id = last.id;
      quest.variant = last.variant;
      GfDataQuest::setSelect(quest);
    }
  } else if (questListAcc->getListVisible(quest)) {
    GfQuestUtil::addOrderParentQuest(quest);
  }

  eventChangeCurrentQuest(oldQuest, quest);
}

void GfQuestManager::resetBattleTaskForPlayerDead() {
  GfQuestManager *manager = get();
  if (manager == nullptr) {
    return;
  }

  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = manager->orderQuests.begin(), last = manager->orderQuests.end(); it != last; ++it) {
    GfQuestTask::resetBattleTaskForPlayerDead((*it).quest);
  }

  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = manager->orderAchievementQuests.begin(), last = manager->orderAchievementQuests.end();
       it != last;
       ++it) {
    GfQuestTask::resetBattleTaskForPlayerDead((*it).quest);
  }
}

void GfQuestManager::acceptOrder(QuestID quest) {
  if (GfQuestInfo::getState(quest) >= QSTATE_FIN_A) {
    GfQuestInfo::setState(quest, QSTATE_NOT_ORDER);
  }

  if (!GfQuestInfo::isParent(quest)) {
    s_pThis->addEntryQuest(quest);
    GfQuestInfo::setState(quest, QSTATE_ORDER);
    GfQuestTask::setupOrderTask(quest);
    return;
  }

  mm::mtl::FixedQueue<QuestData, 8000> *quests = nullptr;
  switch (GfDataQuest::getListQuestCategory(quest)) {
  case QTYPE_NORMAL:
    quests = &normalQuests;
    break;
  case QTYPE_BLADE:
    quests = &bladeQuests;
    break;
  case QTYPE_UNUSED:
  case QTYPE_MERCENARIES:
    quests = &mercenariesQuests;
    break;
  }

  if (quests != nullptr) {
    mm::mtl::FixedQueue<QuestData, 8000>::iterator it = quests->find(QuestData(quest));
    if (it != quests->end()) {
      quests->erase(it);
    }
  }

  GfDataQuest::setOrderTimming(quest);
  GfQuestInfo::setState(quest, QSTATE_ORDER);
  if (GfDataQuest::getListQuestCategory(quest) == QTYPE_MAIN) {
    setCurrentQuestScenario(quest);
  }
}

QuestID GfQuestManager::getCurrentQuestScenario() { return GfDataQuest::getScenario(); }

void GfQuestManager::setCurrentQuestForScenario() {
  QuestID quest = GfQuestUtil::getLastOrderCategoryQuest(QTYPE_MAIN);
  if (!quest.empty()) {
    setCurrentQuest(quest);
  }
}

void GfQuestManager::eventCheckTask(QuestID quest) { GfQuestTask::updateQuestTask(quest); }

bool GfQuestManager::setOrder(QuestID quest) {
  if (GfQuestInfo::isQuestOrder(quest) || GfQuestInfo::isQuestFin(quest) || GfDataQuest::getListNextQuestA(quest).empty()) {
    return false;
  }

  orderQuest(quest);
  return true;
}

void GfQuestManager::orderQuest(QuestID quest) {
  if (s_pThis == nullptr) {
    return;
  }

  s_pThis->acceptOrder(quest);
  QuestID next = GfDataQuest::getListNextQuestA(quest);
  if (!next.empty()) {
    s_pThis->acceptOrder(next);
  }

  eventOrderQuest(quest);
}

void GfQuestManager::eventOrderQuest(QuestID quest) {
  if (!quest.empty()) {
    s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestOrderParam(quest));
  }
}

bool GfQuestManager::compEntryQuest::operator()(const QuestData &data) const {
  int category = GfDataQuest::getListQuestCategory(quest);
  int otherCategory = GfDataQuest::getListQuestCategory(data.quest);
  if (category < otherCategory) {
    return true;
  }

  if (category == QTYPE_ACHIEVEMENT) {
    if (quest.variant == 0) {
      if (data.quest.variant != 0) {
        return false;
      }
    } else if (data.quest.variant == 0) {
      return true;
    }

    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(quest);
    AchievQuest *otherAchievQuest = GfDataQuest::getAchievQuest(data.quest);
    if (achievQuest != nullptr && otherAchievQuest != nullptr) {
      if (otherAchievQuest->achievementType != ACHIEVEMENT_TYPE_BLADE && achievQuest->achievementType == ACHIEVEMENT_TYPE_BLADE) {
        return true;
      }

      return achievQuest->sortIndex < otherAchievQuest->sortIndex;
    }
  }

  return quest.id < data.quest.id;
}

void GfQuestManager::entryOrderAchievQuest(QuestID quest) {
  if (!GfQuestInfo::isParent(quest)) {
    s_pThis->addEntryQuest(quest);
  }
}

void GfQuestManager::setupParallelTaskCheck() {
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = orderQuests.begin(), last = orderQuests.end(); it != last; ++it) {
    if (parallelTaskChecks.find(*it) == parallelTaskChecks.end()) {
      parallelTaskChecks.push(*it);
    }
  }
}

u32 GfQuestManager::getOrderQuestMaxWithAchievement() {
  if (s_pThis == nullptr) {
    return 0;
  }

  return s_pThis->orderQuests.size() + s_pThis->orderAchievementQuests.size();
}

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

void GfQuestManager::eventCompleteQuest(QuestID quest, QSTATE state) {
  if (!quest.empty()) {
    s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestCompleteParam(quest, state));
  }
}

void GfQuestManager::eventPreCompleteQuest(QuestID quest) {
  if (!quest.empty()) {
    s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestPreCompleteParam(quest));
  }
}

void GfQuestManager::eventChangeQuestState(QuestID quest, QSTATE oldState, QSTATE state) {
  bool isEmpty = quest.empty();
  if (state != oldState && !isEmpty) {
    s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestStateParam(quest, oldState, state));
  }
}

void GfQuestManager::eventChangeTaskState(const QuestTaskParam &param) {
  s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8)
                                     QuestTaskParam(param.quest, param.taskIndex, param.state));
}

void GfQuestManager::eventChangeCurrentQuest(QuestID oldQuest, QuestID quest) {
  if (!(quest == oldQuest)) {
    s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestChangeParam(oldQuest, quest));
  }
}

void GfQuestManager::eventAchievementCount(QuestID quest) {
  s_pThis->eventParams.push_back(new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) QuestOrderParam(quest));
}

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

void GfQuestManager::setCurrentQuest(QuestID quest) {
  if (!quest.empty()) {
    QuestID parent = GfDataQuest::getListPRTQuestID(quest);
    if (!parent.empty()) {
      quest.id = parent.id;
      quest.variant = parent.variant;
    }

    if (GfQuestInfo::getState(quest) != QSTATE_ORDER) {
      return;
    }
  }

  if (GfDataQuest::getListQuestCategory(quest) == QTYPE_MAIN) {
    s_pThis->setCurrentQuestScenario(quest);
  } else {
    s_pThis->setCurrentQuestSelect(quest);
  }
}

} // namespace gf
