#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/ui_object_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectFitPlugin : public UIObjectPlugin {
public:
  enum Flag {
    FLAG_HALF_SIZE_MARGIN = 1 << 0,
    FLAG_KEEP_SCALE_X = 1 << 1,
    FLAG_KEEP_SCALE_Y = 1 << 2,
  };

  static mm::mtl::RTTI m_rtti;

  UIObjectFitPlugin();
  virtual ~UIObjectFitPlugin();
  static UIObjectFitPlugin *create(u32 handle, u32 target, u16 marginX, u16 marginY);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  mm::Pnt<u16> unknown1c; // Inferred role: margin; original member name unknown.
  mm::Pnt<s16> unknown20; // Inferred role: expand; original member name unknown.
  mm::Pnt<u16> unknown24; // Inferred role: min size; original member name unknown.
  u32 unknown28;          // Inferred role: flags; original member name unknown.
  u32 unknown2c;          // Inferred role: target; original member name unknown.
};

static_assert(offsetof(UIObjectFitPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(UIObjectFitPlugin, unknown20) == 0x20, "");
static_assert(offsetof(UIObjectFitPlugin, unknown24) == 0x24, "");
static_assert(offsetof(UIObjectFitPlugin, unknown28) == 0x28, "");
static_assert(offsetof(UIObjectFitPlugin, unknown2c) == 0x2c, "");
static_assert(sizeof(UIObjectFitPlugin) == 0x30, "");

} // namespace ui
