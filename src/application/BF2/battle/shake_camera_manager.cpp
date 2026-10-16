#include "battle/shake_camera_manager.h"

#include <math.h>

#include "battle/misc_battle.h"

namespace btl {

constexpr f32 PI = 3.14159265f;

ShakeCameraManager::ShakeCameraManager() : isStopEternalShake(false) {}

ShakeCameraManager::~ShakeCameraManager() { DeleteAllData(); }

void ShakeCameraManager::DeleteAllData() {
  for (ShakeCameraElement *element : elements) {
    delete element;
  }
  elements.clear();
}

void ShakeCameraManager::RegisterData(ShakeCameraElement *element) {
  if (elements.size() == elements.capacity()) {
    ShakeCameraElement *oldest = *elements.begin();
    elements.erase(elements.begin());
    delete oldest;
  }
  elements.push_back(element);
}

ShakeCameraElement::ShakeCameraElement() : type(0), interval(0.0f), counter(0.0f), isFrameTime(true) {}

bool ShakeCameraElement::ProgressShakeCounter(f32 time) {
  f32 total = counter + time;
  if (total >= interval) {
    counter = total - interval;
    return true;
  }

  counter = total;
  return false;
}

ShakeCameraElementRandom::ShakeCameraElementRandom() : phase(PHASE_FADE_IN), phaseTime(0.0f), isVertical(false), isStarted(false) {
  previousShift = mm::Vec3::zero;
  nextShift = mm::Vec3::zero;
}

void ShakeCameraElementRandom::StopEternalShake() {
  if (keepTime < 0.0f) {
    keepTime = 0.0f;
  }
}

ShakeCameraElementAxis::ShakeCameraElementAxis() : axis(), loopCount(0), loop(0), phase(0), isBothSides(false) {}

bool ShakeCameraElementAxis::Update(f32 time) {
  if (!ProgressShakeCounter(time)) {
    return false;
  }

  loop++;
  if (loop < loopCount) {
    return false;
  }

  if (phase == 0 && fadeOutLoopCount > 0) {
    loop = 0;
    phase = 1;
    return false;
  }

  return true;
}

void ShakeCameraElementAxis::CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) {
  f32 shift = power;
  f32 period = interval;
  f32 time = counter;
  f32 angle = time / period * (PI * 2.0f);
  if (!isBothSides) {
    angle += PI * 1.5f;
  }
  f32 wave = sinf(angle);
  if (!isBothSides) {
    wave = (wave + 1.0f) * 0.5f;
  }
  shift *= wave;
  if (phase == 1) {
    shift *= 1.0f - powf((time + period * loop) / (period * fadeOutLoopCount), 0.75f);
  }

  switch (type) {
  case 0: {
    mm::Vec3 vector(shift * axis.x, shift * axis.y, shift * axis.z);
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
    Misc::TurnDirectionAngle(direction, axis, shift, true);
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
  axis = mm::Vec3::zero;
  this->loopCount = loopCount;
  this->fadeOutLoopCount = fadeOutLoopCount;
  this->isBothSides = isBothSides;
  this->shakeAxis = shakeAxis;
  switch (shakeAxis) {
  case SHAKE_AXIS_LEFT:
  case SHAKE_AXIS_DOWN:
  case SHAKE_AXIS_BACK:
    isReverse = true;
    break;
  default:
    isReverse = false;
    break;
  }
}

} // namespace btl
