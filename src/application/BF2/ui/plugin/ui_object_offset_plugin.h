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

class UIObjectOffsetPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectOffsetPlugin();
  virtual ~UIObjectOffsetPlugin();
  static UIObjectOffsetPlugin *create(u32 handle);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  mm::Pnt<s16> targetPos;
  mm::Pnt<u16> maxOffset;
};

static_assert(offsetof(UIObjectOffsetPlugin, targetPos) == 0x7c, "");
static_assert(offsetof(UIObjectOffsetPlugin, maxOffset) == 0x80, "");
static_assert(sizeof(UIObjectOffsetPlugin) == 0x88, "");

} // namespace ui
