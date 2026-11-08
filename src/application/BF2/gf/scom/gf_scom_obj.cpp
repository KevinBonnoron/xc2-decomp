#include "gf/scom/gf_scom_obj.h"

#include "gf/game/quest/gf_quest_task.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

bool SCOM_QUEST_GIMMICK::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeGimmickTask(unknown1c, unknown20);
  return true;
}

bool SCOM_OBJ_WARP_POS::exec(const fw::UpdateInfo &) {
  GfObjUtil::setWarpTransform(unknown20, unknown30, unknown50);
  return true;
}

} // namespace gf
