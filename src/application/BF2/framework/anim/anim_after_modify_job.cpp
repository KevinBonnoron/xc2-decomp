#include "anm/anm_job.h"
#include "framework/anim/anim_manager.h"
#include "types.h"

namespace fw {

const char *AnimAfterModifyJob::_TYPE_NAME = "AnimAfterModifyJob";

AnimAfterModifyJob::AnimAfterModifyJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimAfterModifyJob), 2), unknown30(count) {}

void AnimAfterModifyJob::exec(anm::Job &job) {
  AnimAfterModifyJob &afterModifyJob = static_cast<AnimAfterModifyJob &>(job);
  for (int i = 0; i < afterModifyJob.unknown30; i++) {
    afterModifyJob.unknown10[i]->apply();
  }
}

} // namespace fw
