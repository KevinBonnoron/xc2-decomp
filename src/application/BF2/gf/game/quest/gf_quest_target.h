#pragma once
#include <stddef.h>

#include "gf/data/gf_data_param_acc.h"
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;

// The IQuestEvent base sits at 0x08: the game's non-virtual thunks adjust this by -8.
class GfQuestTarget : public mm::mtl::PtrSingleton<GfQuestTarget>, public IQuestEvent {
public:
  // Layout from GfQuestTarget::entryTargetCache, getTargetCache and update; the FixedList instantiation
  // mm::mtl::FixedList<gf::GfQuestTarget::TargetCache, 512>::erase names the type.
  struct TargetCache {
    TargetCache(GF_OBJ_HANDLE *handle, QuestID quest) : unknown14(0), unknown16(false), unknown17(0) {
      ParamObj object = {handle, 0, 0};
      unknown00 = object;
      unknown10 = quest;
    }

    bool operator==(const ParamObj &object) const {
      if (unknown00.unknown00 != INVALID_HANDLE) {
        return unknown00.unknown00 == object.unknown00;
      }
      return unknown00.unknown08 == object.unknown08 && unknown00.unknown0c == object.unknown0c;
    }

    ParamObj unknown00; // Inferred role: target object; original member name unknown.
    QuestID unknown10;  // Inferred role: quest; original member name unknown.
    u16 unknown14;      // Inferred role: frames since the entry; original member name unknown.
    bool unknown16;     // Inferred role: expired; original member name unknown.
    u8 unknown17;       // Inferred role: frames before an empty quest is refreshed (GfQuestTarget::getIconType); original member name unknown.
  };

  GfQuestTarget();
  ~GfQuestTarget();
  void update(const fw::UpdateInfo &info);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void destroyTargetQuest(QuestID quest);
  virtual void qevChangeTaskState(const QuestTaskParam &param);
  virtual void qevChangeQuestState(const QuestStateParam &param);
  virtual void qevOrderQuest(const QuestOrderParam &param);
  virtual void qevCompleteChildQuest(const QuestCompleteChildParam &param);
  virtual void qevChangeCurrentQuest(const QuestChangeParam &param);
  virtual void qevChangeTaskCondition(const QuestTaskParam &param);
  TargetCache *getTargetCache(GF_OBJ_HANDLE *handle);
  void entryTargetCache(GF_OBJ_HANDLE *handle, QuestID quest);
  static int getIconType(GF_OBJ_HANDLE *handle, QuestID quest);
  static int getIconTypeTalk(u32 npcId, QuestID quest, u32 mapId, bool);
  static int getIconTypeCollect(u32 type, u32 id, QuestID quest, u32 mapId, bool);
  static int getIconTypeReachPlace(u32 category, u32 placeId, QuestID quest, u32 mapId, bool);
  static int getIconTypeBattle(u32 type, u32 id, QuestID quest, GF_OBJ_HANDLE *handle, bool);

  mm::mtl::FixedList<TargetCache, 512> unknown10; // Inferred role: target caches; original member name unknown.
};

static_assert(sizeof(GfQuestTarget::TargetCache) == 0x18, "");
static_assert(offsetof(GfQuestTarget::TargetCache, unknown10) == 0x10, "");
static_assert(offsetof(GfQuestTarget::TargetCache, unknown14) == 0x14, "");
static_assert(offsetof(GfQuestTarget::TargetCache, unknown16) == 0x16, "");
static_assert(offsetof(GfQuestTarget, unknown10) == 0x10, "");
static_assert(sizeof(GfQuestTarget) == 0x4440, "");

} // namespace gf
