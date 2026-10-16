#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFieldCollect : public mm::mtl::PtrSingleton<GfFieldCollect> {
public:
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
};

} // namespace gf
