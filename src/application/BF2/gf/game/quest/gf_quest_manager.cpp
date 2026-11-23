#include "gf/game/quest/gf_quest_manager.h"

#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_quest.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_util.h"
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
#include "gf/scom/gf_scom_achiev.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"

namespace gf {

namespace {

enum {
  ACHIEVEMENT_UNKNOWN_9_2 = 9, // Inferred role: achievement type blade; original name unknown.
};

constexpr u32 CHECK_UNKNOWN_8 = 8; // Inferred role: task check count; original name unknown.

} // namespace

GfBdatQuest *GfQuestManager::s_bdat;
GfQuestEvent *GfQuestManager::s_event;
GfQuestTarget *GfQuestManager::s_target;
GfQuestManager *GfQuestManager::s_pThis;

u32 GfQuestReward::Param::getDevelopZone() const { return GfDataMap::getDevelopMapId(m_developZone); }

GfQuestManager::GfQuestManager(const GfSetupParam &param) : unknown98(false), m_lastOrder() {
  s_pThis = this;
  initialize(param);
}

void GfQuestManager::initialize(const GfSetupParam &) {
  s_bdat = GfBdatQuest::get();
  s_event = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfQuestEvent();
  s_target = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfQuestTarget();
  GfQuestUtil::clearOrderParentQuest();
  unknown408c0 = false;
  unknown408c1 = false;
  unknown408c2 = false;
  unknown98 = true;
}

GfQuestManager::~GfQuestManager() { s_pThis = nullptr; }

void GfQuestManager::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfQuestManager(param); }

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
  unknown98 = false;
}

bool GfQuestManager::isInitialized() {
  if (s_pThis == nullptr) {
    return false;
  }

  return s_pThis->unknown98;
}

void GfQuestManager::setupGame() {
  GfQuestManager *manager = s_pThis;
  if (manager == nullptr) {
    return;
  }

  manager->m_orderQuest.clear();
  manager->m_orderAchievementQuest.clear();
  manager->unknown2df50.clear();
  manager->unknown2f9a8.clear();
  manager->unknown3e418.clear();
  manager->unknown3f428.clear();
  manager->unknown40438.clear();
  manager->refreshOrderQuestList();
  s_pThis->destroyEvent();
  s_pThis->m_lastOrder.unknown00 = 0;
  s_pThis->m_lastOrder.unknown02 = 0;
  GfQuestTask::initializeParams();
}

void GfQuestManager::destroyEvent() {
  while (!unknown2e788.empty()) {
    delete unknown2e788.front();
    unknown2e788.pop_front();
  }
}

void GfQuestManager::addEvent(IQuestEvent *event) {
  GfQuestManager *manager = get();
  if (manager != nullptr) {
    MM_VERIFY(manager->unknown08.find(event));
    manager->unknown08.push(event);
  }
}

void GfQuestManager::removeEvent(IQuestEvent *event) {
  GfQuestManager *manager = get();
  if (manager != nullptr) {
    manager->unknown08.erase(manager->unknown08.find(event));
  }
}

mm::mtl::FixedQueue<QuestData, 15000> *GfQuestManager::getOrderAchievementQuest() { return &get()->m_orderAchievementQuest; }

mm::mtl::FixedQueue<QuestData, 8000> *GfQuestManager::getOrderQuest() { return &get()->m_orderQuest; }

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
  if (!unknown2e788.empty() || !unknown2e370.empty() || !unknown2e160.empty()) {
    updateSortQuestTask();
    setupAchievementTaskCheck();
    GfGameMercenaries::updateMissionAutoStart();
  }

  mm::mtl::for_each(m_orderQuest.begin(), m_orderQuest.end(), updateQuestProgress);

  mm::mtl::for_each(m_orderAchievementQuest.begin(), m_orderAchievementQuest.end(), updateQuestProgress);

  mm::mtl::for_each(unknown2e370.begin(), unknown2e370.end(), applyQuestComplete);
  mm::mtl::for_each(unknown2e160.begin(), unknown2e160.end(), removeOrder);

  for (mm::mtl::FixedList<QuestParam *, 256>::iterator it = unknown2e788.begin(), last = unknown2e788.end(); it != last; ++it) {
    flushEventParam(*it);
  }

  if (!unknown2e370.empty() && GfGameScene::get() != nullptr) {
    GfGameScene::get()->refreshGimmickFlag();
  }

  if (unknown408c0) {
    unknown408c0 = false;
    refreshQuestTaskState();
  }

  unknown2e160.clear();
  unknown2e370.clear();
  destroyEvent();
}

