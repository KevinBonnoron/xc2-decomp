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

static TimeRangeData s_rangeData[TIME_RANGE_COUNT] = {
    {7, 0, 11, 59},
    {12, 0, 15, 59},
    {16, 0, 18, 59},
    {19, 0, 23, 59},
    {0, 0, 4, 59},
    {5, 0, 6, 59},
};

GfFieldTime::GfFieldTime(const GfSetupParam &param) : mInitialized(false), mTimeStopBits(0), mBaseElapseTime(), mElapseTime(), mRealTime(), mElapseStartRealTime(), mGameTime(), mIsDebugStop(false) {
  initialize(param);
}

void GfFieldTime::initialize(const GfSetupParam &) {
  clear();
  mInitialized = true;
}

GfFieldTime::~GfFieldTime() {}

void GfFieldTime::clear() {
  mTimeStopBits = 0;
  mBaseElapseTime = ElapseTime();
  mElapseTime = ElapseTime();
  mUnused28 = 0;
  mGameTime = GameTime();
  mTime = 0.0f;
  mPrevTime = 0.0f;
  mTimeFraction = 0.0f;
  mTimeSpeed = 1.0f;
  mUnused4c = 0;
  mTimeRange = getTimeRange(0, 0);
  mPrevTimeRange = mTimeRange;
  mTimeRangeDN = getTimeRangeDN();
  getRealTime(mElapseStartRealTime);
  mRealTime = mElapseStartRealTime;
  setTime(START_HOUR, 0);
  GfDataManager::getDataGame()->gameTime = mGameTime;
}

u32 GfFieldTime::getTimeRange(u32 hour, u32 minute) const {
  for (u32 i = 0; i < TIME_RANGE_COUNT; i++) {
    const TimeRangeData &rangeData = s_rangeData[i];
    if (rangeData.startHour <= hour && hour <= rangeData.endHour && rangeData.startMinute <= minute && minute <= rangeData.endMinute) {
      return i;
    }
  }

  return TIME_RANGE_MORNING;
}

u32 GfFieldTime::getTimeRangeDN() const { return mTimeRange < TIME_RANGE_EVENING ? TIME_RANGE_DAYTIME : TIME_RANGE_NIGHTTIME; }

void GfFieldTime::getRealTime(RealTime &realTime) const {
  ml::TimeInfo info;
  ml::TimeUtil::getTime(info);
  realTime.year = info.year;
  realTime.month = info.month;
  realTime.dayOfYear = info.dayOfYear;
  realTime.day = info.day;
  realTime.hour = info.hour;
  realTime.minute = info.minute;
  realTime.second = info.second;
  realTime.millisecond = info.millisecond;
}

void GfFieldTime::setTime(u32 hour, u32 minute) {
  mPrevTime = mTime = calcGameTime(hour, minute);
  mTimeFraction = 0.0f;
  mGameTime.hour = hour;
  mGameTime.minute = minute;
  mGameTime.second = 0;
  mTimeRange = getTimeRange(hour, minute);
  mTimeRangeDN = getTimeRangeDN();
  saveRealTime();
}

const GameTime &GfFieldTime::getGameTime() const { return mGameTime; }

void GfFieldTime::setupGame() {
  setElapseTime(GfDataManager::getDataGame()->elapseTime);
  setGameTime(GfDataManager::getDataGame()->gameTime);
  setTimeStop(GfDataManager::getDataGame()->timeStop != 0);
}

void GfFieldTime::setElapseTime(const ElapseTime &elapseTime) {
  mBaseElapseTime = elapseTime;
  mElapseTime = elapseTime;
  getRealTime(mElapseStartRealTime);
}

void GfFieldTime::setGameTime(const GameTime &gameTime) {
  mTime = mPrevTime = calcGameTime(fmodf(gameTime.hour, HOURS_PER_DAY), fmodf(gameTime.minute, MINUTES_PER_HOUR));
  mGameTime = gameTime;
  mTimeRange = getTimeRange(gameTime.hour, gameTime.minute);
  mTimeRangeDN = getTimeRangeDN();
  saveRealTime();
}

void GfFieldTime::setTimeStop(bool isStop) {
  if (isStop) {
    mTimeStopBits |= TIME_STOP_BIT_GAME;
  } else {
    mTimeStopBits &= ~TIME_STOP_BIT_GAME;
  }
}

void GfFieldTime::gevReloadBdat(RELOAD_BDAT, u32) {}

void GfFieldTime::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldTime(param); }

