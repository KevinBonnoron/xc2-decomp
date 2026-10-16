#pragma once
#include "gmk/gmk_manager.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "types.h"
#include <stddef.h>

namespace gmk {

class IGmkList;

class GmkSet {
public:
  virtual ~GmkSet();

  virtual void createGmkLists(int gmkSetId);

  u8 _08[0x10 - 0x08];
  mtl::ALLOC_HANDLE memory;
  u8 _14[0x20 - 0x14];
  mm::Vec3 position;
  f32 rotation;
  u8 _34[0x178 - 0x34];
  GmkNpcManager npcManager;
  IGmkList *lists[GMK_TYPE_NUM];
  u8 _388[0x398 - 0x388];
};

static_assert(offsetof(GmkSet, memory) == 0x10, "");
static_assert(offsetof(GmkSet, position) == 0x20, "");
static_assert(offsetof(GmkSet, rotation) == 0x30, "");
static_assert(offsetof(GmkSet, npcManager) == 0x178, "");
static_assert(offsetof(GmkSet, lists) == 0x1b8, "");

} // namespace gmk
