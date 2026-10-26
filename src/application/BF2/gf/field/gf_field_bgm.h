#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class BgmTrack;

namespace _gffsn {
extern bool s_bStopBGM;
} // namespace _gffsn

class GfFieldBgm : public mm::mtl::PtrSingleton<GfFieldBgm> {
public:
  u32 getRscFieldBgmID() const;
  u32 getRscBossBattleBgmID() const;
  u32 getRscBattleBgmID() const;
  u32 getRscGimmickBgmID() const;
  bool isDisableFieldBgmChange() const;
  bool isBossBgmCopied() const;
  void setGimmickBgmID(u32 id);
  void gevBattleEnd();
  void gevMapjump(GEV gev, const MapjumpCallbackInfo &info);
  void applyMapJumpStart(const MapjumpCallbackInfo &info);
  void applyMapJumpFadein(const MapjumpCallbackInfo &info);
  void applyMapJumpCleanup(const MapjumpCallbackInfo &info);
  void updateGimmickBgm(const fw::UpdateInfo &info);
  void stopBgmForDebug(bool stop);
  static bool isStopBgmForDebug();

  mm::mtl::FixedVector<BgmTrack *, 16> unknown08; // Inferred role: bgm tracks; original member name unknown.
  u32 m_rscBossBattleBgmID;
  u32 unknown94; // Inferred role: boss battle bgm frame counter; original member name unknown.
  u32 m_rscBattleBgmID;
  u32 m_rscGimmickBgmID;
  u32 m_gimmickBgmID;
  s32 unknowna4; // Inferred role: gimmick bgm switch frame counter; original member name unknown.
  bool m_disableFieldBgmChange;
  bool unknowna9; // Inferred role: map jump with field destroy; original member name unknown.
};

static_assert(offsetof(GfFieldBgm, m_rscBossBattleBgmID) == 0x90, "");
static_assert(offsetof(GfFieldBgm, m_rscGimmickBgmID) == 0x9c, "");
static_assert(offsetof(GfFieldBgm, m_gimmickBgmID) == 0xa0, "");
static_assert(offsetof(GfFieldBgm, m_disableFieldBgmChange) == 0xa8, "");

} // namespace gf