void GfQuestManager::updateAchievementTask() {
  for (u32 count = 0; (count < CHECK_UNKNOWN_8 || unknown408c1) && !unknown2f9a8.empty(); count++) {
    QuestData data = unknown2f9a8.front();
    unknown2f9a8.pop_front();
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(data.m_questID);
    if (achievQuest != nullptr && GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
      QSTATE state = GfQuestTask::updateQuestTask(data.m_questID);
      if (state >= QSTATE_UNKNOWN_2) {
        requestQuestComplete(data.m_questID, state);
      }
    }
  }

  unknown408c1 = false;
}

void GfQuestManager::updateParallelTask() {
  for (u32 count = 0; (count < CHECK_UNKNOWN_8 || unknown408c2) && !unknown3e418.empty(); count++) {
    QuestData data = unknown3e418.front();
    unknown3e418.pop_front();
    if (GfQuestInfo::getState(data.m_questID) < QSTATE_UNKNOWN_2) {
      QSTATE state = GfQuestTask::updateQuestTask(data.m_questID);
      if (state >= QSTATE_UNKNOWN_2) {
        requestQuestComplete(data.m_questID, state);
      }
    }
  }

  unknown408c2 = false;
}

void GfQuestManager::updateSortQuestTask() {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = m_orderQuest.begin(), last = m_orderQuest.end(); it != last; ++it) {
    if (questListAcc->getListQuestCategory((*it).m_questID) == QTYPE_UNKNOWN_3) {
      updateQuestTask(*it);
    }
  }

  for (mm::mtl::FixedQueue<CompQuest, 128>::iterator it = unknown2e370.begin(), last = unknown2e370.end(); it != last; ++it) {
    applyQuestComplete(*it);
  }
  unknown2e370.clear();

  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = m_orderQuest.begin(), last = m_orderQuest.end(); it != last; ++it) {
    if (questListAcc->getListQuestCategory((*it).m_questID) != QTYPE_UNKNOWN_3) {
      updateQuestTask(*it);
    }
  }

  for (mm::mtl::FixedQueue<CompQuest, 128>::iterator it = unknown2e370.begin(), last = unknown2e370.end(); it != last; ++it) {
    applyQuestComplete(*it);
  }
  unknown2e370.clear();
}

void GfQuestManager::setupAchievementTaskCheck() {
  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = m_orderAchievementQuest.begin(), last = m_orderAchievementQuest.end(); it != last; ++it) {
    if (unknown2f9a8.find(*it) == unknown2f9a8.end()) {
      unknown2f9a8.push(*it);
    }
  }
}

void GfQuestManager::updateQuestProgress(const QuestData &data) {
  if (GfQuestInfo::getState(data.m_questID) == QSTATE_UNKNOWN_1) {
    cancelCondition(GfQuestInfo::getParentQuest(data.m_questID));
  }
}

void GfQuestManager::applyQuestComplete(const CompQuest &compQuest) { checkQuestComplete(compQuest.m_questID, compQuest.unknown04); }

void GfQuestManager::flushEventParam(const QuestParam *param) {
  switch (param->unknown00) {
  case QUEST_PARAM_UNKNOWN_0:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevChangeTaskState(*static_cast<const QuestTaskParam *>(param)); });
    break;
  case QUEST_PARAM_UNKNOWN_1:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevCompleteQuest(*static_cast<const QuestCompleteParam *>(param)); });
    break;
  case QUEST_PARAM_UNKNOWN_2:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevChangeCurrentQuest(*static_cast<const QuestChangeParam *>(param)); });
    break;
  case QUEST_PARAM_UNKNOWN_3:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevOrderQuest(*static_cast<const QuestOrderParam *>(param)); });
    break;
  case QUEST_PARAM_UNKNOWN_4:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevCompleteChildQuest(*static_cast<const QuestCompleteChildParam *>(param)); });
    break;
  case QUEST_PARAM_UNKNOWN_5:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevPreCompleteQuest(*static_cast<const QuestPreCompleteParam *>(param)); });
    break;
  case QUEST_PARAM_UNKNOWN_6:
    mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [param](IQuestEvent *event) { event->qevChangeQuestState(*static_cast<const QuestStateParam *>(param)); });
    break;
  }
}

