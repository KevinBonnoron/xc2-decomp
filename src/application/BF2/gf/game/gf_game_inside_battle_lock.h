#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfGameInsideBattleLock : public mm::mtl::PtrSingleton<GfGameInsideBattleLock> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);

  u8 _08[0x20 - 0x08];
  bool isPlayerInside;
};

static_assert(offsetof(GfGameInsideBattleLock, isPlayerInside) == 0x20, "");

} // namespace gf
