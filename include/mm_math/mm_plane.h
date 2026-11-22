#pragma once
#include <math.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Plane {
  Plane() {}
  // Normalizes the normal: BlackBoardField::BlackBoardField (1.0.0: 0x7100542c94) normalizes Vec3::unitY in the
  // member initialization of its wall plane, before the stores of the following members.
  Plane(const Vec3 &direction, f32 offset) { unknown002(direction, offset); }

  // Inferred role: normalizes the normal, zero when it is too short; original name unknown.
  void unknown001() {
    f32 length = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length <= 0.000001f) {
      normal = Vec3::zero;
    } else {
      f32 scale = 1.0f / length;
      normal.x = normal.x * scale;
      normal.y = normal.y * scale;
      normal.z = normal.z * scale;
    }
  }

  // Inferred role: sets the plane from a normal, normalized, and a distance; original name unknown.
  void unknown002(const Vec3 &direction, f32 offset) {
    normal = direction;
    unknown001();
    distance = offset;
  }

  // Parameter order from the order of the bounds checks of the two inlined accessors at the call in GfComEnvSensor::flushGroundSingle (1.0.0: 0x710051c77c): the check of the position
  // (the pointer that the dot product uses, in x28) comes first, then the one of the normal (0x710051c8c0, 0x710051c900). The other users (GfInfo::initialize, the constructors of
  // GroundInfo and GfEnvProperty::unknown002) pass constants, which show no order; the game has no symbol for the function (always inlined).
  void set(const Vec3 &position, const Vec3 &direction) {
    normal = direction;
    unknown001();
    distance = -(normal.x * position.x + normal.y * position.y + normal.z * position.z);
  }

  Vec3 normal;
  f32 distance;
};

static_assert(sizeof(Plane) == 0x20, "");

} // namespace mm
