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

  u8 _10[0x14 - 0x10];
  bool unknown14; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(BattleManager, unknown14) == 0x14, "");

} // namespace btl
