#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct QuestCompleteParam;
struct QuestID;
struct QuestOrderParam;

class GfGameMercenaries {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static bool getZoneMission(mm::mtl::FixedVector<u16, 500> &missions, u32 zone);
  static void cancelMission(u32 mission);
  static void clearTeamMember(u32 team);
  static void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  static void qevOrderQuest(const QuestOrderParam &param);
  static void qevCompleteQuest(const QuestCompleteParam &param);
  static void updateMissionAutoStart();
  static bool isQuestMission(QuestID quest);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void setMissionFlag(u32 mission, u32 missionFlag);
  static u32 getMissionFlag(u32 mission);
};

} // namespace gf
