#include "battle/effect/effect_move_component.h"

#include "battle/battle_global.h"
#include "battle/misc_battle.h"
#include "fw/fw_update_info.h"

namespace btl {

void (EffectMoveComponent::*const EffectMoveComponent::m_apUpdateFuncList[])(f32, f32, const mm::Vec3 &) = {
    &EffectMoveComponent::UpdateNormal,
    &EffectMoveComponent::UpdateNormal,
    &EffectMoveComponent::UpdateHoming,
    &EffectMoveComponent::UpdateBounce,
    &EffectMoveComponent::UpdateLinkObj,
    &EffectMoveComponent::UpdateUp,
};

EffectMoveComponent::EffectMoveComponent() { Initialize(); }

void EffectMoveComponent::Initialize() {
  move = mm::Vec3::zero;
  direction = mm::Vec3::zero;
  time = 0.0f;
  moveType = MOVE_TYPE_NONE;
}

void EffectMoveComponent::SetGravity(f32 gravity) { this->gravity = gravity * 0.5f; }

void EffectMoveComponent::UpdateNormal(f32 time, f32 frame, const mm::Vec3 &) {
  f32 moveSpeed = speed * speedRate * frame;
  mm::Vec3 velocity;
  velocity.x = direction.x * moveSpeed;
  velocity.y = moveSpeed * direction.y;
  velocity.z = moveSpeed * direction.z;
  distance += moveSpeed;
  distanceXZ += Misc::CalcLengthXZ(velocity);
  if (gravity != 0.0f) {
    f32 previous = gravityTime;
    gravityTime += time;
    velocity.y -= gravity * (gravityTime * gravityTime - previous * previous);
  }
  move = velocity;

  if (accel != 0.0f) {
    if (accelTime < accelDelay) {
      accelTime += frame;
    } else {
      f32 nextSpeed = accel * frame + speed;
      bool isAccel = accel > 0.0f ? nextSpeed < speedMax : nextSpeed > speedMax;
      speed = isAccel ? nextSpeed : speedMax;
    }
  }
}

void EffectMoveComponent::UpdateBounce(f32, f32, const mm::Vec3 &) {}

void EffectMoveComponent::UpdateUp(f32, f32 frame, const mm::Vec3 &) {
  f32 rate;
  if (up.time <= frame) {
    rate = up.time / frame;
    up.time = 0.0f;
  } else {
    rate = frame;
    up.time -= frame;
  }
  move.x = 0.0f;
  move.z = 0.0f;
  move.y += rate * speed;
}

void EffectMoveComponent::Update(const fw::UpdateInfo &updateInfo, const mm::Vec3 &position) {
  if (moveType != MOVE_TYPE_NONE) {
    f32 deltaTime = updateInfo.deltaTime;
    f32 frame = deltaTime * FRAME_RATE;
    time += deltaTime;
    (this->*m_apUpdateFuncList[moveType - 1])(deltaTime, frame, position);
  }
}

} // namespace btl
