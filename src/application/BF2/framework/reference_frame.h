#pragma once
#include "mm_mtl/reference_object.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace fw {

class ReferenceFrame : public mm::mtl::ReferenceObject {
public:
  const mm::Mat44 &getSyncedWorldMatrix();
};

} // namespace fw
