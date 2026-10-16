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

  struct PROC_DATA {
    PROC_DATA()
        : driver(gf::INVALID_HANDLE), blade(gf::INVALID_HANDLE), target(gf::INVALID_HANDLE), arts(-1), state(STATE_NONE), time(0.0f),
          isButtonChallenge(false) {}

    gf::GF_OBJ_HANDLE *driver;
    gf::GF_OBJ_HANDLE *blade;
    gf::GF_OBJ_HANDLE *target;
    int arts;
    int state;
    f32 time;
    bool isButtonChallenge;
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
  gf::GF_OBJ_HANDLE *GetTargetHandle(gf::GF_OBJ_HANDLE *handle) const;
  bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;
  bool IsBladeStart(gf::GF_OBJ_HANDLE *handle) const;
  bool IsBladeAttack(gf::GF_OBJ_HANDLE *handle) const;

  PROC_DATA procs[10];
  int procNum;
};

static_assert(sizeof(BladeArtsManager::PROC_DATA) == 0x28, "");
static_assert(offsetof(BladeArtsManager, procs) == 0x08, "");
static_assert(offsetof(BladeArtsManager, procNum) == 0x198, "");
static_assert(sizeof(BladeArtsManager) == 0x1a0, "");

} // namespace btl
