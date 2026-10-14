#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct MapjumpCallbackInfo;

class GfGameVoice : public mm::mtl::PtrSingleton<GfGameVoice> {
public:
  static u32 getResult(GF_OBJ_HANDLE *handle);
  static void gevLayerPause(u32 layer, bool isPause);
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  bool isPlayEnemyVoice() const;
  bool isPlayVoice(GF_OBJ_HANDLE *handle) const;
};

} // namespace gf
