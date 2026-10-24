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

  int unknown7c;                                  // Inferred role: number; original member name unknown.
  int unknown80;                                  // Inferred role: min; original member name unknown.
  int unknown84;                                  // Inferred role: max; original member name unknown.
  u8 unknown88;                                   // Inferred role: type; original member name unknown.
  bool unknown89;                                 // Inferred role: reverse; original member name unknown.
  bool unknown8a;                                 // Inferred role: interpolate; original member name unknown.
  const char *unknown90;                          // Inferred role: format; original member name unknown.
  UICtrlSimple<1> unknown98;                      // Inferred role: interpolation; original member name unknown.
  UICtrlSimpleUpdater<UICtrlSimple<1>> unknownc0; // Inferred role: interpolation updater; original member name unknown.
  f32 unknowne0;                                  // Inferred role: interpolate time; original member name unknown.
};

static_assert(offsetof(UIObjectNumberPlugin, unknown7c) == 0x7c, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown80) == 0x80, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown84) == 0x84, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown88) == 0x88, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown89) == 0x89, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown8a) == 0x8a, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown90) == 0x90, "");
static_assert(offsetof(UIObjectNumberPlugin, unknown98) == 0x98, "");
static_assert(offsetof(UIObjectNumberPlugin, unknownc0) == 0xc0, "");
static_assert(offsetof(UIObjectNumberPlugin, unknowne0) == 0xe0, "");
static_assert(sizeof(UIObjectNumberPlugin) == 0xe8, "");

} // namespace ui
