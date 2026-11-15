#include "gf/game/smn_enemy/gf_smn_enemy.h"

#include <algorithm>

#include "framework/debug/debug_draw.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_obj.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/vector.h"

constexpr size_t CAPACITY_UNKNOWN_40 = 40; // Inferred role: smn enemy capacity; original name unknown.

namespace gf {

GfRelSmnEnemy::GfRelSmnEnemy(const CreateInfo *info) : unknown40(1.0f), unknown44(5.0f), unknown48() {
  GfObjManager::addListener(this, OBJEVT_UNKNOWN_0);
  if (info != nullptr) {
    create(*info);
  }
}

GfRelSmnEnemy::~GfRelSmnEnemy() {
  dispose();
  GfObjManager::removeListener(this);
}

void GfRelSmnEnemy::dispose() {
  disposeEnemies(false);
  if (unknown50.size() != 0) {
    unknown50.clear();
    unknown50.destroy();
  }
  unknown10 = CreateInfo();
}

void GfRelSmnEnemy::update(f32 deltaTime) {
  if (unknown10.unknown00 == unknown020 || unknown10.unknown08 < 1) {
    return;
  }
  if (isOwnerValid()) {
    updatePopEnemy();
    updateDepopEnemy();
    validatePopPos();
  } else {
    disposeWaitEnemies();
  }
}

bool GfRelSmnEnemy::isOwnerValid() const {
  GfObjAcc acc(unknown10.unknown00);
  return !acc.isDestroy() && !acc.testFlag(OBJ_FLAG_UNKNOWN_17) && acc.getObj() != nullptr;
}

u32 GfRelSmnEnemy::getEnemyNum() const {
  if (unknown10.unknown00 == unknown020) {
    return 0;
  }
  if (unknown10.unknown08 > 0) {
    return unknowna0.size();
  }
  return 0;
}

GF_OBJ_HANDLE *GfRelSmnEnemy::getEnemy(u32 index) const {
  if (unknown10.unknown00 == unknown020 || unknown10.unknown08 < 1) {
    return unknown020;
  }
  return unknowna0[index];
}

void GfRelSmnEnemy::disposeWaitEnemies() {
  if (!unknown78.empty()) {
    for (std::pair<PopInfo *, GF_OBJ_HANDLE *> *enemy = unknown78.begin(), *end = unknown78.end(); enemy != end; ++enemy) {
      if (enemy->second != unknown020) {
        GfObjUtil::destroy(enemy->second);
      }
    }
    unknown78.destroy();
  }
}

void GfRelSmnEnemy::disposeEnemies(bool isFade) {
  disposeWaitEnemies();
  if (!unknowna0.empty()) {
    for (GF_OBJ_HANDLE **enemy = unknowna0.begin(), **end = unknowna0.end(); enemy != end; ++enemy) {
      if (*enemy != unknown020) {
        if (isFade) {
          SCOM_DESTROY_GAME_OBJ::create(*enemy, 0.5f, 0);
        } else {
          GfObjUtil::destroy(*enemy);
        }
      }
    }
    unknowna0.destroy();
  }
}

void GfRelSmnEnemy::debugDraw() const {
  if (unknown10.unknown00 != unknown020 && unknown10.unknown08 > 0) {
    GfObjAcc acc(unknown10.unknown00);
    if (acc.getObj() != nullptr) {
      mm::Mat44 matrix;
      acc.getWorldTransform().unknown001(matrix);
      matrix.rows[3][1] += 0.1f;
      fw::debug::drawCircleLine(matrix, unknown40, mm::Col4::blue);
      fw::debug::drawCircleLine(matrix, unknown44, mm::Col4::red);
    }
  }
}

void GfRelSmnEnemy::updateDepopEnemy() {
  if (!unknowna0.empty()) {
    for (GF_OBJ_HANDLE **enemy = unknowna0.begin(), **end = unknowna0.end(); enemy != end; ++enemy) {
      GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(*enemy);
      if (0.0f < unknown48.unknown00 && 0.0f < unknown48.unknown04 && !unknown48.isMatch(setup->unknown20)) {
        unknowna0.erase(enemy);
        SCOM_DESTROY_GAME_OBJ::create(*enemy, 0.5f, 0);
        return;
      }
    }
  }
}

void GfRelSmnEnemy::removeEnemy(GF_OBJ_HANDLE *handle) {
  if (!unknown78.empty()) {
    for (std::pair<PopInfo *, GF_OBJ_HANDLE *> *enemy = unknown78.begin(), *end = unknown78.end(); enemy != end; ++enemy) {
      if (enemy->second == handle) {
        unknown78.erase(enemy);
        return;
      }
    }
  }
  if (!unknowna0.empty()) {
    GF_OBJ_HANDLE **enemy = std::find(unknowna0.begin(), unknowna0.end(), handle);
    if (enemy != unknowna0.end()) {
      unknowna0.erase(enemy);
    }
  }
}

GfSmnEnemyManager::GfSmnEnemyManager() {
  unknown08.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown08.reserve(CAPACITY_UNKNOWN_40);
}

GfSmnEnemyManager::~GfSmnEnemyManager() {
  clearSmnEnemies();
  get()->unknown08.destroy();
}

void GfSmnEnemyManager::clearSmnEnemies() {
  GfSmnEnemyManager *manager = get();
  if (manager != nullptr) {
    if (manager->unknown08.size() != 0) {
      for (GfRelSmnEnemy **enemy = manager->unknown08.begin(), **end = manager->unknown08.end(); enemy != end; ++enemy) {
        if (*enemy != nullptr) {
          delete *enemy;
        }
      }
      get()->unknown08.clear();
    }
    for (GF_OBJ_HANDLE *handle : *GfGameObj::getList(OBJECT_TYPE_ENEMY)) {
      gmk::AGmkBase *gmk = gmk::getBindedGmkInst(handle);
      if (gmk != nullptr && gmk->getGmkType() == gmk::GMK_TYPE_ENEMY && static_cast<gmk::GmkEnemy *>(gmk)->unknown48.unknown38.unknown03) {
        GfObjUtil::destroy(handle);
      }
    }
  }
}

void GfSmnEnemyManager::create() {
  dispose();
  // __LINE__ must be 716 as in the original file: its value changes the instruction order.
#line 716
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfSmnEnemyManager();
}

void GfSmnEnemyManager::dispose() {
  if (get() != nullptr) {
    delete get();
  }
}

void GfSmnEnemyManager::update(f32 deltaTime) {
  if (get() != nullptr) {
    for (GfRelSmnEnemy **enemy = get()->unknown08.begin(); enemy != get()->unknown08.end(); ++enemy) {
      GfRelSmnEnemy *smnEnemy = *enemy;
      smnEnemy->update(deltaTime);
      if (smnEnemy->unknown10.unknown00 != unknown020 && smnEnemy->unknown10.unknown08 > 0) {
        continue;
      }
      delete smnEnemy;
      enemy = get()->unknown08.erase(enemy) - 1;
    }
  }
}

namespace {

// Inferred role: asks the summoned enemy gimmicks around a position to pop their enemies; original name unknown.
struct unknown004 {
  void onTraverse(const gmk::AGmkBase &gmk) {
    if (!gmk.isValid()) {
      return;
    }
    const gmk::GmkEnemy &enemy = static_cast<const gmk::GmkEnemy &>(gmk);
    if (!enemy.unknown48.unknown38.unknown03) {
      return;
    }
    mm::Vec3 distance = unknown00 - enemy.unknown08.unknown08->unknown00;
    if (unknown08 < distance.x * distance.x + distance.y * distance.y + distance.z * distance.z) {
      return;
    }
    if (enemy.unknown48.unknown38.isPopCondMatchedOfSmn()) {
      gmk::ForcePopEnemyInfo info;
      info.unknown00 = unknown0c;
      enemy.unknown48.reqForcePopGobInst(info);
    }
  }

