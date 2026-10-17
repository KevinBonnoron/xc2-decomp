#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

class AnimControlUpdaterInterface : public mm::mtl::IntrusiveListNode<AnimControlUpdaterInterface> {
public:
  virtual ~AnimControlUpdaterInterface() {}
  virtual void update(const UpdateInfo &info) = 0;
};

class AnimPoseSamplerInterface : public mm::mtl::IntrusiveListNode<AnimPoseSamplerInterface> {
public:
  virtual ~AnimPoseSamplerInterface();
  virtual void samplePose() = 0;
};

class AnimPoseModifierInterface : public mm::mtl::IntrusiveListNode<AnimPoseModifierInterface> {
public:
  virtual ~AnimPoseModifierInterface();
};

class AnimAfterModifierInterface : public mm::mtl::IntrusiveListNode<AnimAfterModifierInterface> {
public:
  virtual ~AnimAfterModifierInterface();
  virtual void apply() = 0;
};

class IkResolver : public mm::mtl::IntrusiveListNode<IkResolver> {
public:
  void resolve(const UpdateInfo &info);
};

class AnimationManager : public ManagerObject, public mm::mtl::PtrSingleton<AnimationManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<AnimControlUpdaterInterface> controlUpdaters;
    mm::mtl::IntrusiveList<AnimPoseSamplerInterface> poseSamplers;
    mm::mtl::IntrusiveList<AnimPoseModifierInterface> poseModifiers;
    mm::mtl::IntrusiveList<AnimAfterModifierInterface> afterModifiers;
    mm::mtl::IntrusiveList<IkResolver> ikResolvers;
  };

  void addControlUpdater(u32 layer, AnimControlUpdaterInterface &updater);
  void removeControlUpdater(u32 layer, AnimControlUpdaterInterface &updater);
  void addPoseSampler(u32 layer, AnimPoseSamplerInterface &sampler);
  void removePoseSampler(u32 layer, AnimPoseSamplerInterface &sampler);
  void addPoseModifier(u32 layer, AnimPoseModifierInterface &modifier);
  void removePoseModifier(u32 layer, AnimPoseModifierInterface &modifier);
  void addAfterModifier(u32 layer, AnimAfterModifierInterface &modifier);
  void removeAfterModifier(u32 layer, AnimAfterModifierInterface &modifier);
  void addIkResolver(u32 layer, IkResolver &resolver);
  void removeIkResolver(u32 layer, IkResolver &resolver);

  Group groups[LAYER_MAX];
};

static_assert(sizeof(AnimationManager::Group) == 0x78, "");
static_assert(offsetof(AnimationManager, groups) == 0x18, "");

} // namespace fw
