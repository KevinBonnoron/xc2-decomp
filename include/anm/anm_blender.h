#pragma once
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Control;

class Blender : public ReferenceObject {
public:
  bool addControl(Control *control);
  bool removeControl(Control *control);
  void update(f32 deltaTime);
};

} // namespace anm
