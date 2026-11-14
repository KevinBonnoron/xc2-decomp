#include "gf/field/gf_field_time.h"

#include <math.h>

#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/gf_allocator.h"
#include "ml/time_util.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr u32 TIME_RANGE_UNKNOWN_6_2 = 6;            // Inferred role: time range count; original name unknown.
constexpr u32 TIME_RANGE_UNKNOWN_32 = 32;            // Inferred role: time range bit count; original name unknown.
constexpr u32 START_UNKNOWN_7 = 7;                   // Inferred role: start hour; original name unknown.
constexpr u32 HOURS_UNKNOWN_24 = 24;                 // Inferred role: hours per day; original name unknown.
constexpr u32 MINUTES_PER_UNKNOWN_60 = 60;           // Inferred role: minutes per hour; original name unknown.
constexpr u32 SECONDS_PER_UNKNOWN_3600 = 3600;       // Inferred role: seconds per hour; original name unknown.
constexpr u32 SECONDS_PER_UNKNOWN_86400 = 86400;     // Inferred role: seconds per day; original name unknown.
constexpr u32 SECONDS_PER_UNKNOWN_5184000 = 5184000; // Inferred role: seconds per year; original name unknown.
constexpr u32 MINUTES_PER_UNKNOWN_86400 = 86400;     // Inferred role: minutes per year; original name unknown.
constexpr u32 MINUTES_PER_UNKNOWN_1440 = 1440;       // Inferred role: minutes per day; original name unknown.
constexpr u32 DIFF_UNKNOWN_4 = 4;                    // Inferred role: year diff max; original name unknown.
constexpr f32 unknown041 = 1800.0f;                  // Inferred role: game time per hour; original name unknown.
constexpr f32 unknown042 = 30.0f;                    // Inferred role: game time per minute; original name unknown.
constexpr f32 unknown043 = 43200.0f;                 // Inferred role: game time per day; original name unknown.
constexpr f32 unknown044 = 60.0f;                    // Inferred role: game time scale; original name unknown.

static unknown131 s_rangeData[TIME_RANGE_UNKNOWN_6_2] = {
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
  setTime(START_UNKNOWN_7, 0);
  GfDataManager::getDataGame()->unknown1098c0 = m_gameTime;
}

u32 GfFieldTime::getTimeRange(u32 hour, u32 minute) const {
  for (u32 i = 0; i < TIME_RANGE_UNKNOWN_6_2; i++) {
    const unknown131 &rangeData = s_rangeData[i];
    if (rangeData.unknown00 <= hour && hour <= rangeData.unknown04 && rangeData.unknown02 <= minute && minute <= rangeData.unknown06) {
      return i;
    }
  }

  return TIME_RANGE_UNKNOWN_0;
}

u32 GfFieldTime::getTimeRangeDN() const { return m_timeRange < TIME_RANGE_UNKNOWN_3 ? TIME_RANGE_UNKNOWN_6 : TIME_RANGE_UNKNOWN_7; }

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
  unknown30 = unknown34 = calcGameTime(fmodf(gameTime.unknown01_4, HOURS_UNKNOWN_24), fmodf(gameTime.unknown00_6, MINUTES_PER_UNKNOWN_60));
  m_gameTime = gameTime;
  m_timeRange = getTimeRange(gameTime.unknown01_4, gameTime.unknown00_6);
  unknown48 = getTimeRangeDN();
  saveRealTime();
}

void GfFieldTime::setTimeStop(bool isStop) {
  if (isStop) {
    unknown0c |= TIME_STOP_BIT_UNKNOWN_0;
  } else {
    unknown0c &= ~TIME_STOP_BIT_UNKNOWN_0;
  }
}

void GfFieldTime::gevReloadBdat(RELOAD_BDAT, u32) {}

void GfFieldTime::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldTime(param); }

void GfFieldTime::destroy() {
  GfFieldTime *time = get();
  time->finalize();
  delete time;
}

void GfFieldTime::finalize() { unknown08 = false; }

bool GfFieldTime::isTimeStop() const { return (unknown0c & (TIME_STOP_BIT_UNKNOWN_0 | TIME_STOP_BIT_UNKNOWN_1)) != 0; }

void GfFieldTime::saveRealTime() { getRealTime(unknown18); }

void GfFieldTime::updateElapseTime(const fw::UpdateInfo &) {
  RealTime realTime;
  getRealTime(realTime);
  s32 diff = diffRealTimeSec(realTime, unknown20);
  if (diff > 0) {
    ElapseTime elapseTime;
    elapseTime.unknown00_0 = diff % SECONDS_PER_UNKNOWN_3600 % SECONDS_UNKNOWN_60;
    elapseTime.unknown00_6 = diff % SECONDS_PER_UNKNOWN_3600 / SECONDS_UNKNOWN_60;
    elapseTime.unknown01_4 = diff / SECONDS_PER_UNKNOWN_3600;
    m_elapseTime = unknown10 + elapseTime;
  }
}

s32 GfFieldTime::diffRealTimeSec(const RealTime &realTime, const RealTime &baseRealTime) const {
  s32 diff = (realTime.unknown02_0 - baseRealTime.unknown02_0) + (realTime.unknown02_6 - baseRealTime.unknown02_6) * SECONDS_UNKNOWN_60 +
             (realTime.unknown03_4 - baseRealTime.unknown03_4) * SECONDS_PER_UNKNOWN_3600 + (realTime.unknown04_6 - baseRealTime.unknown04_6) * SECONDS_PER_UNKNOWN_86400;
  if (realTime.unknown06_3 < baseRealTime.unknown06_3 + DIFF_UNKNOWN_4) {
    diff += (realTime.unknown06_3 - baseRealTime.unknown06_3) * SECONDS_PER_UNKNOWN_5184000;
  }

  return diff;
}

