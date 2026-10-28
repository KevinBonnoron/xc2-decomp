#include "anm/anm_space_resolve_util.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "anm/anm_transform_util.h"
#include "types.h"

namespace anm {

bool SpaceResolveUtil::clacPoseMSNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms) {
  u32 count = binding->m_indexTable.size();
  if (count != skeleton->getBoneCount()) {
    return false;
  }
  for (u32 i = 0; i < count; i++) {
    if (binding->m_indexTable[i] < 0) {
      s16 parent = skeleton->unknown003(i);
      if (parent == -1) {
        transforms[i] = skeleton->unknown40[i];
      } else {
        TransformUtil::mul(transforms[parent], skeleton->unknown40[i], &transforms[i]);
      }
    }
  }
  return true;
}

void SpaceResolveUtil::convertLStoMS(const Skeleton *skeleton, QsTransform *transforms) {
  u32 count = skeleton->getBoneCount();
  for (u32 i = 0; i < count; i++) {
    s16 parent = skeleton->unknown003(i);
    if (parent != -1) {
      TransformUtil::mul(transforms[parent], transforms[i], &transforms[i]);
    }
  }
}

void SpaceResolveUtil::convertLStoMSPartial(const Skeleton *skeleton, const bool *mask, QsTransform *transforms) {
  u32 count = skeleton->getBoneCount();
  for (u32 i = 0; i < count; i++) {
    s16 parent = skeleton->unknown003(i);
    if (mask[i] && parent != -1) {
      TransformUtil::mul(transforms[parent], transforms[i], &transforms[i]);
    }
  }
}

void SpaceResolveUtil::convertMStoLS(const Skeleton *skeleton, QsTransform *transforms) {
  for (u32 i = skeleton->getBoneCount() - 1; i != 0; i--) {
    s16 parent = skeleton->unknown003(i);
    if (parent != -1) {
      QsTransform inverse;
      TransformUtil::invert(transforms[parent], &inverse);
      TransformUtil::mul(inverse, transforms[i], &transforms[i]);
    }
  }
}

void SpaceResolveUtil::convertMStoLSPartial(const Skeleton *skeleton, const bool *mask, QsTransform *transforms) {
  for (u32 i = skeleton->getBoneCount() - 1; i != 0; i--) {
    s16 parent = skeleton->unknown003(i);
    if (mask[i] && parent != -1) {
      QsTransform inverse;
      TransformUtil::invert(transforms[parent], &inverse);
      TransformUtil::mul(inverse, transforms[i], &transforms[i]);
    }
  }
}

bool SpaceResolveUtil::setReferencePoseNoTruck(const Binding *binding, const Skeleton *skeleton, QsTransform *transforms) {
  u32 count = binding->m_indexTable.size();
  if (count != skeleton->unknown30.size()) {
    return false;
  }
  for (u32 i = 0; i < count; i++) {
    if (binding->m_indexTable[i] < 0) {
      transforms[i] = skeleton->unknown40[i];
    }
  }
  return true;
}

} // namespace anm
