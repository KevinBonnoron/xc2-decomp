#pragma once
#include <stddef.h>

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

struct GF_SEARCH_OBJ;

namespace pc {

class FallIntoColiPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  FallIntoColiPlugin();
  static FallIntoColiPlugin *create();
  ~FallIntoColiPlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  f32 getHeight(GfComBehaviorPc &behavior) const;

  f32 unknown0c;            // Inferred role: search timer; original member name unknown.
  f32 unknown10;            // Inferred role: stay timer; original member name unknown.
  GF_SEARCH_OBJ *unknown18; // Inferred role: search object; original member name unknown.
  f32 unknown20;            // Inferred role: height; original member name unknown.
};

static_assert(offsetof(FallIntoColiPlugin, unknown0c) == 0x0c, "");
static_assert(offsetof(FallIntoColiPlugin, unknown10) == 0x10, "");
static_assert(offsetof(FallIntoColiPlugin, unknown18) == 0x18, "");
static_assert(offsetof(FallIntoColiPlugin, unknown20) == 0x20, "");
static_assert(sizeof(FallIntoColiPlugin) == 0x28, "");

} // namespace pc
} // namespace gf
