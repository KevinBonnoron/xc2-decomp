#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

enum TIME_RANGE {
  TIME_RANGE_MORNING,
  TIME_RANGE_NOONTIME,
  TIME_RANGE_AFTERNOON,
  TIME_RANGE_EVENING,
  TIME_RANGE_LATE_NIGHT,
  TIME_RANGE_DAWN,
  TIME_RANGE_DAYTIME,
  TIME_RANGE_NIGHTTIME,
};

struct ElapseTime {
  u32 second : 6;
  u32 minute : 6;
  u32 hour : 20;

  void getTime(mm::mtl::FixStr<16> &string) const;
};

static_assert(sizeof(ElapseTime) == 4, "");

struct GameTime {
  u32 second : 6;
  u32 minute : 6;
  u32 hour : 5;
  u32 day : 15;

  u32 convMin() const;
  u32 convSec() const;
};

static_assert(sizeof(GameTime) == 4, "");

struct RealTime {
  u64 : 6;
  u64 millisecond : 10;
  u64 second : 6;
  u64 minute : 6;
  u64 hour : 5;
  u64 day : 5;
  u64 dayOfYear : 9;
  u64 month : 4;
  u64 year : 13;
};

static_assert(sizeof(RealTime) == 8, "");

struct TimeRangeData {
  u16 startHour;
  u16 startMinute;
  u16 endHour;
  u16 endMinute;
};

static_assert(sizeof(TimeRangeData) == 8, "");

class GfFieldTime : public mm::mtl::PtrSingleton<GfFieldTime> {
public:
  enum {
    TIME_STOP_BIT_GAME = 1 << 0,
    TIME_STOP_BIT_FIELD_SCRIPT = 1 << 1,
  };

  GfFieldTime(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFieldTime();
  void clear();
  u32 getTimeRange(u32 hour, u32 minute) const;
  u32 getTimeRangeDN() const;
  void getRealTime(RealTime &realTime) const;
  void setTime(u32 hour, u32 minute);
  const GameTime &getGameTime() const;
  void setupGame();
  void setElapseTime(const ElapseTime &elapseTime);
  void setGameTime(const GameTime &gameTime);
  void setTimeStop(bool isStop);
  void gevReloadBdat(RELOAD_BDAT reload, u32 value);
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void update(const fw::UpdateInfo &info);
  void updateElapseTime(const fw::UpdateInfo &info);
  bool isTimeStop() const;
  void saveRealTime();
  s32 diffRealTimeSec(const RealTime &realTime, const RealTime &baseRealTime) const;
  f32 calcGameTime(f32 hour, f32 minute) const;
  const char *getTimeRangeName() const;
  u32 getTimeRange() const;
  bool getTimeRangeName(u8 *&bdat, u32 &textId) const;
  void getGameTime(mm::mtl::FixStr<16> &string) const;
  u32 getHour() const;
  u32 getMin() const;
  void getElapseTime(mm::mtl::FixStr<16> &string) const;
  const ElapseTime &getElapseTime() const;
  void nextDay();
  void saveSuspendRealTime();
  void setDay(u32 day);
  void setHour(u32 hour);
  void setMin(u32 minute);
  u32 getTime(u32 &hour, u32 &minute) const;
  u32 getDay() const;
  u32 getSec() const;
  u32 getTime() const;
  void setTimeSpeed(f32 timeSpeed);
  f32 toRealTime(f32 gameTime) const;
  f32 toGameTime(f32 realTime) const;
  const TimeRangeData *getRangeData(u32 timeRange) const;
  void setTimeRange(u32 timeRange);
  void setTimeRangeBit(u32 timeRangeBits);
  u32 getTimeRangeBits(u32 timeRange) const;
  u32 getTimeRangeBits() const;
  s32 diffRealTimeMin(const RealTime &realTime, const RealTime &baseRealTime) const;
  f32 diffRealTime(const RealTime &realTime, const RealTime &baseRealTime) const;
  void setFieldScriptTimeStop(bool isStop);
  void setDebugStop(bool isStop);
  bool isDebugStop() const;

private:
  bool mInitialized;
  u32 mTimeStopBits;
  ElapseTime mBaseElapseTime;
  ElapseTime mElapseTime;
  RealTime mRealTime;
  RealTime mElapseStartRealTime;
  u32 mUnused28;
  GameTime mGameTime;
  f32 mTime;
  f32 mPrevTime;
  f32 mTimeFraction;
  f32 mTimeSpeed;
  u32 mTimeRange;
  u32 mPrevTimeRange;
  u32 mTimeRangeDN;
  u32 mUnused4c;
  bool mIsDebugStop;
};

static_assert(sizeof(GfFieldTime) == 0x58, "");

ElapseTime operator+(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime);
GameTime operator+(const GameTime &gameTime, const GameTime &otherGameTime);
GameTime operator-(const GameTime &gameTime, const GameTime &otherGameTime);
ElapseTime operator-(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime);

} // namespace gf
