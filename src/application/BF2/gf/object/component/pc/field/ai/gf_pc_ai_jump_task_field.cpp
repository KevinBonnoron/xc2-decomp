#include "gf/object/component/pc/field/ai/gf_pc_ai_jump_task_field.h"

#include <math.h>

#include "fw/fw_param_manager.h"
#include "gf/game/gf_game_inside_battle_lock.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "types.h"

namespace gf {
namespace pc {

bool TaskFieldJump::testCondition(const BlackBoardField &blackBoard) {
  if (blackBoard.unknown200.test(1) && blackBoard.unknown200.test(2)) {
    return !GfGameInsideBattleLock::get()->unknown20;
  }
  return false;
}

void TaskFieldJump::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  const JumpAIParam *param = AgentUtilField::getAIParamAdapter(*property, PARAM_ID_FIELD_AI_UNKNOWN_4).get<JumpAIParam>();
  const mm::Vec3 &velocity = property->unknown80;
  property->unknown60.unknown08.set(INPUT_ID_UNKNOWN_2);
  f32 speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
  property->unknown80 = property->unknown1e0 * (speed > param->minVel ? speed : param->minVel);
}

} // namespace pc
} // namespace gf
