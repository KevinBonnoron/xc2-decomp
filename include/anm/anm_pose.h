#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Skeleton;
struct QsTransform;

class Pose : public ReferenceObject {
public:
  enum PROPAGATE_TYPE : int {
    PROPAGATE_TYPE_UNKNOWN_1 = 1,
  };

  void syncLocalSpace();
  void syncModelSpace();
  void setReferencePose();
  Array<QsTransform> &accessSyncedPoseLocalSpace();
  Array<QsTransform> &accessSyncedPoseModelSpace();
  const QsTransform &getBoneModelSpace(u16 bone);
  const QsTransform &getBoneLocalSpace(u16 bone);
  void setBoneLocalSpace(u16 bone, const QsTransform &transform);
  void setBoneModelSpace(u16 bone, const QsTransform &transform, PROPAGATE_TYPE propagate);

  const Skeleton *unknown18; // Inferred role: skeleton; original member name unknown.
};

static_assert(offsetof(Pose, unknown18) == 0x18, "");

} // namespace anm
