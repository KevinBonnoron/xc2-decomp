#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfGameVisible : public mm::mtl::PtrSingleton<GfGameVisible> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  static void cleanup();
};

} // namespace gf
