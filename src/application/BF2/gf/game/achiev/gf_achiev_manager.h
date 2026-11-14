#pragma once
#include <stddef.h>

#include "gf/data/gf_data_driver.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct AchievQuest;
struct GF_OBJ_HANDLE;
struct MsgObjectNotifyDamage;

class GfAchievStats {
public:
  static void checkBuyItemFromShop(u32 item, u32 count, u32 shop, u32 money);
  static void checkSellItemFromShop(u32 item, u32 count, u32 shop, u32 money);
  static s32 getAchievementTotalCount(const AchievQuest &achievQuest);
  static void checkFallLength(GF_OBJ_HANDLE *handle, const MsgObjectNotifyDamage &message);
  static u32 checkMove(u32 move, u32 count);
  static void checkItem(u32 item, int count);
  static void checkBladeActivate(u32 blade);
  static void checkTalk(u32 npc, GF_OBJ_HANDLE *handle);
};

class GfAchievManager : public mm::mtl::PtrSingleton<GfAchievManager> {
public:
  struct IncQuest {
    QuestID unknown00; // Inferred role: quest; original member name unknown.
    u32 unknown04;     // Inferred role: count; original member name unknown.
    u32 unknown08;     // Inferred role: added count; original member name unknown.
  };

  GfAchievManager(const GfSetupParam &param);
  ~GfAchievManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  void update(const fw::UpdateInfo &info);
  void flushEventIncAchiev(const IncQuest &incQuest);
  void incAchiev(u32 stats, int count);
  void incAchievWithBlade(u32 stats, int count, const mm::mtl::FixedVector<u16, 422> &blades);
  void incleaseAchievCount(QuestID quest, u32 count, u32 add);
  void gevItemAdd(u32 item, int count);
  void gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType);
  void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);
  bool getBladeByAchievementSet(mm::mtl::FixedVector<u16, 422> &blades, u32 achievementSet) const;

  mm::mtl::FixedQueue<IncQuest, 512> unknown08; // Inferred role: pending achievement count increments; original member name unknown.
};

static_assert(sizeof(GfAchievManager::IncQuest) == 0xc, "");
static_assert(offsetof(GfAchievManager, unknown08) == 0x08, "");
static_assert(sizeof(GfAchievManager) == 0x1818, "");

} // namespace gf
