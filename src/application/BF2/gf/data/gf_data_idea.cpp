#include "gf/data/gf_data_idea.h"

#include "gf/data/gf_bdat_blade.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  ATTRIBUTE_UNKNOWN_1 = 1, // Inferred role: attribute fire; original name unknown.
  ATTRIBUTE_UNKNOWN_2 = 2, // Inferred role: attribute water; original name unknown.
  ATTRIBUTE_UNKNOWN_3 = 3, // Inferred role: attribute wind; original name unknown.
  ATTRIBUTE_UNKNOWN_4 = 4, // Inferred role: attribute earth; original name unknown.
  ATTRIBUTE_UNKNOWN_5 = 5, // Inferred role: attribute volt; original name unknown.
  ATTRIBUTE_UNKNOWN_6 = 6, // Inferred role: attribute ice; original name unknown.
  ATTRIBUTE_UNKNOWN_7 = 7, // Inferred role: attribute light; original name unknown.
  ATTRIBUTE_UNKNOWN_8 = 8, // Inferred role: attribute dark; original name unknown.
};

void GfDataIdea::getIdeaAttribute(mm::mtl::FixedVector<u32, 2> &attributes, u32 idea) {
  switch (idea) {
  case 0:
    attributes.push_back(ATTRIBUTE_UNKNOWN_1);
    attributes.push_back(ATTRIBUTE_UNKNOWN_2);
    break;
  case 1:
    attributes.push_back(ATTRIBUTE_UNKNOWN_3);
    attributes.push_back(ATTRIBUTE_UNKNOWN_6);
    break;
  case 2:
    attributes.push_back(ATTRIBUTE_UNKNOWN_4);
    attributes.push_back(ATTRIBUTE_UNKNOWN_5);
    break;
  case 3:
    attributes.push_back(ATTRIBUTE_UNKNOWN_7);
    attributes.push_back(ATTRIBUTE_UNKNOWN_8);
    break;
  }
}

u32 GfDataIdea::calcPoint(int level) {
  if (level < 0 || static_cast<u32>(level) > IDEA_LEVEL_UNKNOWN_10) {
    return 0;
  }

  return GfBdatBlade::get()->getBLD_IdeaNeedPoint(level);
}

u32 GfDataIdea::calcLevel(u32 point) {
  GfBdatBlade *bdatBlade = GfBdatBlade::get();
  for (u32 level = 1; level <= IDEA_LEVEL_UNKNOWN_10; level++) {
    if (point < bdatBlade->getBLD_IdeaNeedPoint(level)) {
      return level - 1;
    }
  }

  return IDEA_LEVEL_UNKNOWN_10;
}

u32 GfDataIdea::getNeedPoint(int level) {
  if (level < 0 || static_cast<u32>(level) > IDEA_LEVEL_UNKNOWN_10) {
    return 0;
  }

  return GfBdatBlade::get()->getBLD_IdeaNeedPoint(level);
}

void SDataIdea::setPoint(u32 idea, u32 point) {
  unknown00[idea].unknown00 = point;
  unknown00[idea].unknown04 = GfDataIdea::calcLevel(point);
}

} // namespace gf
