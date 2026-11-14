#include "gf/object/component/behavior/mob/gf_mob_state_squad_member.h"

#include <math.h>

#include "fw/fw_update_info.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"

namespace gf {
namespace mob {

bool StateSquadMember::isCondMatch(const GfComBehaviorMob &behavior) { return behavior.isSquadMember(); }

void StateSquadMember::enter(GfComBehaviorMob *behavior, ai::State *previous) {
  unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, "C_move"));
  unknown58 = &StateSquadMember::seqUpdateMove;
  behavior->init(true);
}

void StateSquadMember::leave(GfComBehaviorMob *behavior, ai::State *next) {}

void StateSquadMember::seqUpdateMove(GfComBehaviorMob &behavior, const fw::UpdateInfo &info) {
  if (unknown20.unknown00 != unknown020 && !unknown20.unknown08.empty() && !unknown20.unknown34) {
    return;
  }

  const mm::Vec3 &position = behavior.getPos();
  f32 distance = sqrtf((behavior.unknown110.x - position.x) * (behavior.unknown110.x - position.x) + (behavior.unknown110.z - position.z) * (behavior.unknown110.z - position.z));
  f32 rate;
  if (distance < unknown18) {
    if (!unknown68) {
      unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_idle"));
      unknown58 = &StateSquadMember::seqUpdateIdle;
      behavior.initMoveSpeed(0.5f);
      behavior.init(false);
      return;
    }
    rate = (distance - 0.1f) / unknown18;
    rate = rate < 0.0f ? 0.0f : rate;
  } else if (distance < 1.0f) {
    rate = (distance - unknown18) / (1.0f - unknown18) * (behavior.unknown1e0.unknown08 < 0.000001f ? -1.0f : behavior.unknown1e0.unknown0c / behavior.unknown1e0.unknown08 - 1.0f) + 1.0f;
  } else {
    if (behavior.unknown1e0.unknown08 < 0.000001f) {
      rate = 0.0f;
    } else {
      rate = behavior.unknown1e0.unknown0c / behavior.unknown1e0.unknown08;
    }
  }
  behavior.unknown1e0.setSpeedKmph(rate * behavior.unknown1e0.unknown08, 0.5f);
  behavior.moveToGoal(info.unknown04);
}

void StateSquadMember::seqUpdateIdle(GfComBehaviorMob &behavior, const fw::UpdateInfo &info) {
  const mm::Vec3 &position = behavior.getPos();
  f32 distance = sqrtf((behavior.unknown110.x - position.x) * (behavior.unknown110.x - position.x) + (behavior.unknown110.z - position.z) * (behavior.unknown110.z - position.z));
  if (unknown18 <= distance) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown58 = &StateSquadMember::seqUpdateMove;
    behavior.init(true);
  }
}

} // namespace mob
} // namespace gf
