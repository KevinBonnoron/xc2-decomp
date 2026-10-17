#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectNumberPlugin : public UIObjectDispPlugin {
public:
  enum Type {
    TYPE_NONE = 0,
    TYPE_TEXT = 1,
    TYPE_TEXT_STRING = 2,
    TYPE_IMAGE = 3,
    TYPE_EXT = 4,
  };

  static mm::mtl::RTTI m_rtti;
  static char s_MoneySeparetor;

  UIObjectNumberPlugin();
  virtual ~UIObjectNumberPlugin();
  static UIObjectNumberPlugin *create(u32 handle);
  static UIObjectNumberPlugin *createExt(u32 handle, u32 extType);
  static UIObjectNumberPlugin *getPlugin(u32 handle);
  void setMin(int min);
  void setMax(int max);
  void setNumber(int number);
  void setInterpolate(f32 time);
  virtual void reload(UIObjectAcc &acc);
  static void refreshMoneySeparetor();
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  int number;
  int min;
  int max;
  u8 type;
  bool isReverse;
  bool interpolate;
  const char *format;
  UICtrlSimple<1> interpolation;
  UICtrlSimpleUpdater<UICtrlSimple<1>> interpolationUpdater;
  f32 interpolateTime;
};

static_assert(offsetof(UIObjectNumberPlugin, number) == 0x7c, "");
static_assert(offsetof(UIObjectNumberPlugin, min) == 0x80, "");
static_assert(offsetof(UIObjectNumberPlugin, max) == 0x84, "");
static_assert(offsetof(UIObjectNumberPlugin, type) == 0x88, "");
static_assert(offsetof(UIObjectNumberPlugin, isReverse) == 0x89, "");
static_assert(offsetof(UIObjectNumberPlugin, interpolate) == 0x8a, "");
static_assert(offsetof(UIObjectNumberPlugin, format) == 0x90, "");
static_assert(offsetof(UIObjectNumberPlugin, interpolation) == 0x98, "");
static_assert(offsetof(UIObjectNumberPlugin, interpolationUpdater) == 0xc0, "");
static_assert(offsetof(UIObjectNumberPlugin, interpolateTime) == 0xe0, "");
static_assert(sizeof(UIObjectNumberPlugin) == 0xe8, "");

} // namespace ui
