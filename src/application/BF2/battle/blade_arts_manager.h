#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace btl {

class BladeArtsManager : public mm::mtl::PtrSingleton<BladeArtsManager> {
public:
  ~BladeArtsManager();
  static void Destroy();
  void Finalize();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
};

} // namespace btl
