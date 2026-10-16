#include "battle/hate_ring_manager.h"

#include "gf/game/gf_game_party.h"
#include "gf/object/gf_obj_handle.h"

namespace btl {

constexpr int HATE_TARGET_NUM = 3;
constexpr int HATE_ENEMY_NUM_SHIFT = 10;

HateRingManager::~HateRingManager() {}

void HateRingManager::Initialize() {}

void HateRingManager::PreUpdate(const fw::UpdateInfo &updateInfo) { get()->PreUpdateProc(updateInfo); }

void HateRingManager::PreUpdateProc(const fw::UpdateInfo &) {}

void HateRingManager::Update(const fw::UpdateInfo &updateInfo) { get()->UpdateProc(updateInfo); }

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
  u32 nums[HATE_TARGET_NUM] = {};
  const RING_DATA *ring = rings;
  for (int i = 0; i < CHARACTER_COUNT; i++, ring++) {
    if (ring->handle == gf::INVALID_HANDLE) {
      continue;
    }

    int target = ring->target;
    if (target >= 0 && target < HATE_TARGET_NUM) {
      nums[target]++;
    }
  }

  return nums[0] | nums[1] << HATE_ENEMY_NUM_SHIFT | nums[2] << (HATE_ENEMY_NUM_SHIFT * 2);
}

} // namespace btl
