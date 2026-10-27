#include "framework/anim/anim_manager.h"

namespace fw {

const char *AnimationManager::getName() const { return "AnimObjectManager"; }

void AnimationManager::update(const UpdateInfo &info) {}

void AnimationManager::addControlUpdater(u32 layer, AnimControlUpdaterInterface &updater) { unknown18[layer].unknown00.push_back(&updater); }

void AnimationManager::removeControlUpdater(u32 layer, AnimControlUpdaterInterface &updater) { unknown18[layer].unknown00.erase(&updater); }

void AnimationManager::addPoseSampler(u32 layer, AnimPoseSamplerInterface &sampler) { unknown18[layer].unknown18.push_back(&sampler); }

void AnimationManager::removePoseSampler(u32 layer, AnimPoseSamplerInterface &sampler) { unknown18[layer].unknown18.erase(&sampler); }

void AnimationManager::addPoseModifier(u32 layer, AnimPoseModifierInterface &modifier) { unknown18[layer].unknown30.push_back(&modifier); }

void AnimationManager::removePoseModifier(u32 layer, AnimPoseModifierInterface &modifier) { unknown18[layer].unknown30.erase(&modifier); }

void AnimationManager::addAfterModifier(u32 layer, AnimAfterModifierInterface &modifier) { unknown18[layer].unknown48.push_back(&modifier); }

void AnimationManager::removeAfterModifier(u32 layer, AnimAfterModifierInterface &modifier) { unknown18[layer].unknown48.erase(&modifier); }

void AnimationManager::addIkResolver(u32 layer, IkResolver &resolver) { unknown18[layer].unknown60.push_back(&resolver); }

void AnimationManager::removeIkResolver(u32 layer, IkResolver &resolver) { unknown18[layer].unknown60.erase(&resolver); }

void IkResolver::resolve(const UpdateInfo &info) {
  for (u32 i = 0; i < unknown10.size(); i++) {
    if (unknown10[i].get() != nullptr) {
      unknown10[i]->solve(info);
    }
  }
}

const char *AnimSamplePoseJob::_TYPE_NAME = "AnimSamplePoseJob";

AnimSamplePoseJob::AnimSamplePoseJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimSamplePoseJob), 0), unknown30(count) {}

void AnimSamplePoseJob::exec(anm::Job &job) {
  AnimSamplePoseJob &samplePoseJob = static_cast<AnimSamplePoseJob &>(job);
  for (int i = 0; i < samplePoseJob.unknown30; i++) {
    samplePoseJob.unknown10[i]->samplePose();
  }
}

const char *AnimModifyPoseJob::_TYPE_NAME = "AnimModifyPoseJob";

AnimModifyPoseJob::AnimModifyPoseJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimModifyPoseJob), 1), unknown30(count) {}

void AnimModifyPoseJob::exec(anm::Job &job) {
  AnimModifyPoseJob &modifyPoseJob = static_cast<AnimModifyPoseJob &>(job);
  for (int i = 0; i < modifyPoseJob.unknown30; i++) {
    modifyPoseJob.unknown10[i]->apply();
  }
}

const char *AnimAfterModifyJob::_TYPE_NAME = "AnimAfterModifyJob";

AnimAfterModifyJob::AnimAfterModifyJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimAfterModifyJob), 2), unknown30(count) {}

void AnimAfterModifyJob::exec(anm::Job &job) {
  AnimAfterModifyJob &afterModifyJob = static_cast<AnimAfterModifyJob &>(job);
  for (int i = 0; i < afterModifyJob.unknown30; i++) {
    afterModifyJob.unknown10[i]->apply();
  }
}

const char *AnimIkResolveJob::_TYPE_NAME = "AnimIkResolveJob";

AnimIkResolveJob::AnimIkResolveJob(u32 count) : anm::Job(_TYPE_NAME, sizeof(AnimIkResolveJob), 3), unknown18(count), unknown20(nullptr) {}

void AnimIkResolveJob::exec(anm::Job &job) {
  AnimIkResolveJob &ikResolveJob = static_cast<AnimIkResolveJob &>(job);
  for (int i = 0; i < ikResolveJob.unknown18; i++) {
    ikResolveJob.unknown10[i]->resolve(*ikResolveJob.unknown20);
  }
}

} // namespace fw
