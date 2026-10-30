#pragma once
#include <stddef.h>

#include "mm_mtl/bitflag.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_simple.h"
#include "ui/ui_object_param.h"
#include "ui/ui_object_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectAlphaParam : public UIObjectParam {
public:
  UIObjectAlphaParam(u32 handle) : UIObjectParam(handle) {}
  virtual void apply(AdditionalParam &param) const;

  f32 unknown1c; // Inferred role: alpha; original member name unknown.
};

static_assert(offsetof(UIObjectAlphaParam, unknown1c) == 0x1c, "");
static_assert(sizeof(UIObjectAlphaParam) == 0x20, "");

class UIObjectDispPlugin : public UIObjectPlugin {
public:
  enum Mode {
    MODE_ALPHA = 0,
    MODE_REVERSE = 1,
    MODE_FADE = 2,
    MODE_SUSPEND = 3,
  };

  static mm::mtl::RTTI m_rtti;

  UIObjectDispPlugin();
  virtual ~UIObjectDispPlugin();
  void setDisp(bool disp);
  void setAlphaMode(bool alphaMode);
  void setReverseMode(bool reverseMode);
  void setSuspendMode(bool suspendMode);
  void setDispControl(bool dispControl);
  void setFollowObjHandle(u32 handle);
  void setFadeMode(f32 fadeTime);
  static UIObjectDispPlugin *create(u32 handle);
  void init(u32 handle);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  bool unknown1c;                    // Inferred role: disp control; original member name unknown.
  bool unknown1d;                    // Inferred role: disp; original member name unknown.
  mm::mtl::unknown027<32> unknown20; // Inferred role: mode flags; original member name unknown.
  u32 m_followObjHandle;
  UIObjectAlphaParam *unknown28;                  // Inferred role: alpha param; original member name unknown.
  UICtrlSimple<1> unknown30;                      // Inferred role: fade; original member name unknown.
  UICtrlSimpleUpdater<UICtrlSimple<1>> unknown58; // Inferred role: fade updater; original member name unknown.
  f32 unknown78;                                  // Inferred role: fade time; original member name unknown.
};

static_assert(offsetof(UIObjectDispPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(UIObjectDispPlugin, unknown1d) == 0x1d, "");
static_assert(offsetof(UIObjectDispPlugin, unknown20) == 0x20, "");
static_assert(offsetof(UIObjectDispPlugin, m_followObjHandle) == 0x24, "");
static_assert(offsetof(UIObjectDispPlugin, unknown28) == 0x28, "");
static_assert(offsetof(UIObjectDispPlugin, unknown30) == 0x30, "");
static_assert(offsetof(UIObjectDispPlugin, unknown58) == 0x58, "");
static_assert(offsetof(UIObjectDispPlugin, unknown78) == 0x78, "");
static_assert(sizeof(UIObjectDispPlugin) == 0x80, "");

} // namespace ui
