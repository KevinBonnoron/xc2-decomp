#include "battle/hate_ring_manager.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/misc_battle.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int HATE_ENEMY_NUM_SHIFT = 10;

void HateRingManager::RING_DATA::Reset(bool isDestroyEffect) {
  unknown10 = gf::INVALID_HANDLE;
  unknown18 = -1;
  unknown1c = 0.0f;
  if (isDestroyEffect) {
    if (unknown20 != 0) {
      fw::EffectManager::get()->destroyHateRingVec(unknown20);
    }
    if (unknown24 != 0) {
      fw::EffectManager::get()->destroyHateArrow(unknown24);
    }
  }
  unknown20 = 0;
  unknown24 = 0;
  unknown00 = mm::Vec3::zero;
}

HateRingManager::HateRingManager() {
  for (u32 &effect : unknown1120) {
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
  RING_DATA *ring = unknown10;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    ring->Reset(true);
  }
}

void HateRingManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void HateRingManager::PreUpdateProc(const fw::UpdateInfo &) {}

void HateRingManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

void HateRingManager::UpdateProc(const fw::UpdateInfo &updateInfo) {
  for (bool &isUsed : unknown112c) {
    isUsed = false;
  }

  if (BattleGlobal::get()->IsEnableBattle()) {
    RING_DATA *ring = unknown10;
    for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
      if (ring->unknown10 == gf::INVALID_HANDLE) {
        continue;
      }
      BattleCharacter *character = CharacterManager::get()->GetCharacterConst(i);
      if (character == nullptr || character->IsDead(0)) {
        ring->Reset(true);
      } else {
        unknown112c[ring->unknown18] = true;
      }
    }
    for (int i = 0; i < HATE_TARGET_COUNT; i++) {
      if (!unknown112c[i] && unknown1120[i] != 0) {
        fw::EffectManager::get()->destroyHateRing(unknown1120[i]);
        unknown1120[i] = 0;
      }
    }
  }

  RING_DATA *ring = unknown10;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    UpdateArrow(i, *ring, updateInfo.unknown04);
  }
}

void HateRingManager::UpdateRing(int target, mm::Vec3 position, mm::Vec3 direction) {
  unknown10f0[target] = position;
  fw::EffectManager *effectManager = fw::EffectManager::get();
  u32 effect = unknown1120[target];
  if (unknown112c[target]) {
    if (effect != 0 || (effect = effectManager->createHateRing()) != 0) {
      f32 rotation = Misc::CalcRotY(direction);
      effectManager->updateHateRing(unknown1120[target], position, rotation, unknown112c[target], 1.0f);
    }
  } else if (effect != 0) {
    effectManager->destroyHateRing(effect);
    effect = 0;
  }
  unknown1120[target] = effect;
}

int HateRingManager::GetTarget(gf::GF_OBJ_HANDLE *handle) const {
  const RING_DATA *ring = unknown10;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->unknown10 == handle) {
      return ring->unknown18;
    }
  }

  return -1;
}

int HateRingManager::GetTarget(int id) const { return unknown10[id].unknown18; }

gf::GF_OBJ_HANDLE *HateRingManager::GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const { return gf::GfGameParty::getHandleDriver(GetTarget(handle)); }

gf::GF_OBJ_HANDLE *HateRingManager::GetTargetHandle(int id) const { return gf::GfGameParty::getHandleDriver(GetTarget(id)); }

int HateRingManager::GetHateEnemyNum(int target) const {
  int num = 0;
  const RING_DATA *ring = unknown10;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->unknown10 != gf::INVALID_HANDLE && ring->unknown18 == target) {
      num++;
    }
  }

  return num;
}

u32 HateRingManager::GetHateEnemyNumAll() const {
  u32 nums[HATE_TARGET_COUNT] = {};
  const RING_DATA *ring = unknown10;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->unknown10 == gf::INVALID_HANDLE) {
      continue;
    }

    int target = ring->unknown18;
    if (target >= 0 && target < HATE_TARGET_COUNT) {
      nums[target]++;
    }
  }

  return nums[0] | nums[1] << HATE_ENEMY_NUM_SHIFT | nums[2] << (HATE_ENEMY_NUM_SHIFT * 2);
}

} // namespace btl
