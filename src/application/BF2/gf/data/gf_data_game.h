#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataGame {
  u32 money;
  u8 _000004[0x000026 - 0x000004];
  u16 startChapterSave;
  u16 eventChapterSave;
  u8 _00002a[0x1098b0 - 0x00002a];
  u32 skipTravelID;
  u8 _1098b4[0x109b28 - 0x1098b4];
  f32 playerCameraDistance;
  u32 gameClearCount;
  u8 _109b30[0x10ad40 - 0x109b30];
  f32 achievementWalkMove;
  f32 achievementSwimMove;
  u32 assurePoint;
  u32 assureCount;
  u16 rareBladeAppearType;
  u8 _10ad52[0x10ad54 - 0x10ad52];
  u32 coin;
  u8 _10ad58[0x10ad70 - 0x10ad58];
  f32 cameraHeight;
  u8 _10ad74[0x10ae74 - 0x10ad74];
  f32 cameraYaw;
  f32 cameraPitch;
  u8 cameraFreeMode;
  u8 hikariCurrent;
  u16 autoEventAfterLoad;
  u8 collectFlagNewVersion;
  u8 _10ae81[0x10ae82 - 0x10ae81];
  u8 cameraSide;
};

static_assert(offsetof(SDataGame, money) == 0x0, "");
static_assert(offsetof(SDataGame, startChapterSave) == 0x000026, "");
static_assert(offsetof(SDataGame, eventChapterSave) == 0x000028, "");
static_assert(offsetof(SDataGame, skipTravelID) == 0x1098b0, "");
static_assert(offsetof(SDataGame, playerCameraDistance) == 0x109b28, "");
static_assert(offsetof(SDataGame, gameClearCount) == 0x109b2c, "");
static_assert(offsetof(SDataGame, achievementWalkMove) == 0x10ad40, "");
static_assert(offsetof(SDataGame, achievementSwimMove) == 0x10ad44, "");
static_assert(offsetof(SDataGame, assurePoint) == 0x10ad48, "");
static_assert(offsetof(SDataGame, assureCount) == 0x10ad4c, "");
static_assert(offsetof(SDataGame, rareBladeAppearType) == 0x10ad50, "");
static_assert(offsetof(SDataGame, coin) == 0x10ad54, "");
static_assert(offsetof(SDataGame, cameraHeight) == 0x10ad70, "");
static_assert(offsetof(SDataGame, cameraYaw) == 0x10ae74, "");
static_assert(offsetof(SDataGame, cameraPitch) == 0x10ae78, "");
static_assert(offsetof(SDataGame, cameraFreeMode) == 0x10ae7c, "");
static_assert(offsetof(SDataGame, hikariCurrent) == 0x10ae7d, "");
static_assert(offsetof(SDataGame, autoEventAfterLoad) == 0x10ae7e, "");
static_assert(offsetof(SDataGame, collectFlagNewVersion) == 0x10ae80, "");
static_assert(offsetof(SDataGame, cameraSide) == 0x10ae82, "");

} // namespace gf
