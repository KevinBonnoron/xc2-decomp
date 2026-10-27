#pragma once
#include <stddef.h>

#include "anm/anm_job.h"
#include "anm/anm_job_queue.h"
#include "framework/manager_object.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

class SensorUpdater : public mm::mtl::IntrusiveListNode<SensorUpdater> {
public:
  mm::mtl::Delegate<void()> unknown10; // Inferred role: update callback; original member name unknown.
  bool unknown30;                      // Inferred role: registered; original member name unknown.
};

static_assert(offsetof(SensorUpdater, unknown10) == 0x10, "");
static_assert(offsetof(SensorUpdater, unknown30) == 0x30, "");

class SensorUpdateJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit SensorUpdateJob(u32 count);
  static void exec(anm::Job &job);

  SensorUpdater *unknown10[2]; // Inferred role: updaters; original member name unknown.
  u32 unknown20;               // Inferred role: updater count; original member name unknown.
};

static_assert(offsetof(SensorUpdateJob, unknown10) == 0x10, "");
static_assert(offsetof(SensorUpdateJob, unknown20) == 0x20, "");
static_assert(sizeof(SensorUpdateJob) == 0x28, "");

class SensorManager : public ManagerObject, public mm::mtl::PtrSingleton<SensorManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<SensorUpdater> unknown00; // Inferred role: before game updaters; original member name unknown.
    mm::mtl::IntrusiveList<SensorUpdater> unknown18; // Inferred role: after animation updaters; original member name unknown.
  };

  SensorManager();
  ~SensorManager();
  const char *getName() const override;
  virtual void update(const UpdateInfo &info);
  void flushBeforeGame(const UpdateInfo &info, u32 layers);
  void flushAfterAnimation(const UpdateInfo &info, u32 layers);
  void addUpdaterBeforeGame(u32 layer, SensorUpdater &updater);
  void removeUpdaterBeforeGame(u32 layer, SensorUpdater &updater);
  void addUpdaterAfterAnimation(u32 layer, SensorUpdater &updater);
  void removeUpdaterAfterAnimation(u32 layer, SensorUpdater &updater);

  // Inferred helper: queues one job holding the next updaters of a list; original name unknown.
  template <typename Iterator> void unknown001(Iterator &it, u32 count) {
    SensorUpdateJob job(count);
    for (u32 i = 0; i < count; i++) {
      job.unknown10[i] = &*it;
      ++it;
    }
    unknown618->unknown001(job);
  }

  mm::mtl::FixedArray<Group, LAYER_MAX> unknown18; // Inferred role: groups; original member name unknown.
  anm::JobQueue *unknown618;                       // Inferred role: job queue; original member name unknown.
};

static_assert(sizeof(SensorManager::Group) == 0x30, "");
static_assert(offsetof(SensorManager, unknown18) == 0x18, "");
static_assert(offsetof(SensorManager, unknown618) == 0x618, "");

} // namespace fw
