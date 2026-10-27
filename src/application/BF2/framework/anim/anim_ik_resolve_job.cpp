#include "anm/anm_job.h"
#include "framework/anim/anim_manager.h"
#include "types.h"

namespace fw {

const char *AnimIkResolveJob::_TYPE_NAME = "AnimIkResolveJob";

AnimIkResolveJob::AnimIkResolveJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimIkResolveJob), 3), unknown18(count), unknown20(nullptr) {}

void AnimIkResolveJob::exec(anm::Job &job) {
  AnimIkResolveJob &ikResolveJob = static_cast<AnimIkResolveJob &>(job);
  for (int i = 0; i < ikResolveJob.unknown18; i++) {
    ikResolveJob.unknown10[i]->resolve(*ikResolveJob.unknown20);
  }
}

} // namespace fw
