#pragma once
#include "battle/character/character_manager_battle.h"
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

class HateRingManager : public mm::mtl::PtrSingleton<HateRingManager> {
public:
  struct RING_DATA {
    u8 _00[0x10 - 0x00];
    gf::GF_OBJ_HANDLE *handle;
    int target;
    u8 _1c[0x30 - 0x1c];
  };

  ~HateRingManager();
  void Initialize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void SetData(int id, gf::GF_OBJ_HANDLE *handle, int);
  int GetTarget(gf::GF_OBJ_HANDLE *handle) const;
  int GetTarget(int id) const;
  gf::GF_OBJ_HANDLE *GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const;
  gf::GF_OBJ_HANDLE *GetTargetHandle(int id) const;
  int GetHateEnemyNum(int target) const;
  u32 GetHateEnemyNumAll() const;

  u8 _08[0x10 - 0x08];
  RING_DATA rings[CHARACTER_COUNT];
};

static_assert(offsetof(HateRingManager, rings) == 0x10, "");

} // namespace btl
