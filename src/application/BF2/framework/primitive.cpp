#include "framework/primitive.h"

#include <math.h>

namespace fw {

void PrimCapsule::setup(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  set(start, end);
  this->unknown30 = radius;
}

f32 PrimCapsule::getHeight() const {
  f32 x = start.x - end.x;
  f32 y = start.y - end.y;
  f32 z = start.z - end.z;
  return sqrtf(x * x + y * y + z * z);
}

void PrimCapsule::getCenter(mm::Vec3 &center) const {
  center.x = end.x + start.x;
  center.y = end.y + start.y;
  center.z = end.z + start.z;
  center *= 0.5f;
}

bool PrimCapsule::isCollide(const PrimCapsule &capsule) const { return getNearestLength(*this, capsule) <= unknown30 + capsule.unknown30; }

bool PrimCapsule::isCollide(const PrimSphere &sphere) const { return getNearestLength(*this, sphere.unknown00) <= unknown30 + sphere.unknown10; }

PrimCapsule &PrimCapsule::add(const mm::Vec3 &offset) {
  set(start + offset, offset + end);
  return *this;
}

void PrimSphere::setup(const mm::Vec3 &center, f32 radius) {
  this->unknown00 = center;
  this->unknown10 = radius;
}

void PrimSphere::getCenter(mm::Vec3 &center) const { center = this->unknown00; }

bool PrimSphere::isCollide(const PrimSphere &sphere) const {
  f32 distance = sphere.unknown10 + unknown10;
  f32 x = unknown00.x - sphere.unknown00.x;
  f32 y = unknown00.y - sphere.unknown00.y;
  f32 z = unknown00.z - sphere.unknown00.z;
  return x * x + y * y + z * z <= distance * distance;
}

bool PrimSphere::isCollide(const PrimCapsule &capsule) const { return mm::Line2::getNearestLength(capsule, unknown00) <= capsule.unknown30 + unknown10; }

PrimSphere &PrimSphere::add(const mm::Vec3 &offset) {
  unknown00 += offset;
  return *this;
}

} // namespace fw
