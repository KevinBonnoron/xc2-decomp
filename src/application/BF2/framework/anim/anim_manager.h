#pragma once
#include <stddef.h>

#include "anm/anm_job.h"
#include "framework/ik/ik_solver.h"
#include "framework/manager_object.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
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
  virtual ~AnimPoseSamplerInterface() {}
  virtual void samplePose() = 0;
};

class AnimPoseModifierInterface : public mm::mtl::IntrusiveListNode<AnimPoseModifierInterface> {
public:
  virtual ~AnimPoseModifierInterface() {}
  virtual void apply() = 0;
};

class AnimAfterModifierInterface : public mm::mtl::IntrusiveListNode<AnimAfterModifierInterface> {
public:
  virtual ~AnimAfterModifierInterface() {}
  virtual void apply() = 0;
};

class IkResolver : public mm::mtl::IntrusiveListNode<IkResolver> {
public:
  void resolve(const UpdateInfo &info);

  mm::mtl::Vector<mm::mtl::IntrusivePtr<IkSolver>> unknown10; // Inferred role: solvers; original member name unknown.
};

static_assert(offsetof(IkResolver, unknown10) == 0x10, "");

class AnimSamplePoseJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit AnimSamplePoseJob(u32 count);
  static void exec(anm::Job &job);

  AnimPoseSamplerInterface *unknown10[4]; // Inferred role: pose samplers; original member name unknown.
  u32 unknown30;                          // Inferred role: sampler count; original member name unknown.
};

static_assert(offsetof(AnimSamplePoseJob, unknown10) == 0x10, "");
static_assert(offsetof(AnimSamplePoseJob, unknown30) == 0x30, "");
static_assert(sizeof(AnimSamplePoseJob) == 0x38, "");

class AnimModifyPoseJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit AnimModifyPoseJob(u32 count);
  static void exec(anm::Job &job);

  AnimPoseModifierInterface *unknown10[4]; // Inferred role: pose modifiers; original member name unknown.
  u32 unknown30;                           // Inferred role: modifier count; original member name unknown.
};

static_assert(offsetof(AnimModifyPoseJob, unknown10) == 0x10, "");
static_assert(offsetof(AnimModifyPoseJob, unknown30) == 0x30, "");
static_assert(sizeof(AnimModifyPoseJob) == 0x38, "");

class AnimAfterModifyJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit AnimAfterModifyJob(u32 count);
  static void exec(anm::Job &job);

  AnimAfterModifierInterface *unknown10[4]; // Inferred role: after modifiers; original member name unknown.
  u32 unknown30;                            // Inferred role: modifier count; original member name unknown.
};

static_assert(offsetof(AnimAfterModifyJob, unknown10) == 0x10, "");
static_assert(offsetof(AnimAfterModifyJob, unknown30) == 0x30, "");
static_assert(sizeof(AnimAfterModifyJob) == 0x38, "");

class AnimIkResolveJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit AnimIkResolveJob(u32 count);
  static void exec(anm::Job &job);

  IkResolver *unknown10[1];    // Inferred role: ik resolvers; original member name unknown.
  u32 unknown18;               // Inferred role: resolver count; original member name unknown.
  const UpdateInfo *unknown20; // Inferred role: update info; original member name unknown.
};

static_assert(offsetof(AnimIkResolveJob, unknown10) == 0x10, "");
static_assert(offsetof(AnimIkResolveJob, unknown18) == 0x18, "");
static_assert(offsetof(AnimIkResolveJob, unknown20) == 0x20, "");
static_assert(sizeof(AnimIkResolveJob) == 0x28, "");

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

  ~AnimationManager() override;
  const char *getName() const override;
  virtual void update(const UpdateInfo &info);
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
