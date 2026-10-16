#pragma once
#include "gf/data/gf_data_map.h"
#include "gf/event/gf_event.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

enum CLOUD_SEA_PRIO {};
enum CLOUD_SEA_HANDLE {};

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
  static CLOUD_SEA_HANDLE createCloudSea(CLOUD_SEA cloudSea, CLOUD_SEA_PRIO prio);
  static void destroyCloudSea(CLOUD_SEA_HANDLE handle);
  static void setCloudSea(CLOUD_SEA_HANDLE handle, CLOUD_SEA cloudSea);
  static CLOUD_SEA getCloudType(CLOUD_SEA_HANDLE handle);
  static CLOUD_SEA getCurrentCloudSea();
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void gevPlayEvent(GEV event, u32 eventId);
  static void gevGameState(GF_STATE state, GF_STATE oldState);
  static void update(const fw::UpdateInfo &info);
  static bool isRoom();
};

} // namespace gf
