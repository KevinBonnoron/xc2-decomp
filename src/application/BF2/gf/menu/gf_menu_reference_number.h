#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"

namespace gf {

class GfMenuReferenceNumber : public mm::mtl::ReferenceObject {
public:
  int number;
};

static_assert(offsetof(GfMenuReferenceNumber, number) == 0x0c, "");

} // namespace gf
