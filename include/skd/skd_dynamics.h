#pragma once
#include <stddef.h>

#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {
class Pose;
} // namespace anm

namespace mm {
struct Quat;
struct Vec3;
} // namespace mm

namespace skd {

class Dynamics : public anm::ReferenceObject {
public:
  void update(f32 deltaTime);
  void notifyMovement(const mm::Vec3 &position, const mm::Quat &rotation, const mm::Vec3 &previousPosition, const mm::Quat &previousRotation);
  void resetDynamics();

  u8 _18[0x48 - 0x18];
  anm::Pose *pose;
};

static_assert(offsetof(Dynamics, pose) == 0x48, "");

} // namespace skd
