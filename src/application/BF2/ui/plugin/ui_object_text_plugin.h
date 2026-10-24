#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"
#include "ui/ui_str.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectTextPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectTextPlugin();
  virtual ~UIObjectTextPlugin();
  static UIObjectTextPlugin *create(u32 handle);
  void setText(const UIStr &text);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  UIStr unknown80; // Inferred role: text; original member name unknown.
};

static_assert(offsetof(UIObjectTextPlugin, unknown80) == 0x80, "");
static_assert(sizeof(UIObjectTextPlugin) == 0x98, "");

} // namespace ui
