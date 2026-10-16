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

class BladeChangeManager : public mm::mtl::PtrSingleton<BladeChangeManager> {
public:
  enum PROGRESS_ID {};

  enum CHANGE_TYPE {
    CHANGE_TYPE_NORMAL,
    CHANGE_TYPE_HOMURI_FIRST = 3,
    CHANGE_TYPE_HOMURI_LAST = 5,
  };

  enum CANCEL_STATE {
    CANCEL_STATE_DISABLE,
    CANCEL_STATE_ENABLE,
  };

  enum RECEIVE_TYPE {
    RECEIVE_TYPE_BLADE_CHANGE,
    RECEIVE_TYPE_HOMURA_CHANGE,
    RECEIVE_TYPE_NONE,
  };

  struct PROC_DATA {
    PROC_DATA()
        : driver(gf::INVALID_HANDLE), blade(gf::INVALID_HANDLE), changeBlade(gf::INVALID_HANDLE), effect(0), coolTimeRate(0.0f), changeBladeIndex(-1),
          baseBladeBdatId(0), progress(0), step(0), timer(0.0f), changeType(CHANGE_TYPE_NORMAL), receiveType(RECEIVE_TYPE_BLADE_CHANGE),
          isFirst(true), isReceive(false), isDriverEnd(false), isChangeBladeEnd(false), isFinish(false), cancelState(CANCEL_STATE_ENABLE) {}

    gf::GF_OBJ_HANDLE *driver;
    gf::GF_OBJ_HANDLE *blade;
    gf::GF_OBJ_HANDLE *changeBlade;
    u8 _18[0x40 - 0x18];
    u32 effect;
    f32 coolTimeRate;
    int changeBladeIndex;
    int baseBladeBdatId;
    int progress;
    int step;
    f32 timer;
    u8 changeType;
    s8 receiveType;
    bool isFirst;
    bool isReceive;
    bool isDriverEnd;
    bool isChangeBladeEnd;
    bool isFinish;
    u8 cancelState;
    u8 _64[0x70 - 0x64];
  };

  BladeChangeManager();
  ~BladeChangeManager();
  static void Create();
  void Initialize();
  static void Destroy();
  void Finalize();
  void NotifyMapChange();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void FinishBladeChange(gf::GF_OBJ_HANDLE *handle);
  void NotiryProgress(gf::GF_OBJ_HANDLE *handle, PROGRESS_ID progress);
  int GetChangeBladeIndex(gf::GF_OBJ_HANDLE *handle) const;
  int GetBaseBladeBdatID(gf::GF_OBJ_HANDLE *handle) const;
  int GetBladeChangeType(gf::GF_OBJ_HANDLE *handle) const;
  bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;
  bool IsReceiveLater(gf::GF_OBJ_HANDLE *handle) const;
  bool IsProcDisableCancel() const;
  bool IsProcHomuriEnd() const;

  u8 _08[0x10 - 0x08];
  PROC_DATA procs[10];
  int procNum;
  int isEnable;
  u8 _478[0x480 - 0x478];
};

static_assert(sizeof(BladeChangeManager::PROC_DATA) == 0x70, "");
static_assert(offsetof(BladeChangeManager::PROC_DATA, effect) == 0x40, "");
static_assert(offsetof(BladeChangeManager::PROC_DATA, changeType) == 0x5c, "");
static_assert(offsetof(BladeChangeManager::PROC_DATA, cancelState) == 0x63, "");
static_assert(offsetof(BladeChangeManager, procs) == 0x10, "");
static_assert(offsetof(BladeChangeManager, procNum) == 0x470, "");
static_assert(sizeof(BladeChangeManager) == 0x480, "");

} // namespace btl
