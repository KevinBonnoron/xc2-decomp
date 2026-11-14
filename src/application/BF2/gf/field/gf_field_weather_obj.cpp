#include "gf/field/gf_field_weather_obj.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_pause.h"

namespace gf {

constexpr f32 unknown052 = 4.0f;  // Inferred role: se fade sec; original name unknown.
constexpr f32 unknown053 = 1.0f;  // Inferred role: se volume speed up; original name unknown.
constexpr f32 unknown054 = -0.5f; // Inferred role: se volume speed down; original name unknown.
constexpr f32 unknown055 = -1.0f; // Inferred role: se volume speed leave; original name unknown.
constexpr f32 unknown056 = 0.5f;  // Inferred role: se volume room; original name unknown.

WeatherEff::WeatherEff() : unknown0c(false), unknown10(1.0f), unknown14(0) {}

bool WeatherEff::isPlay() const { return unknown14 != 0; }

void WeatherEff::destroy() {
  if (unknown14 != 0) {
    fw::EffectManager::get()->remove(unknown14);
    unknown14 = 0;
  }
}

void WeatherEff::fadeout() {
  if (unknown14 != 0) {
    if (GfGameManager::isFadeout()) {
      fw::EffectManager::get()->remove(unknown14);
    } else {
      fw::EffectManager::get()->dead(unknown14);
    }
    unknown14 = 0;
  }
}

bool WeatherEff::isEraseEffect() const {
  if (unknown0c || unknown08 == WEATYPE_UNKNOWN_0) {
    return false;
  }

  return GfGameManager::isRoom() || !GfFieldWeather::isDispWeather();
}

bool WeatherEff::isDispEffect() const {
  if (!unknown0c || unknown08 == WEATYPE_UNKNOWN_0 || GfGameManager::isRoom()) {
    return false;
  }

  return GfFieldWeather::isDispWeather();
}

void WeatherEff::update(const fw::UpdateInfo &info, f32, bool) {
  if (unknown14 != 0) {
    if (isEraseEffect()) {
      unknown0c = true;
      unknown10 = 1.0f;
    } else if (!fw::EffectManager::get()->isExist(unknown14)) {
      unknown14 = 0;
    }
  }
  if (unknown0c) {
    if (isDispEffect()) {
      unknown0c = false;
      create(unknown08);
    }
    if (unknown0c && unknown10 > 0.0f) {
      unknown10 -= info.unknown04 * 4.0f;
      if (unknown10 < 0.0f) {
        unknown10 = 0.0f;
        destroy();
      }
      applyAlpha(info);
    }
  }
  applySpeed(info);
}

void WeatherEff::applyAlpha(const fw::UpdateInfo &) {
  if (unknown14 != 0) {
    fw::EffectManager::get()->setAlpha(unknown14, unknown10);
  }
}

void WeatherEff::applySpeed(const fw::UpdateInfo &info) {
  if (unknown14 != 0) {
    fw::EffectManager::get()->setSpeed(unknown14, info.unknown08);
  }
}

void WeatherEff::setForceName(const char *) {}

void WeatherEff::setPause(bool) {}

WeatherSnd::WeatherSnd() : unknown10(WEATYPE_UNKNOWN_0), unknown14(false), unknown18(1.0f) {}

bool WeatherSnd::isPlay() const { return unknown08.isValid(); }

void WeatherSnd::create(WEATYPE type) {
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return;
  }

  if (unknown10 != type) {
    unknown14 = false;
  }
  unknown10 = type;
  if (type == WEATYPE_UNKNOWN_0 || unknown14 || !GfFieldWeather::isDispWeather() || GfGameManager::isFadeout()) {
    return;
  }

  const char *name = GfDataMap::getWeatherSndName(type);
  if (name == nullptr) {
    return;
  }

  if (*name == '\0') {
    unknown14 = true;
    return;
  }

  SoundParam param(0, name);
  param.unknown38 = CATEGORY_WEATHER;
  unknown08 = sound->playSe(param);
  if (!unknown08.isValid()) {
    unknown14 = true;
  }
  const char *beginName = GfDataMap::getWeatherSndBeginName(type);
  if (beginName != nullptr && *beginName != '\0') {
    SoundParam beginParam(0, beginName);
    beginParam.unknown38 = CATEGORY_WEATHER;
    sound->playSe(beginParam);
  }
}

void WeatherSnd::destroy() {
  SoundHandle &handle = unknown08;
  if (handle.isValid()) {
    if (GfSound::get() != nullptr) {
      GfSound::get()->stopSe(handle, unknown052);
    }
    handle.clear();
  }
}

void WeatherSnd::fadeout() {
  GfSound *sound = GfSound::get();
  SoundHandle &handle = unknown08;
  if (sound != nullptr && handle.isValid()) {
    sound->stopSe(handle, unknown052);
    handle.clear();
  }
}

void WeatherSnd::update(const fw::UpdateInfo &info, f32 rate, bool isFadeout) {
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return;
  }

  f32 speed = !GfGameManager::isRoom() && !isEraseSe() ? unknown053 : unknown054;
  if (GfGameManager::isLeaveGameForDebug()) {
    speed = unknown055;
  }
  unknown18 += info.unknown04 * speed;

  f32 minVolume = GfGameManager::isRoom() ? unknown056 : 0.0f;
  if (isEraseSe()) {
    minVolume = 0.0f;
  }
  if (unknown18 < minVolume) {
    unknown18 = minVolume;
  } else if (unknown18 > 1.0f) {
    unknown18 = 1.0f;
  }

  SoundHandle &handle = unknown08;
  if (handle.isValid() && !sound->isPlaying(handle)) {
    handle.clear();
  }

  if (isCreateSe(rate)) {
    if (!isFadeout) {
      create(unknown10);
    }
  } else if (unknown18 * rate <= 0.0f) {
    unknown18 = 0.0f;
    destroy();
  }

  applyVolume(info, rate);
}

