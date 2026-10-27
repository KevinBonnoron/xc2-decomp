#pragma once
#include "types.h"

namespace mm {

// Provenance: the name mm::Vec3NA comes from the mangled game symbols of ptlib::emitter::EmitterObj; it is the 12 byte, unaligned counterpart of Vec3.
struct Vec3NA {
  f32 x;
  f32 y;
  f32 z;
};

static_assert(sizeof(Vec3NA) == 0x0c, "");

} // namespace mm
