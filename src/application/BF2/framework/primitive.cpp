#include "framework/primitive.h"

#include <math.h>

namespace fw {

void PrimCapsule::setup(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  set(start, end);
  this->radius = radius;
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

bool PrimCapsule::isCollide(const PrimCapsule &capsule) const { return getNearestLength(*this, capsule) <= radius + capsule.radius; }

bool PrimCapsule::isCollide(const PrimSphere &sphere) const { return getNearestLength(*this, sphere.center) <= radius + sphere.radius; }

PrimCapsule &PrimCapsule::add(const mm::Vec3 &offset) {
  set(start + offset, offset + end);
  return *this;
}

void PrimSphere::setup(const mm::Vec3 &center, f32 radius) {
  this->center = center;
  this->radius = radius;
}

void PrimSphere::getCenter(mm::Vec3 &center) const { center = this->center; }

bool PrimSphere::isCollide(const PrimSphere &sphere) const {
  f32 distance = sphere.radius + radius;
  f32 x = center.x - sphere.center.x;
  f32 y = center.y - sphere.center.y;
  f32 z = center.z - sphere.center.z;
  return x * x + y * y + z * z <= distance * distance;
}

bool PrimSphere::isCollide(const PrimCapsule &capsule) const { return mm::Line2::getNearestLength(capsule, center) <= capsule.radius + radius; }

PrimSphere &PrimSphere::add(const mm::Vec3 &offset) {
  center += offset;
  return *this;
}

} // namespace fw
