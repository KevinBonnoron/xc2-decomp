#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class EffectMoveComponent {
public:
  enum MOVE_TYPE {
    MOVE_TYPE_NONE,
    MOVE_TYPE_NORMAL,
    MOVE_TYPE_PARABOLA,
    MOVE_TYPE_HOMING,
    MOVE_TYPE_BOUNCE,
    MOVE_TYPE_LINK_OBJ,
    MOVE_TYPE_UP,
  };

  struct MOVE_PARAM;

  EffectMoveComponent();
  void Initialize();
  void Initialize(const MOVE_PARAM &param);
  f32 CalcFakeGravity(const mm::Vec3 &position, const mm::Vec3 &target, f32 time) const;
  void SetGravity(f32 gravity);
  bool IsEnd(const mm::Vec3 &previous, mm::Vec3 &position, f32 time) const;
  void UpdateNormal(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateHoming(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateBounce(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateLinkObj(f32 time, f32 frame, const mm::Vec3 &position);
  void UpdateUp(f32 time, f32 frame, const mm::Vec3 &position);
  void Update(const fw::UpdateInfo &updateInfo, const mm::Vec3 &position);

  static void (EffectMoveComponent::*const m_apUpdateFuncList[])(f32 time, f32 frame, const mm::Vec3 &position);

  union {
    struct {
      gf::GF_OBJ_HANDLE *handle;
      f32 targetX;
      f32 targetY;
      f32 targetZ;
      f32 wayX;
      f32 wayY;
      f32 wayZ;
      f32 startTime;
      f32 time;
      f32 waitTime;
      f32 wayTime;
      f32 turnSpeed;
      f32 turnSpeedMax;
      f32 turnAccel;
      bool isFar;
    } homing;
    struct {
      gf::GF_OBJ_HANDLE *handle;
      const char *bone;
      f32 time;
    } linkObj;
    struct {
      f32 time;
    } up;
  };
  mm::Vec3 move;
  mm::Vec3 direction;
  f32 time;
  f32 distance;
  f32 distanceXZ;
  f32 speed;
  f32 speedMax;
  f32 speedRate;
  f32 accel;
  f32 accelDelay;
  f32 accelTime;
  f32 gravity;
  f32 gravityTime;
  f32 endParams[6];
  u8 endFlags;
  u8 moveType;
};

static_assert(offsetof(EffectMoveComponent, homing.turnAccel) == 0x38, "");
static_assert(offsetof(EffectMoveComponent, homing.isFar) == 0x3c, "");
static_assert(offsetof(EffectMoveComponent, move) == 0x40, "");
static_assert(offsetof(EffectMoveComponent, direction) == 0x50, "");
static_assert(offsetof(EffectMoveComponent, time) == 0x60, "");
static_assert(offsetof(EffectMoveComponent, speed) == 0x6c, "");
static_assert(offsetof(EffectMoveComponent, gravity) == 0x84, "");
static_assert(offsetof(EffectMoveComponent, endParams) == 0x8c, "");
static_assert(offsetof(EffectMoveComponent, endFlags) == 0xa4, "");
static_assert(offsetof(EffectMoveComponent, moveType) == 0xa5, "");
static_assert(sizeof(EffectMoveComponent) == 0xb0, "");

} // namespace btl