bool WeatherSnd::isRoomSe() const { return GfGameManager::isRoom(); }

bool WeatherSnd::isEraseSe() const {
  if (!GfFieldWeather::isDispWeather() || GfGameManager::isStartGame()) {
    return true;
  }

  return GfGameManager::isLeaveGameForDebug();
}

bool WeatherSnd::isCreateSe(f32 rate) const {
  if (unknown08.isValid()) {
    return false;
  }

  if (unknown18 * rate > 0.0f && GfFieldWeather::isDispWeather() && !GfGameManager::isStartGame()) {
    return !GfGameManager::isLeaveGameForDebug();
  }

  return false;
}

void WeatherSnd::applyVolume(const fw::UpdateInfo &, f32 rate) {
  if (unknown08.isValid() && GfSound::get() != nullptr) {
    GfSound::get()->setVolume(unknown08, unknown18 * rate, 0.0f);
  }
}

void WeatherSnd::setPause(bool) {}

WeatherInfo::~WeatherInfo() {
  unknown30->destroy();
  unknown38->destroy();
  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
}

void WeatherInfo::destroyEnv() {
  unknown30->destroy();
  unknown38->destroy();
}

bool WeatherInfo::isTimeRangeOK() const {
  if (unknown0c >= WEATHER_A && unknown0c <= WEATHER_D) {
    u32 timeBonus = GfDataMap::getWeatherTimeBonus(unknown18, unknown0c);
    if (GfFieldTime::get() != nullptr) {
      return (GfFieldTime::get()->getTimeRangeBits() & timeBonus) != 0;
    }
  }

  return true;
}

bool WeatherInfo::isTimeup() const { return unknown10 == unknown14; }

void WeatherInfo::fadeoutEnv() {
  unknown30->fadeout();
  unknown38->fadeout();
}

void WeatherInfo::update(const fw::UpdateInfo &info, bool isFadeout) {
  unknown30->update(info, unknown20, isFadeout);
  unknown38->update(info, unknown20, isFadeout);
  if (!GfPause::isPause(PAUSE_BIT_UNKNOWN_4) && unknown10 < unknown14) {
    unknown10 += info.unknown04;
    if (unknown10 > unknown14) {
      unknown10 = unknown14;
    }
  }
}

bool WeatherInfo::updateFadein(const fw::UpdateInfo &info) {
  if (info.unknown04 > 0.0f && unknown24 == 0.0f) {
    unknown30->create(unknown08);
    unknown38->create(unknown08);
  }

  if (unknown24 >= unknown28) {
    return true;
  }

  unknown24 += info.unknown04;
  if (unknown24 >= unknown28) {
    unknown24 = unknown28;
    unknown20 = 1.0f;
    return true;
  }

  unknown20 = unknown24 / unknown28;
  unknown30->update(info, unknown20, false);
  unknown38->update(info, unknown20, false);
  if (!GfPause::isPause(PAUSE_BIT_UNKNOWN_4) && unknown10 < unknown14) {
    unknown10 += info.unknown04;
    if (unknown10 > unknown14) {
      unknown10 = unknown14;
    }
  }

  return false;
}

void WeatherInfo::createEnv() {
  unknown30->create(unknown08);
  unknown38->create(unknown08);
}

bool WeatherInfo::updateFadeout(const fw::UpdateInfo &info) {
  if (unknown24 <= 0.0f) {
    return true;
  }

  unknown24 -= info.unknown04;
  if (unknown24 <= 0.0f) {
    unknown20 = 0.0f;
    unknown24 = 0.0f;
    return true;
  }

  unknown20 = unknown24 / unknown28;
  unknown30->update(info, unknown20, true);
  unknown38->update(info, unknown20, true);
  if (!GfPause::isPause(PAUSE_BIT_UNKNOWN_4) && unknown10 < unknown14) {
    unknown10 += info.unknown04;
    if (unknown10 > unknown14) {
      unknown10 = unknown14;
    }
  }
  return false;
}

bool WeatherInfo::isTimeEnd() const {
  if (unknown14 > 0.0f) {
    return unknown10 >= unknown14;
  }

  return false;
}

bool WeatherInfo::isPlaySE() const { return unknown38->isPlay(); }

void WeatherInfo::setForceEffect(const char *effect) {
  unknown30->setForceName(effect);
  unknown38->setForceName(effect);
}

void WeatherInfo::resetParam(f32 pastSec, f32 existSec, f32 fadeExistSec) {
  this->unknown10 = pastSec;
  this->unknown14 = existSec;
  this->unknown28 = fadeExistSec;
  unknown24 = fadeExistSec;
  if (fadeExistSec > 0.0f) {
    unknown20 = unknown24 / this->unknown28;
  } else {
    unknown20 = 1.0f;
  }
}

void WeatherInfo::setPause(bool isPause) {
  unknown30->setPause(isPause);
  unknown38->setPause(isPause);
}

} // namespace gf
