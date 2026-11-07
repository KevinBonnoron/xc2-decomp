#pragma once
#include <stddef.h>

#include "gf/data/gf_bdat_lookat.h"
#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

namespace pc {

// Inferred role: search result of a look-at candidate (distance at 0x20); original type name unknown.
struct unknown001;

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

  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
};

static_assert(offsetof(LookAtPlugin::TargetInfo, unknown08) == 0x08, "");
static_assert(offsetof(LookAtPlugin::TargetInfo, unknown10) == 0x10, "");
static_assert(offsetof(LookAtPlugin::TargetInfo, unknown18) == 0x18, "");
static_assert(offsetof(LookAtPlugin::TargetInfo, unknown1c) == 0x1c, "");
static_assert(sizeof(LookAtPlugin::TargetInfo) == 0x20, "");

} // namespace pc
} // namespace gf
