#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuShop : public mm::mtl::PtrSingleton<GfMenuShop> {
public:
  GfMenuShop(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuShop() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void setDisp(bool disp);
  static bool isDisp();

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfMenuShop, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuShop) == 0x10, "");

} // namespace gf
