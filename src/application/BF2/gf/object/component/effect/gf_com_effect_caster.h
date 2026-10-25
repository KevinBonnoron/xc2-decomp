#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace anm {
class ResASM;
}

namespace fw {
class EffectCasterBase;
struct EffectResData;
} // namespace fw

namespace mm {
struct Mat44;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

struct EffectMountSetupEv {
  EffectMountSetupEv() : unknown30(mm::Vec3::zero), _40(), unknown41(false), unknown42(false) {}

  // Inferred roles from access offsets; original member names are unknown.
  u32 unknown0;                 // Effect identifier.
  mm::mtl::FixStr<32> unknown8; // Bone name.
  mm::Vec3 unknown30;           // Offset.
  u8 _40[0x41 - 0x40];
  bool unknown41; // Rotation enabled.
  bool unknown42; // Follow enabled.
};

static_assert(offsetof(EffectMountSetupEv, unknown30) == 0x30, "");
static_assert(offsetof(EffectMountSetupEv, unknown41) == 0x41, "");

class GfComEffectCaster : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 7;

  static void registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData);
  bool getEfpMatrix(const char *name, mm::Mat44 &matrix);
  void addMountEffectEv(const EffectMountSetupEv &setup);
  void removeMountEffectEv(u32 effect);
  void setSpeed(u32 effect, f32 speed);

  u8 _10[0x388 - 0x10];
  fw::EffectCasterBase *unknown388; // Inferred role: effect caster; original member name unknown.
};

static_assert(offsetof(GfComEffectCaster, unknown388) == 0x388, "");

} // namespace gf
