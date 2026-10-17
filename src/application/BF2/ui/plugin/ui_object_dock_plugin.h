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

  u32 target;
  mm::Pnt<s16> offset;
  u32 dockType;
  u32 alignType;
  u32 reverse;
  mm::Rect<s16> area;
};

static_assert(offsetof(UIObjectDockPlugin, target) == 0x1c, "");
static_assert(offsetof(UIObjectDockPlugin, offset) == 0x20, "");
static_assert(offsetof(UIObjectDockPlugin, dockType) == 0x24, "");
static_assert(offsetof(UIObjectDockPlugin, alignType) == 0x28, "");
static_assert(offsetof(UIObjectDockPlugin, reverse) == 0x2c, "");
static_assert(offsetof(UIObjectDockPlugin, area) == 0x30, "");
static_assert(sizeof(UIObjectDockPlugin) == 0x38, "");

} // namespace ui
