#pragma once
#include <stddef.h>

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

class DyanmicsManager : public ManagerObject, public mm::mtl::PtrSingleton<DyanmicsManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<DynamicsUpdaterInterface> updaters;
    mm::mtl::IntrusiveList<DynamicsColObjUpdaterInterface> colUpdaters;
  };

  void addColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater);
  void removeColUpdater(u32 layer, DynamicsColObjUpdaterInterface &updater);
  void addUpdater(u32 layer, DynamicsUpdaterInterface &updater);
  void removeUpdater(u32 layer, DynamicsUpdaterInterface &updater);

  Group groups[LAYER_MAX];
};

static_assert(sizeof(DyanmicsManager::Group) == 0x30, "");
static_assert(offsetof(DyanmicsManager, groups) == 0x18, "");

} // namespace fw
