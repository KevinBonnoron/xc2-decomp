#pragma once
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_state.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct MapjumpCallbackInfo;

class GfGameEnv {
public:
  static void clear();
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isStopEnemySearch();
  static bool isMapjumpBlackout();
  static bool isMapjump();
  static bool isMapjumpWithSaveData();
  static u32 getMapJumpID();
  static u32 getMapID();
  static void setMapID(u32 mapJump, u32 map);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void gevPlayEvent(GEV event, u32 eventId);
  static void gevGameState(GF_STATE state, GF_STATE oldState);
  static void update(const fw::UpdateInfo &info);
  static bool isRoom();
};

} // namespace gf
