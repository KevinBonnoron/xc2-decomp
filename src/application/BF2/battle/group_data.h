#pragma once
#include "types.h"
#include <stddef.h>

namespace btl {

constexpr f32 KIZUNA_GAUGE_MAX = 1000.0f;

class KIZUNA_GAUGE_DATA {
public:
  enum TIMER_TYPE {
    TIMER_TYPE_NONE,
    TIMER_TYPE_BUDDY_BATTLE,
    TIMER_TYPE_BUDDY,
    TIMER_TYPE_BUDDY_LOW,
  };

  void ResetGauge(int driver);
  void SetGauge(f32 value, bool isForce);
  void SetKizunaMax(int kizunaMax);
  void AddGauge(f32 value, bool isRevise);
  int GetKizunaStage(f32 *rate) const;
  void SetKizunaStage(int stage, f32 rate, bool isForce);
  void ResetTimingFlag();
  void UpdateCommon(f32 time);
  void UpdateBuddy(f32 time, int target, bool isBattle);
  void UpdateReserve(f32 time);

  f32 gauge;
  f32 subGauge;
  f32 gaugeRate;
  f32 timer;
  mutable f32 stageRate;
  u16 kizunaMax;
  mutable u8 stage;
  u8 timerType;
  u8 personality;
  u8 isPermitMax : 1;
  u8 isReachMax : 1;
  u8 isReachZero : 1;
  u8 isLock : 1;
};

static_assert(offsetof(KIZUNA_GAUGE_DATA, subGauge) == 0x04, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, gaugeRate) == 0x08, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, timer) == 0x0c, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, stageRate) == 0x10, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, kizunaMax) == 0x14, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, stage) == 0x16, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, timerType) == 0x17, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, personality) == 0x18, "");
static_assert(sizeof(KIZUNA_GAUGE_DATA) == 0x1c, "");

class GROUP_BLADE_DATA : public KIZUNA_GAUGE_DATA {
public:
  void Initialize(int blade, int driver, int index);
  void InitializeCoolTime(f32 rate);
  int GetTrustRank() const;
  f32 GetCoolTime() const;
  void ProgressCoolTime(f32 time);
  f32 GetCoolTimeRatio() const;
  bool IsCoolTimeEnd() const;
  void SynchroHomnuraData(const GROUP_BLADE_DATA &blade);

  f32 coolTime;
  f32 coolTimeCounter;
  u16 id;
  u16 bladeArtsEx;
  u8 isDriverBlade : 1;
  u8 : 2;
  u8 isInitialized : 1;
};

static_assert(offsetof(GROUP_BLADE_DATA, coolTime) == 0x1c, "");
static_assert(offsetof(GROUP_BLADE_DATA, coolTimeCounter) == 0x20, "");
static_assert(offsetof(GROUP_BLADE_DATA, id) == 0x24, "");
static_assert(offsetof(GROUP_BLADE_DATA, bladeArtsEx) == 0x26, "");
static_assert(sizeof(GROUP_BLADE_DATA) == 0x2c, "");

class GROUP_DATA {
public:
  void SetBuddyBladeIndex(int index);
  const GROUP_BLADE_DATA *GetBladeDataConst(int index) const;
  void ProgressCoolTime(f32 time);
  void FinishCoolTime();

  u8 _00[0x08 - 0x00];
  GROUP_BLADE_DATA blades[5];
  u8 _e4[0xf0 - 0xe4];
  f32 buddyTime;
  u8 _f4[0xff - 0xf4];
  s8 buddyBladeIndex;
};

static_assert(offsetof(GROUP_DATA, blades) == 0x08, "");
static_assert(offsetof(GROUP_DATA, buddyTime) == 0xf0, "");
static_assert(offsetof(GROUP_DATA, buddyBladeIndex) == 0xff, "");

} // namespace btl
