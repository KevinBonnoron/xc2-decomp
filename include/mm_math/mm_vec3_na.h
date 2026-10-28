#pragma once
#include "types.h"

namespace mm {

// Provenance: the name mm::Vec3NA comes from the mangled game symbols of ptlib::emitter::EmitterObj; it is the 12 byte, unaligned counterpart of Vec3.
struct Vec3NA {
  // Provenance: the static member zero comes from the symbol _ZN2mm6Vec3NA4zeroE.
  static const Vec3NA zero;

  Vec3NA &operator=(const Vec3NA &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
  }

  f32 x;
  f32 y;
  f32 z;
};

static_assert(sizeof(Vec3NA) == 0x0c, "");

} // namespace mm
