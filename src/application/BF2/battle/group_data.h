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

  f32 unknown00;         // Inferred role: gauge; original member name unknown.
  f32 unknown04;         // Inferred role: sub gauge; original member name unknown.
  f32 unknown08;         // Inferred role: gauge rate; original member name unknown.
  f32 unknown0c;         // Inferred role: timer; original member name unknown.
  mutable f32 unknown10; // Inferred role: stage rate; original member name unknown.
  u16 unknown14;         // Inferred role: kizuna max; original member name unknown.
  mutable u8 unknown16;  // Inferred role: stage; original member name unknown.
  u8 unknown17;          // Inferred role: timer type; original member name unknown.
  u8 unknown18;          // Inferred role: personality; original member name unknown.
  u8 unknown19_0 : 1;    // Inferred role: permit max; original member name unknown.
  u8 unknown19_1 : 1;    // Inferred role: reach max; original member name unknown.
  u8 unknown19_2 : 1;    // Inferred role: reach zero; original member name unknown.
  u8 unknown19_3 : 1;    // Inferred role: lock; original member name unknown.
};

static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown04) == 0x04, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown08) == 0x08, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown0c) == 0x0c, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown10) == 0x10, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown14) == 0x14, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown16) == 0x16, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown17) == 0x17, "");
static_assert(offsetof(KIZUNA_GAUGE_DATA, unknown18) == 0x18, "");
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

  f32 m_coolTime;
  f32 unknown20;      // Inferred role: cool time counter; original member name unknown.
  u16 unknown24;      // Inferred role: id; original member name unknown.
  u16 unknown26;      // Inferred role: blade arts ex; original member name unknown.
  u8 unknown28_0 : 1; // Inferred role: driver blade; original member name unknown.
  u8 : 2;
  u8 unknown28_3 : 1; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GROUP_BLADE_DATA, m_coolTime) == 0x1c, "");
static_assert(offsetof(GROUP_BLADE_DATA, unknown20) == 0x20, "");
static_assert(offsetof(GROUP_BLADE_DATA, unknown24) == 0x24, "");
static_assert(offsetof(GROUP_BLADE_DATA, unknown26) == 0x26, "");
static_assert(sizeof(GROUP_BLADE_DATA) == 0x2c, "");

class GROUP_DATA {
public:
  void SetBuddyBladeIndex(int index);
  const GROUP_BLADE_DATA *GetBladeDataConst(int index) const;
  void SetNeedPermit(bool isNeedPermit);
  void ProgressCoolTime(f32 time);
  void FinishCoolTime();

  u8 _00[0x08 - 0x00];
  GROUP_BLADE_DATA unknown08[5]; // Inferred role: blades; original member name unknown.
  f32 unknowne4[3];              // Inferred role: recasts; original member name unknown.
  f32 unknownf0;                 // Inferred role: buddy time; original member name unknown.
  u8 _f4[0xff - 0xf4];
  s8 unknownff; // Inferred role: buddy blade index; original member name unknown.
  u8 _100[0x101 - 0x100];
  s8 unknown101; // Inferred role: SP attack slot; original member name unknown.
  u8 _102[0x104 - 0x102];
  u16 : 1;
  u16 unknown104_1 : 1; // Inferred role: need permit; original member name unknown.
  u16 unknown104_2 : 2; // Inferred role: permit state; original member name unknown.
  u16 : 9;
  u16 unknown105_5 : 1; // Inferred role: entry; original member name unknown.
  u16 : 2;
};

static_assert(offsetof(GROUP_DATA, unknown08) == 0x08, "");
static_assert(offsetof(GROUP_DATA, unknowne4) == 0xe4, "");
static_assert(offsetof(GROUP_DATA, unknownf0) == 0xf0, "");
static_assert(offsetof(GROUP_DATA, unknownff) == 0xff, "");

} // namespace btl
