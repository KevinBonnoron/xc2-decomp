#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"

namespace anm {

class Skeleton;

class Pose : public ReferenceObject {
public:
  void syncLocalSpace();
  void syncModelSpace();

  const Skeleton *skeleton;
};

static_assert(offsetof(Pose, skeleton) == 0x18, "");

} // namespace anm
