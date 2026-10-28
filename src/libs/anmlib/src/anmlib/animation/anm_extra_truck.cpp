#include "anm/anm_extra_truck.h"

#include <algorithm>
#include <iterator>
#include <string.h>

#include "anm/anm_array.h"
#include "anm/anm_skeleton.h"

namespace anm {

struct ExtraTruckSlot::CompTruck {
  bool operator()(const char *lhs, const char *rhs) const { return strcmp(lhs, rhs) < 0; }
};

ExtraTruckBuffer::ExtraTruckBuffer(const Skeleton &skeleton, const ExtraTruckSlot &slot, mm::mtl::IAllocator *pAllocator)
    : ReferenceObject(pAllocator), unknown18(&skeleton), unknown20(&slot), unknown28(pAllocator) {
  unknown18->addRef();
  unknown28.resize(unknown20->unknown18.size());
  std::copy(unknown20->unknown18.begin(), unknown20->unknown18.end(), unknown28.begin());
}

ExtraTruckBuffer::~ExtraTruckBuffer() { unknown001(unknown18); }

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
