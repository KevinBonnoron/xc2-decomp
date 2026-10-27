#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"                          // IWYU pragma: keep
#include "gf/object/component/behavior/gf_com_behavior.h" // IWYU pragma: keep
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class EyeBlinkPlugin : public Plugin {
  GF_PLUGIN(GfComBehavior)

public:
  enum Mode {
    MODE_UNKNOWN_0,
    MODE_UNKNOWN_1,
    MODE_UNKNOWN_2,
    MODE_UNKNOWN_3,
    MODE_UNKNOWN_4,
  };

  // Inferred role: eye blink parameters; original type name unknown.
  struct unknown001 {
    f32 unknown00; // Inferred role: minimum blink interval; original member name unknown.
    f32 unknown04; // Inferred role: maximum blink interval; original member name unknown.
    f32 unknown08; // Inferred role: close ease time; original member name unknown.
    f32 unknown0c; // Inferred role: open ease time; original member name unknown.
    f32 unknown10; // Inferred role: closed hold time; original member name unknown.
    f32 unknown14; // Inferred role: double blink rate; original member name unknown.
  };

  EyeBlinkPlugin();
  static EyeBlinkPlugin *create();
  virtual bool setup(GfComBehavior &behavior);
  virtual void cleanup(GfComBehavior &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehavior &behavior, const fw::UpdateInfo &info);
  void setMode(Mode mode);
  void resetTimer();
  const unknown001 *getParameter() const;
  bool testDouble();

  GfComBehavior *unknown10;                       // Inferred role: behavior; original member name unknown.
  f32 unknown18;                                  // Inferred role: blink timer; original member name unknown.
  Mode unknown1c;                                 // Inferred role: mode; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown20; // Inferred role: param list; original member name unknown.
};

static_assert(offsetof(EyeBlinkPlugin, unknown10) == 0x10, "");
static_assert(offsetof(EyeBlinkPlugin, unknown18) == 0x18, "");
static_assert(offsetof(EyeBlinkPlugin, unknown1c) == 0x1c, "");
static_assert(offsetof(EyeBlinkPlugin, unknown20) == 0x20, "");
static_assert(sizeof(EyeBlinkPlugin) == 0x28, "");

} // namespace gf
