#pragma once
#include <stddef.h>

#include "gf/object/component/gf_component.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace anm {
class ResASM;
}

namespace fw {
class EffectCasterBase;
class EffectPoint;
struct EffectResData;
class MessageObject;
} // namespace fw

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;
struct MsgFxRimBloomEnd;
struct MsgFxRimBloomTarget;
struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;

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
  struct Param {
    u8 _00[0x28];
    f32 unknown28; // Inferred role: elapsed second; original member name unknown.
    u8 _2c[0x30 - 0x2c];
    f32 unknown30; // Inferred role: speed; original member name unknown.
    u8 _34[0x58 - 0x34];
    u32 unknown58; // Inferred role: effect identifier; original member name unknown.
    u8 _5c[0xc0 - 0x5c];
  };

  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 7;

  static void registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData);
  bool getEfpMatrix(const char *name, mm::Mat44 &matrix);
  void addMountEffectEv(const EffectMountSetupEv &setup);
  void removeMountEffectEv(u32 effect);
  u32 calcWeaponID() const;
  void setCaster(u32 effect);
  bool setSpeed(u32 effect, f32 speed);
  f32 getElapsedSecond(u32 effect);
  void procMsgObjectNotifyDamage(fw::MessageObject *object, MsgObjectNotifyDamage &message);
  void procMsgObjectNotifyDead(fw::MessageObject *object, MsgObjectNotifyDead &message);
  void procMsgFxRimBloomEnd(fw::MessageObject *object, MsgFxRimBloomEnd &message);
  void procMsgFxRimBloomTarget(fw::MessageObject *object, MsgFxRimBloomTarget &message);
  fw::EffectPoint *getEffectPoint();
  bool getValidEffectName(const char *name) const;
  bool isDynamicAnnotationEffect(u8 type) const;
  Param *findEffectCasterParam(u32 effect);
  GF_OBJ_HANDLE *getWeaponHandle(u16 weapon);
  void getWpnMatOld1(mm::Mat44 &matrix);
  void getWpnMatOld2(mm::Mat44 &matrix);

  u8 _10[0x14 - 0x10];
  bool unknown14; // Inferred role: rim bloom active; original member name unknown.
  u8 _15[0x18 - 0x15];
  u32 unknown18; // Inferred role: rim bloom state; original member name unknown.
  f32 unknown1c; // Inferred role: rim bloom time; original member name unknown.
  f32 unknown20; // Inferred role: rim bloom duration; original member name unknown.
  f32 unknown24; // Inferred role: water depth threshold of the first swim state; original member name unknown.
  f32 unknown28; // Inferred role: water depth threshold of the second swim state; original member name unknown.
  u8 _2c[0x388 - 0x2c];
  fw::EffectCasterBase *unknown388; // Inferred role: effect caster; original member name unknown.
  fw::EffectPoint *unknown390;      // Inferred role: effect point; original member name unknown.
  u8 _398[0x3a0 - 0x398];
  mm::mtl::FixedVector<Param, 256> unknown3a0; // Inferred role: caster params; original member name unknown.
  u8 _c3a8[0x113d0 - 0xc3a8];
  mm::Mat44 unknown113d0; // Inferred role: weapon matrix of the previous frame; original member name unknown.
  mm::Mat44 unknown11410; // Inferred role: second weapon matrix of the previous frame; original member name unknown.
};

static_assert(offsetof(GfComEffectCaster, unknown14) == 0x14, "");
static_assert(offsetof(GfComEffectCaster, unknown18) == 0x18, "");
static_assert(offsetof(GfComEffectCaster, unknown1c) == 0x1c, "");
static_assert(offsetof(GfComEffectCaster, unknown20) == 0x20, "");
static_assert(offsetof(GfComEffectCaster, unknown24) == 0x24, "");
static_assert(offsetof(GfComEffectCaster, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster, unknown388) == 0x388, "");
static_assert(offsetof(GfComEffectCaster, unknown390) == 0x390, "");
static_assert(offsetof(GfComEffectCaster, unknown3a0) == 0x3a0, "");
static_assert(offsetof(GfComEffectCaster, unknown113d0) == 0x113d0, "");
static_assert(offsetof(GfComEffectCaster, unknown11410) == 0x11410, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown28) == 0x28, "");
static_assert(offsetof(GfComEffectCaster::Param, unknown30) == 0x30, "");
static_assert(sizeof(GfComEffectCaster::Param) == 0xc0, "");

} // namespace gf
