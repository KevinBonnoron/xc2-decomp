#pragma once

namespace gf {
namespace enemy {

// The original enumerator names are unknown. The states registered by GfComBehaviorEnemy::createFsm are noted for each id.
enum STATE_ID {
  STATE_ID_UNKNOWN_0 = 0,   // StateBattle
  STATE_ID_UNKNOWN_1 = 1,   // StateFieldIdle
  STATE_ID_UNKNOWN_2 = 2,   // StateFieldIdle
  STATE_ID_UNKNOWN_3 = 3,   // StateFieldIdle
  STATE_ID_UNKNOWN_4 = 4,   // StateFieldIdle
  STATE_ID_UNKNOWN_5 = 5,   // StateFieldIdle
  STATE_ID_UNKNOWN_6 = 6,   // StateFieldSpawn
  STATE_ID_UNKNOWN_7 = 7,   // StateFieldSpawn
  STATE_ID_UNKNOWN_8 = 8,   // StateFieldAreaWalk
  STATE_ID_UNKNOWN_9 = 9,   // StateFieldWalk
  STATE_ID_UNKNOWN_10 = 10, // StateFieldAreaWalk
  STATE_ID_UNKNOWN_11 = 11, // StateFieldWalk
  STATE_ID_UNKNOWN_13 = 13, // StateFieldHome
  STATE_ID_UNKNOWN_14 = 14, // StateFieldSquadMember
  STATE_ID_UNKNOWN_15 = 15, // StateFieldBlade
};

} // namespace enemy
} // namespace gf
