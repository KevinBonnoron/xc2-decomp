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
    mm::mtl::IntrusiveList<AnimControlUpdaterInterface> unknown00; // Inferred role: control updaters; original member name unknown.
    mm::mtl::IntrusiveList<AnimPoseSamplerInterface> unknown18;    // Inferred role: pose samplers; original member name unknown.
    mm::mtl::IntrusiveList<AnimPoseModifierInterface> unknown30;   // Inferred role: pose modifiers; original member name unknown.
    mm::mtl::IntrusiveList<AnimAfterModifierInterface> unknown48;  // Inferred role: after modifiers; original member name unknown.
    mm::mtl::IntrusiveList<IkResolver> unknown60;                  // Inferred role: ik resolvers; original member name unknown.
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

  Group unknown18[LAYER_MAX]; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(AnimationManager::Group) == 0x78, "");
static_assert(offsetof(AnimationManager, unknown18) == 0x18, "");

} // namespace fw
