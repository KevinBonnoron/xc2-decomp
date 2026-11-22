#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_system.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_real_time.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

// Inferred role: save data task achieve; original type name unknown.
struct unknown106 {
  bool operator==(const unknown106 &other) const { return other.unknown00 == unknown00 && other.unknown02 == unknown02 && other.unknown04 == unknown04; }

  u16 unknown00; // Inferred role: quest; original member name unknown.
  u16 unknown02; // Inferred role: purpose; original member name unknown.
  u16 unknown04; // Inferred role: task index; original member name unknown.
  u32 unknown08; // Inferred role: unused, zero when registered; original member name unknown.
};

static_assert(offsetof(unknown106, unknown00) == 0x00, "");
static_assert(offsetof(unknown106, unknown02) == 0x02, "");
static_assert(offsetof(unknown106, unknown04) == 0x04, "");
static_assert(offsetof(unknown106, unknown08) == 0x08, "");
static_assert(sizeof(unknown106) == 0x0c, "");

// Inferred role: save data achievement popup; original type name unknown.
struct unknown107 {
  u16 unknown00; // Inferred role: blade; original member name unknown.
  u8 unknown02;  // Inferred role: achievement; original member name unknown.
  u8 unknown03;  // Inferred role: level; original member name unknown.
};

static_assert(sizeof(unknown107) == 0x04, "");

struct SDataGame {
  u32 m_money;   // Inferred role: money; named after the game accessor gf::GfDataUtil::getMoney.
  u32 unknown04; // Inferred role: landmark point; original member name unknown.
  u8 _000008[0x000010 - 0x000008];
  mm::Vec3 unknown10;     // Inferred role: landmark pos; original member name unknown.
  f32 unknown20;          // Inferred role: landmark rot y; original member name unknown.
  u16 unknown24;          // Inferred role: time stop; original member name unknown.
  u16 unknown26;          // Inferred role: start chapter save; original member name unknown.
  u16 m_eventChapterSave; // Inferred role: event chapter save; named after the game accessor gf::GfDataUtil::getEventChapterSave.
  u8 _00002a[0x00002c - 0x00002a];
  mm::mtl::FixedArray<SDataDriver, 16> unknown2c;   // Inferred role: drivers; original member name unknown.
  mm::mtl::FixedArray<SDataBlade, 422> unknown5a2c; // Inferred role: blades; original member name unknown.
  unknown124 m_sDataParty;                          // Inferred role: party; named after the game accessor gf::GfDataParty::getSDataParty.
  ItemBox m_itemBox;                                // Inferred role: item box; named after the game accessor gf::GfDataItem::getItemBox.
  GameFlag m_gameFlag;                              // Inferred role: game flag; original member name unknown.
  QuestID m_scenario;                               // Inferred role: scenario; named after the game accessor gf::GfDataQuest::getScenario.
  QuestID m_select;                                 // Inferred role: select; named after the game accessor gf::GfDataQuest::getSelect.
  u8 _1097ec[0x1097f0 - 0x1097ec];
  unknown118 m_sDataMap;                               // Inferred role: map; named after the game accessor gf::GfDataMap::getSDataMap.
  GameTime m_gameTime;                                 // Inferred role: game time; original member name unknown.
  ElapseTime m_elapseTime;                             // Inferred role: elapse time; original member name unknown.
  unknown122 m_sDataMercenaries;                       // Inferred role: mercenaries; named after the game accessor gf::GfDataMercenaries::getSDataMercenaries.
  f32 m_playerCameraDistance;                          // Inferred role: player camera distance; named after the game accessor gf::GfDataUtil::getPlayerCameraDistance.
  u32 m_gameClearCount;                                // Inferred role: game clear count; named after the game accessor gf::GfDataUtil::getGameClearCount.
  mm::mtl::FixedVector<unknown106, 128> m_taskAchieve; // Inferred role: task achieves; named after the game accessor gf::GfDataQuest::getTaskAchieve.
  QuestData m_questData[256];                          // Inferred role: order parent quests; original member name unknown.
  u32 unknown10a538;                                   // Inferred role: order parent quest count; original member name unknown.
  mm::mtl::FixedArray<unknown119, 64> unknown10a53c;   // Inferred role: map infos; original member name unknown.
  u32 m_ether;                                         // Inferred role: ether; named after the game accessor gf::GfDataHana::getEther.
  f32 unknown10ad40;                                   // Inferred role: achievement walk move; original member name unknown.
  f32 unknown10ad44;                                   // Inferred role: achievement swim move; original member name unknown.
  u32 unknown10ad48;                                   // Inferred role: assure point; original member name unknown.
  u32 unknown10ad4c;                                   // Inferred role: assure count; original member name unknown.
  u16 m_rareBladeAppearType;                           // Inferred role: rare blade appear type; named after the game accessor gf::GfDataBladeCreate::setRareBladeAppearType.
  u8 _10ad52[0x10ad54 - 0x10ad52];
  u32 m_coin;              // Inferred role: coin; named after the game accessor gf::GfDataUtil::getCoin.
  u32 unknown10ad58[4];    // Inferred role: saved hp; original member name unknown.
  RealTime m_saveRealTime; // Inferred role: save real time; passed by address to GfFieldTime::getRealTime by GfGameUtilSaveData::setupGameSaveData (0x71003558b8); named after the game accessor
                           // gf::GfDataUtil::getSaveRealTime.
  f32 m_cameraHeight;      // Inferred role: camera height; named after the game accessor gf::GfDataUtil::getCameraHeight.
  mm::mtl::FixedArray<u8, 0x10ae74 - 0x10ad74> unknown10ad74; // Inferred role: block of 0x100 bytes copied by GfGameUtil::setupNewGameParam (memcpy at 0x71003511c8); original member name unknown.
  f32 m_cameraYaw;                                            // Inferred role: camera yaw; named after the game accessor gf::GfDataUtil::getCameraYaw.
  f32 m_cameraPitch;                                          // Inferred role: camera pitch; named after the game accessor gf::GfDataUtil::getCameraPitch.
  u8 m_cameraFreeMode;                                        // Inferred role: camera free mode; named after the game accessor gf::GfDataUtil::isCameraFreeMode.
  u8 unknown10ae7d;                                           // Inferred role: hikari current; original member name unknown.
  u16 m_autoEventAfterLoad;                                   // Inferred role: auto event after load; named after the game accessor gf::GfDataUtil::getAutoEventAfterLoad.
  u8 m_collectFlagNewVersion;                                 // Inferred role: collect flag new version; named after the game accessor gf::GfDataUtil::isCollectFlagNewVersion.
  u8 unknown10ae81;                                           // Inferred role: clear save data; original member name unknown.
  u8 m_cameraSide;                                            // Inferred role: camera side; named after the game accessor gf::GfDataUtil::getCameraSide.
  u8 _10ae83[0x10ae84 - 0x10ae83];
  unknown125 unknown10ae84[500]; // Inferred role: saved events; original member name unknown.
  u32 unknown1171d4;             // Inferred role: saved event num; original member name unknown.
  unknown107 unknown1171d8[300]; // Inferred role: achievement popups; original member name unknown.
  u32 unknown117688;             // Inferred role: achievement popup num; original member name unknown.
  u8 _11768c[0x117690 - 0x11768c];

