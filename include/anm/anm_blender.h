#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Control;
class Skeleton;
struct QsTransform;

class Blender : public ReferenceObject {
public:
  Blender(const Skeleton *skeleton, mm::mtl::IAllocator *allocator);
  bool addControl(Control *control);
  bool removeControl(Control *control);
  void update(f32 deltaTime);
  void sampleTrucks(u32 count, QsTransform *transforms);
  void sampleTrucksMS(u32 count, QsTransform *transforms);
  void sampleExtraTrucks(u16 slot, u32 count, f32 *values);

  mm::mtl::Vector<Control *> unknown18; // Inferred role: controls; original member name unknown.
  const Skeleton *unknown40;            // Inferred role: p skeleton; original member name unknown.
  u8 _48[0x50 - 0x48];
};

static_assert(offsetof(Blender, unknown18) == 0x18, "");
static_assert(offsetof(Blender, unknown40) == 0x40, "");
static_assert(sizeof(Blender) == 0x50, "");

} // namespace anm
