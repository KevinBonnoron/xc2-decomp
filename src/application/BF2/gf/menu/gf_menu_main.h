#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuMain : public mm::mtl::PtrSingleton<GfMenuMain> {
public:
  GfMenuMain(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuMain() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void setDisp(bool disp);
  static bool isDisp();

  bool initialized;
};

static_assert(offsetof(GfMenuMain, initialized) == 0x08, "");
static_assert(sizeof(GfMenuMain) == 0x10, "");

} // namespace gf
