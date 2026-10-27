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

class GfFieldBgm;
struct BGMCOND;

class BgmTrack {
public:
  u32 getBgmCondID() const;

  u8 _00[0x608];
  u32 m_bgmCondID;
  u8 _60c[0x620 - 0x60c];
  GfFieldBgm *unknown620; // Inferred role: owner field bgm; original member name unknown.
};

static_assert(offsetof(BgmTrack, m_bgmCondID) == 0x608, "");
static_assert(offsetof(BgmTrack, unknown620) == 0x620, "");

struct ExecFadeParam {
  struct unknown001 {
    u8 _00[0x20];
    f32 unknown20;  // Inferred role: fade out time; original member name unknown.
    f32 unknown24;  // Inferred role: fade in time; original member name unknown.
    bool unknown28; // Inferred role: flag read by BgmTrack::getPlayVolume; original member name unknown.
    u8 _29[0x30 - 0x29];
  };

  BgmTrack *unknown00;             // Inferred role: bgm track; original member name unknown.
  const fw::UpdateInfo *unknown08; // Inferred role: update info; original member name unknown.
  const unknown001 *unknown10;     // Inferred role: volume fade entry; original member name unknown.
  const BGMCOND *unknown18;        // Inferred role: bgm condition; original member name unknown.
};

static_assert(offsetof(ExecFadeParam::unknown001, unknown20) == 0x20, "");
static_assert(offsetof(ExecFadeParam::unknown001, unknown24) == 0x24, "");
static_assert(sizeof(ExecFadeParam::unknown001) == 0x30, "");
static_assert(sizeof(ExecFadeParam) == 0x20, "");

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
  void setRscBattleBgmID(u32 id);
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
