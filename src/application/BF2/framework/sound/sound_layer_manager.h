#pragma once
#include <stddef.h>

#include "mm_mtl/delegate.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

class SoundUpdater : public mm::mtl::IntrusiveListNode<SoundUpdater> {
public:
  mm::mtl::Delegate<int()> unknown10; // Inferred role: update callback; original member name unknown.
  bool unknown30;                     // Inferred role: callback result; original member name unknown.
  bool unknown31;                     // Inferred role: registered; original member name unknown.
};

static_assert(offsetof(SoundUpdater, unknown10) == 0x10, "");
static_assert(offsetof(SoundUpdater, unknown30) == 0x30, "");
static_assert(offsetof(SoundUpdater, unknown31) == 0x31, "");

class SoundLayerManager : public mm::mtl::PtrSingleton<SoundLayerManager> {
public:
  static const u32 LAYER_MAX = 32;

  SoundLayerManager();
  ~SoundLayerManager() override;
  void update(u32 layerMask);

  mm::mtl::FixedArray<mm::mtl::IntrusiveList<SoundUpdater>, LAYER_MAX> unknown08; // Inferred role: updaters per layer; original member name unknown.
};

static_assert(offsetof(SoundLayerManager, unknown08) == 0x08, "");

} // namespace fw
