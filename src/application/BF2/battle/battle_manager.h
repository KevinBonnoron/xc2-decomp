#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GfSetupParam;
}

namespace btl {

class BattleManager : public mm::mtl::PtrSingleton<BattleManager>, public gf::IGfEvent {
public:
  ~BattleManager();
  void Initialize(const gf::GfSetupParam &param);
  static void build(const gf::GfSetupParam &param);
  static void destroy();
  void Finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &updateInfo);
  void postUpdate(const fw::UpdateInfo &updateInfo);
  void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo &info) override;
  void gevBattleStart() override;
  void gevBattleEnd() override;
  static void NotifyQuestTask(u32 task);
  void QuestTaskProc(u32 task);
  void CheckTargetMode();
  void Update(const fw::UpdateInfo &updateInfo);
  bool CheckGameOver(const fw::UpdateInfo &updateInfo);
  static void CheckBattle();
  void CheckInBattle();

  f32 unknown10;  // Inferred role: battle frame count; original member name unknown.
  bool unknown14; // Inferred role: initialized; original member name unknown.
  bool unknown15; // Inferred role: map jump end; original member name unknown.
  bool unknown16; // Inferred role: game over; original member name unknown.
  bool unknown17; // Inferred role: enemy win voice played; original member name unknown.
};

static_assert(offsetof(BattleManager, unknown10) == 0x10, "");
static_assert(offsetof(BattleManager, unknown14) == 0x14, "");
static_assert(offsetof(BattleManager, unknown15) == 0x15, "");
static_assert(offsetof(BattleManager, unknown17) == 0x17, "");
static_assert(sizeof(BattleManager) == 0x18, "");

} // namespace btl
