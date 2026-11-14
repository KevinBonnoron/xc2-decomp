#include "battle/effect/effect_object.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/misc_battle.h"
#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_math.h"

#include <math.h>

namespace btl {

constexpr int ARTS_SLOT_NONE = 16;
constexpr int DEFAULT_FADE_FRAME = 4;
constexpr int INTERVAL_HIT_FADE_FRAME = 5;

EffectObject::EffectObject() : unknownc0_0(nullptr), unknown240(0), unknown257(OBJECT_TYPE_NONE) { Initialize(0); }

void EffectObject::Initialize(u32 id) {
  if (unknown257 == OBJECT_TYPE_EFFECT) {
    fw::EffectManager *effectManager = fw::EffectManager::get();
    if (effectManager != nullptr) {
      if (unknown256 == 0) {
        effectManager->dead(unknownc0_1);
      } else {
        effectManager->fadeOutDead(unknownc0_1, unknown256);
      }
    }
  }

  unknown00.clear();
  unknown58 = "";
  unknown90 = mm::Vec3::unitZ;
  unknowna0 = mm::Vec3::zero;
  unknownb0 = mm::Vec3::unit;
  unknown48 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown50 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknownc0_0 = nullptr;
  this->unknown240 = id;
  unknown244 = 0;
  unknown248 = 0.0f;
  unknown24c = 0.0f;
  unknown250 = 0;
  unknown252 = 0;
  unknown254 = ARTS_SLOT_NONE;
  unknown255 = 0;
  unknown256 = DEFAULT_FADE_FRAME;
  unknown257 = OBJECT_TYPE_NONE;
  unknown259 = 0;
  unknown25a_0 = true;
  unknown25a_1 = false;
  unknown25a_2 = false;
  unknown25a_3 = true;
  unknown190.Initialize();
  SetOneShotHitData(-1.0f, true);
}

void EffectObject::SetObject(gf::GF_OBJ_HANDLE *handle, mm::mtl::FixedVector<fw::EffectPack *, 8> &packs) {
  gf::GfObj *object = gf::GfObjUtil::getObj(handle);
  if (object != nullptr) {
    gf::GfComTransform *transform = object->getComponent<gf::GfComTransform>();
    if (transform != nullptr) {
      unknown257 = OBJECT_TYPE_OBJECT;
      unknownc0_0 = handle;
      unknown00 = packs;
      unknown80 = transform->getPosition();
      unknown25a_0 = false;
    }
  }
}

void EffectObject::SetOneShotHitData(f32 time, bool isHitOnEnd) {
  unknownc8_0.unknown00 = time;
  unknownc8_0.unknown04 = true;
  unknownc8_0.unknown05 = isHitOnEnd;
  unknownc8_0.unknown06 = true;
  unknownc8_0.unknown07 = unknown259 == 0;
  unknown258 = HIT_TYPE_ONE_SHOT;
}

void EffectObject::SetArtsData(int artsSlot, int hit, bool isArts, u32 attackId) {
  this->unknown244 = attackId;
  this->unknown254 = artsSlot;
  this->unknown255 = hit;
  this->unknown25a_2 = isArts;
}

void EffectObject::SetBulletData(int bulletId, int bulletEffectId) {
  this->unknown250 = bulletId;
  this->unknown252 = bulletEffectId;
  unknown259 = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BULLET), "AddAtkNum", bulletId, 1);
  if (unknown258 == HIT_TYPE_ONE_SHOT) {
    unknownc8_0.unknown07 = !unknown259;
  }
}

void EffectObject::SetIntervalHitData(f32 radius, f32 damage, bool isDamageRate, f32 interval, f32 lifespan, bool isSpecialTarget, bool isTargetFriend, bool isTargetEnemy) {
  unknownc8_1.unknown00 = damage;
  unknownc8_1.unknown04 = radius * 100.0f;
  unknownc8_1.unknown06 = lifespan;
  unknownc8_1.unknown08 = interval;
  unknownc8_1.unknown09_0 = isDamageRate;
  unknownc8_1.unknown09_1 = isSpecialTarget;
  unknownc8_1.unknown09_2 = isTargetFriend;
  unknownc8_1.unknown09_3 = isTargetEnemy;
  __builtin_memset(unknownc8_1.unknowna, 0, sizeof(unknownc8_1.unknowna));
  unknown258 = HIT_TYPE_INTERVAL;
  unknown256 = INTERVAL_HIT_FADE_FRAME;
}

void EffectObject::SetMoveParam(const EffectMoveComponent::MOVE_PARAM &param) { unknown190.Initialize(param); }

void EffectObject::SetEndEffect(const char *name) { unknown58 = name; }

bool EffectObject::IsEnd() const {
  if (!unknown25a_0) {
    return false;
  }
  return unknown24c <= 0.0f;
}

