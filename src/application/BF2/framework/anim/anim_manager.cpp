#include "framework/anim/anim_manager.h"

namespace fw {

void AnimationManager::addControlUpdater(u32 layer, AnimControlUpdaterInterface &updater) { groups[layer].controlUpdaters.push_back(&updater); }

void AnimationManager::removeControlUpdater(u32 layer, AnimControlUpdaterInterface &updater) { groups[layer].controlUpdaters.erase(&updater); }

void AnimationManager::addPoseSampler(u32 layer, AnimPoseSamplerInterface &sampler) { groups[layer].poseSamplers.push_back(&sampler); }

void AnimationManager::removePoseSampler(u32 layer, AnimPoseSamplerInterface &sampler) { groups[layer].poseSamplers.erase(&sampler); }

void AnimationManager::addPoseModifier(u32 layer, AnimPoseModifierInterface &modifier) { groups[layer].poseModifiers.push_back(&modifier); }

void AnimationManager::removePoseModifier(u32 layer, AnimPoseModifierInterface &modifier) { groups[layer].poseModifiers.erase(&modifier); }

void AnimationManager::addAfterModifier(u32 layer, AnimAfterModifierInterface &modifier) { groups[layer].afterModifiers.push_back(&modifier); }

void AnimationManager::removeAfterModifier(u32 layer, AnimAfterModifierInterface &modifier) { groups[layer].afterModifiers.erase(&modifier); }

void AnimationManager::addIkResolver(u32 layer, IkResolver &resolver) { groups[layer].ikResolvers.push_back(&resolver); }

void AnimationManager::removeIkResolver(u32 layer, IkResolver &resolver) { groups[layer].ikResolvers.erase(&resolver); }

} // namespace fw
