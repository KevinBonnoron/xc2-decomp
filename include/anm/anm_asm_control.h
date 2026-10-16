#pragma once
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class ASMControl : public ReferenceObject {
public:
  void updateFrame(f32 deltaTime);
};

} // namespace anm