void EffectObject::ReturnLinkObj() {
  EffectMoveComponent::MOVE_PARAM param;
  param.unknown39 = EffectMoveComponent::MOVE_TYPE_LINK_OBJ;
  param.unknown10 = unknown190.unknown6c * 0.6f;
  param.unknown00 = mm::Vec3::unitY;
  param.unknown40_1.unknown40 = unknown48;
  gf::GfAppend *append = gf::GfObjUtil::getAppend(unknownc0_0, gf::GFATTACH_UNKNOWN_0);
  const BattleCharacter *character = CharacterManager::get()->GetCharacterConst(unknown48);
  param.unknown40_1.unknown48 = append->getBone(character->IsBlade() ? gf::OPTMNT_UNKNOWN_3 : gf::OPTMNT_UNKNOWN_1);
  param.unknown40_1.unknown50[0] = unknown80.x;
  param.unknown40_1.unknown50[1] = unknown80.y;
  param.unknown40_1.unknown50[2] = unknown80.z;
  s32 frame = character->GetAnimSpecialProcData(BattleCharacter::ANIM_SPDATA_TYPE_UNKNOWN_0);
  f32 time = __builtin_fmaxf(frame - unknown248, 0.0f);
  param.unknown40_1.unknown5c = time;
  f32 lifeTime = time * (1.0f / FRAME_RATE);
  param.unknown38 |= 0x10;
  param.unknown20[4] = lifeTime;
  unknown190.Initialize(param);
  unknown24c = lifeTime;
}

void EffectObject::ReboundUp() {
  s32 frame = CharacterManager::get()->GetCharacterConst(unknown48)->GetAnimSpecialProcData(BattleCharacter::ANIM_SPDATA_TYPE_UNKNOWN_0);
  f32 distance = __builtin_fmaxf(frame - unknown248, 0.0f);
  EffectMoveComponent::MOVE_PARAM param;
  f32 time = distance * (1.0f / 3.0f);
  param.unknown39 = EffectMoveComponent::MOVE_TYPE_UP;
  param.unknown40_2 = time;
  u8 upDist = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BULLET), "UpDist", unknown250, 1);
  f32 speed = upDist;
  if (time <= 0.0f) {
    param.unknown10 = speed;
  } else {
    param.unknown10 = speed / time;
  }
  param.unknown00 = mm::Vec3::unitY;
  f32 lifeTime = distance * (1.0f / FRAME_RATE);
  param.unknown38 |= 0x10;
  param.unknown20[4] = lifeTime;
  unknown190.Initialize(param);
  unknown24c = lifeTime;
}

void EffectObject::StartAdditionalAttack() {
  mm::Vec3 target;
  mm::Vec3 way;
  // The blocks are in the game's frame: direction and param share sp+0 (0x710007fbd8 / 0x710007fcfc), and cross and target
  // share x29-0x40 (0x710007fc3c / 0x710007fca4). Both blocks together give the 0xd0 frame.
  {
    mm::Vec3 direction = unknown190.unknown50;
    direction.x = -direction.x;
    direction.z = -direction.z;
    if (!Misc::NormalizeXZ(direction)) {
      direction = mm::Vec3::unitZ;
    }
    {
      mm::Vec3 cross;
      Misc::GetCrossDirection(direction, cross, ml::mtRandf1() < 0.5f ? Misc::CROSS_MODE_RIGHT : Misc::CROSS_MODE_LEFT);
      Misc::TurnDirectionAngle(direction, cross, ml::mtRandf1() * (50.0f * mm::DEG_TO_RAD), true);
    }
    direction.y = tanf(ml::mtRandf1(40.0f * mm::DEG_TO_RAD, 60.0f * mm::DEG_TO_RAD));
    Misc::Normalize(direction);
    target = direction * 3.5f;
    target += unknown80;
    way = direction;
    Misc::NormalizeXZ(way);
    way.y = tanf(78.0f * mm::DEG_TO_RAD);
    Misc::Normalize(way);
  }

  EffectMoveComponent::MOVE_PARAM param;
  param.unknown39 = EffectMoveComponent::MOVE_TYPE_PARABOLA;
  param.unknown00 = way;
  f32 time = __builtin_fmaxf(static_cast<u8>(Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BULLET), "AddAtkDelay", unknown250, 1)), 1.0f);
  f32 cosine = sqrtf(1.0f - way.y * way.y);
  f32 speed = Misc::CalcLengthXZ(unknown80, target) / time / cosine;
  param.unknown10 = speed;
  param.unknown14 = speed;
  param.unknown18 = 0.0f;
  // The game stores this zero explicitly (str xzr, [sp, #0x18] at 0x710007fd74 covers unknown18 and unknown1c), although the
  // constructor already zeroes it.
  param.unknown1c = 0.0f;
  param.unknown40_3.unknown40[0] = unknown80.x;
  param.unknown40_3.unknown40[1] = unknown80.y;
  param.unknown40_3.unknown40[2] = unknown80.z;
  param.unknown40_3.unknown4c[0] = target.x;
  param.unknown40_3.unknown4c[1] = target.y;
  param.unknown40_3.unknown4c[2] = target.z;
  // The game calls CalcLengthXZ (0x710007fdb8), stores the flags (0x710007fdc8), then the field (0x710007fdcc); writing the
  // call straight into the field gives the wrong store order.
  f32 length = Misc::CalcLengthXZ(unknown80, target);
  param.unknown38 |= 0x4;
  param.unknown20[2] = length;
  unknown190.Initialize(param);
  unknown25a_0 = false;
  if (unknown258 == HIT_TYPE_ONE_SHOT) {
    unknownc8_0.unknown04 = false;
    unknownc8_0.unknown05 = false;
    unknownc8_0.unknown06 = false;
    unknownc8_0.unknown07 = false;
  }
}

} // namespace btl
