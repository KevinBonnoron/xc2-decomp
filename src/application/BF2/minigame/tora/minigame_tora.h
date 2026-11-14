#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
class SoundResource;
class UpdatableObject;
} // namespace fw

namespace ui {
class UIObjectAcc;
}

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
  u8 _20[0x2c - 0x20];
  int unknown2c; // Read by get_pc_pos and, shifted right by 8, by get_coli_xy and get_pc_atk_xy as the x coordinate; original member name unknown.
  int unknown30; // Read by get_pc_pos and, shifted right by 8, by get_coli_xy and get_pc_atk_xy as the y coordinate; original member name unknown.
  u8 _34[0x36 - 0x34];
  s16 unknown36; // Signed 16-bit offset added to the shifted x in get_coli_xy; original member name unknown.
  s16 unknown38; // Signed 16-bit offset added to the shifted y in get_coli_xy; original member name unknown.
  u8 _3a[0x58 - 0x3a];
  s16 unknown58; // Signed 16-bit offset added to the shifted x in get_pc_atk_xy; original member name unknown.
  s16 unknown5a; // Signed 16-bit offset added to the shifted y in get_pc_atk_xy; original member name unknown.
  u8 unknown5c;  // Unsigned 8-bit value subtracted from x in get_pc_atk_xy; original member name unknown.
  u8 unknown5d;  // Unsigned 8-bit value subtracted from y in get_pc_atk_xy; original member name unknown.
};

static_assert(offsetof(_sTask, unknown2c) == 0x2c, "");
static_assert(offsetof(_sTask, unknown30) == 0x30, "");
static_assert(offsetof(_sTask, unknown36) == 0x36, "");
static_assert(offsetof(_sTask, unknown38) == 0x38, "");
static_assert(offsetof(_sTask, unknown58) == 0x58, "");
static_assert(offsetof(_sTask, unknown5a) == 0x5a, "");
static_assert(offsetof(_sTask, unknown5c) == 0x5c, "");
static_assert(offsetof(_sTask, unknown5d) == 0x5d, "");
static_assert(offsetof(_sTask, unknown00) == 0x00, "");
static_assert(offsetof(_sTask, unknown08) == 0x08, "");
static_assert(offsetof(_sTask, unknown10) == 0x10, "");
static_assert(offsetof(_sTask, unknown18) == 0x18, "");

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
  u8 _04[0x10 - 0x04];
  u8 unknown10[]; // Inferred role: palette entries followed by the tiles; original member name unknown.
};

static_assert(offsetof(unknown002, unknown02) == 0x02, "");
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
  u8 _04[0x08 - 0x04];
  const unknown012 *unknown08; // Inferred role: frames; original member name unknown.
  u8 _10[0x18 - 0x10];
};

static_assert(offsetof(unknown013, unknown08) == 0x08, "");
static_assert(sizeof(unknown013) == 0x18, "");

// Inferred role: screen buffers of the minigame; original type name unknown.
struct unknown004 {
  u8 _00[0x1c];
  s16 unknown1c; // Inferred role: horizontal offset of the sprites; original member name unknown.
  s16 unknown1e; // Inferred role: vertical offset of the sprites; original member name unknown.
  u8 _20[0x21100 - 0x20];
  unknown003 unknown21100[0x40]; // Inferred role: sprites; original member name unknown.
  u8 _21500[0x25500 - 0x21500];
  u16 unknown25500[0x800]; // Inferred role: text screen, 64 by 32 characters; original member name unknown.
  u8 _26500[0x4bd00 - 0x26500];
};

static_assert(offsetof(unknown004, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown004, unknown1e) == 0x1e, "");
static_assert(offsetof(unknown004, unknown21100) == 0x21100, "");
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
  u8 unknown00; // Inferred role: set to 1 when the save data is valid; original member name unknown.
  u8 _01[0x08 - 0x01];
  unknown005 unknown08[5]; // Inferred role: ranking; original member name unknown.
  u64 unknown30;           // Inferred role: total score; original member name unknown.
  u8 _38[0x48 - 0x38];
  int unknown48; // Inferred role: number of items obtained; original member name unknown.
  u8 _4c[0xd0 - 0x4c];
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
  u8 unknown00; // Inferred role: type of the box, the Type column of MIN_TT_Tbox; original member name unknown.
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

