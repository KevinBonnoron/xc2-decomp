#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfTrinityAttack : public mm::mtl::PtrSingleton<GfTrinityAttack> {
public:
  void update(const fw::UpdateInfo &info);
  static GfTrinityAttack *create();
  static void destroy();
};

} // namespace gf
