#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_quest.h"
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfQuestEvent;
class GfQuestTarget;
struct GfQuestReward;
struct GfSetupParam;

struct QuestOrderParam : QuestParam {
  QuestOrderParam(QuestID quest) : QuestParam(QUEST_PARAM_ORDER), unknown04(quest) {}

  QuestID unknown04; // Inferred role: quest; original member name unknown.
};

struct QuestCompleteParam : QuestParam {
  QuestCompleteParam(QuestID quest, QSTATE state) : QuestParam(QUEST_PARAM_COMPLETE), unknown04(quest), unknown08(state) {}

  QuestID unknown04; // Inferred role: quest; original member name unknown.
  QSTATE unknown08;  // Inferred role: state; original member name unknown.
};

struct QuestPreCompleteParam : QuestParam {
  QuestPreCompleteParam(QuestID quest) : QuestParam(QUEST_PARAM_PRE_COMPLETE), unknown04(quest) {}

  QuestID unknown04; // Inferred role: quest; original member name unknown.
};

struct QuestStateParam : QuestParam {
  QuestStateParam(QuestID quest, QSTATE oldState, QSTATE state) : QuestParam(QUEST_PARAM_STATE), unknown04(quest), unknown08(oldState), unknown0c(state) {}

  QuestID unknown04; // Inferred role: quest; original member name unknown.
  QSTATE unknown08;  // Inferred role: old state; original member name unknown.
  QSTATE unknown0c;  // Inferred role: state; original member name unknown.
};

struct QuestChangeParam : QuestParam {
  QuestChangeParam(QuestID oldQuest, QuestID quest) : QuestParam(QUEST_PARAM_CHANGE), unknown04(oldQuest), unknown08(quest) {}

  QuestID unknown04; // Inferred role: old quest; original member name unknown.
  QuestID unknown08; // Inferred role: quest; original member name unknown.
};

struct QuestCompleteChildParam : QuestParam {
  QuestCompleteChildParam(QuestID quest) : QuestParam(QUEST_PARAM_COMPLETE_CHILD), unknown04(quest) {}

  QuestID unknown04; // Inferred role: quest; original member name unknown.
};

static_assert(sizeof(QuestOrderParam) == 0x08, "");
static_assert(sizeof(QuestCompleteParam) == 0x0c, "");
static_assert(sizeof(QuestPreCompleteParam) == 0x08, "");
static_assert(sizeof(QuestStateParam) == 0x10, "");
static_assert(sizeof(QuestChangeParam) == 0x0c, "");

static_assert(offsetof(QuestCompleteChildParam, unknown04) == 0x04, "");

class IQuestEvent {
public:
  virtual ~IQuestEvent() {}
  virtual void qevAchievementCount(const QuestOrderParam &) {}
  virtual void qevOrderQuest(const QuestOrderParam &) {}
  virtual void qevCompleteQuest(const QuestCompleteParam &);
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
    CompQuest &operator=(const CompQuest &other) {
      unknown00.unknown00 = other.unknown00.unknown00;
      unknown00.unknown02 = other.unknown00.unknown02;
      unknown04 = other.unknown04;
      return *this;
    }

    bool operator==(const CompQuest &other) const { return unknown00 == other.unknown00 && unknown04 == other.unknown04; }

