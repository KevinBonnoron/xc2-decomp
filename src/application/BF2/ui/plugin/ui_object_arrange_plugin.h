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

class UIObjectArrangePlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectArrangePlugin();
  virtual ~UIObjectArrangePlugin();
  static UIObjectArrangePlugin *create(u32 handle);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  bool unknown7c; // Inferred role: arrange; original member name unknown.
};

static_assert(offsetof(UIObjectArrangePlugin, unknown7c) == 0x7c, "");
static_assert(sizeof(UIObjectArrangePlugin) == 0x80, "");

} // namespace ui
