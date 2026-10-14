#pragma once
#include "gf/event/gf_event.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct MapjumpCallbackInfo;
struct QuestCompleteParam;
struct QuestOrderParam;

class GfGameMercenaries {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void cancelMission(u32 mission);
  static void clearTeamMember(u32 team);
  static void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  static void qevOrderQuest(const QuestOrderParam &param);
  static void qevCompleteQuest(const QuestCompleteParam &param);
  static void updateMissionAutoStart();
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
};

} // namespace gf
