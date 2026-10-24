#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuEquip : public mm::mtl::PtrSingleton<GfMenuEquip> {
public:
  GfMenuEquip(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuEquip() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void setDisp(bool disp);
  static bool isDisp();

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfMenuEquip, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuEquip) == 0x10, "");

} // namespace gf
