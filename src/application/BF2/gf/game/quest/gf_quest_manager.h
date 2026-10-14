#pragma once
#include "gf/data/gf_bdat_quest.h"
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfQuestEvent;
class GfQuestTarget;
struct GfQuestReward;
struct GfSetupParam;
struct QuestChangeParam;
struct QuestCompleteParam;
struct QuestOrderParam;
struct QuestParam;
struct QuestPreCompleteParam;
struct QuestStateParam;
struct QuestTaskParam;

struct QuestCompleteChildParam {
  u8 _00[0x04 - 0x00];
  QuestID quest;
};

static_assert(offsetof(QuestCompleteChildParam, quest) == 0x04, "");

class IQuestEvent {
public:
  virtual ~IQuestEvent() {}
  virtual void qevAchievementCount(const QuestOrderParam &) {}
  virtual void qevOrderQuest(const QuestOrderParam &) {}
  virtual void qevCompleteQuest(const QuestCompleteParam &) {}
  virtual void qevPreCompleteQuest(const QuestPreCompleteParam &) {}
  virtual void qevChangeTaskState(const QuestTaskParam &) {}
  virtual void qevLoadTaskState(u32) {}
  virtual void qevCompleteChildQuest(const QuestCompleteChildParam &) {}
  virtual void qevChangeQuestState(const QuestStateParam &) {}
  virtual void qevChangeCurrentQuest(const QuestChangeParam &) {}
  virtual void qevChangeTaskCondition(const QuestTaskParam &) {}
};

class GfQuestManager : public mm::mtl::PtrSingleton<GfQuestManager> {
public:
  struct CompQuest {
    QuestID quest;
    QSTATE state;
  };

  struct compEntryQuest {
    bool operator()(const QuestData &data) const;
  };

  GfQuestManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfQuestManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void setupGame();
  void refreshOrderQuestList();
  void destroyEvent();
  static void addEvent(IQuestEvent *event);
  static void removeEvent(IQuestEvent *event);
  static mm::mtl::FixedQueue<QuestData, 15000> *getOrderAchievementQuest();
  static mm::mtl::FixedQueue<QuestData, 8000> *getOrderQuest();
  static void update(const fw::UpdateInfo &info);
  void updateOrderQuest();
  static void updateCurrentTaskCondition();
  void updateAchievementTask();
  void updateParallelTask();
  void updateSortQuestTask();
  void setupAchievementTaskCheck();
  static void updateQuestProgress(const QuestData &data);
  static void applyQuestComplete(const CompQuest &compQuest);
  static void removeOrder(QuestID quest);
  static void flushEventParam(const QuestParam *param);
  static void refreshQuestTaskState();
  static void requestQuestComplete(QuestID quest, QSTATE state);
  static void cancelCondition(QuestID quest);
  static void resetQuest(QuestID quest);
  static void requestRefreshQuestTaskState();
  static void checkQuestComplete(QuestID quest, QSTATE state);
  static void eventCompleteChildQuest(QuestID quest);
  static void orderChildQuest(QuestID quest, u32 child);
  static void setCompleteQuest(QuestID quest, QuestID child, QSTATE state);
  static QuestID getCurrentQuest(QTYPE type);
  static void setCurrentQuestScenario(QuestID quest);
  static void setCompleteState(QuestID quest, QuestID child, QSTATE state);
  static void execReward(QuestID quest);
  static bool getRewardItem(GfQuestReward &reward, QuestID quest, bool isRandom);
  static bool getLinkQuest(mm::mtl::FixedVector<QuestID, 16> &quests, QuestID quest);
  static QuestID getProgressCurrentQuest(QTYPE type);
  static QuestID getPrevCompleteQuest();
  static void updateQuestTask(const QuestData &data);
  static QuestID getCurrentQuestSelect();
  static void setCurrentQuestSelect(QuestID quest);
  static void resetBattleTaskForPlayerDead();
  static bool acceptOrder(QuestID quest);
  static void addEntryQuest(QuestID quest);
  static QuestID getCurrentQuestScenario();
  static void setCurrentQuestForScenario();
  static void eventCheckTask(QuestID quest);
  static bool openOrder(QuestID quest, bool isEvent);
  static bool setOrder(QuestID quest);
  static bool orderQuest(QuestID quest);
  static void eventOrderQuest(QuestID quest);
  static void reqistLinkQuest(QuestID quest);
  static void entryOrderAchievQuest(QuestID quest);
  void setupParallelTaskCheck();
  static u32 getOrderQuestMaxWithAchievement();
  static QuestID getOrderQuestWithAchievement(u32 index);
  static u32 getOrderQuestMax();
  static QuestID getOrderQuest(u32 index);
  static u32 getReduceHpQuestMax();
  static QuestID getReduceHpQuest(u32 index);
  static QuestID getOrderQuestId(u32 purpose);
  static QuestID getLastOrder();
  static void eventCompleteQuest(QuestID quest, QSTATE state);
  static void eventPreCompleteQuest(QuestID quest);
  static void eventChangeQuestState(QuestID quest, QSTATE oldState, QSTATE state);
  static void eventChangeTaskState(const QuestTaskParam &param);
  static void eventChangeCurrentQuest(QuestID oldQuest, QuestID quest);
  static void eventAchievementCount(QuestID quest);
  static void eventCheckTaskAll();
  static QuestID getCurrentQuestNormal();
  static void eventCheckTaskAllParallel();
  static void checkTaskByQuestID(u32 quest);
  static void gevReloadBdat(RELOAD_BDAT reload, u32 value);
  static void addCompleteQuest(QuestID quest);
  static void requestOrderAchievementQuestForce();
  static void requestOrderQuestForce();
  static void resetBattleTaskForBattleEnd();
  static void gevBattleEnd();
  static void gevPlayEvent(GEV event, u32 eventId);
  static void gevItemAdd(u32 item, int count);
  static void gevChangeWeather(u32 weather, u32 oldWeather);
  static void gevChangeTimeRange(u32 timeRange);
  static void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void setCurrentQuest(QuestID quest);

  static GfBdatQuest *s_bdat;
  static GfQuestEvent *s_event;
  static GfQuestTarget *s_target;
  static GfQuestManager *s_pThis;

  mm::mtl::FixedQueue<IQuestEvent *, 16> events;
  bool isInitialize;
  mm::mtl::FixedQueue<QuestData, 8000> orderQuests;
  mm::mtl::FixedQueue<QuestData, 15000> orderAchievementQuests;
  u8 _16820[0x2e780 - 0x16820];
  QuestID lastOrder;
  u8 _2e784[0x3f428 - 0x2e784];
  mm::mtl::FixedQueue<QuestData, 1024> reduceHpQuests;
  u8 _40438[0x408c0 - 0x40438];
  bool isRequestRefreshQuestTaskState;
  bool isRequestOrderAchievementQuestForce;
  bool isRequestOrderQuestForce;
};

struct GfQuestManagerLayout {
  static_assert(offsetof(GfQuestManager, events) == 0x08, "");
  static_assert(offsetof(GfQuestManager, isInitialize) == 0x98, "");
  static_assert(offsetof(GfQuestManager, orderQuests) == 0xa0, "");
  static_assert(offsetof(GfQuestManager, orderAchievementQuests) == 0x7db0, "");
  static_assert(offsetof(GfQuestManager, lastOrder) == 0x2e780, "");
  static_assert(offsetof(GfQuestManager, reduceHpQuests) == 0x3f428, "");
  static_assert(offsetof(GfQuestManager, isRequestRefreshQuestTaskState) == 0x408c0, "");
  static_assert(sizeof(GfQuestManager) == 0x408c8, "");
};

} // namespace gf
