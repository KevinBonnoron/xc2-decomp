#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"

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
};

} // namespace gf
