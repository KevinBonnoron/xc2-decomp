#include "gf/field/gf_field_time.h"

#include <math.h>

#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/gf_allocator.h"
#include "ml/time_util.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr u32 TIME_RANGE_COUNT = 6;
constexpr u32 TIME_RANGE_BIT_COUNT = 32;
constexpr u32 START_HOUR = 7;
constexpr u32 HOURS_PER_DAY = 24;
constexpr u32 MINUTES_PER_HOUR = 60;
constexpr u32 SECONDS_PER_HOUR = 3600;
constexpr u32 SECONDS_PER_DAY = 86400;
constexpr u32 SECONDS_PER_YEAR = 5184000;
constexpr u32 MINUTES_PER_YEAR = 86400;
constexpr u32 MINUTES_PER_DAY = 1440;
constexpr u32 YEAR_DIFF_MAX = 4;
constexpr f32 GAME_TIME_PER_HOUR = 1800.0f;
constexpr f32 GAME_TIME_PER_MINUTE = 30.0f;
constexpr f32 GAME_TIME_PER_DAY = 43200.0f;
constexpr f32 GAME_TIME_SCALE = 60.0f;

static unknown131 s_rangeData[TIME_RANGE_COUNT] = {
    {7, 0, 11, 59},
    {12, 0, 15, 59},
    {16, 0, 18, 59},
    {19, 0, 23, 59},
    {0, 0, 4, 59},
    {5, 0, 6, 59},
};

GfFieldTime::GfFieldTime(const GfSetupParam &param) : unknown08(false), unknown0c(0), unknown10(), m_elapseTime(), unknown18(), unknown20(), m_gameTime(), m_debugStop(false) { initialize(param); }

void GfFieldTime::initialize(const GfSetupParam &) {
  clear();
  unknown08 = true;
}

GfFieldTime::~GfFieldTime() {}

void GfFieldTime::clear() {
  unknown0c = 0;
  unknown10 = ElapseTime();
  m_elapseTime = ElapseTime();
  unknown28 = 0;
  m_gameTime = GameTime();
  unknown30 = 0.0f;
  unknown34 = 0.0f;
  unknown38 = 0.0f;
  m_timeSpeed = 1.0f;
  unknown4c = 0;
  m_timeRange = getTimeRange(0, 0);
  unknown44 = m_timeRange;
  unknown48 = getTimeRangeDN();
  getRealTime(unknown20);
  unknown18 = unknown20;
  setTime(START_HOUR, 0);
  GfDataManager::getDataGame()->unknown1098c0 = m_gameTime;
}

u32 GfFieldTime::getTimeRange(u32 hour, u32 minute) const {
  for (u32 i = 0; i < TIME_RANGE_COUNT; i++) {
    const unknown131 &rangeData = s_rangeData[i];
    if (rangeData.unknown00 <= hour && hour <= rangeData.unknown04 && rangeData.unknown02 <= minute && minute <= rangeData.unknown06) {
      return i;
    }
  }

  return TIME_RANGE_MORNING;
}

u32 GfFieldTime::getTimeRangeDN() const { return m_timeRange < TIME_RANGE_EVENING ? TIME_RANGE_DAYTIME : TIME_RANGE_NIGHTTIME; }

void GfFieldTime::getRealTime(RealTime &realTime) const {
  ml::TimeInfo info;
  ml::TimeUtil::getTime(info);
  realTime.unknown06_3 = info.unknown06_2;
  realTime.unknown05_7 = info.unknown05_6;
  realTime.unknown04_6 = info.unknown04_5;
  realTime.unknown04_1 = info.unknown04_0;
  realTime.unknown03_4 = info.unknown03_2;
  realTime.unknown02_6 = info.unknown02_4;
  realTime.unknown02_0 = info.unknown01_6;
  realTime.unknown00_6 = info.unknown00_0;
}

void GfFieldTime::setTime(u32 hour, u32 minute) {
  unknown34 = unknown30 = calcGameTime(hour, minute);
  unknown38 = 0.0f;
  m_gameTime.unknown01_4 = hour;
  m_gameTime.unknown00_6 = minute;
  m_gameTime.unknown00_0 = 0;
  m_timeRange = getTimeRange(hour, minute);
  unknown48 = getTimeRangeDN();
  saveRealTime();
}

