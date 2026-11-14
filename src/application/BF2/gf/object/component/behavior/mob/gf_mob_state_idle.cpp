#include "gf/object/component/behavior/mob/gf_mob_state_idle.h"

#include <string.h>

#include "framework/object/updatable_object.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior_mob.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixstr.h"

namespace gf {
namespace mob {

void StateIdle::enter(GfComBehaviorMob *behavior, ai::State *previous) {
  if (previous != nullptr) {
    execEndSchedule(*behavior);
  }

  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const char *stateName = nullptr;
  if (comAsm != nullptr) {
    stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
  }

  GfObjSetupMob *setup = GfObjUtil::getObjSetup<GfObjSetupMob>(static_cast<GfObj *>(behavior->unknown08)->unknownf8);
  if (stateName == nullptr || strcmp(setup->unknown6c.c_str(), stateName) != 0) {
    mm::mtl::FixStr<32> command(setup->unknown6c);
    command.unknown002(0) = 'C';
    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, command.c_str()));
  }
}

void StateIdle::leave(GfComBehaviorMob *behavior, ai::State *next) { execEndSchedule(*behavior); }

} // namespace mob
} // namespace gf
