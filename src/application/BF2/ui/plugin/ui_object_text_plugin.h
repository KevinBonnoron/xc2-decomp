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

  static UIObjectTextPlugin *create(u32 handle);
  void setText(const UIStr &text);

  UIStr text;
};

static_assert(offsetof(UIObjectTextPlugin, text) == 0x80, "");

} // namespace ui
