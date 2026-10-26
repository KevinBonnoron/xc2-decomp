#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfChainAttack : public mm::mtl::PtrSingleton<GfChainAttack> {
public:
  void update(const fw::UpdateInfo &info);
  void startSetup();
  static void destroy();
};

} // namespace gf
