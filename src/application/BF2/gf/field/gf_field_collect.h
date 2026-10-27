#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfFieldCollect : public mm::mtl::PtrSingleton<GfFieldCollect> {
public:
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void seqEnd(float time);
  void start(GF_OBJ_HANDLE *handle);
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);

  u8 _08[0x1f0 - 0x08];
};

static_assert(sizeof(GfFieldCollect) == 0x1f0, "");

} // namespace gf
