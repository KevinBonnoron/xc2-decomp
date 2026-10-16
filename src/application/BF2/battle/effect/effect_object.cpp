#include "battle/effect/effect_object.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"

namespace btl {

constexpr int ARTS_SLOT_NONE = 16;
constexpr int DEFAULT_FADE_FRAME = 4;
constexpr int INTERVAL_HIT_FADE_FRAME = 5;

EffectObject::EffectObject() : objectHandle(nullptr), id(0), objectType(OBJECT_TYPE_NONE) { Initialize(0); }

void EffectObject::Initialize(u32 id) {
  if (objectType == OBJECT_TYPE_EFFECT) {
    fw::EffectManager *effectManager = fw::EffectManager::get();
    if (effectManager != nullptr) {
      if (fadeFrame == 0) {
        effectManager->dead(effectHandle);
      } else {
        effectManager->fadeOutDead(effectHandle, fadeFrame);
      }
    }
  }

  effectPacks.clear();
  endEffect = "";
  direction = mm::Vec3::unitZ;
  rotation = mm::Vec3::zero;
  scale = mm::Vec3::unit;
  attacker = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  target = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  objectHandle = nullptr;
  this->id = id;
  attackId = 0;
  frame = 0.0f;
  lifeTime = 0.0f;
  bulletId = 0;
  bulletEffectId = 0;
  artsSlot = ARTS_SLOT_NONE;
  hit = 0;
  fadeFrame = DEFAULT_FADE_FRAME;
  objectType = OBJECT_TYPE_NONE;
  additionalAttackNum = 0;
  isEnd = true;
  isRotation = false;
  isArts = false;
  isHitEnable = true;
  move.Initialize();
  SetOneShotHitData(-1.0f, true);
}

void EffectObject::SetOneShotHitData(f32 time, bool isHitOnEnd) {
  oneShotHit.time = time;
  oneShotHit.isEnableHit = true;
  oneShotHit.isHitOnEnd = isHitOnEnd;
  oneShotHit.isEndHit = true;
  oneShotHit.isLastAttack = additionalAttackNum == 0;
  hitType = HIT_TYPE_ONE_SHOT;
}

void EffectObject::SetArtsData(int artsSlot, int hit, bool isArts, u32 attackId) {
  this->attackId = attackId;
  this->artsSlot = artsSlot;
  this->hit = hit;
  this->isArts = isArts;
}

void EffectObject::SetBulletData(int bulletId, int bulletEffectId) {
  this->bulletId = bulletId;
  this->bulletEffectId = bulletEffectId;
  additionalAttackNum = Bdat::getValCheck(gf::GfDataBdat::getFP(gf::BDAT_BTL_BULLET), "AddAtkNum", bulletId, 1);
  if (hitType == HIT_TYPE_ONE_SHOT) {
    oneShotHit.isLastAttack = !additionalAttackNum;
  }
}

void EffectObject::SetIntervalHitData(f32 radius, f32 damage, bool isDamageRate, f32 interval, f32 lifespan, bool isSpecialTarget,
                                      bool isTargetFriend, bool isTargetEnemy) {
  intervalHit.damage = damage;
  intervalHit.radius = radius * 100.0f;
  intervalHit.lifespan = lifespan;
  intervalHit.interval = interval;
  intervalHit.isDamageRate = isDamageRate;
  intervalHit.isSpecialTarget = isSpecialTarget;
  intervalHit.isTargetFriend = isTargetFriend;
  intervalHit.isTargetEnemy = isTargetEnemy;
  __builtin_memset(intervalHit.hitTimers, 0, sizeof(intervalHit.hitTimers));
  hitType = HIT_TYPE_INTERVAL;
  fadeFrame = INTERVAL_HIT_FADE_FRAME;
}

void EffectObject::SetMoveParam(const EffectMoveComponent::MOVE_PARAM &param) { move.Initialize(param); }

void EffectObject::SetEndEffect(const char *name) { endEffect = name; }

bool EffectObject::IsEnd() const {
  if (!isEnd) {
    return false;
  }
  return lifeTime <= 0.0f;
}

} // namespace btl
