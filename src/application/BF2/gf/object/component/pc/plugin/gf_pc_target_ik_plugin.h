#pragma once
#include <stddef.h>

#include "framework/ik/ik_look_solver.h" // IWYU pragma: keep
#include "fw/fw_param_manager.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class MessageObject;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
class GfComPropertyPc;
struct MsgGameChangeTarget;

namespace pc {

struct TargetIKParam {
  f32 unknown00; // Inferred role: active angle in degrees; original member name unknown.
  f32 unknown04; // Inferred role: fade time; original member name unknown.
  u8 _08[0x14 - 0x08];
  f32 unknown14; // Inferred role: ratio change time; original member name unknown.
};

static_assert(offsetof(TargetIKParam, unknown04) == 0x04, "");
static_assert(offsetof(TargetIKParam, unknown14) == 0x14, "");

// Evidence: size 0x50 from the operator new of create, the constructor stores (handle -1 at 0x10, Vec3::unitZ at 0x30, two 1.0f at 0x40), the look solver at 0x18 is released by the destructor, the
// param entry at 0x20 is entry 4 of the pc param list (setup, 0x40 / 0x10).
class TargetIKPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  TargetIKPlugin();
  ~TargetIKPlugin() override;
  static TargetIKPlugin *create();
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  void onActivate() override;
  void onDeactivate() override;
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  const TargetIKParam *getParam() const;
  bool isActiveRange(GfComPropertyPc &property, const mm::Vec3 &target);
  void procMsgGameChangeTarget(fw::MessageObject *object, MsgGameChangeTarget &message);

  GF_OBJ_HANDLE *unknown10;                          // Inferred role: target; original member name unknown.
  mm::mtl::IntrusivePtr<fw::LookIkSolver> unknown18; // Inferred role: look ik solver; original member name unknown.
  const fw::ParamList::Entry *unknown20;             // Inferred role: param entry; original member name unknown.
  u8 _28[0x30 - 0x28];
  mm::Vec3 unknown30; // Inferred role: look axis; original member name unknown.
  f32 unknown40;      // Inferred role: target up ratio; original member name unknown.
  f32 unknown44;      // Inferred role: target down ratio; original member name unknown.
};

static_assert(offsetof(TargetIKPlugin, unknown10) == 0x10, "");
static_assert(offsetof(TargetIKPlugin, unknown18) == 0x18, "");
static_assert(offsetof(TargetIKPlugin, unknown20) == 0x20, "");
static_assert(offsetof(TargetIKPlugin, unknown30) == 0x30, "");
static_assert(offsetof(TargetIKPlugin, unknown40) == 0x40, "");
static_assert(offsetof(TargetIKPlugin, unknown44) == 0x44, "");
static_assert(sizeof(TargetIKPlugin) == 0x50, "");

} // namespace pc
} // namespace gf
