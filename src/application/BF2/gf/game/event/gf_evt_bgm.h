#pragma once
#include <stddef.h>

#include "gf/game/event/gf_event_bgm_setup.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class EvtBgmTask;
struct GfSetupParam;

class GfEvtBgm : public mm::mtl::PtrSingleton<GfEvtBgm> {
public:
  enum PLAY_STATE {
    PLAY_STATE_UNKNOWN_0 = 0,
    PLAY_STATE_UNKNOWN_1 = 1,
    PLAY_STATE_UNKNOWN_2 = 2,
    PLAY_STATE_UNKNOWN_3 = 3,
    PLAY_STATE_UNKNOWN_4 = 4,
  };

  GfEvtBgm(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfEvtBgm();
  void clear();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  bool isInitialized();
  void playBgm(const EventBgmSetup &setup);
  bool isPlayBgm() const;
  bool isPlaySilent() const;
  void stopBgm(const EventBgmSetup &setup);
  void cancelOverTime();
  void changeBgmVolume(const EventBgmSetup &setup);
  f32 getPlayBgmTime() const;
  f32 getTotalBgmTime() const;
  void update(const fw::UpdateInfo &info);
  void updateBgmTask(const fw::UpdateInfo &info);
  void setPlayBgmVolume(f32 volume);
  void setPlayBgmTakeOver(const char *name);
  void setPlayParam(const EventBgmSetup &setup);
  void setPlayState(PLAY_STATE playState);
  bool isEnableEventBgm() const;
  void setFadeoutVolume();

  bool m_initialized;
  u8 _09[0x0c - 0x09];
  EventBgmSetup m_eventBgmSetup; // Inferred role: setup of the playing event bgm; original member name unknown.
  PLAY_STATE m_playState;
  // Layout from GfEvtBgm::clear (0x7100306e9c), isPlayBgm (0x7100307364) and isPlaySilent (0x71003077a4), which walk 128 task pointers at 0x78 from the
  // index at 0x480 for the count at 0x478 with `& 0x7f`.
  mm::mtl::FixedQueue<EvtBgmTask *, 128> unknown78; // Inferred role: queue of the event bgm tasks; original member name unknown.
  void *unknown488;                                 // Role and original member name unknown.
};

static_assert(offsetof(GfEvtBgm, m_initialized) == 0x08, "");
static_assert(offsetof(GfEvtBgm, m_eventBgmSetup) == 0x0c, "");
static_assert(offsetof(GfEvtBgm, m_playState) == 0x74, "");
static_assert(offsetof(GfEvtBgm, unknown78) == 0x78, "");
static_assert(offsetof(GfEvtBgm, unknown488) == 0x488, "");
static_assert(sizeof(GfEvtBgm) == 0x490, "");

} // namespace gf
