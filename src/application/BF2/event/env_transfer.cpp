#include "event/env_transfer.h"

#include "event/env_manager.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/event/gf_game_event.h"
#include "mm_mtl/singleton.h"

namespace event {

EnvTransfer::EnvTransfer() : mHour(0), mMinute(0), mWeather(gf::WEATHER_A) {}

void EnvTransfer::clear() {
  mWeather = gf::WEATHER_A;
  mHour = 0;
  mMinute = 0;
}

void EnvTransfer::save() {
  if (gf::GfFieldTime::get() != nullptr) {
    gf::GfFieldTime::get()->getTime(mHour, mMinute);
    mWeather = gf::GfFieldWeather::getCurrentMapWeatherID(false);
    mCloudSea = gf::GfFieldWeather::getCurrentCloudSea();
  }
}

void EnvTransfer::load() {
  if (gf::GfFieldTime::get() == nullptr) {
    return;
  }
  gf::GfFieldTime::get()->setTime(mHour, mMinute);
  gf::GfGameEvent::setMapWeather(mWeather);
  switch (mCloudSea) {
  case 0:
    mm::mtl::Singleton<EnvManager>::getPtr()->setCloudSea(EVT_CLOUDTYPE_LOW);
    break;
  case 1:
    mm::mtl::Singleton<EnvManager>::getPtr()->setCloudSea(EVT_CLOUDTYPE_HIGH);
    break;
  }
}

} // namespace event