void GfQuestManager::refreshQuestTaskState() {
  QuestID quest = getProgressCurrentQuest(QTYPE_UNKNOWN_0);
  if (quest.empty()) {
    return;
  }

  u32 id = quest.unknown00;
  mm::mtl::for_each(s_pThis->unknown08.begin(), s_pThis->unknown08.end(), [id](IQuestEvent *event) { event->qevLoadTaskState(id); });
}

void GfQuestManager::requestQuestComplete(QuestID quest, QSTATE state) {
  GfQuestManager *manager = s_pThis;
  CompQuest compQuest = {quest, state};
  if (manager->unknown2e370.find(compQuest) == manager->unknown2e370.end()) {
    manager->unknown2e370.push(compQuest);
  }
}

void GfQuestManager::resetQuest(QuestID quest) {
  if (s_pThis == nullptr) {
    return;
  }

  GfQuestTask::clearTask(quest);
  GfQuestInfo::setState(quest, QSTATE_UNKNOWN_0);
  if (!GfQuestInfo::isParent(quest)) {
    mm::mtl::FixedQueue<QuestData, 8000>::iterator order = s_pThis->m_orderQuest.find(QuestData(quest));
    if (order != s_pThis->m_orderQuest.end()) {
      s_pThis->m_orderQuest.erase(order);

      mm::mtl::FixedQueue<QuestData, 1024>::iterator parallel = s_pThis->unknown3e418.find(QuestData(quest));
      if (parallel != s_pThis->unknown3e418.end()) {
        s_pThis->unknown3e418.erase(parallel);
      }

      mm::mtl::FixedQueue<QuestData, 1024>::iterator reduceHp = s_pThis->unknown3f428.find(QuestData(quest));
      if (reduceHp != s_pThis->unknown3f428.end()) {
        s_pThis->unknown3f428.erase(reduceHp);
      }
    } else {
      mm::mtl::FixedQueue<QuestData, 15000>::iterator achievement = s_pThis->m_orderAchievementQuest.find(QuestData(quest));
      if (achievement != s_pThis->m_orderAchievementQuest.end()) {
        s_pThis->m_orderAchievementQuest.erase(achievement);
      }

      mm::mtl::FixedQueue<QuestData, 15000>::iterator achievementCheck = s_pThis->unknown2f9a8.find(QuestData(quest));
      if (achievementCheck != s_pThis->unknown2f9a8.end()) {
        s_pThis->unknown2f9a8.erase(achievementCheck);
      }
    }
  } else {
    QuestID select = GfDataQuest::getSelect();
    if (select == quest) {
      s_pThis->setCurrentQuestSelect(toQuestID(0));
    }

    GfQuestUtil::removeOrderParentQuest(quest);
    GfQuestManager *manager = s_pThis;
    mm::mtl::FixedQueue<QuestData, 8000> *quests = nullptr;
    switch (GfDataQuest::getListQuestCategory(quest)) {
    case QTYPE_UNKNOWN_3:
      quests = &manager->unknown1e530;
      break;
    case QTYPE_UNKNOWN_2:
      quests = &manager->unknown16820;
      break;
    case QTYPE_UNKNOWN_4:
    case QTYPE_UNKNOWN_5:
      quests = &manager->unknown26240;
      break;
    }

    if (quests != nullptr) {
      quests->push(QuestData(quest));
    }

    requestRefreshQuestTaskState();
  }

  QuestID child = GfQuestInfo::getChildQuestID(quest);
  if (!child.empty() && child.unknown00 < QUEST_ID_UNKNOWN_30000) {
    resetQuest(child);
  }
}

void GfQuestManager::requestRefreshQuestTaskState() {
  if (s_pThis != nullptr) {
    s_pThis->unknown408c0 = true;
  }
}

