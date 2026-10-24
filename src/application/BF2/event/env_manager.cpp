#include "event/env_manager.h"

#include <stddef.h>

#include "event/manager.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_debug.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

EnvManager::EnvManager()
    : unknown10(0), unknown14(0), unknown18(-1), unknown1c(-1), unknown20(EVT_CLOUDTYPE_DEFAULT), unknown24(COLORFILTER_TYPE_STOP), unknown28(-1), unknown2c(-1), unknown30(0.0f), unknown34(0),
      unknown38(0) {}

void EnvManager::setCloudSea(EVT_cloudtype cloudType) {
  if (unknown20 != cloudType) {
    switch (cloudType) {
    case EVT_CLOUDTYPE_DEFAULT:
      gf::GfGameEvent::setCloudSea(false, false);
      break;
    case EVT_CLOUDTYPE_HIGH:
      gf::GfGameEvent::setCloudSea(true, true);
      break;
    case EVT_CLOUDTYPE_LOW:
      gf::GfGameEvent::setCloudSea(true, false);
      break;
    }
  }
  unknown20 = cloudType;
}

void EnvManager::setMotBlur(bool isEnable) {
  if (isEnable == ((unknown10 & FLAG_MOT_BLUR) != 0)) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setMotBlurOverride(true);
    parmAcc.setMotBlur(isEnable);
    unknown10 = isEnable ? unknown10 & ~FLAG_MOT_BLUR : unknown10 | FLAG_MOT_BLUR;
  }
}

void EnvManager::setToneMap(bool isEnable, f32 toneMap) {
  if (isEnable != ((unknown10 & FLAG_TONE_MAP) != 0)) {
    if (isEnable) {
      ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
      parmAcc.setOverrideToneMap(toneMap);
      unknown10 |= FLAG_TONE_MAP;
    } else {
      unknown10 &= ~FLAG_TONE_MAP;
    }
    unknown3c = toneMap;
  }
}

void EnvManager::login() {
  unknown60.clear();
  unknown60.save();
}

void EnvManager::logout() {}

void EnvManager::updateColorFilter() {
  if (unknown24 != COLORFILTER_TYPE_FADE) {
    return;
  }
  if (static_cast<int>(unknown30) <= unknown34++) {
    gf::GfGameEvent::setColorFilter(false, -1, -1, 0.0f);
    unknown24 = COLORFILTER_TYPE_STOP;
    unknown30 = 0.0f;
    stopVignette();
  }
}

void EnvManager::updateMotBlur() {
  if ((unknown10 & FLAG_MOT_BLUR) != 0) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setMotBlurOverride(true);
    parmAcc.setMotBlur(false);
  }
}

void EnvManager::updateToneMap() {
  if ((unknown10 & FLAG_TONE_MAP) != 0) {
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
    parmAcc.setOverrideToneMap(unknown3c);
  }
}

void EnvManager::render() {
  if (!(unknown14 & DISP_FLAG_DISP)) {
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
  if (((unknown10 & FLAG_CLOCK_STOP) != 0) == isStop) {
    return;
  }
  if (gf::GfFieldTime::get() != nullptr) {
    gf::GfFieldTime::get()->setTimeStop(isStop);
  }
  if (isStop) {
    unknown10 |= FLAG_CLOCK_STOP;
  } else {
    unknown10 &= ~FLAG_CLOCK_STOP;
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
  if (unknown18 != hour || unknown1c != minute) {
    if (gf::GfFieldTime::get() != nullptr) {
      gf::GfFieldTime::get()->setTime(hour, minute);
    }
    unknown18 = hour;
    unknown1c = minute;
  }
}

void EnvManager::setClock(f32 clock) {
  int hour = static_cast<int>(clock);
  int minute = static_cast<int>((clock - hour) * 60.0f);
  while (hour >= 24) {
    hour -= 24;
  }
  if (unknown18 != hour || unknown1c != minute) {
    if (gf::GfFieldTime::get() != nullptr) {
      gf::GfFieldTime::get()->setTime(hour, minute);
    }
    unknown18 = hour;
    unknown1c = minute;
  }
}

void EnvManager::setMapWeatherID(gf::WEATHERID weather, f32 frame) {
  gf::GfFieldWeather::getCurrentMapWeatherID(false);
  gf::GfGameEvent::setMapWeather(weather);
  ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
  parmAcc.setWeatherFrame(frame);
}

void EnvManager::setWeatherType(gf::WEATYPE type) {
  gf::GfGameEvent::setWeaType(type);
  unknown10 |= FLAG_WEATHER_TYPE;
}

void EnvManager::setColorFilter(COLORFILTER_TYPE type, int filter, int subFilter, f32 frame) {
  switch (type) {
  case COLORFILTER_TYPE_STOP:
    if (unknown24 != COLORFILTER_TYPE_STOP) {
      gf::GfGameEvent::setColorFilter(false, -1, -1, frame / 30.0f);
      unknown24 = COLORFILTER_TYPE_STOP;
      unknown30 = frame;
      stopVignette();
    }
    break;
  case COLORFILTER_TYPE_PLAY:
    if (unknown24 != COLORFILTER_TYPE_PLAY || unknown28 != filter || unknown2c != subFilter || unknown30 != frame) {
      gf::GfGameEvent::setColorFilter(true, filter, subFilter, frame / 30.0f);
      unknown24 = COLORFILTER_TYPE_PLAY;
      unknown28 = filter;
      unknown2c = subFilter;
      unknown30 = frame;
      playVignette(filter, subFilter);
    }
    break;
  case COLORFILTER_TYPE_FADE:
    if (unknown24 == COLORFILTER_TYPE_PLAY) {
      gf::GfGameEvent::setColorFilter(true, -1, -1, frame / 30.0f);
      unknown24 = COLORFILTER_TYPE_FADE;
      unknown30 = frame;
      unknown34 = 0;
      stopVignette();
    }
    unknown30 = frame;
    break;
  }
}

void EnvManager::stopVignette() {
  if (unknown38 != 0) {
    fw::EffectManager::get()->dead(unknown38);
  }
  unknown38 = 0;
}

void EnvManager::saveTransferEnvironment(u32 fromEventID, u32 toEventID) { unknown40.save(fromEventID, toEventID); }

bool EnvManager::hasTransferEnvironment(u32 eventID) const { return unknown40.has(eventID); }

void EnvManager::loadTransferEnvironment(u32 eventID) { unknown40.load(eventID); }

void EnvManager::loadFieldEnvironment() { unknown60.load(); }

void EnvManager::setAutoResetSceneEnable(bool isEnable) {
  ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
  parmAcc.setAutoResetScene(isEnable);
  if (isEnable) {
    unknown10 |= FLAG_AUTO_RESET_SCENE;
  } else {
    unknown10 &= ~FLAG_AUTO_RESET_SCENE;
  }
}

void EnvManager::resetScene() {
  ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->renderDrSys, 0);
  parmAcc.resetScene();
}

void EnvManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_DISP;
  } else {
    unknown14 &= ~DISP_FLAG_DISP;
  }
}

bool EnvManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

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
