#pragma once
#include "fw/fw_camera.h" // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {
struct GF_OBJ_HANDLE;
class GfArtsMovie;
class GfTrinityAttack;
} // namespace gf

namespace btl {

class SpAttackManager : public mm::mtl::PtrSingleton<SpAttackManager> {
public:
  enum MOVIE_STEP {
    MOVIE_STEP_NONE,
    MOVIE_STEP_WAIT_ANIMATION,
    MOVIE_STEP_CREATE,
    MOVIE_STEP_LOAD,
    MOVIE_STEP_PLAY,
    MOVIE_STEP_END,
  };

  struct PROC_DATA {
    bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;

    gf::GfArtsMovie *unknown00;     // Inferred role: movie; original member name unknown.
    gf::GfTrinityAttack *unknown08; // Inferred role: trinity attack; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown10;   // Inferred role: driver handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown18;   // Inferred role: blade handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown20;   // Inferred role: target handle; original member name unknown.
    u8 _28[0x53 - 0x28];
    u8 unknown53; // Inferred role: movie step; original member name unknown.
    u8 _54[0x5a - 0x54];
    u8 unknown5a; // Inferred role: slot; original member name unknown.
    u8 _5b[0x5c - 0x5b];
    u8 : 2;
    u8 unknown5c_2 : 1; // Inferred role: update attack data; original member name unknown.
    u8 unknown5c_3 : 1; // Inferred role: last attack driver; original member name unknown.
    u8 : 2;
    u8 unknown5c_6 : 1; // Inferred role: display third character; original member name unknown.
  };

  ~SpAttackManager();
  static void Destroy();
  void Finalize();
  void NotifyMapChange();
  void DeleteCamera(bool isFade);
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;
  void FinishUpdateAttackData(gf::GF_OBJ_HANDLE *handle);
  int GetSpAttackSlot(gf::GF_OBJ_HANDLE *handle) const;
  gf::GF_OBJ_HANDLE *GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const;
  bool IsLastAttackDriver(gf::GF_OBJ_HANDLE *handle) const;
  bool IsTrinityAttack(gf::GF_OBJ_HANDLE *handle) const;
  bool IsDispThirdChr() const;
  bool IsMovie() const;

  const PROC_DATA *GetProcDataConst(gf::GF_OBJ_HANDLE *handle) const {
    int num = unknown208;
    for (int i = 0; i < num; i++) {
      if (unknown28[i].IsRegister(handle)) {
        return &unknown28[i];
      }
    }

    return nullptr;
  }

  mm::mtl::IntrusivePtr<fw::Camera> unknown08; // Inferred role: camera; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown10;                // Inferred role: driver handle; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown18;                // Inferred role: blade handle; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown20;                // Inferred role: target handle; original member name unknown.
  PROC_DATA unknown28[5];                      // Inferred role: procs; original member name unknown.
  int unknown208;                              // Inferred role: proc count; original member name unknown.
  u32 unknown20c;                              // Inferred role: fade out; original member name unknown.
  u8 unknown210;                               // Inferred role: fade frame; original member name unknown.
};

static_assert(sizeof(SpAttackManager::PROC_DATA) == 0x60, "");
static_assert(offsetof(SpAttackManager::PROC_DATA, unknown53) == 0x53, "");
static_assert(offsetof(SpAttackManager::PROC_DATA, unknown5a) == 0x5a, "");
static_assert(offsetof(SpAttackManager, unknown08) == 0x8, "");
static_assert(offsetof(SpAttackManager, unknown28) == 0x28, "");
static_assert(offsetof(SpAttackManager, unknown10) == 0x10, "");
static_assert(offsetof(SpAttackManager, unknown208) == 0x208, "");
static_assert(offsetof(SpAttackManager, unknown20c) == 0x20c, "");
static_assert(offsetof(SpAttackManager, unknown210) == 0x210, "");
static_assert(sizeof(SpAttackManager) == 0x218, "");

} // namespace btl
