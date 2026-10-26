#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace btl {

class EffectManager : public mm::mtl::PtrSingleton<EffectManager> {
public:
  void Initialize();
  void NotifyMapChange();
  static void PreUpdate(const fw::UpdateInfo &updateInfo);
  void PreUpdateProc(const fw::UpdateInfo &updateInfo);
  static void Update(const fw::UpdateInfo &updateInfo);
  void UpdateProc(const fw::UpdateInfo &updateInfo);
};

} // namespace btl
