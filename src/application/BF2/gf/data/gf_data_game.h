#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_time.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct SDataTaskAchieve {
  u8 _00[0x0c - 0x00];
};

static_assert(sizeof(SDataTaskAchieve) == 0x0c, "");

struct SDataAchievementPopup {
  u16 unknown00; // Inferred role: blade; original member name unknown.
  u8 unknown02;  // Inferred role: achievement; original member name unknown.
  u8 unknown03;  // Inferred role: level; original member name unknown.
};

static_assert(sizeof(SDataAchievementPopup) == 0x04, "");

struct SDataGame {
  u32 unknown00; // Inferred role: money; original member name unknown.
  u32 unknown04; // Inferred role: landmark point; original member name unknown.
  u8 _000008[0x000010 - 0x000008];
  mm::Vec3 unknown10; // Inferred role: landmark pos; original member name unknown.
  f32 unknown20;      // Inferred role: landmark rot y; original member name unknown.
  u16 unknown24;      // Inferred role: time stop; original member name unknown.
  u16 unknown26;      // Inferred role: start chapter save; original member name unknown.
  u16 unknown28;      // Inferred role: event chapter save; original member name unknown.
  u8 _00002a[0x00002c - 0x00002a];
  SDataDriver unknown2c[16];                        // Inferred role: drivers; original member name unknown.
  mm::mtl::FixedArray<SDataBlade, 422> unknown5a2c; // Inferred role: blades; original member name unknown.
  SDataParty unknowne9884;                          // Inferred role: party; original member name unknown.
  ItemBox unknowne98d8;                             // Inferred role: item box; original member name unknown.
  GameFlag unknownfbbc4;                            // Inferred role: game flag; original member name unknown.
  QuestID unknown1097e4;                            // Inferred role: scenario; original member name unknown.
  QuestID unknown1097e8;                            // Inferred role: select; original member name unknown.
  u8 _1097ec[0x1097f0 - 0x1097ec];
  SDataMap unknown1097f0;                                    // Inferred role: map; original member name unknown.
  GameTime unknown1098c0;                                    // Inferred role: game time; original member name unknown.
  ElapseTime unknown1098c4;                                  // Inferred role: elapse time; original member name unknown.
  SDataMercenaries unknown1098c8;                            // Inferred role: mercenaries; original member name unknown.
  f32 unknown109b28;                                         // Inferred role: player camera distance; original member name unknown.
  u32 unknown109b2c;                                         // Inferred role: game clear count; original member name unknown.
  mm::mtl::FixedVector<SDataTaskAchieve, 128> unknown109b30; // Inferred role: task achieves; original member name unknown.
  QuestData unknown10a138[256];                              // Inferred role: order parent quests; original member name unknown.
  u32 unknown10a538;                                         // Inferred role: order parent quest count; original member name unknown.
  mm::mtl::FixedArray<SDataMapInfo, 64> unknown10a53c;       // Inferred role: map infos; original member name unknown.
  u32 unknown10ad3c;                                         // Inferred role: ether; original member name unknown.
  f32 unknown10ad40;                                         // Inferred role: achievement walk move; original member name unknown.
  f32 unknown10ad44;                                         // Inferred role: achievement swim move; original member name unknown.
  u32 unknown10ad48;                                         // Inferred role: assure point; original member name unknown.
  u32 unknown10ad4c;                                         // Inferred role: assure count; original member name unknown.
  u16 unknown10ad50;                                         // Inferred role: rare blade appear type; original member name unknown.
  u8 _10ad52[0x10ad54 - 0x10ad52];
  u32 unknown10ad54;    // Inferred role: coin; original member name unknown.
  u32 unknown10ad58[4]; // Inferred role: saved hp; original member name unknown.
  u64 unknown10ad68;    // Inferred role: save real time; original member name unknown.
  f32 unknown10ad70;    // Inferred role: camera height; original member name unknown.
  u8 _10ad74[0x10ae74 - 0x10ad74];
  f32 unknown10ae74; // Inferred role: camera yaw; original member name unknown.
  f32 unknown10ae78; // Inferred role: camera pitch; original member name unknown.
  u8 unknown10ae7c;  // Inferred role: camera free mode; original member name unknown.
  u8 unknown10ae7d;  // Inferred role: hikari current; original member name unknown.
  u16 unknown10ae7e; // Inferred role: auto event after load; original member name unknown.
  u8 unknown10ae80;  // Inferred role: collect flag new version; original member name unknown.
  u8 unknown10ae81;  // Inferred role: clear save data; original member name unknown.
  u8 unknown10ae82;  // Inferred role: camera side; original member name unknown.
  u8 _10ae83[0x10ae84 - 0x10ae83];
  SDataSavedEvent unknown10ae84[500];       // Inferred role: saved events; original member name unknown.
  u32 unknown1171d4;                        // Inferred role: saved event num; original member name unknown.
  SDataAchievementPopup unknown1171d8[300]; // Inferred role: achievement popups; original member name unknown.
  u32 unknown117688;                        // Inferred role: achievement popup num; original member name unknown.
  u8 _11768c[0x117690 - 0x11768c];

