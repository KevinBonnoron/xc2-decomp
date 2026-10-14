#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfDataIdea {
public:
  static void getIdeaAttribute(mm::mtl::FixedVector<u32, 2> &attributes, u32 idea);
  static u32 calcPoint(int level);
  static u32 calcLevel(u32 point);
  static u32 getNeedPoint(int level);
};

} // namespace gf
