#pragma once
#include "ptlib/particle_intrusive_list.h"

namespace ptlib {

struct FxHeader;

namespace emitter {

class EmitterSetNode : public IntrusiveListNode {
public:
  virtual ~EmitterSetNode() {}

  FxHeader *unknown18; // Inferred role: effect header; original member name unknown.
};

static_assert(sizeof(EmitterSetNode) == 0x20, "");

} // namespace emitter
} // namespace ptlib
