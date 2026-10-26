#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class GfStatusProperty : public mm::mtl::ReferenceObject {
public:
  GfStatusProperty(u32 hp) : unknown0c(hp), unknown10(hp), unknown14(0), unknown18(false), _19(), unknown1a(false), _1b() {}

  u32 unknown0c;  // Inferred role: max hp; original member name unknown.
  u32 unknown10;  // Inferred role: hp; original member name unknown.
  u32 unknown14;  // Inferred role: limit hp; original member name unknown.
  bool unknown18; // Inferred role: invincible; original member name unknown.
  u8 _19[0x1a - 0x19];
  bool unknown1a; // Inferred role: disable auto heal; original member name unknown.
  u8 _1b[0x1c - 0x1b];
};

static_assert(offsetof(GfStatusProperty, unknown0c) == 0x0c, "");
static_assert(offsetof(GfStatusProperty, unknown10) == 0x10, "");
static_assert(offsetof(GfStatusProperty, unknown14) == 0x14, "");
static_assert(offsetof(GfStatusProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfStatusProperty, unknown1a) == 0x1a, "");

struct GfPropertyTarget {
  GF_OBJ_HANDLE *handle;
};

struct GfPropertyAlpha {
  f32 unknown00[OBJ_ALPHA_MAX]; // Inferred role: alphas; original member name unknown.
  f32 unknown18;                // Inferred role: total alpha; original member name unknown.
  bool unknown1c;               // Inferred role: changed; original member name unknown.
};

static_assert(offsetof(GfPropertyAlpha, unknown18) == 0x18, "");
static_assert(offsetof(GfPropertyAlpha, unknown1c) == 0x1c, "");

struct GfPropertyDebugFlags {
  bool invincible;
  bool disableFallDead;
};

class GfComProperty : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 5;

  void flush();

  GfStatusProperty *unknown10; // Inferred role: status; original member name unknown.
  GfPropertyTarget *unknown18; // Inferred role: target; original member name unknown.
  GfPropertyAlpha *unknown20;  // Inferred role: alpha; original member name unknown.
  u8 _28[0x30 - 0x28];
  GfPropertyDebugFlags *unknown30; // Inferred role: debug flags; original member name unknown.
};

static_assert(offsetof(GfComProperty, unknown10) == 0x10, "");
static_assert(offsetof(GfComProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfComProperty, unknown20) == 0x20, "");
static_assert(offsetof(GfComProperty, unknown30) == 0x30, "");

enum {
  HEAL_TYPE_NORMAL = 0,
  HEAL_TYPE_FULL = 1,
  HEAL_TYPE_SET = 2,
};

struct MsgObjectDamage : fw::Message {
  u32 unknown08; // Inferred role: damage; original member name unknown.
  u8 _0c[0x28 - 0x0c];
  u8 : 1;
  u8 unknown28_1 : 1; // Inferred role: critical; original member name unknown.
};

static_assert(offsetof(MsgObjectDamage, unknown08) == 0x08, "");

struct MsgObjectNotifyDamage : fw::Message {
  const MsgObjectDamage *unknown08; // Inferred role: damage; original member name unknown.
  GF_OBJ_HANDLE *unknown10;         // Inferred role: attacker; original member name unknown.
};

static_assert(offsetof(MsgObjectNotifyDamage, unknown10) == 0x10, "");

struct MsgObjectNotifyDead : fw::Message {
  int unknown08;                    // Inferred role: dead type; original member name unknown.
  const MsgObjectDamage *unknown10; // Inferred role: damage; original member name unknown.
};

static_assert(offsetof(MsgObjectNotifyDead, unknown10) == 0x10, "");

struct MsgObjectHealHp : fw::Message {
  MsgObjectHealHp(u32 hp, u32 healType)
      : fw::Message(0x1000033, 0x20), unknown08(hp), unknown0c(healType), unknown10(nullptr), unknown18(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), _20(), unknown21(false), unknown22(false),
        unknown23(false) {}

  u32 unknown08;             // Inferred role: hp; original member name unknown.
  u32 unknown0c;             // Inferred role: heal type; original member name unknown.
  const mm::Vec3 *unknown10; // Inferred role: position; original member name unknown.
  GF_OBJ_HANDLE *unknown18;  // Inferred role: healer; original member name unknown.
  u8 _20[0x21 - 0x20];
  bool unknown21; // Inferred role: revive; original member name unknown.
  bool unknown22; // Inferred role: hp max; original member name unknown.
  bool unknown23; // Inferred role: healed; original member name unknown.
};

static_assert(offsetof(MsgObjectHealHp, unknown10) == 0x10, "");
static_assert(offsetof(MsgObjectHealHp, unknown18) == 0x18, "");
static_assert(offsetof(MsgObjectHealHp, unknown21) == 0x21, "");
static_assert(offsetof(MsgObjectHealHp, unknown23) == 0x23, "");

struct MsgObjectAlpha : fw::Message {
  MsgObjectAlpha(OBJ_ALPHA type, f32 alpha) : fw::Message(0x100003a, 0x20), type(type), alpha(alpha) {}

  OBJ_ALPHA type;
  f32 alpha;
};

struct MsgObjectChangeHpMax : fw::Message {
  MsgObjectChangeHpMax(u32 maxHp) : fw::Message(0x1000034, 0x20), maxHp(maxHp) {}

  u32 maxHp;
};

struct MsgObjectChangeHp : fw::Message {
  MsgObjectChangeHp(u32 hp) : fw::Message(0x1000035, 0x20), hp(hp) {}

  u32 hp;
};

struct MsgObjectChangeAttribute : fw::Message {
  MsgObjectChangeAttribute() : fw::Message(0x1000042, 0x20) {}

  u32 unknown08; // Inferred role: attribute; original member name unknown.
  u32 unknown0c; // Inferred role: old attribute; original member name unknown.
};

enum {
  DEAD_TYPE_EMERGENCY_ESCAPE = 4,
};

struct MsgObjectDead : fw::Message {
  MsgObjectDead(u32 deadType) : fw::Message(0x1000036, 0x20), deadType(deadType) {}

  u32 deadType;
};

struct MsgObjectStopAutoHeal : fw::Message {
  MsgObjectStopAutoHeal(bool isStop) : fw::Message(0x1000043, 0x20), isStop(isStop) {}

  bool isStop;
};

struct MsgObjectInvincible : fw::Message {
  MsgObjectInvincible(bool invincible, bool invincibleSub) : fw::Message(0x1000044, 0x20), invincible(invincible), invincibleSub(invincibleSub) {}

  bool invincible;
  bool invincibleSub;
};

struct MsgObjectLimitHP : fw::Message {
  MsgObjectLimitHP(u32 limitHp) : fw::Message(0x1000045, 0x20), limitHp(limitHp) {}

  u32 limitHp;
};

} // namespace gf
