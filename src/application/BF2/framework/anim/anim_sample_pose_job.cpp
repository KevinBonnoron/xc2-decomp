#include "anm/anm_job.h"
#include "framework/anim/anim_manager.h"
#include "types.h"

namespace fw {

const char *AnimSamplePoseJob::_TYPE_NAME = "AnimSamplePoseJob";

AnimSamplePoseJob::AnimSamplePoseJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimSamplePoseJob), 0), unknown30(count) {}

void AnimSamplePoseJob::exec(anm::Job &job) {
  AnimSamplePoseJob &samplePoseJob = static_cast<AnimSamplePoseJob &>(job);
  for (int i = 0; i < samplePoseJob.unknown30; i++) {
    samplePoseJob.unknown10[i]->samplePose();
  }
}

} // namespace fw
