#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

class BladeChangeManager : public mm::mtl::PtrSingleton<BladeChangeManager> {
public:
  enum PROGRESS_ID {};

  ~BladeChangeManager();
  static void Destroy();
  void Finalize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
  void NotiryProgress(gf::GF_OBJ_HANDLE *handle, PROGRESS_ID progress);
  bool IsRegister(gf::GF_OBJ_HANDLE *handle) const;
};

} // namespace btl
