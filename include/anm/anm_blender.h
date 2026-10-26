#pragma once
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class Control;
struct QsTransform;

class Blender : public ReferenceObject {
public:
  bool addControl(Control *control);
  bool removeControl(Control *control);
  void update(f32 deltaTime);
  void sampleTrucks(u32 count, QsTransform *transforms);
  void sampleTrucksMS(u32 count, QsTransform *transforms);
  void sampleExtraTrucks(u16 slot, u32 count, f32 *values);
};

} // namespace anm