void GfFieldTime::destroy() {
  GfFieldTime *time = get();
  time->finalize();
  delete time;
}

void GfFieldTime::finalize() { mInitialized = false; }

bool GfFieldTime::isTimeStop() const { return (mTimeStopBits & (TIME_STOP_BIT_GAME | TIME_STOP_BIT_FIELD_SCRIPT)) != 0; }

void GfFieldTime::saveRealTime() { getRealTime(mRealTime); }

s32 GfFieldTime::diffRealTimeSec(const RealTime &realTime, const RealTime &baseRealTime) const {
  s32 diff = (realTime.second - baseRealTime.second) + (realTime.minute - baseRealTime.minute) * SECONDS_PER_MINUTE + (realTime.hour - baseRealTime.hour) * SECONDS_PER_HOUR +
             (realTime.dayOfYear - baseRealTime.dayOfYear) * SECONDS_PER_DAY;
  if (realTime.year < baseRealTime.year + YEAR_DIFF_MAX) {
    diff += (realTime.year - baseRealTime.year) * SECONDS_PER_YEAR;
  }

  return diff;
}

f32 GfFieldTime::calcGameTime(f32 hour, f32 minute) const { return hour * GAME_TIME_PER_HOUR + minute * GAME_TIME_PER_MINUTE; }

const char *GfFieldTime::getTimeRangeName() const { return GfDataMap::getTimeRangeName(mTimeRange); }

u32 GfFieldTime::getTimeRange() const { return mTimeRange; }

bool GfFieldTime::getTimeRangeName(u8 *&bdat, u32 &textId) const { return GfDataMap::getTimeRangeName(bdat, textId, mTimeRange); }

void GfFieldTime::getGameTime(mm::mtl::FixStr<16> &string) const {
  mm::mtl::FixStr<16> work;
  work.format("%2d", mGameTime.hour);
  string = work.c_str();
  string += ":";
  work.format("%02d", mGameTime.minute);
  string += work.c_str();
}

u32 GfFieldTime::getHour() const { return mGameTime.hour; }

u32 GfFieldTime::getMin() const { return mGameTime.minute; }

void GfFieldTime::getElapseTime(mm::mtl::FixStr<16> &string) const {
  mm::mtl::FixStr<16> work;
  work.format("%2d", mElapseTime.hour);
  string = work.c_str();
  string += ":";
  work.format("%02d", mElapseTime.minute);
  string += work.c_str();
  string += ":";
  work.format("%02d", mElapseTime.second);
  string += work.c_str();
}

const ElapseTime &GfFieldTime::getElapseTime() const { return mElapseTime; }

void GfFieldTime::nextDay() { mGameTime.day++; }

void GfFieldTime::setDay(u32 day) {
  mGameTime.day = day;
  saveRealTime();
}

void GfFieldTime::setHour(u32 hour) {
  u32 minute = getMin();
  mPrevTime = mTime = calcGameTime(hour, minute);
  mTimeFraction = 0.0f;
  mGameTime.hour = hour;
  mGameTime.minute = minute;
  mGameTime.second = 0;
  mTimeRange = getTimeRange(hour, 0);
  mTimeRangeDN = getTimeRangeDN();
  saveRealTime();
}

void GfFieldTime::setMin(u32 minute) {
  u32 hour = getHour();
  mPrevTime = mTime = calcGameTime(hour, minute);
  mTimeFraction = 0.0f;
  mGameTime.hour = hour;
  mGameTime.minute = minute;
  mGameTime.second = 0;
  saveRealTime();
}

u32 GfFieldTime::getTime(u32 &hour, u32 &minute) const {
  f32 time = mTime;
  hour = fmodf(time / GAME_TIME_PER_HOUR, HOURS_PER_DAY);
  minute = fmodf(time / GAME_TIME_PER_MINUTE, MINUTES_PER_HOUR);
  return fmodf(time, GAME_TIME_PER_DAY) * 2.0f;
}

u32 GfFieldTime::getDay() const { return mGameTime.day; }

u32 GfFieldTime::getSec() const { return mGameTime.second; }

u32 GfFieldTime::getTime() const { return mGameTime.hour * SECONDS_PER_HOUR + mGameTime.minute * SECONDS_PER_MINUTE + mGameTime.second; }

void GfFieldTime::setTimeSpeed(f32 timeSpeed) { mTimeSpeed = timeSpeed; }

