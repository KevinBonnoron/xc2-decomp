#pragma once
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace skd {

class DynamicsSolver;

class ForceInterface {
public:
  virtual void calcForce(f32 deltaTime, const DynamicsSolver &solver, mm::mtl::Vector<mm::Vec3> *forces) = 0;
};

} // namespace skd
