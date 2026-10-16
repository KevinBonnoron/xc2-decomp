#pragma once
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class Camera;
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
  struct PROC_DATA {
    bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;

    gf::GfArtsMovie *movie;
    gf::GfTrinityAttack *trinityAttack;
    gf::GF_OBJ_HANDLE *driver;
    gf::GF_OBJ_HANDLE *blade;
    gf::GF_OBJ_HANDLE *target;
    u8 _28[0x5a - 0x28];
    u8 slot;
    u8 _5b[0x5c - 0x5b];
    u8 : 2;
    u8 isUpdateAttackData : 1;
    u8 isLastAttackDriver : 1;
    u8 : 2;
    u8 isDispThirdChr : 1;
  };

  ~SpAttackManager();
  static void Destroy();
  void Finalize();
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

  const PROC_DATA *GetProcDataConst(gf::GF_OBJ_HANDLE *handle) const {
    int num = procCount;
    for (int i = 0; i < num; i++) {
      if (procs[i].IsRegister(handle)) {
        return &procs[i];
      }
    }

    return nullptr;
  }

  mm::mtl::IntrusivePtr<fw::Camera> camera;
  u8 _10[0x28 - 0x10];
  PROC_DATA procs[5];
  int procCount;
};

static_assert(sizeof(SpAttackManager::PROC_DATA) == 0x60, "");
static_assert(offsetof(SpAttackManager::PROC_DATA, slot) == 0x5a, "");
static_assert(offsetof(SpAttackManager, camera) == 0x8, "");
static_assert(offsetof(SpAttackManager, procs) == 0x28, "");
static_assert(offsetof(SpAttackManager, procCount) == 0x208, "");

} // namespace btl
