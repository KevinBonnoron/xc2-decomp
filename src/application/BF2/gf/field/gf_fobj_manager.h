#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFobjManager : public mm::mtl::PtrSingleton<GfFobjManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);
  static bool isExistObj();
  static void destroyObj();
};

} // namespace gf
