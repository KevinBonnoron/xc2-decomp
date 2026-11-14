#pragma once
#include <stddef.h>

#include "gf/data/gf_data_param_acc.h"
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;

// Target matched against the quest tasks by the GfQuestTarget::getIconType* functions; layout from TargetInfo::setupForFieldObj,
// setupForGimmick and setupForCollect.
struct TargetInfo {
  // Inferred role: kind of a collect target, compared with the collect task data; original enumerator names unknown.
  enum COLLECT_CATEGORY {
    COLLECT_CATEGORY_UNKNOWN_0 = 0,
    COLLECT_CATEGORY_UNKNOWN_1 = 1, // Inferred role: treasure; original enumerator name unknown.
    COLLECT_CATEGORY_UNKNOWN_3 = 3, // Inferred role: enemy; original enumerator name unknown.
    COLLECT_CATEGORY_UNKNOWN_4 = 4, // Inferred role: item; original enumerator name unknown.
  };

  TargetInfo()
      : unknown00(unknown020), unknown08(0), unknown0c(), unknown10(0), unknown14(false), unknown18(0), unknown1c(COLLECT_CATEGORY_UNKNOWN_0), unknown20(0), unknown24(0),
        unknown28(gmk::GMK_TYPE_UNKNOWN_59) {}

  // Inferred helper: sets a reach place target; original name unknown.
  void unknown008(u32 category, u32 placeId, QuestID quest, u32 mapId, bool isCheckCurrent) {
    unknown18 = 2;
    unknown08 = placeId;
    unknown0c = quest;
    unknown10 = mapId;
    unknown20 = category;
    unknown14 = isCheckCurrent;
  }

  // Inferred helper: sets a battle target; original name unknown.
  void unknown010(u32 type, u32 id, QuestID quest, GF_OBJ_HANDLE *handle, bool isCheckCurrent) {
    unknown18 = 3;
    unknown24 = type;
    unknown08 = id;
    unknown0c = quest;
    unknown00 = handle;
    unknown14 = isCheckCurrent;
  }

  // Inferred helper: sets a talk target; original name unknown.
  void unknown011(GF_OBJ_HANDLE *handle, u32 npcId, QuestID quest, u32 mapId, bool isCheckCurrent) {
    unknown18 = 4;
    unknown08 = npcId;
    unknown0c = quest;
    unknown10 = mapId;
    unknown00 = handle;
    unknown14 = isCheckCurrent;
  }

  void setupForFieldObj(QuestID quest, GF_OBJ_HANDLE *handle, bool isCheckCurrent);
  void setupForGimmick(QuestID quest, u32 mapId, GF_OBJ_HANDLE *handle, bool isCheckCurrent);
  void setupForCollect(QuestID quest, COLLECT_CATEGORY category, u32 id, u32 mapId, bool isCheckCurrent);

  GF_OBJ_HANDLE *unknown00;   // Inferred role: object; original member name unknown.
  u32 unknown08;              // Inferred role: id; original member name unknown.
  QuestID unknown0c;          // Inferred role: quest; original member name unknown.
  u32 unknown10;              // Inferred role: map id; original member name unknown.
  bool unknown14;             // Inferred role: compare with the current quests; original member name unknown.
  u32 unknown18;              // Inferred role: target type (1 collect, 2 reach, 3 battle, 4 talk, 5 gimmick); original member name unknown.
  COLLECT_CATEGORY unknown1c; // Inferred role: collect category; original member name unknown.
  u32 unknown20;              // Inferred role: reach category; original member name unknown.
  u32 unknown24;              // Inferred role: battle type; original member name unknown.
  gmk::GmkType unknown28;     // Inferred role: gimmick type; original member name unknown.
};

static_assert(offsetof(TargetInfo, unknown08) == 0x08, "");
static_assert(offsetof(TargetInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(TargetInfo, unknown10) == 0x10, "");
static_assert(offsetof(TargetInfo, unknown14) == 0x14, "");
static_assert(offsetof(TargetInfo, unknown18) == 0x18, "");
static_assert(offsetof(TargetInfo, unknown1c) == 0x1c, "");
static_assert(offsetof(TargetInfo, unknown20) == 0x20, "");
static_assert(offsetof(TargetInfo, unknown24) == 0x24, "");
static_assert(offsetof(TargetInfo, unknown28) == 0x28, "");
static_assert(sizeof(TargetInfo) == 0x30, "");

// The IQuestEvent base sits at 0x08: the game's non-virtual thunks adjust this by -8.
class GfQuestTarget : public mm::mtl::PtrSingleton<GfQuestTarget>, public IQuestEvent {
public:
  // Layout from GfQuestTarget::entryTargetCache, getTargetCache and update; the FixedList instantiation
  // mm::mtl::FixedList<gf::GfQuestTarget::TargetCache, 512>::erase names the type.
  struct TargetCache {
    TargetCache(GF_OBJ_HANDLE *handle, QuestID quest) : unknown10(quest.unknown00, quest.unknown02), unknown14(0), unknown16(false), unknown17(0) {
      ParamObj object = {handle, 0, 0};
      unknown00 = object;
    }

    bool operator==(const ParamObj &object) const {
      if (unknown00.unknown00 != unknown020) {
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
  static int getIconTypeReachPlace(u32 category, u32 placeId, QuestID quest, u32 mapId, bool isCheckCurrent);
  static int getIconTypeCollect(u32 type, u32 id, QuestID quest, u32 mapId, bool isCheckCurrent);
  static int getIconTypeBattle(u32 type, u32 id, QuestID quest, GF_OBJ_HANDLE *handle, bool isCheckCurrent);
  static int getIconTypeTalk(u32 npcId, QuestID quest, u32 mapId, bool isCheckCurrent);
  static int getIconTypeTalk(GF_OBJ_HANDLE *handle, QuestID quest, u32 mapId, bool isCheckCurrent);
  static int getIconTypeGimmick(GF_OBJ_HANDLE *handle, QuestID quest, u32 mapId, bool isCheckCurrent);
  static int getIconTypeFieldObj(GF_OBJ_HANDLE *handle, QuestID quest, u32 mapId, bool isCheckCurrent);

  mm::mtl::FixedList<TargetCache, 512> unknown10; // Inferred role: target caches; original member name unknown.
};

static_assert(sizeof(GfQuestTarget::TargetCache) == 0x18, "");
static_assert(offsetof(GfQuestTarget::TargetCache, unknown10) == 0x10, "");
static_assert(offsetof(GfQuestTarget::TargetCache, unknown14) == 0x14, "");
static_assert(offsetof(GfQuestTarget::TargetCache, unknown16) == 0x16, "");
static_assert(offsetof(GfQuestTarget, unknown10) == 0x10, "");
static_assert(sizeof(GfQuestTarget) == 0x4440, "");

} // namespace gf
