#include "framework/primitive.h"

#include <math.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"

namespace fw {

void PrimCapsule::setup(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  set(start, end);
  this->unknown30 = radius;
}

void PrimCapsule::setup(const mm::Vec3 &position, const mm::Quat &rotation, f32 length, f32 radius) {
  mm::Vec3 start(0.0f, 0.0f, length * 0.5f);
  mm::Vec3 end(0.0f, 0.0f, length * -0.5f);
  start = rotation.rotate(start);
  end = rotation.rotate(end);
  set(position + start, position + end);
  this->unknown30 = radius;
}

void PrimCapsule::setup(const mm::Mat44 &matrix, f32 length, f32 radius) {
  mm::Quat rotation;
  mm::unknown004(rotation, matrix);
  mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
  setup(position, rotation, length, radius);
}

f32 PrimCapsule::getHeight() const {
  f32 x = start.x - end.x;
  f32 y = start.y - end.y;
  f32 z = start.z - end.z;
  return sqrtf(x * x + y * y + z * z);
}

void PrimCapsule::getRot(mm::Quat &rotation) const {
  const mm::Vec3 &axis = mm::Vec3::unitY;
  f32 dot = axis.x * direction.x + axis.y * direction.y + axis.z * direction.z;
  if (!(dot < -0.9999f)) {
    f32 x = axis.y * direction.z - direction.y * axis.z;
    f32 y = direction.x * axis.z - axis.x * direction.z;
    f32 z = axis.x * direction.y - direction.x * axis.y;
    f32 value = dot + 1.0f;
    value = value + value;
    f32 length = sqrtf(value);
    f32 scale = 1.0f / length;
    rotation.x = x * scale;
    rotation.y = y * scale;
    rotation.z = z * scale;
    rotation.w = length * 0.5f;
  } else {
    rotation.x = 0.0f;
    rotation.y = 1.0f;
    rotation.z = 0.0f;
    rotation.w = 0.0f;
  }
}

void PrimCapsule::getCenter(mm::Vec3 &center) const {
  center.x = end.x + start.x;
  center.y = end.y + start.y;
  center.z = end.z + start.z;
  center *= 0.5f;
}

void PrimCapsule::getMat(mm::Mat44 &matrix) const {
  mm::Quat rotation;
  getRot(rotation);
  mm::Vec3 center;
  getCenter(center);
  mm::unknown001(matrix, rotation);
  matrix.setTrans(center);
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
