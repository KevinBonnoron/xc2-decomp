#pragma once
#include "battle/effect/effect_move_component.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace fw {
class EffectPack;
}

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace btl {

constexpr int EFFECT_HIT_CHARACTER_COUNT = 90;

class EffectObject {
public:
  enum OBJECT_TYPE {
    OBJECT_TYPE_NONE,
    OBJECT_TYPE_OBJECT,
    OBJECT_TYPE_EFFECT,
  };

  enum HIT_TYPE {
    HIT_TYPE_NONE,
    HIT_TYPE_ONE_SHOT,
    HIT_TYPE_INTERVAL,
  };

  struct ONE_SHOT_HIT_DATA {
    f32 time;
    bool isEnableHit;
    bool isHitOnEnd;
    bool isEndHit;
    bool isLastAttack;
  };

  struct INTERVAL_HIT_DATA {
    f32 damage;
    u16 radius;
    s16 lifespan;
    u8 interval;
    u8 isDamageRate : 1;
    u8 isSpecialTarget : 1;
    u8 isTargetFriend : 1;
    u8 isTargetEnemy : 1;
    u16 hitTimers[EFFECT_HIT_CHARACTER_COUNT];
  };

  EffectObject();
  void Initialize(u32 id);
  void SetOneShotHitData(f32 time, bool isHitOnEnd);
  void SetArtsData(int artsSlot, int hit, bool isArts, u32 attackId);
  void SetBulletData(int bulletId, int bulletEffectId);
  void SetIntervalHitData(f32 radius, f32 damage, bool isDamageRate, f32 interval, f32 lifespan, bool isSpecialTarget, bool isTargetFriend,
                          bool isTargetEnemy);
  void SetMoveParam(const EffectMoveComponent::MOVE_PARAM &param);
  void SetEndEffect(const char *name);
  bool IsEnd() const;

  mm::mtl::FixedVector<fw::EffectPack *, 8> effectPacks;
  gf::GF_OBJ_HANDLE *attacker;
  gf::GF_OBJ_HANDLE *target;
  mm::mtl::FixStr<32> endEffect;
  mm::Vec3 position;
  mm::Vec3 direction;
  mm::Vec3 rotation;
  mm::Vec3 scale;
  union {
    gf::GF_OBJ_HANDLE *objectHandle;
    u32 effectHandle;
  };
  union {
    ONE_SHOT_HIT_DATA oneShotHit;
    INTERVAL_HIT_DATA intervalHit;
  };
  EffectMoveComponent move;
  u32 id;
  u32 attackId;
  f32 frame;
  f32 lifeTime;
  u16 bulletId;
  u16 bulletEffectId;
  u8 artsSlot;
  u8 hit;
  u8 fadeFrame;
  u8 objectType;
  u8 hitType;
  u8 additionalAttackNum;
  u8 isEnd : 1;
  u8 isRotation : 1;
  u8 isArts : 1;
  u8 isHitEnable : 1;
};

static_assert(offsetof(EffectObject, attacker) == 0x48, "");
static_assert(offsetof(EffectObject, endEffect) == 0x58, "");
static_assert(offsetof(EffectObject, position) == 0x80, "");
static_assert(offsetof(EffectObject, scale) == 0xb0, "");
static_assert(offsetof(EffectObject, objectHandle) == 0xc0, "");
static_assert(offsetof(EffectObject, oneShotHit) == 0xc8, "");
static_assert(offsetof(EffectObject::INTERVAL_HIT_DATA, hitTimers) == 0xa, "");
static_assert(offsetof(EffectObject, move) == 0x190, "");
static_assert(offsetof(EffectObject, id) == 0x240, "");
static_assert(offsetof(EffectObject, bulletId) == 0x250, "");
static_assert(offsetof(EffectObject, objectType) == 0x257, "");
static_assert(sizeof(EffectObject) == 0x260, "");

} // namespace btl