class minigame : public mm::mtl::PtrSingleton<minigame> {
public:
  struct _sResult {
    u32 unknown00;          // Inferred role: best score of the ranking; original member name unknown.
    unknown010 unknown04[]; // Inferred role: items obtained, ended by an entry of zeros; original member name unknown.
  };

  void get_pc_pos(int &x, int &y);
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
  int add_item(int item, void *param);
  void *get_dropitem();
  void playbgm(int index);
  void draw_obj(int sheet, int frame, int x, int y, u8 flip, u8 palette);

  u8 _08[0x18 - 0x08];
  unknown004 *unknown18;        // Inferred role: screen buffers; original member name unknown.
  archive unknown20;            // Inferred role: archive of the resources; original member name unknown.
  fw::SoundResource *unknown28; // Inferred role: sound resource whose pack plays the sound effects; original member name unknown.
  unknown013 unknown30[65];     // Inferred role: loaded sprite sheets; original member name unknown.
  u8 _648[0x64c - 0x648];
  u32 unknown64c; // Inferred role: phase to run; original member name unknown.
  u32 unknown650; // Inferred role: phase to run after unknown64c; original member name unknown.
  u8 _654[0x1260 - 0x654];
  unknown001 *unknown1260; // Inferred role: map resource; original member name unknown.
  u8 _1268[0x1270 - 0x1268];
  u32 unknown1270; // Inferred role: handle of the playing background music; original member name unknown.
  u8 _1274[0x1688 - 0x1274];
  unknown007 unknown1688[16]; // Inferred role: treasure box table, the MIN_TT_Tbox sheet; original member name unknown.
  u8 _1928[0x33e0 - 0x1928];
  int unknown33e0; // Inferred role: rank of the stage; original member name unknown.
  u8 _33e4[0x3409 - 0x33e4];
  u8 unknown3409; // Inferred role: timer of the score display; original member name unknown.
  u8 _340a[0x3410 - 0x340a];
  u32 unknown3410; // Inferred role: score; original member name unknown.
  u8 _3414[0x3418 - 0x3414];
  u16 unknown3418; // Inferred role: bonus item of the result; original member name unknown.
  u8 _341a[0x3420 - 0x341a];
  unknown011 unknown3420[16]; // Inferred role: items waiting to be dropped; original member name unknown.
  void *unknown3520;          // Inferred role: item dropped by the next defeated enemy; original member name unknown.
  _sTask *unknown3528;        // Task whose 0x2c/0x30 fields get_pc_pos and get_pc_dxdy read; original member name unknown.
  u8 _3530[0x3560 - 0x3530];
  int unknown3560; // Divided by 256 and added to the y of unknown3528 in get_pc_pos and get_pc_dxdy; original member name unknown.
  u8 _3564[0x3566 - 0x3564];
  u16 unknown3566; // Inferred role: height of the map in pixels minus the screen height; original member name unknown.
  u8 _3568[0x3de0 - 0x3568];
  unknown008 unknown3de0[0x80]; // Inferred role: result table, one entry per item; original member name unknown.
  unknown006 unknown3fe0;       // Inferred role: save data; original member name unknown.
  u8 unknown40b0;               // Inferred role: number of sprites used in the frame; original member name unknown.
};

static_assert(offsetof(minigame, unknown18) == 0x18, "");
static_assert(offsetof(minigame, unknown20) == 0x20, "");
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
static_assert(offsetof(minigame, unknown3528) == 0x3528, "");
static_assert(offsetof(minigame, unknown3560) == 0x3560, "");
static_assert(offsetof(minigame, unknown3566) == 0x3566, "");
static_assert(offsetof(minigame, unknown3de0) == 0x3de0, "");
static_assert(offsetof(minigame, unknown3fe0) == 0x3fe0, "");
static_assert(offsetof(minigame, unknown40b0) == 0x40b0, "");

} // namespace tora
} // namespace minigame
