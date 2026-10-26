#pragma once
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "types.h"
#include <stddef.h>

namespace gmk {

class AGmkBase;
class IGmkList;

class GmkSet {
public:
  struct CreateInfo {
    CreateInfo() : unknown04(-1), unknown10(0.0f, 0.0f, 0.0f), unknown20(0.0f), unknown24(false) {}

    mtl::ALLOC_HANDLE unknown00; // Inferred role: memory; original member name unknown.
    int unknown04;               // Inferred role: gmk set id; original member name unknown.
    mm::Vec3 unknown10;          // Inferred role: position; original member name unknown.
    f32 unknown20;               // Inferred role: rotation; original member name unknown.
    bool unknown24;              // Inferred role: game entity disabled; original member name unknown.
  };

  virtual ~GmkSet();

  virtual void createGmkLists(int gmkSetId);

  bool isValid() const;
  bool isGmkListsCreated() const;
  bool updateImmediate();
  const AGmkBase *findFirstGmkInstByBdatId(GmkType type, int bdatId) const;
  const AGmkBase *findGmkInstByGmkInstIndex(GmkType type, u32 index) const;
  void update(f32 deltaTime);
  explicit GmkSet(const CreateInfo *info);
  void create(const CreateInfo &info);
  void dispose();
  const IGmkList *getGmkList(GmkType type) const;
  IGmkList *getGmkList(GmkType type);
  void seqWaitToValidate_GfGameManager_m_mapID(f32 deltaTime);
  void disposeGmkLists();
  void disposeMapBdat();
  void seqUpdate(f32 deltaTime);
  bool createMapBdat(int map);
  void seqCreateMapBdat(f32 deltaTime);
  void seqCreateMapGmk(f32 deltaTime);

  CreateInfo unknown10;               // Inferred role: create info; original member name unknown.
  GmkBdat unknown40;                  // Inferred role: map bdat; original member name unknown.
  GmkNpcManager unknown178;           // Inferred role: npc manager; original member name unknown.
  IGmkList *unknown1b8[GMK_TYPE_NUM]; // Inferred role: lists; original member name unknown.
  void (GmkSet::*unknown388)(f32);    // Inferred role: seq; original member name unknown.
};

static_assert(sizeof(GmkSet::CreateInfo) == 0x30, "");
static_assert(offsetof(GmkSet, unknown10) == 0x10, "");
static_assert(offsetof(GmkSet, unknown40) == 0x40, "");
static_assert(offsetof(GmkSet, unknown178) == 0x178, "");
static_assert(offsetof(GmkSet, unknown1b8) == 0x1b8, "");
static_assert(offsetof(GmkSet, unknown388) == 0x388, "");
static_assert(sizeof(GmkSet) == 0x3a0, "");

} // namespace gmk