  const mm::Vec3 &unknown00; // Inferred role: summon position; original member name unknown.
  f32 unknown08;             // Inferred role: squared summon radius; original member name unknown.
  u8 unknown0c;              // Inferred role: enemy genus; original member name unknown.
};

} // namespace

bool GfSmnEnemyManager::execAbsSummon(const AbsSmnInfo &info) {
  GfObj *owner = GfObjUtil::getObj(info.unknown00);
  if (owner == nullptr) {
    return false;
  }
  GfComTransform *transform = owner->getComponent<GfComTransform>();
  if (transform == nullptr) {
    return false;
  }
  const mm::Vec3 &position = transform->getPosition();
  f32 radiusSq = info.unknown08 * info.unknown08;
  for (GF_OBJ_HANDLE *handle : *GfGameObj::getList(OBJECT_TYPE_ENEMY)) {
    if (info.unknown0c != 0) {
      DataParamAcc paramAcc(handle);
      if (!paramAcc.isValid()) {
        continue;
      }
      // Decision 2026-11-14 #12: the game keeps the accessor's data in a local across the destructor of paramAcc (csel w24, wzr, w28, eq then cbnz w24); testing it in the `if` duplicates the
      // destructor call (206 instructions instead of 207).
      const SDataEnemy *data = paramAcc.getSDataEnemy();
      if (data->unknown99 != info.unknown0c) {
        continue;
      }
    }
    GfObjAcc acc(handle);
    GfObj *obj = acc.getObj();
    if (obj == nullptr) {
      continue;
    }
    GfComBehaviorEnemy *behavior = obj->getComponent<GfComBehaviorEnemy>();
    if (behavior == nullptr) {
      continue;
    }
    mm::Vec3 distance = position - acc.getWorldTransformNoSync().unknown00;
    if (radiusSq < distance.x * distance.x + distance.y * distance.y + distance.z * distance.z) {
      continue;
    }
    behavior->reqChangeBattle();
  }
  unknown004 traverser = {position, radiusSq, info.unknown0c};
  return gmk::GmkManager::get()->traverseGmkInst(gmk::GMK_TYPE_ENEMY, traverser);
}

bool GfSmnEnemyManager::execRelSummon(const RelSmnInfo &info) {
  if (get()->unknown08.capacity() > get()->unknown08.size()) {
    GfRelSmnEnemy::CreateInfo createInfo;
    createInfo.unknown00 = info.unknown00;
    createInfo.unknown08 = info.unknown08;
    GfRelSmnEnemy *enemy = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfRelSmnEnemy(&createInfo);
    get()->unknown08.push_back(enemy);
    return true;
  }
  return false;
}

void GfSmnEnemyManager::debugDraw() {
  GfSmnEnemyManager *manager = get();
  if (manager != nullptr) {
    for (GfRelSmnEnemy **enemy = manager->unknown08.begin(), **end = manager->unknown08.end(); enemy != end; ++enemy) {
      (*enemy)->debugDraw();
    }
  }
}

void GfRelSmnEnemy::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (event == OBJEVT_UNKNOWN_3) {
    removeEnemy(handle);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfSmnEnemyManager>::~PtrSingleton();

template void mm::mtl::Vector<gf::GF_OBJ_HANDLE *>::expand(size_t, size_t);
template gf::GfRelSmnEnemy **mm::mtl::Vector<gf::GfRelSmnEnemy *>::erase(gf::GfRelSmnEnemy **);
template void mm::mtl::Vector<gf::GfRelSmnEnemy *>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfRelSmnEnemy::PopInfo>::push_back(const gf::GfRelSmnEnemy::PopInfo &);
template void mm::mtl::Vector<gf::GfRelSmnEnemy::PopInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<std::pair<gf::GfRelSmnEnemy::PopInfo *, gf::GF_OBJ_HANDLE *>>::expand(size_t, size_t);
