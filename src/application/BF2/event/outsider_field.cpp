#include "event/outsider_field.h"

namespace event {

OutsiderField::OutsiderField() { clear(); }

void OutsiderField::clear() {
  mType = TYPE_CIRCLE;
  mDefinePos = mm::Vec3::zero;
  mDefineRadius = 0.0f;
  mPos = mm::Vec3::zero;
  mRadius = 0.0f;
}

void OutsiderField::setField(TYPE type, const mm::Vec3 &pos, f32 radius) {
  mType = type;
  mDefinePos = pos;
  mDefineRadius = radius;
}

bool OutsiderField::isInside(const mm::Vec3 &pos) const {
  if (mType < TYPE_CIRCLE) {
    return false;
  }
  if (mRadius <= 0.0f) {
    return false;
  }
  f32 distanceX = mPos.x - pos.x;
  f32 distanceZ = mPos.z - pos.z;
  f32 squaredX = distanceX * distanceX;
  f32 squaredZ = distanceZ * distanceZ;
  f32 squaredRadius = mRadius * mRadius;
  return squaredX + squaredZ < squaredRadius;
}

} // namespace event
