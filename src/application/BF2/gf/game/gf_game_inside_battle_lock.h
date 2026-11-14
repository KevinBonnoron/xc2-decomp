#pragma once
#include <stddef.h>

#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Vec3;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfGameInsideBattleLock : public mm::mtl::PtrSingleton<GfGameInsideBattleLock> {
public:
  // Inlined in build (0x7100316e98); the game has no constructor symbol.
  GfGameInsideBattleLock() : unknown20(false) {}

  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  void updateInfos();
  static void updateInfo(GF_OBJ_HANDLE *handle);
  static bool isInside(GF_OBJ_HANDLE *handle);
  static bool isInside(const mm::Vec3 &position);
  bool isInsideBattleLock(GF_OBJ_HANDLE *handle) const;

  mm::mtl::Map<GF_OBJ_HANDLE *, bool> unknown08; // Inferred role: whether each enemy is inside a battle lock; original member name unknown.
  bool unknown20;                                // Inferred role: player inside; original member name unknown.
};

static_assert(offsetof(GfGameInsideBattleLock, unknown20) == 0x20, "");

} // namespace gf
