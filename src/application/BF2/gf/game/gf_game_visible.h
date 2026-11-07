#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfGameVisible : public mm::mtl::PtrSingleton<GfGameVisible> {
public:
  struct Info;

  static void build(const GfSetupParam &param);
  static void destroy();
  void update(const fw::UpdateInfo &info);
  void updateImpl(const fw::UpdateInfo &info);
  static void cleanup();
  static bool isVisible(GF_OBJ_HANDLE *handle);
};

} // namespace gf
