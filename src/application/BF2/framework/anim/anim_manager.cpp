#include "framework/anim/anim_manager.h"

#include "anm/anm_thread_pool.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

AnimationManager::AnimationManager() {
  unknownf20 = nullptr;
  unknownf18 = nullptr;
  mm::mtl::IAllocator *allocator = Allocator::getProcAllocator();
  anm::TreadPoolInfo info;
  info.unknown00 = 3;
  info.unknown04 = 2;
  info.unknown08 = 2;
#line 40
  unknownf18 = new (allocator, 16, __FILE__, __LINE__) anm::ThreadPool(info, *allocator);
#line 43
  unknownf20 = new (allocator, 16, __FILE__, __LINE__) anm::JobQueue(allocator);
  unknownf20->registerJobExecuter(0, AnimSamplePoseJob::exec);
  unknownf20->registerJobExecuter(1, AnimModifyPoseJob::exec);
  unknownf20->registerJobExecuter(2, AnimAfterModifyJob::exec);
  unknownf20->registerJobExecuter(3, AnimIkResolveJob::exec);
}

AnimationManager::~AnimationManager() {
  unknownf18->waitForCompletion();
  if (unknownf20 != nullptr) {
    delete unknownf20;
    unknownf20 = nullptr;
  }

  if (unknownf18 != nullptr) {
    delete unknownf18;
    unknownf18 = nullptr;
  }
}

void AnimationManager::samplePose(u32 layers) {
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      unknown002<AnimSamplePoseJob, AnimPoseSamplerInterface>(unknown18[layer].unknown18);
    }
  }

  unknownf18->processAllJob(*unknownf20);
  unknownf18->waitForCompletion();
}

void AnimationManager::applyPose(u32 layers) {
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      unknown002<AnimModifyPoseJob, AnimPoseModifierInterface>(unknown18[layer].unknown30);
    }
  }

  unknownf18->processAllJob(*unknownf20);
  unknownf18->waitForCompletion();
}

void AnimationManager::applyAfterModifyPose(u32 layers) {
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      unknown002<AnimAfterModifyJob, AnimAfterModifierInterface>(unknown18[layer].unknown48);
    }
  }

  unknownf18->processAllJob(*unknownf20);
  unknownf18->waitForCompletion();
}

void AnimationManager::solveIK(const UpdateInfo &info, u32 layers) {
  for (u32 layer = 0; layer < LAYER_MAX; layer++) {
    if ((layers & 1 << layer) != 0) {
      mm::mtl::IntrusiveList<IkResolver> &list = unknown18[layer].unknown60;
      mm::mtl::IntrusiveList<IkResolver>::iterator it = list.begin();
      for (int count = list.size(); count != 0; count--) {
        AnimIkResolveJob job(1);
        job.unknown20 = &info;
        job.unknown10[0] = &*it;
        ++it;
        unknownf20->unknown001(job);
      }
    }
  }

  unknownf18->processAllJob(*unknownf20);
  unknownf18->waitForCompletion();
}

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

} // namespace fw
