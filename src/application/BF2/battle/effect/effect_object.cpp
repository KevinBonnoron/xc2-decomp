#include "battle/effect/effect_object.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

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

} // namespace btl
