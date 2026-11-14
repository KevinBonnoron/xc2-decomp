#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h" // IWYU pragma: keep
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
struct AccessParam;

namespace pc {

bool isActiveRangeLure(GfComPropertyPc &property, const AccessParam &param, GF_OBJ_HANDLE *target);

class LurePlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  static const u32 PLUGIN_INDEX = 15;

  LurePlugin();
  static LurePlugin *create();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  const AccessParam *getParam() const;
  void drawDebug(GfComBehaviorPc &behavior);

  GF_OBJ_HANDLE *unknown10;                       // Inferred role: target; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown18; // Inferred role: param list; original member name unknown.
  GfComBehaviorPc *unknown20;                     // Inferred role: behavior; original member name unknown.
};

static_assert(offsetof(LurePlugin, unknown10) == 0x10, "");
static_assert(offsetof(LurePlugin, unknown18) == 0x18, "");
static_assert(offsetof(LurePlugin, unknown20) == 0x20, "");
static_assert(sizeof(LurePlugin) == 0x28, "");

} // namespace pc
} // namespace gf