const GameTime &GfFieldTime::getGameTime() const { return m_gameTime; }

void GfFieldTime::setupGame() {
  setElapseTime(GfDataManager::getDataGame()->unknown1098c4);
  setGameTime(GfDataManager::getDataGame()->unknown1098c0);
  setTimeStop(GfDataManager::getDataGame()->unknown24 != 0);
}

void GfFieldTime::setElapseTime(const ElapseTime &elapseTime) {
  unknown10 = elapseTime;
  m_elapseTime = elapseTime;
  getRealTime(unknown20);
}

void GfFieldTime::setGameTime(const GameTime &gameTime) {
  unknown30 = unknown34 = calcGameTime(fmodf(gameTime.unknown01_4, HOURS_PER_DAY), fmodf(gameTime.unknown00_6, MINUTES_PER_HOUR));
  m_gameTime = gameTime;
  m_timeRange = getTimeRange(gameTime.unknown01_4, gameTime.unknown00_6);
  unknown48 = getTimeRangeDN();
  saveRealTime();
}

void GfFieldTime::setTimeStop(bool isStop) {
  if (isStop) {
    unknown0c |= TIME_STOP_BIT_GAME;
  } else {
    unknown0c &= ~TIME_STOP_BIT_GAME;
  }
}

void GfFieldTime::gevReloadBdat(RELOAD_BDAT, u32) {}

void GfFieldTime::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldTime(param); }

void GfFieldTime::destroy() {
  GfFieldTime *time = get();
  time->finalize();
  delete time;
}

void GfFieldTime::finalize() { unknown08 = false; }

bool GfFieldTime::isTimeStop() const { return (unknown0c & (TIME_STOP_BIT_GAME | TIME_STOP_BIT_FIELD_SCRIPT)) != 0; }

void GfFieldTime::saveRealTime() { getRealTime(unknown18); }

s32 GfFieldTime::diffRealTimeSec(const RealTime &realTime, const RealTime &baseRealTime) const {
  s32 diff = (realTime.unknown02_0 - baseRealTime.unknown02_0) + (realTime.unknown02_6 - baseRealTime.unknown02_6) * SECONDS_PER_MINUTE +
             (realTime.unknown03_4 - baseRealTime.unknown03_4) * SECONDS_PER_HOUR + (realTime.unknown04_6 - baseRealTime.unknown04_6) * SECONDS_PER_DAY;
  if (realTime.unknown06_3 < baseRealTime.unknown06_3 + YEAR_DIFF_MAX) {
    diff += (realTime.unknown06_3 - baseRealTime.unknown06_3) * SECONDS_PER_YEAR;
  }

  return diff;
}

f32 GfFieldTime::calcGameTime(f32 hour, f32 minute) const { return hour * GAME_TIME_PER_HOUR + minute * GAME_TIME_PER_MINUTE; }

const char *GfFieldTime::getTimeRangeName() const { return GfDataMap::getTimeRangeName(m_timeRange); }

u32 GfFieldTime::getTimeRange() const { return m_timeRange; }

bool GfFieldTime::getTimeRangeName(u8 *&bdat, u32 &textId) const { return GfDataMap::getTimeRangeName(bdat, textId, m_timeRange); }

void GfFieldTime::getGameTime(mm::mtl::FixStr<16> &string) const {
  mm::mtl::FixStr<16> work;
  work.format("%2d", m_gameTime.unknown01_4);
  string = work.c_str();
  string += ":";
  work.format("%02d", m_gameTime.unknown00_6);
  string += work.c_str();
}

u32 GfFieldTime::getHour() const { return m_gameTime.unknown01_4; }

u32 GfFieldTime::getMin() const { return m_gameTime.unknown00_6; }

void GfFieldTime::getElapseTime(mm::mtl::FixStr<16> &string) const {
  mm::mtl::FixStr<16> work;
  work.format("%2d", m_elapseTime.unknown01_4);
  string = work.c_str();
  string += ":";
  work.format("%02d", m_elapseTime.unknown00_6);
  string += work.c_str();
  string += ":";
  work.format("%02d", m_elapseTime.unknown00_0);
  string += work.c_str();
}

const ElapseTime &GfFieldTime::getElapseTime() const { return m_elapseTime; }

