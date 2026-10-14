#pragma once
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_party.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataGame {
  u32 money;
  u8 _000004[0x000026 - 0x000004];
  u16 startChapterSave;
  u16 eventChapterSave;
  u8 _00002a[0x00002c - 0x00002a];
  SDataDriver drivers[16];
  SDataBlade blades[422];
  SDataParty party;
  SDataItemBox itemBox;
  QuestID scenario;
  QuestID select;
  u8 _1097ec[0x1097f0 - 0x1097ec];
  SDataMap map;
  u8 _1098c0[0x1098c8 - 0x1098c0];
  SDataMercenaries mercenaries;
  f32 playerCameraDistance;
  u32 gameClearCount;
  u8 _109b30[0x10a53c - 0x109b30];
  mm::mtl::FixedArray<SDataMapInfo, 64> mapInfos;
  u32 ether;
  f32 achievementWalkMove;
  f32 achievementSwimMove;
  u32 assurePoint;
  u32 assureCount;
  u16 rareBladeAppearType;
  u8 _10ad52[0x10ad54 - 0x10ad52];
  u32 coin;
  u32 savedHp[4];
  u64 saveRealTime;
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
static_assert(offsetof(SDataGame, drivers) == 0x00002c, "");
static_assert(offsetof(SDataGame, blades) == 0x005a2c, "");
static_assert(offsetof(SDataGame, party) == 0x0e9884, "");
static_assert(offsetof(SDataGame, itemBox) == 0x0e98d8, "");
static_assert(offsetof(SDataGame, scenario) == 0x1097e4, "");
static_assert(offsetof(SDataGame, select) == 0x1097e8, "");
static_assert(offsetof(SDataGame, map) == 0x1097f0, "");
static_assert(offsetof(SDataGame, mercenaries) == 0x1098c8, "");
static_assert(offsetof(SDataGame, playerCameraDistance) == 0x109b28, "");
static_assert(offsetof(SDataGame, gameClearCount) == 0x109b2c, "");
static_assert(offsetof(SDataGame, mapInfos) == 0x10a53c, "");
static_assert(offsetof(SDataGame, ether) == 0x10ad3c, "");
static_assert(offsetof(SDataGame, achievementWalkMove) == 0x10ad40, "");
static_assert(offsetof(SDataGame, achievementSwimMove) == 0x10ad44, "");
static_assert(offsetof(SDataGame, assurePoint) == 0x10ad48, "");
static_assert(offsetof(SDataGame, assureCount) == 0x10ad4c, "");
static_assert(offsetof(SDataGame, rareBladeAppearType) == 0x10ad50, "");
static_assert(offsetof(SDataGame, coin) == 0x10ad54, "");
static_assert(offsetof(SDataGame, savedHp) == 0x10ad58, "");
static_assert(offsetof(SDataGame, saveRealTime) == 0x10ad68, "");
static_assert(offsetof(SDataGame, cameraHeight) == 0x10ad70, "");
static_assert(offsetof(SDataGame, cameraYaw) == 0x10ae74, "");
static_assert(offsetof(SDataGame, cameraPitch) == 0x10ae78, "");
static_assert(offsetof(SDataGame, cameraFreeMode) == 0x10ae7c, "");
static_assert(offsetof(SDataGame, hikariCurrent) == 0x10ae7d, "");
static_assert(offsetof(SDataGame, autoEventAfterLoad) == 0x10ae7e, "");
static_assert(offsetof(SDataGame, collectFlagNewVersion) == 0x10ae80, "");
static_assert(offsetof(SDataGame, cameraSide) == 0x10ae82, "");

} // namespace gf
