#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

namespace pc {

struct LureParam;

class LurePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  LurePlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  const LureParam *getParam() const;
  void drawDebug(GfComBehaviorPc &behavior);

  GF_OBJ_HANDLE *target;
  mm::mtl::IntrusivePtr<fw::ParamList> paramList;
  GfComBehaviorPc *behavior;
};

static_assert(offsetof(LurePlugin, target) == 0x10, "");
static_assert(offsetof(LurePlugin, paramList) == 0x18, "");
static_assert(offsetof(LurePlugin, behavior) == 0x20, "");
static_assert(sizeof(LurePlugin) == 0x28, "");

} // namespace pc
} // namespace gf
