#pragma once
#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
struct Col3;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectColorPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  static UIObjectColorPlugin *create(u32 handle);
  void setMulColor(const mm::Col3 &color);
  void setMulColor(const char *name);
  void setAddColor(const char *name);
  void setColorMode(u32 mode);
  void setColor(const char *name);
};

} // namespace ui
