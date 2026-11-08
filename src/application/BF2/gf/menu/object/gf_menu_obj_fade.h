#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace gf {

class GfMenuObjFade : public GfMenuObject {
public:
  struct StartParam {
    u8 unknown00;  // Inferred role: fade layer index (IMG_fade%02d); original member name unknown.
    u16 unknown02; // Inferred role: event parameter, copied as is; original member name unknown.
    f32 unknown04; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
    f32 unknown08; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
    f32 unknown0c; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
    f32 unknown10; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
  };

  GfMenuObjFade(u32 handle);
  ~GfMenuObjFade() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void dispLoading(bool disp, u16 type);
  static void dispSaving(bool disp, u16 type);
  static void start(const StartParam &param);
  static void getFadeColor(u8 type, mm::Col4 &color);

  u32 unknown24;  // Role and original member name unknown, zeroed by the constructor.
  bool unknown28; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjFade::StartParam, unknown02) == 0x02, "");
static_assert(offsetof(GfMenuObjFade::StartParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjFade::StartParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjFade::StartParam) == 0x14, "");

static_assert(offsetof(GfMenuObjFade, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjFade, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjFade) == 0x30, "");

} // namespace gf
