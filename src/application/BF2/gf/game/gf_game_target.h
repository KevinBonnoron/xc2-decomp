#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfGameTarget : public mm::mtl::PtrSingleton<GfGameTarget> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static void lockTarget(bool isLock);
};

} // namespace gf
