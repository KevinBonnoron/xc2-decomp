#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectPosPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectPosPlugin();
  virtual ~UIObjectPosPlugin();
  static UIObjectPosPlugin *create(u32 handle, s16 x, s16 y);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  mm::Pnt<s16> pos;
  bool isAdjustScreen;
  u16 adjustWidth;
  u16 adjustHeight;
  s16 adjustOffsetX;
  s16 adjustOffsetY;
  u32 offsetMode;
  bool adjusting;
};

static_assert(offsetof(UIObjectPosPlugin, pos) == 0x7c, "");
static_assert(offsetof(UIObjectPosPlugin, isAdjustScreen) == 0x80, "");
static_assert(offsetof(UIObjectPosPlugin, adjustWidth) == 0x82, "");
static_assert(offsetof(UIObjectPosPlugin, adjustOffsetX) == 0x86, "");
static_assert(offsetof(UIObjectPosPlugin, offsetMode) == 0x8c, "");
static_assert(offsetof(UIObjectPosPlugin, adjusting) == 0x90, "");
static_assert(sizeof(UIObjectPosPlugin) == 0x98, "");

} // namespace ui
