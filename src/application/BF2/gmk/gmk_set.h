#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_map_obj.h"
#include "gmk/gmk_mob/gmk_mob.h"
#include "gmk/gmk_mob/gmk_routed_mob.h"
#include "gmk/gmk_npc/gmk_npc.h"
#include "gmk/gmk_npc/gmk_npc_manager.h"
#include "gmk/gmk_npc/gmk_routed_npc.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/vector.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace gmk {

class AGmkBase;
class IGmkGameObjTraverser;

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
  bool traverseGmkGameObj(IGmkGameObjTraverser &traverser) const;
  bool isValidView() const;
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
  static bool isGmkInstValidView(const AGmkBase &gmk);
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

// The game instantiates it for gf::GfGmkBladeTraverser, gf::GfUnpopBladeIds, gf::LocatorPrecious,
// gmk::GmkInstDispTraverserByBdatId and two lambdas of gf::GfGameInsideBattleLock::updateInfoByGmk.
template <typename T> bool GmkManager::traverseGmkInst(GmkType type, T &traverser) const {
  if (!isGmkSetsReady()) {
    return false;
  }
  for (GmkSet *const *it = unknownf358.begin(); it != unknownf358.end(); ++it) {
    const GmkSet *set = *it;
    if (set == nullptr) {
      continue;
    }
    const IGmkList *list = set->getGmkList(type);
    if (list == nullptr) {
      continue;
    }
    u32 num = list->getInstNum();
    for (u32 index = 0; index < num; index++) {
      const AGmkBase *gmk = list->getInst(index);
      if (gmk != nullptr) {
        traverser.onTraverse(*gmk);
      }
    }
  }
  return true;
}

// Inferred helpers: the game object of a gimmick instance, and the instances of a gimmick that owns several; original names unknown.
inline gf::GF_OBJ_HANDLE *unknown010(const GmkNpc &gmk) { return gmk.getGobInst(); }

inline gf::GF_OBJ_HANDLE *unknown010(const GmkRoutedNpc &gmk) { return gmk.getGobInst(); }

inline gf::GF_OBJ_HANDLE *unknown010(const GmkMapObj &gmk) { return gmk.unknown48; }

inline gf::GF_OBJ_HANDLE *unknown010(const GmkRoutedMapObj &gmk) { return gmk.unknown50; }

inline const GmkEnemyInsts &unknown011(const GmkEnemy &gmk) { return gmk.unknown48; }

inline const GmkEnemyInsts &unknown011(const GmkRoutedEnemy &gmk) { return gmk.unknown50; }

inline const GmkMobInsts &unknown011(const GmkMob &gmk) { return gmk.unknown48; }

inline const GmkMobInsts &unknown011(const GmkRoutedMob &gmk) { return gmk.unknown50; }

// Inferred helpers: the number of game objects of the instances and one of them; original names unknown.
inline u32 unknown012(const GmkEnemyInsts &insts) { return insts.unknown98.getGobInstNum(); }

inline u32 unknown012(const GmkMobInsts &insts) { return insts.unknowna8->size(); }

inline gf::GF_OBJ_HANDLE *unknown013(const GmkEnemyInsts &insts, u32 index) { return insts.getGobInst(index); }

inline gf::GF_OBJ_HANDLE *unknown013(const GmkMobInsts &insts, u32 index) { return (*insts.unknowna8)[index]; }

// The game instantiates them for the gimmicks that GfGameUtil collects the game objects of.
template <typename T> void GmkManager::collectGameObjs(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024> &handles) const {
  size_t setNum = unknownf358.size();
  for (size_t i = 0; i < setNum; i++) {
    const GmkSet *set = unknownf358[i];
    if (set == nullptr) {
      continue;
    }
    const IGmkList *list = set->getGmkList(T::GMK_TYPE);
    if (list == nullptr) {
      continue;
    }
    u32 num = list->getInstNum();
    for (u32 index = 0; index < num; index++) {
      const T *gmk = static_cast<const T *>(list->getInst(index));
      if (gmk != nullptr && gmk->isValid()) {
        gf::GF_OBJ_HANDLE *handle = unknown010(*gmk);
        if (handle != gf::unknown020) {
          handles.push_back(handle);
        }
      }
    }
  }
}

template <typename T> void GmkManager::collectGameObjsUnbound(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024> &handles) const {
  size_t setNum = unknownf358.size();
  for (size_t i = 0; i < setNum; i++) {
    const GmkSet *set = unknownf358[i];
    if (set == nullptr) {
      continue;
    }
    const IGmkList *list = set->getGmkList(T::GMK_TYPE);
    if (list == nullptr) {
      continue;
    }
    u32 num = list->getInstNum();
    for (u32 index = 0; index < num; index++) {
      const T *gmk = static_cast<const T *>(list->getInst(index));
      if (gmk != nullptr && gmk->isValid()) {
        const auto &insts = unknown011(*gmk);
        u32 count = unknown012(insts);
        for (u32 handleIndex = 0; handleIndex < count; handleIndex++) {
          gf::GF_OBJ_HANDLE *handle = unknown013(insts, handleIndex);
          if (handle != gf::unknown020) {
            handles.push_back(handle);
          }
        }
      }
    }
  }
}

} // namespace gmk
