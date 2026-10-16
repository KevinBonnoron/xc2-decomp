#pragma once
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

class UIManager : public mm::mtl::PtrSingleton<UIManager> {
public:
  ~UIManager();
  void Initialize();
  static void Destroy();
  void Finalize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void RegisterRescueUI(gf::GF_OBJ_HANDLE *handle);

  u8 _08[0x20 - 0x08];
  gf::GF_OBJ_HANDLE *rescueTarget;
};

static_assert(offsetof(UIManager, rescueTarget) == 0x20, "");

} // namespace btl
