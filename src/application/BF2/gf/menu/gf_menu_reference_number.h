#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"

namespace gf {

class GfMenuReferenceNumber : public mm::mtl::ReferenceObject {
public:
  int unknown0c; // Inferred role: number; original member name unknown.
  int unknown10; // Inferred role: min; original member name unknown.
  int unknown14; // Inferred role: max; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceNumber, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceNumber, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuReferenceNumber, unknown14) == 0x14, "");

} // namespace gf
