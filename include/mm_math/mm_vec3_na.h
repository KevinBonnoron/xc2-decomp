#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

// Provenance: the name mm::Vec3NA comes from the mangled game symbols of ptlib::emitter::EmitterObj; it is the 12 byte, unaligned counterpart of Vec3.
struct Vec3NA {
  // Provenance: the static member zero comes from the symbol _ZN2mm6Vec3NA4zeroE.
  static const Vec3NA zero;

  Vec3NA() {}
  Vec3NA(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
  // Evidence: ml::CacheDraw's render*/add* constructors load x and y of the argument with one 64-bit load, z with a 32-bit load, and store
  // stp w,w + str w (renderCube 0x7100700bd4). Only this form gives that code: assigning the three components one by one does not, and
  // initialising them in the mem-initializer list leaves 20 of the 138 functions of CacheDraw different.
  Vec3NA(const Vec3 &vector) : Vec3NA(vector.x, vector.y, vector.z) {}

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
