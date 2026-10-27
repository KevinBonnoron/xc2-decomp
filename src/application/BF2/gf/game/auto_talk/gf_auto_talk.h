#pragma once
#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfAutoTalkManager : public mm::mtl::PtrSingleton<GfAutoTalkManager> {
public:
  void create();
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
};

} // namespace gf
