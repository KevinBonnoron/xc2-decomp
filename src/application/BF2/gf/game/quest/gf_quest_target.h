#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
struct QuestID;

class GfQuestTarget : public mm::mtl::PtrSingleton<GfQuestTarget> {
public:
  GfQuestTarget();
  ~GfQuestTarget();
  void update(const fw::UpdateInfo &info);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static int getIconType(GF_OBJ_HANDLE *handle, QuestID quest);
  static int getIconTypeTalk(u32 npcId, QuestID quest, u32 mapId, bool);
  static int getIconTypeCollect(u32 type, u32 id, QuestID quest, u32 mapId, bool);
  static int getIconTypeReachPlace(u32 category, u32 placeId, QuestID quest, u32 mapId, bool);
  static int getIconTypeBattle(u32 type, u32 id, QuestID quest, GF_OBJ_HANDLE *handle, bool);

  u8 _08[0x4440 - 0x08];
};

static_assert(sizeof(GfQuestTarget) == 0x4440, "");

} // namespace gf
