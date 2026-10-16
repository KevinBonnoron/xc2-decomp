#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
struct Col4;
} // namespace mm

namespace ui {
struct EventData;
} // namespace ui

namespace gf {

struct GfSetupParam;

class GfMenuFade : public mm::mtl::PtrSingleton<GfMenuFade> {
public:
  static const u32 FADE_COUNT = 3;

  GfMenuFade(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMenuFade() override;
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void postUpdate(const fw::UpdateInfo &info);
  static void getFadeColor(u32 type, mm::Col4 &color);
  static void setLoading(u32 type, bool disp);
  static bool isFading(u32 type);
  static void reciveEvent(const ui::EventData &event, u32 handle);

  bool initialized;
  bool fading[FADE_COUNT];
};

static_assert(offsetof(GfMenuFade, initialized) == 0x08, "");
static_assert(offsetof(GfMenuFade, fading) == 0x09, "");
static_assert(sizeof(GfMenuFade) == 0x10, "");

} // namespace gf
