#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct EventBgmSetup;
struct GfSetupParam;

class GfEvtBgm : public mm::mtl::PtrSingleton<GfEvtBgm> {
public:
  enum PLAY_STATE {
    PLAY_STATE_UNKNOWN_0 = 0,
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
  void stopBgm(const EventBgmSetup &setup);
  void cancelOverTime();
  void changeBgmVolume(const EventBgmSetup &setup);
  f32 getPlayBgmTime() const;
  f32 getTotalBgmTime() const;
  void update(const fw::UpdateInfo &info);
  void setPlayBgmVolume(f32 volume);
  void setPlayState(PLAY_STATE playState);
  bool isEnableEventBgm() const;
  void setFadeoutVolume();

  bool m_initialized;
  u8 _09[0x50 - 0x09];
  f32 m_playBgmVolume;
  u8 _54[0x74 - 0x54];
  PLAY_STATE m_playState;
  u8 _78[0x478 - 0x78];
  void *unknown478; // Role and original member name unknown.
  u8 _480[0x490 - 0x480];
};

static_assert(offsetof(GfEvtBgm, m_initialized) == 0x08, "");
static_assert(offsetof(GfEvtBgm, m_playBgmVolume) == 0x50, "");
static_assert(offsetof(GfEvtBgm, m_playState) == 0x74, "");
static_assert(offsetof(GfEvtBgm, unknown478) == 0x478, "");
static_assert(sizeof(GfEvtBgm) == 0x490, "");

} // namespace gf