void GfQuestManager::checkQuestComplete(QuestID quest, QSTATE state) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent = GfQuestInfo::getParentQuest(quest);
  GfQuestInfo::setState(quest, state);
  GfQuestUtil::questCompleteItem(quest);
  s_pThis->unknown2e160.push(QuestData(quest));
  eventCompleteChildQuest(quest);
  QuestID next = s_pThis->orderChildQuest(quest, state);
  u32 event = GfQuestInfo::getPlayEvent(quest, state);
  if (event != 0) {
    GfPlayFactory::createOneEvent(event);
  }

  if (!next.empty() && next.unknown00 < QUEST_ID_UNKNOWN_30000) {
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
    QuestID current = getCurrentQuest(QTYPE_UNKNOWN_0);
    if (current == parent) {
      s_pThis->setCurrentQuestScenario(toQuestID(0));
    }
  }
}

void GfQuestManager::eventCompleteChildQuest(QuestID quest) {
  if (!quest.empty()) {
    s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestCompleteChildParam(quest));
  }
}

QuestID GfQuestManager::orderChildQuest(QuestID quest, u32 state) {
  QuestID next = state == QSTATE_UNKNOWN_3 ? GfDataQuest::getListNextQuestB(quest) : GfDataQuest::getListNextQuestA(quest);
  if (!next.empty() && next.unknown00 < QUEST_ID_UNKNOWN_30000) {
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

void GfQuestManager::setCompleteState(QuestID quest, QuestID child, QSTATE state) {
  QuestID parent = GfDataQuest::getListPRTQuestID(child);
  if (!parent.empty()) {
    GfQuestInfo::setState(parent, state);
    eventCompleteQuest(parent, state);
  }

  QuestData data(quest);
  s_pThis->unknown2e160.push(data);
  if (GfDataQuest::getListQuestCategory(data.m_questID) != QTYPE_UNKNOWN_1 && data.m_questID.unknown02 == 0) {
    SCOM_ACHIEV_INC::addTotalCount(1, 1);
    SCOM_ACHIEV_INC::create(1, 1, 0);
  }
}

// Inlined into every caller: the game keeps an out-of-line copy this code does not match yet.
inline QuestID GfQuestManager::getCurrentQuest(QTYPE type) {
  QuestID quest;
  if (type == QTYPE_UNKNOWN_0) {
    QuestID select = GfDataQuest::getSelect();
    quest = select.empty() ? GfDataQuest::getScenario() : select;
  } else if (type == QTYPE_UNKNOWN_1) {
    quest = GfDataQuest::getScenario();
  } else {
    quest = GfDataQuest::getSelect();
    if (GfDataQuest::getListQuestCategory(quest) != type) {
      quest.unknown00 = 0;
      quest.unknown02 = 0;
    }
  }

  return quest;
}

void GfQuestManager::setCurrentQuestScenario(QuestID quest) {
  QuestID oldQuest = getCurrentQuest(QTYPE_UNKNOWN_0);
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

  if (quest.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(quest);
    if (achievQuest != nullptr) {
      reward.unknown360 = achievQuest->unknown16;
    }
  }

  GfQuestUtil::execReward(reward);
}

bool GfQuestManager::getRewardItem(GfQuestReward &reward, QuestID quest, bool isRandom) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (quest.empty() && quest.unknown02 == 0) {
    quest = getPrevCompleteQuest();
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent = quest;
  }

  u32 rewardSet;
  if (!GfQuestInfo::isQuestFin(parent)) {
    rewardSet = questListAcc->getListRewardSetA(parent);
    if (rewardSet == 0) {
      rewardSet = questListAcc->getListRewardSetB(parent);
    }
  } else {
    rewardSet = 0;
    if (GfQuestInfo::getState(parent) == QSTATE_UNKNOWN_2) {
      rewardSet = questListAcc->getListRewardSetA(parent);
    }
    if (GfQuestInfo::getState(parent) == QSTATE_UNKNOWN_3) {
      rewardSet = questListAcc->getListRewardSetB(parent);
    }
  }

  return GfQuestUtil::getReward(reward, rewardSet, isRandom);
}

void GfQuestManager::getLinkQuest(mm::mtl::FixedVector<QuestID, 16> &quests, QuestID quest) {
  if (s_pThis == nullptr || quest.empty()) {
    return;
  }

  for (mm::mtl::FixedVector<QuestID, 16> *links = s_pThis->unknown40438.begin(), *last = s_pThis->unknown40438.end(); links != last; ++links) {
    if ((*links)[0] == quest) {
      if (quest == getProgressCurrentQuest(QTYPE_UNKNOWN_0)) {
        quests = *links;
        return;
      }
      break;
    }
  }

  quests.push_back(quest);
}

// Inlined into every caller: the game keeps an out-of-line copy this code does not match yet.
inline QuestID GfQuestManager::getProgressCurrentQuest(QTYPE type) {
  QuestID progress = GfQuestInfo::getProgressQuest(getCurrentQuest(type));
  return progress.empty() ? toQuestID(0) : progress;
}

QuestID GfQuestManager::getPrevCompleteQuest() {
  if (s_pThis->unknown2df50.empty()) {
    return QuestID();
  }

  return s_pThis->unknown2df50.back();
}

void GfQuestManager::updateQuestTask(const QuestData &data) {
  if (GfQuestInfo::getState(data.m_questID) >= QSTATE_UNKNOWN_2) {
    return;
  }

  QSTATE state = GfQuestTask::updateQuestTask(data.m_questID);
  if (state >= QSTATE_UNKNOWN_2) {
    requestQuestComplete(data.m_questID, state);
  }
}

QuestID GfQuestManager::getCurrentQuestSelect() { return GfDataQuest::getSelect(); }

void GfQuestManager::setCurrentQuestSelect(QuestID quest) {
  QuestListAcc *questListAcc = s_bdat->m_questListAcc;
  QuestID oldQuest = getCurrentQuest(QTYPE_UNKNOWN_0);
  GfDataQuest::setSelect(quest);
  if (quest.empty()) {
    QuestID last = GfQuestUtil::getLastOrderParentQuest();
    if (!last.empty() && GfDataQuest::getListQuestCategory(last) != QTYPE_UNKNOWN_1 && !(last == oldQuest)) {
      quest.unknown00 = last.unknown00;
      quest.unknown02 = last.unknown02;
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

  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = manager->m_orderQuest.begin(), last = manager->m_orderQuest.end(); it != last; ++it) {
    GfQuestTask::resetBattleTaskForPlayerDead((*it).m_questID);
  }

  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = manager->m_orderAchievementQuest.begin(), last = manager->m_orderAchievementQuest.end(); it != last; ++it) {
    GfQuestTask::resetBattleTaskForPlayerDead((*it).m_questID);
  }
}

void GfQuestManager::resetBattleTaskForBattleEnd() {
  mm::mtl::FixedVector<u16, 128> enemies;
  u32 count = getOrderQuestMax();
  for (u32 i = 0; i < count; i++) {
    GfQuestTask::resetBattleTaskForBattleEnd(enemies, getOrderQuest(i));
  }

  mm::mtl::for_each(enemies.begin(), enemies.end(), GfGameUtil::clearEnemyRepopCounter);
}

void GfQuestManager::acceptOrder(QuestID quest) {
  if (GfQuestInfo::getState(quest) >= QSTATE_UNKNOWN_2) {
    GfQuestInfo::setState(quest, QSTATE_UNKNOWN_0);
  }

  if (!GfQuestInfo::isParent(quest)) {
    s_pThis->addEntryQuest(quest);
    GfQuestInfo::setState(quest, QSTATE_UNKNOWN_1);
    GfQuestTask::setupOrderTask(quest);
    return;
  }

  mm::mtl::FixedQueue<QuestData, 8000> *quests = nullptr;
  switch (GfDataQuest::getListQuestCategory(quest)) {
  case QTYPE_UNKNOWN_3:
    quests = &unknown1e530;
    break;
  case QTYPE_UNKNOWN_2:
    quests = &unknown16820;
    break;
  case QTYPE_UNKNOWN_4:
  case QTYPE_UNKNOWN_5:
    quests = &unknown26240;
    break;
  }

  if (quests != nullptr) {
    mm::mtl::FixedQueue<QuestData, 8000>::iterator it = quests->find(QuestData(quest));
    if (it != quests->end()) {
      quests->erase(it);
    }
  }

  GfDataQuest::setOrderTimming(quest);
  GfQuestInfo::setState(quest, QSTATE_UNKNOWN_1);
  if (GfDataQuest::getListQuestCategory(quest) == QTYPE_UNKNOWN_1) {
    setCurrentQuestScenario(quest);
  }
}

QuestID GfQuestManager::getCurrentQuestScenario() { return GfDataQuest::getScenario(); }

void GfQuestManager::setCurrentQuestForScenario() {
  QuestID quest = GfQuestUtil::getLastOrderCategoryQuest(QTYPE_UNKNOWN_1);
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
    s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestOrderParam(quest));
  }
}

