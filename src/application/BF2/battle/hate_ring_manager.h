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

    mm::Vec3 unknown00;           // Inferred role: position; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown10; // Inferred role: handle; original member name unknown.
    int unknown18;                // Inferred role: target; original member name unknown.
    f32 unknown1c;                // Inferred role: arrow frame; original member name unknown.
    u32 unknown20;                // Inferred role: ring effect; original member name unknown.
    u32 unknown24;                // Inferred role: arrow effect; original member name unknown.
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
  RING_DATA unknown10[CHARACTER_COUNT];    // Inferred role: rings; original member name unknown.
  mm::Vec3 unknown10f0[HATE_TARGET_COUNT]; // Inferred role: target ring positions; original member name unknown.
  u32 unknown1120[HATE_TARGET_COUNT];      // Inferred role: target ring effects; original member name unknown.
  bool unknown112c[HATE_TARGET_COUNT];     // Inferred role: target ring used; original member name unknown.
};

static_assert(sizeof(HateRingManager::RING_DATA) == 0x30, "");
static_assert(offsetof(HateRingManager, unknown10) == 0x10, "");
static_assert(offsetof(HateRingManager, unknown1120) == 0x1120, "");
static_assert(sizeof(HateRingManager) == 0x1130, "");

} // namespace btl
