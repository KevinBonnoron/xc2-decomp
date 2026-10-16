#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
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

struct GF_OBJ_HANDLE;
class GfComPropertyPc;

namespace pc {

struct AccessParam;

class AccessPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  AccessPlugin();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  u32 getParamIndex(GfComPropertyPc &property) const;
  const AccessParam *getParam(u32 index) const;
  void drawDebug(GfComBehaviorPc &behavior, u32 index);

  GF_OBJ_HANDLE *target;
  mm::mtl::IntrusivePtr<fw::ParamList> paramList;
  GfComBehaviorPc *behavior;
  int paramIndex;
};

static_assert(offsetof(AccessPlugin, target) == 0x10, "");
static_assert(offsetof(AccessPlugin, paramList) == 0x18, "");
static_assert(offsetof(AccessPlugin, behavior) == 0x20, "");
static_assert(offsetof(AccessPlugin, paramIndex) == 0x28, "");
static_assert(sizeof(AccessPlugin) == 0x30, "");

} // namespace pc
} // namespace gf
