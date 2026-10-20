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

  const Skeleton *skeleton;
};

static_assert(offsetof(Pose, skeleton) == 0x18, "");

} // namespace anm
