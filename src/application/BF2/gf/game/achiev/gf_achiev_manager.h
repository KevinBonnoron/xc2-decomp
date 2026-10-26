#pragma once
#include "gf/data/gf_data_blade.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct AchievQuest;
struct QuestID;
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
};

class GfAchievManager : public mm::mtl::PtrSingleton<GfAchievManager> {
public:
  GfAchievManager(const GfSetupParam &param);
  ~GfAchievManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  void update(const fw::UpdateInfo &info);
  void incleaseAchievCount(QuestID quest, u32 count, u32 add);
  void gevItemAdd(u32 item, int count);
  void gevBladeActivate(u32 blade, ActivateType activateType, ActivateType oldActivateType);
  void gevMercenariesMissionFlag(u32 mission, u32 flag, u32 value);

  u8 _08[0x1808 - 0x08];
  u64 unknown1808; // Inferred role: unknown; original member name unknown.
  u64 unknown1810; // Inferred role: unknown; original member name unknown.
};

static_assert(offsetof(GfAchievManager, unknown1808) == 0x1808, "");
static_assert(sizeof(GfAchievManager) == 0x1818, "");

} // namespace gf
