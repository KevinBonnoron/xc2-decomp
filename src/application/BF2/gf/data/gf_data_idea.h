#pragma once
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

constexpr u32 IDEA_LEVEL_MAX = 10;

class GfDataIdea {
public:
  static void getIdeaAttribute(mm::mtl::FixedVector<u32, 2> &attributes, u32 idea);
  static u32 calcPoint(int level);
  static u32 calcLevel(u32 point);
  static u32 getNeedPoint(int level);
};

struct SDataIdea {
  static const u32 IDEA_MAX = 4;

  // Inferred role: idea; original type name unknown.
  struct unknown004 {
    u32 unknown00; // Inferred role: point; original member name unknown.
    int unknown04; // Inferred role: level; original member name unknown.
  };

  void setLevel(u32 idea, int level);
  void setPoint(u32 idea, u32 point);

  unknown004 unknown00[IDEA_MAX]; // Inferred role: ideas; original member name unknown.
};

static_assert(sizeof(SDataIdea) == 0x20, "");

} // namespace gf
