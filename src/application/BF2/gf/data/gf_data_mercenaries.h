#pragma once
#include <stddef.h>

#include "gf/field/gf_field_time.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

struct GfRequestBladeData {
  u32 type;
  u32 target;
  u32 level;
  u32 number;
};

static_assert(sizeof(GfRequestBladeData) == 0x10, "");

constexpr u32 MERCENARIES_LEVEL_MAX = 5;

struct SDataMercenariesTeam {
  u16 members[6];
  u8 _0c[0x10 - 0x0c];
  u32 teamID;
  u32 mission;
  f32 missionElapsedTime;
  ElapseTime missionTime;
  ElapseTime missionTimeOriginal;
  bool _24;
};

static_assert(offsetof(SDataMercenariesTeam, teamID) == 0x10, "");
static_assert(offsetof(SDataMercenariesTeam, mission) == 0x14, "");
static_assert(offsetof(SDataMercenariesTeam, missionTime) == 0x1c, "");
static_assert(offsetof(SDataMercenariesTeam, missionTimeOriginal) == 0x20, "");
static_assert(sizeof(SDataMercenariesTeam) == 0x28, "");

struct SDataMercenariesPreset {
  u8 _00[0x0c - 0x00];
};

static_assert(sizeof(SDataMercenariesPreset) == 0x0c, "");

struct SDataMercenaries {
  mm::mtl::FixedVector<SDataMercenariesTeam, 3> teams;
  SDataMercenariesPreset presets[40];
};

static_assert(offsetof(SDataMercenaries, presets) == 0x080, "");
static_assert(sizeof(SDataMercenaries) == 0x260, "");

class GfDataMercenaries {
public:
  static u32 getReserverMax();
  static SDataMercenaries *getSDataMercenaries();
  static u32 getLevel();
  static u32 getLevelMax();
  static void setLevel(u32 level);
  static u32 getPoint();
  static u32 getPointMax();
  static u32 getPointLimit();
  static void setPoint(u32 point);
  static u32 getTeamMax();
  static u32 getTeamNum();
  static bool getReserver(mm::mtl::FixedVector<u16, 422> &reservers);
  static bool isValidTeamID(u32 teamID);
  static SDataMercenariesTeam *getTeamByTeamID(u32 teamID);
  static u32 getTeamPower(u32 teamID);
  static u32 getTeamID(u32 blade);
  static u32 getMissionIdByBlade(u32 blade);
  static SDataMercenariesTeam *getTeamByIndex(u32 index);
  static SDataMercenariesTeam *getTeamByMissionID(u32 mission);
  static u32 getTeamIDByMissionID(u32 mission);
  static SDataMercenariesTeam *getTeamMember(u32 teamID);
  static u8 getTeamAnimalNum(u32 teamID);
  static bool getTeamByZoneMissionWorking(mm::mtl::FixedVector<u16, 3> &teams, u32 zone);
  static u32 getMissionFlag(u32 mission);
  static u32 getMissionMapID(u32 mission);
  static bool getTeamByZoneMissionComplete(mm::mtl::FixedVector<u16, 3> &teams, u32 zone);
  static bool isTeamStateReward(u32 teamID);
  static void setMissionFlag(u32 mission, u32 missionFlag);
  static bool isMissionCompleteFlag(u32 mission);
  static void setMissionCompleteFlag(u32 mission);
  static u32 getRequestPerformance(u32 mission);
  static u32 getTeamMissionTime(u32 teamID, u32 mission);
  static u32 getFieldSkill(u32 mission, u32 index);
  static f32 getMissionPerformanceRatio();
  static u32 getStartMissionID();
  static u32 getEndMissionID();
  static QuestID getMissionQuestID(u32 mission);
  static u32 getMissionPurposeID(u32 mission);
  static u32 getTeamMission(u32 teamID);
  static ElapseTime getTeamMissionTime(u32 teamID);
  static ElapseTime getTeamMissionTimeOriginal(u32 teamID);
  static bool isTeamStateEmpty(u32 teamID);
  static bool isTeamStateExpedition(u32 teamID);
  static u32 getMissionTaskType(u32 mission, u32 index);
  static u32 getMissionTaskType(u32 mission);
  static u32 getMissionCategory(u32 mission);
  static u32 getMissionRewardID(u32 mission);
  static bool isOrderOnlyOne(u32 mission);
  static u32 getMissionZoneID(u32 mission);
  static bool isMissionOrderTeam(u32 mission);
  static bool isMissionComplete(u32 mission);
  static bool isEnableMissionBlade(u32 blade, u32 requestBlade);
  static u16 getTeamLeader(u32 teamID);
  static bool isEnableOrder(u32 mission);
  static bool isNewMission(u32 mission);
  static void clearNewMission(u32 mission);
  static u32 getFieldSkill1(u32 mission);
  static u32 getFieldSkill2(u32 mission);
  static u32 getFieldSkill3(u32 mission);
  static u32 getMissionTime(u32 mission);
  static bool getFieldSkill1Info(u8 *&bdat, u32 &textId, u32 mission);
  static bool getFieldSkill2Info(u8 *&bdat, u32 &textId, u32 mission);
  static bool getFieldSkill3Info(u8 *&bdat, u32 &textId, u32 mission);
  static bool getFieldSkillInfo(u8 *&bdat, u32 &textId, u32 mission, u32 index);
  static u32 getRewardAchievmentRatio();
  static bool getMsgTitleName(u8 *&bdat, u32 &textId, u32 mission);
  static bool getMsgZoneName(u8 *&bdat, u32 &textId, u32 mission);
  static bool getMsgSummaryName(u8 *&bdat, u32 &textId, u32 mission);
  static bool getMsgTaskName(u8 *&bdat, u32 &textId, u32 mission, u32 index);
  static bool getRequestBladeTextForDebug(mm::mtl::FixStr<128> &text, const GfRequestBladeData &requestBladeData);
  static bool isTeamMemberFill(u32 teamID);
  static bool isTeamMemberEmpty(u32 teamID);
  static u8 getTeamMemberNum(u32 teamID);
  static bool getRequestCondition(GfRequestBladeData &requestBladeData, u32 mission, u32 task);
  static void setFullEnableOrderMissionForDebug();
  static u32 getBladeWithLeader(u32 mission);
  static SDataMercenariesPreset *getPreset(u32 index);
};

} // namespace gf