void GfQuestManager::reqistLinkQuest(QuestID quest) {
  if (quest.unknown02 != 0) {
    return;
  }

  QuestID linked;
  u32 linkedQuest = QuestListAcc::get()->getListLinkedQuestID(quest);
  linked.unknown00 = linkedQuest;
  linked.unknown02 = linkedQuest >> 16;
  if (linked.empty()) {
    return;
  }

  for (mm::mtl::FixedVector<QuestID, 16> *links = unknown40438.begin(), *last = unknown40438.end(); links != last; ++links) {
    if ((*links)[0] == linked) {
      links->push_back(quest);
      return;
    }
  }

  mm::mtl::FixedVector<QuestID, 16> links;
  links.push_back(linked);
  links.push_back(quest);
  unknown40438.push_back(links);
}

bool GfQuestManager::compEntryQuest::operator()(const QuestData &data) const {
  int category = GfDataQuest::getListQuestCategory(quest);
  int otherCategory = GfDataQuest::getListQuestCategory(data.m_questID);
  if (category < otherCategory) {
    return true;
  }

  if (category == QTYPE_UNKNOWN_6) {
    if (quest.unknown02 == 0) {
      if (data.m_questID.unknown02 != 0) {
        return false;
      }
    } else if (data.m_questID.unknown02 == 0) {
      return true;
    }

    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(quest);
    AchievQuest *otherAchievQuest = GfDataQuest::getAchievQuest(data.m_questID);
    if (achievQuest != nullptr && otherAchievQuest != nullptr) {
      if (otherAchievQuest->unknown12 != ACHIEVEMENT_UNKNOWN_9_2 && achievQuest->unknown12 == ACHIEVEMENT_UNKNOWN_9_2) {
        return true;
      }

      return achievQuest->unknown14 < otherAchievQuest->unknown14;
    }
  }

  return quest.unknown00 < data.m_questID.unknown00;
}

