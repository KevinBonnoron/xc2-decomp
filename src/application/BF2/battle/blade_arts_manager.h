#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace fw {
struct UpdateInfo;
}

namespace btl {

class BladeArtsManager : public mm::mtl::PtrSingleton<BladeArtsManager> {
public:
  enum STATE {
    STATE_NONE,
    STATE_ATTACK = 4,
    STATE_FINISH = 7,
  };

  enum PROGRESS_ID {
    PROGRESS_ID_NONE,
  };

  struct PROC_DATA {
    PROC_DATA() : unknown00(gf::INVALID_HANDLE), unknown08(gf::INVALID_HANDLE), unknown10(gf::INVALID_HANDLE), unknown18(-1), unknown1c(STATE_NONE), unknown20(0.0f), unknown24(false) {}

    gf::GF_OBJ_HANDLE *unknown00; // Inferred role: driver handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown08; // Inferred role: blade handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown10; // Inferred role: target handle; original member name unknown.
    int unknown18;                // Inferred role: arts id; original member name unknown.
    int unknown1c;                // Inferred role: state; original member name unknown.
    f32 unknown20;                // Inferred role: time; original member name unknown.
    bool unknown24;               // Inferred role: button challenge flag; original member name unknown.
  };

  BladeArtsManager();
  ~BladeArtsManager();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  void NotifyMapChange();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  void FinishBladeArts(gf::GF_OBJ_HANDLE *handle);
  bool NotifyProgress(gf::GF_OBJ_HANDLE *handle, PROGRESS_ID progress);
  gf::GF_OBJ_HANDLE *GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const;
  bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;
  bool IsBladeStart(gf::GF_OBJ_HANDLE *handle) const;
  bool IsBladeAttack(gf::GF_OBJ_HANDLE *handle) const;

  PROC_DATA unknown08[10]; // Inferred role: procs; original member name unknown.
  int unknown198;          // Inferred role: proc count; original member name unknown.
};

static_assert(sizeof(BladeArtsManager::PROC_DATA) == 0x28, "");
static_assert(offsetof(BladeArtsManager, unknown08) == 0x08, "");
static_assert(offsetof(BladeArtsManager, unknown198) == 0x198, "");
static_assert(sizeof(BladeArtsManager) == 0x1a0, "");

} // namespace btl
