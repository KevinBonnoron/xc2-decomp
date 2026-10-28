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
  GfGameMercenaries(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameMercenaries();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  void updateMercenariesTeam(const fw::UpdateInfo &info);
  void rebuildAutoStartList();
  static void findMemberForMission(u16 blade);
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
  static void setMissionComplete(u32 mission);
  void applyCompleteMission(const QuestCompleteParam &param);
  static void execMissionReward(u32 mission);
  static void applyDestroyMission();
  static void execMissionAchievementForBlade(u32 mission);
  void applyMercenariesLevel(const QuestCompleteParam &param);
  static u32 getRewardDevelopZone(u32 mission);
  static u32 getRewardTrust(u32 mission);
  static u16 getRewardIdeaPoint(u32 mission);
  static u16 getRewardIdeaType(u32 mission);
  static bool getTeam(mm::mtl::FixedVector<u16, 3> &teams);
  static void execMissionRewardByTeamID(u32 team);
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

  bool unknown08;                           // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedVector<u16, 422> unknown10; // Inferred role: member blades for mission; original member name unknown.
  u8 _368[0x378 - 0x368];
  u32 unknown378;                            // Inferred role: requested blade of the mission; original member name unknown.
  mm::mtl::FixedVector<u16, 512> unknown380; // Inferred role: auto start missions; original member name unknown.
  bool unknown788;                           // Inferred role: mission time stopped; original member name unknown.
};

static_assert(offsetof(GfGameMercenaries, unknown08) == 0x08, "");
static_assert(offsetof(GfGameMercenaries, unknown10) == 0x10, "");
static_assert(offsetof(GfGameMercenaries, unknown378) == 0x378, "");
static_assert(offsetof(GfGameMercenaries, unknown380) == 0x380, "");
static_assert(offsetof(GfGameMercenaries, unknown788) == 0x788, "");
static_assert(sizeof(GfGameMercenaries) == 0x790, "");

} // namespace gf
