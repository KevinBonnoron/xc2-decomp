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
  ~FallIntoColiPlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  f32 getHeight(GfComBehaviorPc &behavior) const;

  f32 searchTimer;
  f32 stayTimer;
  GF_SEARCH_OBJ *searchObj;
  f32 height;
};

static_assert(offsetof(FallIntoColiPlugin, searchTimer) == 0x0c, "");
static_assert(offsetof(FallIntoColiPlugin, stayTimer) == 0x10, "");
static_assert(offsetof(FallIntoColiPlugin, searchObj) == 0x18, "");
static_assert(offsetof(FallIntoColiPlugin, height) == 0x20, "");
static_assert(sizeof(FallIntoColiPlugin) == 0x28, "");

} // namespace pc
} // namespace gf
