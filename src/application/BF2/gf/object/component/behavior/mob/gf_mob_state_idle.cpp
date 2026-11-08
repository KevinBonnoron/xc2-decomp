#include "gf/object/component/behavior/mob/gf_mob_state_idle.h"

#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/behavior/gf_com_behavior_mob.h"

namespace gf {
namespace mob {

void StateIdle::leave(GfComBehaviorMob *behavior, ai::State *next) { execEndSchedule(*behavior); }

} // namespace mob
} // namespace gf
