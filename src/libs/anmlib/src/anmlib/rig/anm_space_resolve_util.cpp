#include "anm/anm_space_resolve_util.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_skeleton.h"
#include "types.h"

namespace anm {

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
