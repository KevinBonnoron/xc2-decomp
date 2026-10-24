#include "framework/anim/anim_manager.h"

namespace fw {

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

} // namespace fw