  SDataGame();
  SDataGame &operator=(const SDataGame &dataGame);
};

static_assert(offsetof(SDataGame, unknown00) == 0x0, "");
static_assert(offsetof(SDataGame, unknown04) == 0x000004, "");
static_assert(offsetof(SDataGame, unknown10) == 0x000010, "");
static_assert(offsetof(SDataGame, unknown20) == 0x000020, "");
static_assert(offsetof(SDataGame, unknown24) == 0x000024, "");
static_assert(offsetof(SDataGame, unknown26) == 0x000026, "");
static_assert(offsetof(SDataGame, unknown28) == 0x000028, "");
static_assert(offsetof(SDataGame, unknown2c) == 0x00002c, "");
static_assert(offsetof(SDataGame, unknown5a2c) == 0x005a2c, "");
static_assert(offsetof(SDataGame, unknowne9884) == 0x0e9884, "");
static_assert(offsetof(SDataGame, unknowne98d8) == 0x0e98d8, "");
static_assert(offsetof(SDataGame, unknownfbbc4) == 0x0fbbc4, "");
static_assert(offsetof(SDataGame, unknown1097e4) == 0x1097e4, "");
static_assert(offsetof(SDataGame, unknown1097e8) == 0x1097e8, "");
static_assert(offsetof(SDataGame, unknown1097f0) == 0x1097f0, "");
static_assert(offsetof(SDataGame, unknown1098c0) == 0x1098c0, "");
static_assert(offsetof(SDataGame, unknown1098c4) == 0x1098c4, "");
static_assert(offsetof(SDataGame, unknown1098c8) == 0x1098c8, "");
static_assert(offsetof(SDataGame, unknown109b28) == 0x109b28, "");
static_assert(offsetof(SDataGame, unknown109b2c) == 0x109b2c, "");
static_assert(offsetof(SDataGame, unknown109b30) == 0x109b30, "");
static_assert(offsetof(SDataGame, unknown10a138) == 0x10a138, "");
static_assert(offsetof(SDataGame, unknown10a538) == 0x10a538, "");
static_assert(offsetof(SDataGame, unknown10a53c) == 0x10a53c, "");
static_assert(offsetof(SDataGame, unknown10ad3c) == 0x10ad3c, "");
static_assert(offsetof(SDataGame, unknown10ad40) == 0x10ad40, "");
static_assert(offsetof(SDataGame, unknown10ad44) == 0x10ad44, "");
static_assert(offsetof(SDataGame, unknown10ad48) == 0x10ad48, "");
static_assert(offsetof(SDataGame, unknown10ad4c) == 0x10ad4c, "");
static_assert(offsetof(SDataGame, unknown10ad50) == 0x10ad50, "");
static_assert(offsetof(SDataGame, unknown10ad54) == 0x10ad54, "");
static_assert(offsetof(SDataGame, unknown10ad58) == 0x10ad58, "");
static_assert(offsetof(SDataGame, unknown10ad68) == 0x10ad68, "");
static_assert(offsetof(SDataGame, unknown10ad70) == 0x10ad70, "");
static_assert(offsetof(SDataGame, unknown10ae74) == 0x10ae74, "");
static_assert(offsetof(SDataGame, unknown10ae78) == 0x10ae78, "");
static_assert(offsetof(SDataGame, unknown10ae7c) == 0x10ae7c, "");
static_assert(offsetof(SDataGame, unknown10ae7d) == 0x10ae7d, "");
static_assert(offsetof(SDataGame, unknown10ae7e) == 0x10ae7e, "");
static_assert(offsetof(SDataGame, unknown10ae80) == 0x10ae80, "");
static_assert(offsetof(SDataGame, unknown10ae82) == 0x10ae82, "");
static_assert(offsetof(SDataGame, unknown10ae84) == 0x10ae84, "");
static_assert(offsetof(SDataGame, unknown1171d4) == 0x1171d4, "");
static_assert(offsetof(SDataGame, unknown1171d8) == 0x1171d8, "");
static_assert(offsetof(SDataGame, unknown117688) == 0x117688, "");
static_assert(sizeof(SDataGame) == 0x117690, "");

} // namespace gf
