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

  struct Idea {
    u32 point;
    int level;
  };

  void setLevel(u32 idea, int level);
  void setPoint(u32 idea, u32 point);

  Idea ideas[IDEA_MAX];
};

static_assert(sizeof(SDataIdea) == 0x20, "");

} // namespace gf
