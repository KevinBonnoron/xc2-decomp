#pragma once
#include <stddef.h>

#include "anm/anm_qs_transform.h"
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

class Blender : public ReferenceObject {
public:
  // Inferred scratch buffers of the sampling functions; original member names unknown.
  struct Work {
    mm::mtl::Vector<f32> unknown00;         // Inferred role: extra truck values; original member name unknown.
    mm::mtl::Vector<QsTransform> unknown28; // Inferred role: transforms; original member name unknown.
    mm::mtl::Vector<f32> unknown50;         // Inferred role: extra truck values; original member name unknown.
    mm::mtl::Vector<bool> unknown78;        // Inferred role: bone flags; original member name unknown.
  };

  Blender(const Skeleton *skeleton, mm::mtl::IAllocator *allocator);
  ~Blender() override;
  bool addControl(Control *control);
  bool removeControl(Control *control);
  void update(f32 deltaTime);
  void sampleTrucks(u32 count, QsTransform *transforms);
  void sampleTrucksMS(u32 count, QsTransform *transforms);
  void sampleExtraTrucks(u16 slot, u32 count, f32 *values);

  mm::mtl::Vector<Control *> unknown18; // Inferred role: controls; original member name unknown.
  const Skeleton *unknown40;            // Inferred role: p skeleton; original member name unknown.
  Work *unknown48;                      // Inferred role: scratch buffers; original member name unknown.
};

static_assert(sizeof(Blender::Work) == 0xa0, "");
static_assert(offsetof(Blender::Work, unknown28) == 0x28, "");
static_assert(offsetof(Blender::Work, unknown50) == 0x50, "");
static_assert(offsetof(Blender::Work, unknown78) == 0x78, "");
static_assert(offsetof(Blender, unknown18) == 0x18, "");
static_assert(offsetof(Blender, unknown40) == 0x40, "");
static_assert(offsetof(Blender, unknown48) == 0x48, "");
static_assert(sizeof(Blender) == 0x50, "");

} // namespace anm
