#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "mm_mtl/vector.h"
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

  u8 _08[0x10 - 0x08];
  u8 unknown10; // Inferred role: impl type tag (0 uncompressed, 1 cubic); original member name unknown.
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(unknown002, unknown10) == 0x10, "");
static_assert(sizeof(unknown002) == 0x18, "");

// Inferred limit of an extra truck value; original name unknown.
struct unknown00f {
  f32 unknown00; // Inferred role: minimum; original member name unknown.
  f32 unknown04; // Inferred role: maximum; original member name unknown.
};

static_assert(sizeof(unknown00f) == 0x8, "");

class ExtraTruckSlot {
public:
  struct CompTruck;

  u16 getTruckID(const char *name) const;
  // Inferred helper: truck name by 16-bit index; original name unknown.
  const char *unknown001(u16 index) const { return unknown08[index]; }

  const char *unknown00;         // Inferred role: name; original member name unknown.
  Array<const char *> unknown08; // Inferred role: truck names, sorted; original member name unknown.
  Array<f32> unknown18;          // Inferred role: reference values of the trucks; original member name unknown.
  Array<unknown00f> unknown28;   // Inferred role: limits of the trucks; original member name unknown.
};

static_assert(offsetof(ExtraTruckSlot, unknown00) == 0x00, "");
static_assert(offsetof(ExtraTruckSlot, unknown08) == 0x08, "");
static_assert(offsetof(ExtraTruckSlot, unknown18) == 0x18, "");
static_assert(offsetof(ExtraTruckSlot, unknown28) == 0x28, "");
static_assert(sizeof(ExtraTruckSlot) == 0x38, "");

class ExtraTruckBuffer : public ReferenceObject {
public:
  ExtraTruckBuffer(const Skeleton &skeleton, const ExtraTruckSlot &slot, mm::mtl::IAllocator *pAllocator);
  ~ExtraTruckBuffer() override;

  const Skeleton *unknown18;       // Inferred role: skeleton; original member name unknown.
  const ExtraTruckSlot *unknown20; // Inferred role: slot; original member name unknown.
  mm::mtl::Vector<f32> unknown28;  // Inferred role: truck values; original member name unknown.
};

static_assert(offsetof(ExtraTruckBuffer, unknown18) == 0x18, "");
static_assert(offsetof(ExtraTruckBuffer, unknown20) == 0x20, "");
static_assert(offsetof(ExtraTruckBuffer, unknown28) == 0x28, "");
static_assert(sizeof(ExtraTruckBuffer) == 0x50, "");

} // namespace anm
