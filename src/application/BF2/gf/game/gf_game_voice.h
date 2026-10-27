#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;
struct GfVoiceName;
struct GAME_VOICE_HANDLE;

enum CV_PRIO {
  CV_PRIO_UNKNOWN_1 = 1,
  CV_PRIO_UNKNOWN_2 = 2,
};

class GfGameVoice : public mm::mtl::PtrSingleton<GfGameVoice> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static u32 getResult(GF_OBJ_HANDLE *handle);
  static GAME_VOICE_HANDLE *playVoice(GF_OBJ_HANDLE *handle, const char *name, CV_PRIO priority);
  static void gevLayerPause(u32 layer, bool isPause);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  bool isPlayEnemyVoice() const;
  bool isPlayVoice(GF_OBJ_HANDLE *handle) const;
  void applyHanaVoiceCondirtion(GfVoiceName &name);
  static bool isInitialized();

  GAME_VOICE_HANDLE *createHandle();

  bool unknown08; // Inferred role: initialized; original member name unknown.
  u8 _09[0x110 - 0x09];
  u64 unknown110; // Inferred role: handle serial; original member name unknown.
};

static_assert(offsetof(GfGameVoice, unknown110) == 0x110, "");

} // namespace gf
