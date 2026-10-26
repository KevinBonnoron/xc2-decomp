#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

class GfArtsMovie : public mm::mtl::PtrSingleton<GfArtsMovie> {
public:
  void update(const fw::UpdateInfo &info);
  void startSetup(const char *name);
  static void destroy();
};

} // namespace gf
