#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuPrecious : public mm::mtl::PtrSingleton<GfMenuPrecious> {
public:
  GfMenuPrecious(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuPrecious() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void setDisp(bool disp, u32 type);
  static bool isDisp();

  bool initialized;
};

static_assert(offsetof(GfMenuPrecious, initialized) == 0x08, "");
static_assert(sizeof(GfMenuPrecious) == 0x10, "");

} // namespace gf
