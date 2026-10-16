#pragma once
#include "battle/character/character_manager_battle.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int HATE_TARGET_COUNT = 3;

class HateRingManager : public mm::mtl::PtrSingleton<HateRingManager> {
public:
  struct RING_DATA {
    RING_DATA() { Reset(false); }
    void Reset(bool isDestroyEffect);

    mm::Vec3 position;
    gf::GF_OBJ_HANDLE *handle;
    int target;
    f32 arrowFrame;
    u32 ringEffect;
    u32 arrowEffect;
    u8 _28[0x30 - 0x28];
  };

  HateRingManager();
  ~HateRingManager();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void UpdateArrow(int id, RING_DATA &ring, f32 time);
  void UpdateRing(int target, mm::Vec3 position, mm::Vec3 direction);
  void SetData(int id, gf::GF_OBJ_HANDLE *handle, int);
  int GetTarget(gf::GF_OBJ_HANDLE *handle) const;
  int GetTarget(int id) const;
  gf::GF_OBJ_HANDLE *GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const;
  gf::GF_OBJ_HANDLE *GetTargetHandle(int id) const;
  int GetHateEnemyNum(int target) const;
  u32 GetHateEnemyNumAll() const;

  u8 _08[0x10 - 0x08];
  RING_DATA rings[CHARACTER_COUNT];
  mm::Vec3 targetRingPositions[HATE_TARGET_COUNT];
  u32 targetRingEffects[HATE_TARGET_COUNT];
  bool isTargetRingUsed[HATE_TARGET_COUNT];
};

static_assert(sizeof(HateRingManager::RING_DATA) == 0x30, "");
static_assert(offsetof(HateRingManager, rings) == 0x10, "");
static_assert(offsetof(HateRingManager, targetRingEffects) == 0x1120, "");
static_assert(sizeof(HateRingManager) == 0x1130, "");

} // namespace btl