f32 GfFieldTime::calcGameTime(f32 hour, f32 minute) const { return hour * unknown041 + minute * unknown042; }

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
  hour = fmodf(time / unknown041, HOURS_UNKNOWN_24);
  minute = fmodf(time / unknown042, MINUTES_PER_UNKNOWN_60);
  return fmodf(time, unknown043) * 2.0f;
}

u32 GfFieldTime::getDay() const { return m_gameTime.unknown02_1; }

u32 GfFieldTime::getSec() const { return m_gameTime.unknown00_0; }

u32 GfFieldTime::getTime() const { return m_gameTime.unknown01_4 * SECONDS_PER_UNKNOWN_3600 + m_gameTime.unknown00_6 * SECONDS_UNKNOWN_60 + m_gameTime.unknown00_0; }

void GfFieldTime::setTimeSpeed(f32 timeSpeed) { m_timeSpeed = timeSpeed; }

ElapseTime operator+(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime) {
  s32 hour = elapseTime.unknown01_4 + otherElapseTime.unknown01_4;
  s32 minute = elapseTime.unknown00_6 + otherElapseTime.unknown00_6;
  s32 second = elapseTime.unknown00_0 + otherElapseTime.unknown00_0;
  while (second >= 60) {
    minute++;
    second -= 60;
  }
  while (minute >= 60) {
    hour++;
    minute -= 60;
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

f32 GfFieldTime::toRealTime(f32 gameTime) const { return gameTime / unknown044; }

f32 GfFieldTime::toGameTime(f32 realTime) const { return realTime * unknown044; }

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
  for (u32 i = 0; i < TIME_RANGE_UNKNOWN_32; i++) {
    if ((timeRangeBits & bit) != 0) {
      setTimeRange(i);
      return;
    }
    bit <<= 1;
  }
}

u32 GfFieldTime::getTimeRangeBits(u32 timeRange) const { return 1 << timeRange; }

s32 GfFieldTime::diffRealTimeMin(const RealTime &realTime, const RealTime &baseRealTime) const {
  return (realTime.unknown02_6 - baseRealTime.unknown02_6) + (realTime.unknown03_4 - baseRealTime.unknown03_4) * MINUTES_PER_UNKNOWN_60 +
         (realTime.unknown04_6 - baseRealTime.unknown04_6) * MINUTES_PER_UNKNOWN_1440 + (realTime.unknown06_3 - baseRealTime.unknown06_3) * MINUTES_PER_UNKNOWN_86400;
}

f32 GfFieldTime::diffRealTime(const RealTime &realTime, const RealTime &baseRealTime) const {
  return diffRealTimeSec(realTime, baseRealTime) + static_cast<s32>(realTime.unknown00_6 - baseRealTime.unknown00_6) * 0.001f;
}

void GfFieldTime::setFieldScriptTimeStop(bool isStop) {
  if (isStop) {
    unknown0c |= TIME_STOP_BIT_UNKNOWN_1;
  } else {
    unknown0c &= ~TIME_STOP_BIT_UNKNOWN_1;
  }
}

void GfFieldTime::setDebugStop(bool isStop) { m_debugStop = isStop; }

bool GfFieldTime::isDebugStop() const { return m_debugStop; }

GameTime operator+(const GameTime &gameTime, const GameTime &otherGameTime) {
  u32 second = gameTime.unknown00_0 + otherGameTime.unknown00_0;
  u32 minute = gameTime.unknown00_6 + otherGameTime.unknown00_6;
  u32 hour = gameTime.unknown01_4 + otherGameTime.unknown01_4;
  u32 day = gameTime.unknown02_1 + otherGameTime.unknown02_1;
  if (second >= SECONDS_UNKNOWN_60) {
    second -= SECONDS_UNKNOWN_60;
    minute++;
  }
  if (minute >= MINUTES_PER_UNKNOWN_60) {
    minute -= MINUTES_PER_UNKNOWN_60;
    hour++;
  }
  if (hour >= HOURS_UNKNOWN_24) {
    hour -= HOURS_UNKNOWN_24;
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
    second += SECONDS_UNKNOWN_60;
    minute--;
  }
  if (minute < 0) {
    minute += MINUTES_PER_UNKNOWN_60;
    hour--;
  }
  if (hour < 0) {
    hour += HOURS_UNKNOWN_24;
    day--;
  }

  GameTime result;
  result.unknown00_0 = second;
  result.unknown00_6 = minute;
  result.unknown01_4 = hour;
  result.unknown02_1 = day;
  return result;
}

u32 GameTime::convMin() const { return unknown02_1 * MINUTES_PER_UNKNOWN_1440 + unknown01_4 * MINUTES_PER_UNKNOWN_60 + unknown00_6; }

u32 GameTime::convSec() const { return unknown02_1 * SECONDS_PER_UNKNOWN_86400 + unknown01_4 * SECONDS_PER_UNKNOWN_3600 + unknown00_6 * SECONDS_UNKNOWN_60 + unknown00_0; }

ElapseTime operator-(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime) {
  s32 hour = elapseTime.unknown01_4 - otherElapseTime.unknown01_4;
  s32 minute = elapseTime.unknown00_6 - otherElapseTime.unknown00_6;
  s32 second = elapseTime.unknown00_0 - otherElapseTime.unknown00_0;
  if (second < 0) {
    second += SECONDS_UNKNOWN_60;
    minute--;
  }
  if (minute < 0) {
    minute += MINUTES_PER_UNKNOWN_60;
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
