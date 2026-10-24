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
  unknown40 = mm::Vec3::zero;
  unknown50 = mm::Vec3::zero;
  unknown60 = 0.0f;
  unknowna5 = MOVE_TYPE_NONE;
}

void EffectMoveComponent::SetGravity(f32 gravity) { this->unknown84 = gravity * 0.5f; }

void EffectMoveComponent::UpdateNormal(f32 time, f32 frame, const mm::Vec3 &) {
  f32 moveSpeed = unknown6c * unknown74 * frame;
  mm::Vec3 velocity;
  velocity.x = unknown50.x * moveSpeed;
  velocity.y = moveSpeed * unknown50.y;
  velocity.z = moveSpeed * unknown50.z;
  unknown64 += moveSpeed;
  unknown68 += Misc::CalcLengthXZ(velocity);
  if (unknown84 != 0.0f) {
    f32 previous = unknown88;
    unknown88 += time;
    velocity.y -= unknown84 * (unknown88 * unknown88 - previous * previous);
  }
  unknown40 = velocity;

  if (unknown78 != 0.0f) {
    if (unknown80 < unknown7c) {
      unknown80 += frame;
    } else {
      f32 nextSpeed = unknown78 * frame + unknown6c;
      bool isAccel = unknown78 > 0.0f ? nextSpeed < unknown70 : nextSpeed > unknown70;
      unknown6c = isAccel ? nextSpeed : unknown70;
    }
  }
}

void EffectMoveComponent::UpdateBounce(f32, f32, const mm::Vec3 &) {}

void EffectMoveComponent::UpdateUp(f32, f32 frame, const mm::Vec3 &) {
  f32 rate;
  if (unknown00_2.unknown00 <= frame) {
    rate = unknown00_2.unknown00 / frame;
    unknown00_2.unknown00 = 0.0f;
  } else {
    rate = frame;
    unknown00_2.unknown00 -= frame;
  }
  unknown40.x = 0.0f;
  unknown40.z = 0.0f;
  unknown40.y += rate * unknown6c;
}

void EffectMoveComponent::Update(const fw::UpdateInfo &updateInfo, const mm::Vec3 &position) {
  if (unknowna5 != MOVE_TYPE_NONE) {
    f32 deltaTime = updateInfo.unknown04;
    f32 frame = deltaTime * FRAME_RATE;
    unknown60 += deltaTime;
    (this->*m_apUpdateFuncList[unknowna5 - 1])(deltaTime, frame, position);
  }
}

} // namespace btl