void GfQuestManager::entryOrderAchievQuest(QuestID quest) {
  if (!GfQuestInfo::isParent(quest)) {
    s_pThis->addEntryQuest(quest);
  }
}

void GfQuestManager::setupParallelTaskCheck() {
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = m_orderQuest.begin(), last = m_orderQuest.end(); it != last; ++it) {
    if (unknown3e418.find(*it) == unknown3e418.end()) {
      unknown3e418.push(*it);
    }
  }
}

u32 GfQuestManager::getOrderQuestMaxWithAchievement() {
  if (s_pThis == nullptr) {
    return 0;
  }

  return s_pThis->m_orderQuest.size() + s_pThis->m_orderAchievementQuest.size();
}

QuestID GfQuestManager::getOrderQuestWithAchievement(u32 index) {
  u16 id = 0;
  u16 variant = 0;
  if (s_pThis != nullptr) {
    size_t size = s_pThis->m_orderQuest.size();
    size_t rest = index - size;
    QuestID quest;
    if (index < size) {
      quest = s_pThis->m_orderQuest[index];
    } else {
      quest = s_pThis->m_orderAchievementQuest[rest];
    }
    id = quest.unknown00;
    variant = quest.unknown02;
  }

  return QuestID(id, variant);
}

u32 GfQuestManager::getOrderQuestMax() {
  if (s_pThis == nullptr) {
    return 0;
  }

  return s_pThis->m_orderQuest.size();
}

QuestID GfQuestManager::getOrderQuest(u32 index) {
  if (s_pThis == nullptr) {
    return QuestID();
  }

  return s_pThis->m_orderQuest[index];
}

u32 GfQuestManager::getReduceHpQuestMax() {
  if (s_pThis == nullptr) {
    return 0;
  }

  return s_pThis->unknown3f428.size();
}

QuestID GfQuestManager::getReduceHpQuest(u32 index) {
  if (s_pThis == nullptr) {
    return QuestID();
  }

  return s_pThis->unknown3f428[index];
}

