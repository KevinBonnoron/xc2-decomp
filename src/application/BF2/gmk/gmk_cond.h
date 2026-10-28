#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

struct CBdatWrapper;

namespace mm {
struct Col4;
} // namespace mm

namespace gmk {

class AGmkBase;

class ScenarioFlagCond {
public:
  ScenarioFlagCond() : unknown00(0), unknown02(0) {}
  ScenarioFlagCond(u16 min, u16 max) : unknown00(min), unknown02(max) {}
  ScenarioFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk);
  ScenarioFlagCond(const CBdatWrapper &bdat, int id, const char *prefix);
  bool isEnable() const { return unknown02 != 0; }
  bool isMatch() const;

  u16 unknown00; // Inferred role: min; original member name unknown.
  u16 unknown02; // Inferred role: max; original member name unknown.
};

static_assert(sizeof(ScenarioFlagCond) == 0x4, "");

class QuestFlagCond {
public:
  QuestFlagCond() : unknown00(0), unknown02(0), unknown03(0) {}
  QuestFlagCond(u16 quest, u8 minState, u8 maxState) : unknown00(quest), unknown02(minState), unknown03(maxState) {}
  QuestFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk);
  QuestFlagCond(const CBdatWrapper &bdat, int id, const char *prefix);
  bool isEnable() const { return unknown00 != 0 && unknown02 <= unknown03; }
  bool isMatch() const;

  u16 unknown00; // Inferred role: quest; original member name unknown.
  u8 unknown02;  // Inferred role: min state; original member name unknown.
  u8 unknown03;  // Inferred role: max state; original member name unknown.
};

static_assert(offsetof(QuestFlagCond, unknown02) == 0x2, "");
static_assert(offsetof(QuestFlagCond, unknown03) == 0x3, "");

class DistHvCond {
public:
  static u16 clampDepopDist(u16 depopDist, u16 popDist) { return depopDist <= popDist ? popDist + 1 : depopDist; }

  void set(f32 horizontalDist, f32 verticalDist) {
    unknown00 = horizontalDist * horizontalDist;
    unknown04 = verticalDist * verticalDist;
  }

  bool isMatch(const mm::Vec3 &position) const;
  void debugDraw(const mm::Vec3 &position, const mm::Col4 &color) const;

  f32 unknown00; // Inferred role: horizontal dist sq; original member name unknown.
  f32 unknown04; // Inferred role: vertical dist sq; original member name unknown.
};

static_assert(sizeof(DistHvCond) == 0x8, "");

class DistCond {
public:
  void debugDraw(const mm::Vec3 &position, const mm::Col4 &color) const;
  static bool isMatch(f32 distSq, const mm::Vec3 &position);

  f32 unknown00; // Inferred role: dist sq; original member name unknown.
};

class TimeCond {
public:
  TimeCond() : unknown08(0xffff) {}
  virtual ~TimeCond() {}
  bool isEnable() const { return unknown08 != 0; }
  bool isMatch() const;

  u32 unknown08; // Inferred role: time range bits; original member name unknown.
};

static_assert(offsetof(TimeCond, unknown08) == 0x8, "");

class WeatherCond {
public:
  WeatherCond() : unknown08(0xff) {}
  virtual ~WeatherCond() {}
  bool isEnable() const { return unknown08 != 0; }
  bool isMatch() const;

  u8 unknown08; // Inferred role: weather bits; original member name unknown.
};

static_assert(offsetof(WeatherCond, unknown08) == 0x8, "");

class CloudCond {
public:
  enum Type {
    TYPE_NO_CLOUD_SEA = 0,
    TYPE_CLOUD_SEA = 1,
  };

  CloudCond() : unknown08(static_cast<Type>(-1)) {}
  virtual ~CloudCond() {}
  bool isMatch() const;

  Type unknown08; // Inferred role: type; original member name unknown.
};

static_assert(offsetof(CloudCond, unknown08) == 0x8, "");

class InOutDoorCond {
public:
  InOutDoorCond() : unknown08(true), unknown09(true) {}
  virtual ~InOutDoorCond() {}
  bool isMatch() const;

  bool unknown08; // Inferred role: indoor; original member name unknown.
  bool unknown09; // Inferred role: outdoor; original member name unknown.
};

static_assert(offsetof(InOutDoorCond, unknown08) == 0x8, "");
static_assert(offsetof(InOutDoorCond, unknown09) == 0x9, "");

class GameFlagCond {
public:
  GameFlagCond() {}
  GameFlagCond(int size, int index) : unknown08(size), unknown0c(index) {}
  virtual ~GameFlagCond() {}
  bool isMatch(u32 value) const;

  int unknown08; // Inferred role: size; original member name unknown.
  int unknown0c; // Inferred role: index; original member name unknown.
};

static_assert(offsetof(GameFlagCond, unknown08) == 0x8, "");
static_assert(offsetof(GameFlagCond, unknown0c) == 0xc, "");

class PopPosSafeCond {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(mm::Vec3::zero), unknown10(0), unknown14(0.0f), unknown18(10.0f) {}

    mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
    u8 unknown10;       // Inferred role: water type; original member name unknown.
    f32 unknown14;      // Inferred role: water depth; original member name unknown.
    f32 unknown18;      // Inferred role: snap height; original member name unknown.
  };

  PopPosSafeCond(const CreateInfo *info);

  void create(const CreateInfo &info) {
    dispose();
    unknown00 = info;
    unknown20 = true;
  }

  void dispose() { unknown00 = CreateInfo(); }

  CreateInfo unknown00; // Inferred role: create info; original member name unknown.
  bool unknown20;       // Inferred role: created; original member name unknown.
};

static_assert(sizeof(PopPosSafeCond::CreateInfo) == 0x20, "");
static_assert(offsetof(PopPosSafeCond, unknown20) == 0x20, "");

class BootedGmkCond {
public:
  BootedGmkCond() : unknown00(0), unknown02(0) {}
  BootedGmkCond(u8 gimmickType, u16 gimmickId);
  void create(u8 gimmickType, u16 gimmickId);

  BootedGmkCond(const CBdatWrapper &bdat, int id, const char *prefix);
  void dispose();
  void createIfEnable(u8 gimmickType, u16 gimmickId) {
    if (gimmickType == 0 || gimmickId == 0) {
      return;
    }
    create(gimmickType, gimmickId);
  }

  bool isEnable() const { return unknown00 != 0 && unknown02 != 0; }
  bool isMatch() const;

  u8 unknown00;  // Inferred role: gimmick type; original member name unknown.
  u16 unknown02; // Inferred role: gimmick id; original member name unknown.
};

static_assert(sizeof(BootedGmkCond) == 0x4, "");

} // namespace gmk
