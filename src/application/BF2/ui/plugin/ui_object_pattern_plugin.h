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

class UIObjectPatternPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectPatternPlugin();
  virtual ~UIObjectPatternPlugin();
  static UIObjectPatternPlugin *create(u32 handle);
  void setFacePattern(const char *name);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  u32 facePattern;
};

static_assert(offsetof(UIObjectPatternPlugin, facePattern) == 0x7c, "");
static_assert(sizeof(UIObjectPatternPlugin) == 0x80, "");

} // namespace ui