void GfFieldTime::nextDay() { m_gameTime.unknown02_1++; }

void GfFieldTime::setDay(u32 day) {
  m_gameTime.unknown02_1 = day;
  saveRealTime();
}

void GfFieldTime::setHour(u32 hour) {
  u32 minute = getMin();
  unknown34 = unknown30 = calcGameTime(hour, minute);
  unknown38 = 0.0f;
  m_gameTime.unknown01_4 = hour;
  m_gameTime.unknown00_6 = minute;
  m_gameTime.unknown00_0 = 0;
  m_timeRange = getTimeRange(hour, 0);
  unknown48 = getTimeRangeDN();
  saveRealTime();
}

void GfFieldTime::setMin(u32 minute) {
  u32 hour = getHour();
  unknown34 = unknown30 = calcGameTime(hour, minute);
  unknown38 = 0.0f;
  m_gameTime.unknown01_4 = hour;
  m_gameTime.unknown00_6 = minute;
  m_gameTime.unknown00_0 = 0;
  saveRealTime();
}

u32 GfFieldTime::getTime(u32 &hour, u32 &minute) const {
  f32 time = unknown30;
  hour = fmodf(time / GAME_TIME_PER_HOUR, HOURS_PER_DAY);
  minute = fmodf(time / GAME_TIME_PER_MINUTE, MINUTES_PER_HOUR);
  return fmodf(time, GAME_TIME_PER_DAY) * 2.0f;
}

u32 GfFieldTime::getDay() const { return m_gameTime.unknown02_1; }

u32 GfFieldTime::getSec() const { return m_gameTime.unknown00_0; }

u32 GfFieldTime::getTime() const { return m_gameTime.unknown01_4 * SECONDS_PER_HOUR + m_gameTime.unknown00_6 * SECONDS_PER_MINUTE + m_gameTime.unknown00_0; }

void GfFieldTime::setTimeSpeed(f32 timeSpeed) { m_timeSpeed = timeSpeed; }

ElapseTime operator+(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime) {
  s32 hour = elapseTime.unknown01_4 + otherElapseTime.unknown01_4;
  s32 minute = elapseTime.unknown00_6 + otherElapseTime.unknown00_6;
  s32 second = elapseTime.unknown00_0 + otherElapseTime.unknown00_0;
  while (second >= 60) {
    second -= 60;
    minute++;
  }
  while (minute >= 60) {
    minute -= 60;
    hour++;
  }

  ElapseTime result;
  result.unknown00_0 = second;
  result.unknown00_6 = minute;
  result.unknown01_4 = hour;
  if (hour > 9999) {
    result.unknown00_0 = 59;
    result.unknown00_6 = 59;
    result.unknown01_4 = 9999;
  }

  return result;
}

f32 GfFieldTime::toRealTime(f32 gameTime) const { return gameTime / GAME_TIME_SCALE; }

f32 GfFieldTime::toGameTime(f32 realTime) const { return realTime * GAME_TIME_SCALE; }

const unknown131 *GfFieldTime::getRangeData(u32 timeRange) const { return &s_rangeData[timeRange]; }

void GfFieldTime::setTimeRange(u32 timeRange) {
  const unknown131 *rangeData = getRangeData(timeRange);
  setTime(rangeData->unknown00, rangeData->unknown02);
}

void GfFieldTime::setTimeRangeBit(u32 timeRangeBits) {
  if (timeRangeBits == 0) {
    return;
  }

  u32 bit = 1;
  for (u32 i = 0; i < TIME_RANGE_BIT_COUNT; i++) {
    if ((timeRangeBits & bit) != 0) {
      setTimeRange(i);
      return;
    }
    bit <<= 1;
  }
}

u32 GfFieldTime::getTimeRangeBits(u32 timeRange) const { return 1 << timeRange; }

s32 GfFieldTime::diffRealTimeMin(const RealTime &realTime, const RealTime &baseRealTime) const {
  return (realTime.unknown02_6 - baseRealTime.unknown02_6) + (realTime.unknown03_4 - baseRealTime.unknown03_4) * MINUTES_PER_HOUR +
         (realTime.unknown04_6 - baseRealTime.unknown04_6) * MINUTES_PER_DAY + (realTime.unknown06_3 - baseRealTime.unknown06_3) * MINUTES_PER_YEAR;
}

