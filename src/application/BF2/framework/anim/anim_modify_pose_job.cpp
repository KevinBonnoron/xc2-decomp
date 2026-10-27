#include "anm/anm_job.h"
#include "framework/anim/anim_manager.h"
#include "types.h"

namespace fw {

const char *AnimModifyPoseJob::_TYPE_NAME = "AnimModifyPoseJob";

AnimModifyPoseJob::AnimModifyPoseJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimModifyPoseJob), 1), unknown30(count) {}

void AnimModifyPoseJob::exec(anm::Job &job) {
  AnimModifyPoseJob &modifyPoseJob = static_cast<AnimModifyPoseJob &>(job);
  for (int i = 0; i < modifyPoseJob.unknown30; i++) {
    modifyPoseJob.unknown10[i]->apply();
  }
}

} // namespace fw
