#pragma once
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

  static UIObjectPatternPlugin *create(u32 handle);
  void setFacePattern(const char *name);
};

} // namespace ui
