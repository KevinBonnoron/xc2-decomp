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
    f32 unknown00;  // Inferred role: time; original member name unknown.
    bool unknown04; // Inferred role: hit enabled; original member name unknown.
    bool unknown05; // Inferred role: hit on end; original member name unknown.
    bool unknown06; // Inferred role: end hit; original member name unknown.
    bool unknown07; // Inferred role: last attack; original member name unknown.
  };

  struct INTERVAL_HIT_DATA {
    f32 unknown00;                            // Inferred role: damage; original member name unknown.
    u16 unknown04;                            // Inferred role: radius; original member name unknown.
    s16 unknown06;                            // Inferred role: lifespan; original member name unknown.
    u8 unknown08;                             // Inferred role: interval; original member name unknown.
    u8 unknown09_0 : 1;                       // Inferred role: damage rate; original member name unknown.
    u8 unknown09_1 : 1;                       // Inferred role: special target; original member name unknown.
    u8 unknown09_2 : 1;                       // Inferred role: target friend; original member name unknown.
    u8 unknown09_3 : 1;                       // Inferred role: target enemy; original member name unknown.
    u16 unknowna[EFFECT_HIT_CHARACTER_COUNT]; // Inferred role: hit timers; original member name unknown.
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

  mm::mtl::FixedVector<fw::EffectPack *, 8> unknown00; // Inferred role: effect packs; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown48;                        // Inferred role: attacker; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown50;                        // Inferred role: target; original member name unknown.
  mm::mtl::FixStr<32> unknown58;                       // Inferred role: end effect name; original member name unknown.
  mm::Vec3 unknown80;                                  // Inferred role: position; original member name unknown.
  mm::Vec3 unknown90;                                  // Inferred role: direction; original member name unknown.
  mm::Vec3 unknowna0;                                  // Inferred role: rotation; original member name unknown.
  mm::Vec3 unknownb0;                                  // Inferred role: scale; original member name unknown.
  union {
    gf::GF_OBJ_HANDLE *unknownc0_0; // Inferred role: object handle; original member name unknown.
    u32 unknownc0_1;                // Inferred role: effect handle; original member name unknown.
  };
  union {
    ONE_SHOT_HIT_DATA unknownc8_0; // Inferred role: one shot hit data; original member name unknown.
    INTERVAL_HIT_DATA unknownc8_1; // Inferred role: interval hit data; original member name unknown.
  };
  EffectMoveComponent unknown190; // Inferred role: move component; original member name unknown.
  u32 unknown240;                 // Inferred role: id; original member name unknown.
  u32 unknown244;                 // Inferred role: attack id; original member name unknown.
  f32 unknown248;                 // Inferred role: frame; original member name unknown.
  f32 unknown24c;                 // Inferred role: life time; original member name unknown.
  u16 unknown250;                 // Inferred role: bullet id; original member name unknown.
  u16 unknown252;                 // Inferred role: bullet effect id; original member name unknown.
  u8 unknown254;                  // Inferred role: arts slot; original member name unknown.
  u8 unknown255;                  // Inferred role: hit; original member name unknown.
  u8 unknown256;                  // Inferred role: fade frame; original member name unknown.
  u8 unknown257;                  // Inferred role: object type; original member name unknown.
  u8 unknown258;                  // Inferred role: hit type; original member name unknown.
  u8 unknown259;                  // Inferred role: additional attack count; original member name unknown.
  u8 unknown25a_0 : 1;            // Inferred role: end; original member name unknown.
  u8 unknown25a_1 : 1;            // Inferred role: rotation; original member name unknown.
  u8 unknown25a_2 : 1;            // Inferred role: arts; original member name unknown.
  u8 unknown25a_3 : 1;            // Inferred role: hit enabled; original member name unknown.
};

static_assert(offsetof(EffectObject, unknown48) == 0x48, "");
static_assert(offsetof(EffectObject, unknown58) == 0x58, "");
static_assert(offsetof(EffectObject, unknown80) == 0x80, "");
static_assert(offsetof(EffectObject, unknownb0) == 0xb0, "");
static_assert(offsetof(EffectObject, unknownc0_0) == 0xc0, "");
static_assert(offsetof(EffectObject, unknownc8_0) == 0xc8, "");
static_assert(offsetof(EffectObject::INTERVAL_HIT_DATA, unknowna) == 0xa, "");
static_assert(offsetof(EffectObject, unknown190) == 0x190, "");
static_assert(offsetof(EffectObject, unknown240) == 0x240, "");
static_assert(offsetof(EffectObject, unknown250) == 0x250, "");
static_assert(offsetof(EffectObject, unknown257) == 0x257, "");
static_assert(sizeof(EffectObject) == 0x260, "");

} // namespace btl
