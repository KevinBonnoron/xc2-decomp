#include "anm/anm_skeleton_mapper.h"

#include <string.h>

#include "anm/anm_skeleton.h"

namespace anm {

SkeletonMapper::SkeletonMapper(const Skeleton &skeletonA, const Skeleton &skeletonB, const SkeletonMapperData &data, mm::mtl::IAllocator *pAllocator)
    : ReferenceObject(pAllocator), unknown18(&skeletonA), unknown20(&skeletonB), unknown28(&data), unknown30(pAllocator) {
  u32 count;
  if (data.unknown28 > data.unknown2c) {
    count = data.unknown28;
  } else {
    count = data.unknown2c;
  }
  unknown30.reserve(count);
}

SkeletonMapper::~SkeletonMapper() {}

bool SkeletonMapper::enableBind(const Skeleton &skeletonA, const Skeleton &skeletonB, const SkeletonMapperData &data) {
  if (data.unknown28 == skeletonA.unknown30.size() && data.unknown2c == skeletonB.unknown30.size() && strcmp(skeletonA.unknown18, data.unknown18) == 0 &&
      strcmp(skeletonB.unknown18, data.unknown20) == 0) {
    return true;
  }
  return false;
}

} // namespace anm
