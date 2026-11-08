#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

// Layout evidence: the constructor (0x71002f5de8) clears 0x00 and the vector at 0x20, create (0x71002f5e08) stores the
// effect count at 0x00 and the three effect resources at 0x08, 0x10 and 0x18 and reserves the vector.
class GfFobjGottenEffectManager {
public:
  // Layout evidence: create reads the effect count at 0x00.
  struct CreateInfo {
    u32 unknown00; // Inferred role: effect count; original member name unknown.
  };

  // Layout evidence: createEffect (0x71002f60dc) reads the start position at 0x00, the target at 0x10 and the
  // effect resource index at 0x18.
  struct CreateEffectInfo {
    mm::Vec3 unknown00;       // Inferred role: start position; original member name unknown.
    GF_OBJ_HANDLE *unknown10; // Inferred role: target object; original member name unknown.
    u8 unknown18;             // Inferred role: effect resource index; original member name unknown.
  };

  // Layout evidence: createEffect (0x71002f60dc) fills the four curve points, the effect handle and the target
  // before Vector<EffectInfo>::push_back (0x71002f6424), whose copy moves the Vec3 members one by one and the bytes
  // from 0x40 to 0x54 raw; update (0x71002f6558) advances the time at 0x50 and moves the effect along the curve.
  struct EffectInfo {
    mm::Vec3 unknown00;       // Inferred role: start position; original member name unknown.
    mm::Vec3 unknown10;       // Inferred role: first control point; original member name unknown.
    mm::Vec3 unknown20;       // Inferred role: second control point; original member name unknown.
    mm::Vec3 unknown30;       // Inferred role: target position; original member name unknown.
    u32 unknown40;            // Inferred role: effect handle; original member name unknown.
    GF_OBJ_HANDLE *unknown48; // Inferred role: target object; original member name unknown.
    f32 unknown50;            // Inferred role: elapsed time; original member name unknown.
  };

  GfFobjGottenEffectManager(const CreateInfo *info);
  ~GfFobjGottenEffectManager() { dispose(); }
  void create(const CreateInfo &info);
  void dispose();
  void update(f32 deltaTime);
  void createEffect(const CreateEffectInfo &info);
  void createResHandles();
  bool getTargetPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle) const;

  u32 unknown00;                         // Inferred role: effect count; original member name unknown.
  void *unknown08[3];                    // Inferred role: effect resources cmn_200_030 to cmn_200_032; original member name unknown.
  mm::mtl::Vector<EffectInfo> unknown20; // Inferred role: running effects; original member name unknown.
};

static_assert(offsetof(GfFobjGottenEffectManager::CreateEffectInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjGottenEffectManager::CreateEffectInfo, unknown18) == 0x18, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown20) == 0x20, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown40) == 0x40, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown48) == 0x48, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown50) == 0x50, "");
static_assert(sizeof(GfFobjGottenEffectManager::EffectInfo) == 0x60, "");
static_assert(offsetof(GfFobjGottenEffectManager, unknown08) == 0x08, "");
static_assert(offsetof(GfFobjGottenEffectManager, unknown20) == 0x20, "");
static_assert(sizeof(GfFobjGottenEffectManager) == 0x48, "");

} // namespace gf
