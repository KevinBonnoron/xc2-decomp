#include "gf/object/component/pc/field/gf_pc_state_field_wall.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_sound.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWall::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableLookIK(*behavior, false);
  StateUtilField::setWallMoveMode(*behavior, true);
  GfComPropertyPc *property = behavior->getProperty();
  property->unknown310.unknown18 = property->unknown310.unknown003()->unknown20;
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  property->unknownc0 = 0.0f;
  flushWallType(behavior);
}

void StateFieldWall::flushWallType(GfComBehaviorPc *behavior) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComSound *sound = behavior->unknown08->getComponent<GfComSound>();
  if (property->unknown310.unknown10_6) {
    // The game loads the ladder word (ldr w20 at 0x7100559ca8) before the getSoundVariableName call and keeps the
    // branch on its bit after it (tbnz, one call per arm, tails merged): the single-use local places that load
    // (ruling 2026-11-13 #2, P2), the if/else gives the two arms (one expression gives ubfx; 49 vs 45 insns
    // with the name call in each arm).
    bool isLadder = property->unknown310.unknown130.unknown24_7;
    const char *name = getSoundVariableName(SOUND_VARIABLE_UNKNOWN_2);
    if (isLadder) {
      sound->unknown001(name, 1);
    } else {
      sound->unknown001(name, 0);
    }
  }
}

void StateFieldWall::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  flushWallType(behavior);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (!property->unknown310.unknown10_6) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_UNKNOWN_3);
    }
  }
}

} // namespace pc
} // namespace gf
