#pragma once
#include "event/i_manager.h"
#include "framework/sound/sound_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CsSndManager : public IManager, public mm::mtl::Singleton<CsSndManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: preload flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: pause flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: stall flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
  };

  CsSndManager();
  virtual ~CsSndManager() {}
  void clear();
  void stop();
  void update();
  void render();
  f32 getPlayFrame() const;
  f32 getTotalFrame() const;
  void preloadAuto(const char *name);
  static void makePath(mm::mtl::FixStr<256> &path, const char *name);
  void preload(const char *path);
  bool isLoading() const;
  void playAuto(const char *name);
  void play(const char *path);
  static u32 playBgm(const char *path, f32 volume, bool isPause);
  bool isPlay() const;
  void pause(bool isPause);
  void setDisp(bool isDisp);
  bool isDisp() const;
  f32 getSyncFrame() const;
  void setSyncFrame(f32 frame);
  f32 getStartedTotalFrame() const;
  void setSyncFrameOffset(f32 offset);
  virtual void OnEventProc(MSG_TYPE type);

private:
  static const s32 unknown001[7]; // Inferred role: heights of the debug sound bars; original name unknown.

  void stopPreload() {
    fw::SoundManager::get()->stopBgm(unknown18, 1.0f);
    unknown18 = 0;
    unknown20 = "";
    unknown10 &= ~FLAG_UNKNOWN_0;
  }

  void stopPlay() {
    fw::SoundManager::get()->stopBgm(unknown1c, 1.0f);
    unknown1c = 0;
    unknown124 = "";
    unknown10 &= ~(FLAG_UNKNOWN_1 | FLAG_UNKNOWN_2 | FLAG_UNKNOWN_3);
  }

  u32 unknown10;                   // Inferred role: flags; original member name unknown.
  u32 unknown14;                   // Inferred role: disp flags; original member name unknown.
  u32 unknown18;                   // Inferred role: preload handle; original member name unknown.
  u32 unknown1c;                   // Inferred role: play handle; original member name unknown.
  mm::mtl::FixStr<256> unknown20;  // Inferred role: preload path; original member name unknown.
  mm::mtl::FixStr<256> unknown124; // Inferred role: play path; original member name unknown.
  f32 unknown228;                  // Inferred role: prev play time; original member name unknown.
  int unknown22c;                  // Inferred role: stall count; original member name unknown.
  int unknown230;                  // Inferred role: restart count; original member name unknown.
  f32 m_startedTotalFrame;
  u64 unknown238; // Inferred role: unused; original member name unknown.
  f32 m_syncFrameOffset;
};

static_assert(sizeof(CsSndManager) == 0x248, "");

} // namespace event
