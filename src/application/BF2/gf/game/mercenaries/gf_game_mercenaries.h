#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct QuestCompleteParam;
struct QuestID;
struct QuestOrderParam;

class GfGameMercenaries : public mm::mtl::PtrSingleton<GfGameMercenaries> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static bool getZoneMission(mm::mtl::FixedVector<u16, 500> &missions, u32 zone);
  static void cancelMission(u32 mission);
  static void addPoint(u32 point);
  static void setLevel(u32 level);
  static void clearTeamMember(u32 team);
  static void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  static void qevOrderQuest(const QuestOrderParam &param);
  static void qevCompleteQuest(const QuestCompleteParam &param);
  static void updateMissionAutoStart();
  static bool isQuestMission(QuestID quest);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void setMissionFlag(u32 mission, u32 missionFlag);
  static u32 getMissionFlag(u32 mission);
  static void setupNewGameParam();
  static void setMissionCompleteForce(u32 mission);
  static void setMissionTimeForDebug(u32 mission, u32 time);
  static bool isAddTeamMember(u32 team);
  static bool isCompleteMission();
  static bool orderMission(u32 mission);
  static bool addTeamMember(u32 team, u32 blade);
  static bool isRemoveTeamMember(u32 team, u32 blade);
  static void stopMissionTime(bool isStop);

  u8 _08[0x788 - 0x08];
  bool unknown788; // Inferred role: mission time stopped; original member name unknown.
};

static_assert(offsetof(GfGameMercenaries, unknown788) == 0x788, "");

} // namespace gf
