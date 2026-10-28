#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Binding;
class Skeleton;
struct ExtraBinding;

// Inferred base class of CubicExtraTruck and UncompressExtraTruck (first virtual is sampleTrucks); original name unknown.
class unknown002 {
public:
  virtual void sampleTrucks(f32 time, const Binding &binding, const ExtraBinding &extraBinding, u32 count, f32 *values) const = 0;
};

class ExtraTruckSlot {
public:
  struct CompTruck;

  u16 getTruckID(const char *name) const;

  const char *unknown00;         // Inferred role: name; original member name unknown.
  Array<const char *> unknown08; // Inferred role: truck names, sorted; original member name unknown.
  u8 _18[0x20 - 0x18];
  u32 unknown20; // Inferred role: truck count; original member name unknown.
  u8 _24[0x38 - 0x24];
};

static_assert(offsetof(ExtraTruckSlot, unknown00) == 0x00, "");
static_assert(offsetof(ExtraTruckSlot, unknown08) == 0x08, "");
static_assert(offsetof(ExtraTruckSlot, unknown20) == 0x20, "");
static_assert(sizeof(ExtraTruckSlot) == 0x38, "");

class ExtraTruckBuffer : public ReferenceObject {
public:
  ExtraTruckBuffer(const Skeleton &skeleton, const ExtraTruckSlot &slot, mm::mtl::IAllocator *pAllocator);
  const Skeleton *unknown18;       // Inferred role: skeleton; original member name unknown.
  const ExtraTruckSlot *unknown20; // Inferred role: slot; original member name unknown.
  f32 *unknown28;                  // Inferred role: truck values (start of an mtl::Vector<float>); original member name unknown.
  size_t unknown30;                // Inferred role: truck value count; original member name unknown.
  u8 _38[0x50 - 0x38];
};

static_assert(offsetof(ExtraTruckBuffer, unknown18) == 0x18, "");
static_assert(offsetof(ExtraTruckBuffer, unknown20) == 0x20, "");
static_assert(offsetof(ExtraTruckBuffer, unknown28) == 0x28, "");
static_assert(offsetof(ExtraTruckBuffer, unknown30) == 0x30, "");
static_assert(sizeof(ExtraTruckBuffer) == 0x50, "");

} // namespace anm
