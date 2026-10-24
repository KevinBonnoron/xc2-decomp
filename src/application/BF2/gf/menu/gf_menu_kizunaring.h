#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuKizunaring : public mm::mtl::PtrSingleton<GfMenuKizunaring> {
public:
  GfMenuKizunaring(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuKizunaring() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void openMenu(u32 id);
  static void closeMenu();
  static bool isOpenMenu();

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfMenuKizunaring, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuKizunaring) == 0x10, "");

} // namespace gf
