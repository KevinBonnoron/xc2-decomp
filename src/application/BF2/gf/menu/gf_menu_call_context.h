#pragma once
#include "mm_mtl/reference_object.h"

namespace gf {

class GfMenuCallContext : public mm::mtl::ReferenceObject {
public:
  static GfMenuCallContext *create();
  bool isTerm() const;
  void reset();
};

} // namespace gf
