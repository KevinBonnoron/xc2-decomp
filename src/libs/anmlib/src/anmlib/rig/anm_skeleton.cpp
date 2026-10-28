#include "anm/anm_skeleton.h"

#include <algorithm>
#include <iterator>
#include <string.h>

#include "anm/anm_array.h"
#include "anm/anm_extra_truck.h"

namespace anm {

struct Skeleton::CompTruck {
  bool operator()(const ExtraTruckSlot &lhs, const char *rhs) const { return strcmp(lhs.unknown00, rhs) < 0; }
};

struct Skeleton::CompLable {
  bool operator()(const SkelLabel &lhs, const LabelKey &rhs) const {
    if (lhs.unknown00 == rhs.unknown00) {
      return lhs.unknown04 < rhs.unknown04;
    }
    return lhs.unknown00 < rhs.unknown00;
  }
};

u16 Skeleton::getExtraTruckSlotID(const char *name) const {
  if (unknown50.size() != 0) {
    ArrayIterartor<const ExtraTruckSlot> it = std::lower_bound(unknown50.begin(), unknown50.end(), name, CompTruck());
    if (it != unknown50.end() && strcmp(it->unknown00, name) == 0) {
      return std::distance(unknown50.begin(), it);
    }
  }
  return 0xffff;
}

const Skeleton::Bone *Skeleton::getBoneFromLabel(LabelType type, u16 id) const {
  u16 bone = 0xffff;
  if (unknown90.size() != 0) {
    LabelKey key = {type, id};
    ArrayIterartor<const SkelLabel> it = std::lower_bound(unknown90.begin(), unknown90.end(), key, CompLable());
    if (it != unknown90.end() && it->unknown00 == type && it->unknown04 == id) {
      bone = it->unknown06;
    }
  }
  if (bone == 0xffff) {
    return nullptr;
  }
  return &unknown30[bone];
}

} // namespace anm
