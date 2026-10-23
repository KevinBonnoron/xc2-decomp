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

  mm::mtl::FixedVector<ShakeCameraElement *, 20> unknown08; // Inferred role: elements; original member name unknown.
  bool unknownb0;                                           // Inferred role: stop eternal shake; original member name unknown.
};

static_assert(offsetof(ShakeCameraManager, unknown08) == 0x08, "");
static_assert(offsetof(ShakeCameraManager, unknownb0) == 0xb0, "");
static_assert(sizeof(ShakeCameraManager) == 0xb8, "");

class ShakeCameraElement {
public:
  ShakeCameraElement();
  virtual ~ShakeCameraElement() {}
  bool ProgressShakeCounter(f32 time);
  virtual void StopEternalShake() {}
  virtual bool Update(f32 time) = 0;
  virtual void CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) = 0;

  int unknown08;  // Inferred role: type; original member name unknown.
  f32 unknown0c;  // Inferred role: power; original member name unknown.
  f32 unknown10;  // Inferred role: interval; original member name unknown.
  f32 unknown14;  // Inferred role: counter; original member name unknown.
  bool unknown18; // Inferred role: frame time; original member name unknown.
};

static_assert(offsetof(ShakeCameraElement, unknown08) == 0x08, "");
static_assert(offsetof(ShakeCameraElement, unknown0c) == 0x0c, "");
static_assert(offsetof(ShakeCameraElement, unknown10) == 0x10, "");
static_assert(offsetof(ShakeCameraElement, unknown14) == 0x14, "");
static_assert(offsetof(ShakeCameraElement, unknown18) == 0x18, "");

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

  mm::Vec3 unknown20; // Inferred role: previous shift; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: next shift; original member name unknown.
  f32 unknown40;      // Inferred role: fade in time; original member name unknown.
  f32 unknown44;      // Inferred role: keep time; original member name unknown.
  f32 unknown48;      // Inferred role: fade out time; original member name unknown.
  int unknown4c;      // Inferred role: phase; original member name unknown.
  f32 unknown50;      // Inferred role: phase time; original member name unknown.
  bool unknown54;     // Inferred role: vertical; original member name unknown.
  bool unknown55;     // Inferred role: started; original member name unknown.
};

static_assert(offsetof(ShakeCameraElementRandom, unknown20) == 0x20, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown30) == 0x30, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown40) == 0x40, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown44) == 0x44, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown48) == 0x48, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown4c) == 0x4c, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown50) == 0x50, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown54) == 0x54, "");
static_assert(offsetof(ShakeCameraElementRandom, unknown55) == 0x55, "");
static_assert(sizeof(ShakeCameraElementRandom) == 0x60, "");

class ShakeCameraElementAxis : public ShakeCameraElement {
public:
  ShakeCameraElementAxis();
  bool Update(f32 time) override;
  void CalcShift(const mm::Vec3 &position, const mm::Vec3 &target, mm::Vec3 &positionShift, mm::Vec3 &targetShift) override;

  mm::Vec3 unknown20; // Inferred role: axis; original member name unknown.
  int unknown30;      // Inferred role: loop count; original member name unknown.
  int unknown34;      // Inferred role: fade out loop count; original member name unknown.
  int unknown38;      // Inferred role: loop; original member name unknown.
  int unknown3c;      // Inferred role: phase; original member name unknown.
  bool unknown40;     // Inferred role: both sides; original member name unknown.
};

static_assert(offsetof(ShakeCameraElementAxis, unknown20) == 0x20, "");
static_assert(offsetof(ShakeCameraElementAxis, unknown30) == 0x30, "");
static_assert(offsetof(ShakeCameraElementAxis, unknown34) == 0x34, "");
static_assert(offsetof(ShakeCameraElementAxis, unknown38) == 0x38, "");
static_assert(offsetof(ShakeCameraElementAxis, unknown3c) == 0x3c, "");
static_assert(offsetof(ShakeCameraElementAxis, unknown40) == 0x40, "");
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

  SHAKE_AXIS unknown44; // Inferred role: shake axis; original member name unknown.
  bool unknown48;       // Inferred role: reverse; original member name unknown.
};

static_assert(offsetof(ShakeCameraElementCameraAxis, unknown44) == 0x44, "");
static_assert(offsetof(ShakeCameraElementCameraAxis, unknown48) == 0x48, "");
static_assert(sizeof(ShakeCameraElementCameraAxis) == 0x50, "");

} // namespace btl
