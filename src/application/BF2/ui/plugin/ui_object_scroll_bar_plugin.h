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

  const UIListInfoBase *unknown20; // Inferred role: list; original member name unknown.
  u32 unknown28;                   // Inferred role: bar; original member name unknown.
  u32 unknown2c;                   // Inferred role: direction; original member name unknown.
  mm::Pnt<s16> unknown30;          // Inferred role: base pos; original member name unknown.
  u8 _34[0x40 - 0x34];
  mm::Vec2 unknown40; // Inferred role: base scale; original member name unknown.
  u8 _48[0x50 - 0x48];
  bool unknown50; // Inferred role: scale enable; original member name unknown.
  u8 _51[0x60 - 0x51];
};

static_assert(offsetof(UIObjectScrollBarPlugin, unknown20) == 0x20, "");
static_assert(offsetof(UIObjectScrollBarPlugin, unknown28) == 0x28, "");
static_assert(offsetof(UIObjectScrollBarPlugin, unknown2c) == 0x2c, "");
static_assert(offsetof(UIObjectScrollBarPlugin, unknown30) == 0x30, "");
static_assert(offsetof(UIObjectScrollBarPlugin, unknown40) == 0x40, "");
static_assert(offsetof(UIObjectScrollBarPlugin, unknown50) == 0x50, "");
static_assert(sizeof(UIObjectScrollBarPlugin) == 0x60, "");

} // namespace ui
