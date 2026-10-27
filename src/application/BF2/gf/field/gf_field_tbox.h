#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFieldTbox : public mm::mtl::PtrSingleton<GfFieldTbox> {
public:
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void build(const GfSetupParam &param);
  static void destroy();
  bool isDropitemsEmitted() const;
  static void update(const fw::UpdateInfo &info);

  u8 _08[0x80 - 0x08];
  bool m_dropitemsEmitted;
};

static_assert(offsetof(GfFieldTbox, m_dropitemsEmitted) == 0x80, "");

} // namespace gf
