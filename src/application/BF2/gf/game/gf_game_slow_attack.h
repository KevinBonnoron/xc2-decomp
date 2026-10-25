#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfSlowAttack : public mm::mtl::PtrSingleton<GfSlowAttack> {
public:
  void update(const fw::UpdateInfo &info);
  f32 getPlaySpeed() const;
  static GfSlowAttack *create();
  static void destroy();
};

} // namespace gf