ElapseTime operator+(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime) {
  s32 hour = elapseTime.hour + otherElapseTime.hour;
  s32 minute = elapseTime.minute + otherElapseTime.minute;
  s32 second = elapseTime.second + otherElapseTime.second;
  while (second >= 60) {
    second -= 60;
    minute++;
  }
  while (minute >= 60) {
    minute -= 60;
    hour++;
  }

  ElapseTime result;
  result.second = second;
  result.minute = minute;
  result.hour = hour;
  if (hour > 9999) {
    result.second = 59;
    result.minute = 59;
    result.hour = 9999;
  }

  return result;
}

f32 GfFieldTime::toRealTime(f32 gameTime) const { return gameTime / GAME_TIME_SCALE; }

f32 GfFieldTime::toGameTime(f32 realTime) const { return realTime * GAME_TIME_SCALE; }

const TimeRangeData *GfFieldTime::getRangeData(u32 timeRange) const { return &s_rangeData[timeRange]; }

void GfFieldTime::setTimeRange(u32 timeRange) {
  const TimeRangeData *rangeData = getRangeData(timeRange);
  setTime(rangeData->startHour, rangeData->startMinute);
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
  return (realTime.minute - baseRealTime.minute) + (realTime.hour - baseRealTime.hour) * MINUTES_PER_HOUR + (realTime.dayOfYear - baseRealTime.dayOfYear) * MINUTES_PER_DAY +
         (realTime.year - baseRealTime.year) * MINUTES_PER_YEAR;
}

f32 GfFieldTime::diffRealTime(const RealTime &realTime, const RealTime &baseRealTime) const {
  return diffRealTimeSec(realTime, baseRealTime) + static_cast<s32>(realTime.millisecond - baseRealTime.millisecond) * 0.001f;
}

void GfFieldTime::setFieldScriptTimeStop(bool isStop) {
  if (isStop) {
    mTimeStopBits |= TIME_STOP_BIT_FIELD_SCRIPT;
  } else {
    mTimeStopBits &= ~TIME_STOP_BIT_FIELD_SCRIPT;
  }
}

void GfFieldTime::setDebugStop(bool isStop) { mIsDebugStop = isStop; }

bool GfFieldTime::isDebugStop() const { return mIsDebugStop; }

GameTime operator+(const GameTime &gameTime, const GameTime &otherGameTime) {
  u32 second = gameTime.second + otherGameTime.second;
  u32 minute = gameTime.minute + otherGameTime.minute;
  u32 hour = gameTime.hour + otherGameTime.hour;
  u32 day = gameTime.day + otherGameTime.day;
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
  result.second = second;
  result.minute = minute;
  result.hour = hour;
  result.day = day;
  return result;
}

GameTime operator-(const GameTime &gameTime, const GameTime &otherGameTime) {
  s32 second = gameTime.second - otherGameTime.second;
  s32 minute = gameTime.minute - otherGameTime.minute;
  s32 hour = gameTime.hour - otherGameTime.hour;
  s32 day = gameTime.day - otherGameTime.day;
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
  result.second = second;
  result.minute = minute;
  result.hour = hour;
  result.day = day;
  return result;
}

u32 GameTime::convMin() const { return day * MINUTES_PER_DAY + hour * MINUTES_PER_HOUR + minute; }

u32 GameTime::convSec() const { return day * SECONDS_PER_DAY + hour * SECONDS_PER_HOUR + minute * SECONDS_PER_MINUTE + second; }

ElapseTime operator-(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime) {
  s32 hour = elapseTime.hour - otherElapseTime.hour;
  s32 minute = elapseTime.minute - otherElapseTime.minute;
  s32 second = elapseTime.second - otherElapseTime.second;
  if (second < 0) {
    second += SECONDS_PER_MINUTE;
    minute--;
  }
  if (minute < 0) {
    minute += MINUTES_PER_HOUR;
    hour--;
  }

  ElapseTime result;
  result.second = second;
  result.minute = minute;
  result.hour = hour;
  if (hour < 0) {
    result = ElapseTime();
  }

  return result;
}

void ElapseTime::getTime(mm::mtl::FixStr<16> &string) const {
  mm::mtl::FixStr<16> work;
  work.format("%d", hour);
  string = work.c_str();
  string += ":";
  if (minute < 10) {
    string += "0";
  }
  work.format("%d", minute);
  string += work.c_str();
  string += ":";
  if (second < 10) {
    string += "0";
  }
  work.format("%d", second);
  string += work.c_str();
}

} // namespace gf
