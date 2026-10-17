#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec2.h"
#include "types.h"
#include "ui/ui_object_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIListInfoBase;

class UIObjectScrollBarPlugin : public UIObjectPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectScrollBarPlugin();
  virtual ~UIObjectScrollBarPlugin();
  static UIObjectScrollBarPlugin *create(u32 handle, u32 direction, const UIListInfoBase *list, const char *barName);
  void setScaleEnable(bool enable);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  const UIListInfoBase *list;
  u32 bar;
  u32 direction;
  mm::Pnt<s16> basePos;
  u8 _34[0x40 - 0x34];
  mm::Vec2 baseScale;
  u8 _48[0x50 - 0x48];
  bool scaleEnable;
  u8 _51[0x60 - 0x51];
};

static_assert(offsetof(UIObjectScrollBarPlugin, list) == 0x20, "");
static_assert(offsetof(UIObjectScrollBarPlugin, bar) == 0x28, "");
static_assert(offsetof(UIObjectScrollBarPlugin, direction) == 0x2c, "");
static_assert(offsetof(UIObjectScrollBarPlugin, basePos) == 0x30, "");
static_assert(offsetof(UIObjectScrollBarPlugin, baseScale) == 0x40, "");
static_assert(offsetof(UIObjectScrollBarPlugin, scaleEnable) == 0x50, "");
static_assert(sizeof(UIObjectScrollBarPlugin) == 0x60, "");

} // namespace ui
