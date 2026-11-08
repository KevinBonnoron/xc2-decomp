#pragma once
#include <stddef.h>

#include "gf/gf_allocator.h"
#include "mm_mtl/reference_object.h"

namespace gf {

class GfMenuReferenceNumber : public mm::mtl::ReferenceObject {
public:
  GfMenuReferenceNumber() : unknown0c(0), unknown10(0), unknown14(9999) {}

  int unknown0c; // Inferred role: number; original member name unknown.
  int unknown10; // Inferred role: min; original member name unknown.
  int unknown14; // Inferred role: max; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceNumber, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceNumber, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuReferenceNumber, unknown14) == 0x14, "");

// Inferred helper: allocates a reference number; original name unknown.
// __LINE__ must be 46 as in the original header: it is the line argument of operator new.
#line 46
inline GfMenuReferenceNumber *unknown160() { return new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuReferenceNumber(); }

} // namespace gf
