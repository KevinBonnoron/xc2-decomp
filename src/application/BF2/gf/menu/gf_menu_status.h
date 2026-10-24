#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuStatus : public mm::mtl::PtrSingleton<GfMenuStatus> {
public:
  GfMenuStatus(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuStatus() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfMenuStatus, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuStatus) == 0x10, "");

} // namespace gf
