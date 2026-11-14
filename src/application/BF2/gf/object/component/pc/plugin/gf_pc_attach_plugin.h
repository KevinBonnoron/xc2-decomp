#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
struct Transform;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

namespace pc {

class AttachPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  AttachPlugin();
  ~AttachPlugin() override;
  static AttachPlugin *create();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  void dettachObj();
  void attachObj(GF_OBJ_HANDLE *handle);
  void notifyMovement();
  void changeWallMode(bool isWall);
  void notifyExcludeMovementRider(const fw::Transform &transform);

  u32 unknown0c;              // Inferred role: flags; original member name unknown.
  GF_OBJ_HANDLE *unknown10;   // Inferred role: attached object; original member name unknown.
  GfComBehaviorPc *unknown18; // Inferred role: behavior; original member name unknown.
  mm::Vec3 unknown20;         // Inferred role: attached position; original member name unknown.
  mm::Quat unknown30;         // Inferred role: attached rotation; original member name unknown.
};

static_assert(offsetof(AttachPlugin, unknown0c) == 0x0c, "");
static_assert(offsetof(AttachPlugin, unknown10) == 0x10, "");
static_assert(offsetof(AttachPlugin, unknown18) == 0x18, "");
static_assert(offsetof(AttachPlugin, unknown20) == 0x20, "");
static_assert(offsetof(AttachPlugin, unknown30) == 0x30, "");
static_assert(sizeof(AttachPlugin) == 0x40, "");

} // namespace pc
} // namespace gf