QuestID GfQuestManager::getOrderQuestId(u32 purpose) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = s_pThis->m_orderQuest.begin(); it != s_pThis->m_orderQuest.end(); ++it) {
    if (questListAcc->getListPurposeID(*it) == purpose) {
      return *it;
    }
  }

  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = s_pThis->m_orderAchievementQuest.begin(); it != s_pThis->m_orderAchievementQuest.end(); ++it) {
    if (questListAcc->getListPurposeID(*it) == purpose) {
      return *it;
    }
  }

  return QuestID();
}

QuestID GfQuestManager::getLastOrder() { return s_pThis->m_lastOrder; }

void GfQuestManager::eventCompleteQuest(QuestID quest, QSTATE state) {
  if (!quest.empty()) {
    s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestCompleteParam(quest, state));
  }
}

void GfQuestManager::eventPreCompleteQuest(QuestID quest) {
  if (!quest.empty()) {
    s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestPreCompleteParam(quest));
  }
}

void GfQuestManager::eventChangeQuestState(QuestID quest, QSTATE oldState, QSTATE state) {
  bool isEmpty = quest.empty();
  if (state != oldState && !isEmpty) {
    s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestStateParam(quest, oldState, state));
  }
}

void GfQuestManager::eventChangeTaskState(const QuestTaskParam &param) {
  s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestTaskParam(param.m_questID, param.unknown0c, param.unknown18));
}

void GfQuestManager::eventChangeCurrentQuest(QuestID oldQuest, QuestID quest) {
  if (!(quest == oldQuest)) {
    s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestChangeParam(oldQuest, quest));
  }
}

void GfQuestManager::eventAchievementCount(QuestID quest) { s_pThis->unknown2e788.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) QuestOrderParam(quest)); }

void GfQuestManager::eventCheckTaskAll() {
  if (s_pThis == nullptr) {
    return;
  }

  QuestID quest = GfDataQuest::getSelect();
  if (!quest.empty()) {
    GfQuestTask::updateQuestTask(quest);
  }

  QuestID scenario = GfDataQuest::getScenario();
  quest.unknown00 = scenario.unknown00;
  quest.unknown02 = scenario.unknown02;
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

void GfQuestManager::checkTaskByQuestID(u32 quest) {
  eventCheckTask(toQuestID(quest));
  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = s_pThis->m_orderAchievementQuest.begin(); it != s_pThis->m_orderAchievementQuest.end(); ++it) {
    if ((*it).m_questID.unknown00 == quest) {
      eventCheckTask(*it);
    }
  }
}

void GfQuestManager::gevReloadBdat(RELOAD_BDAT reload, u32) {
  if (reload == RELOAD_BDAT_UNKNOWN_1) {
    s_pThis->refreshOrderQuestList();
    GfQuestTask::refreshTaskCounters();
  }
}

void GfQuestManager::addCompleteQuest(QuestID quest) {
  QuestData data(quest);
  if (s_pThis->unknown2df50.full()) {
    s_pThis->unknown2df50.pop_front();
  }
  s_pThis->unknown2df50.push(data);
}

void GfQuestManager::requestOrderAchievementQuestForce() {
  GfQuestManager *manager = get();
  if (manager != nullptr) {
    manager->unknown408c1 = true;
  }
}

void GfQuestManager::requestOrderQuestForce() {
  GfQuestManager *manager = get();
  if (manager != nullptr) {
    manager->unknown408c2 = true;
    manager->setupParallelTaskCheck();
  }
}

void GfQuestManager::gevBattleEnd() { SCOM_BATTLE_TASK_RESET::create(); }

void GfQuestManager::gevPlayEvent(GEV event, u32 eventId) {
  if (event == GEV_UNKNOWN_9) {
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
  if (event == GEV_UNKNOWN_6 && s_pThis != nullptr) {
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
      quest.unknown00 = parent.unknown00;
      quest.unknown02 = parent.unknown02;
    }

    if (GfQuestInfo::getState(quest) != QSTATE_UNKNOWN_1) {
      return;
    }
  }

  if (GfDataQuest::getListQuestCategory(quest) == QTYPE_UNKNOWN_1) {
    s_pThis->setCurrentQuestScenario(quest);
  } else {
    s_pThis->setCurrentQuestSelect(quest);
  }
}

} // namespace gf
