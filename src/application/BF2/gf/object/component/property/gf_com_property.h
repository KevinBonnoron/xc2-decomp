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
  GfStatusProperty(u32 hp) : maxHp(hp), hp(hp), limitHp(0), invincible(false), _19(), disableAutoHeal(false), _1b() {}

  u32 maxHp;
  u32 hp;
  u32 limitHp;
  bool invincible;
  u8 _19[0x1a - 0x19];
  bool disableAutoHeal;
  u8 _1b[0x1c - 0x1b];
};

static_assert(offsetof(GfStatusProperty, maxHp) == 0x0c, "");
static_assert(offsetof(GfStatusProperty, hp) == 0x10, "");
static_assert(offsetof(GfStatusProperty, limitHp) == 0x14, "");
static_assert(offsetof(GfStatusProperty, invincible) == 0x18, "");
static_assert(offsetof(GfStatusProperty, disableAutoHeal) == 0x1a, "");

struct GfPropertyTarget {
  GF_OBJ_HANDLE *handle;
};

struct GfPropertyAlpha {
  f32 alphas[OBJ_ALPHA_MAX];
  f32 totalAlpha;
  bool isChanged;
};

static_assert(offsetof(GfPropertyAlpha, totalAlpha) == 0x18, "");
static_assert(offsetof(GfPropertyAlpha, isChanged) == 0x1c, "");

struct GfPropertyDebugFlags {
  bool invincible;
  bool disableFallDead;
};

class GfComProperty : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 5;

  GfStatusProperty *status;
  GfPropertyTarget *target;
  GfPropertyAlpha *alpha;
  u8 _28[0x30 - 0x28];
  GfPropertyDebugFlags *debugFlags;
};

static_assert(offsetof(GfComProperty, status) == 0x10, "");
static_assert(offsetof(GfComProperty, target) == 0x18, "");
static_assert(offsetof(GfComProperty, alpha) == 0x20, "");
static_assert(offsetof(GfComProperty, debugFlags) == 0x30, "");

enum {
  HEAL_TYPE_NORMAL = 0,
  HEAL_TYPE_FULL = 1,
  HEAL_TYPE_SET = 2,
};

struct MsgObjectHealHp : fw::Message {
  MsgObjectHealHp(u32 hp, u32 healType)
      : fw::Message(0x1000033, 0x20), hp(hp), healType(healType), position(nullptr), healer(reinterpret_cast<GF_OBJ_HANDLE *>(-1)), _20(),
        isRevive(false), isHpMax(false), isHealed(false) {}

  u32 hp;
  u32 healType;
  const mm::Vec3 *position;
  GF_OBJ_HANDLE *healer;
  u8 _20[0x21 - 0x20];
  bool isRevive;
  bool isHpMax;
  bool isHealed;
};

static_assert(offsetof(MsgObjectHealHp, position) == 0x10, "");
static_assert(offsetof(MsgObjectHealHp, healer) == 0x18, "");
static_assert(offsetof(MsgObjectHealHp, isRevive) == 0x21, "");
static_assert(offsetof(MsgObjectHealHp, isHealed) == 0x23, "");

struct MsgObjectAlpha : fw::Message {
  MsgObjectAlpha(OBJ_ALPHA type, f32 alpha) : fw::Message(0x100003a, 0x20), type(type), alpha(alpha) {}

  OBJ_ALPHA type;
  f32 alpha;
};

struct MsgObjectChangeHpMax : fw::Message {
  MsgObjectChangeHpMax(u32 maxHp) : fw::Message(0x1000034, 0x20), maxHp(maxHp) {}

  u32 maxHp;
};

struct MsgObjectChangeAttribute : fw::Message {
  MsgObjectChangeAttribute() : fw::Message(0x1000042, 0x20) {}

  u32 attribute;
  u32 oldAttribute;
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
