#pragma once
#include <stddef.h>

#include "framework/object/updatable_object.h"
#include "framework/pointer_map.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class CommonResource;
class SoundResource;
} // namespace fw

namespace gf {
class GfMenuCallContext;
} // namespace gf

namespace layer {
class LayerBase;
} // namespace layer

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace minigame {
namespace tora {
namespace factory {

fw::UpdatableObject *create(ui::UIObjectAcc *parent);

} // namespace factory

struct _sTask {
  _sTask *unknown00;             // Inferred role: next task of the list, or next free slot; original member name unknown.
  _sTask *unknown08;             // Inferred role: previous task of the list; original member name unknown.
  void (*unknown10)(void *task); // Inferred role: move function called by mytask::executeMove; original member name unknown.
  void (*unknown18)(void *task); // Inferred role: draw function called by mytask::executeDraw; original member name unknown.
  const char *unknown20;         // Inferred role: name of the task, "awa", "tora", "item" or the Name column of an enemy row; original member name unknown.
  u8 unknown28;                  // Inferred role: mirroring flags, bit 0 flips x and bit 1 flips y in draw_obj; original member name unknown.
  u8 unknown29;                  // Role not yet identified (zeroed with unknown28 by the creation of a task, the compiler merges the four stores); original member name unknown.
  u8 unknown2a;                  // Role not yet identified (zeroed with unknown28 by the creation of a task); original member name unknown.
  u8 unknown2b;                  // Role not yet identified (zeroed with unknown28 by the creation of a task); original member name unknown.
  int unknown2c;                 // Read by get_pc_pos and, shifted right by 8, by get_coli_xy and get_pc_atk_xy as the x coordinate; original member name unknown.
  int unknown30;                 // Read by get_pc_pos and, shifted right by 8, by get_coli_xy and get_pc_atk_xy as the y coordinate; original member name unknown.
  u8 unknown34;                  // Inferred role: mask of what hits this task; original member name unknown.
  u8 unknown35;                  // Inferred role: hit result written by check_dmg_map_obj and check_atk_obj; original member name unknown.
  s16 unknown36;                 // Signed 16-bit offset added to the shifted x in get_coli_xy; original member name unknown.
  s16 unknown38;                 // Signed 16-bit offset added to the shifted y in get_coli_xy; original member name unknown.
  u8 unknown3a;                  // Inferred role: width of the hit box; original member name unknown.
  u8 unknown3b;                  // Inferred role: height of the hit box; original member name unknown.
  u8 _3c[0x40 - 0x3c];
};

static_assert(sizeof(_sTask) == 0x40, "");

// Inferred role: effect task (bubble) run by effect_move and effect_draw; original type name unknown.
// The task kinds share the header of _sTask and overlay their own data from 0x40 on, so each kind is a view
// derived from _sTask whose members are named by their byte offset in the task.
struct unknown020 : _sTask {
  u8 unknown40; // Inferred role: kind, 0 draws the bubble; original member name unknown.
  u8 unknown41; // Inferred role: animation counter, drives the horizontal sway; original member name unknown.
  u8 unknown42; // Inferred role: frames to live, 0 for no limit; original member name unknown.
  u8 _43;
  int unknown44; // Inferred role: horizontal speed in 1/256 pixel; original member name unknown.
  int unknown48; // Inferred role: vertical speed in 1/256 pixel, added to the scroll compensation; original member name unknown.
};

static_assert(offsetof(unknown020, unknown44) == 0x44, "");
static_assert(sizeof(unknown020) == 0x50, "");

// Inferred role: item task run by item_move and item_draw; original type name unknown.
struct unknown021 : _sTask {
  u8 unknown40;  // Inferred role: item and kind, bits 0..4 the item, bits 5..6 the class (0x40 treasure box, 0x60 bonus item); original member name unknown.
  u8 unknown41;  // Inferred role: state; original member name unknown.
  u8 unknown42;  // Inferred role: frame counter; original member name unknown.
  u8 unknown43;  // Inferred role: duration; original member name unknown.
  int unknown44; // Inferred role: x at which the item sits in 1/256 pixel; original member name unknown.
  int unknown48; // Inferred role: y at which the item sits in 1/256 pixel; original member name unknown.
  int unknown4c; // Inferred role: x at the start of the move; original member name unknown.
  int unknown50; // Inferred role: y at the start of the move; original member name unknown.
  int unknown54; // Inferred role: x distance of the move; original member name unknown.
  int unknown58; // Inferred role: y distance of the move; original member name unknown.
  u16 unknown5c; // Inferred role: score of the item; original member name unknown.
};

static_assert(offsetof(unknown021, unknown54) == 0x54, "");
static_assert(offsetof(unknown021, unknown5c) == 0x5c, "");

// Inferred role: player task run by player_move and player_draw; original type name unknown.
struct unknown022 : _sTask {
  u8 unknown40;  // Role not yet identified (0 while the player is controlled, 2 ignores the push of the map; player_move, player_draw); original member name unknown.
  u8 unknown41;  // Inferred role: frames left of the stun after a hit, set to 0x20; the player blinks while it is odd and bubbles appear above 0x18; original member name unknown.
  u8 unknown42;  // Inferred role: frame of the body, set by player_move from the direction; original member name unknown.
  u8 unknown43;  // Inferred role: frame counter, bit 4 alternates the frame of the body; original member name unknown.
  u8 unknown44;  // Inferred role: set to 1 while the player is held at the upper limit of the screen; original member name unknown.
  u8 unknown45;  // Inferred role: frame of the attack, 0 when idle, counts up to 15; original member name unknown.
  u8 unknown46;  // Inferred role: direction of the player, index of 9 directions; original member name unknown.
  u8 unknown47;  // Inferred role: set to 1 when the attack bounced; original member name unknown.
  u16 unknown48; // Inferred role: frames of invincibility left (0x168 after a star); original member name unknown.
  u8 _4a[0x4c - 0x4a];
  u8 unknown4c; // Role not yet identified (zero when the player can be hurt; player_move); original member name unknown.
  u8 unknown4d; // Role not yet identified (selects the mask of what the attack hits in check_atk_obj); original member name unknown.
  u8 _4e;
  u8 unknown4f;  // Inferred role: damage the map does to the player, a quarter of the Hp column of MIN_TT_PC; original member name unknown.
  u16 unknown50; // Inferred role: SpdU column of MIN_TT_PC scaled by 256/100, the speed up; original member name unknown.
  u16 unknown52; // Inferred role: SpdLR column of MIN_TT_PC scaled by 256/100, the speed to the sides; original member name unknown.
  u16 unknown54; // Inferred role: SpdD column of MIN_TT_PC scaled by 256/100, the speed down; original member name unknown.
  u16 unknown56; // Inferred role: limit of the y position, in pixels; original member name unknown.
  s16 unknown58; // Signed 16-bit offset added to the shifted x in get_pc_atk_xy; original member name unknown.
  s16 unknown5a; // Signed 16-bit offset added to the shifted y in get_pc_atk_xy; original member name unknown.
  u8 unknown5c;  // Unsigned 8-bit value subtracted from x in get_pc_atk_xy; original member name unknown.
  u8 unknown5d;  // Unsigned 8-bit value subtracted from y in get_pc_atk_xy; original member name unknown.
};

static_assert(offsetof(unknown022, unknown58) == 0x58, "");
static_assert(offsetof(unknown022, unknown5a) == 0x5a, "");
static_assert(offsetof(unknown022, unknown5c) == 0x5c, "");
static_assert(offsetof(unknown022, unknown5d) == 0x5d, "");

// Inferred role: segment of the tail of a type 9 enemy; original type name unknown.
struct unknown026 {
  s8 unknown00; // Inferred role: x offset in pixels from the head; original member name unknown.
  s8 unknown01; // Inferred role: y offset in pixels from the head; original member name unknown.
  u8 unknown02; // Inferred role: angle of the segment, 256 for a turn; original member name unknown.
  u8 _03;
  u8 unknown04[12]; // Inferred role: previous angles, handed to the next segment; original member name unknown.
};

static_assert(sizeof(unknown026) == 0x10, "");

// Inferred role: enemy task run by enemy_move and enemy_draw; original type name unknown. The 0x88 to 0xc7 bytes hold four segments of 16 bytes (see enemy_move).
struct unknown023 : _sTask {
  u8 unknown40; // Inferred role: set once the four tail tasks of a type 9 enemy exist; original member name unknown.
  u8 unknown41; // Role not yet identified; original member name unknown.
  u8 unknown42; // Inferred role: frame counter, incremented by enemy_move; original member name unknown.
  u8 unknown43; // Inferred role: movement state; original member name unknown.
  u8 unknown44; // Inferred role: wait or animation counter of the movement; original member name unknown.
  u8 unknown45; // Inferred role: frames left of the knock back; original member name unknown.
  u8 unknown46; // Inferred role: direction of the knock back, index of a table of offsets; original member name unknown.
  u8 _47;
  int unknown48; // Inferred role: x position in 1/256 pixel; original member name unknown.
  int unknown4c; // Inferred role: y position in 1/256 pixel; original member name unknown.
  int unknown50; // Inferred role: horizontal speed in 1/256 pixel; original member name unknown.
  int unknown54; // Inferred role: vertical speed in 1/256 pixel; original member name unknown.
  int unknown58; // Inferred role: x of the start position in 1/256 pixel; original member name unknown.
  int unknown5c; // Inferred role: y of the start position in 1/256 pixel; original member name unknown.
  u16 unknown60; // Inferred role: Speed column of the enemy row; original member name unknown.
  u16 unknown62; // Inferred role: Range column of the enemy row; original member name unknown.
  u16 unknown64; // Inferred role: Search column of the enemy row; original member name unknown.
  u16 unknown66; // Inferred role: ActSpd column of the enemy row; original member name unknown.
  u8 unknown68;  // Inferred role: BackFrm column of the enemy row; original member name unknown.
  u8 unknown69;  // Inferred role: copy of the enemy row byte that follows BackFrm, stored by the creation of the task; original member name unknown.
  u16 unknown6a; // Inferred role: BackSpd column of the enemy row; original member name unknown.
  u16 unknown6c; // Inferred role: Score column of the enemy row; original member name unknown.
  u8 unknown6e;  // Inferred role: HitW column of the enemy row, stored by the creation of the task; original member name unknown.
  u8 unknown6f;  // Inferred role: MoveType column of the enemy row; original member name unknown.
  u8 unknown70;  // Inferred role: HitType column of the enemy row; original member name unknown.
  u8 unknown71;  // Inferred role: sprite sheet used by enemy_draw; original member name unknown.
  u8 _72[0x78 - 0x72];
  u8 unknown78; // Inferred role: index plus one of a tail task in its head, 0 for the head; original member name unknown.
  u8 _79[0x80 - 0x79];
  unknown023 *unknown80;   // Inferred role: head of a tail task; original member name unknown.
  unknown026 unknown88[4]; // Inferred role: segments of the tail of a type 9 enemy; original member name unknown.
};

static_assert(offsetof(unknown023, unknown48) == 0x48, "");
static_assert(offsetof(unknown023, unknown60) == 0x60, "");
static_assert(offsetof(unknown023, unknown6f) == 0x6f, "");
static_assert(offsetof(unknown023, unknown80) == 0x80, "");
static_assert(sizeof(unknown023) == 0xc8, "");

static_assert(offsetof(_sTask, unknown2c) == 0x2c, "");
static_assert(offsetof(_sTask, unknown30) == 0x30, "");
static_assert(offsetof(_sTask, unknown36) == 0x36, "");
static_assert(offsetof(_sTask, unknown38) == 0x38, "");
static_assert(offsetof(_sTask, unknown20) == 0x20, "");
static_assert(offsetof(_sTask, unknown28) == 0x28, "");
static_assert(offsetof(_sTask, unknown34) == 0x34, "");
static_assert(offsetof(_sTask, unknown35) == 0x35, "");
static_assert(offsetof(_sTask, unknown3a) == 0x3a, "");
static_assert(offsetof(_sTask, unknown3b) == 0x3b, "");

static_assert(offsetof(_sTask, unknown00) == 0x00, "");
static_assert(offsetof(_sTask, unknown08) == 0x08, "");
static_assert(offsetof(_sTask, unknown10) == 0x10, "");
static_assert(offsetof(_sTask, unknown18) == 0x18, "");

void effect_move(void *task);
void item_move(void *task);
void item_draw(void *task);

class mytask {
public:
  mytask(int taskSize, int taskCount);
  ~mytask();
  void reset();
  void *entry();
  void *entryNext(void *task);
  void *entryTop();
  void *entryPrev(void *task);
  void *entryEnd();
  void remove(void *task);
  void executeMove();
  void executeDraw();
  void *enum_next(void *task);

  void *unknown00;   // Inferred role: memory of the task pool; original member name unknown.
  int unknown08;     // Inferred role: size of a task; original member name unknown.
  int unknown0c;     // Inferred role: number of tasks; original member name unknown.
  _sTask *unknown10; // Inferred role: first free task; original member name unknown.
  _sTask *unknown18; // Inferred role: first task of the list; original member name unknown.
  _sTask *unknown20; // Inferred role: last task of the list; original member name unknown.
  _sTask *unknown28; // Inferred role: task executeMove and executeDraw run next, kept up to date when remove runs from a callback; original member name unknown.
};

static_assert(offsetof(mytask, unknown08) == 0x08, "");
static_assert(offsetof(mytask, unknown10) == 0x10, "");
static_assert(offsetof(mytask, unknown28) == 0x28, "");
static_assert(sizeof(mytask) == 0x30, "");

class archive {
public:
  void *get_res(int index);
  int get_res_sz(int index);

  u32 *unknown00; // Inferred role: archive data, a table of offsets followed by the resources; original member name unknown.
};

static_assert(sizeof(archive) == 0x08, "");

// Inferred role: resource of the archive that holds a map; original type name unknown.
struct unknown001 {
  u8 _00[0x10];
  u8 unknown10[]; // Inferred role: map tiles, 16 per row; original member name unknown.
};

static_assert(sizeof(unknown001) == 0x10, "");

// Inferred role: resource of the archive that holds sprite tiles and a palette; original type name unknown.
struct unknown002 {
  u8 _00[0x02];
  u16 unknown02; // Inferred role: size of the palette that precedes the tiles, zero without palette; original member name unknown.
  u16 unknown04; // Inferred role: width of the tile data in pixels, zero for tiles stored one after the other; original member name unknown.
  u16 unknown06; // Inferred role: height of the tile data in pixels, or number of tiles when unknown04 is zero; original member name unknown.
  u8 unknown08;  // Inferred role: nonzero when frames of the sprite sheet follow the tile data; original member name unknown.
  u8 _09[0x10 - 0x09];
  u8 unknown10[]; // Inferred role: palette entries followed by the tiles; original member name unknown.
};

static_assert(offsetof(unknown002, unknown02) == 0x02, "");
static_assert(offsetof(unknown002, unknown04) == 0x04, "");
static_assert(offsetof(unknown002, unknown06) == 0x06, "");
static_assert(offsetof(unknown002, unknown08) == 0x08, "");
static_assert(sizeof(unknown002) == 0x10, "");

// Inferred role: hardware sprite of the screen buffers; original type name unknown.
struct unknown003 {
  u8 unknown00; // Inferred role: mirroring flags; original member name unknown.
  u8 unknown01; // Inferred role: palette; original member name unknown.
  u8 _02[0x04 - 0x02];
  s16 unknown04; // Inferred role: x; original member name unknown.
  s16 unknown06; // Inferred role: y; original member name unknown.
  s16 unknown08; // Inferred role: tile; original member name unknown.
  u8 unknown0a;  // Inferred role: width in tiles; original member name unknown.
  u8 unknown0b;  // Inferred role: height in tiles; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(unknown003, unknown04) == 0x04, "");
static_assert(offsetof(unknown003, unknown0a) == 0x0a, "");
static_assert(sizeof(unknown003) == 0x10, "");

// Inferred role: frame of a sprite sheet; original type name unknown.
struct unknown012 {
  u8 unknown00; // Inferred role: mirroring flags; original member name unknown.
  u8 _01;
  u16 unknown02; // Inferred role: first tile, relative to the tiles of the sheet; original member name unknown.
  u8 unknown04;  // Inferred role: width in pixels; original member name unknown.
  u8 unknown05;  // Inferred role: height in pixels; original member name unknown.
  s8 unknown06;  // Inferred role: x offset; original member name unknown.
  s8 unknown07;  // Inferred role: y offset; original member name unknown.
};

static_assert(offsetof(unknown012, unknown06) == 0x06, "");
static_assert(sizeof(unknown012) == 0x08, "");

// Inferred role: sprite sheet loaded by decode_4bpp_sprt; original type name unknown.
struct unknown013 {
  u32 unknown00; // Inferred role: first tile of the sheet; original member name unknown.
  u16 unknown04; // Inferred role: unknown08 of the sheet resource (unknown002), nonzero when the sheet has frames; original member name unknown.
  u8 _06[0x08 - 0x06];
  const unknown012 *unknown08; // Inferred role: frames; original member name unknown.
  u8 _10[0x18 - 0x10];
};

static_assert(offsetof(unknown013, unknown08) == 0x08, "");
static_assert(offsetof(unknown013, unknown04) == 0x04, "");
static_assert(sizeof(unknown013) == 0x18, "");

// Inferred role: screen buffers of the minigame; original type name unknown.
struct unknown004 {
  u8 _00[0x10];
  u8 unknown10; // Inferred role: brightness level written by update_palt; original member name unknown.
  u8 _11[0x1c - 0x11];
  s16 unknown1c; // Inferred role: horizontal offset of the sprites; original member name unknown.
  s16 unknown1e; // Inferred role: vertical offset of the sprites; original member name unknown.
  u8 _20[0x26 - 0x20];
  s16 unknown26; // Inferred role: vertical scroll of the map in pixels; original member name unknown.
  u8 _28[0x100 - 0x28];
  u8 unknown100[0x20000]; // Inferred role: tile memory, 0x1000 tiles of 32 bytes written by decode_4bpp_sprt; original member name unknown.
  u8 unknown20100[0xc00]; // Inferred role: faded copy of the palettes of minigame::unknown65c, 64 palettes of 16 entries of 3 bytes, written by update_palt; original member name unknown.
  u8 _20d00[0x21100 - 0x20d00];
  unknown003 unknown21100[0x40]; // Inferred role: sprites; original member name unknown.
  u8 _21500[0x25500 - 0x21500];
  u16 unknown25500[0x800]; // Inferred role: text screen, 64 by 32 characters; original member name unknown.
  u8 _26500[0x4bd00 - 0x26500];
};

static_assert(offsetof(unknown004, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown004, unknown1e) == 0x1e, "");
static_assert(offsetof(unknown004, unknown26) == 0x26, "");
static_assert(offsetof(unknown004, unknown21100) == 0x21100, "");
static_assert(offsetof(unknown004, unknown10) == 0x10, "");
static_assert(offsetof(unknown004, unknown100) == 0x100, "");
static_assert(offsetof(unknown004, unknown20100) == 0x20100, "");
static_assert(offsetof(unknown004, unknown25500) == 0x25500, "");
static_assert(sizeof(unknown004) == 0x4bd00, "");

// Inferred role: entry of the table of the rank list of the save data; original type name unknown.
struct unknown005 {
  u32 unknown00;     // Inferred role: score; original member name unknown.
  char unknown04[4]; // Inferred role: name of three letters; original member name unknown.
};

static_assert(sizeof(unknown005) == 0x08, "");

// Inferred role: save data of the minigame; original type name unknown.
struct unknown006 {
  u8 unknown00; // Inferred role: set to 1 when the save data is valid; initialize tests the first three bytes as one 24-bit word (0x71006a2148, ldr w + and #0xffffff); original member name unknown.
  u8 unknown01; // Inferred role: tested against 0 by initialize with unknown00 and unknown02; original member name unknown.
  u8 unknown02; // Inferred role: tested against 0 by initialize with unknown00 and unknown01; original member name unknown.
  u8 _03[0x08 - 0x03];
  unknown005 unknown08[5]; // Inferred role: ranking; original member name unknown.
  union {
    struct {
      u64 unknown30; // Inferred role: total score; original member name unknown.
      u8 _38[0x44 - 0x38];
      int unknown44; // Inferred role: number of bonus items obtained, incremented by item_move; original member name unknown.
      int unknown48; // Inferred role: number of items obtained; original member name unknown.
      u8 _4c[0xd0 - 0x4c];
    };
    // Inferred role: counters of the save data from 0x30 on, 4 bytes each, the number of enemies defeated per row of the enemy table at 0x4c (index 7 plus the row);
    // enemy_damage (0x71006af2e8) addresses them from `this + 0x4010` with the index plus 7, which only an array that starts at 0x30 gives; original member name unknown.
    int unknown30_s32[0x28];
  };
};

static_assert(offsetof(unknown006, unknown08) == 0x08, "");
static_assert(sizeof(unknown006) == 0xd0, "");

// Inferred role: treasure and condition of a treasure box; original type name unknown.
struct unknown009 {
  u16 unknown00; // Inferred role: item table, the tdefN column of MIN_TT_Tbox; original member name unknown.
  u16 unknown02; // Inferred role: game condition, the condN column of MIN_TT_Tbox; original member name unknown.
};

static_assert(sizeof(unknown009) == 0x04, "");

// Inferred role: entry of the treasure box table; original type name unknown.
struct unknown007 {
  u8 m_tbox_type; // Inferred role: type of the box, the Type column of MIN_TT_Tbox; named after the game accessor minigame::tora::minigame::get_tbox_type (AGENTS.md accessor rule).
  u8 _01;
  unknown009 unknown02[10];
};

static_assert(offsetof(unknown007, unknown02) == 0x02, "");
static_assert(sizeof(unknown007) == 0x2a, "");

// Inferred role: entry of the result table; original type name unknown.
struct unknown008 {
  u16 unknown00; // Inferred role: item; original member name unknown.
  u16 unknown02; // Inferred role: number of times the item was obtained; original member name unknown.
};

static_assert(sizeof(unknown008) == 0x04, "");

// Inferred role: item and number of times it was obtained in a result; original type name unknown.
struct unknown010 {
  u16 unknown00; // Inferred role: item; original member name unknown.
  u16 unknown02; // Inferred role: number of times the item was obtained; original member name unknown.
};

static_assert(sizeof(unknown010) == 0x04, "");

// Inferred role: item waiting to be dropped; original type name unknown.
struct unknown011 {
  u8 unknown00;    // Inferred role: item, 0xff when the slot is free; original member name unknown.
  void *unknown08; // Inferred role: object of the item; original member name unknown.
};

static_assert(sizeof(unknown011) == 0x10, "");

// Inferred role: entry of the enemy table, a row of the MIN_TT_Enemy sheet; original type name unknown.
struct unknown014 {
  const char *unknown00; // Inferred role: Name column, a string (initialize stores the 64-bit Bdat::uVal of Bdat::getVal at 0x71006a1ac8+); original member name unknown.
  u8 unknown08;          // Inferred role: MoveType column; original member name unknown.
  u8 unknown09;          // Inferred role: HitType column; original member name unknown.
  u8 unknown0a;          // Inferred role: HitW column; original member name unknown.
  u8 unknown0b;          // Inferred role: HitH column; original member name unknown.
  u8 unknown0c;          // Inferred role: Atk column; original member name unknown.
  u8 _0d;
  s16 unknown0e; // Inferred role: Speed column scaled by 256/100; original member name unknown.
  u16 unknown10; // Inferred role: Range column; original member name unknown.
  u16 unknown12; // Inferred role: Search column; original member name unknown.
  s16 unknown14; // Inferred role: ActSpd column scaled by 256/100; original member name unknown.
  u8 unknown16;  // Inferred role: Hp column; original member name unknown.
  u8 unknown17;  // Inferred role: BackFrm column; original member name unknown.
  s16 unknown18; // Inferred role: BackSpd column scaled by 256/100; original member name unknown.
  u16 unknown1a; // Inferred role: Score column; original member name unknown.
  u8 unknown1c;  // Inferred role: ResID column; original member name unknown.
  u8 _1d[3];
};

static_assert(offsetof(unknown014, unknown0e) == 0x0e, "");
static_assert(offsetof(unknown014, unknown1c) == 0x1c, "");
static_assert(sizeof(unknown014) == 0x20, "");

// Inferred role: item and rate of a row of the MIN_TT_Tdef sheet; original type name unknown.
struct unknown015 {
  u16 unknown00; // Inferred role: itemN column; original member name unknown.
  u8 unknown02;  // Inferred role: rateN column; original member name unknown.
  u8 _03;
};

static_assert(sizeof(unknown015) == 0x04, "");

// Inferred role: row of the MIN_TT_Tdef sheet; original type name unknown.
struct unknown016 {
  unknown015 unknown00[12]; // Inferred role: the item1 to item12 and rate1 to rate12 columns; original member name unknown.
};

static_assert(sizeof(unknown016) == 0x30, "");

// Inferred role: row of the MIN_TT_Crystal sheet; original type name unknown.
struct unknown017 {
  u16 unknown00; // Inferred role: Score column; original member name unknown.
  u8 _02[0x08 - 0x02];
  const char *unknown08; // Inferred role: Res column, a string (the 64-bit Bdat::uVal of Bdat::getVal); original member name unknown.
};

static_assert(offsetof(unknown017, unknown08) == 0x08, "");
static_assert(sizeof(unknown017) == 0x10, "");

// Inferred role: row of the MIN_TT_Stage sheet; original type name unknown.
struct unknown018 {
  s16 unknown00; // Inferred role: SpdD column scaled by 256/100; original member name unknown.
  s16 unknown02; // Inferred role: SpdU column scaled by 256/100; original member name unknown.
  s16 unknown04; // Inferred role: AccU column scaled by 1024/1000; original member name unknown.
  s16 unknown06; // Inferred role: MaxU column scaled by 256/100; original member name unknown.
  u16 unknown08; // Inferred role: Scroll column; original member name unknown.
  u16 unknown0a; // Inferred role: Bonus column; original member name unknown.
  u16 unknown0c; // Inferred role: StarRate column; original member name unknown.
  u16 unknown0e; // Inferred role: BotRate column; original member name unknown.
  u8 unknown10;  // Inferred role: BotVal column; original member name unknown.
  u8 _11;
  u16 unknown12; // Inferred role: BonusTime column; original member name unknown.
  u16 unknown14; // Inferred role: UniRate column; original member name unknown.
  u8 unknown16;  // Inferred role: EthRate column; original member name unknown.
  u8 unknown17;  // Inferred role: BonusEntry column; original member name unknown.
  u16 unknown18; // Inferred role: Condition column; original member name unknown.
  u8 _1a[0x20 - 0x1a];
  const char *unknown20; // Inferred role: Res column, a string (the 64-bit Bdat::uVal of Bdat::getVal); original member name unknown.
};

static_assert(offsetof(unknown018, unknown12) == 0x12, "");
static_assert(offsetof(unknown018, unknown20) == 0x20, "");
static_assert(sizeof(unknown018) == 0x28, "");

// Inferred role: sprite animated by title_vm; original type name unknown.
struct unknown019 {
  u8 unknown00;  // Inferred role: sprite sheet plus one, zero when the slot is free; original member name unknown.
  u8 unknown01;  // Inferred role: frame; original member name unknown.
  u16 unknown02; // Inferred role: x in 1/256 pixel; original member name unknown.
  u16 unknown04; // Inferred role: y in 1/256 pixel; original member name unknown.
  u8 unknown06;  // Inferred role: palette; original member name unknown.
  u8 unknown07;  // Inferred role: flip; original member name unknown.
  u8 unknown08;  // Inferred role: frames left in the current step; original member name unknown.
  u8 unknown09;  // Inferred role: offset of the current step in the animation; original member name unknown.
  u8 _0a[0x10 - 0x0a];
  const u8 *unknown10; // Inferred role: animation script; original member name unknown.
};

static_assert(offsetof(unknown019, unknown10) == 0x10, "");
static_assert(sizeof(unknown019) == 0x18, "");

// Inferred role: state of the cell animation of tora_cell_anime; original type name unknown.
struct unknown027 {
  u8 *unknown00;   // Inferred role: resource of the cell animation (palette at 0x10, tiles of the two frames at 0x40 and 0x840); original member name unknown.
  u8 unknown08;    // Inferred role: frame of the cell animation shown last, 0 or 1; original member name unknown.
  u8 unknown09;    // Inferred role: frames left before the cell animation shows its next frame; original member name unknown.
  u8 unknown0a[2]; // Inferred role: frames each frame of the cell animation stays, read from the csv of the archive by tora_cell_anime_setup; original member name unknown.
};

static_assert(offsetof(unknown027, unknown0a) == 0x0a, "");
static_assert(sizeof(unknown027) == 0x10, "");

class minigame : public mm::mtl::PtrSingleton<minigame> {
public:
  struct _sResult {
    u32 unknown00;               // Inferred role: best score of the ranking; original member name unknown.
    unknown010 unknown04[0x100]; // Inferred role: items obtained, ended by an entry of zeros; the 0x404 bytes are the local MinigameUpdatableObject::update (0x71006a0ad8) reserves for it; original
                                 // member name unknown.
  };

  // Name from the mangled symbol of draw_mesh_box (minigame::tora::minigame::_sPalette).
  struct _sPalette {
    u8 unknown00; // Inferred role: first of the three bytes of a pixel that draw_mesh_box copies; original member name unknown.
    u8 unknown01; // Inferred role: second byte of the pixel; original member name unknown.
    u8 unknown02; // Inferred role: third byte of the pixel; original member name unknown.
  };

  void get_pc_pos(int &x, int &y);
  void title_vm();
  void initialize();
  void finalize();
  void update_pad();
  void get_pc_dxdy(int x, int y, int &dx, int &dy);
  void get_coli_xy(int &x, int &y, _sTask *task);
  void get_pc_atk_xy(int &x, int &y, _sTask *task);
  u8 *get_map_bin();
  u8 check_map(int x, int y);
  u8 get_tbox_type(int index);
  bool check_rank();
  void sprite_reset();
  unknown003 *sprite_get();
  void reset_save();
  u8 *get_res_pal(int index);
  void req_reload();
  void playse(int id);
  u32 get_pc_dist(int x, int y);
  void draw_text(u16 *dst, u16 base, const char *text);
  void debug_text(int x, int y, const char *text);
  void vram_fill(u16 *dst, int width, int height, u16 value);
  void clip_screen(int &x, int &y, int &width, int &height, int &dstX, int &dstY);
  void getResult(_sResult *result);
  void get_score_text(char *text, u32 score);
  void draw_mesh_box(u8 *dst, int stride, int x, int y, int width, int height, const _sPalette *palette);
  u32 decode_4bpp_sprt(u32 tile, const u8 *res);
  void decode_4bpp_sprt(u32 tile, int sheet);
  void debug_hex(int x, int y, u32 value, int digits);
  u8 check_map(_sTask *task);
  _sTask *check_dmg_map_obj(_sTask *task, u8 &mapHit);
  _sTask *check_atk_obj(_sTask *task);
  void update_palt(int level);
  void draw_obj(int sheet, int frame, const _sTask *task, u8 palette);
  int add_item(int item, void *param);
  void *get_dropitem();
  void playbgm(int index);
  void draw_obj(int sheet, int frame, int x, int y, u8 flip, u8 palette);
  // The constructor inlined in MinigameUpdatableObject::myinit (0x71006a077c) stores unknown18, m_archive and m_mytask, nothing else. The game has its own destructors D2 and D0 (0x71006a0f38 and
  // 0x71006a0f58, the vtable 0x71011a79b8 points at D2) next to MinigameUpdatableObject, emitted at the end of that unit with the vtable: an inline destructor. An empty body is aliased to the one of
  // PtrSingleton<minigame> (no D2 of its own), a body that is not empty (the null statement, as in users::Component1) keeps D2 and D0, and being inline it has no D1.
  minigame() : unknown18(nullptr), m_archive(), m_mytask(nullptr) {}
  ~minigame() override { ; }

  // Defined by the owners of those functions; MinigameUpdatableObject calls it.
  void update(u8 *screen, int width, int height, void *resource, void *soundResource);
  void get_pc_vxvy(int x, int y, int speed, int &vx, int &vy);
  static int get_time();
  int add_result(u16 id, u32 &score);
  void tora_cell_anime_setup(int index);
  void tora_cell_anime();
  _sTask *task_entry();
  u32 add_air(int amount);
  void enemy_damage(_sTask *task, int damage);
  void choice_tbox(int index, u16 &result, u16 *items);
  // Inferred role: one step of the linear congruential generator on unknown0c, returns the new state (callers use >> 8 and masks); original name unknown. Users: phase_game, create_awa, player_move,
  // enemy_move, item_move, ...
  u32 unknown024() {
    unknown0c = unknown0c * 0x41c64e6d + 0x3039;
    return unknown0c;
  }

  u8 unknown08; // Inferred role: cleared by initialize; original member name unknown.
  u8 _09[0xc - 0x9];
  u32 unknown0c;                // Inferred role: random number generator state, seeded by initialize from ml::mtRand; original member name unknown.
  u32 unknown10;                // Inferred role: pad buttons held, built by update_pad; original member name unknown.
  u32 unknown14;                // Inferred role: pad buttons pressed this frame, built by update_pad; original member name unknown.
  unknown004 *unknown18;        // Inferred role: screen buffers; original member name unknown.
  archive m_archive;            // Inferred role: archive of the resources; original member name unknown.
  fw::SoundResource *unknown28; // Inferred role: sound resource whose pack plays the sound effects; original member name unknown.
  unknown013 unknown30[65];     // Inferred role: loaded sprite sheets; original member name unknown.
  int unknown648;               // Inferred role: cleared by initialize; original member name unknown.
  u32 unknown64c;               // Inferred role: phase to run; original member name unknown.
  u32 unknown650;               // Inferred role: phase to run after unknown64c; original member name unknown.
  u8 _654[0x658 - 0x654];
  s16 unknown658; // Inferred role: fade level of the palettes, 0 to 0xff in steps of 0x10; original member name unknown.
  u8 unknown65a;  // Role not yet identified (set by phase_boot, phase_title and phase_select); original member name unknown.
  u8 _65b[0x65c - 0x65b];
  u8 unknown65c[0xc00]; // Inferred role: palettes, 64 palettes of 16 entries of 3 bytes: decode_4bpp_sprt writes the palette of a sheet at ((tile >> 8) & 0x3f0) * 3 and update_palt reads 0xc00 bytes
                        // from here; original member name unknown.
  unknown001 *unknown1260; // Inferred role: map resource; original member name unknown.
  u64 unknown1268;         // Role not yet identified (read by phase_game); original member name unknown.
  u32 unknown1270;         // Inferred role: handle of the playing background music; original member name unknown.
  u8 _1274[0x1278 - 0x1274];
  // Inferred role: the tables that initialize reads from the BDAT sheets (MIN_TT_PC, MIN_TT_Enemy, MIN_TT_Tbox, MIN_TT_Tdef, MIN_TT_Crystal, MIN_TT_Stage, ITM_EtherCrystal, BTL_SystemBalance), one
  // nested object that starts at 0x1278; choice_tbox (0x71006afaa0) reads unknown1688 and unknown1928 from the shared base `this + 0x1278`, which only members of a nested object give (a scratch with
  // the members of the class itself addresses them from `this`); original member name and type name unknown.
  struct {
    u16 unknown1278; // Inferred role: Hp column of MIN_TT_PC read by initialize; original member name unknown.
    u8 unknown127a;  // Inferred role: HitW column of MIN_TT_PC; original member name unknown.
    u8 unknown127b;  // Inferred role: HitH column of MIN_TT_PC; original member name unknown.
    u8 unknown127c;  // Inferred role: AtkW column of MIN_TT_PC; original member name unknown.
    u8 unknown127d;  // Inferred role: AtkH column of MIN_TT_PC; original member name unknown.
    s16 unknown127e; // Inferred role: SpdU column of MIN_TT_PC scaled by 256/100; original member name unknown.
    s16 unknown1280; // Inferred role: SpdLR column of MIN_TT_PC scaled by 256/100; original member name unknown.
    s16 unknown1282; // Inferred role: SpdD column of MIN_TT_PC scaled by 256/100; original member name unknown.
    u8 _1284[0x1288 - 0x1284];
    unknown014 unknown1288[32];  // Inferred role: enemy table, the MIN_TT_Enemy sheet read by initialize; original member name unknown.
    unknown007 unknown1688[16];  // Inferred role: treasure box table, the MIN_TT_Tbox sheet; original member name unknown.
    unknown016 unknown1928[129]; // Inferred role: treasure table, the MIN_TT_Tdef sheet read by initialize (row 0 unused); original member name unknown.
    unknown017 unknown3158[4];   // Inferred role: crystal table, the MIN_TT_Crystal sheet; original member name unknown.
    unknown018 unknown3198[8];   // Inferred role: stage table, the MIN_TT_Stage sheet; original member name unknown.
    u16 unknown32d8[8];          // Inferred role: Score column of ITM_EtherCrystal for the eight ether crystals; original member name unknown.
    u16 unknown32e8;             // Inferred role: Param column of BTL_SystemBalance row 0x8b; original member name unknown.
    u16 unknown32ea;             // Inferred role: Param column of BTL_SystemBalance row 0x8c; original member name unknown.
    u16 unknown32ec;             // Inferred role: Param column of BTL_SystemBalance row 0x8d; original member name unknown.
    u16 unknown32ee;             // Inferred role: Param column of BTL_SystemBalance row 0x8e; original member name unknown.
  };
  u32 unknown32f0; // Role not yet identified (phase_boot, phase_title); original member name unknown.
  u32 unknown32f4; // Role not yet identified (phase_title); original member name unknown.
  u32 unknown32f8; // Role not yet identified (phase_title); original member name unknown.
  u8 unknown32fc;  // Role not yet identified (phase_title); original member name unknown.
  u8 _32fd[0x3300 - 0x32fd];
  u8 unknown3300[0x10];      // Inferred role: registers of the script of title_vm; original member name unknown.
  const u8 *unknown3310;     // Inferred role: start of the script of title_vm; original member name unknown.
  const u8 *unknown3318;     // Inferred role: instruction pointer of title_vm, null when the script ended; original member name unknown.
  unknown019 unknown3320[8]; // Inferred role: sprites animated by title_vm; original member name unknown.
  int unknown33e0;           // Inferred role: rank of the stage; original member name unknown.
  u8 unknown33e4;            // Role not yet identified (phase_select, read as one word together with unknown33e6); original member name unknown.
  u8 _33e5[0x33e6 - 0x33e5];
  u16 unknown33e6;                 // Role not yet identified (phase_select); original member name unknown.
  u16 unknown33e8;                 // Role not yet identified (phase_select); original member name unknown.
  u8 unknown33ea[0x3400 - 0x33ea]; // Inferred role: pairs of coordinates indexed by unknown65a (phase_select); original member name unknown.
  u8 unknown3400;                  // Role not yet identified (phase_game, read as a halfword together with unknown3401); original member name unknown.
  u8 unknown3401;                  // Role not yet identified (phase_game); original member name unknown.
  u8 _3402[0x3404 - 0x3402];
  u16 unknown3404; // Role not yet identified (phase_game); original member name unknown.
  u8 _3406[0x3408 - 0x3406];
  u8 unknown3408; // Role not yet identified (phase_game, add_air); original member name unknown.
  u8 unknown3409; // Inferred role: timer of the score display; original member name unknown.
  u8 _340a[0x340b - 0x340a];
  u8 unknown340b;  // Role not yet identified (phase_game, phase_clear, enemy_damage); original member name unknown.
  u16 unknown340c; // Role not yet identified (phase_game, phase_clear, add_air); original member name unknown.
  u16 unknown340e; // Role not yet identified (phase_game); original member name unknown.
  u32 unknown3410; // Inferred role: score; original member name unknown.
  u32 unknown3414; // Role not yet identified (phase_game); original member name unknown.
  u16 unknown3418; // Inferred role: bonus item of the result; original member name unknown.
  u8 _341a[0x3420 - 0x341a];
  unknown011 unknown3420[16]; // Inferred role: items waiting to be dropped; original member name unknown.
  void *unknown3520;          // Inferred role: item dropped by the next defeated enemy; original member name unknown.
  _sTask *m_sTask;            // Task whose 0x2c/0x30 fields get_pc_pos and get_pc_dxdy read; original member name unknown.
  u64 unknown3530;            // Role not yet identified (phase_game); original member name unknown.
  u32 unknown3538;            // Role not yet identified (phase_game); original member name unknown.
  u32 unknown353c;            // Role not yet identified (phase_game); original member name unknown.
  u32 unknown3540;            // Role not yet identified (phase_game); original member name unknown.
  u32 unknown3544;            // Role not yet identified (phase_game); original member name unknown.
  u16 unknown3548;            // Role not yet identified (phase_game); original member name unknown.
  u16 unknown354a;            // Role not yet identified (phase_game, enemy_damage); original member name unknown.
  u16 unknown354c;            // Role not yet identified (phase_game, enemy_damage); original member name unknown.
  u8 unknown354e;             // Role not yet identified (phase_game); original member name unknown.
  u8 _354f[0x3550 - 0x354f];
  u16 unknown3550; // Role not yet identified (phase_game); original member name unknown.
  u16 unknown3552; // Role not yet identified (phase_game); original member name unknown.
  u8 unknown3554;  // Role not yet identified (phase_game); original member name unknown.
  u8 unknown3555;  // Role not yet identified (phase_game); original member name unknown.
  u8 _3556[0x3558 - 0x3556];
  int unknown3558; // Signed (effect_move divides it by 256 and subtracts it from the y speed of a bubble; phase_game); original member name unknown.
  u8 unknown355c;  // Role not yet identified (phase_game); original member name unknown.
  u8 _355d[0x3560 - 0x355d];
  int unknown3560;                 // Divided by 256 and added to the y of m_sTask in get_pc_pos and get_pc_dxdy; original member name unknown.
  u16 unknown3564;                 // Role not yet identified (phase_game, read as one word together with unknown3566); original member name unknown.
  u16 unknown3566;                 // Inferred role: height of the map in pixels minus the screen height; original member name unknown.
  u16 unknown3568;                 // Role not yet identified (phase_game, phase_clear); original member name unknown.
  u16 unknown356a;                 // Role not yet identified (phase_game, phase_clear); original member name unknown.
  u8 unknown356c[0x3d6c - 0x356c]; // Role not yet identified (phase_game reads records of 8 bytes from 0x356c and halfwords at 0x3570 and 0x3572); original member name unknown.
  u8 unknown3d6c[0x3d78 - 0x3d6c]; // Role not yet identified (phase_game); original member name unknown.
  unknown027 unknown3d78;          // Inferred role: state of the cell animation, set by tora_cell_anime_setup; original member name unknown.
  u8 _3d88[0x3de0 - 0x3d88];
  unknown008 unknown3de0[0x80]; // Inferred role: result table, one entry per item; original member name unknown.
  unknown006 unknown3fe0;       // Inferred role: save data; original member name unknown.
  u8 unknown40b0;               // Inferred role: number of sprites used in the frame; original member name unknown.
  u8 _40b1[0x40b8 - 0x40b1];
  mytask *m_mytask; // Inferred role: task list; named after its type, see AGENTS.md.
  u8 _40c0[0x40c8 - 0x40c0];
};

static_assert(offsetof(minigame, unknown18) == 0x18, "");
static_assert(offsetof(minigame, m_archive) == 0x20, "");
static_assert(offsetof(minigame, unknown28) == 0x28, "");
static_assert(offsetof(minigame, unknown30) == 0x30, "");
static_assert(offsetof(minigame, unknown64c) == 0x64c, "");
static_assert(offsetof(minigame, unknown1260) == 0x1260, "");
static_assert(offsetof(minigame, unknown1270) == 0x1270, "");
static_assert(offsetof(minigame, unknown1688) == 0x1688, "");
static_assert(offsetof(minigame, unknown33e0) == 0x33e0, "");
static_assert(offsetof(minigame, unknown3409) == 0x3409, "");
static_assert(offsetof(minigame, unknown3410) == 0x3410, "");
static_assert(offsetof(minigame, unknown3420) == 0x3420, "");
static_assert(offsetof(minigame, unknown3520) == 0x3520, "");
static_assert(offsetof(minigame, m_sTask) == 0x3528, "");
static_assert(offsetof(minigame, unknown3560) == 0x3560, "");
static_assert(offsetof(minigame, unknown3566) == 0x3566, "");
static_assert(offsetof(minigame, unknown3de0) == 0x3de0, "");
static_assert(offsetof(minigame, unknown3fe0) == 0x3fe0, "");
static_assert(offsetof(minigame, unknown40b0) == 0x40b0, "");
static_assert(offsetof(minigame, m_mytask) == 0x40b8, "");
static_assert(offsetof(minigame, unknown658) == 0x658, "");
static_assert(offsetof(minigame, unknown65c) == 0x65c, "");
static_assert(offsetof(minigame, unknown1278) == 0x1278, "");
static_assert(offsetof(minigame, unknown1282) == 0x1282, "");
static_assert(offsetof(minigame, unknown1288) == 0x1288, "");
static_assert(offsetof(minigame, unknown1928) == 0x1928, "");
static_assert(offsetof(minigame, unknown3158) == 0x3158, "");
static_assert(offsetof(minigame, unknown3198) == 0x3198, "");
static_assert(offsetof(minigame, unknown32d8) == 0x32d8, "");
static_assert(offsetof(minigame, unknown32f0) == 0x32f0, "");
static_assert(offsetof(minigame, unknown3300) == 0x3300, "");
static_assert(offsetof(minigame, unknown3310) == 0x3310, "");
static_assert(offsetof(minigame, unknown3320) == 0x3320, "");
static_assert(offsetof(minigame, unknown33ea) == 0x33ea, "");
static_assert(offsetof(minigame, unknown3400) == 0x3400, "");
static_assert(offsetof(minigame, unknown3414) == 0x3414, "");
static_assert(offsetof(minigame, unknown3538) == 0x3538, "");
static_assert(offsetof(minigame, unknown3558) == 0x3558, "");
static_assert(offsetof(minigame, unknown356c) == 0x356c, "");
static_assert(offsetof(minigame, unknown3d6c) == 0x3d6c, "");
static_assert(offsetof(minigame, unknown3d78) == 0x3d78, "");
static_assert(sizeof(minigame) == 0x40c8, "");

class MinigameUpdatableObject : public fw::UpdatableObject {
public:
  static mm::mtl::RTTI m_rtti;

  MinigameUpdatableObject(u32 type, const fw::HandlePtr<fw::UpdatableObject> &handle, u32 layer);
  ~MinigameUpdatableObject() override;
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
  void res_load();
  void myinit(ui::UIObjectAcc *parent);
  bool disp_result();

  ui::UIObjectAcc *m_uIObjectAcc;           // Inferred role: on-memory screen the game draws into, or null; named after the game type (decision 58).
  layer::LayerBase *m_layerBase;            // Inferred role: memory layer the game draws into when no screen is given; named after the game type (decision 58).
  fw::CommonResource *m_commonResource;     // Inferred role: resource minigame/tora.bin; named after the game type (decision 58).
  fw::SoundResource *m_soundResource;       // Inferred role: sound resource sound/se/minigame.xsp; named after the game type (decision 58).
  minigame *m_minigame;                     // Inferred role: the minigame; named after the game type (decision 58).
  gf::GfMenuCallContext *m_menuCallContext; // Inferred role: context of the result window; named after the game type (decision 58).
  unknown010 *unknown110;                   // Inferred role: items of the result, entry 0 holds the next index and the count; original member name unknown.
};

static_assert(offsetof(MinigameUpdatableObject, m_uIObjectAcc) == 0xe0, "");
static_assert(offsetof(MinigameUpdatableObject, m_layerBase) == 0xe8, "");
static_assert(offsetof(MinigameUpdatableObject, m_commonResource) == 0xf0, "");
static_assert(offsetof(MinigameUpdatableObject, m_soundResource) == 0xf8, "");
static_assert(offsetof(MinigameUpdatableObject, m_minigame) == 0x100, "");
static_assert(offsetof(MinigameUpdatableObject, m_menuCallContext) == 0x108, "");
static_assert(offsetof(MinigameUpdatableObject, unknown110) == 0x110, "");
static_assert(sizeof(MinigameUpdatableObject) == 0x118, "");

void effect_move(void *task);
void item_move(void *task);
void item_draw(void *task);
void effect_draw(void *task);
unknown020 *create_awa();
void player_move(void *task);
void player_draw(void *task);
void enemy_move(void *task);
void enemy_draw(void *task);

} // namespace tora
} // namespace minigame
