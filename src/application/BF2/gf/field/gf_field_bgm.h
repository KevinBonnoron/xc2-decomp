#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "gf/sound/gf_sound.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfFieldBgm;

struct BGMCOND {
  BGMCOND();
  void clear();
  void copyPlayInfo(const BGMCOND &src);
  bool isInvalidBgm() const;
  bool isInvalidPlay() const;
  bool isSilentPlay() const;

  f32 unknown00;                 // Inferred role: volume; original member name unknown.
  SoundHandle unknown04;         // Inferred role: playing sound handle; original member name unknown.
  u32 unknown0c;                 // Inferred role: play parameter cleared by clear; original member name unknown.
  u8 unknown10;                  // Inferred role: play flag; original member name unknown.
  u8 unknown11;                  // Inferred role: play flag read by isInvalidPlay; original member name unknown.
  mm::mtl::FixStr<64> unknown14; // Inferred role: bgm name; original member name unknown.
  u32 unknown58;                 // Inferred role: cleared by the constructor; original member name unknown.
};

static_assert(offsetof(BGMCOND, unknown04) == 0x04, "");
static_assert(offsetof(BGMCOND, unknown14) == 0x14, "");
static_assert(offsetof(BGMCOND, unknown58) == 0x58, "");
static_assert(sizeof(BGMCOND) == 0x5c, "");

struct BgmFileInfo {
  u32 unknown00;  // Inferred role: bgm condition id; original member name unknown.
  u32 unknown04;  // Inferred role: bgm id; original member name unknown.
  u32 unknown08;  // Inferred role: bgm condition index; original member name unknown.
  bool unknown0c; // Inferred role: field bgm flag; original member name unknown.
};

static_assert(offsetof(BgmFileInfo, unknown0c) == 0x0c, "");
static_assert(sizeof(BgmFileInfo) == 0x10, "");

struct ExecFadeParam;

class BgmTrack {
public:
  struct unknown001 {
    mm::mtl::Delegate<f32(ExecFadeParam &)> unknown00; // Inferred role: volume fade function; original member name unknown.
    f32 unknown20;                                     // Inferred role: fade out time; original member name unknown.
    f32 unknown24;                                     // Inferred role: fade in time; original member name unknown.
    bool unknown28;                                    // Inferred role: flag read by getPlayVolume; original member name unknown.
  };

  struct unknown002 {
    mm::mtl::Delegate<f32(f32, f32, f32)> unknown00; // Inferred role: volume multiply function; original member name unknown.
    f32 unknown20;                                   // Inferred role: first function argument; original member name unknown.
    f32 unknown24;                                   // Inferred role: second function argument; original member name unknown.
    f32 unknown28;                                   // Inferred role: third function argument; original member name unknown.
  };

  BgmTrack(GfFieldBgm *owner, bool unknown);
  virtual ~BgmTrack() {}
  virtual const char *getTrackName() const = 0;
  virtual bool isPlaying() const;
  virtual void update(const fw::UpdateInfo &info);
  u32 getBgmCondID() const;
  void destroy();
  void destroyFader();
  void setPause(bool pause);
  void setCategoryApply(u8 category);
  f32 getVolume() const;
  void play(u32 bgmCondID);
  void play(const char *name);
  void playWithFadeout(u32 bgmCondID);
  void stopBGM(f32 fadeTime);
  void stopCondBGM(f32 fadeTime, BGMCOND &cond);
  void addVolumeFade(f32 (*function)(ExecFadeParam &), f32 fadeOutTime, f32 fadeInTime, bool flag);
  void addVolumeMulti(f32 (*function)(f32, f32, f32), f32 arg0, f32 arg1, f32 arg2);
  void calcMultiplyVolume(const fw::UpdateInfo &info);
  bool getPlayVolume(f32 &volume, const fw::UpdateInfo &info, const BGMCOND &cond, bool isFadeOut);
  void copyPlayParam(BgmTrack *src, const BgmFileInfo &info);
  bool makeBgmFile(mm::mtl::FixStr<64> &name, u32 &bgmID, u32 bgmCondID, u32 index) const;
  const char *getPlayingBgmFileName() const;
  void setPlayingBgmFileName(const char *name);
  f32 getPlayTime() const;
  f32 getTotalTime() const;
  bool isLoop() const;
  bool isEnablePlayBgmData(const BGMCOND &cond) const;
  bool streamIsPlay(const BGMCOND &cond) const;
  void streamVolume(const BGMCOND &cond);
  u32 getBgmConditionBgmID(u32 id, u32 index) const;

