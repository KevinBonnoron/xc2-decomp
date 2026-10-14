#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"
#include <stddef.h>

namespace gf {

class GfStatusProperty {
public:
  virtual ~GfStatusProperty();

  int refCount;
  u32 maxHp;
  u32 hp;
  u32 limitHp;
  bool invincible;
  u8 _19[0x1a - 0x19];
  bool disableAutoHeal;
};

static_assert(offsetof(GfStatusProperty, maxHp) == 0x0c, "");
static_assert(offsetof(GfStatusProperty, hp) == 0x10, "");
static_assert(offsetof(GfStatusProperty, limitHp) == 0x14, "");
static_assert(offsetof(GfStatusProperty, invincible) == 0x18, "");
static_assert(offsetof(GfStatusProperty, disableAutoHeal) == 0x1a, "");

struct GfPropertyDebugFlags {
  bool invincible;
  bool disableFallDead;
};

class GfComProperty : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 5;

  GfStatusProperty *status;
  u8 _18[0x30 - 0x18];
  GfPropertyDebugFlags *debugFlags;
};

static_assert(offsetof(GfComProperty, status) == 0x10, "");
static_assert(offsetof(GfComProperty, debugFlags) == 0x30, "");

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
