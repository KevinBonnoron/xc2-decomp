#include "event/env_manager.h"

#include <stddef.h>

#include "framework/effect/effect_manager.h"
#include "fw/fw_debug.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

EnvManager::EnvManager()
    : flags(0), dispFlags(0), mClockHour(-1), mClockMinute(-1), mCloudType(EVT_CLOUDTYPE_DEFAULT), mColorFilterState(COLORFILTER_TYPE_STOP),
      mColorFilter(-1), mColorSubFilter(-1), mColorFilterFrame(0.0f), mColorFilterCount(0), mVignetteHandle(0) {}

void EnvManager::login() {
  mTransferField.clear();
  mTransferField.save();
}

void EnvManager::logout() {}

void EnvManager::updateColorFilter() {
  if (mColorFilterState != COLORFILTER_TYPE_FADE) {
    return;
  }
  if (static_cast<int>(mColorFilterFrame) <= mColorFilterCount++) {
    gf::GfGameEvent::setColorFilter(false, -1, -1, 0.0f);
    mColorFilterState = COLORFILTER_TYPE_STOP;
    mColorFilterFrame = 0.0f;
    stopVignette();
  }
}

void EnvManager::render() {
  if (!(dispFlags & DISP_FLAG_DISP)) {
    return;
  }
  gf::GfFieldTime *fieldTime = gf::GfFieldTime::get();
  if (fieldTime == nullptr) {
    return;
  }
  int width = ml::DevGraph::getRootWidth();
  int x = width - 150;
  int y = 160;
  fw::debug::drawSquare2D(mm::Rect<int>(x, y, 140, 70), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 140, 70), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 5, y + 5, "ENV");
  int labelX = x + 10;
  u32 hour;
  u32 minute;
  fieldTime->getTime(hour, minute);
  fw::debug::drawFont(labelX, y + 20, "clock:");
  int valueX = x + 90;
  fw::debug::drawFont(valueX, y + 20, "%02d:%02d", hour, minute);
  int weather = gf::GfFieldWeather::getCurrentMapWeatherID(false);
  fw::debug::drawFont(labelX, y + 35, "weather:");
  fw::debug::drawFont(valueX, y + 35, "%d", weather);
  int cloudSea = gf::GfFieldWeather::getCurrentCloudSea();
  fw::debug::drawFont(labelX, y + 50, "sea:");
  fw::debug::drawFont(valueX, y + 50, "%d", cloudSea);
}

void EnvManager::setClockStop(bool isStop) {
  if (((flags & FLAG_CLOCK_STOP) != 0) == isStop) {
    return;
  }
  if (gf::GfFieldTime::get() != nullptr) {
    gf::GfFieldTime::get()->setTimeStop(isStop);
  }
  if (isStop) {
    flags |= FLAG_CLOCK_STOP;
  } else {
    flags &= ~FLAG_CLOCK_STOP;
  }
}

void EnvManager::setClock(const char *clock) {
  size_t length = __builtin_strlen(clock);
  int hourTens = length > 0 ? (clock[0] - '0') * 10 : 0;
  int hourOnes = length > 1 ? clock[1] - '0' : 0;
  int minuteTens = length > 2 ? (clock[2] - '0') * 10 : 0;
  int minuteOnes = length > 3 ? clock[3] - '0' : 0;
  int hour = hourOnes + hourTens;
  int minute = minuteOnes + minuteTens;
  while (hour > 23) {
    hour -= 24;
  }
  while (minute > 59) {
    minute -= 60;
  }
  if (mClockHour != hour || mClockMinute != minute) {
    if (gf::GfFieldTime::get() != nullptr) {
      gf::GfFieldTime::get()->setTime(hour, minute);
    }
    mClockHour = hour;
    mClockMinute = minute;
  }
}

void EnvManager::setClock(f32 clock) {
  int hour = static_cast<int>(clock);
  int minute = static_cast<int>((clock - hour) * 60.0f);
  while (hour >= 24) {
    hour -= 24;
  }
  if (mClockHour != hour || mClockMinute != minute) {
    if (gf::GfFieldTime::get() != nullptr) {
      gf::GfFieldTime::get()->setTime(hour, minute);
    }
    mClockHour = hour;
    mClockMinute = minute;
  }
}

void EnvManager::setWeatherType(gf::WEATYPE type) {
  gf::GfGameEvent::setWeaType(type);
  flags |= FLAG_WEATHER_TYPE;
}

void EnvManager::setColorFilter(COLORFILTER_TYPE type, int filter, int subFilter, f32 frame) {
  switch (type) {
  case COLORFILTER_TYPE_STOP:
    if (mColorFilterState != COLORFILTER_TYPE_STOP) {
      gf::GfGameEvent::setColorFilter(false, -1, -1, frame / 30.0f);
      mColorFilterState = COLORFILTER_TYPE_STOP;
      mColorFilterFrame = frame;
      stopVignette();
    }
    break;
  case COLORFILTER_TYPE_PLAY:
    if (mColorFilterState != COLORFILTER_TYPE_PLAY || mColorFilter != filter || mColorSubFilter != subFilter || mColorFilterFrame != frame) {
      gf::GfGameEvent::setColorFilter(true, filter, subFilter, frame / 30.0f);
      mColorFilterState = COLORFILTER_TYPE_PLAY;
      mColorFilter = filter;
      mColorSubFilter = subFilter;
      mColorFilterFrame = frame;
      playVignette(filter, subFilter);
    }
    break;
  case COLORFILTER_TYPE_FADE:
    if (mColorFilterState == COLORFILTER_TYPE_PLAY) {
      gf::GfGameEvent::setColorFilter(true, -1, -1, frame / 30.0f);
      mColorFilterState = COLORFILTER_TYPE_FADE;
      mColorFilterFrame = frame;
      mColorFilterCount = 0;
      stopVignette();
    }
    mColorFilterFrame = frame;
    break;
  }
}

void EnvManager::stopVignette() {
  if (mVignetteHandle != 0) {
    fw::EffectManager::get()->dead(mVignetteHandle);
  }
  mVignetteHandle = 0;
}

void EnvManager::saveTransferEnvironment(u32 fromEventID, u32 toEventID) { mTransferEvent.save(fromEventID, toEventID); }

bool EnvManager::hasTransferEnvironment(u32 eventID) const { return mTransferEvent.has(eventID); }

void EnvManager::loadTransferEnvironment(u32 eventID) { mTransferEvent.load(eventID); }

void EnvManager::loadFieldEnvironment() { mTransferField.load(); }

void EnvManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool EnvManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void EnvManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT_BEGIN:
    login();
    break;
  case MSG_TYPE_INIT:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER_POST:
    render();
    break;
  default:
    break;
  }
}

} // namespace event
