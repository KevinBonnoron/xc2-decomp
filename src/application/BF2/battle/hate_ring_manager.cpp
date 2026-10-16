#include "battle/hate_ring_manager.h"

#include "battle/misc_battle.h"
#include "framework/effect/effect_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int HATE_ENEMY_NUM_SHIFT = 10;

void HateRingManager::RING_DATA::Reset(bool isDestroyEffect) {
  handle = gf::INVALID_HANDLE;
  target = -1;
  arrowFrame = 0.0f;
  if (isDestroyEffect) {
    if (ringEffect != 0) {
      fw::EffectManager::get()->destroyHateRingVec(ringEffect);
    }
    if (arrowEffect != 0) {
      fw::EffectManager::get()->destroyHateArrow(arrowEffect);
    }
  }
  ringEffect = 0;
  arrowEffect = 0;
  position = mm::Vec3::zero;
}

HateRingManager::HateRingManager() {
  for (u32 &effect : targetRingEffects) {
    effect = 0;
  }
}

HateRingManager::~HateRingManager() {}

void HateRingManager::Create() {
  // __LINE__ must be 91 as in the original file: it is an argument of operator new.
#line 91
  HateRingManager *manager = new (gf::getAllocator(gf::ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) HateRingManager();
  manager->Initialize();
}

void HateRingManager::Initialize() {}

void HateRingManager::Destroy() {
  HateRingManager *manager = get();
  manager->Finalize();
  if (manager != nullptr) {
    delete manager;
  }
}

void HateRingManager::Finalize() {
  RING_DATA *ring = rings;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    ring->Reset(true);
  }
}

void HateRingManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void HateRingManager::PreUpdateProc(const fw::UpdateInfo &) {}

void HateRingManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void HateRingManager::UpdateRing(int target, mm::Vec3 position, mm::Vec3 direction) {
  targetRingPositions[target] = position;
  fw::EffectManager *effectManager = fw::EffectManager::get();
  u32 effect = targetRingEffects[target];
  if (isTargetRingUsed[target]) {
    if (effect != 0 || (effect = effectManager->createHateRing()) != 0) {
      f32 rotation = Misc::CalcRotY(direction);
      effectManager->updateHateRing(targetRingEffects[target], position, rotation, isTargetRingUsed[target], 1.0f);
    }
  } else if (effect != 0) {
    effectManager->destroyHateRing(effect);
    effect = 0;
  }
  targetRingEffects[target] = effect;
}

int HateRingManager::GetTarget(gf::GF_OBJ_HANDLE *handle) const {
  const RING_DATA *ring = rings;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->handle == handle) {
      return ring->target;
    }
  }

  return -1;
}

int HateRingManager::GetTarget(int id) const { return rings[id].target; }

gf::GF_OBJ_HANDLE *HateRingManager::GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const { return gf::GfGameParty::getHandleDriver(GetTarget(handle)); }

gf::GF_OBJ_HANDLE *HateRingManager::GetTargetHandle(int id) const { return gf::GfGameParty::getHandleDriver(GetTarget(id)); }

int HateRingManager::GetHateEnemyNum(int target) const {
  int num = 0;
  const RING_DATA *ring = rings;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->handle != gf::INVALID_HANDLE && ring->target == target) {
      num++;
    }
  }

  return num;
}

u32 HateRingManager::GetHateEnemyNumAll() const {
  u32 nums[HATE_TARGET_COUNT] = {};
  const RING_DATA *ring = rings;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->handle == gf::INVALID_HANDLE) {
      continue;
    }

    int target = ring->target;
    if (target >= 0 && target < HATE_TARGET_COUNT) {
      nums[target]++;
    }
  }

  return nums[0] | nums[1] << HATE_ENEMY_NUM_SHIFT | nums[2] << (HATE_ENEMY_NUM_SHIFT * 2);
}

} // namespace btl
