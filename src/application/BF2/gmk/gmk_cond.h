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
  ScenarioFlagCond(u16 min, u16 max) : min(min), max(max) {}
  ScenarioFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk);
  ScenarioFlagCond(const CBdatWrapper &bdat, int id, const char *prefix);
  bool isEnable() const { return max != 0; }
  bool isMatch() const;

  u16 min;
  u16 max;
};

static_assert(sizeof(ScenarioFlagCond) == 0x4, "");

class QuestFlagCond {
public:
  QuestFlagCond(u16 quest, u8 minState, u8 maxState) : quest(quest), minState(minState), maxState(maxState) {}
  QuestFlagCond(const CBdatWrapper &bdat, int id, const AGmkBase &gmk);
  QuestFlagCond(const CBdatWrapper &bdat, int id, const char *prefix);
  bool isEnable() const { return quest != 0 && minState <= maxState; }
  bool isMatch() const;

  u16 quest;
  u8 minState;
  u8 maxState;
};

static_assert(offsetof(QuestFlagCond, minState) == 0x2, "");
static_assert(offsetof(QuestFlagCond, maxState) == 0x3, "");

class DistHvCond {
public:
  static u16 clampDepopDist(u16 depopDist, u16 popDist) { return depopDist <= popDist ? popDist + 1 : depopDist; }

  void set(f32 horizontalDist, f32 verticalDist) {
    horizontalDistSq = horizontalDist * horizontalDist;
    verticalDistSq = verticalDist * verticalDist;
  }

  bool isMatch(const mm::Vec3 &position) const;
  void debugDraw(const mm::Vec3 &position, const mm::Col4 &color) const;

  f32 horizontalDistSq;
  f32 verticalDistSq;
};

static_assert(sizeof(DistHvCond) == 0x8, "");

class DistCond {
public:
  void debugDraw(const mm::Vec3 &position, const mm::Col4 &color) const;
  static bool isMatch(f32 distSq, const mm::Vec3 &position);

  f32 distSq;
};

class TimeCond {
public:
  virtual ~TimeCond() {}
  bool isEnable() const { return timeRangeBits != 0; }
  bool isMatch() const;

  u32 timeRangeBits;
};

static_assert(offsetof(TimeCond, timeRangeBits) == 0x8, "");

class WeatherCond {
public:
  virtual ~WeatherCond() {}
  bool isEnable() const { return weatherBits != 0; }
  bool isMatch() const;

  u8 weatherBits;
};

static_assert(offsetof(WeatherCond, weatherBits) == 0x8, "");

class CloudCond {
public:
  enum Type {
    TYPE_NO_CLOUD_SEA = 0,
    TYPE_CLOUD_SEA = 1,
  };

  virtual ~CloudCond() {}
  bool isMatch() const;

  Type type;
};

static_assert(offsetof(CloudCond, type) == 0x8, "");

class InOutDoorCond {
public:
  virtual ~InOutDoorCond() {}
  bool isMatch() const;

  bool isIndoor;
  bool isOutdoor;
};

static_assert(offsetof(InOutDoorCond, isIndoor) == 0x8, "");
static_assert(offsetof(InOutDoorCond, isOutdoor) == 0x9, "");

class GameFlagCond {
public:
  virtual ~GameFlagCond() {}
  bool isMatch(u32 value) const;

  int size;
  int index;
};

static_assert(offsetof(GameFlagCond, size) == 0x8, "");
static_assert(offsetof(GameFlagCond, index) == 0xc, "");

class PopPosSafeCond {
public:
  struct CreateInfo {
    CreateInfo() : position(mm::Vec3::zero), waterType(0), waterDepth(0.0f), snapHeight(10.0f) {}

    mm::Vec3 position;
    u8 waterType;
    f32 waterDepth;
    f32 snapHeight;
  };

  PopPosSafeCond(const CreateInfo *info);

  void create(const CreateInfo &info) {
    dispose();
    createInfo = info;
    isCreated = true;
  }

  void dispose() { createInfo = CreateInfo(); }

  CreateInfo createInfo;
  bool isCreated;
};

static_assert(sizeof(PopPosSafeCond::CreateInfo) == 0x20, "");
static_assert(offsetof(PopPosSafeCond, isCreated) == 0x20, "");

class BootedGmkCond {
public:
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

  bool isEnable() const { return gimmickType != 0 && gimmickId != 0; }
  bool isMatch() const;

  u8 gimmickType;
  u16 gimmickId;
};

static_assert(sizeof(BootedGmkCond) == 0x4, "");

} // namespace gmk
