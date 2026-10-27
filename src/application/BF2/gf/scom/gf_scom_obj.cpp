#include "gf/scom/gf_scom_obj.h"

#include "gf/game/quest/gf_quest_task.h"

namespace gf {

bool SCOM_QUEST_GIMMICK::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeGimmickTask(unknown1c, unknown20);
  return true;
}

} // namespace gf
