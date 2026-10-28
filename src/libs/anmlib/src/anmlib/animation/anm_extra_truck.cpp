#include "anm/anm_extra_truck.h"

#include <algorithm>
#include <iterator>
#include <string.h>

#include "anm/anm_array.h"

namespace anm {

struct ExtraTruckSlot::CompTruck {
  bool operator()(const char *lhs, const char *rhs) const { return strcmp(lhs, rhs) < 0; }
};

u16 ExtraTruckSlot::getTruckID(const char *name) const {
  if (unknown08.size() != 0) {
    ArrayIterartor<const char *const> it = std::lower_bound(unknown08.begin(), unknown08.end(), name, CompTruck());
    if (it != unknown08.end() && strcmp(*it, name) == 0) {
      return std::distance(unknown08.begin(), it);
    }
  }
  return 0xffff;
}

} // namespace anm
