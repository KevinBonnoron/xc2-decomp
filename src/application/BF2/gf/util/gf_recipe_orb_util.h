#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct OrbRecipe {
  u16 unknown00; // Inferred role: item id; original member name unknown.
  u16 unknown02; // Inferred role: item count; original member name unknown.
};

static_assert(sizeof(OrbRecipe) == 0x4, "");

class GfRecipeOrbUtil {
public:
  static bool getRecipeItemsByItemBox(mm::mtl::FixedVector<OrbRecipe, 128> &items, u32 id);
  static bool isEnableRecipe(u32 id);
  static u32 getRecipeID(u32 id);
  static u32 getEquipOrb(u32 id);
};

} // namespace gf
