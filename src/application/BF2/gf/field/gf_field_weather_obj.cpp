#include "gf/field/gf_field_weather_obj.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_pause.h"

namespace gf {

constexpr f32 SE_FADE_SEC = 4.0f;
constexpr f32 SE_VOLUME_SPEED_UP = 1.0f;
constexpr f32 SE_VOLUME_SPEED_DOWN = -0.5f;
constexpr f32 SE_VOLUME_SPEED_LEAVE = -1.0f;
constexpr f32 SE_VOLUME_ROOM = 0.5f;

WeatherEff::WeatherEff() : mIsErased(false), mAlpha(1.0f), mEffectHandle(0) {}

bool WeatherEff::isPlay() const { return mEffectHandle != 0; }

void WeatherEff::destroy() {
  if (mEffectHandle != 0) {
    fw::EffectManager::get()->remove(mEffectHandle);
    mEffectHandle = 0;
  }
}

void WeatherEff::fadeout() {
  if (mEffectHandle != 0) {
    if (GfGameManager::isFadeout()) {
      fw::EffectManager::get()->remove(mEffectHandle);
    } else {
      fw::EffectManager::get()->dead(mEffectHandle);
    }
    mEffectHandle = 0;
  }
}

bool WeatherEff::isEraseEffect() const {
  if (mIsErased || mType == WEATYPE_DEFAULT) {
    return false;
  }

  return GfGameManager::isRoom() || !GfFieldWeather::isDispWeather();
}

bool WeatherEff::isDispEffect() const {
  if (!mIsErased || mType == WEATYPE_DEFAULT || GfGameManager::isRoom()) {
    return false;
  }

  return GfFieldWeather::isDispWeather();
}

void WeatherEff::applyAlpha(const fw::UpdateInfo &) {
  if (mEffectHandle != 0) {
    fw::EffectManager::get()->setAlpha(mEffectHandle, mAlpha);
  }
}

void WeatherEff::setForceName(const char *) {}

void WeatherEff::setPause(bool) {}

WeatherSnd::WeatherSnd() : mType(WEATYPE_DEFAULT), mIsSkipped(false), mVolume(1.0f) {}

bool WeatherSnd::isPlay() const { return mSoundHandle.isValid(); }

void WeatherSnd::destroy() {
  SoundHandle &handle = mSoundHandle;
  if (handle.isValid()) {
    if (GfSound::get() != nullptr) {
      GfSound::get()->stopSe(handle, SE_FADE_SEC);
    }
    handle.clear();
  }
}

void WeatherSnd::fadeout() {
  GfSound *sound = GfSound::get();
  SoundHandle &handle = mSoundHandle;
  if (sound != nullptr && handle.isValid()) {
    sound->stopSe(handle, SE_FADE_SEC);
    handle.clear();
  }
}

void WeatherSnd::update(const fw::UpdateInfo &info, f32 rate, bool isFadeout) {
  GfSound *sound = GfSound::get();
  if (sound == nullptr) {
    return;
  }

  f32 speed = !GfGameManager::isRoom() && !isEraseSe() ? SE_VOLUME_SPEED_UP : SE_VOLUME_SPEED_DOWN;
  if (GfGameManager::isLeaveGameForDebug()) {
    speed = SE_VOLUME_SPEED_LEAVE;
  }
  mVolume += info.deltaTime * speed;

  f32 minVolume = GfGameManager::isRoom() ? SE_VOLUME_ROOM : 0.0f;
  if (isEraseSe()) {
    minVolume = 0.0f;
  }
  if (mVolume < minVolume) {
    mVolume = minVolume;
  } else if (mVolume > 1.0f) {
    mVolume = 1.0f;
  }

  SoundHandle &handle = mSoundHandle;
  if (handle.isValid() && !sound->isPlaying(handle)) {
    handle.clear();
  }

  if (isCreateSe(rate)) {
    if (!isFadeout) {
      create(mType);
    }
  } else if (mVolume * rate <= 0.0f) {
    mVolume = 0.0f;
    destroy();
  }

  applyVolume(info, rate);
}

bool WeatherSnd::isEraseSe() const {
  if (!GfFieldWeather::isDispWeather() || GfGameManager::isStartGame()) {
    return true;
  }

  return GfGameManager::isLeaveGameForDebug();
}

bool WeatherSnd::isCreateSe(f32 rate) const {
  if (mSoundHandle.isValid()) {
    return false;
  }

  if (mVolume * rate > 0.0f && GfFieldWeather::isDispWeather() && !GfGameManager::isStartGame()) {
    return !GfGameManager::isLeaveGameForDebug();
  }

  return false;
}

void WeatherSnd::applyVolume(const fw::UpdateInfo &, f32 rate) {
  if (mSoundHandle.isValid() && GfSound::get() != nullptr) {
    GfSound::get()->setVolume(mSoundHandle, mVolume * rate, 0.0f);
  }
}

void WeatherSnd::setPause(bool) {}

WeatherInfo::~WeatherInfo() {
  eff->destroy();
  snd->destroy();
  if (eff != nullptr) {
    delete eff;
    eff = nullptr;
  }
  if (snd != nullptr) {
    delete snd;
    snd = nullptr;
  }
}

void WeatherInfo::destroyEnv() {
  eff->destroy();
  snd->destroy();
}

bool WeatherInfo::isTimeRangeOK() const {
  if (weather >= WEATHER_A && weather <= WEATHER_D) {
    u32 timeBonus = GfDataMap::getWeatherTimeBonus(map, weather);
    if (GfFieldTime::get() != nullptr) {
      return (GfFieldTime::get()->getTimeRangeBits() & timeBonus) != 0;
    }
  }

  return true;
}

bool WeatherInfo::isTimeup() const { return pastSec == existSec; }

void WeatherInfo::fadeoutEnv() {
  eff->fadeout();
  snd->fadeout();
}

void WeatherInfo::update(const fw::UpdateInfo &info, bool isFadeout) {
  eff->update(info, fadeRate, isFadeout);
  snd->update(info, fadeRate, isFadeout);
  if (!GfPause::isPause(PAUSE_BIT_FIELD_TIME) && pastSec < existSec) {
    pastSec += info.deltaTime;
    if (pastSec > existSec) {
      pastSec = existSec;
    }
  }
}

bool WeatherInfo::updateFadein(const fw::UpdateInfo &info) {
  if (info.deltaTime > 0.0f && fadePastSec == 0.0f) {
    eff->create(type);
    snd->create(type);
  }

  if (fadePastSec >= fadeExistSec) {
    return true;
  }

  fadePastSec += info.deltaTime;
  if (fadePastSec >= fadeExistSec) {
    fadePastSec = fadeExistSec;
    fadeRate = 1.0f;
    return true;
  }

  fadeRate = fadePastSec / fadeExistSec;
  eff->update(info, fadeRate, false);
  snd->update(info, fadeRate, false);
  if (!GfPause::isPause(PAUSE_BIT_FIELD_TIME) && pastSec < existSec) {
    pastSec += info.deltaTime;
    if (pastSec > existSec) {
      pastSec = existSec;
    }
  }

  return false;
}

void WeatherInfo::createEnv() {
  eff->create(type);
  snd->create(type);
}

bool WeatherInfo::updateFadeout(const fw::UpdateInfo &info) {
  if (fadePastSec <= 0.0f) {
    return true;
  }

  fadePastSec -= info.deltaTime;
  if (fadePastSec <= 0.0f) {
    fadeRate = 0.0f;
    fadePastSec = 0.0f;
    return true;
  }

  fadeRate = fadePastSec / fadeExistSec;
  eff->update(info, fadeRate, true);
  snd->update(info, fadeRate, true);
  if (!GfPause::isPause(PAUSE_BIT_FIELD_TIME) && pastSec < existSec) {
    pastSec += info.deltaTime;
    if (pastSec > existSec) {
      pastSec = existSec;
    }
  }
  return false;
}

bool WeatherInfo::isTimeEnd() const {
  if (existSec > 0.0f) {
    return pastSec >= existSec;
  }

  return false;
}

bool WeatherInfo::isPlaySE() const { return snd->isPlay(); }

void WeatherInfo::setForceEffect(const char *effect) {
  eff->setForceName(effect);
  snd->setForceName(effect);
}

void WeatherInfo::resetParam(f32 pastSec, f32 existSec, f32 fadeExistSec) {
  this->pastSec = pastSec;
  this->existSec = existSec;
  this->fadeExistSec = fadeExistSec;
  fadePastSec = fadeExistSec;
  if (fadeExistSec > 0.0f) {
    fadeRate = fadePastSec / this->fadeExistSec;
  } else {
    fadeRate = 1.0f;
  }
}

void WeatherInfo::setPause(bool isPause) {
  eff->setPause(isPause);
  snd->setPause(isPause);
}

} // namespace gf
