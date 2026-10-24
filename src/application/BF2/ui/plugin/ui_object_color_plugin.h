#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectColorPlugin : public UIObjectDispPlugin {
public:
  enum ColorMode {
    COLOR_MODE_MUL = 0,
    COLOR_MODE_ADD = 1,
  };

  static mm::mtl::RTTI m_rtti;

  UIObjectColorPlugin();
  virtual ~UIObjectColorPlugin();
  static UIObjectColorPlugin *create(u32 handle);
  void setMulColor(const mm::Col3 &color);
  void setMulColor(const char *name);
  void setAddColor(const mm::Col3 &color);
  void setAddColor(const char *name);
  void setColorMode(u32 mode);
  void setColor(const mm::Col3 &color);
  void setColor(const char *name);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  mm::Col3 unknown7c; // Inferred role: color; original member name unknown.
  u32 unknown88;      // Inferred role: color mode; original member name unknown.
};

static_assert(offsetof(UIObjectColorPlugin, unknown7c) == 0x7c, "");
static_assert(offsetof(UIObjectColorPlugin, unknown88) == 0x88, "");
static_assert(sizeof(UIObjectColorPlugin) == 0x90, "");

} // namespace ui
