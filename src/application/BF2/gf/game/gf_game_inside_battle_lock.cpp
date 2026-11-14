#include "gf/game/gf_game_inside_battle_lock.h"

#include "framework/memory/framework_memory.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_object_type.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_battle_lock.h"
#include "gmk/gmk_collision.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

namespace gf {
namespace {

// Inferred role: tells whether a position is inside one of the battle locks; original name unknown.
struct unknown001 {
  void onTraverse(const gmk::AGmkBase &gmk) {
    if (static_cast<const gmk::GmkBattleLock &>(gmk).unknown50.unknown58 != nullptr) {
      result = gmk.isInsideShape(position, 0.0f);
    }
  }

  bool &result;
  mm::Vec3 position;
};

// Inferred role: tells whether one of the battle locks is active; original name unknown.
struct unknown002 {
  void onTraverse(const gmk::AGmkBase &gmk) {
    if (static_cast<const gmk::GmkBattleLock &>(gmk).unknown50.unknown58 != nullptr) {
      lock->unknown20 = true;
    }
  }

  GfGameInsideBattleLock *lock;
};

} // namespace

bool GfGameInsideBattleLock::isInside(const mm::Vec3 &position) {
  bool result = false;
  unknown001 traverser = {result, position};
  if (gmk::GmkManager::get()->traverseGmkInst(gmk::GMK_TYPE_BATTLE_LOCK, traverser)) {
    return result;
  }

  return false;
}

bool GfGameInsideBattleLock::isInside(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    return get()->unknown08[handle];
  }
  return false;
}

void GfGameInsideBattleLock::build(const GfSetupParam &) {
  // __LINE__ must be 35 as in the original source: it is the line argument of operator new.
#line 35
  GfGameInsideBattleLock *lock = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameInsideBattleLock;
  lock->unknown08.setAllocator(fw::FrameworkMemory::getAllocator(5));
}

void GfGameInsideBattleLock::destroy() { delete get(); }

void GfGameInsideBattleLock::update(const fw::UpdateInfo &) {
  GfGameInsideBattleLock *lock = get();
  if (lock == nullptr || gmk::GmkManager::get() == nullptr) {
    return;
  }

  lock->updateInfos();
  lock->unknown20 = false;
  unknown002 traverser = {lock};
  gmk::GmkManager::get()->traverseGmkInst(gmk::GMK_TYPE_BATTLE_LOCK, traverser);
}

void GfGameInsideBattleLock::updateInfo(GF_OBJ_HANDLE *handle) { get()->unknown08[handle] = get()->isInsideBattleLock(handle); }

bool GfGameInsideBattleLock::isInsideBattleLock(GF_OBJ_HANDLE *handle) const {
  GfObjAcc acc(handle);
  GfObj *obj = acc.getObj();
  if (obj == nullptr || obj->unknown28 != OBJECT_TYPE_ENEMY) {
    return false;
  }

  mm::Vec3 position;
  if (acc.isValidTransform()) {
    position = acc.getWorldTransform().unknown00;
  } else {
    position = GfObjUtil::getObjSetup(handle)->unknown20;
  }
  return isInside(position);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameInsideBattleLock>::~PtrSingleton();

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<gf::GF_OBJ_HANDLE *, bool>::MapTraits<gf::GF_OBJ_HANDLE *, bool>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<gf::GF_OBJ_HANDLE *, bool> &);
template void unknown101::rebalance(unknown101::node *);
