#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
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
namespace pc {

struct FadeParam {
  f32 fadeOutTime;
  f32 blackTime;
  f32 fadeTime;
};

class FadePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  enum Mode {
    MODE_NONE,
    MODE_FADE_IN,
    MODE_BLACK,
    MODE_FADE_OUT,
  };

  FadePlugin();
  static FadePlugin *create();
  ~FadePlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void changeMode(Mode mode);
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);

  const FadeParam *getParam() const { return unknown18 != nullptr ? static_cast<const FadeParam *>(unknown18->param) : nullptr; }

  Mode unknown0c;                        // Inferred role: mode; original member name unknown.
  f32 unknown10;                         // Inferred role: timer; original member name unknown.
  const fw::ParamList::Entry *unknown18; // Inferred role: param entry; original member name unknown.
};

static_assert(offsetof(FadePlugin, unknown0c) == 0x0c, "");
static_assert(offsetof(FadePlugin, unknown10) == 0x10, "");
static_assert(offsetof(FadePlugin, unknown18) == 0x18, "");
static_assert(sizeof(FadePlugin) == 0x20, "");

} // namespace pc
} // namespace gf
