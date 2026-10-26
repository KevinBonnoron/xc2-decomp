#pragma once

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {

class Raycaster {
public:
  virtual ~Raycaster() {}
  virtual bool castRay(const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 *position, mm::Vec3 *normal);
};

} // namespace fw