    QuestID unknown00; // Inferred role: quest; original member name unknown.
    QSTATE unknown04;  // Inferred role: state; original member name unknown.
  };

  struct compEntryQuest {
    compEntryQuest(QuestID quest) : quest(quest) {}

    bool operator()(const QuestData &data) const;

    QuestID quest;
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
  QuestID orderChildQuest(QuestID quest, u32 state);
  static void setCompleteQuest(QuestID quest, QuestID child, QSTATE state);
  static QuestID getCurrentQuest(QTYPE type);
  void setCurrentQuestScenario(QuestID quest);
  static void setCompleteState(QuestID quest, QuestID child, QSTATE state);
  static void execReward(QuestID quest);
  static bool getRewardItem(GfQuestReward &reward, QuestID quest, bool isRandom);
  static void getLinkQuest(mm::mtl::FixedVector<QuestID, 16> &quests, QuestID quest);
  static QuestID getProgressCurrentQuest(QTYPE type);
  static QuestID getPrevCompleteQuest();
  static void updateQuestTask(const QuestData &data);
  static QuestID getCurrentQuestSelect();
  void setCurrentQuestSelect(QuestID quest);
  static void resetBattleTaskForPlayerDead();
  void acceptOrder(QuestID quest);
  void addEntryQuest(QuestID quest);
  static QuestID getCurrentQuestScenario();
  static void setCurrentQuestForScenario();
  static void eventCheckTask(QuestID quest);
  static bool openOrder(QuestID quest, bool isEvent);
  bool setOrder(QuestID quest);
  void orderQuest(QuestID quest);
  static void eventOrderQuest(QuestID quest);
  void reqistLinkQuest(QuestID quest);
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

  mm::mtl::FixedQueue<IQuestEvent *, 16> unknown08;                         // Inferred role: events; original member name unknown.
  bool unknown98;                                                           // Inferred role: initialize; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 8000> unknowna0;                           // Inferred role: order quests; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 15000> unknown7db0;                        // Inferred role: order achievement quests; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 8000> unknown16820;                        // Inferred role: blade quests; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 8000> unknown1e530;                        // Inferred role: normal quests; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 8000> unknown26240;                        // Inferred role: mercenaries quests; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 128> unknown2df50;                         // Inferred role: prev complete quests; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 128> unknown2e160;                         // Inferred role: remove quests; original member name unknown.
  mm::mtl::FixedQueue<CompQuest, 128> unknown2e370;                         // Inferred role: complete quests; original member name unknown.
  QuestID unknown2e780;                                                     // Inferred role: last order; original member name unknown.
  mm::mtl::FixedList<QuestParam *, 256> unknown2e788;                       // Inferred role: event params; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 15000> unknown2f9a8;                       // Inferred role: achievement task checks; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 1024> unknown3e418;                        // Inferred role: parallel task checks; original member name unknown.
  mm::mtl::FixedQueue<QuestData, 1024> unknown3f428;                        // Inferred role: reduce hp quests; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixedVector<QuestID, 16>, 16> unknown40438; // Inferred role: link quests; original member name unknown.
  bool unknown408c0;                                                        // Inferred role: request refresh quest task state; original member name unknown.
  bool unknown408c1;                                                        // Inferred role: request order achievement quest force; original member name unknown.
  bool unknown408c2;                                                        // Inferred role: request order quest force; original member name unknown.
};

struct GfQuestManagerLayout {
  static_assert(offsetof(GfQuestManager, unknown08) == 0x08, "");
  static_assert(offsetof(GfQuestManager, unknown98) == 0x98, "");
  static_assert(offsetof(GfQuestManager, unknowna0) == 0xa0, "");
  static_assert(offsetof(GfQuestManager, unknown7db0) == 0x7db0, "");
  static_assert(offsetof(GfQuestManager, unknown16820) == 0x16820, "");
  static_assert(offsetof(GfQuestManager, unknown1e530) == 0x1e530, "");
  static_assert(offsetof(GfQuestManager, unknown26240) == 0x26240, "");
  static_assert(offsetof(GfQuestManager, unknown2df50) == 0x2df50, "");
  static_assert(offsetof(GfQuestManager, unknown2e160) == 0x2e160, "");
  static_assert(offsetof(GfQuestManager, unknown2e370) == 0x2e370, "");
  static_assert(offsetof(GfQuestManager, unknown2e780) == 0x2e780, "");
  static_assert(offsetof(GfQuestManager, unknown2e788) == 0x2e788, "");
  static_assert(offsetof(GfQuestManager, unknown2f9a8) == 0x2f9a8, "");
  static_assert(offsetof(GfQuestManager, unknown3e418) == 0x3e418, "");
  static_assert(offsetof(GfQuestManager, unknown3f428) == 0x3f428, "");
  static_assert(offsetof(GfQuestManager, unknown40438) == 0x40438, "");
  static_assert(offsetof(GfQuestManager, unknown408c0) == 0x408c0, "");
  static_assert(sizeof(GfQuestManager) == 0x408c8, "");
};

} // namespace gf
