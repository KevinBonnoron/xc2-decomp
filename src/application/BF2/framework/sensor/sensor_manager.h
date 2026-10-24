#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

class SensorUpdater : public mm::mtl::IntrusiveListNode<SensorUpdater> {
public:
  u8 _10[0x30 - 0x10];
  bool unknown30; // Inferred role: registered; original member name unknown.
};

static_assert(offsetof(SensorUpdater, unknown30) == 0x30, "");

class SensorManager : public ManagerObject, public mm::mtl::PtrSingleton<SensorManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<SensorUpdater> unknown00; // Inferred role: before game updaters; original member name unknown.
    mm::mtl::IntrusiveList<SensorUpdater> unknown18; // Inferred role: after animation updaters; original member name unknown.
  };

  void addUpdaterBeforeGame(u32 layer, SensorUpdater &updater);
  void removeUpdaterBeforeGame(u32 layer, SensorUpdater &updater);
  void addUpdaterAfterAnimation(u32 layer, SensorUpdater &updater);
  void removeUpdaterAfterAnimation(u32 layer, SensorUpdater &updater);

  mm::mtl::FixedArray<Group, LAYER_MAX> unknown18; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(SensorManager::Group) == 0x30, "");
static_assert(offsetof(SensorManager, unknown18) == 0x18, "");

} // namespace fw
