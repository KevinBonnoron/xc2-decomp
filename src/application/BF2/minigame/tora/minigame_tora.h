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
  u8 unknown3a;                  // Inferred role: width of the hit box, added to the x of get_coli_xy by check_dmg_map_obj and check_atk_obj; original member name unknown.
  u8 unknown3b;                  // Inferred role: height of the hit box, added to the y of get_coli_xy by check_dmg_map_obj and check_atk_obj; original member name unknown.
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
  u8 unknown44;  // Inferred role: set to 1 while the player is held at its limit unknown56 of the y position (y grows downward, so the lower edge of the play area); original member name unknown.
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
  u8 unknown5c;  // Unsigned 8-bit value subtracted from x in get_pc_atk_xy; also half the width of the attack box in check_atk_obj (the attack is skipped when it is 0); original member name unknown.
  u8 unknown5d;  // Unsigned 8-bit value subtracted from y in get_pc_atk_xy; also half the height of the attack box in check_atk_obj; original member name unknown.
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

  u8 *unknown00; // Inferred role: archive data, a table of 32-bit offsets followed by the resources (get_res reads the table through a u32 pointer); original member name unknown.
};

static_assert(sizeof(archive) == 0x08, "");

// Inferred role: resource of the archive that holds a map; original type name unknown.
struct unknown001 {
  u16 unknown00; // Inferred role: width in tiles; original member name unknown.
  u16 unknown02; // Inferred role: height in tiles; original member name unknown.
  u8 _04[0x10 - 0x04];
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

struct unknown004;

// Inferred role: entry of the table of the rank list of the save data; original type name unknown.
struct unknown005 {
  u32 unknown00;     // Inferred role: score; original member name unknown.
  char unknown04[4]; // Inferred role: name of three letters; original member name unknown.
};

static_assert(sizeof(unknown005) == 0x08, "");

// Inferred role: save data of the minigame; original type name unknown.
struct unknown006 {
  u8 unknown00;  // Inferred role: set to 1 when the save data is valid; initialize tests the first three bytes as one 24-bit word (0x71006a2148, ldr w + and #0xffffff); original member name unknown.
  u8 unknown01;  // Inferred role: tested against 0 by initialize with unknown00 and unknown02; original member name unknown.
  u8 unknown02;  // Inferred role: tested against 0 by initialize with unknown00 and unknown01; original member name unknown.
  u8 unknown03;  // Inferred role: counter, grows by one for each 300 seconds since the time of unknown04 up to 3 (phase_boot); phase_title stores the credits left (unknown32f0) in it when a game
                 // starts; original member name unknown.
  u32 unknown04; // Inferred role: time of the last start in seconds of the year (phase_boot); original member name unknown.
  unknown005 unknown08[5]; // Inferred role: ranking; original member name unknown.
  union {
    struct {
      u64 unknown30; // Inferred role: total score; original member name unknown.
      int unknown38; // Inferred role: non-zero when phase_title offers the second menu entry; the game compares it with 0 as a 32-bit word (0x71006a3c4c); original member name unknown.
      int unknown3c; // Inferred role: counter increased when the clear phase starts (phase_clear, 0x71006aae48 to 0x71006aae54: `ldr; add; str` of the word at 0x401c); original member name unknown.
      int unknown40; // Inferred role: counter incremented when the game over screen starts (phase_over, 0x71006ac910); original member name unknown.
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
static_assert(offsetof(unknown006, unknown3c) == 0x3c, "");
static_assert(offsetof(unknown006, unknown40) == 0x40, "");
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
  u16 unknown00; // Inferred role: SpdD column scaled by 256/100; phase_game loads it with ldrh (0x71006a6080); original member name unknown.
  u16 unknown02; // Inferred role: SpdU column scaled by 256/100; phase_game loads it with ldrh (0x71006a60a0); original member name unknown.
  u16 unknown04; // Inferred role: AccU column scaled by 1024/1000; phase_game loads it with ldrh (0x71006a60b0); original member name unknown.
  u16 unknown06; // Inferred role: MaxU column scaled by 256/100; phase_game loads it with ldrh (0x71006a60d0); original member name unknown.
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
  u16 unknown02; // Inferred role: x in 1/64 pixel (phase_title draws it shifted right by 6, 0x71006a47cc, and title_vm adds signed bytes times 0x40); original member name unknown.
  u16 unknown04; // Inferred role: y in 1/64 pixel (phase_title draws it shifted right by 6, 0x71006a47d0); original member name unknown.
  u8 unknown06;  // Inferred role: flip, xor-ed with the mirroring flags of the frame by phase_title (0x71006a47a0, passed as the flip of draw_obj); original member name unknown.
  u8 unknown07;  // Inferred role: palette, passed as the palette of draw_obj by phase_title (0x71006a47a8); original member name unknown.
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

// Inferred role: object of the map, an entry of the list that phase_game builds from the map tiles; original type name unknown.
struct unknown088 {
  u8 unknown00; // Role not yet identified (cleared by phase_game); original member name unknown.
  u8 unknown01; // Role not yet identified (cleared by phase_game); original member name unknown.
  u8 unknown02; // Inferred role: tile of the object, zero ends the list; original member name unknown.
  u8 _03;
  u16 unknown04; // Inferred role: x in pixels; original member name unknown.
  u16 unknown06; // Inferred role: y in pixels; original member name unknown.
};

static_assert(sizeof(unknown088) == 0x08, "");

// Inferred role: position of a stage on the stage select screen, read from the csv of the archive by phase_select; original type name unknown. The game indexes the table with `lsl #1` and reads
// the two bytes at +0 and +1 (0x71006a4ba8, 0x71006a5190).
struct unknown089 {
  u8 unknown00; // Inferred role: x in pixels; original member name unknown.
  u8 unknown01; // Inferred role: y in pixels; original member name unknown.
};

static_assert(sizeof(unknown089) == 0x02, "");

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
  void phase_boot();
  void phase_title();
  void phase_select();
  void phase_game();
  void phase_clear();
  void phase_over();
  void phase_name();
  void get_pc_dxdy(int x, int y, int &dx, int &dy);
  void get_coli_xy(int &x, int &y, _sTask *task);
  void get_pc_atk_xy(int &x, int &y, _sTask *task);
  u8 *get_map_bin();
  u8 check_map(int x, int y);
  u8 get_tbox_type(int index);
  // 1 when the score unknown3410 is not below the entry of the stage unknown33e0 in the rank list, 0 for a stage out of range; an `int` for the join in phase_name (see there).
  int check_rank();
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
  u32 decode_4bpp_sprt(u32 tile, int sheet);
  // Inferred role: resets the position, bank and tile records of the layers of the screen buffers (0x00 to 0x35), inlined by the first sub phase of every phase; original name unknown.
  void unknown025();
  // Inferred role: clears the sprite widths and the line offsets (0x20d00) of the screen buffers, inlined by the first sub phase of every phase after unknown025; original name unknown.
  void unknown032();
  // Inferred name; single-user helper of phase_title (see its definition). Clears the counters of the menu of the title screen (unknown32f4, unknown32f8, unknown32fc).
  void clearMenuCounters();
  // Inferred role: clears the first layer of the screen buffers, decodes the sprite sheet 2 from tile 0x80 and clears the first palette entry (unknown65c[0]); inlined by the first sub phase of the
  // title, clear and game over screens; original name unknown.
  void unknown074();
  // Inferred role: one frame of the count-up of the clear screen (the step unknown3d88 lasts unknown3d89 frames), inlined by sub phases 3, 5, 8, 9 and 11 of phase_clear; original name unknown.
  void unknown075();
  // Inferred role: ends the frame of a phase: resets the number of sprites used, runs the draw functions of the tasks and clears the width of the sprites that they did not use; inlined by
  // phase_game, phase_over and phase_name; original name unknown.
  void unknown076();
  // Inferred role: one frame of the bubbles of the game screen: every 16th frame of unknown648 creates a bubble (create_awa) with a random x and the bottom y, then the move functions of the tasks
  // run; inlined by sub phases 1 to 11 of phase_game; original name unknown.
  void unknown087();
  // Inferred role: decodes the next sprite sheet of a chain (the end of the previous one, masked to 16 bits, plus a page), returns the end of the new sheet; inlined by phase_title and phase_game;
  // original name unknown.
  u32 unknown077(u32 tile, u32 page, int sheet);
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
  // The game loads it with `ldrh` and does not widen the load (phase_over 0x71006ac1ec). With the palettes typed _sPalette and update_palt called, a direct member keeps that load (without the typed
  // palettes and with the loop written out, GVN widened it to 64 bits as a member aligned to 8).
  s16 unknown658; // Inferred role: fade level of the palettes, 0 to 0xff in steps of 0x10; original member name unknown.
  u8 unknown65a;  // Role not yet identified (set by phase_boot, phase_title and phase_select; phase_clear and phase_over pass it to tora_cell_anime_setup); original member name unknown.
  u8 _65b[0x65c - 0x65b];
  _sPalette unknown65c[0x400]; // Inferred role: palettes, 64 palettes of 16 entries: decode_4bpp_sprt writes the palette of a sheet at entry (tile >> 8) & 0x3f0 and update_palt reads 0x400 entries
                               // from here, a pointer walk over _sPalette entries (a byte offset walk matches the standalone update_palt only, the inlined copies get another base register); original
                               // member name unknown.
  unknown001 *unknown1260;     // Inferred role: map resource; original member name unknown.
  unknown002 *unknown1268;     // Inferred role: tile data of the map, a resource of the archive; original member name unknown.
  u32 unknown1270;             // Inferred role: handle of the playing background music; original member name unknown.
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
    u16 unknown127e; // Inferred role: SpdU column of MIN_TT_PC scaled by 256/100 (read with ldrh by phase_game); original member name unknown.
    u16 unknown1280; // Inferred role: SpdLR column of MIN_TT_PC scaled by 256/100 (read with ldrh by phase_game); original member name unknown.
    u16 unknown1282; // Inferred role: SpdD column of MIN_TT_PC scaled by 256/100 (read with ldrh by phase_game, 0x71006a5af8); original member name unknown.
    u8 _1284[0x1288 - 0x1284];
    unknown014 unknown1288[32];  // Inferred role: enemy table, the MIN_TT_Enemy sheet read by initialize; original member name unknown.
    unknown007 unknown1688[16];  // Inferred role: treasure box table, the MIN_TT_Tbox sheet; original member name unknown.
    unknown016 unknown1928[129]; // Inferred role: treasure table, the MIN_TT_Tdef sheet read by initialize (row 0 unused); original member name unknown.
    unknown017 unknown3158[4];   // Inferred role: crystal table, the MIN_TT_Crystal sheet; original member name unknown.
    unknown018 unknown3198[8];   // Inferred role: stage table, the MIN_TT_Stage sheet; original member name unknown.
    u16 unknown32d8[8];          // Inferred role: Score column of ITM_EtherCrystal for the eight ether crystals; original member name unknown.
    s16 unknown32e8;             // Inferred role: Param column of BTL_SystemBalance row 0x8b, read as signed by phase_clear (ldrsh); original member name unknown.
    s16 unknown32ea;             // Inferred role: Param column of BTL_SystemBalance row 0x8c, read as signed by phase_clear (ldrsh); original member name unknown.
    s16 unknown32ec;             // Inferred role: Param column of BTL_SystemBalance row 0x8d, read as signed by phase_clear (ldrsh); original member name unknown.
    s16 unknown32ee;             // Inferred role: Param column of BTL_SystemBalance row 0x8e, read as signed by phase_clear (ldrsh); original member name unknown.
  };
  int unknown32f0; // Inferred role: number of credits shown by phase_title, decremented when a game starts; the game compares it signed (cmp w8, #2; csel lt, 0x71006a46dc); original member name
                   // unknown.
  u32 unknown32f4; // Role not yet identified (phase_title); original member name unknown.
  u32 unknown32f8; // Role not yet identified (phase_title); original member name unknown.
  u8 unknown32fc;  // Role not yet identified (phase_title); original member name unknown.
  u8 _32fd[0x3300 - 0x32fd];
  u8 unknown3300[0x10];      // Inferred role: registers of the script of title_vm; original member name unknown.
  const u8 *unknown3310;     // Inferred role: start of the script of title_vm; original member name unknown.
  const u8 *unknown3318;     // Inferred role: instruction pointer of title_vm, null when the script ended; original member name unknown.
  unknown019 unknown3320[8]; // Inferred role: sprites animated by title_vm; original member name unknown.
  int unknown33e0;           // Inferred role: rank of the stage; original member name unknown.
  u8 unknown33e4; // Inferred role: number of stages shown on the stage select screen, 1 to 8 (phase_select counts the stages of unknown3198 whose condition is met; the game reads it as one word
                  // together with unknown33e6); original member name unknown.
  u8 _33e5[0x33e6 - 0x33e5];
  s16 unknown33e6; // Inferred role: x of the cursor of the stage select screen, moves half way to the stage under it each frame; the game sign-extends it (sxth, 0x71006a54c0); original member name
                   // unknown.
  s16 unknown33e8; // Inferred role: y of the cursor of the stage select screen; the game loads it with ldrsh (0x71006a54b8); original member name unknown.
  unknown089 unknown33ea[(0x3400 - 0x33ea) / sizeof(unknown089)]; // Inferred role: positions of the stages on the stage select screen, indexed by unknown65a; the game addresses them from `this +
                                                                  // index * 2 + 0x33ea`; original member name unknown.
  u8 unknown3400;                                                 // Role not yet identified (phase_game, read as a halfword together with unknown3401); original member name unknown.
  u8 unknown3401;                                                 // Role not yet identified (phase_game); original member name unknown.
  u8 _3402[0x3404 - 0x3402];
  u16 unknown3404; // Role not yet identified (phase_game); original member name unknown.
  u8 _3406[0x3408 - 0x3406];
  u8 unknown3408; // Role not yet identified (phase_game, add_air); original member name unknown.
  u8 unknown3409; // Inferred role: timer of the score display; original member name unknown.
  u8 _340a[0x340b - 0x340a];
  u8 unknown340b;  // Role not yet identified (phase_game, phase_clear, enemy_damage); original member name unknown.
  u16 unknown340c; // Role not yet identified (phase_game, phase_clear, add_air); original member name unknown.
  u16 unknown340e; // Inferred role: air shown by the gauge, trails unknown340c by a share per frame while unknown3408 counts down (phase_game); original member name unknown.
  u32 unknown3410; // Inferred role: score; original member name unknown.
  u32 unknown3414; // Inferred role: score shown on the screen, catches up with unknown3410 by a share per frame while unknown3409 counts down, at most 999999 (phase_game); original member name
                   // unknown.
  u16 unknown3418; // Inferred role: ether count, the bonus items (class 0x60) picked up, incremented by item_move; phase_clear compares it with unknown356a and adds unknown341a to it; original member
                   // name unknown.
  u16 unknown341a; // Inferred role: second part of the ether count, added to unknown3418 by phase_game for the display under the ETHER label and by phase_clear; no other function of the unit writes
                   // it; original member name unknown.
  u8 _341c[0x3420 - 0x341c];
  unknown011 unknown3420[16]; // Inferred role: items waiting to be dropped; original member name unknown.
  void *unknown3520;          // Inferred role: item dropped by the next defeated enemy; original member name unknown.
  _sTask *m_sTask;            // Task whose 0x2c/0x30 fields get_pc_pos and get_pc_dxdy read; original member name unknown.
  unknown021 *unknown3530;    // Inferred role: item task of the treasure box that is kept in the map until it is opened; original member name unknown.
  int unknown3538; // Inferred role: scroll speed of the stage in 1/65536 pixel per frame, the SpdD column of the stage row (unknown018::unknown00) shifted left by 8; unknown3558 takes it in sub
                   // phases 0 and 4 of phase_game; original member name unknown.
  int unknown353c; // Inferred role: scroll speed while the scroll goes back to 0, the SpdU column (unknown018::unknown02) negated and shifted left by 8; unknown3558 takes it in sub phase 2 of
                   // phase_game; original member name unknown.
  int unknown3540; // Inferred role: change of the scroll speed per frame in sub phase 3 of phase_game, the AccU column (unknown018::unknown04) negated and shifted left by 6; original member name
                   // unknown.
  int unknown3544; // Inferred role: lower limit of the scroll speed in sub phase 3 of phase_game, the MaxU column (unknown018::unknown06) negated and shifted left by 8; original member name unknown.
  u16 unknown3548; // Inferred role: Scroll column of the stage row (unknown018::unknown08); non-zero lets sub phase 1 of phase_game change the scroll speed by the level unknown355c, and phase_game
                   // stores it in unknown56 of the player task; original member name unknown.
  u16 unknown354a; // Inferred role: StarRate column of the stage row (unknown018::unknown0c), the chance in 10000 that enemy_damage leaves a star (item kind 0); original member name unknown.
  u16 unknown354c; // Inferred role: BotRate column of the stage row (unknown018::unknown0e), the chance in 10000 after StarRate that enemy_damage leaves a bottle (item kind 1); original member name
                   // unknown.
  u8 unknown354e;  // Inferred role: BotVal column of the stage row (unknown018::unknown10), the air that a bottle gives (item_move passes it to add_air); original member name unknown.
  u8 _354f[0x3550 - 0x354f];
  u16 unknown3550; // Inferred role: BonusTime column of the stage row (unknown018::unknown12), the frames of the bonus scene (sub phase 8 of phase_game copies it to unknown3d6e); original member name
                   // unknown.
  u16 unknown3552; // Inferred role: UniRate column of the stage row (unknown018::unknown14), the chance in 10000 that the bonus object of sub phase 9 of phase_game has sheet 0x35 and no score;
                   // original member name unknown.
  u8 unknown3554;  // Inferred role: EthRate column of the stage row (unknown018::unknown16), stored by sub phase 9 of phase_game as the score (unknown6c) of the other bonus object, sheet 0x30;
                   // original member name unknown.
  u8 unknown3555;  // Inferred role: BonusEntry column of the stage row (unknown018::unknown17), stored by phase_game in unknown78 of the enemy tasks with move type 0xa; original member name unknown.
  u8 _3556[0x3558 - 0x3556];
  int unknown3558; // Signed (effect_move divides it by 256 and subtracts it from the y speed of a bubble; phase_game); original member name unknown.
  s8 unknown355c;  // Role not yet identified (phase_game); original member name unknown.
  u8 _355d[0x3560 - 0x355d];
  int unknown3560; // Divided by 256 and added to the y of m_sTask in get_pc_pos and get_pc_dxdy; original member name unknown.
  union {
    int unknown3564; // Inferred role: scroll limit in 1/65536 pixel; original member name unknown.
    struct {
      u16 unknown3564_16; // Inferred role: low half of unknown3564, the part below one pixel; original member name unknown.
      u16 unknown3566;    // Inferred role: height of the map in pixels minus the screen height, the high half of unknown3564; original member name unknown.
    };
  };
  u16 unknown3568;               // Role not yet identified (phase_game, phase_clear); original member name unknown.
  u16 unknown356a;               // Role not yet identified (phase_game, phase_clear); original member name unknown.
  unknown088 unknown356c[0x100]; // Inferred role: objects of the map in the order of their position, ended by an entry whose unknown02 is zero; original member name unknown.
  u8 unknown3d6c;                // Inferred role: sub phase (unknown650) to run when the fade-in after the bonus scene ends; original member name unknown.
  u8 unknown3d6d;                // Inferred role: set to end the bonus scene early; original member name unknown.
  u16 unknown3d6e;               // Inferred role: frames left of the bonus scene; original member name unknown.
  u16 unknown3d70;               // Inferred role: x of the player in pixels, saved during the bonus scene; original member name unknown.
  u16 unknown3d72;               // Inferred role: y of the player in pixels, saved during the bonus scene; original member name unknown.
  u16 unknown3d74;               // Inferred role: unknown56 of the player task, saved during the bonus scene; original member name unknown.
  u8 _3d76[0x3d78 - 0x3d76];
  unknown027 unknown3d78; // Inferred role: state of the cell animation, set by tora_cell_anime_setup; original member name unknown.
  u8 unknown3d88;         // Inferred role: step of the count-up of phase_clear, set to 0 with unknown3d89 by phase_over and phase_clear when the fade-in ends; original member name unknown.
  u8 unknown3d89;         // Inferred role: frames left in the step of phase_clear, set to 30 when the fade-in ends (phase_over, phase_clear); original member name unknown.
  u8 unknown3d8a;         // Role not yet identified (cleared by phase_clear); original member name unknown.
  u8 _3d8b;
  u32 unknown3d8c; // Inferred role: pool that phase_clear still has to move, a share per frame, into the score (unknown3410) or the ether count (unknown3418): the bonus of the step; original member
                   // name unknown.
  u32 unknown3d90; // Inferred role: second pool of sub phase 9 of phase_clear, moved into the ether count (unknown3418) with unknown3d8c; set to the Score of ITM_EtherCrystal row 4 (unknown32d8[4]);
                   // original member name unknown.
  u8 unknown3d94[8];    // Role not yet identified (cleared by phase_clear, with unknown3d9c and unknown3da1[0] as one 14 byte store run); original member name unknown.
  u8 unknown3d9c[5];    // Inferred role: bonus given, one per bonus of the clear phase; original member name unknown.
  u8 unknown3da1[5];    // Inferred role: bonus earned, one per bonus of the clear phase; original member name unknown.
  u16 unknown3da6;      // Inferred role: item of the treasure box shown by phase_clear; original member name unknown.
  u8 unknown3da8[16];   // Inferred role: treasure boxes picked up, 0xff ends the list; original member name unknown.
  u8 unknown3db8[0x18]; // Inferred role: state of each treasure box of the list (phase_clear); phase_over clears the 0x18 bytes as three 64-bit stores, 0x71006ac920; original member name unknown.
  u64 unknown3dd0;      // Role not yet identified (cleared by phase_name, 0x71006ad894); original member name unknown.
  u8 unknown3dd8;       // Inferred role: blink timer of the name entry, incremented every frame (phase_name); original member name unknown.
  u8 unknown3dd9;       // Inferred role: index of the letter being entered (phase_name); original member name unknown.
  u8 unknown3dda;       // Inferred role: index in the alphabet of the letter being entered (phase_name); original member name unknown.
  u8 unknown3ddb;       // Inferred role: set when the score enters the ranking, the player then enters initials (phase_name); original member name unknown.
  char unknown3ddc[4];  // Inferred role: name being entered, three letters and the end of string (phase_name); original member name unknown.
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
static_assert(offsetof(minigame, unknown650) == 0x650, "");
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
static_assert(offsetof(minigame, unknown65a) == 0x65a, "");
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
static_assert(offsetof(minigame, unknown3d88) == 0x3d88, "");
static_assert(offsetof(minigame, unknown3d8c) == 0x3d8c, "");
static_assert(offsetof(minigame, unknown3d90) == 0x3d90, "");
static_assert(offsetof(minigame, unknown3d94) == 0x3d94, "");
static_assert(offsetof(minigame, unknown3d9c) == 0x3d9c, "");
static_assert(offsetof(minigame, unknown3da1) == 0x3da1, "");
static_assert(offsetof(minigame, unknown3da6) == 0x3da6, "");
static_assert(offsetof(minigame, unknown3da8) == 0x3da8, "");
static_assert(offsetof(minigame, unknown3db8) == 0x3db8, "");
static_assert(offsetof(minigame, unknown3dd0) == 0x3dd0, "");
static_assert(offsetof(minigame, unknown3dd8) == 0x3dd8, "");
static_assert(offsetof(minigame, unknown3ddb) == 0x3ddb, "");
static_assert(offsetof(minigame, unknown3ddc) == 0x3ddc, "");
static_assert(sizeof(minigame) == 0x40c8, "");

// Inferred role: screen buffers of the minigame; original type name unknown.
struct unknown004 {
  u8 *unknown00;       // Inferred role: bitmap of 256 by 256 pixels of one byte, an index in unknown08, used by update when unknown11 is set; original member name unknown.
  const u8 *unknown08; // Inferred role: palette of the bitmap, 3 bytes per entry; original member name unknown.
  u8 unknown10;        // Inferred role: brightness level written by update_palt, brightness of the bitmap pixels in update; original member name unknown.
  u8 unknown11;        // Inferred role: set when the bitmap is shown; original member name unknown.
  u8 _12[0x18 - 0x12];
  u8 unknown18; // Inferred role: palette bank of the sprites; original member name unknown.
  u8 _19;
  u16 unknown1a; // Inferred role: first tile of the sprites; original member name unknown.
  s16 unknown1c; // Inferred role: horizontal offset of the sprites; original member name unknown.
  s16 unknown1e; // Inferred role: vertical offset of the sprites; original member name unknown.
  u8 unknown20;  // Inferred role: palette bank of the first layer; original member name unknown.
  u8 _21;
  u16 unknown22; // Inferred role: first tile of the first layer; original member name unknown.
  s16 unknown24; // Inferred role: horizontal scroll of the first layer; original member name unknown.
  s16 unknown26; // Inferred role: vertical scroll of the map in pixels; original member name unknown.
  u8 unknown28;  // Inferred role: palette bank of the second layer; original member name unknown.
  u8 _29;
  u16 unknown2a; // Inferred role: first tile of the second layer; original member name unknown.
  s16 unknown2c; // Inferred role: horizontal scroll of the second layer; original member name unknown.
  s16 unknown2e; // Inferred role: vertical scroll of the second layer; original member name unknown.
  u8 unknown30;  // Inferred role: palette bank of the text layer; original member name unknown.
  u8 _31;
  u16 unknown32; // Inferred role: first tile of the text layer; original member name unknown.
  s8 unknown34;  // Inferred role: width in tiles of the text layer on the left (positive) or on the right (negative); original member name unknown.
  s8 unknown35;  // Inferred role: height in tiles of the text layer at the top (positive) or at the bottom (negative); original member name unknown.
  u8 _36[0x38 - 0x36];
  u8 unknown38; // Inferred role: reduction of the colours of the frame, 0 for none to 3; original member name unknown.
  u8 _39[0x100 - 0x39];
  u8 unknown100[0x20000]; // Inferred role: tile memory, 0x1000 tiles of 32 bytes written by decode_4bpp_sprt; phase_game (0x71006a61f4) and tora_cell_anime also write eight rows of 64
                          // big-endian words each, at 0x3000 and 0x2800; original member name unknown.
  minigame::_sPalette unknown20100[0x400]; // Inferred role: faded copy of the palettes of minigame::unknown65c, written by update_palt; original member name unknown.
  s16 unknown20d00[0x200];                 // Inferred role: horizontal offsets per line, 0x100 entries for the first layer then 0x100 for the second; original member name unknown.
  unknown003 unknown21100[0x40];           // Inferred role: sprites; original member name unknown.
  u16 unknown21500[0x1000];                // Inferred role: map of 64 by 64 tiles of the first layer; original member name unknown.
  u16 unknown23500[0x1000];                // Inferred role: map of 64 by 64 tiles of the second layer; original member name unknown.
  u16 unknown25500[0x800];                 // Inferred role: text screen, 64 by 32 characters; original member name unknown.
  u16 unknown26500[0xf0][0x140];           // Inferred role: pixels of the sprites, the 4 bits of priority, the 8 bits of the palette bank and the 4 bits of the colour; original member name unknown.
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
