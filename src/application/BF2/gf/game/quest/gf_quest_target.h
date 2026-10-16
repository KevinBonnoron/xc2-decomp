#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfQuestTarget : public mm::mtl::PtrSingleton<GfQuestTarget> {
public:
  GfQuestTarget();
  ~GfQuestTarget();
  void update(const fw::UpdateInfo &info);
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);

  u8 _08[0x4440 - 0x08];
};

static_assert(sizeof(GfQuestTarget) == 0x4440, "");

} // namespace gf
