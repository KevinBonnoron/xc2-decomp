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

constexpr u32 SECONDS_PER_MINUTE = 60;

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
  u32 unknown00_0 : 6;  // Inferred role: second; original member name unknown.
  u32 unknown00_6 : 6;  // Inferred role: minute; original member name unknown.
  u32 unknown01_4 : 20; // Inferred role: hour; original member name unknown.

  void getTime(mm::mtl::FixStr<16> &string) const;
};

static_assert(sizeof(ElapseTime) == 4, "");

struct GameTime {
  u32 unknown00_0 : 6;  // Inferred role: second; original member name unknown.
  u32 unknown00_6 : 6;  // Inferred role: minute; original member name unknown.
  u32 unknown01_4 : 5;  // Inferred role: hour; original member name unknown.
  u32 unknown02_1 : 15; // Inferred role: day; original member name unknown.

  u32 convMin() const;
  u32 convSec() const;
};

static_assert(sizeof(GameTime) == 4, "");

struct RealTime {
  u64 : 6;
  u64 unknown00_6 : 10; // Inferred role: millisecond; original member name unknown.
  u64 unknown02_0 : 6;  // Inferred role: second; original member name unknown.
  u64 unknown02_6 : 6;  // Inferred role: minute; original member name unknown.
  u64 unknown03_4 : 5;  // Inferred role: hour; original member name unknown.
  u64 unknown04_1 : 5;  // Inferred role: day; original member name unknown.
  u64 unknown04_6 : 9;  // Inferred role: day of year; original member name unknown.
  u64 unknown05_7 : 4;  // Inferred role: month; original member name unknown.
  u64 unknown06_3 : 13; // Inferred role: year; original member name unknown.
};

static_assert(sizeof(RealTime) == 8, "");

struct TimeRangeData {
  u16 unknown00; // Inferred role: start hour; original member name unknown.
  u16 unknown02; // Inferred role: start minute; original member name unknown.
  u16 unknown04; // Inferred role: end hour; original member name unknown.
  u16 unknown06; // Inferred role: end minute; original member name unknown.
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
  bool unknown08;       // Inferred role: initialized; original member name unknown.
  u32 unknown0c;        // Inferred role: time stop bits; original member name unknown.
  ElapseTime unknown10; // Inferred role: base elapse time; original member name unknown.
  ElapseTime m_elapseTime;
  RealTime unknown18; // Inferred role: real time; original member name unknown.
  RealTime unknown20; // Inferred role: elapse start real time; original member name unknown.
  u32 unknown28;      // Inferred role: unused28; original member name unknown.
  GameTime m_gameTime;
  f32 unknown30; // Inferred role: time; original member name unknown.
  f32 unknown34; // Inferred role: prev time; original member name unknown.
  f32 unknown38; // Inferred role: time fraction; original member name unknown.
  f32 m_timeSpeed;
  u32 m_timeRange;
  u32 unknown44; // Inferred role: prev time range; original member name unknown.
  u32 unknown48; // Inferred role: time range dn; original member name unknown.
  u32 unknown4c; // Inferred role: unused4c; original member name unknown.
  bool m_debugStop;
};

static_assert(sizeof(GfFieldTime) == 0x58, "");

ElapseTime operator+(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime);
GameTime operator+(const GameTime &gameTime, const GameTime &otherGameTime);
GameTime operator-(const GameTime &gameTime, const GameTime &otherGameTime);
ElapseTime operator-(const ElapseTime &elapseTime, const ElapseTime &otherElapseTime);

} // namespace gf
