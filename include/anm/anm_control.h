#pragma once
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Control : public ReferenceObject {
public:
  void update(f32 deltaTime);
};

} // namespace anm
