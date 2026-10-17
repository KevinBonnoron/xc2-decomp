#pragma once
#include "gmk/gmk_bdat.h"
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
  struct CreateInfo {
    CreateInfo() : gmkSetId(-1), position(0.0f, 0.0f, 0.0f), rotation(0.0f), isGameEntityDisabled(false) {}

    mtl::ALLOC_HANDLE memory;
    int gmkSetId;
    mm::Vec3 position;
    f32 rotation;
    bool isGameEntityDisabled;
  };

  virtual ~GmkSet();

  virtual void createGmkLists(int gmkSetId);

  CreateInfo createInfo;
  GmkBdat mapBdat;
  GmkNpcManager npcManager;
  IGmkList *lists[GMK_TYPE_NUM];
  u8 _388[0x398 - 0x388];
};

static_assert(sizeof(GmkSet::CreateInfo) == 0x30, "");
static_assert(offsetof(GmkSet, createInfo) == 0x10, "");
static_assert(offsetof(GmkSet, mapBdat) == 0x40, "");
static_assert(offsetof(GmkSet, npcManager) == 0x178, "");
static_assert(offsetof(GmkSet, lists) == 0x1b8, "");

} // namespace gmk
