#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/ui_object_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectDockPlugin : public UIObjectPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectDockPlugin(u32 target);
  virtual ~UIObjectDockPlugin();
  static UIObjectDockPlugin *create(u32 handle, s16 offsetX, s16 offsetY, u32 target);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  u32 unknown1c;           // Inferred role: target; original member name unknown.
  mm::Pnt<s16> unknown20;  // Inferred role: offset; original member name unknown.
  u32 unknown24;           // Inferred role: dock type; original member name unknown.
  u32 unknown28;           // Inferred role: align type; original member name unknown.
  u32 unknown2c;           // Inferred role: reverse; original member name unknown.
  mm::Rect<s16> unknown30; // Inferred role: area; original member name unknown.
};

static_assert(offsetof(UIObjectDockPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(UIObjectDockPlugin, unknown20) == 0x20, "");
static_assert(offsetof(UIObjectDockPlugin, unknown24) == 0x24, "");
static_assert(offsetof(UIObjectDockPlugin, unknown28) == 0x28, "");
static_assert(offsetof(UIObjectDockPlugin, unknown2c) == 0x2c, "");
static_assert(offsetof(UIObjectDockPlugin, unknown30) == 0x30, "");
static_assert(sizeof(UIObjectDockPlugin) == 0x38, "");

} // namespace ui