  // Inferred role: first bgm condition with a valid sound handle; original name unknown.
  BGMCOND *unknown003() {
    for (u32 i = 0; i < 4; i++) {
      if (unknown08[i].unknown04.isValid()) {
        return &unknown08[i];
      }
    }
    return nullptr;
  }

  // Inferred role: first bgm condition with a valid sound handle; original name unknown.
  const BGMCOND *unknown003() const {
    for (u32 i = 0; i < 4; i++) {
      if (unknown08[i].unknown04.isValid()) {
        return &unknown08[i];
      }
    }
    return nullptr;
  }

  // Inferred role: first valid sound handle of the bgm conditions; original name unknown.
  const SoundHandle *unknown004() const {
    for (u32 i = 0; i < 4; i++) {
      if (unknown08[i].unknown04.isValid()) {
        return &unknown08[i].unknown04;
      }
    }
    return nullptr;
  }

  mm::mtl::FixedArray<BGMCOND, 4> unknown08;       // Inferred role: bgm conditions; original member name unknown.
  mm::mtl::FixedVector<unknown001, 12> unknown178; // Inferred role: volume fades; original member name unknown.
  mm::mtl::FixedVector<unknown002, 12> unknown3c0; // Inferred role: volume multipliers; original member name unknown.
  u32 m_bgmCondID;
  bool unknown60c;        // Inferred role: constructor argument; original member name unknown.
  bool unknown60d;        // Inferred role: set by update and copyPlayParam; original member name unknown.
  bool unknown60e;        // Inferred role: keeps the bgm id on stopBGM; original member name unknown.
  f32 unknown610;         // Inferred role: multiplied volume; original member name unknown.
  f32 unknown614;         // Inferred role: applied volume; original member name unknown.
  f32 unknown618;         // Inferred role: volume scale; original member name unknown.
  f32 unknown61c;         // Inferred role: start play time; original member name unknown.
  GfFieldBgm *unknown620; // Inferred role: owner field bgm; original member name unknown.
  bool m_pause;
  bool unknown629; // Inferred role: set by copyPlayParam; original member name unknown.
  u8 m_categoryApply;
};

static_assert(offsetof(BgmTrack, unknown08) == 0x08, "");
static_assert(offsetof(BgmTrack, unknown178) == 0x178, "");
static_assert(offsetof(BgmTrack, unknown3c0) == 0x3c0, "");
static_assert(offsetof(BgmTrack, m_bgmCondID) == 0x608, "");
static_assert(offsetof(BgmTrack, unknown610) == 0x610, "");
static_assert(offsetof(BgmTrack, unknown620) == 0x620, "");
static_assert(offsetof(BgmTrack, m_pause) == 0x628, "");
static_assert(offsetof(BgmTrack, m_categoryApply) == 0x62a, "");
static_assert(sizeof(BgmTrack::unknown001) == 0x30, "");
static_assert(sizeof(BgmTrack::unknown002) == 0x30, "");
static_assert(sizeof(BgmTrack) == 0x630, "");

struct ExecFadeParam {
  BgmTrack *unknown00;                   // Inferred role: bgm track; original member name unknown.
  const fw::UpdateInfo *unknown08;       // Inferred role: update info; original member name unknown.
  const BgmTrack::unknown001 *unknown10; // Inferred role: volume fade entry; original member name unknown.
  const BGMCOND *unknown18;              // Inferred role: bgm condition; original member name unknown.
};

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
  void gevPlayEvent(GEV gev, u32 value);
  void gevPause(u32 resumeBits, u32 pauseBits);
  void update(const fw::UpdateInfo &info);
  void destroy();
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
