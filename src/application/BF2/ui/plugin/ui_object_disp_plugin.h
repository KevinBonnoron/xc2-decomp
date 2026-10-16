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

  f32 alpha;
};

static_assert(offsetof(UIObjectAlphaParam, alpha) == 0x1c, "");
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

  bool dispControl;
  bool disp;
  mm::mtl::BitFlag<32> modeFlags;
  u32 followObjHandle;
  UIObjectAlphaParam *alphaParam;
  UICtrlSimple<1> fade;
  UICtrlSimpleUpdater<UICtrlSimple<1>> fadeUpdater;
  f32 fadeTime;
};

static_assert(offsetof(UIObjectDispPlugin, dispControl) == 0x1c, "");
static_assert(offsetof(UIObjectDispPlugin, disp) == 0x1d, "");
static_assert(offsetof(UIObjectDispPlugin, modeFlags) == 0x20, "");
static_assert(offsetof(UIObjectDispPlugin, followObjHandle) == 0x24, "");
static_assert(offsetof(UIObjectDispPlugin, alphaParam) == 0x28, "");
static_assert(offsetof(UIObjectDispPlugin, fade) == 0x30, "");
static_assert(offsetof(UIObjectDispPlugin, fadeUpdater) == 0x58, "");
static_assert(offsetof(UIObjectDispPlugin, fadeTime) == 0x78, "");
static_assert(sizeof(UIObjectDispPlugin) == 0x80, "");

} // namespace ui
