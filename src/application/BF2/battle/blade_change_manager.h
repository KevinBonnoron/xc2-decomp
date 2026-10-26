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
        : unknown00(gf::INVALID_HANDLE), unknown08(gf::INVALID_HANDLE), unknown10(gf::INVALID_HANDLE), unknown40(0), unknown44(0.0f), unknown48(-1), unknown4c(0), unknown50(0), unknown54(0),
          unknown58(0.0f), unknown5c(CHANGE_TYPE_NORMAL), unknown5d(RECEIVE_TYPE_BLADE_CHANGE), unknown5e(true), unknown5f(false), unknown60(false), unknown61(false), unknown62(false),
          unknown63(CANCEL_STATE_ENABLE) {}

    gf::GF_OBJ_HANDLE *unknown00; // Inferred role: driver handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown08; // Inferred role: blade handle; original member name unknown.
    gf::GF_OBJ_HANDLE *unknown10; // Inferred role: blade being changed to; original member name unknown.
    u8 _18[0x40 - 0x18];
    u32 unknown40;  // Inferred role: effect id; original member name unknown.
    f32 unknown44;  // Inferred role: cool time rate; original member name unknown.
    int unknown48;  // Inferred role: change blade index; original member name unknown.
    int unknown4c;  // Inferred role: base blade bdat id; original member name unknown.
    int unknown50;  // Inferred role: progress; original member name unknown.
    int unknown54;  // Inferred role: step; original member name unknown.
    f32 unknown58;  // Inferred role: timer; original member name unknown.
    u8 unknown5c;   // Inferred role: change type; original member name unknown.
    s8 unknown5d;   // Inferred role: receive type; original member name unknown.
    bool unknown5e; // Inferred role: first flag; original member name unknown.
    bool unknown5f; // Inferred role: receive flag; original member name unknown.
    bool unknown60; // Inferred role: driver end flag; original member name unknown.
    bool unknown61; // Inferred role: change blade end flag; original member name unknown.
    bool unknown62; // Inferred role: finish flag; original member name unknown.
    u8 unknown63;   // Inferred role: cancel state; original member name unknown.
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
  void UpdateEffect(PROC_DATA &proc, f32 time);
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
  PROC_DATA unknown10[10]; // Inferred role: procs; original member name unknown.
  int unknown470;          // Inferred role: proc count; original member name unknown.
  int unknown474;          // Inferred role: enable flag; original member name unknown.
  u8 _478[0x480 - 0x478];
};

static_assert(sizeof(BladeChangeManager::PROC_DATA) == 0x70, "");
static_assert(offsetof(BladeChangeManager::PROC_DATA, unknown40) == 0x40, "");
static_assert(offsetof(BladeChangeManager::PROC_DATA, unknown5c) == 0x5c, "");
static_assert(offsetof(BladeChangeManager::PROC_DATA, unknown63) == 0x63, "");
static_assert(offsetof(BladeChangeManager, unknown10) == 0x10, "");
static_assert(offsetof(BladeChangeManager, unknown470) == 0x470, "");
static_assert(sizeof(BladeChangeManager) == 0x480, "");

} // namespace btl
