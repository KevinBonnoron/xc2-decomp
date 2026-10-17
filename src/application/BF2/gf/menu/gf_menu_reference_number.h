#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"

namespace gf {

class GfMenuReferenceNumber : public mm::mtl::ReferenceObject {
public:
  int number;
  int min;
  int max;
};

static_assert(offsetof(GfMenuReferenceNumber, number) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceNumber, min) == 0x10, "");
static_assert(offsetof(GfMenuReferenceNumber, max) == 0x14, "");

} // namespace gf
