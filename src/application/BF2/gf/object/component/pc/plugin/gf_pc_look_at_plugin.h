#pragma once
#include <stddef.h>

#include "framework/ik/ik_look_solver.h" // IWYU pragma: keep
#include "fw/fw_param_manager.h"         // IWYU pragma: keep
#include "gf/data/gf_bdat_lookat.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h"
#include "types.h"

namespace fw {
struct Transform;
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SEARCH_OBJ;

namespace pc {

// Inferred role: search result of a look-at candidate (distance at 0x20); original type name unknown.
struct unknown001;

// Inferred role: LookAtPlugin parameters, entry 4 of the param list at 0x430 of the param manager; original type name unknown.
struct unknown002 {
  f32 unknown00; // Inferred role: search height; original member name unknown.
  u8 _04[0x08 - 0x04];
  f32 unknown08; // Inferred role: fade in time; original member name unknown.
  f32 unknown0c; // Inferred role: target fade time; original member name unknown.
  f32 unknown10; // Inferred role: fade out time; original member name unknown.
};

static_assert(offsetof(unknown002, unknown08) == 0x08, "");
static_assert(offsetof(unknown002, unknown10) == 0x10, "");

// Evidence: size 0x88 from the operator new of create; the constructor stores the sentinel of the map at 0x28, the allocator, the handle -1 at 0x20 and zeroes 0x40 and 0x68 to 0x84; the destructor
// releases the param list at 0x18 and the look solver at 0x10 and frees the map.
class LookAtPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  // Layout evidence: updateHoldHandles (0x71005793f4) fills it before Map<GF_OBJ_HANDLE *, TargetInfo>::insert
  // (0x710057a0fc), which copies the 0x28-byte MapPair (key at 0x00, value at 0x08); changeTarget (0x710057997c) reads
  // 0x08, 0x10 and 0x18 and sets 0x1c; getTargetTransform (0x7100579ca0) reads 0x00.
  struct TargetInfo {
    GF_OBJ_HANDLE *unknown00;                  // Inferred role: target handle; original member name unknown.
    const unknown001 *unknown08;               // Inferred role: search result; original member name unknown.
    const GfBdatLookAt::unknown001 *unknown10; // Inferred role: look info; original member name unknown.
    u32 unknown18;                             // Inferred role: chara type; original member name unknown.
    bool unknown1c;                            // Inferred role: already looked at; original member name unknown.
  };

  LookAtPlugin();
  ~LookAtPlugin() override;
  static LookAtPlugin *create();
  void onActivate() override;
  void onDeactivate() override;
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
  const unknown002 *getParam() const;
  bool getTargetTransform(const TargetInfo &info, fw::Transform *transform) const;
  void drawDebugTarget();

  mm::mtl::IntrusivePtr<fw::LookIkSolver> unknown10;   // Inferred role: look solver; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown18;      // Inferred role: param list; original member name unknown.
  GF_SEARCH_OBJ *unknown20;                            // Inferred role: search object; original member name unknown.
  mm::mtl::Map<GF_OBJ_HANDLE *, TargetInfo> unknown28; // Inferred role: candidates; original member name unknown.
  TargetInfo *unknown40;                               // Inferred role: current target, points to unknown48; original member name unknown.
  TargetInfo unknown48;                                // Inferred role: current target copy; original member name unknown.
  u32 unknown68;                                       // Inferred role: current target side; original member name unknown.
  f32 unknown6c;                                       // Inferred role: change target timer; original member name unknown.
  f32 unknown70[5];                                    // Inferred role: look timers per chara type; original member name unknown.
};

static_assert(offsetof(LookAtPlugin::TargetInfo, unknown08) == 0x08, "");
static_assert(offsetof(LookAtPlugin::TargetInfo, unknown10) == 0x10, "");
static_assert(offsetof(LookAtPlugin::TargetInfo, unknown18) == 0x18, "");
static_assert(offsetof(LookAtPlugin::TargetInfo, unknown1c) == 0x1c, "");
static_assert(sizeof(LookAtPlugin::TargetInfo) == 0x20, "");
static_assert(offsetof(LookAtPlugin, unknown10) == 0x10, "");
static_assert(offsetof(LookAtPlugin, unknown18) == 0x18, "");
static_assert(offsetof(LookAtPlugin, unknown20) == 0x20, "");
static_assert(offsetof(LookAtPlugin, unknown28) == 0x28, "");
static_assert(offsetof(LookAtPlugin, unknown40) == 0x40, "");
static_assert(offsetof(LookAtPlugin, unknown48) == 0x48, "");
static_assert(offsetof(LookAtPlugin, unknown68) == 0x68, "");
static_assert(offsetof(LookAtPlugin, unknown6c) == 0x6c, "");
static_assert(offsetof(LookAtPlugin, unknown70) == 0x70, "");
static_assert(sizeof(LookAtPlugin) == 0x88, "");

} // namespace pc
} // namespace gf
