#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfDataSalvage {
public:
  static bool getSalvageSkillBlade(mm::mtl::FixedVector<u16, 422> &blades);
  static u8 getSalvageSkillLevel(u32 blade);
};

} // namespace gf
