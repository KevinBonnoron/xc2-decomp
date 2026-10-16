#include "gf/data/gf_data_idea.h"

#include "gf/data/gf_bdat_blade.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  ATTRIBUTE_FIRE = 1,
  ATTRIBUTE_WATER = 2,
  ATTRIBUTE_WIND = 3,
  ATTRIBUTE_EARTH = 4,
  ATTRIBUTE_VOLT = 5,
  ATTRIBUTE_ICE = 6,
  ATTRIBUTE_LIGHT = 7,
  ATTRIBUTE_DARK = 8,
};

constexpr u32 IDEA_LEVEL_MAX = 10;

void GfDataIdea::getIdeaAttribute(mm::mtl::FixedVector<u32, 2> &attributes, u32 idea) {
  switch (idea) {
  case 0:
    attributes.push_back(ATTRIBUTE_FIRE);
    attributes.push_back(ATTRIBUTE_WATER);
    break;
  case 1:
    attributes.push_back(ATTRIBUTE_WIND);
    attributes.push_back(ATTRIBUTE_ICE);
    break;
  case 2:
    attributes.push_back(ATTRIBUTE_EARTH);
    attributes.push_back(ATTRIBUTE_VOLT);
    break;
  case 3:
    attributes.push_back(ATTRIBUTE_LIGHT);
    attributes.push_back(ATTRIBUTE_DARK);
    break;
  }
}

u32 GfDataIdea::calcPoint(int level) {
  if (level < 0 || static_cast<u32>(level) > IDEA_LEVEL_MAX) {
    return 0;
  }

  return GfBdatBlade::get()->getBLD_IdeaNeedPoint(level);
}

u32 GfDataIdea::calcLevel(u32 point) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  for (u32 level = 1; level <= IDEA_LEVEL_MAX; level++) {
    if (point < bdatBlade->getBLD_IdeaNeedPoint(level)) {
      return level - 1;
    }
  }

  return IDEA_LEVEL_MAX;
}

u32 GfDataIdea::getNeedPoint(int level) {
  if (level < 0 || static_cast<u32>(level) > IDEA_LEVEL_MAX) {
    return 0;
  }

  return GfBdatBlade::get()->getBLD_IdeaNeedPoint(level);
}

} // namespace gf
