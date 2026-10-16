#pragma once
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace btl {

class ShakeCameraElement;

class ShakeCameraManager {
public:
  ShakeCameraManager();
  virtual ~ShakeCameraManager();
  void DeleteAllData();
  void RegisterData(ShakeCameraElement *element);
  void Update(const fw::UpdateInfo &updateInfo);
  void ApplyShake(mm::Vec3 &position, mm::Vec3 &target);

  mm::mtl::FixedVector<ShakeCameraElement *, 20> elements;
  bool isStopEternalShake;
};

static_assert(offsetof(ShakeCameraManager, elements) == 0x08, "");
static_assert(offsetof(ShakeCameraManager, isStopEternalShake) == 0xb0, "");
static_assert(sizeof(ShakeCameraManager) == 0xb8, "");

class ShakeCameraElement {
public:
  ShakeCameraElement();
  virtual ~ShakeCameraElement() {}
  bool ProgressShakeCounter(f32 time);
  virtual void StopEternalShake() {}
  virtual bool Update(f32 time) = 0;
  virtual void CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) = 0;

  int type;
  f32 power;
  f32 interval;
  f32 counter;
  bool isFrameTime;
};

static_assert(offsetof(ShakeCameraElement, type) == 0x08, "");
static_assert(offsetof(ShakeCameraElement, power) == 0x0c, "");
static_assert(offsetof(ShakeCameraElement, interval) == 0x10, "");
static_assert(offsetof(ShakeCameraElement, counter) == 0x14, "");
static_assert(offsetof(ShakeCameraElement, isFrameTime) == 0x18, "");

class ShakeCameraElementRandom : public ShakeCameraElement {
public:
  enum PHASE {
    PHASE_FADE_IN,
    PHASE_KEEP,
    PHASE_FADE_OUT,
  };

  ShakeCameraElementRandom();
  void StopEternalShake() override;
  bool Update(f32 time) override;
  void CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) override;

  mm::Vec3 previousShift;
  mm::Vec3 nextShift;
  f32 fadeInTime;
  f32 keepTime;
  f32 fadeOutTime;
  int phase;
  f32 phaseTime;
  bool isVertical;
  bool isStarted;
};

static_assert(offsetof(ShakeCameraElementRandom, previousShift) == 0x20, "");
static_assert(offsetof(ShakeCameraElementRandom, nextShift) == 0x30, "");
static_assert(offsetof(ShakeCameraElementRandom, fadeInTime) == 0x40, "");
static_assert(offsetof(ShakeCameraElementRandom, keepTime) == 0x44, "");
static_assert(offsetof(ShakeCameraElementRandom, fadeOutTime) == 0x48, "");
static_assert(offsetof(ShakeCameraElementRandom, phase) == 0x4c, "");
static_assert(offsetof(ShakeCameraElementRandom, phaseTime) == 0x50, "");
static_assert(offsetof(ShakeCameraElementRandom, isVertical) == 0x54, "");
static_assert(offsetof(ShakeCameraElementRandom, isStarted) == 0x55, "");
static_assert(sizeof(ShakeCameraElementRandom) == 0x60, "");

class ShakeCameraElementAxis : public ShakeCameraElement {
public:
  ShakeCameraElementAxis();
  bool Update(f32 time) override;
  void CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) override;

  mm::Vec3 axis;
  int loopCount;
  int fadeOutLoopCount;
  int loop;
  int phase;
  bool isBothSides;
};

static_assert(offsetof(ShakeCameraElementAxis, axis) == 0x20, "");
static_assert(offsetof(ShakeCameraElementAxis, loopCount) == 0x30, "");
static_assert(offsetof(ShakeCameraElementAxis, fadeOutLoopCount) == 0x34, "");
static_assert(offsetof(ShakeCameraElementAxis, loop) == 0x38, "");
static_assert(offsetof(ShakeCameraElementAxis, phase) == 0x3c, "");
static_assert(offsetof(ShakeCameraElementAxis, isBothSides) == 0x40, "");
static_assert(sizeof(ShakeCameraElementAxis) == 0x50, "");

class ShakeCameraElementCameraAxis : public ShakeCameraElementAxis {
public:
  enum SHAKE_AXIS {
    SHAKE_AXIS_RIGHT,
    SHAKE_AXIS_LEFT,
    SHAKE_AXIS_UP,
    SHAKE_AXIS_DOWN,
    SHAKE_AXIS_FRONT,
    SHAKE_AXIS_BACK,
  };

  void SetData(SHAKE_AXIS shakeAxis, int loopCount, int fadeOutLoopCount, bool isBothSides);
  void CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) override;

  SHAKE_AXIS shakeAxis;
  bool isReverse;
};

static_assert(offsetof(ShakeCameraElementCameraAxis, shakeAxis) == 0x44, "");
static_assert(offsetof(ShakeCameraElementCameraAxis, isReverse) == 0x48, "");
static_assert(sizeof(ShakeCameraElementCameraAxis) == 0x50, "");

} // namespace btl
