#include "gf/object/component/pc/field/ai/gf_pc_ai_retreat_task_field.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "navi/nvmsh_ac_obj.h"
#include "types.h"

namespace gf {
namespace pc {

bool TaskFieldRetreat::testCondition(const BlackBoardField &blackBoard) {
  if (blackBoard.unknown200.test(4)) {
    mm::Vec3 diff = blackBoard.unknown1f0 - blackBoard.unknown08->unknown160.unknown00;
    return sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) > 1.0f;
  }
  return false;
}

void TaskFieldRetreat::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  navi::NvmshAcObj *naviObject = blackBoard.unknown10;
  naviObject->setBeginPos(property->unknown160.unknown00);
  naviObject->setEndPos(blackBoard.unknown1f0);
  mm::Vec3 diff = blackBoard.unknown1f0 - blackBoard.unknown08->unknown160.unknown00;
  const mm::Vec3 &moveVec = naviObject->getMoveVec();
  f32 distance = fabsf(diff.x * moveVec.x + diff.y * moveVec.y + diff.z * moveVec.z);
  f32 power = AgentUtilField::setFollowInput(distance, naviObject, *property);
  if (distance < 3.0f && power > 0.1f) {
    property->setInputDirPow(naviObject->getMoveVec(), 0.1f);
  }
  blackBoard.unknown200.set(3);
}

} // namespace pc
} // namespace gf