  SDataGame();
  SDataGame &operator=(const SDataGame &dataGame);

  // Inferred helper: copies one game flag of a size from another save game; original name unknown. Inlined in GfGameUtil::setupNewGameParam (0x7100351354) and in
  // GfGameUtilSaveData::setupGameSaveData (0x7100355178).
  void unknown001(const SDataGame &src, u32 size, int flag) { GfGameFlag::setLocal(m_gameFlag, size, flag, GfGameFlag::getLocal(src.m_gameFlag, size, flag)); }

  // Inferred helper: copies the game flags of a size from first up to last (excluded), the loops that start at the first flag (0x71003517e4); original name unknown.
  void unknown002(const SDataGame &src, u32 size, int first, int last) {
    for (int flag = first; flag < last; flag++) {
      unknown001(src, size, flag);
    }
  }

  // Inferred helper: copies count game flags of a size from a base flag, the loops that add the base to a counter (0x7100351370); original name unknown.
  void unknown003(const SDataGame &src, u32 size, int base, int count) {
    for (int i = 0; i < count; i++) {
      unknown001(src, size, base + i);
    }
  }
};

static_assert(offsetof(SDataGame, m_money) == 0x0, "");
static_assert(offsetof(SDataGame, unknown04) == 0x000004, "");
static_assert(offsetof(SDataGame, unknown10) == 0x000010, "");
static_assert(offsetof(SDataGame, unknown20) == 0x000020, "");
static_assert(offsetof(SDataGame, unknown24) == 0x000024, "");
static_assert(offsetof(SDataGame, unknown26) == 0x000026, "");
static_assert(offsetof(SDataGame, m_eventChapterSave) == 0x000028, "");
static_assert(offsetof(SDataGame, unknown2c) == 0x00002c, "");
static_assert(offsetof(SDataGame, unknown5a2c) == 0x005a2c, "");
static_assert(offsetof(SDataGame, m_sDataParty) == 0x0e9884, "");
static_assert(offsetof(SDataGame, m_itemBox) == 0x0e98d8, "");
static_assert(offsetof(SDataGame, m_gameFlag) == 0x0fbbc4, "");
static_assert(offsetof(SDataGame, m_scenario) == 0x1097e4, "");
static_assert(offsetof(SDataGame, m_select) == 0x1097e8, "");
static_assert(offsetof(SDataGame, m_sDataMap) == 0x1097f0, "");
static_assert(offsetof(SDataGame, m_gameTime) == 0x1098c0, "");
static_assert(offsetof(SDataGame, m_elapseTime) == 0x1098c4, "");
static_assert(offsetof(SDataGame, m_sDataMercenaries) == 0x1098c8, "");
static_assert(offsetof(SDataGame, m_playerCameraDistance) == 0x109b28, "");
static_assert(offsetof(SDataGame, m_gameClearCount) == 0x109b2c, "");
static_assert(offsetof(SDataGame, m_taskAchieve) == 0x109b30, "");
static_assert(offsetof(SDataGame, m_questData) == 0x10a138, "");
static_assert(offsetof(SDataGame, unknown10a538) == 0x10a538, "");
static_assert(offsetof(SDataGame, unknown10a53c) == 0x10a53c, "");
static_assert(offsetof(SDataGame, m_ether) == 0x10ad3c, "");
static_assert(offsetof(SDataGame, unknown10ad40) == 0x10ad40, "");
static_assert(offsetof(SDataGame, unknown10ad44) == 0x10ad44, "");
static_assert(offsetof(SDataGame, unknown10ad48) == 0x10ad48, "");
static_assert(offsetof(SDataGame, unknown10ad4c) == 0x10ad4c, "");
static_assert(offsetof(SDataGame, m_rareBladeAppearType) == 0x10ad50, "");
static_assert(offsetof(SDataGame, m_coin) == 0x10ad54, "");
static_assert(offsetof(SDataGame, unknown10ad58) == 0x10ad58, "");
static_assert(offsetof(SDataGame, m_saveRealTime) == 0x10ad68, "");
static_assert(offsetof(SDataGame, m_cameraHeight) == 0x10ad70, "");
static_assert(offsetof(SDataGame, unknown10ad74) == 0x10ad74, "");
static_assert(offsetof(SDataGame, m_cameraYaw) == 0x10ae74, "");
static_assert(offsetof(SDataGame, m_cameraPitch) == 0x10ae78, "");
static_assert(offsetof(SDataGame, m_cameraFreeMode) == 0x10ae7c, "");
static_assert(offsetof(SDataGame, unknown10ae7d) == 0x10ae7d, "");
static_assert(offsetof(SDataGame, m_autoEventAfterLoad) == 0x10ae7e, "");
static_assert(offsetof(SDataGame, m_collectFlagNewVersion) == 0x10ae80, "");
static_assert(offsetof(SDataGame, m_cameraSide) == 0x10ae82, "");
static_assert(offsetof(SDataGame, unknown10ae84) == 0x10ae84, "");
static_assert(offsetof(SDataGame, unknown1171d4) == 0x1171d4, "");
static_assert(offsetof(SDataGame, unknown1171d8) == 0x1171d8, "");
static_assert(offsetof(SDataGame, unknown117688) == 0x117688, "");
static_assert(sizeof(SDataGame) == 0x117690, "");

struct SDataSave : SDataSystem {
  SDataSave() {}

  SDataGame m_game; // Inferred role: game data; original member name unknown.
};

static_assert(offsetof(SDataSave, m_realTime) == 0x08, "");
static_assert(offsetof(SDataSave, m_game) == 0x10, "");
static_assert(sizeof(SDataSave) == 0x1176a0, "");

} // namespace gf
