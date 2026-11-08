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
  GfMenuObjFade(u32 handle);
  ~GfMenuObjFade() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void dispLoading(bool disp, u16 type);
  static void dispSaving(bool disp, u16 type);
  static void getFadeColor(u8 type, mm::Col4 &color);

  u32 unknown24;  // Role and original member name unknown, zeroed by the constructor.
  bool unknown28; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjFade, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjFade, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjFade) == 0x30, "");

} // namespace gf
