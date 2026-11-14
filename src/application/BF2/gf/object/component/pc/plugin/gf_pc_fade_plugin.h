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
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {
namespace pc {

struct FadeParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 fadeInTime;
  f32 blackOutTime;
  f32 fadeOutTime;
};

static_assert(offsetof(FadeParam, blackOutTime) == 0x04, "");
static_assert(offsetof(FadeParam, fadeOutTime) == 0x08, "");
static_assert(sizeof(FadeParam) == 0x0c, "");

class FadePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  static const u32 PLUGIN_INDEX = 11;

  enum Mode {
    MODE_UNKNOWN_0, // Inferred role: mode none; original name unknown.
    MODE_UNKNOWN_1, // Inferred role: mode fade in; original name unknown.
    MODE_UNKNOWN_2, // Inferred role: mode black; original name unknown.
    MODE_UNKNOWN_3, // Inferred role: mode fade out; original name unknown.
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

  Mode unknown0c;                             // Inferred role: mode; original member name unknown.
  f32 unknown10;                              // Inferred role: timer; original member name unknown.
  const fw::ParamList::unknown005 *unknown18; // Inferred role: param entry; original member name unknown.
};

static_assert(offsetof(FadePlugin, unknown0c) == 0x0c, "");
static_assert(offsetof(FadePlugin, unknown10) == 0x10, "");
static_assert(offsetof(FadePlugin, unknown18) == 0x18, "");
static_assert(sizeof(FadePlugin) == 0x20, "");

} // namespace pc
} // namespace gf
