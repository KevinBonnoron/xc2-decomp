#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Skeleton;
struct QsTransform;

class Pose : public ReferenceObject {
public:
  void syncLocalSpace();
  void syncModelSpace();
  const QsTransform &getBoneModelSpace(u16 bone);
  const QsTransform &getBoneLocalSpace(u16 bone);
  void setBoneLocalSpace(u16 bone, const QsTransform &transform);

  const Skeleton *unknown18; // Inferred role: skeleton; original member name unknown.
};

static_assert(offsetof(Pose, unknown18) == 0x18, "");

} // namespace anm
