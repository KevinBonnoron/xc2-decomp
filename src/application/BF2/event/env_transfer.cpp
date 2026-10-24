#include "event/env_transfer.h"

#include "event/env_manager.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/event/gf_game_event.h"
#include "mm_mtl/singleton.h"

namespace event {

EnvTransfer::EnvTransfer() : unknown08(0), unknown0c(0), unknown10(gf::WEATHER_A) {}

void EnvTransfer::clear() {
  unknown10 = gf::WEATHER_A;
  unknown08 = 0;
  unknown0c = 0;
}

void EnvTransfer::save() {
  if (gf::GfFieldTime::get() != nullptr) {
    gf::GfFieldTime::get()->getTime(unknown08, unknown0c);
    unknown10 = gf::GfFieldWeather::getCurrentMapWeatherID(false);
    unknown14 = gf::GfFieldWeather::getCurrentCloudSea();
  }
}

void EnvTransfer::load() {
  if (gf::GfFieldTime::get() == nullptr) {
    return;
  }
  gf::GfFieldTime::get()->setTime(unknown08, unknown0c);
  gf::GfGameEvent::setMapWeather(unknown10);
  switch (static_cast<int>(unknown14)) {
  case 0:
    mm::mtl::Singleton<EnvManager>::getPtr()->setCloudSea(EVT_CLOUDTYPE_LOW);
    break;
  case 1:
    mm::mtl::Singleton<EnvManager>::getPtr()->setCloudSea(EVT_CLOUDTYPE_HIGH);
    break;
  }
}

} // namespace event
