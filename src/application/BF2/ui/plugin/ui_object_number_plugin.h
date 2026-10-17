#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectNumberPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  static UIObjectNumberPlugin *create(u32 handle);
  void setMin(int min);
  void setMax(int max);
  void setNumber(int number);
  void setInterpolate(f32 time);

  int number;
  int min;
  int max;
  u8 _88[0x89 - 0x88];
  bool isReverse;
};

static_assert(offsetof(UIObjectNumberPlugin, number) == 0x7c, "");
static_assert(offsetof(UIObjectNumberPlugin, min) == 0x80, "");
static_assert(offsetof(UIObjectNumberPlugin, max) == 0x84, "");
static_assert(offsetof(UIObjectNumberPlugin, isReverse) == 0x89, "");

} // namespace ui
