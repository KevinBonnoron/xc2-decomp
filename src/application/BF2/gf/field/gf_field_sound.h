#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class SoundPack;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfFieldSound : public mm::mtl::PtrSingleton<GfFieldSound> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  void update(const fw::UpdateInfo &info);
  void postUpdate(const fw::UpdateInfo &info);
  void clear();
  void gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter);
  void gevPlayEvent(GEV event, u32 value);
  void gevBattleEnd();
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void gevPause(u32 resumeBits, u32 pauseBits);
  fw::SoundPack *getCommonPack();
  fw::SoundPack *getMapPack();
  void setCategorySeFadeoutForEvent(f32 volume);

  u8 _08[0xc4 - 0x08];
  mm::mtl::FixStr<64> unknownc4; // Inferred role: map se pack name; original member name unknown.
};

static_assert(offsetof(GfFieldSound, unknownc4) == 0xc4, "");

} // namespace gf
