#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfReqParam;
struct GfSetupParam;

class GfReqManager : public mm::mtl::PtrSingleton<GfReqManager> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  void update(const fw::UpdateInfo &info);
  static bool isExistCommand(void (*command)(const GfReqParam *param));
};

} // namespace gf
