#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
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
struct GfEnvProperty;

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

struct GfTargetProperty {
  GF_OBJ_HANDLE *handle;
};

struct GfAlphaProperty {
  f32 unknown00[OBJ_ALPHA_MAX]; // Inferred role: alphas; original member name unknown.
  f32 unknown18;                // Inferred role: total alpha; original member name unknown.
  bool unknown1c;               // Inferred role: changed; original member name unknown.
};

static_assert(offsetof(GfAlphaProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfAlphaProperty, unknown1c) == 0x1c, "");

struct GfDebugStatusProperty {
  bool invincible;
  bool disableFallDead;
};

struct MsgObjectMaxHp;
struct MsgObjectSetHp;
struct MsgObjectStopAutoHeal;
struct MsgObjectLimitHP;

class GfComProperty : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 5;

  GfComProperty();
  ~GfComProperty() override;
  void flush();
  void procMsgObjectMaxHp(fw::MessageObject *object, MsgObjectMaxHp &message);
  void procMsgObjectSetHp(fw::MessageObject *object, MsgObjectSetHp &message);
  void procMsgObjectStopAutoHeal(fw::MessageObject *object, MsgObjectStopAutoHeal &message);
  void procMsgObjectLimitHP(fw::MessageObject *object, MsgObjectLimitHP &message);

  GfStatusProperty *unknown10;      // Inferred role: status; original member name unknown.
  GfTargetProperty *unknown18;      // Inferred role: target; original member name unknown.
  GfAlphaProperty *unknown20;       // Inferred role: alpha; original member name unknown.
  GfEnvProperty *unknown28;         // Inferred role: environment; original member name unknown.
  GfDebugStatusProperty *unknown30; // Inferred role: debug flags; original member name unknown.
};

static_assert(offsetof(GfComProperty, unknown10) == 0x10, "");
static_assert(offsetof(GfComProperty, unknown18) == 0x18, "");
static_assert(offsetof(GfComProperty, unknown20) == 0x20, "");
static_assert(offsetof(GfComProperty, unknown28) == 0x28, "");
static_assert(offsetof(GfComProperty, unknown30) == 0x30, "");

enum {
  HEAL_TYPE_NORMAL = 0,
  HEAL_TYPE_FULL = 1,
  HEAL_TYPE_SET = 2,
};

enum {
  MSG_OBJECT_DAMAGE = 0x1000032,
  MSG_OBJECT_NOTIFY_DAMAGE = 0x1000037,
  MSG_OBJECT_NOTIFY_DEAD = 0x1000038,
};

// Layout evidence: GfComBehaviorEnemy::procMsgObjectLure (0x7100513fc4) and GfFieldDmg::update build it on the stack and the
// handlers of GfComBehaviorEnemy read the members at 0x20, 0x2a and 0x2e.
struct MsgObjectDamage : fw::Message {
  MsgObjectDamage(u32 damage, u32 type)
      : fw::Message(MSG_OBJECT_DAMAGE, 0x20), unknown08(damage), unknown0c(damage), unknown10(type), unknown18(nullptr), unknown20(INVALID_HANDLE), unknown28_0(0), unknown28_1(0), unknown28_2(0),
        unknown29(0), unknown2a(false), unknown2b(0), unknown2c(0), unknown2e(false), unknown2f(true), unknown30(false), unknown34(0), unknown38(false) {}

  u32 unknown08;             // Inferred role: damage; original member name unknown.
  u32 unknown0c;             // Role and original member name unknown.
  u32 unknown10;             // Role and original member name unknown.
  const mm::Vec3 *unknown18; // Role and original member name unknown.
  GF_OBJ_HANDLE *unknown20;  // Inferred role: attacker; original member name unknown.
  u8 unknown28_0 : 1;        // Role and original member name unknown.
  u8 unknown28_1 : 1;        // Inferred role: critical; original member name unknown.
  u8 unknown28_2 : 6;        // Role and original member name unknown.
  u8 unknown29;              // Role and original member name unknown.
  bool unknown2a;            // Role and original member name unknown.
  u8 unknown2b;              // Role and original member name unknown.
  u16 unknown2c;             // Role and original member name unknown.
  bool unknown2e;            // Role and original member name unknown.
  bool unknown2f;            // Role and original member name unknown.
  bool unknown30;            // Role and original member name unknown.
  u32 unknown34;             // Role and original member name unknown.
  bool unknown38;            // Role and original member name unknown.
};

static_assert(offsetof(MsgObjectDamage, unknown08) == 0x08, "");
static_assert(offsetof(MsgObjectDamage, unknown18) == 0x18, "");
static_assert(offsetof(MsgObjectDamage, unknown20) == 0x20, "");
static_assert(offsetof(MsgObjectDamage, unknown2a) == 0x2a, "");
static_assert(offsetof(MsgObjectDamage, unknown2c) == 0x2c, "");
static_assert(offsetof(MsgObjectDamage, unknown2e) == 0x2e, "");
static_assert(offsetof(MsgObjectDamage, unknown38) == 0x38, "");
static_assert(sizeof(MsgObjectDamage) == 0x40, "");

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

struct MsgGameChangeTarget : fw::Message {
  GF_OBJ_HANDLE *unknown08; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(MsgGameChangeTarget, unknown08) == 0x08, "");

struct MsgObjectMaxHp : fw::Message {
  MsgObjectMaxHp(u32 maxHp) : fw::Message(0x1000034, 0x20), maxHp(maxHp) {}

  u32 maxHp;
};

struct MsgObjectSetHp : fw::Message {
  MsgObjectSetHp(u32 hp) : fw::Message(0x1000035, 0x20), hp(hp) {}

  u32 hp;
};

struct MsgObjectNotifyChangeAttribute : fw::Message {
  MsgObjectNotifyChangeAttribute() : fw::Message(0x1000042, 0x20) {}

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
