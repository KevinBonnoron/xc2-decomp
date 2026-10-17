#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfSlowAttack : public mm::mtl::PtrSingleton<GfSlowAttack> {
public:
  void update(const fw::UpdateInfo &info);
  static GfSlowAttack *create();
  static void destroy();
};

} // namespace gf
