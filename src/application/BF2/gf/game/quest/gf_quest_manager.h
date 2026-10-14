#pragma once
#include "gf/data/gf_bdat_quest.h"
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct QuestChangeParam;
struct QuestCompleteParam;
struct QuestOrderParam;
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

class GfQuestManager {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void setupGame();
  static void addEvent(IQuestEvent *event);
  static void removeEvent(IQuestEvent *event);
  static void update(const fw::UpdateInfo &info);
  static void checkQuestComplete(QuestID quest, QSTATE state);
  static QuestID getCurrentQuest(QTYPE type);
  static QuestID getProgressCurrentQuest(QTYPE type);
  static QuestID getPrevCompleteQuest();
  static void eventCheckTask(QuestID quest);
  static bool openOrder(QuestID quest, bool isEvent);
  static QuestID getOrderQuestId(u32 purpose);
  static void eventChangeQuestState(QuestID quest, QSTATE oldState, QSTATE state);
  static void eventChangeTaskState(const QuestTaskParam &param);
  static void gevReloadBdat(RELOAD_BDAT reload, u32 value);
  static void addCompleteQuest(QuestID quest);
  static void gevBattleEnd();
  static void gevPlayEvent(GEV event, u32 eventId);
  static void gevItemAdd(u32 item, int count);
  static void gevChangeWeather(u32 weather, u32 oldWeather);
  static void gevChangeTimeRange(u32 timeRange);
  static void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
};

} // namespace gf
