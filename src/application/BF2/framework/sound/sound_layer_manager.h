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
  // The constructor has no game symbol; it is inline in GfComSound::GfComSound (0x710057ead4), which clears the two flags with one 16-bit store (strh wzr, [x19, #0x120], 0x710057eb58).
  SoundUpdater() : unknown30(false), unknown31(false) {}

  // The delegate returns u32: GfComSound::setup binds GfComSound::flush through Delegate<unsigned int()>::memberFuncInvoker<GfComSound> (0x71005802a4).
  mm::mtl::Delegate<u32()> unknown10; // Inferred role: update callback; original member name unknown.
  bool unknown30;                     // Inferred role: callback result; original member name unknown.
  bool unknown31;                     // Inferred role: registered; original member name unknown.
};

static_assert(offsetof(SoundUpdater, unknown10) == 0x10, "");
static_assert(offsetof(SoundUpdater, unknown30) == 0x30, "");
static_assert(offsetof(SoundUpdater, unknown31) == 0x31, "");

class SoundLayerManager : public mm::mtl::PtrSingleton<SoundLayerManager> {
public:
  static const u32 LAYER_UNKNOWN_32 = 32; // Inferred role: maximum number of layers; original name unknown.

  SoundLayerManager();
  ~SoundLayerManager() override;
  void update(u32 layerMask);

  mm::mtl::FixedArray<mm::mtl::IntrusiveList<SoundUpdater>, LAYER_UNKNOWN_32> unknown08; // Inferred role: updaters per layer; original member name unknown.
};

static_assert(offsetof(SoundLayerManager, unknown08) == 0x08, "");

} // namespace fw
