#include "battle/shake_camera_manager.h"

#include <math.h>

#include "battle/misc_battle.h"

namespace btl {

constexpr f32 PI = 3.14159265f;

ShakeCameraManager::ShakeCameraManager() : unknownb0(false) {}

ShakeCameraManager::~ShakeCameraManager() { DeleteAllData(); }

void ShakeCameraManager::DeleteAllData() {
  for (ShakeCameraElement *element : unknown08) {
    delete element;
  }
  unknown08.clear();
}

void ShakeCameraManager::RegisterData(ShakeCameraElement *element) {
  if (unknown08.size() == unknown08.capacity()) {
    ShakeCameraElement *oldest = *unknown08.begin();
    unknown08.erase(unknown08.begin());
    delete oldest;
  }
  unknown08.push_back(element);
}

ShakeCameraElement::ShakeCameraElement() : unknown08(0), unknown10(0.0f), unknown14(0.0f), unknown18(true) {}

bool ShakeCameraElement::ProgressShakeCounter(f32 time) {
  f32 total = unknown14 + time;
  if (total >= unknown10) {
    unknown14 = total - unknown10;
    return true;
  }

  unknown14 = total;
  return false;
}

ShakeCameraElementRandom::ShakeCameraElementRandom() : unknown4c(PHASE_FADE_IN), unknown50(0.0f), unknown54(false), unknown55(false) {
  unknown20 = mm::Vec3::zero;
  unknown30 = mm::Vec3::zero;
}

void ShakeCameraElementRandom::StopEternalShake() {
  if (unknown44 < 0.0f) {
    unknown44 = 0.0f;
  }
}

ShakeCameraElementAxis::ShakeCameraElementAxis() : unknown20(), unknown30(0), unknown38(0), unknown3c(0), unknown40(false) {}

bool ShakeCameraElementAxis::Update(f32 time) {
  if (!ProgressShakeCounter(time)) {
    return false;
  }

  unknown38++;
  if (unknown38 < unknown30) {
    return false;
  }

  if (unknown3c == 0 && unknown34 > 0) {
    unknown38 = 0;
    unknown3c = 1;
    return false;
  }

  return true;
}

void ShakeCameraElementAxis::CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) {
  f32 shift = unknown0c;
  f32 period = unknown10;
  f32 time = unknown14;
  f32 angle = time / period * (PI * 2.0f);
  if (!unknown40) {
    angle += PI * 1.5f;
  }
  f32 wave = sinf(angle);
  if (!unknown40) {
    wave = (wave + 1.0f) * 0.5f;
  }
  shift *= wave;
  if (unknown3c == 1) {
    shift *= 1.0f - powf((time + period * unknown38) / (period * unknown34), 0.75f);
  }

  switch (unknown08) {
  case 0: {
    mm::Vec3 vector(shift * unknown20.x, shift * unknown20.y, shift * unknown20.z);
    positionShift = vector;
    targetShift = vector;
    break;
  }
  case 1: {
    positionShift = mm::Vec3::zero;
    mm::Vec3 forward;
    forward.x = target.x - position.x;
    forward.y = target.y - position.y;
    forward.z = target.z - position.z;
    Misc::Normalize(forward);
    mm::Vec3 direction = forward;
    Misc::TurnDirectionAngle(direction, unknown20, shift, true);
    f32 x = position.x - target.x;
    f32 y = position.y - target.y;
    f32 z = position.z - target.z;
    f32 length = sqrtf(x * x + y * y + z * z);
    mm::Vec3 shiftedTarget(length * direction.x, length * direction.y, length * direction.z);
    shiftedTarget += position;
    targetShift.x = shiftedTarget.x - target.x;
    targetShift.y = shiftedTarget.y - target.y;
    targetShift.z = shiftedTarget.z - target.z;
    break;
  }
  case 2:
    break;
  default:
    positionShift = mm::Vec3::zero;
    targetShift = mm::Vec3::zero;
    break;
  }
}

void ShakeCameraElementCameraAxis::SetData(SHAKE_AXIS shakeAxis, int loopCount, int fadeOutLoopCount, bool isBothSides) {
  unknown20 = mm::Vec3::zero;
  this->unknown30 = loopCount;
  this->unknown34 = fadeOutLoopCount;
  this->unknown40 = isBothSides;
  this->unknown44 = shakeAxis;
  switch (shakeAxis) {
  case SHAKE_AXIS_LEFT:
  case SHAKE_AXIS_DOWN:
  case SHAKE_AXIS_BACK:
    unknown48 = true;
    break;
  default:
    unknown48 = false;
    break;
  }
}

} // namespace btl