f32 GfFieldTime::diffRealTime(const RealTime &realTime, const RealTime &baseRealTime) const {
  return diffRealTimeSec(realTime, baseRealTime) + static_cast<s32>(realTime.unknown00_6 - baseRealTime.unknown00_6) * 0.001f;
}

void GfFieldTime::setFieldScriptTimeStop(bool isStop) {
  if (isStop) {
    unknown0c |= TIME_STOP_BIT_FIELD_SCRIPT;
  } else {
    unknown0c &= ~TIME_STOP_BIT_FIELD_SCRIPT;
  }
}

void GfFieldTime::setDebugStop(bool isStop) { m_debugStop = isStop; }

bool GfFieldTime::isDebugStop() const { return m_debugStop; }

GameTime operator+(const GameTime &gameTime, const GameTime &otherGameTime) {
  u32 second = gameTime.unknown00_0 + otherGameTime.unknown00_0;
  u32 minute = gameTime.unknown00_6 + otherGameTime.unknown00_6;
  u32 hour = gameTime.unknown01_4 + otherGameTime.unknown01_4;
  u32 day = gameTime.unknown02_1 + otherGameTime.unknown02_1;
  if (second >= SECONDS_PER_MINUTE) {
    second -= SECONDS_PER_MINUTE;
    minute++;
  }
  if (minute >= MINUTES_PER_HOUR) {
    minute -= MINUTES_PER_HOUR;
    hour++;
  }
  if (hour >= HOURS_PER_DAY) {
    hour -= HOURS_PER_DAY;
    day++;
  }

  GameTime result;
  result.unknown00_0 = second;
  result.unknown00_6 = minute;
  result.unknown01_4 = hour;
  result.unknown02_1 = day;
  return result;
}

GameTime operator-(const GameTime &gameTime, const GameTime &otherGameTime) {
  s32 second = gameTime.unknown00_0 - otherGameTime.unknown00_0;
  s32 minute = gameTime.unknown00_6 - otherGameTime.unknown00_6;
  s32 hour = gameTime.unknown01_4 - otherGameTime.unknown01_4;
  s32 day = gameTime.unknown02_1 - otherGameTime.unknown02_1;
  if (second < 0) {
    second += SECONDS_PER_MINUTE;
    minute--;
  }
  if (minute < 0) {
    minute += MINUTES_PER_HOUR;
    hour--;
  }
  if (hour < 0) {
    hour += HOURS_PER_DAY;
    day--;
  }

  GameTime result;
  result.unknown00_0 = second;
  result.unknown00_6 = minute;
  result.unknown01_4 = hour;
  result.unknown02_1 = day;
  return result;
}

u32 GameTime::convMin() const { return unknown02_1 * MINUTES_PER_DAY + unknown01_4 * MINUTES_PER_HOUR + unknown00_6; }

u32 GameTime::convSec() const { return unknown02_1 * SECONDS_PER_DAY + unknown01_4 * SECONDS_PER_HOUR + unknown00_6 * SECONDS_PER_MINUTE + unknown00_0; }

ElapseTime operator-(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime) {
  s32 hour = elapseTime.unknown01_4 - otherElapseTime.unknown01_4;
  s32 minute = elapseTime.unknown00_6 - otherElapseTime.unknown00_6;
  s32 second = elapseTime.unknown00_0 - otherElapseTime.unknown00_0;
  if (second < 0) {
    second += SECONDS_PER_MINUTE;
    minute--;
  }
  if (minute < 0) {
    minute += MINUTES_PER_HOUR;
    hour--;
  }

  ElapseTime result;
  result.unknown00_0 = second;
  result.unknown00_6 = minute;
  result.unknown01_4 = hour;
  if (hour < 0) {
    result = ElapseTime();
  }

  return result;
}

void ElapseTime::getTime(mm::mtl::FixStr<16> &string) const {
  mm::mtl::FixStr<16> work;
  work.format("%d", unknown01_4);
  string = work.c_str();
  string += ":";
  if (unknown00_6 < 10) {
    string += "0";
  }
  work.format("%d", unknown00_6);
  string += work.c_str();
  string += ":";
  if (unknown00_0 < 10) {
    string += "0";
  }
  work.format("%d", unknown00_0);
  string += work.c_str();
}

} // namespace gf
