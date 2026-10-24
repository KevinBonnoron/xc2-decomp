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
  GfEvtBgm(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfEvtBgm();
  void clear();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  void playBgm(const EventBgmSetup &setup);
  bool isPlayBgm() const;
  void stopBgm(const EventBgmSetup &setup);
  void cancelOverTime();
  void changeBgmVolume(const EventBgmSetup &setup);
  f32 getPlayBgmTime() const;
  f32 getTotalBgmTime() const;
  void update(const fw::UpdateInfo &info);

  u8 _08[0x50 - 0x08];
  f32 m_playBgmVolume;
  u8 _54[0x490 - 0x54];
};

static_assert(offsetof(GfEvtBgm, m_playBgmVolume) == 0x50, "");
static_assert(sizeof(GfEvtBgm) == 0x490, "");

} // namespace gf
