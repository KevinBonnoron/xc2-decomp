#include "gf/field/gf_field_enemy_sensor.h"

#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_manager.h"

namespace gf {

void GfFieldEnemySensor::dispose() {
  unknownf0 = false;
  unknownac = false;
  unknowna8 = 0.0f;
  unknowna0.reset();
  unknown98 = false;
  unknown99 = false;
  unknown90 = 0.0f;
  unknown94 = 0.0f;
  unknown88.reset();
}

bool GfFieldEnemySensor::isPlayerEnter() const {
  if (unknown98 && unknown99) {
    return true;
  }

  if (unknownac) {
    return true;
  }

  return unknownf0;
}

f32 GfFieldEnemySensor::getEyeRadiusSq() const {
  f32 rate = static_cast<f32>(GfGameManager::getOwnerBonus()->unknown00[OWNER_BONUS_UNKNOWN_9]) * -0.01f + 1.0f;
  if (rate < 0.5f) {
    rate = 0.5f;
  } else if (rate > 1.0f) {
    rate = 1.0f;
  }

  return unknown90 * rate * rate;
}

void GfFieldEnemySensor::createByGmkBattleLock() {
  gmk::GmkAcc::CreateInfo createInfo;
  createInfo.unknown00 = unknown10.unknown48;
  createInfo.unknown04 = gmk::GMK_TYPE_BATTLE_LOCK;
  createInfo.unknown08 = unknown10.unknown4c;
  unknownb0.create(createInfo);
}

void GfFieldEnemySensor::enter(const EnterInfo &info) {
  if (unknown88.get() != info.object) {
    if (unknowna0.get() == info.object) {
      unknownac = true;
    }
  } else {
    unknown98 = true;
  }
}

void GfFieldEnemySensor::leave(const LeaveInfo &info) {
  if (unknown88.get() != info.object) {
    if (unknowna0.get() == info.object) {
      unknownac = false;
    }
  } else {
    unknown98 = false;
  }
}

} // namespace gf
