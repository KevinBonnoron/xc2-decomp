#pragma once
#include <stddef.h>

#include "anm/anm_job.h"
#include "framework/manager_object.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

class DynamicsUpdaterInterface : public mm::mtl::IntrusiveListNode<DynamicsUpdaterInterface> {
public:
  virtual ~DynamicsUpdaterInterface() {}
  virtual void update(const UpdateInfo &info) = 0;
  virtual void drawDebug() = 0;
};

class DynamicsColObjUpdaterInterface : public mm::mtl::IntrusiveListNode<DynamicsColObjUpdaterInterface> {
public:
  virtual ~DynamicsColObjUpdaterInterface() {}
  virtual void update() = 0;
};

class DynamicsColUpdateJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit DynamicsColUpdateJob(u32 count);
  static void exec(anm::Job &job);

  DynamicsColObjUpdaterInterface *unknown10[1]; // Inferred role: col updaters; original member name unknown.
  u32 unknown18;                                // Inferred role: updater count; original member name unknown.
};

static_assert(offsetof(DynamicsColUpdateJob, unknown10) == 0x10, "");
static_assert(offsetof(DynamicsColUpdateJob, unknown18) == 0x18, "");
static_assert(sizeof(DynamicsColUpdateJob) == 0x20, "");

class DynamicsUpdateJob : public anm::Job {
public:
  static const char *_TYPE_NAME;

  explicit DynamicsUpdateJob(u32 count);
  static void exec(anm::Job &job);

  DynamicsUpdaterInterface *unknown10[1]; // Inferred role: updaters; original member name unknown.
  u32 unknown18;                          // Inferred role: updater count; original member name unknown.
  const UpdateInfo *unknown20;            // Inferred role: update info; original member name unknown.
};

static_assert(offsetof(DynamicsUpdateJob, unknown10) == 0x10, "");
static_assert(offsetof(DynamicsUpdateJob, unknown18) == 0x18, "");
static_assert(offsetof(DynamicsUpdateJob, unknown20) == 0x20, "");
static_assert(sizeof(DynamicsUpdateJob) == 0x28, "");

class DyanmicsManager : public ManagerObject, public mm::mtl::PtrSingleton<DyanmicsManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<DynamicsUpdaterInterface> unknown00;       // Inferred role: updaters; original member name unknown.
    mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface> unknown18; // Inferred role: col updaters; original member name unknown.
  };

  ~DyanmicsManager() override;
  const char *getName() const override;
  virtual void update(const UpdateInfo &info);
  void addColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater);
  void removeColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater);
  void addUpdater(u32 layer, DynamicsUpdaterInterface &updater);
  void removeUpdater(u32 layer, DynamicsUpdaterInterface &updater);

  Group unknown18[LAYER_MAX]; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(DyanmicsManager::Group) == 0x30, "");
static_assert(offsetof(DyanmicsManager, unknown18) == 0x18, "");

} // namespace fw
