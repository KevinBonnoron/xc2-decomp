// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/minigame/tora/minigame_tora.cpp.
#include "minigame/tora/minigame_tora.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "bdat.h"
#include "csvb/csvb_data.h"
#include "framework/memory/framework_memory.h"
#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_pad.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_pad.h"
#include "gf/gf_allocator.h"
#include "ml/rand.h"
#include "ml/time_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixstr.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace minigame {
namespace tora {

void minigame::get_pc_pos(int &x, int &y) {
  x = m_sTask->unknown2c;
  y = m_sTask->unknown30 + unknown3560 / 256;
}

void minigame::get_pc_dxdy(int x, int y, int &dx, int &dy) {
  dx = x - m_sTask->unknown2c;
  dy = y - m_sTask->unknown30 - unknown3560 / 256;
}

void minigame::get_coli_xy(int &x, int &y, _sTask *task) {
  x = task->unknown2c >> 8;
  y = task->unknown30 >> 8;
  x += task->unknown36;
  y += task->unknown38;
}

void minigame::get_pc_atk_xy(int &x, int &y, _sTask *task) {
  unknown022 *player = static_cast<unknown022 *>(task);
  x = player->unknown2c >> 8;
  y = player->unknown30 >> 8;
  x += player->unknown58;
  y += player->unknown5a;
  x -= player->unknown5c;
  y -= player->unknown5d;
}

// The offsets are read through a u32 pointer of the byte base: with a u32 member the inlined `get_res(0) + 8` of phase_boot is reassociated by the DAG, the byte base keeps the `or` of the game
// (0x71006a338c) when the offset of the font is added as an integer.
void *archive::get_res(int index) {
  const u32 *table = reinterpret_cast<const u32 *>(unknown00);
  u8 *res = unknown00 + ((table[0] + 0x10) & ~0xf);
  if (index > 0) {
    res += table[index];
  }
  return res;
}

int archive::get_res_sz(int index) { return static_cast<u8 *>(get_res(index + 1)) - static_cast<u8 *>(get_res(index)); }

u8 *minigame::get_map_bin() {
  if (unknown1260 == nullptr) {
    return nullptr;
  }
  return unknown1260->unknown10;
}

u8 minigame::check_map(int x, int y) {
  u8 *map = get_map_bin();
  if (map == nullptr) {
    return 0;
  }
  if (static_cast<u32>(x) < 0x100 && y >= 0 && y < unknown3566 + 0xf0) {
    return map[(y & ~0xf) + (x >> 4)];
  }
  return 0x80;
}

// Inferred role: tests the solid bit (0x80) of the map tile at the pixel column x and the pixel row y, in the rows that start at `rows`; original name unknown. Used five times: four by
// check_map(_sTask *) (0x71006ae0ec), which holds the four tests as `ldrsb` and `cmp #0; csel`, and one by player_move for the last test of the map; the helper matches as written, so the
// repeated test is not written out (P4).
static bool unknown029(const u8 *rows, int x, int y) { return (rows[(x >> 4) + (y & ~0xf)] & 0x80) != 0; }

// The position words of the task are read through a copy (P2: the game loads the words at 0x34 and 0x38 first and those at 0x2c and 0x30 second, `ldp w13, w12, [x1, #52]` then
// `ldp w10, w11, [x1, #44]`, 0x71006ae0f8 and 0x71006ae0fc; reading x, y and the offsets of the box directly from the task gives the pairs in the other order, 54 instructions
// against 54 with other registers). The size of the box is read from the task: reading it from the copy does not match either. The result is a u8: an `int` result folds the first
// test into `or result, zext(tile < 0)` (InstCombine FoldSelectIntoOp), the game keeps the `csel` of all four tests.
u8 minigame::check_map(_sTask *task) {
  if (unknown1260 == nullptr) {
    return 0;
  }
  int scroll = unknown18->unknown26;
  _sTask c = *task;
  int top = (scroll & 0xf) + (c.unknown30 >> 8) + c.unknown38;
  int left = c.unknown36 + (c.unknown2c >> 8);
  if (left < 0) {
    left = 0;
  } else if (left > 0x200) {
    return 0;
  }
  int right = left + task->unknown3a - 1;
  int bottom = top + task->unknown3b - 1;
  u8 *rows = unknown1260->unknown10 + (scroll >> 4) * 0x10;
  u8 result = 0;
  if (top < 0) {
    result = 3;
  }
  if (unknown029(rows, left, top)) {
    result |= 1;
  }
  if (unknown029(rows, right, top)) {
    result |= 2;
  }
  if (unknown029(rows, left, bottom)) {
    result |= 4;
  }
  if (unknown029(rows, right, bottom)) {
    result |= 8;
  }
  return result;
}

// check_dmg_map_obj (0x71006ae1c4, 88 instructions) and check_atk_obj (0x71006ae324, 84 instructions) walk the task list with mytask::enum_next and run the same four box tests, and
// match with the same forms (measured with scratch compiles of the unit, diffed against the game):
// - The box of the task is read through get_coli_xy / get_pc_atk_xy before the first enum_next call and right and bottom are locals: the game keeps left, top, right and bottom in
//   w21..w24 across the call. A snapshot copy `_sTask c = *task` of check_dmg_map_obj gives the same four word loads but in other registers (ldp w21, w22 / w23, w24 against the game's
//   ldp w21, w23 / w22, w24).
// - The walk is a `for` loop: with the guarded do-while the last `mov x0, x8` of check_dmg_map_obj lands after the final strb, and in check_atk_obj the final `and` lands before the `tst`.
// - The tests are written right > otherLeft, otherBottom > top, otherRight > left, bottom > otherTop; the game branches on them in the order right > otherLeft, otherBottom > top,
//   bottom > otherTop, otherRight > left (`cmp w13, w23` before `cmp w25, w12` in check_atk_obj). With -print-after-all SimplifyCFG merges the last two tests into one `and` and
//   Reassociate puts the test against `bottom` first (inferred: its operands have the lower rank), so the game's order is reached from the source order above. Written in the game's
//   order the merged pair is otherBottom > top and bottom > otherTop, which Reassociate swaps the same way (the two tests come out in the other order).
_sTask *minigame::check_dmg_map_obj(_sTask *task, u8 &mapHit) {
  if (task->unknown34 != 0 && task->unknown35 == 0) {
    u8 hit = check_map(task);
    if (hit != 0) {
      mapHit = hit;
      task->unknown35 |= 0x80;
      return nullptr;
    }
    int left;
    int top;
    get_coli_xy(left, top, task);
    int right = left + task->unknown3a;
    int bottom = top + task->unknown3b;
    for (_sTask *other = static_cast<_sTask *>(m_mytask->enum_next(nullptr)); other != nullptr; other = static_cast<_sTask *>(m_mytask->enum_next(other))) {
      if (other != task && other->unknown35 == 0) {
        u8 common = task->unknown34 & other->unknown34;
        if (common != 0) {
          int otherLeft;
          int otherTop;
          get_coli_xy(otherLeft, otherTop, other);
          if (right > otherLeft && otherTop + other->unknown3b > top && otherLeft + other->unknown3a > left && bottom > otherTop) {
            task->unknown35 |= common;
            other->unknown35 |= common;
            return other;
          }
        }
      }
    }
  }
  return nullptr;
}

// The mask of what the attack hits is `mask |= 4` on 2: the game computes it in the entry block (`ldr x8, [x20, #0x3528]; ldrb w8, [x8, #0x4d]; cmp; orr; orr; csel w21`, before the
// `ldrh w8, [x19, #0x34]` test), written `mask = 6` InstCombine sinks the select into the loop preheader (`csel` right before `cmp x8, x19`). The half width `attacker->unknown5c` is read
// three times (test, get_pc_atk_xy, right) and the game loads it once (`ldrb w24, [x19, #0x5c]`, held across the call), the other fields of the box come from one load of the word
// at 0x58 (`ldr x23, [x19, #0x58]`), which GVN does for these reads. Forms and order of the box tests as in check_dmg_map_obj (see its comment).
_sTask *minigame::check_atk_obj(_sTask *task) {
  u8 mask = 2;
  if (static_cast<unknown022 *>(m_sTask)->unknown4d != 0) {
    mask |= 4;
  }
  unknown022 *attacker = static_cast<unknown022 *>(task);
  if (attacker->unknown34 != 0 && attacker->unknown35 == 0 && attacker->unknown5c != 0) {
    int left;
    int top;
    get_pc_atk_xy(left, top, task);
    int right = left + attacker->unknown5c * 2;
    int bottom = top + attacker->unknown5d * 2;
    for (_sTask *other = static_cast<_sTask *>(m_mytask->enum_next(nullptr)); other != nullptr; other = static_cast<_sTask *>(m_mytask->enum_next(other))) {
      if (other != task && other->unknown35 == 0) {
        u8 otherMask = other->unknown34;
        if ((otherMask & mask) != 0) {
          int otherLeft;
          int otherTop;
          get_coli_xy(otherLeft, otherTop, other);
          if (right > otherLeft && otherTop + other->unknown3b > top && otherLeft + other->unknown3a > left && bottom > otherTop) {
            other->unknown35 = task->unknown34 & otherMask;
            if ((otherMask & 2) != 0) {
              return other;
            }
            return nullptr;
          }
        }
      }
    }
  }
  return nullptr;
}

void minigame::get_pc_vxvy(int x, int y, int speed, int &vx, int &vy) {
  int px;
  int py;
  get_pc_pos(px, py);
  int dx = x - px;
  int dy = y - py;
  f32 fx = dx * 0.00390625f;
  f32 fy = dy * 0.00390625f;
  f32 dist = sqrtf(fx * fx + fy * fy);
  if (dist < 1.0f) {
    vx = 0;
    vy = 0;
  } else {
    vx = fx * (-static_cast<f32>(speed) / dist);
    vy = (-static_cast<f32>(speed) / dist) * fy;
  }
}

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build
// gives a symbol. The game reads the time (get_time, 0x71006ae82c) as one 64-bit word and extracts the fields with `ubfx x`; reading the fields of the TimeInfo that
// getTime filled loads two 32-bit words (`ldp w8, w9`, 22 instructions), and so does a plain copy `TimeInfo copy = info`. Passing the TimeInfo by value is the form
// that gives the 64-bit word; the sum written as seconds, minutes, hours, days gives the game's registers (the other 23 orders of the terms do not).
static int toSeconds(ml::TimeInfo time) { return time.unknown01_6 + time.unknown02_4 * 60 + time.unknown03_2 * 3600 + time.unknown04_5 * 86400; }

int minigame::get_time() {
  ml::TimeInfo info;
  ml::TimeUtil::getTime(info);
  return toSeconds(info);
}

u8 minigame::get_tbox_type(int index) { return unknown1688[index].m_tbox_type; }

int minigame::add_result(u16 id, u32 &score) {
  if (!id) {
    return 0;
  }
  if (id >= 0xee49 && id <= 0xee4d) {
    score += unknown32d8[id - 0xee49];
    return 2;
  }
  int kind = 3;
  if (id >= 0xafc9 && id < 0xb000) {
    kind = 12;
  }
  for (int i = 0; i < 0x80; i++) {
    if (unknown3de0[i].unknown00 == id) {
      unknown3de0[i].unknown02++;
      return kind;
    }
    if (unknown3de0[i].unknown02 == 0) {
      unknown3de0[i].unknown00 = id;
      unknown3de0[i].unknown02 = 1;
      return kind;
    }
  }
  return kind;
}

void minigame::tora_cell_anime_setup(int index) {
  unknown3d78.unknown00 = static_cast<u8 *>(m_archive.get_res(index + 8));
  unknown3d78.unknown08 = 0;
  unknown3d78.unknown09 = 1;
  csvb::CCsvbData csv;
  csv.Load(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), m_archive.get_res(7), m_archive.get_res_sz(7));
  unknown3d78.unknown0a[0] = csv.GetInt(index, 0);
  unknown3d78.unknown0a[1] = csv.GetInt(index, 1);
}

// Inferred role: reads a 32-bit big-endian word from four bytes (the tile memory is stored as big-endian words); original name unknown. Used by tora_cell_anime, phase_select, phase_game and
// decode_4bpp_sprt(u32, const u8 *) (four users, ruling 8: the helper form matches in all of them, measured, so the expression is not written out four times).
static inline u32 unknown078(const u8 *bytes) { return bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3]; }

// The tile memory is bytes, and the game addresses its columns with a byte pointer next to a separate counter (`cmp w8, #0x100; b.ne`): a single index or a u32
// pointer gives `cmp x8; b.lo`, or different register order in the first row. The store of the word is a memcpy of the big-endian word (0x71006aea20).
void minigame::tora_cell_anime() {
  if (--unknown3d78.unknown09 == 0) {
    unknown3d78.unknown08 = ~unknown3d78.unknown08 & 1;
    unknown3d78.unknown09 = unknown3d78.unknown0a[unknown3d78.unknown08];
    const u8 *src = unknown3d78.unknown00 + unknown3d78.unknown08 * 0x800 + 0x40;
    u8 *dst = unknown18->unknown100 + 0x2800;
    for (int column = 0; column != 0x40; column++, dst += 4) {
      for (int row = 0; row < 8; row++) {
        u32 word = unknown078(src);
        memcpy(dst + row * 0x100, &word, sizeof(word));
        src += 4;
      }
    }
  }
}

int minigame::check_rank() {
  if (unknown33e0 < 0 || unknown33e0 > 4) {
    return 0;
  }
  return unknown3410 >= unknown3fe0.unknown08[unknown33e0].unknown00;
}

void minigame::sprite_reset() {
  unknown40b0 = 0;
  memset(unknown18->unknown21100, 0, sizeof(unknown18->unknown21100));
}

unknown003 *minigame::sprite_get() {
  if (unknown40b0 >= 0x40) {
    return nullptr;
  }
  return unknown18->unknown21100 + unknown40b0++;
}

u8 *minigame::get_res_pal(int index) {
  unknown002 *res = static_cast<unknown002 *>(m_archive.get_res(index));
  if (res->unknown02 == 0) {
    return nullptr;
  }
  return res->unknown10;
}

_sTask *minigame::task_entry() {
  _sTask *task = static_cast<_sTask *>(m_mytask->entry());
  if (task == nullptr) {
    for (void *it = m_mytask->enum_next(nullptr); it != nullptr; it = m_mytask->enum_next(it)) {
      if (static_cast<_sTask *>(it)->unknown10 == effect_move) {
        m_mytask->remove(it);
        return static_cast<_sTask *>(m_mytask->entry());
      }
    }
    return nullptr;
  }
  return task;
}

void minigame::req_reload() {
  fw::SoundManager::get()->stopBgmAll();
  fw::SoundManager::get()->stopSeAll();
  unknown64c = 8;
  unknown650 = 0x10;
}

void minigame::playse(int id) {
  if (id != 0 && unknown28 != nullptr) {
    fw::SoundManager::get()->playSe(id, unknown28->getSoundPack(), 1.0f, static_cast<fw::SoundCategory>(3));
  }
}

void minigame::reset_save() {
  memset(&unknown3fe0, 0, sizeof(unknown3fe0));
  unknown3fe0.unknown00 = 1;
  unknown3fe0.unknown08[0].unknown00 = 3000;
  unknown3fe0.unknown08[0].unknown04[0] = 'M';
  unknown3fe0.unknown08[0].unknown04[1] = 'O';
  unknown3fe0.unknown08[0].unknown04[2] = 'N';
  unknown3fe0.unknown08[0].unknown04[3] = '\0';
  unknown3fe0.unknown08[1].unknown00 = 3000;
  unknown3fe0.unknown08[1].unknown04[0] = 'Y';
  unknown3fe0.unknown08[1].unknown04[1] = 'J';
  unknown3fe0.unknown08[1].unknown04[2] = 'M';
  unknown3fe0.unknown08[1].unknown04[3] = '\0';
  unknown3fe0.unknown08[2].unknown00 = 3000;
  unknown3fe0.unknown08[2].unknown04[0] = 'T';
  unknown3fe0.unknown08[2].unknown04[1] = 'N';
  unknown3fe0.unknown08[2].unknown04[2] = 'Y';
  unknown3fe0.unknown08[2].unknown04[3] = '\0';
  unknown3fe0.unknown08[3].unknown00 = 3000;
  unknown3fe0.unknown08[3].unknown04[0] = 'K';
  unknown3fe0.unknown08[3].unknown04[1] = 'W';
  unknown3fe0.unknown08[3].unknown04[2] = 'N';
  unknown3fe0.unknown08[3].unknown04[3] = '\0';
  unknown3fe0.unknown08[4].unknown00 = 3000;
  unknown3fe0.unknown08[4].unknown04[0] = 'H';
  unknown3fe0.unknown08[4].unknown04[1] = 'A';
  unknown3fe0.unknown08[4].unknown04[2] = 'G';
  unknown3fe0.unknown08[4].unknown04[3] = '\0';
}

u32 minigame::get_pc_dist(int x, int y) {
  int dx;
  int dy;
  get_pc_dxdy(x, y, dx, dy);
  f32 fx = dx * 0.00390625f;
  f32 fy = dy * 0.00390625f;
  return sqrtf(fx * fx + fy * fy);
}

void minigame::draw_text(u16 *dst, u16 base, const char *text) {
  while (*text != 0) {
    *dst++ = base + static_cast<u8>(*text++);
  }
}

// Writes the digits of value, most significant first, into the text screen (the last digit at x + digits - 1). The loop stops at the end of the screen
// (0x71006adf3c); P2: `last` and `cell` place the address computations in the game's order (the start cell, then the last cell of the screen, then the last digit's cell): without
// `last` the function has 40 instructions against the game's 36, without `cell` 36 with other registers.
void minigame::debug_hex(int x, int y, u32 value, int digits) {
  u16 *cell = unknown18->unknown25500 + ((y & 0x1f) << 6) + (x & 0x3f);
  u16 *last = unknown18->unknown25500 + 0x7ff;
  u16 *dst = cell + (digits - 1);
  for (int i = 0; i < digits && dst <= last; i++) {
    *dst = (value & 0xf) + 1;
    value >>= 4;
    dst--;
  }
}

void minigame::debug_text(int x, int y, const char *text) {
  u16 *dst = unknown18->unknown25500 + ((y & 0x1f) << 6) + (x & 0x3f);
  while (*text != 0) {
    *dst++ = static_cast<u8>(*text++);
  }
}

void minigame::vram_fill(u16 *dst, int width, int height, u16 value) {
  for (int y = 0; y < height; y++) {
    u16 *row = dst;
    for (int x = 0; x < width; x++) {
      *row++ = value;
    }
    dst += 0x40;
  }
}

void minigame::clip_screen(int &x, int &y, int &width, int &height, int &dstX, int &dstY) {
  dstX = x;
  if (x < 0) {
    x = -x;
    dstX = 0;
  } else {
    if (x + width > 0x140) {
      width = 0x140 - x;
    }
    x = 0;
  }
  dstY = y;
  if (y >= 0) {
    if (y + height > 0xf0) {
      height = 0xf0 - y;
    }
    y = 0;
  } else {
    y = -y;
    dstY = 0;
  }
}

// Inferred role: tests that a box of the given size at this position overlaps the screen along one axis; original name unknown. Used for x and y by draw_mesh_box.
// Written without the helper (the six tests in one && chain, nested ifs, `||` early returns, `x + width <= 0`) SimplifyCFG folds the tests into two `and` chains and Reassociate sorts them by the rank
// of the arguments (x, y, width, height), giving `cmp w3,#0x13f` first and the last guard column before row; the game tests width, height, then x against 0x140 and -width, then y (0x71006ad9dc),
// which is the order of the calls of this helper (each call is a block too costly for SimplifyCFG to fold into the previous one) and of the loop guards without an explicit `row < height && column <
// width`.
static bool unknown028(int position, int size, int limit) { return position < limit && position > -size; }

void minigame::draw_mesh_box(u8 *dst, int stride, int x, int y, int width, int height, const _sPalette *palette) {
  if (width != 0 && height != 0 && unknown028(x, width, 0x140) && unknown028(y, height, 0xf0)) {
    int column;
    int offset;
    if (x < 0) {
      offset = 0;
      column = -x;
    } else {
      column = 0;
      if (x + width > 0x140) {
        width = 0x140 - x;
      }
      offset = x * 3;
    }
    int row;
    if (y < 0) {
      row = -y;
      y = 0;
    } else {
      row = 0;
      if (y + height > 0xf0) {
        height = 0xf0 - y;
      }
    }
    u8 *line = dst + offset + y * stride;
    for (; row < height; row++) {
      u8 *pixel = line;
      for (int i = column; i < width; i++) {
        if (((row + i) & 1) != 0) {
          pixel[0] = palette->unknown00;
          pixel[1] = palette->unknown01;
          pixel[2] = palette->unknown02;
        }
        pixel += 3;
      }
      line += stride;
    }
  }
}

void minigame::getResult(_sResult *result) {
  u32 best = unknown3fe0.unknown08[0].unknown00;
  for (int i = 1; i < 5; i++) {
    if (best < unknown3fe0.unknown08[i].unknown00) {
      best = unknown3fe0.unknown08[i].unknown00;
    }
  }
  result->unknown00 = best;
  unknown010 *entry = result->unknown04;
  if (unknown3418 != 0) {
    entry->unknown00 = 0xffff;
    entry->unknown02 = unknown3418;
    entry++;
  }
  for (int i = 0; i < 0x80; i++) {
    if (unknown3de0[i].unknown02 != 0) {
      entry->unknown00 = unknown3de0[i].unknown00;
      entry->unknown02 = unknown3de0[i].unknown02;
      entry++;
    }
  }
  entry->unknown00 = 0;
  entry->unknown02 = 0;
}

void minigame::draw_obj(int sheet, int frame, int x, int y, u8 flip, u8 palette) {
  if (unknown30[sheet].unknown08 != nullptr) {
    const unknown012 *info = &unknown30[sheet].unknown08[frame];
    unknown003 *sprite = sprite_get();
    if (sprite != nullptr) {
      sprite->unknown00 = (info->unknown00 ^ flip) & 3;
      sprite->unknown01 = palette;
      sprite->unknown04 = info->unknown06 + x + unknown18->unknown1c;
      sprite->unknown06 = info->unknown07 + y + unknown18->unknown1e;
      sprite->unknown08 = info->unknown02 + unknown30[sheet].unknown00;
      sprite->unknown0a = info->unknown04 >> 3;
      sprite->unknown0b = info->unknown05 >> 3;
    }
  }
}

// The sprite of a task: bit 0 of unknown28 mirrors x (the frame's x offset and width are subtracted from the position), bit 1 mirrors y. The sprite is
// only made when the frame is not above or below the screen (0x71006aeed0).
void minigame::draw_obj(int sheet, int frame, const _sTask *task, u8 palette) {
  if (unknown30[sheet].unknown08 != nullptr) {
    const unknown012 *info = &unknown30[sheet].unknown08[frame];
    int x = task->unknown2c >> 8;
    int y = task->unknown30 >> 8;
    if ((task->unknown28 & 1) == 0) {
      x += info->unknown06;
    } else {
      x -= info->unknown06 + info->unknown04;
    }
    if (((task->unknown28 >> 1) & 1) == 0) {
      y += info->unknown07;
    } else {
      y -= info->unknown07 + info->unknown05;
    }
    if (-info->unknown05 <= y && y < 0xf1) {
      unknown003 *sprite = sprite_get();
      if (sprite != nullptr) {
        sprite->unknown00 = (info->unknown00 ^ task->unknown28) & 3;
        sprite->unknown01 = palette;
        sprite->unknown04 = x + unknown18->unknown1c;
        sprite->unknown06 = y + unknown18->unknown1e;
        sprite->unknown08 = info->unknown02 + unknown30[sheet].unknown00;
        sprite->unknown0a = info->unknown04 >> 3;
        sprite->unknown0b = info->unknown05 >> 3;
      }
    }
  }
}

// A pointer walk over the 0x400 palette entries (_sPalette, three bytes), both pointers advanced by one entry (found by the phase_clear pass). The earlier form with a byte offset counter
// (`*(dst + offset + k)` and `src[offset + k]`, an entry counter next to the byte offset) matched the standalone function (0x71006ae474) but its inlined copies got the destination base biased by
// one (`movk w12, #257`, `sturb [x15, #-1]`, 4 differing lines per copy in phase_over); the walk gives the game's code standalone and in every inlined copy, and with indexed entries
// (`dst[i].unknown00`) 9 instructions of the standalone function differ. The game has no caller of the standalone function: every phase inlines it.
void minigame::update_palt(int level) {
  _sPalette *dst = unknown18->unknown20100;
  const _sPalette *src = unknown65c;
  for (int i = 0; i < 0x400; i++) {
    dst->unknown00 = src->unknown00 * level / 255;
    dst->unknown01 = src->unknown01 * level / 255;
    dst->unknown02 = src->unknown02 * level / 255;
    dst++;
    src++;
  }
  unknown18->unknown10 = level;
}

void minigame::playbgm(int index) {
  if (unknown1270 != 0) {
    fw::SoundManager::get()->stopBgm(unknown1270, 0.0f);
  }
  mm::mtl::FixStr<64> name;
  name.format("stream/bgm/m102%c.wav", index + 'a');
  unknown1270 = fw::SoundManager::get()->playBgm(name.c_str(), 1.0f, false, -1, static_cast<fw::SoundCategory>(0x11));
  fw::SoundManager::get()->setPitch(unknown1270, 1.0f, 0.0f);
}

void *minigame::get_dropitem() {
  if (unknown3520 != nullptr) {
    void *item = unknown3520;
    unknown3520 = nullptr;
    return item;
  }
  int even = -1;
  int odd = -1;
  for (int i = 0; i < 16; i++) {
    if (unknown3420[i].unknown00 != 0xff) {
      if ((unknown3420[i].unknown00 & 1) != 0) {
        odd = i;
      } else {
        even = i;
      }
    }
  }
  if (even < 0) {
    even = odd;
  }
  if (even < 0) {
    return nullptr;
  }
  unknown3420[even].unknown00 = 0xff;
  return unknown3420[even].unknown08;
}

u32 minigame::add_air(int amount) {
  u16 air = unknown340c;
  if (amount != 0) {
    int value = air + amount;
    if (value < 0) {
      value = 0;
    }
    if (value > unknown1278) {
      value = unknown1278;
    }
    int threshold = unknown1278 / 10;
    if (air >= threshold && value < threshold) {
      fw::SoundManager::get()->setPitch(unknown1270, 1.5f, 0.0f);
    }
    unknown340c = value;
    unknown3408 = 7;
    air = value;
  }
  return air;
}

int minigame::add_item(int item, void *param) {
  if (unknown1688[item].m_tbox_type == 2) {
    if (unknown3520 != nullptr) {
      u16 score = unknown1688[item].unknown02[0].unknown00;
      unknown3410 += score;
      unknown3409 = 0x1e;
      unknown3fe0.unknown30 += score;
      return -1;
    }
    unknown3520 = param;
    return 0;
  }
  int count = 0;
  for (int i = 0; i < 16; i++) {
    if (unknown3420[i].unknown00 == 0xff) {
      unknown3420[i].unknown00 = item;
      unknown3420[i].unknown08 = param;
      unknown3fe0.unknown48++;
      return count;
    }
    if (unknown1688[unknown3420[i].unknown00].m_tbox_type == 0) {
      count++;
    }
  }
  return -1;
}

void minigame::get_score_text(char *text, u32 score) {
  text[5] = (score % 10) | '0';
  if (score >= 10) {
    text[4] = (score / 10 % 10) | '0';
  } else {
    text[4] = ' ';
  }
  if (score >= 100) {
    text[3] = (score / 100 % 10) | '0';
  } else {
    text[3] = ' ';
  }
  if (score >= 1000) {
    text[2] = (score / 1000 % 10) | '0';
  } else {
    text[2] = ' ';
  }
  if (score >= 10000) {
    text[1] = (score / 10000 % 10) | '0';
  } else {
    text[1] = ' ';
  }
  if (score >= 100000) {
    text[0] = (score / 100000 % 10) | '0';
  } else {
    text[0] = ' ';
  }
  text[6] = '\0';
}

// Bytecode interpreter of the title screen script (0x71006a136c). Opcode 0 is a no-op, 0x10-0x3e work on the 16 byte registers
// unknown3300 (an even opcode reads its second operand from a register, an odd one is an immediate: mov 0x10/0x11, add 0x12/0x13,
// and 0x14, or 0x16, xor 0x18, shl 0x1a/0x1b, shr 0x1c/0x1d, mul 0x20, div 0x22, mod 0x24, and the jumps if equal 0x30/0x31, not equal
// 0x32/0x33, less 0x34/0x35 with a 16 bit offset into the script), 0x40-0x44 set, replace and add to the fields of a sprite and give
// it an animation, 0xfd jumps, 0xfe ends the frame keeping the instruction pointer, 0xff ends the script and clears the eight
// sprites; any other opcode ends the script. Each frame ends with the animation step of the eight sprites. The range tests
// (op <= 0x3e, op <= 0x4e) are the ones of the game (0x71006a13cc, 0x71006a1410).
// Ruling 8: the block that gives a sprite the animation at an offset of the script (none for offset 0) is written out in the opcodes 0x40, 0x42 and 0x44, as the game holds
// it (each arm ends in the jump back to the loop, with its own store of the pointer). A helper does not match, measured on title_vm (299 instructions in the game): a `static
// inline` and a `static` helper (`unknown019 &, const u8 *script, u16 offset`) give 299 instructions with other code, since the store of unknown10 of the two arms is sunk into the
// join as a phi (`mov x4, xzr` and one store; first difference at 0x71006a1578); the same with the arms swapped, with an early return and with a pointer parameter; the stores of
// unknown08 and unknown09 before the store of unknown10 give 301.
void minigame::title_vm() {
  if (unknown3318 != nullptr) {
    const u8 *script = unknown3310;
    const u8 *ip = unknown3318;
    for (;;) {
      u8 op = *ip++;
      if (op == 0) {
        continue;
      }
      if (op >= 0x10 && op <= 0x3e) {
        u8 a = *ip++;
        u8 b = *ip++;
        if ((op & 1) == 0) {
          b = unknown3300[b];
        }
        switch (op) {
        case 0x10:
        case 0x11:
          unknown3300[a] = b;
          continue;
        case 0x12:
        case 0x13:
          unknown3300[a] += b;
          continue;
        case 0x14:
          unknown3300[a] &= b;
          continue;
        case 0x16:
          unknown3300[a] |= b;
          continue;
        case 0x18:
          unknown3300[a] ^= b;
          continue;
        case 0x1a:
        case 0x1b:
          unknown3300[a] <<= b;
          continue;
        case 0x1c:
        case 0x1d:
          unknown3300[a] >>= b;
          continue;
        case 0x20:
          unknown3300[a] *= b;
          continue;
        case 0x22:
          unknown3300[a] /= b;
          continue;
        case 0x24:
          unknown3300[a] %= b;
          continue;
        case 0x30:
        case 0x31: {
          u8 low = *ip++;
          u8 high = *ip++;
          if (unknown3300[a] == b) {
            ip = unknown3318 = script + (low | high << 8);
          }
          continue;
        }
        case 0x32:
        case 0x33: {
          u8 low = *ip++;
          u8 high = *ip++;
          if (unknown3300[a] != b) {
            ip = unknown3318 = script + (low | high << 8);
          }
          continue;
        }
        case 0x34:
        case 0x35: {
          u8 low = *ip++;
          u8 high = *ip++;
          if (unknown3300[a] < b) {
            ip = unknown3318 = script + (low | high << 8);
          }
          continue;
        }
        default:
          break;
        }
      } else if (op >= 0x40 && op <= 0x4e) {
        u8 a = *ip++;
        unknown019 &sprite = unknown3320[a];
        switch (op) {
        case 0x40: {
          sprite.unknown00 = ip[0];
          sprite.unknown01 = ip[1];
          sprite.unknown02 = ip[2] << 8;
          sprite.unknown04 = ip[3] << 8;
          sprite.unknown06 = ip[4];
          sprite.unknown07 = ip[5];
          u16 offset = ip[6] | ip[7] << 8;
          if (offset == 0) {
            sprite.unknown10 = nullptr;
          } else {
            sprite.unknown10 = script + offset;
            sprite.unknown08 = 0;
            sprite.unknown09 = 0;
          }
          ip += 8;
          continue;
        }
        case 0x41:
          sprite.unknown00 = 0;
          continue;
        case 0x42: {
          u8 flags = *ip++;
          if (flags & 1) {
            sprite.unknown00 = *ip++;
          }
          if (flags & 2) {
            sprite.unknown01 = *ip++;
          }
          if (flags & 4) {
            sprite.unknown02 = *ip++ << 8;
          }
          if (flags & 8) {
            sprite.unknown04 = *ip++ << 8;
          }
          if (flags & 0x10) {
            sprite.unknown06 = *ip++;
          }
          if (flags & 0x20) {
            sprite.unknown07 = *ip++;
          }
          if (flags & 0x40) {
            u16 offset = ip[0] | ip[1] << 8;
            ip += 2;
            if (offset == 0) {
              sprite.unknown10 = nullptr;
            } else {
              sprite.unknown10 = script + offset;
              sprite.unknown08 = 0;
              sprite.unknown09 = 0;
            }
          }
          continue;
        }
        case 0x43: {
          u8 flags = *ip++;
          if (flags & 1) {
            sprite.unknown00 += *ip++;
          }
          if (flags & 2) {
            sprite.unknown01 += *ip++;
          }
          if (flags & 4) {
            sprite.unknown02 += static_cast<s8>(*ip++) * 0x40;
          }
          if (flags & 8) {
            sprite.unknown04 += static_cast<s8>(*ip++) * 0x40;
          }
          if (flags & 0x10) {
            sprite.unknown06 += *ip++;
          }
          if (flags & 0x20) {
            sprite.unknown07 += *ip++;
          }
          continue;
        }
        case 0x44: {
          u16 offset = ip[0] | ip[1] << 8;
          ip += 2;
          if (offset == 0) {
            sprite.unknown10 = nullptr;
          } else {
            sprite.unknown10 = script + offset;
            sprite.unknown08 = 0;
            sprite.unknown09 = 0;
          }
          continue;
        }
        default:
          break;
        }
      } else if (op >= 0xf0) {
        if (op == 0xfd) {
          ip = unknown3318 = script + (ip[0] | ip[1] << 8);
          continue;
        }
        if (op == 0xfe) {
          unknown3318 = ip;
          break;
        }
        if (op == 0xff) {
          unknown3318 = nullptr;
          for (int i = 0; i < 8; i++) {
            unknown3320[i].unknown00 = 0;
          }
          break;
        }
      }
      unknown3318 = nullptr;
      break;
    }
  }
  for (int i = 0; i < 8; i++) {
    unknown019 &sprite = unknown3320[i];
    if (sprite.unknown00 != 0 && sprite.unknown10 != nullptr) {
      if (sprite.unknown08 == 0) {
        const u8 *anim = sprite.unknown10;
        u8 offset = sprite.unknown09;
        sprite.unknown08 = anim[offset] - 1;
        sprite.unknown01 = anim[offset + 1];
        u8 next = offset + 2;
        sprite.unknown09 = anim[next] == 0 ? 0 : next;
      } else {
        sprite.unknown08--;
      }
    }
  }
}

// The memset at 0x71006a18c8 clears 0x3988 bytes from 0x658, the members up to the save data at 0x3fe0. The game reads the sheets with
// Bdat::getVal and scales the speed columns (percent) to 1/256 pixel by (value << 8) / 100. The save data check at 0x71006a2148 reads
// its first three bytes as one 24-bit word (ldr w, and #0xffffff), which is how clang merges the three byte tests written here, and
// reset_save is inlined in the branch that replaces invalid data.
void minigame::initialize() {
  unknown08 = 0;
  unknown0c = ml::mtRand();
  unknown648 = 0;
  memset(&unknown658, 0, offsetof(minigame, unknown3fe0) - offsetof(minigame, unknown658));
  m_archive.unknown00 = nullptr;
  unknown28 = nullptr;
  if (unknown18 == nullptr) {
    unknown18 = static_cast<unknown004 *>(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->allocate(sizeof(unknown004), 0x40));
  }
  memset(unknown18, 0, sizeof(unknown004));
  sprite_reset();
  if (m_mytask == nullptr) {
    // __LINE__ must be 190 as in the original file: the game passes 0xbe to operator new (0x71006a1948).
#line 190
    m_mytask = new (gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), 16, __FILE__, __LINE__) mytask(200, 256);
  } else {
    m_mytask->reset();
  }
  u8 *pc = fw::BdatManager::getFp("MIN_TT_PC");
  unknown1278 = Bdat::getVal(pc, "Hp", 0).valueU16;
  unknown127a = Bdat::getVal(pc, "HitW", 0).valueU8;
  unknown127b = Bdat::getVal(pc, "HitH", 0).valueU8;
  unknown127c = Bdat::getVal(pc, "AtkW", 0).valueU8;
  unknown127d = Bdat::getVal(pc, "AtkH", 0).valueU8;
  unknown127e = (Bdat::getVal(pc, "SpdU", 0).valueU16 << 8) / 100;
  unknown1280 = (Bdat::getVal(pc, "SpdLR", 0).valueU16 << 8) / 100;
  unknown1282 = (Bdat::getVal(pc, "SpdD", 0).valueU16 << 8) / 100;
  u8 *enemy = fw::BdatManager::getFp("MIN_TT_Enemy");
  for (int i = 0; i < Bdat::getIdCount(enemy); i++) {
    unknown1288[i].unknown00 = Bdat::getVal(enemy, "Name", i).valueString;
    unknown1288[i].unknown08 = Bdat::getVal(enemy, "MoveType", i).valueU8;
    unknown1288[i].unknown09 = Bdat::getVal(enemy, "HitType", i).valueU8;
    unknown1288[i].unknown0a = Bdat::getVal(enemy, "HitW", i).valueU8;
    unknown1288[i].unknown0b = Bdat::getVal(enemy, "HitH", i).valueU8;
    unknown1288[i].unknown0c = Bdat::getVal(enemy, "Atk", i).valueU8;
    unknown1288[i].unknown0e = (Bdat::getVal(enemy, "Speed", i).valueU16 << 8) / 100;
    unknown1288[i].unknown10 = Bdat::getVal(enemy, "Range", i).valueU16;
    unknown1288[i].unknown12 = Bdat::getVal(enemy, "Search", i).valueU16;
    unknown1288[i].unknown14 = (Bdat::getVal(enemy, "ActSpd", i).valueU16 << 8) / 100;
    unknown1288[i].unknown16 = Bdat::getVal(enemy, "Hp", i).valueU8;
    unknown1288[i].unknown17 = Bdat::getVal(enemy, "BackFrm", i).valueU8;
    unknown1288[i].unknown18 = (Bdat::getVal(enemy, "BackSpd", i).valueU16 << 8) / 100;
    unknown1288[i].unknown1a = Bdat::getVal(enemy, "Score", i).valueU16;
    unknown1288[i].unknown1c = Bdat::getVal(enemy, "ResID", i).valueU8;
  }
  u8 *tbox = fw::BdatManager::getFp("MIN_TT_Tbox");
  for (int i = 0; i < Bdat::getIdCount(tbox); i++) {
    unknown1688[i].m_tbox_type = Bdat::getVal(tbox, "Type", i).valueU8;
    for (int j = 0; j < 10; j++) {
      char name[16];
      char condition[16];
      sprintf(name, "tdef%d", j + 1);
      sprintf(condition, "cond%d", j + 1);
      unknown1688[i].unknown02[j].unknown00 = Bdat::getVal(tbox, name, i).valueU16;
      unknown1688[i].unknown02[j].unknown02 = Bdat::getVal(tbox, condition, i).valueU16;
    }
  }
  u8 *tdef = fw::BdatManager::getFp("MIN_TT_Tdef");
  for (int i = 1; i <= Bdat::getIdCount(tdef); i++) {
    for (int j = 0; j < 12; j++) {
      char name[16];
      char condition[16];
      sprintf(name, "item%d", j + 1);
      sprintf(condition, "rate%d", j + 1);
      unknown1928[i].unknown00[j].unknown00 = Bdat::getVal(tdef, name, i).valueU16;
      unknown1928[i].unknown00[j].unknown02 = Bdat::getVal(tdef, condition, i).valueU8;
    }
  }
  u8 *crystal = fw::BdatManager::getFp("MIN_TT_Crystal");
  for (int i = 0; i < Bdat::getIdCount(crystal); i++) {
    unknown3158[i].unknown00 = Bdat::getVal(crystal, "Score", i).valueU16;
    unknown3158[i].unknown08 = Bdat::getVal(crystal, "Res", i).valueString;
  }
  u8 *stage = fw::BdatManager::getFp("MIN_TT_Stage");
  for (int i = 0; i < Bdat::getIdCount(stage); i++) {
    unknown3198[i].unknown00 = (Bdat::getVal(stage, "SpdD", i).valueU16 << 8) / 100;
    unknown3198[i].unknown02 = (Bdat::getVal(stage, "SpdU", i).valueU16 << 8) / 100;
    unknown3198[i].unknown04 = (Bdat::getVal(stage, "AccU", i).valueU16 << 10) / 1000;
    unknown3198[i].unknown06 = (Bdat::getVal(stage, "MaxU", i).valueU16 << 8) / 100;
    unknown3198[i].unknown08 = Bdat::getVal(stage, "Scroll", i).valueU16;
    unknown3198[i].unknown0a = Bdat::getVal(stage, "Bonus", i).valueU16;
    unknown3198[i].unknown0c = Bdat::getVal(stage, "StarRate", i).valueU16;
    unknown3198[i].unknown0e = Bdat::getVal(stage, "BotRate", i).valueU16;
    unknown3198[i].unknown10 = Bdat::getVal(stage, "BotVal", i).valueU8;
    unknown3198[i].unknown12 = Bdat::getVal(stage, "BonusTime", i).valueU16;
    unknown3198[i].unknown14 = Bdat::getVal(stage, "UniRate", i).valueU16;
    unknown3198[i].unknown16 = Bdat::getVal(stage, "EthRate", i).valueU8;
    unknown3198[i].unknown17 = Bdat::getVal(stage, "BonusEntry", i).valueU8;
    unknown3198[i].unknown18 = Bdat::getVal(stage, "Condition", i).valueU16;
    unknown3198[i].unknown20 = Bdat::getVal(stage, "Res", i).valueString;
  }
  u8 *ether = fw::BdatManager::getFp("ITM_EtherCrystal");
  for (int i = 0; i < Bdat::getIdCount(ether); i++) {
    unknown32d8[i] = Bdat::getVal(ether, "Score", i + 0xee49).valueU16;
  }
  u8 *balance = fw::BdatManager::getFp("BTL_SystemBalance");
  unknown32e8 = Bdat::getVal(balance, "Param", 0x8b).valueU16;
  unknown32ea = Bdat::getVal(balance, "Param", 0x8c).valueU16;
  unknown32ec = Bdat::getVal(balance, "Param", 0x8d).valueU16;
  unknown32ee = Bdat::getVal(balance, "Param", 0x8e).valueU16;
  memcpy(&unknown3fe0, gf::GfDataManager::getDataGame()->unknown10ad74.begin(), sizeof(unknown3fe0));
  if (unknown3fe0.unknown00 != 1 || unknown3fe0.unknown01 != 0 || unknown3fe0.unknown02 != 0) {
    reset_save();
  }
  unknown64c = 0;
  unknown650 = 0;
}

// The game copies the 0xd0 bytes of save data into the 0x100 byte block of the game data and clears the last 0x30 bytes with six
// 8-byte stores (0x71006a23f4-0x71006a2440): the memset of the whole block written first is shortened by dead store elimination.
void minigame::finalize() {
  fw::SoundManager::get()->stopBgmAll();
  fw::SoundManager::get()->stopSeAll();
  gf::SDataGame *dataGame = gf::GfDataManager::getDataGame();
  memset(dataGame->unknown10ad74.begin(), 0, dataGame->unknown10ad74.size());
  memcpy(dataGame->unknown10ad74.begin(), &unknown3fe0, sizeof(unknown3fe0));
  if (m_mytask != nullptr) {
    delete m_mytask;
    m_mytask = nullptr;
  }
  if (unknown18 != nullptr) {
    gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->deallocate(unknown18);
    unknown18 = nullptr;
  }
}

// Inferred role: direction bits (bits 0 to 3, which update_pad moves to pad bits 24 to 27) of the left stick, indexed by the sign of
// x (1), the sign of y (2), |x| > |y| (4) and ratio > tan(22.5 degrees) (8); original name unknown. Game rodata 0x7100f75300.
static const u8 unknown050[16] = {1, 1, 4, 4, 2, 8, 2, 8, 3, 9, 6, 12, 3, 9, 6, 12};

// Converts the left stick into the four direction bits 24 to 27 of the pad words (0x71006a3188): the stick must be longer than
// fw::PadManager::ANALOG_TRIGGER_THRESHOLD, the octant comes from the signs, the larger axis and the ratio of the axes against
// tan(22.5 degrees), and the table gives the bits of the octant (two bits for a diagonal).
void minigame::update_pad() {
  u32 prev = unknown10;
  u32 hold = static_cast<u16>(gf::GfGamePad::getPadPlayer()->unknown00);
  f32 x = gf::GfGamePad::getPadPlayer()->unknown1c;
  f32 y = gf::GfGamePad::getPadPlayer()->unknown20;
  if (fabsf(x * x + y * y) > fw::PadManager::ANALOG_TRIGGER_THRESHOLD) {
    f32 ax = fabsf(x);
    f32 ay = fabsf(y);
    u8 index = x < 0.0f;
    if (y < 0.0f) {
      index |= 2;
    }
    f32 ratio;
    if (ax > ay) {
      index |= 4;
      ratio = ay / ax;
    } else {
      ratio = ax / ay;
    }
    if (ratio > 0.41421357f) {
      index += 8;
    }
    u8 bits = unknown050[index];
    hold = hold | (bits & 1) << 24 | (bits >> 1 & 1) << 25 | (bits >> 2 & 1) << 26 | (bits >> 3 & 1) << 27;
  }
  unknown10 = hold;
  unknown14 = hold & ~prev;
}

// Inferred role: palette of the game over and name entry screens, 16 entries of 3 bytes; original name unknown. Game rodata 0x7100f758b4.
static const u8 unknown070[16][3] = {{0x00, 0x00, 0x00},
                                     {0x00, 0x00, 0x00},
                                     {0xff, 0xff, 0xff},
                                     {0x80, 0x00, 0x80},
                                     {0x00, 0x80, 0x00},
                                     {0x00, 0x80, 0x80},
                                     {0x80, 0x80, 0x00},
                                     {0x80, 0x80, 0x80},
                                     {0xc0, 0xc0, 0xc0},
                                     {0x00, 0x00, 0xff},
                                     {0xff, 0x00, 0x00},
                                     {0xff, 0x00, 0xff},
                                     {0x00, 0xff, 0x00},
                                     {0x00, 0xff, 0xff},
                                     {0xff, 0xff, 0x00},
                                     {0xff, 0xff, 0xff}};

// Inferred role: tiles of the five rows of the picture of the game over and name entry screens, 5 rows of 40 tiles; original name unknown. Game rodata 0x7100f758e4.
static const u8 unknown071[5][0x28] = {
    {0, 0, 0, 0, 0, 1, 1, 13, 0, 1, 13, 0, 1, 13, 1, 13, 1, 1, 1, 13, 0, 7, 14, 0, 7, 14, 7, 14, 7, 7, 7, 14, 7, 7, 14, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 2, 13, 0, 0, 2, 13, 2, 13, 2, 2, 2, 13, 2, 13, 0, 0, 8, 14, 8, 14, 8, 14, 8, 14, 8, 14, 0, 0, 8, 14, 8, 14, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 13, 3, 13, 3, 3, 3, 13, 3, 13, 3, 13, 3, 3, 13, 0, 9, 14, 9, 14, 9, 14, 9, 14, 9, 9, 14, 0, 9, 9, 14, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 0, 0, 10, 14, 10, 14, 10, 14, 10, 14, 10, 14, 0, 0, 10, 14, 10, 14, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 5, 5, 13, 5, 13, 5, 13, 5, 13, 5, 13, 5, 5, 5, 13, 0, 11, 14, 0, 0, 11, 14, 0, 11, 11, 11, 14, 11, 14, 11, 14, 0, 0, 0, 0},
};

// The screen reset that the first sub phase of every phase inlines (phase_boot 0x71006a32ac, phase_over 0x71006ac000, phase_name 0x71006ac9e8), in two functions: this one stores the layer records,
// unknown032 clears the sprite widths and the line offsets. The game has no out-of-line copy, so the definitions are `inline`: a plain one is emitted as a function that the game does not have.
// Forms measured against the 60 instructions of the game, in a scratch with the real header:
// - 0x34 and 0x35 are two byte members. Two halfword members merge into one `stur wzr, [x8, #0x32]` (the DAG merges adjacent stores of equal width); a halfword at 0x32 and two bytes give the game's
//   `strh [0x32]; strh [0x34]` (the two bytes merge into the second `strh`, never across widths). No barrier is needed between the stores.
// - the first two members are the bitmap and palette pointers, cleared by one `stp xzr, xzr` (0x71006ac018); the order of the other stores does not change the code (address order, `unknown10` first
// or last).
// - `screen` is a local for the stores of the layer records only: the game loads `unknown18` again before the sprite loop (0x71006ac044) and before the memset (0x71006ac06c).
// - the two halves are separate functions because phase_boot stores the byte at 0x38 between them (`strb [x8, #0x38]` after the last `stur`, 0x71006a32f0, before the reload of unknown18): inlined,
// the stores of unknown025 are already merged into memsets (MemCpyOpt places the memsets after the single stores of the callee), so a store written after them in the caller stays last; written in the
// same function the store lands after 0x34 whatever its position in the source (0x71006a32b8, 6 differing lines). Both halves in one function are the same code for the phases without that store.
inline void minigame::unknown025() {
  unknown004 *screen = unknown18;
  screen->unknown00 = nullptr;
  screen->unknown08 = nullptr;
  screen->unknown10 = 0;
  screen->unknown18 = 0;
  screen->unknown1a = 0;
  screen->unknown1c = 0;
  screen->unknown1e = 0;
  screen->unknown20 = 0;
  screen->unknown22 = 0;
  screen->unknown24 = 0;
  screen->unknown26 = 0;
  screen->unknown28 = 0;
  screen->unknown2a = 0;
  screen->unknown2c = 0;
  screen->unknown2e = 0;
  screen->unknown30 = 0;
  screen->unknown32 = 0;
  screen->unknown34 = 0;
  screen->unknown35 = 0;
}

// Inferred role: clears the sprite widths and the line offsets of the screen buffers, inlined after unknown025 by the first sub phase of every phase (0x71006a32f4 in phase_boot); original name
// unknown. The pointer of the screen buffers is read again (the stores of unknown025 may alias it), as in the game (`ldr x8, [x19, #0x18]` before the loop and before the memset). `inline`: see
// unknown025.
inline void minigame::unknown032() {
  unknown003 *sprite = unknown18->unknown21100;
  for (int i = 0; i < 0x40; i++) {
    sprite[i].unknown0a = 0;
  }
  memset(unknown18->unknown20d00, 0, sizeof(unknown18->unknown20d00));
}

// Inferred role: palettes (2 of 16 entries) copied to unknown65c by phase_boot; original name unknown. Game rodata 0x7100f75370 (bytes found in the executable).
static const u8 unknown055[0x60] = {0,   0,   0,   0,   0, 0,   255, 255, 255, 0,   0,   0, 0, 0,   0,   0, 0, 0,   0, 0,   0, 0,   0,   0,   0,   0,   0,   0,   0, 0,   0,   0,
                                    0,   0,   0,   0,   0, 0,   0,   0,   0,   0,   0,   0, 0, 0,   0,   0, 0, 0,   0, 0,   0, 0,   255, 255, 255, 128, 0,   128, 0, 128, 0,   0,
                                    128, 128, 128, 128, 0, 128, 128, 128, 192, 192, 192, 0, 0, 255, 255, 0, 0, 255, 0, 255, 0, 255, 0,   0,   255, 255, 255, 255, 0, 255, 255, 255};

// The phases of the start up screen (0x71006a3274, 450 instructions): case 0 resets the screen, draws the font and the first lines of text and counts the starts, the other cases wait for the
// sound pack ("ROM CHECK"), count 15 frames ("RAM CHECK"), 8 frames ("BACKUP") and 16 frames, then start the music and the next phase (unknown64c = 1).
// Every case that is done falls into the next one, every case that waits adds one to unknown65a and returns: `if (unknown65a < N) { unknown65a++; return; }`. The test of the next case is
// folded after `unknown65a = 0`, so the stores of the cases that are done (`unknown65a = 0; unknown650 = N`, in this order) reach the increment of the waiting arm of the next case, and the
// join has the game's incremented value, a phi of the loaded values and of the 0 (`mov w9, wzr; add w9, w9, #1`). That gives the game's block order (the waiting arm is the next block of the
// compare, so the ISel keeps `cmp #7` / `cmp #15` with `b.ls` / `b.hi`) and the machine tail merge of the two arms that store `unknown65a` and `unknown650` (450 instructions). With the increment
// after the switch (`unknown65a = 0; unknown650 = N; break;` and one `unknown65a++` at the end) the code is the same except `cmp #8; b.lo`, `cmp #16; b.hs` and no tail merge (451 instructions).
// The font starts after the 8 bytes of header of the first resource, `get_res(0) + 8`: the game adds the 8 to the offset before the base (`orr x11, x11, #8; add x9, x9, x11` at 0x71006a338c, the
// `or` InstCombine makes of a 64 bit `add` of a value with the low bits clear), and so does this form with the byte base of the archive. The call `static_cast<const u8 *>(m_archive.get_res(0)) + 8`
// gives two adds (`add x9, x9, w11, uxtw; add x9, x9, #8`), also with a pointer walk or an index from 8 over the call, a struct with the font at 8, and `(const u32 *)res + 2`; with the offset
// as a 32 bit value the `or` is 32 bit (`orr w11, w11, #8`).
// The offset of the header is widened to 64 bits (`static_cast<u64>`) because the game's `or` is 64 bit (`orr x11, x11, #8`); measured: without the cast the function is 450 instructions
// like the game with 1 differing line (`orr w11, w11, #0x8` against `orr x11, x11, #0x8`, 0x71006a338c), and the call form `static_cast<const u8 *>(m_archive.get_res(0)) + 8` is 450 instructions
// with 1 differing line (`add x9, x9, w11, uxtw` against the `orr x11`, 0x71006a338c). The cast is kept for that line: nothing else gives the 64 bit `or`.
// The time block is get_time() inlined (`now`): the count is stored once after the `if` (GVN-PRE of the address of unknown03), the division before the load of unknown03.
void minigame::phase_boot() {
  switch (unknown650) {
  case 0: {
    // `screen` is a local for the store of unknown38 between the two halves of the reset (see unknown025): with `unknown18->unknown38 = 0` and the local declared later the function is 451
    // instructions against the game's 450.
    unknown004 *screen = unknown18;
    unknown025();
    screen->unknown38 = 0;
    unknown032();
    memset(unknown18->unknown21500, 0, sizeof(unknown18->unknown21500));
    memset(unknown18->unknown23500, 0, sizeof(unknown18->unknown23500));
    screen = unknown18;
    const u8 *base = m_archive.unknown00;
    const u32 *table = reinterpret_cast<const u32 *>(base);
    const u8 *font = base + (static_cast<u64>((table[0] + 0x10) & ~0xfu) + 8);
    memset(screen->unknown100, 0, 0x20);
    u8 *tile = screen->unknown100 + 0x20;
    for (int i = 0; i < 0x3f8; i++) {
      u32 row = 0;
      u32 mask = *font;
      for (int j = 0; j < 8; j++) {
        row = (row << 4 | 1) + (mask >> 7);
        mask = mask << 1 & 0xff;
      }
      memcpy(tile, &row, sizeof(row));
      tile += 4;
      font++;
    }
    memcpy(unknown65c, unknown055, sizeof(unknown055));
    unknown658 = 0xff;
    update_palt(0xff);
    draw_text(&unknown18->unknown21500[0x104], 0, "TIGER! TIGER!");
    draw_text(&unknown18->unknown21500[0x204], 0, "ROM CHECK :");
    draw_text(&unknown18->unknown21500[0x284], 0, "RAM CHECK :");
    draw_text(&unknown18->unknown21500[0x304], 0, "BACKUP    :");
    // `last` places the load of unknown04 before the call of get_time (ruling 2): read after the call, in the test and in the difference, the function is 450 instructions with other code
    // (first difference at the stack store `str xzr, [sp, #8]`).
    u32 last = unknown3fe0.unknown04;
    u32 now = get_time();
    u32 count = 0;
    if (now > last) {
      count = (now - last) / 300 + unknown3fe0.unknown03;
      count = count > 3 ? 3 : count;
    }
    unknown3fe0.unknown03 = count;
    unknown3fe0.unknown04 = now;
    unknown32f0 = 1;
    unknown650 = 1;
    unknown65a = 0;
  }
  case 1:
    if (unknown28 == nullptr || unknown28->getSoundPack() == nullptr) {
      return;
    }
    draw_text(&unknown18->unknown21500[0x210], 0, "OK");
    unknown650 = 2;
  case 2:
    if (unknown65a < 0xf) {
      unknown65a++;
      char text[3];
      text[0] = "0123456789ABCDEF"[unknown65a];
      text[1] = text[0];
      text[2] = 0;
      draw_text(&unknown18->unknown21500[0x290], 0, text);
      return;
    }
    draw_text(&unknown18->unknown21500[0x290], 0, "OK");
    unknown65a = 0;
    unknown650 = 3;
  case 3:
    if (unknown65a < 8) {
      unknown65a++;
      return;
    }
    draw_text(&unknown18->unknown21500[0x310], 0, "OK");
    unknown65a = 0;
    unknown650 = 4;
  case 4:
    if (unknown65a < 0x10) {
      unknown65a++;
      return;
    }
    unknown650 = 4;
  default:
    unknown1270 = 0;
    playbgm(0);
    unknown64c = 1;
    unknown650 = 0;
  }
}

// Inferred role: tiles of the logo of the title screen, 12 rows of 40 tiles; original name unknown. Game rodata 0x7100f753d0.
static const u8 unknown060[12][40] = {
    {0, 0, 0, 0, 1, 1, 1, 6, 0, 1, 6, 0, 0, 1, 1, 1, 6, 0, 1, 1, 1, 6, 0, 1, 1, 6, 0, 0, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 6, 0, 0, 2, 6, 0, 2, 6, 0, 0, 0, 0, 2, 6, 0, 0, 0, 2, 6, 2, 6, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 6, 0, 0, 3, 6, 0, 3, 6, 3, 3, 6, 0, 3, 3, 6, 0, 0, 3, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 4, 6, 0, 0, 4, 6, 0, 4, 6, 0, 4, 6, 0, 4, 6, 0, 0, 0, 4, 6, 4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 5, 6, 0, 0, 5, 6, 0, 0, 5, 5, 6, 0, 0, 5, 5, 5, 6, 0, 5, 6, 5, 6, 0, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 12, 0, 7, 12, 0, 0, 7, 7, 7, 12, 0, 7, 7, 7, 12, 0, 7, 7, 12, 0, 0, 7, 12, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 12, 0, 0, 8, 12, 0, 8, 12, 0, 0, 0, 0, 8, 12, 0, 0, 0, 8, 12, 8, 12, 0, 8, 12, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 12, 0, 0, 9, 12, 0, 9, 12, 9, 9, 12, 0, 9, 9, 12, 0, 0, 9, 9, 12, 0, 0, 9, 12, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 12, 0, 0, 10, 12, 0, 10, 12, 0, 10, 12, 0, 10, 12, 0, 0, 0, 10, 12, 10, 12, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 12, 0, 0, 11, 12, 0, 0, 11, 11, 12, 0, 0, 11, 11, 11, 12, 0, 11, 12, 11, 12, 0, 11, 12, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// Inferred role: palette of the title screen, 16 entries of 3 bytes; original name unknown. Game rodata 0x7100f755b0.
static const u8 unknown061[] = {16, 0,  16, 0, 0, 32, 32, 0, 0, 32, 0, 32, 0, 32, 0, 0, 32, 32, 32, 32, 0, 32, 32, 32,
                                48, 48, 48, 0, 0, 64, 64, 0, 0, 64, 0, 64, 0, 64, 0, 0, 64, 64, 64, 64, 0, 64, 64, 64};

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// Role: clears the counters of the menu of the title screen (unknown32f4, unknown32f8 and unknown32fc, which phase_title stores as one byte and one word pair, the memset of 9 bytes of the IR).
// Its only user is phase_title (0x71006a397c), where the game stores them at 0x71006a4658 to 0x71006a4668 (`strb 0x32fc; str xzr, [0x32f4]`) between the clears of the sprites 1 to 7 and of the
// sprite 0. Form tried without the helper: the three stores written in phase_title give 975 instructions like the game, with 4 differing lines (first difference at 0x71006a46a4: the
// game stores 0x32fc first and the sprite 0 (0x3320) after 0x32f4, the written-out form clears the sprite 0 before 0x32fc): MemCpyOpt places the memset it builds after the single stores of the block,
// so the clears of the sprites all come before it; only a callee optimised first (the memset already made) has the game's order. `inline`: the game has no out-of-line copy (decision 41).
inline void minigame::clearMenuCounters() {
  unknown32fc = 0;
  unknown32f4 = 0;
  unknown32f8 = 0;
}

// Inferred role: clears the first layer of the screen buffers (unknown21500), decodes the sprite sheet 2 from tile 0x80 and clears the first palette entry; original name unknown. Inlined by the first
// sub phase of phase_title, phase_clear and phase_over (three users; the quality gate reports the five statements as a block shared by three functions when they are written out, a helper matches, so
// P4 keeps it; `inline`: the game has no out-of-line copy, decision 41).
inline void minigame::unknown074() {
  memset(unknown18->unknown21500, 0, sizeof(unknown18->unknown21500));
  decode_4bpp_sprt(0x80, 2);
  unknown65c[0].unknown00 = 0;
  unknown65c[0].unknown01 = 0;
  unknown65c[0].unknown02 = 0;
}

// Inferred role: one frame of the count-up of the clear screen: unknown3d89 counts down from 30 within the step unknown3d88 and the next step starts when it is zero (after step 2 the step becomes
// 100, which ends the count); original name unknown. Inlined by sub phases 3, 5, 8, 9 and 11 of phase_clear.
inline void minigame::unknown075() {
  if (unknown3d89 != 0) {
    unknown3d89--;
  } else {
    if (unknown3d88 == 2) {
      unknown3d88 = 99;
    }
    unknown3d88++;
    unknown3d89 = 30;
  }
}

// Inferred role: clears the width of the sprites that the frame did not use (from the number of sprites used on); original name unknown. Used by phase_title, phase_select and unknown076 (three
// users); the helper form matches in all of them, so the loop is not written out three times (ruling 8).
static inline void unknown079(minigame &game) {
  for (; game.unknown40b0 < 0x40; game.unknown40b0++) {
    game.unknown18->unknown21100[game.unknown40b0].unknown0a = 0;
  }
}

// Inferred role: ends the frame of a phase: resets the number of sprites used, runs the draw functions of the tasks and clears the width of the sprites that they did not use; inlined by
// phase_game, phase_over and phase_name; original name unknown. Same helper rule as unknown074 (the quality gate reports the three written-out copies).
inline void minigame::unknown076() {
  unknown40b0 = 0;
  m_mytask->executeDraw();
  unknown079(*this);
}

// Inferred role: decodes the next sprite sheet of a chain: the sheet goes to the tiles that follow the page of the end of the previous sheet (the low 16 bits of the result of its decode), the end
// of the new sheet is returned; inlined by phase_title and phase_game (ten and fifteen calls); original name unknown. The chain written out (`tile = (tile & 0xffff) + page; tile = decode...`) gives
// the same code; the add after the call (`tile = (decode_4bpp_sprt(tile, sheet) & 0xffff) + page`) is 976 instructions in phase_title against the game's 975, and a loop over a table of (page, sheet)
// pairs is not unrolled by clang 3.9 (the body holds the inlined decoder; 755 instructions against 975; only `#pragma clang loop unroll(full)` unrolls it, which is refused).
inline u32 minigame::unknown077(u32 tile, u32 page, int sheet) { return decode_4bpp_sprt((tile & 0xffff) + page, sheet); }

// Title screen (0x71006a397c). Sub phase 0 builds the screen (logo, the 11 sprite sheets chained from tile 0x101e0, palette of bank 3), 1 fades in, 2 runs the menu (START / END) and the
// script of title_vm, 3 fades out and switches to the stage select (phase 2, or the game, phase 3, when a stage is already chosen) or to phase 11.
// Forms measured against the 975 instructions of the game (scratch compiles of the unit): the logo is read with a walked pointer over the whole table (`*logo++`; indexed forms give another
// loop: 70 differing lines against 46), the direction step is `(mask) ? -1 : 0` then `if (mask) step = 1` (the else-if chain gives `csel eq` with swapped operands).
// The clear of unknown3320[0].unknown00 comes after the three stores of clearMenuCounters (a memset that MemCpyOpt builds inside the callee, placed after the single stores of the block).
void minigame::phase_title() {
  switch (unknown650) {
  case 0: {
    unknown025();
    unknown032();
    unknown18->unknown18 = 0x10;
    unknown074();
    const u8 *logo = &unknown060[0][0];
    for (int y = 0; y < 12; y++) {
      for (int x = 0; x < 40; x++) {
        unknown18->unknown21500[(y + 2) * 0x40 + x] = *logo++ + 0x80;
      }
    }
    draw_text(&unknown18->unknown21500[27 * 0x40 + 12], 0x1000, "*2017 MONOLITHSOFT");
    unknown18->unknown21500[27 * 0x40 + 12] = 0x1018;
    draw_text(&unknown18->unknown21500[29 * 0x40 + 2], 0x1000, "CREDIT");
    memset(unknown18->unknown23500, 0, sizeof(unknown18->unknown23500));
    u32 tile = decode_4bpp_sprt(0x101e0, 0x33);
    tile = unknown077(tile, 0x11000, 0x32);
    tile = unknown077(tile, 0x12000, 0x31);
    tile = unknown077(tile, 0x13000, 0x30);
    tile = unknown077(tile, 0x14000, 0x34);
    tile = unknown077(tile, 0x15000, 0x35);
    tile = unknown077(tile, 0x16000, 0x36);
    tile = unknown077(tile, 0x17000, 0x37);
    tile = unknown077(tile, 0x18000, 0x39);
    tile = unknown077(tile, 0x19000, 0x3a);
    unknown077(tile, 0x1d000, 0x3f);
    memcpy(&unknown65c[48], unknown061, sizeof(unknown061));
    unknown658 = 0;
    memset(unknown18->unknown20100, 0, sizeof(unknown18->unknown20100));
    unknown18->unknown10 = 0;
    for (int i = 1; i < 8; i++) {
      unknown3320[i].unknown00 = 0;
    }
    clearMenuCounters();
    unknown3320[0].unknown00 = 0;
    unknown33e0 = -1;
    unknown3318 = nullptr;
    unknown3310 = nullptr;
    unknown650 = 1;
    break;
  }
  case 1:
    unknown658 += 0x10;
    if (unknown658 > 0xff) {
      unknown65a = 0;
      unknown658 = 0xff;
      unknown650 = 2;
    }
    update_palt(unknown658);
    break;
  case 2:
    if (unknown3318 == nullptr) {
      archive script;
      script.unknown00 = static_cast<u8 *>(m_archive.get_res(6));
      unknown3310 = static_cast<const u8 *>(script.get_res(unknown32fc));
      unknown3318 = unknown3310;
      unknown32fc = (unknown32fc + 1) % 3;
    }
    {
      int step = (unknown14 & 0x1001000) != 0 ? -1 : 0;
      if (unknown14 & 0x4004000) {
        step = 1;
      }
      int selected = unknown65a + step;
      if (selected < 0) {
        selected = 0;
      }
      if (selected > 1) {
        selected = 1;
      }
      if (unknown3fe0.unknown38 == 0) {
        selected = 0;
      }
      if (unknown65a != selected) {
        unknown65a = selected;
        playse(10);
      }
    }
    unknown18->unknown21500[22 * 0x40 + 16] = unknown65a == 0 ? 0x103e : 0;
    draw_text(&unknown18->unknown21500[22 * 0x40 + 18], 0x1000, "START");
    if (unknown3fe0.unknown38 != 0) {
      unknown18->unknown21500[24 * 0x40 + 16] = unknown65a == 1 ? 0x103e : 0;
      draw_text(&unknown18->unknown21500[24 * 0x40 + 18], 0x1000, " END ");
    }
    if (unknown14 & 4) {
      if (unknown65a == 0 && unknown32f0 == 0) {
        playse(0xc);
      } else {
        playse(0xb);
        if (unknown65a == 0) {
          unknown32f0--;
          unknown3fe0.unknown03 = unknown32f0;
        }
        unknown650 = 3;
      }
    }
    break;
  case 3:
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      if (unknown65a == 0) {
        unknown64c = unknown33e0 < 0 ? 2 : 3;
        unknown650 = 0;
      } else {
        unknown64c = 0xb;
      }
    }
    update_palt(unknown658);
    break;
  }
  unknown18->unknown21500[29 * 0x40 + 8] = unknown32f0 < 2 ? 0 : 0x1053;
  unknown18->unknown21500[29 * 0x40 + 10] = unknown32f0 + 0x1030;
  title_vm();
  unknown40b0 = 0;
  for (int i = 0; i < 8; i++) {
    if (unknown3320[i].unknown00 != 0) {
      draw_obj(unknown3320[i].unknown00, unknown3320[i].unknown01, unknown3320[i].unknown02 >> 6, unknown3320[i].unknown04 >> 6, unknown3320[i].unknown06, unknown3320[i].unknown07);
    }
  }
  unknown079(*this);
}

// Inferred role: palette of the stage select screen, 16 entries of 3 bytes; original name unknown. Game rodata 0x7100f755e0.
static const u8 unknown062[] = {0, 0, 0, 0, 0, 0, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Stage select screen (0x71006a48b8). Sub phase 0 builds the screen (the 128 by 128 picture of resource 0x10 with its palette in bank 2, the sheets of the stage markers and of the cursor from tile
// 0x3140, the 16 by 16 tile block of the map, "STAGE SELECT" and "STAGE", the number of stages whose condition is met from the stage table, the positions of the stages from the csv of resource 0x12),
// 1 fades in, 2 moves the selection to the nearest stage in the direction pressed and waits for the button of bit 2, 3 fades out and switches to phase 3. Every call ends with the stage number, the
// markers, the cursor that moves half way to the selected stage each frame and the clearing of the width of the sprites that were not used.
// Forms measured against the 869 instructions of the game (scratch compiles of the unit):
// - the tile block counts `x` as a `u64` tested with `!=` and takes the column as `x / 0x10`: with `int`, `long` or `u32` for `x` (alone, or next to a `column` counter, or with `column` alone) LSR
//   biases the counter by -0x100 (`cbnz`, constants 0x2400 to 0x240f); a `<` test on the unsigned counter gives `b.lo`.
// - the loop of the direction search reads `unknown33e4` in its condition: with a local `count` the exit test is `cmp x10, x13; b.ne` against the game's `cmp x13, x10; b.lt`. The cases are written in
//   the order 1, 2, 4, 8 (the 23 other orders measured 24 to 68 differing lines, the place of `default` changed nothing) and `found` is declared before `best` (the order of the two `csel`).
// - the position of the current stage is read into two locals before the loop, with no test of the count before them (the guard of the rotated loop is the game's `cbz x10`): a test of the count in
//   front of the locals, or the x read in the loop, moves the loads and the `mov w, #0x33ea`.
// - the data of the csv lives in its own block: the game destroys it before the stores of the cursor position and of the sub phase, and the store of the sub phase 1 of case 0 is then the one that
//   case 2 shares (`orr w8, wzr, #3; b`); the explicit test of the row count before the loop gave a second `GetRowCount` call.
void minigame::phase_select() {
  switch (unknown650) {
  case 0: {
    unknown025();
    unknown032();
    // `palette` is a local: with `res->unknown10` as the source of the memcpy the function is 869 instructions like the game with 2 differing lines (the address of unknown65c[32],
    // `add x0, x19, #1724`, is computed elsewhere).
    const void *blob = m_archive.get_res(0x10);
    const unknown002 *res = static_cast<const unknown002 *>(blob);
    const u8 *palette = res->unknown10;
    memcpy(&unknown65c[32], palette, 0x30);
    const u8 *src = static_cast<const u8 *>(blob);
    u8 *dst = unknown18->unknown100 + 0x6000;
    for (int row = 0; row < 0x80; row++) {
      src += 0x40;
      const u8 *pixels = src;
      u8 *out = dst;
      for (int x = 0; x < 0x80; x += 8) {
        u32 word = unknown078(pixels);
        memcpy(out, &word, sizeof(word));
        pixels += 4;
        out += 0x200;
      }
      dst += 4;
    }
    memcpy(&unknown65c[16], unknown062, sizeof(unknown062));
    u32 tile = decode_4bpp_sprt(0x3140, 0x11);
    decode_4bpp_sprt((tile & 0xffff) + 0x4000, 0x33);
    // `layer` is a local: with `unknown18->unknown21500[i]` and `unknown18->unknown23500[i]` in the two loops the function is 872 instructions against the game's 869, and with
    // `vram_fill(layer, 0x40, 0x40, 0x20)` for both 909.
    u16 *layer = unknown18->unknown21500;
    for (int i = 0; i < 0x1000; i++) {
      layer[i] = 0x20;
    }
    layer = unknown18->unknown23500;
    for (int i = 0; i < 0x1000; i++) {
      layer[i] = 0x20;
    }
    for (u64 x = 0; x != 0x100; x += 0x10) {
      for (int row = 0; row < 16; row++) {
        unknown18->unknown21500[(7 + row) * 0x40 + 12 + x / 0x10] = 0x2300 + x + row;
      }
    }
    draw_text(&unknown18->unknown21500[2 * 0x40 + 14], 0x1000, "STAGE SELECT");
    draw_text(&unknown18->unknown21500[25 * 0x40 + 17], 0x1000, "STAGE");
    unknown658 = 0;
    memset(unknown18->unknown20100, 0, sizeof(unknown18->unknown20100));
    unknown18->unknown10 = 0;
    unknown33e0 = -1;
    unknown65a = 0;
    unknown33e4 = 8;
    for (int i = 1; i < 8; i++) {
      u16 condition = unknown3198[i].unknown18;
      if (condition == 0 || !gf::GfGameCond::isGameCond(condition)) {
        unknown33e4 = i;
        break;
      }
    }
    {
      csvb::CCsvbData data;
      data.Load(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), m_archive.get_res(0x12), m_archive.get_res_sz(0x12));
      for (int i = 0; i < data.GetRowCount(); i++) {
        unknown33ea[i].unknown00 = data.GetInt(i, 0);
        unknown33ea[i].unknown01 = data.GetInt(i, 1);
      }
    }
    unknown33e6 = 0x40;
    unknown33e8 = 0x90;
    unknown650 = 1;
    break;
  }
  case 1:
    unknown658 += 0x10;
    if (unknown658 > 0xff) {
      unknown65a = 0;
      unknown658 = 0xff;
      unknown650 = 2;
    }
    update_palt(unknown658);
    break;
  case 2: {
    u8 direction = (unknown14 & 0x1001000) != 0;
    if (unknown14 & 0x4004000) {
      direction = 2;
    }
    if (unknown14 & 0x8008000) {
      direction = 4;
    }
    if (unknown14 & 0x2002000) {
      direction = 8;
    }
    if (direction != 0) {
      int current = unknown65a;
      int fromX = unknown33ea[current].unknown00;
      int fromY = unknown33ea[current].unknown01;
      int found = -1;
      int best = 999;
      for (int i = 0; i < unknown33e4; i++) {
        if (current != i) {
          int distance;
          switch (direction) {
          case 1:
            distance = fromY - unknown33ea[i].unknown01;
            break;
          case 2:
            distance = unknown33ea[i].unknown01 - fromY;
            break;
          case 4:
            distance = fromX - unknown33ea[i].unknown00;
            break;
          case 8:
            distance = unknown33ea[i].unknown00 - fromX;
            break;
          default:
            distance = -1;
            break;
          }
          if (distance >= 0 && distance < best) {
            found = i;
            best = distance;
          }
        }
      }
      if (found >= 0) {
        unknown65a = found;
        playse(10);
      }
    }
    if (unknown14 & 4) {
      playse(0xb);
      unknown650 = 3;
    }
    break;
  }
  case 3:
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      unknown33e0 = unknown65a;
      unknown64c = 3;
      unknown650 = 0;
    }
    update_palt(unknown658);
    break;
  }
  unknown18->unknown21500[25 * 0x40 + 23] = unknown65a + 0x31;
  unknown40b0 = 0;
  for (int i = 0; i < unknown33e4; i++) {
    draw_obj(0x11, 0, unknown33ea[i].unknown00 + 0x60, unknown33ea[i].unknown01 + 0x38, 0, 0x80);
  }
  int dx = unknown33ea[unknown65a].unknown00 - unknown33e6;
  int dy = unknown33ea[unknown65a].unknown01 - 0x14 - unknown33e8;
  if (dx > 1 || dx < -1) {
    dx /= 2;
  }
  if (dy > 1 || dy < -1) {
    dy /= 2;
  }
  unknown33e6 += dx;
  unknown33e8 += dy;
  draw_obj(0x33, 2 | (unknown648 >> 4 & 1), unknown33e6 + 0x60, unknown33e8 + 0x38, 0, 0x90);
  unknown079(*this);
}

// Inferred role: palette that phase_game copies to the screen; original name unknown. Read from the rodata at 0x7100f75710.
static const u8 unknown084[0x90] = {0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80,
                                    0xc0, 0xc0, 0xc0, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
                                    0x00, 0x00, 0x00, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x33, 0x33, 0x33, 0x44, 0x44, 0x44, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x77, 0x77, 0x77,
                                    0x88, 0x88, 0x88, 0x99, 0x99, 0x99, 0xaa, 0xaa, 0xaa, 0xbb, 0xbb, 0xbb, 0xcc, 0xcc, 0xcc, 0xdd, 0xdd, 0xdd, 0xee, 0xee, 0xee, 0xff, 0xff, 0xff};

// Inferred role: sprite sheet (unknown30 index) of the enemy sprites by ResID column; original name unknown. Read from the rodata at 0x7100f757a0.
static const u8 unknown085[12] = {0x34, 0x35, 0x36, 0x37, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40};

// Inferred role: tiles of the air gauge, indexed by `(8 - filled) + 8 * target` (the 8-cell shares of unknown340e and unknown340c, see the end of phase_game); original name unknown. Read from the
// rodata at 0x7100f757ac.
static const u8 unknown086[64] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x00, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24,
                                  0x00, 0x00, 0x25, 0x26, 0x27, 0x28, 0x29, 0x00, 0x00, 0x00, 0x2a, 0x2b, 0x2c, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x2e, 0x2f, 0x30, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x31, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
// The name of resource `index` for the search of the map resource below: the same address as archive::get_res, without its `index > 0` test and with an unsigned index. Called with the index of
// the search loop. Its only user is phase_game (0x71006a564c; the load is at 0x71006a5ecc: `ldr w11, [x27, x25, lsl #2]; add x11, x8, x11`, the table index is not sign extended). Forms tried
// without the helper: the plain call `static_cast<const char *>(stageArchive.get_res(index))` in the loop gives 3159 instructions against the game's 3165 (with `u32 index` 3169): the compare
// of the search is the compare of the get_res(index) after the loop, indvars folds both and the game's `cmp w25, #1; b.lt` is lost (0x71006a5f34). The offsets are read from the header of the
// archive itself, as in archive::get_res (decisions 38 and 54).
static const char *getResName(archive &stage, u32 index) {
  const u32 *table = reinterpret_cast<const u32 *>(stage.unknown00);
  return reinterpret_cast<const char *>(stage.unknown00 + ((table[0] + 0x10) & ~0xf) + table[index]);
}

inline void minigame::unknown087() {
  if ((unknown648 & 0xf) == 0) {
    unknown020 *task = create_awa();
    if (task != nullptr) {
      task->unknown2c = unknown024() & 0xffff;
      task->unknown30 = 0xf000;
    }
  }
}

// Game screen (0x71006a564c, 3165 instructions). `switch (unknown650)` of sub phases: 0 builds the stage (the map and the tile data are assembled from the chunks that the csv of the stage lists
// with a random draw per row, the stage row of unknown3198 fills the scroll and bonus state, the palette words, the sixteen sprite sheets and the text screen are loaded, the player task is created),
// the others run the game, the bonus scene, the fades and the end of the stage, creating the bubbles with unknown087 (seven users; the seven written-out blocks give the same code, so ruling 8 does
// not apply); every call ends with unknown076 (draw functions of the tasks). The sheets of the chain of sub phase 0 after the first are decoded by unknown077 (fifteen calls), as in phase_title. Forms
// and measurements of this function: the mapping of the registers of the creation loop follows `unknown6f` compared with 9 and 0xa (not the Name column), the stores of a created task are written in
// the order of the game (pointers first, then the constants in address order: a run of constant stores is merged only when it ends the stores of the block), `unknown3410/3414/3418/341a` are cleared
// by four plain stores (the game's `str wzr` plus `str xzr`; a 12 byte memset from &unknown3410 gives the same code but is a view across four members), and `chance >> 8` of the bonus is computed
// once, first (the shift is the first instruction of the block: the register it takes decides the temporaries of the block).
void minigame::phase_game() {
  switch (unknown650) {
  case 0: {
    unknown025();
    unknown032();
    memset(unknown18->unknown21500, 0, sizeof(unknown18->unknown21500));
    unknown18->unknown18 = 0x10;
    // The stage is read before the two allocations (without the local 3164 instructions against the game's 3165).
    int stage = unknown33e0;
    unknown1260 = static_cast<unknown001 *>(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->allocate(0x10000, 0x40));
    unknown1268 = static_cast<unknown002 *>(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->allocate(0x100000, 0x40));
    u16 mapRows = 0;
    u16 tileRows = 0;
    {
      archive stageArchive;
      stageArchive.unknown00 = static_cast<u8 *>(m_archive.get_res(stage + 0x20));
      csvb::CCsvbData csv;
      csv.Load(gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0), stageArchive.get_res(0), stageArchive.get_res_sz(0));
      u8 *mapDst = unknown1260->unknown10 - 0x10;
      u8 *tileDst = unknown1268->unknown10 - 0x10;
      for (int row = 0; row < csv.GetRowCount(); row++) {
        u32 chance = unknown024();
        if (csv.GetColumCount(row) != 0) {
          int remaining = (chance >> 8) % 100;
          int column = 0;
          do {
            remaining -= csv.GetInt(row, column + 1);
            if (remaining < 0) {
              const char *name = csv.GetString(row, column);
              int index = 1;
              for (;; index += 2) {
                const char *resName = getResName(stageArchive, index);
                const char *letter = name;
                while (*letter != 0) {
                  if (*resName == 0 || *letter != *resName) {
                    break;
                  }
                  letter++;
                  resName++;
                }
                if (*letter == 0 && *resName == '.') {
                  break;
                }
              }
              const u8 *mapRes = static_cast<const u8 *>(stageArchive.get_res(index));
              // The size is read next to the resource and the `- 0x10` of the map is taken where the source is chosen, in the `if (row > 0)`: subtracted straight after the read, the table
              // loads of this block take w9/x9 for the start and w10/x10 for the end of the resource, the game has the reverse (0x71006a5f60), and the constants of the row test move too.
              u32 resSize = stageArchive.get_res_sz(index);
              // The map chunk starts after the 0x10 bytes of header of the resource (decision 54).
              const unknown001 *chunk = reinterpret_cast<const unknown001 *>(mapRes + 0x10);
              mapRows = chunk->unknown02 + mapRows;
              const u8 *mapSrc = mapRes + 0x10;
              u32 mapSize = resSize - 0x10;
              if (row > 0) {
                mapSrc = chunk->unknown10;
                mapSize -= 0x10;
              }
              memcpy(mapDst, mapSrc, mapSize);
              const unknown002 *tiles = static_cast<const unknown002 *>(stageArchive.get_res(index + 1));
              tileRows = tiles->unknown06 + tileRows;
              mapDst += mapSize;
              u32 tilesSize = stageArchive.get_res_sz(index + 1);
              const u8 *tilesSrc = tiles->unknown10 - 0x10;
              if (row > 0) {
                u32 tilesSkip = tiles->unknown02 + 0x10;
                tilesSrc += tilesSkip;
                tilesSize -= tilesSkip;
              }
              memcpy(tileDst, tilesSrc, tilesSize);
              tileDst += tilesSize;
              break;
            }
            column += 2;
          } while (column < csv.GetColumCount(row));
        }
      }
      unknown1260->unknown02 = mapRows;
      unknown1268->unknown06 = tileRows;
      const unknown018 &stageRow = unknown3198[unknown33e0];
      unknown3538 = stageRow.unknown00 << 8;
      unknown353c = -stageRow.unknown02 << 8;
      unknown3540 = -stageRow.unknown04 << 6;
      unknown3544 = -stageRow.unknown06 << 8;
      unknown3548 = stageRow.unknown08;
      unknown354a = stageRow.unknown0c;
      unknown354c = stageRow.unknown0e;
      unknown354e = stageRow.unknown10;
      unknown3550 = stageRow.unknown12;
      unknown3552 = stageRow.unknown14;
      unknown3554 = stageRow.unknown16;
      unknown3555 = stageRow.unknown17;
      unknown3558 = unknown3538;
      unknown355c = 0;
      unknown3560 = 0;
      unknown3564 = mapRows * 0x100000 - 0xf00000;
      unknown3568 = 0;
      unknown356a = 0;
    }
    const u8 *paletteRes = static_cast<const u8 *>(m_archive.get_res(unknown33e0 % 5 + 0x18));
    // The source of the memcpy is a local, as for the palette of the sheets: written inline the game's order of the two address computations (`add x1` before `add x0`, 0x71006a61d0) is lost.
    const u8 *palette = paletteRes + 0x10;
    memcpy(&unknown65c[0x30], palette, 0x30);
    // The same loop as tora_cell_anime, on the table at 0x3000 of the tile memory (a byte pointer next to a separate counter, the word stored with a memcpy). Written with a u32 pointer
    // (`dst[k * 0x40]`, `dst++`) the address of the first store (`add x11, x10, x8`, 0x71006a6210) is computed before the first loads, not after them, and the first group takes other
    // registers (w12/w13 for w11..w14, 0x71006a61f4).
    {
      u8 *dst = unknown18->unknown100 + 0x3000;
      const u8 *src = paletteRes + 0x40;
      for (int column = 0; column != 0x40; column++, dst += 4) {
        for (int row = 0; row < 8; row++) {
          u32 word = unknown078(src);
          memcpy(dst + row * 0x100, &word, sizeof(word));
          src += 4;
        }
      }
    }
    u32 tile = decode_4bpp_sprt(0x41e0, 1);
    tile = unknown077(tile, 0x10000, 0x33);
    tile = unknown077(tile, 0x11000, 0x32);
    tile = unknown077(tile, 0x12000, 0x31);
    tile = unknown077(tile, 0x13000, 0x30);
    tile = unknown077(tile, 0x14000, 0x34);
    tile = unknown077(tile, 0x15000, 0x35);
    tile = unknown077(tile, 0x16000, 0x36);
    tile = unknown077(tile, 0x17000, 0x37);
    tile = unknown077(tile, 0x18000, 0x39);
    tile = unknown077(tile, 0x19000, 0x3a);
    tile = unknown077(tile, 0x1a000, 0x3b);
    tile = unknown077(tile, 0x1b000, 0x3c);
    tile = unknown077(tile, 0x1c000, 0x3d);
    tile = unknown077(tile, 0x1d000, 0x3e);
    unknown077(tile, 0x1d000, 0x3f);
    memcpy(unknown65c, unknown084, sizeof(unknown084));
    unknown658 = 0xff;
    update_palt(unknown658);
    u8 *tileData = unknown1268->unknown10;
    unknown18->unknown08 = tileData;
    unknown18->unknown00 = tileData + 0x300;
    unknown18->unknown11 = 1;
    for (int y = 0; y < 0x40; y += 8) {
      for (int x = 0; x < 0x40; x += 8) {
        for (int j = 0; j < 8; j++) {
          for (int i = 0; i < 8; i++) {
            unknown18->unknown23500[(y + j) * 0x40 + x + i] = 0x3180 + j + i * 8;
          }
        }
      }
    }
    // The base of the loop is a local (written as `unknown18->unknown25500[i]` the function has 3167 instructions).
    u16 *tilemap = unknown18->unknown25500;
    for (int i = 0; i < 0x800; i++) {
      tilemap[i] = 0x20;
    }
    draw_text(unknown18->unknown25500 + 0x61, 0x1000, "SCORE");
    draw_text(unknown18->unknown25500 + 0x121, 0x1000, "ETHER");
    draw_text(unknown18->unknown25500 + 0x1e1, 0x1000, "AIR");
    u16 gaugeTile = unknown30[1].unknown00;
    unknown18->unknown25500[0x220] = gaugeTile + 10;
    for (int i = 1; i < 7; i++) {
      unknown18->unknown25500[0x220 + i] = gaugeTile + 8;
    }
    unknown18->unknown25500[0x227] = gaugeTile + 9;
    unknown18->unknown25500[0x420] = gaugeTile + 0xf;
    for (int i = 1; i < 7; i++) {
      unknown18->unknown25500[0x420 + i] = gaugeTile + 0xd;
      unknown18->unknown25500[0x720 + i] = gaugeTile + 0x80d;
    }
    unknown18->unknown25500[0x427] = gaugeTile + 0x40f;
    for (int row = 0x11; row < 0x1c; row++) {
      unknown18->unknown25500[row * 0x40 + 0x20] = gaugeTile + 0xe;
      unknown18->unknown25500[row * 0x40 + 0x27] = gaugeTile + 0x40e;
    }
    unknown18->unknown25500[0x720] = gaugeTile + 0x80f;
    unknown18->unknown25500[0x727] = gaugeTile + 0xc0f;
    unknown18->unknown34 = 0xf8;
    unknown18->unknown35 = 0;
    sprite_reset();
    unknown022 *player = static_cast<unknown022 *>(task_entry());
    m_sTask = player;
    if (player != nullptr) {
      player->unknown10 = player_move;
      player->unknown18 = player_draw;
      player->unknown20 = "tora";
      player->unknown28 = 0;
      player->unknown29 = 0;
      player->unknown2a = 0;
      player->unknown2b = 0;
      player->unknown2c = 0x8000;
      player->unknown30 = 0x4000;
      player->unknown34 = 0xff;
      player->unknown35 = 0;
      player->unknown36 = -unknown127a;
      player->unknown38 = -unknown127b;
      player->unknown3a = unknown127a << 1;
      player->unknown3b = unknown127b << 1;
      player->unknown40 = 0;
      player->unknown41 = 0;
      player->unknown42 = 2;
      player->unknown43 = 0;
      player->unknown44 = 0;
      player->unknown45 = 0;
      player->unknown46 = 2;
      player->unknown47 = 0;
      player->unknown48 = 0;
      player->unknown4c = 0;
      player->unknown4d = 0;
      player->unknown4f = unknown1278 >> 2;
      player->unknown50 = unknown127e;
      player->unknown52 = unknown1280;
      player->unknown54 = unknown1282;
      player->unknown56 = unknown3548;
      player->unknown58 = 0;
      player->unknown5a = 0;
      player->unknown5c = unknown127c;
      player->unknown5d = unknown127d;
    }
    int objectCount = 0;
    u16 width = unknown1260->unknown00;
    u16 height = unknown1260->unknown02;
    if (height != 0 && width != 0) {
      u8 *cell = unknown1260->unknown10;
      for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
          u8 value = *cell;
          if (value >= 0x80) {
            if (value >= 0xc0) {
              *cell = 1;
            }
          } else {
            switch (value & 0xf0) {
            case 0x10:
            case 0x20:
            case 0x30:
            case 0x40:
            case 0x50:
            case 0x60:
            case 0x70:
              unknown356c[objectCount].unknown00 = 0;
              unknown356c[objectCount].unknown01 = 0;
              unknown356c[objectCount].unknown02 = value;
              unknown356c[objectCount].unknown04 = column << 4 | 8;
              unknown356c[objectCount].unknown06 = row << 4 | 8;
              objectCount++;
              break;
            }
            if ((value & 0x60) == 0x40) {
              if (unknown1688[value & 0x1f].m_tbox_type < 2) {
                unknown3568++;
              }
            } else if ((value & 0x60) == 0x60) {
              unknown356a++;
            }
          }
          cell++;
        }
      }
    }
    unknown356c[objectCount].unknown00 = 0;
    unknown356c[objectCount].unknown02 = 0;
    unknown3530 = nullptr;
    for (int i = 0; i < 0x100; i++) {
      u8 value = unknown356c[i].unknown02;
      if (value == 0) {
        break;
      }
      _sTask *task = task_entry();
      if (task != nullptr) {
        int x = unknown356c[i].unknown04 << 8;
        int y = unknown356c[i].unknown06 << 8;
        task->unknown35 = 0;
        task->unknown28 = 0;
        task->unknown29 = 0;
        task->unknown2a = 0;
        task->unknown2b = 0;
        switch (value & 0xf0) {
        case 0x10:
        case 0x20:
        case 0x30: {
          unknown023 *enemy = static_cast<unknown023 *>(task);
          u8 id = value - 0x10;
          enemy->unknown10 = enemy_move;
          enemy->unknown18 = enemy_draw;
          const unknown014 &row = unknown1288[id];
          enemy->unknown20 = row.unknown00;
          enemy->unknown2c = 0x40000;
          enemy->unknown30 = 0;
          enemy->unknown34 = 2;
          enemy->unknown36 = -row.unknown0a;
          enemy->unknown38 = -row.unknown0b;
          enemy->unknown3a = row.unknown0a << 1;
          enemy->unknown3b = row.unknown0b << 1;
          enemy->unknown40 = 0;
          enemy->unknown41 = id;
          enemy->unknown42 = 0;
          enemy->unknown43 = 0;
          enemy->unknown44 = unknown024() >> 8;
          enemy->unknown45 = 0;
          enemy->unknown48 = x;
          enemy->unknown4c = y;
          enemy->unknown50 = 0;
          enemy->unknown54 = 0;
          enemy->unknown58 = x;
          enemy->unknown5c = y;
          enemy->unknown60 = row.unknown0e;
          enemy->unknown62 = row.unknown10;
          enemy->unknown64 = row.unknown12;
          enemy->unknown66 = row.unknown14;
          enemy->unknown68 = row.unknown16;
          enemy->unknown69 = row.unknown17;
          enemy->unknown6a = row.unknown18;
          enemy->unknown6c = row.unknown1a;
          enemy->unknown6e = row.unknown0c;
          enemy->unknown6f = row.unknown08;
          enemy->unknown70 = row.unknown09;
          enemy->unknown71 = unknown085[row.unknown1c];
          if (enemy->unknown6f == 9) {
            enemy->unknown78 = 0;
            enemy->unknown80 = nullptr;
            for (int s = 0; s < 4; s++) {
              enemy->unknown88[s].unknown00 = s * 0x10;
              enemy->unknown88[s].unknown01 = 0;
              enemy->unknown88[s].unknown02 = 0;
              enemy->unknown88[s].unknown04[0] = 0;
              enemy->unknown88[s].unknown04[1] = 0;
              enemy->unknown88[s].unknown04[2] = 0;
              enemy->unknown88[s].unknown04[3] = 0;
              enemy->unknown88[s].unknown04[4] = 0;
            }
          } else if (enemy->unknown6f == 0xa) {
            enemy->unknown78 = unknown3555;
          }
          break;
        }
        case 0x40:
        case 0x50:
        case 0x60:
        case 0x70: {
          unknown021 *item = static_cast<unknown021 *>(task);
          // `id` is computed once (written out at the two uses: 3166 instructions).
          int id = value & 0x1f;
          item->unknown10 = item_move;
          item->unknown18 = item_draw;
          item->unknown20 = "item";
          item->unknown36 = -10;
          item->unknown38 = -10;
          item->unknown3a = 0x14;
          item->unknown3b = 0x14;
          item->unknown40 = value;
          item->unknown41 = 0;
          item->unknown42 = 0;
          item->unknown43 = 0;
          item->unknown2c = 0x40000;
          item->unknown30 = 0;
          item->unknown34 = 4;
          item->unknown44 = x;
          item->unknown48 = y;
          if (value < 0x60) {
            item->unknown5c = 0;
            if (unknown1688[id].m_tbox_type == 1) {
              unknown3530 = item;
              item->unknown3a = 0x24;
              item->unknown3b = 0x24;
            }
          } else {
            item->unknown5c = unknown3158[id].unknown00;
          }
          break;
        }
        }
      }
    }
    unknown3fe0.unknown38++;
    unknown3400 = 0;
    unknown3404 = 0;
    unknown18->unknown25500[0x100] = 0x103e;
    unknown3408 = 0;
    unknown3409 = 0;
    unknown340c = unknown1278;
    unknown340e = unknown1278;
    unknown3410 = 0;
    unknown3414 = 0;
    unknown3418 = 0;
    unknown341a = 0;
    for (int i = 0; i < 16; i++) {
      unknown3420[i].unknown00 = 0xff;
    }
    unknown3520 = nullptr;
    unknown3401 = 0x3c;
    unknown650 = 4;
    playbgm(1);
    break;
  }
  case 1:
  case 2:
  case 3:
  case 4: {
    if (unknown340c == 0) {
      unknown650 = 5;
      unknown3401 = 0x3c;
      m_sTask->unknown34 = 0;
      break;
    }
    if (unknown3400 != 0) {
      unknown3400 = 0;
      break;
    }
    switch (unknown650) {
    case 1: {
      if (unknown3548 != 0) {
        if (static_cast<unknown022 *>(m_sTask)->unknown44 == 0) {
          unknown355c--;
          if (unknown355c < 0) {
            unknown355c = 0;
          }
        } else {
          unknown355c++;
          if (unknown355c > 8) {
            unknown355c = 8;
          }
        }
        unknown3558 = (unknown1282 * unknown355c & 0xffffff) << 5;
      }
      unknown3560 = unknown3560 + unknown3558;
      if (unknown3560 >= unknown3564) {
        static_cast<unknown022 *>(m_sTask)->unknown56 = 0;
        unknown3560 = unknown3564;
        if (unknown3530 == nullptr || unknown3530->unknown41 != 0) {
          static_cast<unknown022 *>(m_sTask)->unknown42 = 8;
          m_sTask->unknown28 = 0;
          static_cast<unknown022 *>(m_sTask)->unknown40 = 1;
          unknown3401 = 0x3c;
          unknown650 = 2;
        }
      }
      break;
    }
    case 2: {
      unknown3401--;
      if (unknown3401 == 0) {
        unknown3558 = unknown353c;
        unknown650 = 3;
        playbgm(2);
      }
      break;
    }
    case 3: {
      // `scroll` and `speed` are both computed from the old values before either member is stored (`unknown3560 += unknown3558` first gives other registers, 0x71006a6734).
      int scroll = unknown3560 + unknown3558;
      int speed = unknown3540 + unknown3558;
      if (speed < unknown3544) {
        speed = unknown3544;
      }
      unknown3558 = speed;
      unknown3560 = scroll;
      if (scroll < 0) {
        playse(0xf);
        static_cast<unknown022 *>(m_sTask)->unknown42 = 8;
        m_sTask->unknown28 = 0;
        static_cast<unknown022 *>(m_sTask)->unknown40 = 2;
        unknown3560 = 0;
        unknown3401 = 0x5a;
        unknown650 = 6;
        m_sTask->unknown34 = 0;
      }
      break;
    }
    case 4: {
      unknown3401--;
      if (unknown3401 == 0) {
        unknown3558 = unknown3538;
        unknown650 = 1;
      }
      break;
    }
    default:
      // Dead code the game holds: the outer switch only sends 1 to 4 here, yet the game has this default (`b.hi 0x71006a6638`, 22 instructions); without it the function has 3143
      // instructions against 3165 (ruling 5).
      if (unknown1278 > 9 && unknown340c >= unknown1278 / 10) {
        fw::SoundManager::get()->setPitch(unknown1270, 1.5f, 0.0f);
      }
      unknown340c = 0;
      unknown3408 = 7;
      break;
    }
    unknown18->unknown26 = unknown3560 >> 16;
    unknown18->unknown2e = unknown3560 >> 17;
    debug_hex(0, 0, unknown18->unknown26, 8);
    debug_hex(10, 0, unknown3558, 8);
    unknown087();
    m_mytask->executeMove();
    break;
  }
  case 6:
    m_sTask->unknown30 -= 0x400;
    // fall through
  case 5:
    unknown3401--;
    if (unknown3401 == 0) {
      unknown650 = 7;
    }
    unknown087();
    m_mytask->executeMove();
    break;
  case 7: {
    unknown087();
    m_mytask->executeMove();
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      m_mytask->reset();
      gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->deallocate(unknown1260);
      unknown1260 = nullptr;
      gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->deallocate(unknown1268);
      unknown1268 = nullptr;
      if (unknown340c == 0) {
        unknown64c = 5;
        unknown650 = 0;
        unknown65a = (unknown024() & 3) | 4;
      } else {
        unknown64c = 4;
        unknown650 = 0;
        unknown65a = unknown024() & 3;
      }
    }
    update_palt(unknown658);
    break;
  }
  case 8: {
    unknown087();
    m_mytask->executeMove();
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      unknown650 = 9;
      unknown3d6e = unknown3550;
      unknown3d6d = 0;
      unknown3d70 = m_sTask->unknown2c >> 8;
      unknown3d72 = m_sTask->unknown30 >> 8;
      unknown3d74 = static_cast<unknown022 *>(m_sTask)->unknown56;
      m_sTask->unknown2c = 0x48000;
      m_sTask->unknown30 = 0x8000;
      static_cast<unknown022 *>(m_sTask)->unknown56 = 0;
      static_cast<unknown022 *>(m_sTask)->unknown48 = 0;
      unknown18->unknown1c = -0x400;
      unknown18->unknown11 = 0;
      unknown023 *enemy = static_cast<unknown023 *>(get()->task_entry());
      if (enemy != nullptr) {
        enemy->unknown10 = enemy_move;
        enemy->unknown20 = "senzo";
        enemy->unknown35 = 0;
        enemy->unknown18 = enemy_draw;
        enemy->unknown28 = 0;
        enemy->unknown29 = 0;
        enemy->unknown2a = 0;
        enemy->unknown2b = 0;
        enemy->unknown2c = 0x40000;
        enemy->unknown30 = 0;
        enemy->unknown34 = 2;
        enemy->unknown36 = -8;
        enemy->unknown38 = -8;
        enemy->unknown3a = 0x10;
        enemy->unknown3b = 0x10;
        enemy->unknown40 = 0;
        enemy->unknown41 = 0x1f;
        enemy->unknown42 = 0;
        enemy->unknown43 = 0;
        enemy->unknown44 = unknown024() >> 8;
        enemy->unknown45 = 0;
        enemy->unknown48 = 0x48000;
        enemy->unknown4c = unknown3560 / 256 + 0x2000;
        enemy->unknown54 = 0;
        enemy->unknown58 = 0x48000;
        enemy->unknown6e = 0;
        enemy->unknown6f = 0;
        enemy->unknown60 = 0;
        enemy->unknown62 = 0;
        enemy->unknown64 = 0;
        enemy->unknown66 = 0;
        enemy->unknown50 = 0;
        enemy->unknown5c = enemy->unknown4c;
        enemy->unknown70 = 3;
        enemy->unknown6c = 0;
        enemy->unknown71 = 0x3e;
      }
    }
    update_palt(unknown658);
    break;
  }
  case 9: {
    if (unknown3d6e > 0x5a && (unknown3d6e & 3) == 0) {
      // The number is drawn before task_entry() (the LCG advance `madd w22` at 0x71006a5aec comes before the
      // call at 0x71006a5b04) and shifted once: `lsr w8, w22, #8` (0x71006a7d10, the rate test) and
      // `ubfx w12, w22, #8, #10` (0x71006a7cdc, unknown50) read the raw value. Machine sinking puts the
      // shift at the top of the block of stores, so w8 stays busy through it as in the game; `(chance >> 8)`
      // written at each use leaves w8 to the temporaries (16 differing lines). The stores of the block start like
      // those of the senzo block of case 8 (unknown10, unknown20, unknown35, unknown18, unknown28 to unknown48);
      // from unknown50 on the two blocks are in the order of the game's own stores, which differ.
      u32 chance = unknown024() >> 8;
      unknown023 *bonus = static_cast<unknown023 *>(get()->task_entry());
      if (bonus != nullptr) {
        bonus->unknown10 = enemy_move;
        bonus->unknown20 = "bonus";
        bonus->unknown35 = 0;
        bonus->unknown18 = enemy_draw;
        bonus->unknown28 = 0;
        bonus->unknown29 = 0;
        bonus->unknown2a = 0;
        bonus->unknown2b = 0;
        bonus->unknown2c = 0x40000;
        bonus->unknown30 = 0;
        bonus->unknown34 = 2;
        bonus->unknown36 = -8;
        bonus->unknown38 = -8;
        bonus->unknown3a = 0x10;
        bonus->unknown3b = 0x10;
        bonus->unknown40 = 0;
        bonus->unknown41 = 0x1f;
        bonus->unknown42 = 0;
        bonus->unknown43 = 8;
        bonus->unknown44 = unknown024() >> 8;
        bonus->unknown45 = 0;
        bonus->unknown48 = 0x48000;
        bonus->unknown4c = unknown3560 / 256 + 0x2000;
        bonus->unknown50 = (chance & 0x3ff) - 0x200;
        bonus->unknown54 = -0x400;
        bonus->unknown58 = 0x48000;
        bonus->unknown5c = bonus->unknown4c;
        bonus->unknown60 = 0x40;
        bonus->unknown62 = 0;
        bonus->unknown64 = 0;
        bonus->unknown66 = 0;
        bonus->unknown6e = 0;
        bonus->unknown6f = 0xb;
        bonus->unknown70 = 3;
        if (chance % 10000 < unknown3552) {
          bonus->unknown6c = 0;
          bonus->unknown71 = 0x35;
        } else {
          bonus->unknown6c = unknown3554;
          bonus->unknown71 = 0x30;
        }
      }
    }
    unknown3d6e--;
    if (unknown3d6e == 0 || unknown3d6d != 0) {
      unknown650 = 10;
      m_sTask->unknown34 = 0;
    }
    unknown087();
    m_mytask->executeMove();
    if (unknown658 < 0xff) {
      unknown658 += 0x10;
      if (unknown658 > 0xff) {
        unknown658 = 0xff;
      }
      update_palt(unknown658);
    }
    break;
  }
  case 10: {
    unknown087();
    m_mytask->executeMove();
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      unknown650 = 0xb;
      m_sTask->unknown2c = unknown3d70 << 8;
      m_sTask->unknown30 = unknown3d72 << 8;
      static_cast<unknown022 *>(m_sTask)->unknown56 = unknown3d74;
      unknown18->unknown1c = 0;
      unknown18->unknown11 = 1;
    }
    update_palt(unknown658);
    break;
  }
  case 11: {
    unknown087();
    m_mytask->executeMove();
    unknown658 += 0x10;
    if (unknown658 > 0xff) {
      unknown658 = 0xff;
      unknown650 = unknown3d6c;
      static_cast<unknown022 *>(m_sTask)->unknown48 = 0x5a;
      m_sTask->unknown34 = 0xff;
    }
    update_palt(unknown658);
    break;
  }
  }
  // The score text lives in its own block (ruling 3): with one `text` for both numbers the function has 3169 instructions and the frame differs (`mov w10, #0xf0000` for the game's w9 at
  // 0x71006a828c).
  {
    char text[7];
    if (unknown3409 != 0) {
      unknown3414 = (unknown3409 + unknown3410 - 1 - unknown3414) / unknown3409 + unknown3414;
      unknown3409--;
    }
    if (unknown3414 >= 1000000) {
      unknown3414 = 999999;
    }
    get_score_text(text, unknown3414);
    draw_text(unknown18->unknown25500 + 0xa1, 0x1000, text);
  }
  char text[7];
  get_score_text(text, unknown3418 + unknown341a);
  draw_text(unknown18->unknown25500 + 0x161, 0x1000, text);
  if (unknown3408 != 0) {
    unknown340e += (unknown3408 + unknown340c - 1 - unknown340e) / unknown3408;
    unknown3408--;
  }
  u32 hp = unknown1278;
  int filled = unknown340e * 0x30 / hp;
  if (hp > unknown340e * 0x30 && unknown340e != 0) {
    filled = 1;
  }
  int target = unknown340c * 0x30 / hp;
  if (hp > unknown340c * 0x30 && unknown340c != 0) {
    target = 1;
  }
  // A pointer walk: indexed by `0x221 + i` the loop has other registers (`mul w13` for the game's `ldrh w14, [x19, #4728]`, 0x71006a8618).
  u16 *cells = &unknown18->unknown25500[0x221];
  for (int i = 0; i < 6; i++) {
    u16 gauge;
    if (target < 8) {
      if (filled < 8) {
        if (filled > target) {
          gauge = unknown086[(8 - filled) + target * 8];
        } else {
          gauge = 8 - target;
        }
      } else {
        gauge = unknown086[target * 8];
      }
    } else {
      gauge = 0;
    }
    filled -= 8;
    if (filled < 0) {
      filled = 0;
    }
    target -= 8;
    if (target < 0) {
      target = 0;
    }
    *cells++ = unknown30[1].unknown00 + gauge;
  }
  if (unknown340c == 0 || unknown340c >= unknown1278 / 10) {
    fw::SoundManager::get()->setPitch(unknown1270, 1.0f, 0.0f);
  } else {
    fw::SoundManager::get()->setPitch(unknown1270, 1.5f, 0.0f);
  }
  unknown076();
}

// Stage clear screen (0x71006a87c0). Sub phase 0 builds the screen (the picture of 5 rows of unknown072 in the first layer, the 8 by 8 tiles from tile 0x140 in palette bank 2), sets the five bonus
// flags unknown3da1 (unknown340c against unknown1278, unknown3418 against unknown356a, the number of entries of unknown3420 (up to 16, ended by 0xff) against unknown3568, the three together, and
// unknown340b equal to zero) and lists the entries of unknown3420 in unknown3da8 (the entries of type 0 in the order found from index 1, the last other entry at index 0, the rest 0xff) with a mark
// per entry in unknown3db8. Sub phase 1 fades in, 2 to 11 show and count up the score, the ether and the bonuses one after the other, 12 and 0x5a wait for the button of bit 2 of unknown14 and 99
// fades out and switches to phase 6. Every call ends with the cell animation, the draw tasks and the clearing of the width of the sprites that they did not use (the last loop reads `unknown40b0` at
// every iteration: the sprite stores may alias it).
// The entry list of sub phase 0 stores `unknown3da8[n] = item; n++;` as two statements. With `unknown3da8[n++] = item;` the function has 3586 instructions as well, but 17 differ in the join after
// the count test: the game issues `mov #0x3da6`, `mov #0x3da5` and `mov #0x3db8` after `ldrb [0x340b]; cmp #0` and holds the addresses of flags [3] and [4] in w11 and w12, the other way round from
// the one-statement form. Measured with `llc` 3.9.1 on the IR of the function: the machine scheduler output and the post-register-allocation schedule are the game's in both (the post-RA scheduler
// turns our pre-RA order into the game's final order when it is given the game's registers), so only the register assignment differs. The two statements move the increment of `n` behind the store in
// the loop body; presumably this changes the size of the live range of the loop-carried `n` against that of the address of unknown3da8, which the greedy allocator assigns in order of size. The
// count-up sub phases 3, 5, 8, 9 and 11 share the frame step (unknown075, inlined: the same code as the five written-out copies) and the screen set-up of sub phase 0 is shared with the title and game
// over screens (unknown074). Ruling 8: the transfer of the share `(unknown3d8c + unknown3d89) / (unknown3d89 + 1)` from a pool to a counter (`unknown3410`, a `u32`, or `unknown3418`, a `u16`;
// sub phase 9 moves two shares, from unknown3d8c and unknown3d90) is written out in sub phases 3, 5, 8, 9 and 11 because the helper forms measured on the unit all miss (3586 instructions each, the
// game's count): `template <typename T> static void f(u32 &pool, T &counter, u32 frames)` (also with a `u8 frames`) is 19 differing lines, the registers of the 0x3410 address and the share, and a
// helper that subtracts the share from the pool and returns it (`unknown3410 += f(unknown3d8c, unknown3d89)`) 53 lines; the quality gate reports the five blocks.
void minigame::phase_clear() {
  switch (unknown650) {
  case 0:
    unknown025();
    unknown032();
    playbgm(3);
    decode_4bpp_sprt(0x71e0, 56);
    memcpy(&unknown65c[16], unknown070, sizeof(unknown070));
    tora_cell_anime_setup(unknown65a);
    memcpy(&unknown65c[32], unknown3d78.unknown00 + 0x10, 0x30);
    unknown074();
    // Inferred role: tiles of the five rows of the picture of the stage clear screen, 5 rows of 40 tiles; original name unknown. Game rodata 0x7100f757ec.
    static const u8 unknown072[5][0x28] = {{0, 1, 1, 13, 1, 1, 1, 13, 0, 1, 13, 0, 0, 1, 1, 13, 1, 1, 1, 13, 0, 7, 7, 14, 7, 14, 0, 0, 7, 7, 7, 14, 0, 7, 14, 0, 7, 7, 14, 0},
                                           {2, 13, 0, 0, 0, 2, 13, 0, 2, 13, 2, 13, 2, 13, 0, 0, 2, 13, 0, 0, 8, 14, 0, 0, 8, 14, 0, 0, 8, 14, 0, 0, 8, 14, 8, 14, 8, 14, 8, 14},
                                           {0, 3, 13, 0, 0, 3, 13, 0, 3, 3, 3, 13, 3, 13, 3, 13, 3, 3, 13, 0, 9, 14, 0, 0, 9, 14, 0, 0, 9, 9, 14, 0, 9, 9, 9, 14, 9, 9, 14, 0},
                                           {0, 0, 4, 13, 0, 4, 13, 0, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 0, 0, 10, 14, 0, 0, 10, 14, 0, 0, 10, 14, 0, 0, 10, 14, 10, 14, 10, 14, 10, 14},
                                           {5, 5, 13, 0, 0, 5, 13, 0, 5, 13, 5, 13, 0, 5, 5, 13, 5, 5, 5, 13, 0, 11, 11, 14, 11, 11, 11, 14, 11, 11, 11, 14, 11, 14, 11, 14, 11, 14, 11, 14}};
    for (int row = 0; row < 5; row++) {
      for (int i = 0; i < 0x28; i++) {
        unknown18->unknown21500[(row + 1) * 0x40 + i] = unknown072[row][i] + 0x80;
      }
    }
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        unknown18->unknown21500[(y + 9) * 0x40 + x + 2] = 0x2140 + x * 8 + y;
      }
    }
    memset(unknown18->unknown23500, 0, sizeof(unknown18->unknown23500));
    unknown658 = 0;
    update_palt(0);
    unknown3fe0.unknown3c++;
    memset(unknown3d94, 0, sizeof(unknown3d94));
    memset(unknown3d9c, 0, sizeof(unknown3d9c));
    // P3: the game stores zero here (the 14 byte run of unknown3d94, unknown3d9c and unknown3da1[0]: `str xzr` at 0x3d9a and 0x3d94, 0x71006aae5c and 0x71006aae64) and again the flag (`strb` at
    // 0x71006aae84); without the first store the run is 13 bytes and the code differs (0x3d99 against 0x3d9a).
    unknown3da1[0] = 0;
    unknown3da1[0] = unknown340c == unknown1278;
    unknown3da1[1] = unknown3418 == unknown356a;
    unknown3418 += unknown341a;
    unknown3da1[2] = 0;
    {
      int count = 0;
      while (count < 16 && unknown3420[count].unknown00 != 0xff) {
        count++;
      }
      if (count == unknown3568) {
        unknown3da1[2] = 1;
      }
      unknown3da1[3] = 0;
      if (unknown3da1[0] && unknown3da1[1] && unknown3da1[2]) {
        unknown3da1[3] = 1;
      }
    }
    unknown3da1[4] = unknown340b == 0;
    unknown3da6 = 0;
    memset(unknown3db8, 0, 16);
    memset(unknown3da8, 0xff, sizeof(unknown3da8));
    {
      int n = 1;
      for (int i = 0; i < 16; i++) {
        u8 item = unknown3420[i].unknown00;
        if (item != 0xff) {
          if (unknown1688[item].m_tbox_type == 0) {
            unknown3da8[n] = item;
            n++;
          } else {
            unknown3da8[0] = item;
          }
        }
      }
    }
    for (int i = 0; i < 16; i++) {
      if (unknown3da8[i] == 0xff) {
        break;
      }
      unknown3db8[i] = 1;
    }
    unknown650++;
    break;
  case 1:
    unknown658 += 0x10;
    if (unknown658 > 0xff) {
      unknown658 = 0xff;
      unknown3d88 = 0;
      unknown3d89 = 30;
      unknown650 = 2;
    }
    update_palt(unknown658);
    break;
  case 2: {
    char text[7];
    if (unknown3d89 == 0) {
      if (unknown3da1[0] == 0) {
        unknown3d89 = 30;
        unknown650 = 4;
        break;
      }
      playse(6);
      unknown3d9c[0] = 1;
      unknown3d8c = unknown32ea * unknown3410 / 100;
      unknown3d88 = 0;
      unknown3d89 = 30;
      unknown650++;
      break;
    }
    unknown3d89--;
    get_score_text(text, unknown3410);
    draw_text(unknown18->unknown21500 + 0x30e, 0x1000, "SCORE:");
    draw_text(unknown18->unknown21500 + 0x314, 0x1000, text);
    break;
  }
  case 3: {
    char text[7];
    if (unknown3d88 < 99) {
      unknown075();
      if (unknown3d88 == 1) {
        u32 delta = (unknown3d8c + unknown3d89) / (unknown3d89 + 1);
        unknown3410 += delta;
        unknown3d8c -= delta;
        playse(10);
      }
      get_score_text(text, unknown3410);
      draw_text(unknown18->unknown21500 + 0x314, 0x1000, text);
      get_score_text(text, unknown3d8c);
      draw_text(unknown18->unknown21500 + 0x31b, 0x1000, "+");
      draw_text(unknown18->unknown21500 + 0x31c, 0x1000, text);
      draw_text(unknown18->unknown21500 + 0x35d, 0x1000, "NO DAMAGE");
      break;
    }
    vram_fill(unknown18->unknown21500 + 0x31b, 13, 2, 0);
    unknown3d89 = 30;
    unknown650++;
    break;
  }
  case 4: {
    char text[7];
    if (unknown3d89 == 0) {
      if (unknown3da1[1] == 0) {
        unknown3d8c = 0;
        unknown3d88 = 0;
        unknown3d89 = 30;
        unknown3d8a = 0;
        unknown650 = 6;
      } else {
        playse(6);
        unknown3d9c[1] = 1;
        unknown3d8c = unknown3418 * unknown32e8 / 100;
        unknown3d88 = 0;
        unknown3d89 = 30;
        unknown650++;
      }
      break;
    }
    unknown3d89--;
    get_score_text(text, unknown3418);
    draw_text(unknown18->unknown21500 + 0x3ce, 0x1000, "ETHER:");
    draw_text(unknown18->unknown21500 + 0x3d4, 0x1000, text);
    break;
  }
  case 5: {
    char text[7];
    if (unknown3d88 < 99) {
      unknown075();
      if (unknown3d88 == 1) {
        u32 delta = (unknown3d8c + unknown3d89) / (unknown3d89 + 1);
        unknown3418 += delta;
        unknown3d8c -= delta;
        playse(10);
      }
      get_score_text(text, unknown3418);
      draw_text(unknown18->unknown21500 + 0x3d4, 0x1000, text);
      get_score_text(text, unknown3d8c);
      draw_text(unknown18->unknown21500 + 0x3db, 0x1000, "+");
      draw_text(unknown18->unknown21500 + 0x3dc, 0x1000, text);
      draw_text(unknown18->unknown21500 + 0x41d, 0x1000, "COMPLETE");
      break;
    }
    vram_fill(unknown18->unknown21500 + 0x3db, 13, 2, 0);
    unknown3d8c = 0;
    unknown3d88 = 0;
    unknown3d89 = 30;
    unknown3d8a = 0;
    unknown650++;
    break;
  }
  case 6: {
    // `item` and the `bonus` of case 7 are out parameters of choice_tbox and stay uninitialised: `= 0` adds a store (3587 instructions against 3586; `bonus = 0` alone in case 7 also misses).
    u16 item;
    if (unknown3d89 != 0) {
      unknown3d89--;
      if (unknown3d89 == 0) {
        unknown3d89 = 6;
        if (unknown3da8[unknown3d88] != 0xff) {
          playse(8);
          unknown3db8[unknown3d88] = 2;
          unknown3d88++;
          break;
        }
        if (unknown3da1[2] != 0) {
          unknown3d9c[2] = 1;
          draw_text(unknown18->unknown21500 + 0x50a, 0x1000, "TREASURE COMPLETE !!");
          {
            u16 bonus = 0;
            u8 box = unknown3da8[0];
            for (int i = 0; box != 0xff; i++) {
              if (unknown1688[box].m_tbox_type == 1) {
                choice_tbox(box & 0x1f, item, &bonus);
                unknown3d8c = unknown32d8[bonus - 0xee49];
                break;
              }
              box = unknown3da8[i + 1];
            }
            unknown3da6 = bonus;
          }
          if (unknown3da6 != 0) {
            char text[7];
            get_score_text(text, unknown3d8c);
            draw_text(unknown18->unknown21500 + 0x3db, 0x1000, "+");
            draw_text(unknown18->unknown21500 + 0x3dc, 0x1000, text);
            draw_text(unknown18->unknown21500 + 0x41d, 0x1000, "TREASURE");
          }
        }
        unknown3d88 = 0;
        unknown3d89 = 30;
        unknown650++;
      }
    }
    break;
  }
  case 7: {
    if (unknown3d89 != 0) {
      unknown3d89--;
      if (unknown3d89 == 0) {
        unknown3d89 = 10;
        if (unknown3da8[unknown3d88] == 0xff) {
          unknown3d88 = 0;
          unknown3d89 = 30;
          unknown650 = 8;
          break;
        }
        playse(6);
        u16 item;
        u16 bonus;
        choice_tbox(unknown3da8[unknown3d88], item, unknown3da1[2] != 0 ? &bonus : nullptr);
        unknown3db8[unknown3d88] = add_result(item, unknown3d8c) + 1;
        unknown3d88++;
      }
    }
    char text[7];
    get_score_text(text, unknown3418);
    draw_text(unknown18->unknown21500 + 0x3d4, 0x1000, text);
    get_score_text(text, unknown3d8c);
    draw_text(unknown18->unknown21500 + 0x3db, 0x1000, "+");
    draw_text(unknown18->unknown21500 + 0x3dc, 0x1000, text);
    draw_text(unknown18->unknown21500 + 0x41d, 0x1000, "TREASURE");
    break;
  }
  case 8: {
    char text[7];
    if (unknown3d88 < 99) {
      unknown075();
      if (unknown3d88 == 1) {
        u32 delta = (unknown3d8c + unknown3d89) / (unknown3d89 + 1);
        unknown3418 += delta;
        unknown3d8c -= delta;
        playse(10);
      }
      get_score_text(text, unknown3418);
      draw_text(unknown18->unknown21500 + 0x3d4, 0x1000, text);
      get_score_text(text, unknown3d8c);
      draw_text(unknown18->unknown21500 + 0x3db, 0x1000, "+");
      draw_text(unknown18->unknown21500 + 0x3dc, 0x1000, text);
      draw_text(unknown18->unknown21500 + 0x41d, 0x1000, "TREASURE");
      break;
    }
    vram_fill(unknown18->unknown21500 + 0x3db, 13, 2, 0);
    if (unknown3da1[3] == 0) {
      unknown3d88 = 0;
      unknown3d89 = 30;
      unknown650 += 2;
      break;
    }
    playse(6);
    unknown3d9c[3] = 1;
    unknown3d8c = unknown32ec * unknown3410 / 100;
    unknown3d90 = unknown32d8[4];
    unknown3d88 = 0;
    unknown3d89 = 30;
    unknown650++;
    break;
  }
  case 9: {
    char text[7];
    if (unknown3d88 < 99) {
      unknown075();
      if (unknown3d88 == 1) {
        u32 delta = (unknown3d8c + unknown3d89) / (unknown3d89 + 1);
        unknown3410 += delta;
        unknown3d8c -= delta;
        u32 delta2 = (unknown3d89 + unknown3d90) / (unknown3d89 + 1);
        unknown3418 += delta2;
        unknown3d90 -= delta2;
        playse(10);
      }
      get_score_text(text, unknown3410);
      draw_text(unknown18->unknown21500 + 0x314, 0x1000, text);
      get_score_text(text, unknown3d8c);
      draw_text(unknown18->unknown21500 + 0x31b, 0x1000, "+");
      draw_text(unknown18->unknown21500 + 0x31c, 0x1000, text);
      draw_text(unknown18->unknown21500 + 0x35d, 0x1000, "PERFECT");
      get_score_text(text, unknown3418);
      draw_text(unknown18->unknown21500 + 0x3d4, 0x1000, text);
      get_score_text(text, unknown3d90);
      draw_text(unknown18->unknown21500 + 0x3db, 0x1000, "+");
      draw_text(unknown18->unknown21500 + 0x3dc, 0x1000, text);
      draw_text(unknown18->unknown21500 + 0x41d, 0x1000, "PERFECT");
      break;
    }
    vram_fill(unknown18->unknown21500 + 0x31b, 13, 5, 0);
    unknown3d88 = 0;
    unknown3d89 = 30;
    unknown650++;
    break;
  }
  case 10:
    if (unknown3da1[4] == 0) {
      unknown3d88 = 0;
      unknown3d89 = 30;
      unknown650 = 12;
    } else {
      playse(6);
      unknown3d9c[4] = 1;
      unknown3d8c = unknown32ee * unknown3410 / 100;
      unknown3d88 = 0;
      unknown3d89 = 30;
      unknown650++;
    }
    break;
  case 11: {
    char text[7];
    if (unknown3d88 < 99) {
      unknown075();
      if (unknown3d88 == 1) {
        u32 delta = (unknown3d8c + unknown3d89) / (unknown3d89 + 1);
        unknown3410 += delta;
        unknown3d8c -= delta;
        playse(10);
      }
      get_score_text(text, unknown3410);
      draw_text(unknown18->unknown21500 + 0x314, 0x1000, text);
      get_score_text(text, unknown3d8c);
      draw_text(unknown18->unknown21500 + 0x31b, 0x1000, "+");
      draw_text(unknown18->unknown21500 + 0x31c, 0x1000, text);
      draw_text(unknown18->unknown21500 + 0x35d, 0x1000, "NO KILL");
      break;
    }
    vram_fill(unknown18->unknown21500 + 0x31b, 13, 2, 0);
    unknown3d89 = 30;
    unknown650++;
    break;
  }
  case 12:
    unknown650 = 0x5a;
  case 0x5a:
    if ((unknown14 & 4) != 0) {
      playse(11);
      unknown650 = 99;
    }
    break;
  case 99:
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      unknown64c = 6;
      unknown650 = 0;
    }
    update_palt(unknown658);
    break;
  }
  tora_cell_anime();
  unknown40b0 = 0;
  // `get()->draw_obj`, not `draw_obj`: the game loads the singleton from the GOT (0x71006ab7c4, `ldr x8, [x8, #0x870]; ldr x8, [x8]`) and addresses unknown18, unknown40b0 and the sprites from x8
  // instead of `this` (x19) in the inlined draw_obj (0x71006ab82c to 0x71006ab954).
  for (int i = 0; i < 4; i++) {
    get()->draw_obj(56, unknown3d9c[i] != 0 ? i + 5 : 4, 0x70 + i * 0x30, 0x48, 0, 0x80);
  }
  if (unknown3d9c[4] != 0) {
    get()->draw_obj(56, 9, 0x130, 0x48, 0, 0x80);
  }
  // Inferred role: x and y of the draw object of each of the 16 entries of unknown3db8, halved; original name unknown. Game rodata 0x7100f75630.
  static const u8 unknown073[16][2] = {
      {28, 102}, {58, 94}, {84, 94}, {110, 94}, {136, 94}, {58, 110}, {84, 110}, {110, 110}, {136, 110}, {17, 94}, {17, 94}, {17, 94}, {17, 94}, {17, 94}, {17, 94}, {17, 94}};
  for (int i = 0; i < 16; i++) {
    u8 state = unknown3db8[i];
    if (state != 0) {
      get()->draw_obj(56, state + (state < 3 && i == 0 ? 10 : 0) - 1, unknown073[i][0] * 2, unknown073[i][1] * 2, 0, 0x80);
    }
  }
  if (unknown3da6 != 0) {
    get()->draw_obj(56, 2, 0x100, 0xa0, 0, 0x80);
  }
  // The end of the frame of unknown076 written out: unknown076 zeroes unknown40b0 first, and here the draw_obj calls sit between that store and executeDraw, so it cannot be called.
  m_mytask->executeDraw();
  for (; unknown40b0 < 0x40; unknown40b0++) {
    unknown18->unknown21100[unknown40b0].unknown0a = 0;
  }
}

// Game over screen (0x71006abfc8). Sub phase 0 builds the screen (the picture of 5 rows of unknown071 in the first layer, the 8 by 8 tiles from tile 0x140 in palette bank 2, "SCORE:" and "ETHER:"
// with their numbers; the palettes of banks 1 and 2 are at 0x68c and 0x6bc), 1 fades in, 2 waits for the button of bit 2 and 3 fades out and switches to phase 6. Every call ends with the cell
// animation, the draw tasks and the clearing of the width of the sprites that they did not use (the last loop reads `unknown40b0` at every iteration: the sprite stores may alias it).
void minigame::phase_over() {
  switch (unknown650) {
  case 0: {
    unknown025();
    unknown032();
    playbgm(3);
    memcpy(&unknown65c[16], unknown070, sizeof(unknown070));
    tora_cell_anime_setup(unknown65a);
    memcpy(&unknown65c[32], unknown3d78.unknown00 + 0x10, 0x30);
    unknown074();
    for (int row = 0; row < 5; row++) {
      for (int column = 0; column < 0x28; column++) {
        unknown18->unknown21500[(row + 1) * 0x40 + column] = unknown071[row][column] + 0x80;
      }
    }
    for (int column = 0; column < 8; column++) {
      for (int row = 0; row < 8; row++) {
        unknown18->unknown21500[(row + 7) * 0x40 + column + 16] = 0x2140 + column * 8 + row;
      }
    }
    char text[7];
    get_score_text(text, unknown3410);
    draw_text(&unknown18->unknown21500[16 * 0x40 + 14], 0x1000, "SCORE:");
    draw_text(&unknown18->unknown21500[16 * 0x40 + 20], 0x1000, text);
    get_score_text(text, unknown3418);
    draw_text(&unknown18->unknown21500[18 * 0x40 + 14], 0x1000, "ETHER:");
    draw_text(&unknown18->unknown21500[18 * 0x40 + 20], 0x1000, text);
    memset(unknown18->unknown23500, 0, sizeof(unknown18->unknown23500));
    unknown658 = 0;
    memset(unknown18->unknown20100, 0, sizeof(unknown18->unknown20100));
    unknown18->unknown10 = 0;
    unknown3fe0.unknown40++;
    memset(unknown3db8, 0, sizeof(unknown3db8));
    unknown650 = 1;
    break;
  }
  case 1:
    unknown658 += 0x10;
    if (unknown658 > 0xff) {
      unknown658 = 0xff;
      unknown3d88 = 0;
      unknown3d89 = 30;
      unknown650 = 2;
    }
    update_palt(unknown658);
    break;
  case 2:
    if ((unknown14 & 4) != 0) {
      playse(11);
      unknown650 = 3;
    }
    break;
  case 3:
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      unknown64c = 6;
      unknown650 = 0;
    }
    update_palt(unknown658);
    break;
  }
  tora_cell_anime();
  unknown076();
}

// Inferred role: letters of the name entry, in the order of the cursor; original name unknown. Game rodata 0x7100f75650.
static const char unknown080[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!?&-. ";

// Inferred role: three colors of the ranking screen, 3 entries of 3 bytes; original name unknown. Game rodata 0x7100f759ac.
static const u8 unknown081[3][3] = {{0, 0, 0}, {0, 0, 0}, {0xff, 0, 0}};

// Name entry and ranking screen (0x71006ac9a4). Sub phase 0 builds the screen: unknown3ddb says whether the score enters the rank list of the stage unknown33e0 (check_rank); if so the score is
// stored in the list with a blank name and "ENTER YOUR INITIALS !" and the score are drawn, otherwise "YOUR SCORE", the score and "TOP PLAYERS"; then come the five lines of the list ("STAGE n", score
// and name, the line of the stage in palette bank 2), the palettes and the clear of the second layer. 1 fades in, 2 moves the cursor (direction masks 0x1001000 and 0x4004000) and enters a
// letter with the button of bit 2, 3 waits for that button, 4 waits 0x20 frames, 5 fades out and asks for the next phase (unknown64c = 0xb). Every call ends with the draw tasks and the clearing of
// the width of the sprites that they did not use.
// Forms measured against the 990 instructions of the game (scratch compiles of the unit):
// - check_rank returns an `int`: with `bool`, `u8` or `u16` JumpThreading threads the join of `unknown3ddb = check_rank()` (the flag store and the test of the flag) and the function is 300 to 340
//   lines off; with an `int` the stored byte is a `trunc` and the test an `icmp` of it, which keeps the join (with the lifetime start of the text array) above the duplication threshold.
// - the text is a `char[8]` in two scopes (the screen header, then the lines of the list): the game keeps both in one 8 byte slot (`strb w12, [sp, #0xd]` of the score text at 0x71006acca0 and
//   `strb w27, [sp, #8]` of the list at 0x71006ad618, frame 0x70). Two disjoint `char[7]` get two slots (sp and sp + 8, 14 lines off) and two `char[8]` share one (ruling 3); the scope of the header
//   starts before the first test of the flag, whose join then holds the lifetime start. One array for both gives another list loop (78 lines off).
// - the clamp of unknown33e0 to the first entry is `int x = unknown33e0; if (x < 0 || x > 4) x = 0;`: the game loads the score before the `cmp`/`csel` (0x71006acaa4, 0x71006acaa8) and the stage
//   before the word of the name (0x71006ad200, 0x71006ad204); the ternary form gives the `cmp` first (3 lines off) and the `mov w13, #0x3fed` of the name stores hoisted (2 lines off). It is written
//   again at each use because the stores to the list and the draw calls may alias the member (the game reloads it, 0x71006ad2a8).
// - `slot` in the cursor step is the address of the letter, computed before the load of the alphabet (0x71006acfe0, then the load at 0x71006acfe4); the direct store is 10 lines off.
void minigame::phase_name() {
  switch (unknown650) {
  case 0:
    unknown025();
    unknown032();
    unknown3ddb = check_rank();
    {
      char text[8];
      if (unknown3ddb) {
        int rank = unknown33e0;
        if (rank < 0 || rank > 4) {
          rank = 0;
        }
        unknown3fe0.unknown08[rank].unknown00 = unknown3410;
        unknown3fe0.unknown08[rank].unknown04[0] = ' ';
        unknown3fe0.unknown08[rank].unknown04[1] = ' ';
        unknown3fe0.unknown08[rank].unknown04[2] = ' ';
      }
      memset(unknown18->unknown21500, 0, sizeof(unknown18->unknown21500));
      if (unknown3ddb) {
        draw_text(&unknown18->unknown21500[4 * 0x40 + 10], 0, "ENTER YOUR INITIALS !");
        draw_text(&unknown18->unknown21500[7 * 0x40 + 12], 0, "SCORE       NAME");
        get_score_text(text, unknown3410);
        draw_text(&unknown18->unknown21500[9 * 0x40 + 11], 0x2000, text);
      } else {
        draw_text(&unknown18->unknown21500[4 * 0x40 + 15], 0, "YOUR SCORE");
        get_score_text(text, unknown3410);
        draw_text(&unknown18->unknown21500[6 * 0x40 + 16], 0, text);
        draw_text(&unknown18->unknown21500[12 * 0x40 + 15], 0, "TOP PLAYERS");
      }
      draw_text(&unknown18->unknown21500[15 * 0x40 + 17], 0, "SCORE      NAME");
    }
    for (int i = 0; i < 5; i++) {
      char text[8];
      text[0] = i + '1';
      text[1] = '\0';
      u16 color = (i == unknown33e0) << 13;
      u32 offset = i * 0x80 + 0x440;
      draw_text(&unknown18->unknown21500[offset] + 7, color, "STAGE");
      draw_text(&unknown18->unknown21500[offset] + 13, color, text);
      get_score_text(text, unknown3fe0.unknown08[i].unknown00);
      draw_text(&unknown18->unknown21500[offset] + 16, color, text);
      draw_text(&unknown18->unknown21500[offset] + 29, color, unknown3fe0.unknown08[i].unknown04);
    }
    memset(unknown18->unknown23500, 0, sizeof(unknown18->unknown23500));
    // Three 3 byte copies: one `memcpy(&unknown65c[32], unknown081, sizeof(unknown081))` is 982 instructions against the game's 990 (measured).
    memcpy(&unknown65c[32], unknown081[0], 3);
    memcpy(&unknown65c[33], unknown081[1], 3);
    memcpy(&unknown65c[34], unknown081[2], 3);
    unknown658 = 0;
    memset(unknown18->unknown20100, 0, sizeof(unknown18->unknown20100));
    unknown18->unknown10 = 0;
    unknown3dd0 = 0;
    unknown650 = 1;
    break;
  case 1:
    unknown658 += 0x10;
    if (unknown658 > 0xff) {
      unknown658 = 0xff;
      if (unknown3ddb == 0) {
        unknown650 = 3;
      } else {
        unknown3dd8 = 0;
        unknown3dd9 = 0;
        unknown3dda = 0;
        unknown3ddc[0] = 'A';
        unknown3ddc[1] = ' ';
        unknown3ddc[2] = ' ';
        unknown3ddc[3] = '\0';
        unknown650 = 2;
      }
    }
    update_palt(unknown658);
    break;
  case 2: {
    int direction = (unknown14 & 0x1001000) != 0 ? 1 : 0;
    if ((unknown14 & 0x4004000) != 0) {
      direction = -1;
    }
    if (direction != 0) {
      unknown3dd8 = 0;
      playse(10);
      unknown3dda = (unknown3dda + direction + 0x20) % 0x20;
    }
    if ((unknown14 & 4) != 0) {
      char *slot = &unknown3ddc[unknown3dd9];
      *slot = unknown080[unknown3dda];
      unknown3dd8 = 0;
      playse(11);
      if (unknown3dd9 == 2) {
        unknown650 = 4;
      } else {
        unknown3dd9++;
      }
    }
    int slot = unknown33e0;
    if (slot < 0 || slot > 4) {
      slot = 0;
    }
    unknown3fe0.unknown08[slot].unknown04[0] = unknown3ddc[0];
    unknown3fe0.unknown08[slot].unknown04[1] = unknown3ddc[1];
    unknown3fe0.unknown08[slot].unknown04[2] = unknown3ddc[2];
    unknown3dd8++;
    unknown3ddc[unknown3dd9] = (unknown3dd8 & 0x10) == 0 ? unknown080[unknown3dda] : ' ';
    draw_text(&unknown18->unknown21500[9 * 0x40 + 25], 0x2000, unknown3ddc);
    int rank = unknown33e0;
    if (rank < 0 || rank > 4) {
      rank = 0;
    }
    draw_text(&unknown18->unknown21500[((rank * 2 + 17) & 0x3f) * 0x40] + 29, 0x2000, unknown3fe0.unknown08[rank].unknown04);
    break;
  }
  case 3:
    if ((unknown14 & 4) != 0) {
      playse(11);
      unknown650 = 5;
    }
    break;
  case 4:
    unknown3dd8++;
    if (unknown3dd8 > 0x20) {
      unknown650 = 5;
    }
    break;
  case 5:
    unknown658 -= 0x10;
    if (unknown658 < 0) {
      unknown658 = 0;
      unknown64c = 0xb;
      unknown650 = 0;
    }
    update_palt(unknown658);
    break;
  }
  unknown076();
}

void minigame::enemy_damage(_sTask *task, int damage) {
  unknown023 *enemy = static_cast<unknown023 *>(task);
  playse(2);
  if (enemy->unknown45 == 0) {
    enemy->unknown45 = enemy->unknown69;
    enemy->unknown46 = damage;
    if (enemy->unknown68 > 1) {
      return;
    }
  }
  u16 score = enemy->unknown6c;
  unknown3410 += score;
  unknown3409 = 0x1e;
  unknown3fe0.unknown30 += score;
  unknown3fe0.unknown30_s32[7 + enemy->unknown41]++;
  unknown340b++;
  u32 chance = (unknown024() >> 8) % 10000;
  if (chance < unknown354a + unknown354c) {
    unknown021 *item = static_cast<unknown021 *>(task_entry());
    if (item != nullptr) {
      item->unknown35 = 0;
      item->unknown28 = 0;
      item->unknown29 = 0;
      item->unknown2a = 0;
      item->unknown2b = 0;
      item->unknown10 = item_move;
      item->unknown18 = item_draw;
      item->unknown20 = "item";
      item->unknown2c = enemy->unknown2c;
      item->unknown30 = enemy->unknown30;
      item->unknown34 = 4;
      item->unknown36 = -10;
      item->unknown38 = -10;
      item->unknown3a = 0x14;
      item->unknown3b = 0x14;
      item->unknown40 = chance >= unknown354a;
      item->unknown41 = 4;
      item->unknown42 = 0x96;
      item->unknown43 = 0;
      item->unknown44 = enemy->unknown48;
      item->unknown48 = enemy->unknown4c;
      item->unknown5c = 0;
    }
  }
}

void minigame::choice_tbox(int index, u16 &result, u16 *items) {
  u16 candidates[10];
  int count = 0;
  result = 0;
  for (int i = 0; i < 10; i++) {
    unknown009 &entry = unknown1688[index].unknown02[i];
    if (entry.unknown00 != 0) {
      if (entry.unknown02 != 0 && !gf::GfGameCond::isGameCond(entry.unknown02)) {
        continue;
      }
      candidates[count++] = entry.unknown00;
    }
  }
  if (count == 0) {
    for (int i = 0; i < 10; i++) {
      u16 first = unknown1688[index].unknown02[i].unknown00;
      if (first != 0) {
        candidates[0] = first;
        count = 1;
        break;
      }
    }
  }
  u16 item = candidates[(unknown024() >> 8) % count];
  u32 roll;
  if (items != nullptr) {
    *items = unknown1928[item].unknown00[11].unknown00;
    roll = (unknown024() >> 8) % 100;
    if (unknown1688[index].m_tbox_type == 1) {
      roll -= unknown1928[item].unknown00[11].unknown02;
    }
  } else {
    roll = (unknown024() >> 8) % 100;
  }
  int remaining = roll;
  for (int i = 0; i < 12; i++) {
    remaining -= unknown1928[item].unknown00[i].unknown02;
    if (remaining < 0) {
      result = unknown1928[item].unknown00[i].unknown00;
      return;
    }
  }
}

void effect_move(void *task) {
  unknown020 *effect = static_cast<unknown020 *>(task);
  if (effect->unknown40 == 0) {
    effect->unknown41++;
    effect->unknown2c += effect->unknown44 + static_cast<int>(sinf(effect->unknown41 * 0.2f) * 256.0f);
    effect->unknown30 += effect->unknown48 - minigame::get()->unknown3558 / 256;
    if (effect->unknown30 < 0 || (effect->unknown42 != 0 && --effect->unknown42 == 0)) {
      minigame::get()->m_mytask->remove(effect);
    }
  }
}

void item_move(void *task) {
  static const u16 unknown031[16][2] = {// Inferred role: position in pixels where the n-th treasure box waiting in the inventory flies to; original name unknown.
                                        {0x114, 0x90},
                                        {0x12c, 0x90},
                                        {0x114, 0xa8},
                                        {0x12c, 0xa8},
                                        {0x114, 0xc0},
                                        {0x12c, 0xc0},
                                        {0x114, 0xd8},
                                        {0x12c, 0xd8},
                                        {0x114, 0x90},
                                        {0x114, 0x90},
                                        {0x114, 0x90},
                                        {0x114, 0x90},
                                        {0x114, 0x90},
                                        {0x114, 0x90},
                                        {0x114, 0x90},
                                        {0x114, 0x90}};
  unknown021 *item = static_cast<unknown021 *>(task);
  switch (item->unknown41) {
  case 0: {
    item->unknown42++;
    item->unknown2c = item->unknown44;
    item->unknown30 = item->unknown48 - minigame::get()->unknown3560 / 256;
    if (item->unknown35 == 0) {
      return;
    }
    item->unknown41 = 1;
    item->unknown4c = item->unknown44;
    item->unknown50 = item->unknown30;
    u32 kind = item->unknown40;
    switch (kind & 0x60) {
    case 0x40: {
      u32 index = kind & 0x1f;
      u8 type = minigame::get()->get_tbox_type(index);
      int slot = minigame::get()->add_item(index, item);
      if (slot < 0) {
        minigame::get()->m_mytask->remove(item);
        return;
      }
      item->unknown43 = 0x1e;
      if (type != 0) {
        if (type == 1) {
          item->unknown54 = 0x10c00;
          item->unknown58 = 0x5c00;
        } else {
          item->unknown54 = 0x13400;
          item->unknown58 = 0x6400;
        }
      } else {
        item->unknown54 = unknown031[slot][0] << 8;
        item->unknown58 = unknown031[slot][1] << 8;
      }
      minigame::get()->playse(4);
      break;
    }
    case 0x60:
      item->unknown43 = 0x1e;
      item->unknown54 = 0x13000;
      item->unknown58 = 0x2800;
      minigame::get()->playse(3);
      break;
    }
    item->unknown42 = 0;
    item->unknown54 -= item->unknown4c;
    item->unknown58 -= item->unknown50;
    break;
  }
  case 1:
    if (item->unknown42 < item->unknown43) {
      item->unknown42++;
      item->unknown2c = item->unknown4c + item->unknown54 * item->unknown42 / item->unknown43;
      item->unknown30 = item->unknown50 + item->unknown42 * item->unknown58 / item->unknown43 + static_cast<int>(sinf(item->unknown42 * 3.1415927f / item->unknown43) * 64.0f * 256.0f);
    } else {
      u16 score = item->unknown5c;
      minigame::get()->unknown3410 += score;
      minigame::get()->unknown3409 = 0x1e;
      minigame::get()->unknown3fe0.unknown30 += score;
      switch (item->unknown40 & 0x60) {
      case 0x40:
        item->unknown2c = item->unknown4c + item->unknown54;
        item->unknown30 = item->unknown50 + item->unknown58;
        item->unknown41 = 2;
        break;
      case 0x60:
        minigame::get()->unknown3418++;
        minigame::get()->unknown3fe0.unknown44++;
        minigame::get()->m_mytask->remove(item);
        break;
      default:
        minigame::get()->m_mytask->remove(item);
        break;
      }
    }
    break;
  case 3:
    item->unknown30 += 0x400;
    if (item->unknown30 > 0xf000) {
      minigame::get()->m_mytask->remove(item);
    }
    break;
  case 4:
    if (item->unknown42 == 0) {
      minigame::get()->m_mytask->remove(item);
      return;
    }
    item->unknown42--;
    item->unknown2c = item->unknown44;
    item->unknown30 = item->unknown48 - minigame::get()->unknown3560 / 256;
    if (item->unknown35 == 0) {
      return;
    }
    minigame::get()->playse(4);
    if (item->unknown40 != 0) {
      minigame::get()->add_air(minigame::get()->unknown354e);
      minigame::get()->m_mytask->remove(item);
    } else {
      static_cast<unknown022 *>(minigame::get()->m_sTask)->unknown48 = 0x168;
      minigame::get()->m_mytask->remove(item);
    }
    break;
  }
}

void item_draw(void *task) {
  unknown021 *item = static_cast<unknown021 *>(task);
  u8 palette = 0x50;
  if (item->unknown41 != 0) {
    if (item->unknown41 == 4) {
      if (item->unknown42 < 0x1e && (item->unknown42 & 1) != 0) {
        return;
      }
      minigame::get()->draw_obj(0x31, item->unknown40 + 3, item, 0x50);
      return;
    }
    palette = 0x80;
  }
  switch (item->unknown40 & 0x60) {
  case 0x40: {
    u32 index = item->unknown40 & 0x1f; // Unsigned: the game indexes with umaddl, a plain int index gives and x + mul (measured, 53 against 52 instructions).
    minigame::get()->draw_obj(0x31, minigame::get()->unknown1688[index].m_tbox_type, item, palette);
    break;
  }
  case 0x60:
    if ((item->unknown42 & 0x30) != 0) {
      minigame::get()->draw_obj(0x30, 0, item, palette);
    } else {
      minigame::get()->draw_obj(0x30, item->unknown42 >> 2 & 3, item, palette);
    }
    break;
  }
}

void effect_draw(void *task) {
  unknown020 *effect = static_cast<unknown020 *>(task);
  if (effect->unknown40 == 0) {
    minigame::get()->draw_obj(0x32, 0, effect, 0x80);
  }
}

unknown020 *create_awa() {
  unknown020 *effect = static_cast<unknown020 *>(minigame::get()->m_mytask->entry());
  if (effect != nullptr) {
    effect->unknown10 = effect_move;
    effect->unknown18 = effect_draw;
    effect->unknown20 = "awa";
    effect->unknown28 = 0;
    effect->unknown29 = 0;
    effect->unknown2a = 0;
    effect->unknown2b = 0;
    effect->unknown2c = 0x40000;
    effect->unknown30 = 0;
    effect->unknown34 = 0;
    effect->unknown40 = 0;
    effect->unknown41 = minigame::get()->unknown024() >> 8;
    effect->unknown42 = 0;
    effect->unknown44 = 0;
    effect->unknown48 = (minigame::get()->unknown024() >> 8 & 0xff) - 0x280;
  }
  return effect;
}

// Inferred role: the attack or the body of the player hit something solid and bounces: the frame of the attack is turned around 15 when that gives a larger value (the attack starts to
// retract), the sound 0x11 plays and unknown47 is set; original name unknown. Five users in player_move (the four map tests and the enemy test): the game holds the block twice (0x71006b021c
// for the map tests, tail-merged, and 0x71006b0298 for the enemy test) and shares the tail from the sound on (0x71006b02b4), which is what the helper inlined five times gives.
static void unknown041(unknown022 *player) {
  int reverse = 0xf - player->unknown45;
  if (reverse > player->unknown45) {
    player->unknown45 = reverse;
  }
  minigame::get()->playse(0x11);
  player->unknown47 = 1;
}

// The player (0x71006afeec): the counters, the damage from the map and the enemies, the attack against enemies and the map, the bubbles while stunned, the push of the map, the move from
// the pad and the limits of the screen.
// Measured on the unit (495 instructions in the game, all forms below are checked with the rest of the function written as it is):
// - `sTask` is the view of the task as an _sTask, made once at the top: the game keeps the address of unknown35 in x21 across both arms and loads the byte through it
//   (`ldrb w9, [x21]`, 0x71006aff5c; the other arm `ldrb w9, [x21, #0x35]!`, 0x71006affa8). Converting `player` at each call (`check_dmg_map_obj(player, ...)`) gives a use of the task in the
//   block of the load that lets the address fold into `[x19, #0x35]`: 495 instructions, 1 differing line. The local is used at the three calls (check_dmg_map_obj twice, check_atk_obj) and is kept
//   only because no other form matches.
// - `player->unknown35 = 0` is written once after both arms; written at the end of each arm the function is 491 instructions and 41 lines off (the address of the store is no longer shared).
// - noAir, hit and air are the three values the game keeps live from the arms to the damage test (w24, w8, w23: `cbz w8`, `cbz w23`, `tbnz w24`). Their declaration order is the order of the
//   phis, which gives the order of the constants in the two arms that set them (0x71006affe8, 0x71006b0024): noAir before hit before air matches (4 of the 24 orders of the four
//   locals do); `stunned` is the condition of the store of 0x20 into unknown41 that the arms undo (`strb wzr, [x19, #0x41]` at 0x71006b0030 is skipped only when the damage is not zero
//   and the player is not invincible).
// - `add_air(noAir ? 0 : air)` (value-neutral, air is 0 whenever noAir holds, but `add_air(air)` is 488 instructions and so is a function without noAir): the game loads the singleton and forms the
// address of unknown340c before the test of w24 (0x71006b0084 to 0x71006b008c), as an unconditional call does; the
//   branch `if (!noAir) add_air(air)` loads the singleton in each successor (492 instructions, 57 lines off).
// - the kind of the enemy is tested with the direction bit first (`(0x124UL >> dir & 1) != 0 && kind == 1`): the game tests the kind, then the bit, three times in the order 0, 1, 2 and tests
//   kind == 2 again after the bit of kind 1 failed (0x71006b017c); `kind == 1 && bit` makes SimplifyCFG a switch whose case 1 and 2 share one bit test with a selected mask (515 instructions).
// - the direction masks (`0x124UL >> dir & 1`, `0x92UL >> dir & 1`, `0x222UL >> dir & 1`) are the game's own `mov #mask; lsr; tbnz`: the comparison chains `dir == 2 || dir == 5 || dir == 8` and
//   `dir == 1 || dir == 4 || dir == 7` for the two enemy tests are 504 instructions, `dir == 1 || dir == 5 || dir == 9` for the speed keeps 495 but compiles to `cmp #5; ccmp #9` instead of the
//   shifted mask (the first difference is at the load of the speed).
// - ruling 8: the three bounds tests of the map repeat the statements of check_map(int, int) (0x71006ae07c) at each exit and are not a call `check_map(boxX, boxY) & 0x80` (the call form is
//   494 instructions and 36 lines off: the inlined body gets its x and y tests merged into one unsigned test of y against the limit and tests y before x). The game has the three tests as
//   three branches (0x71006b01e0 `cmp w11, #0xff`, 0x71006b01f8 `tbnz w12, #0x1f`, 0x71006b0204 `cmp w10, w12` against `unknown3566 + 0xf0`), so each failing test has its own exit. The
//   tile test is unknown029 (the helper of check_map(_sTask *)): written out or as the helper it gives the same code. `unknown3566 + 0xf0 <= boxY` (limit first) and `boxX >= 0 && boxX < 0x100`
//   as the branch that continues give the game's compares (`boxX >= 0x100` as the failing test gives `cmp w11, #0x100; b.hs` and `boxY >= unknown3566 + 0xf0` gives `cmp w12, w10; b.ge`,
//   2 differing lines each). boxX and boxY are computed before the test of the map (0x71006b01ac loads the scroll, the other loads sink into the arms): inside the test 25 lines are off.
// - `unknown039[dir][0] * unknown52` with the table first (the other order: 13 differing lines for x, 7 for y), `unknown45++` followed by the wrap (the select form
//   `(u8)(x + 1) < 0x10 ? x + 1 : 0` gives 4 differing lines).
// The tables are the game's rodata at 0x7100f75310 (push), 0x7100f75320 and 0x7100f75330 (direction), 0x7100f75610 (step) and 0x7100f75670 (frames).
void player_move(void *task) {
  // Inferred role: for every combination of the four corners of the box that touch the map (the bits of the result of check_dmg_map_obj: 1 left top, 2 right top, 4 left bottom, 8 right
  // bottom), the push away from them: bit 0 left, bit 1 right, bit 2 up, bit 3 down; original name unknown.
  static const u8 unknown036[16] = {0x00, 0x0a, 0x09, 0x08, 0x06, 0x02, 0x00, 0x0a, 0x05, 0x00, 0x01, 0x09, 0x04, 0x06, 0x05, 0x00};
  // Inferred role: direction of the player (unknown022::unknown46, 0 none, 1 up, 2 down, 3 left, 4 up left, 5 down left, 6 right, 7 up right, 8 down right) for every combination of the four
  // pad bits (1 up, 2 down, 4 left, 8 right): without an item to drop only the four directions, the diagonals keep the vertical one; original name unknown.
  static const u8 unknown037[16] = {0x00, 0x01, 0x02, 0x00, 0x03, 0x01, 0x02, 0x00, 0x06, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
  // Inferred role: the same with the diagonals, used while an item waits to be dropped (unknown3520); original name unknown.
  static const u8 unknown038[16] = {0x00, 0x01, 0x02, 0x00, 0x03, 0x04, 0x05, 0x00, 0x06, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00};
  // Inferred role: step of the player per frame in 1/64 of its speed (x, y) for every combination of the four pad bits (0x2d is 64 / sqrt 2); original name unknown.
  static const s8 unknown039[16][2] = {{0x00, 0x00},
                                       {0x00, -0x40},
                                       {0x00, 0x40},
                                       {0x00, 0x00},
                                       {-0x40, 0x00},
                                       {-0x2d, -0x2d},
                                       {-0x2d, 0x2d},
                                       {0x00, 0x00},
                                       {0x40, 0x00},
                                       {0x2d, -0x2d},
                                       {0x2d, 0x2d},
                                       {0x00, 0x00},
                                       {0x00, 0x00},
                                       {0x00, 0x00},
                                       {0x00, 0x00},
                                       {0x00, 0x00}};
  // Inferred role: frame of the body (unknown42) and mirroring (unknown28) for the 9 directions; original name unknown.
  static const u8 unknown040[9][2] = {{0, 0}, {2, 2}, {2, 0}, {6, 0}, {4, 2}, {4, 0}, {6, 1}, {4, 3}, {4, 1}};
  _sTask *sTask = static_cast<_sTask *>(task);
  unknown022 *player = static_cast<unknown022 *>(sTask);
  u8 hitMask = 0;
  player->unknown43++;
  if (player->unknown48 != 0) {
    player->unknown48--;
  }
  if (player->unknown41 != 0) {
    player->unknown41--;
    unknown023 *enemy = static_cast<unknown023 *>(minigame::get()->check_dmg_map_obj(sTask, hitMask));
    if (enemy != nullptr && (player->unknown35 & 0x82) != 0 && enemy->unknown70 == 4) {
      minigame::get()->enemy_damage(enemy, player->unknown46);
    }
  } else {
    unknown023 *enemy = static_cast<unknown023 *>(minigame::get()->check_dmg_map_obj(sTask, hitMask));
    bool noAir = true;
    bool hit = false;
    int air = 0;
    bool stunned = false;
    if ((player->unknown35 & 0x82) != 0) {
      player->unknown41 = 0x20;
      if (enemy != nullptr && enemy->unknown70 == 4) {
        player->unknown41 = 0;
        minigame::get()->enemy_damage(enemy, player->unknown46);
      } else {
        u8 damage = enemy == nullptr ? player->unknown4f : enemy->unknown6e;
        hit = true;
        if (damage != 0) {
          noAir = false;
          air = -damage;
          if (player->unknown48 == 0) {
            stunned = true;
          }
        }
      }
    }
    if (!stunned) {
      player->unknown41 = 0;
    }
    if (hit && air != 0 && player->unknown48 == 0 && player->unknown4c == 0) {
      minigame::get()->playse(1);
      minigame::get()->add_air(noAir ? 0 : air);
      void *item = minigame::get()->get_dropitem();
      if (item != nullptr) {
        static_cast<unknown021 *>(item)->unknown41 = 3;
      }
    }
  }
  player->unknown35 = 0;
  if (player->unknown40 == 0 && player->unknown47 == 0) {
    unknown023 *target = static_cast<unknown023 *>(minigame::get()->check_atk_obj(sTask));
    if (target == nullptr) {
      if (player->unknown5c != 0) {
        int boxX = (player->unknown2c >> 8) + player->unknown58;
        int boxY = ((player->unknown30 + minigame::get()->unknown3560 / 256) >> 8) + player->unknown5a;
        u8 *map = minigame::get()->get_map_bin();
        if (map != nullptr) {
          if (boxX >= 0 && boxX < 0x100) {
            if (boxY < 0) {
              unknown041(player);
            } else if (minigame::get()->unknown3566 + 0xf0 <= boxY) {
              unknown041(player);
            } else if (unknown029(map, boxX, boxY)) {
              unknown041(player);
            }
          } else {
            unknown041(player);
          }
        }
      }
    } else if (target->unknown70 < 3) {
      u8 dir = player->unknown46;
      u8 kind = target->unknown70;
      if (kind == 0 || ((0x124UL >> dir & 1) != 0 && kind == 1) || ((0x92UL >> dir & 1) != 0 && kind == 2)) {
        minigame::get()->enemy_damage(target, dir);
      } else {
        unknown041(player);
      }
    }
  }
  if (player->unknown41 > 0x18) {
    unknown020 *awa = create_awa();
    if (awa != nullptr) {
      awa->unknown42 = (minigame::get()->unknown024() >> 8 & 0x1f) + 0x10;
      awa->unknown44 = (static_cast<int>(minigame::get()->unknown024() >> 8 & 0x1ff) - 0x100) / 2;
      awa->unknown2c = player->unknown2c + (minigame::get()->unknown024() >> 6 & 0x7fc) - 0x400;
      awa->unknown30 = player->unknown30 + (minigame::get()->unknown024() >> 6 & 0x7fc) - 0x400;
    }
  }
  int x = player->unknown2c;
  int y = player->unknown30;
  if (player->unknown40 == 2) {
    hitMask = 0;
  } else if (hitMask != 0) {
    u8 push = unknown036[hitMask];
    if ((push & 1) != 0) {
      x -= 0x800;
    }
    if ((push & 2) != 0) {
      x += 0x800;
    }
    if ((push & 4) != 0) {
      y -= 0x800;
    }
    if ((push & 8) != 0) {
      y += 0x800;
    }
  }
  if (player->unknown34 != 0) {
    minigame *game = minigame::get();
    u32 buttons = game->unknown10;
    u32 dir = 0;
    if ((buttons & 0x8008000) != 0) {
      dir |= 4;
    }
    if ((buttons & 0x2002000) != 0) {
      dir |= 8;
    }
    dir |= (buttons & 0x1001000) != 0;
    if ((buttons & 0x4004000) != 0) {
      dir |= 2;
    }
    x += unknown039[dir][0] * player->unknown52 / 64;
    y += unknown039[dir][1] * ((0x222UL >> dir & 1) != 0 ? player->unknown50 : player->unknown54) / 64;
    if (player->unknown40 == 0 && player->unknown45 == 0) {
      if (dir != 0) {
        u8 direction = (game->unknown3520 == nullptr ? unknown037 : unknown038)[dir];
        player->unknown46 = direction;
        player->unknown42 = unknown040[direction][0];
        player->unknown28 = unknown040[direction][1];
      }
      if (x < 0x20000 && (game->unknown14 >> 2 & 1) != 0) {
        minigame::get()->playse(0x10);
        player->unknown45 = 1;
        player->unknown47 = 0;
      }
    }
    if (x < 0x20000) {
      x = x < 0x800 ? 0x800 : x;
      x = x > 0xf800 ? 0xf800 : x;
    } else {
      x = x < 0x40800 ? 0x40800 : x;
      x = x > 0x4f800 ? 0x4f800 : x;
    }
    y = y < 0x800 ? 0x800 : y;
    y = y > 0xe800 ? 0xe800 : y;
  }
  if (player->unknown40 == 0) {
    player->unknown44 = 0;
    if (player->unknown56 != 0 && y > player->unknown56 * 256) {
      player->unknown44 = 1;
      y = player->unknown56 * 256;
    }
    if (player->unknown45 != 0) {
      player->unknown45++;
      if (player->unknown45 > 0xf) {
        player->unknown45 = 0;
      }
    }
  }
  player->unknown2c = x;
  player->unknown30 = y;
}

// Inferred role: entry of the table that player_draw indexes with the direction of the player (game rodata 0x7100f75682, 6 bytes per entry); original type name unknown.
struct unknown034 {
  s8 unknown00; // Inferred role: x offset of the attack sprites from the player in pixels; original member name unknown.
  s8 unknown01; // Inferred role: y offset of the attack sprites from the player in pixels; original member name unknown.
  s8 unknown02; // Inferred role: x of the unit step of the attack, per 8 pixels and in 16ths; original member name unknown.
  s8 unknown03; // Inferred role: y of the unit step of the attack; original member name unknown.
  u8 unknown04; // Inferred role: bits 0 to 5 the first frame of the attack (the frame of the attack at rest; the tip is the next one, the shaft the one after), bits 6 and 7 the mirroring flags of
                // draw_obj; original member name unknown.
  s8 unknown05; // Inferred role: palette of the attack sprites minus 0x60 (the body uses 0x60); original member name unknown.
};

// The player and, while it is controlled, the attack: a sprite of the body (blinks while stunned or invincible), then one sprite per 8 pixels of reach along the direction, the first one with
// the tip frame and the others with the shaft frame (0x71006b06a8).
// The values of the table entry are read into locals ahead of the branch on the reach (ruling 2: the game loads the x and y offsets, the frame byte and the palette before the `cbz` on the
// reach, 0x71006b0748 to 0x71006b0778, and keeps the entry address in x12 for the two step loads, which the machine sinking moves into the arm; the other forms make the arm form the address
// again: 265 instructions against the game's 263). Measured: the shift `entry.unknown04 >> 6` written at each of the three calls gives 267 (one shift shared by the inlined draw_obj bodies,
// which then does not fuse into their `eor`); a local `flip` alone gives 265, with locals for the two steps 263 but count and reach in swapped registers (16 differing lines); the position
// words added the other way round (`(position >> 8) + offset`, the load of the position before the load of the offset) give the game's registers. Without the local for the step, the frame
// (`base`) or the flip every variant is 265 instructions and 52 to 96 lines off, without the local for the palette 269, and a `u8` palette loads it with `ldrb` where the game has `ldrsb` (a
// sign-extended int); an entry copied by value (`unknown034 entry = ...`) gives 265.
void player_draw(void *task) {
  // Inferred role: attack sprites of the player (offset, step, frame and palette) for the 9 directions of unknown022::unknown46 (none, up, down, left, up left, down left, right, up right, down
  // right); original name unknown.
  static const unknown034 unknown033[9] = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                           {-0x08, -0x10, 0x00, -0x10, 0x8a, 0x01},
                                           {-0x08, 0x08, 0x00, 0x10, 0x0a, 0x01},
                                           {-0x14, 0x00, -0x10, 0x00, 0x10, 0x01},
                                           {-0x0f, -0x0c, -0x0b, -0x0b, 0x8d, 0x01},
                                           {-0x0f, 0x0c, -0x0b, 0x0b, 0x0d, 0x01},
                                           {0x0c, 0x00, 0x10, 0x00, 0x50, 0x01},
                                           {0x0f, -0x0c, 0x0b, -0x0b, 0xcd, 0x01},
                                           {0x0f, 0x0c, 0x0b, 0x0b, 0x4d, 0x01}};
  unknown022 *player = static_cast<unknown022 *>(task);
  if (player->unknown41 != 0) {
    if ((player->unknown41 & 1) != 0) {
      return;
    }
  } else {
    u16 invincible = player->unknown48;
    if (invincible != 0) {
      if (invincible >= 0x5b) {
        if ((invincible & 1) != 0) {
          return;
        }
      } else if ((invincible & 3) == 3) {
        return;
      }
    }
  }
  if ((player->unknown43 >> 4 & 1) == 0) {
    minigame::get()->draw_obj(0x33, player->unknown42 + 1, player, 0x60);
  } else {
    minigame::get()->draw_obj(0x33, player->unknown42, player, 0x60);
  }
  if (player->unknown40 == 0) {
    int step = player->unknown45;
    const unknown034 &entry = unknown033[player->unknown46];
    int count = step > 7 ? 0xf - step : step;
    int x = (player->unknown2c >> 8) + entry.unknown00;
    int y = (player->unknown30 >> 8) + entry.unknown01;
    u32 base = entry.unknown04 & 0x3f;
    int flip = entry.unknown04 >> 6;
    int palette = entry.unknown05 + 0x60;
    int stepX = entry.unknown02;
    int stepY = entry.unknown03;
    if (count == 0) {
      minigame::get()->draw_obj(0x33, base, x, y, flip, palette);
      player->unknown5c = 0;
      player->unknown5d = 0;
    } else {
      int reach = count * 8;
      int offsetX = stepX * reach / 16;
      int offsetY = stepY * reach / 16;
      player->unknown58 = offsetX;
      player->unknown5a = offsetY;
      player->unknown5c = 0xc;
      player->unknown5d = 0xc;
      minigame::get()->draw_obj(0x33, base + 1, x + offsetX, y + offsetY, flip, palette);
      for (int offset = reach; offset > 0; offset -= 8) {
        minigame::get()->draw_obj(0x33, base + 2, x + stepX * (offset - 8) / 16, y + stepY * (offset - 8) / 16, flip, palette);
      }
    }
  }
}

void enemy_draw(void *task) {
  static const u8 unknown030[] = {0, 0, 0, 1, 2}; // Inferred role: frame of the segments of a tail by index in the tail; original name unknown.
  unknown023 *enemy = static_cast<unknown023 *>(task);
  if ((enemy->unknown45 & 1) != 0) {
    return;
  }
  switch (enemy->unknown71) {
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x39:
  case 0x3a:
  case 0x3b:
  case 0x3c:
  case 0x3f:
    minigame::get()->draw_obj(enemy->unknown71, enemy->unknown42 >> 2 & 1, enemy, 0x50);
    break;
  case 0x3d:
    minigame::get()->draw_obj(0x3d, unknown030[enemy->unknown78], enemy, 0x50);
    break;
  case 0x3e:
    enemy->unknown28 = enemy->unknown42 >> 5 & 1;
    minigame::get()->draw_obj(0x3e, 0, enemy, 0x40);
    break;
  case 0x40:
    break;
  default:
    minigame::get()->draw_obj(enemy->unknown71, 0, enemy, 0x50);
    break;
  }
}

// Decodes the tiles of a sprite sheet resource (0x71006adbd4): a header (unknown002), the palette of the sheet, then the tiles. Without a width the tiles are copied as they are; with one
// every row of the image is a run of 4 byte groups per 8 pixels, each group stored with its bytes reversed (a big-endian word read, as in tora_cell_anime, written with memcpy). The palette
// goes to the slot given by bits 12 to 17 of the first tile ((tile >> 8) & 0x3f0, an entry index). Returns the tile after the last one written. The game reads the header at byte offsets from the blob
// (decision 54). Matched with `int` width and height locals (u16 locals: 11 differing lines of 163, the width load moves behind the destination address; u32: 1) and `src += 4` before `dst += 4` (the
// other order hoists the exit value of the destination pointer instead of the source's, 3 lines). The palette is 16 `_sPalette` entries at byte 0x10 of the blob (decision 54: an offset from the
// header of the blob), copied entry by entry through two walking pointers, the update_palt idiom: the game's 48 `ldrb`/`strb` come out fully unrolled. Indexed entries (`dst[i].unknown00 =
// src[i].unknown00`) give 81 instructions against the game's 163 (not unrolled); memcpy gives a call (71 against 163). A loop over 0x30 bytes from `&unknown65c[index].unknown00` (`bytes[i] =
// header->unknown10[i]`) also matches (163), but it walks past one member through a `u8 *` (decision 46), so it is refused. The tiles start after the palette, at `header->unknown10 + paletteSize`.
u32 minigame::decode_4bpp_sprt(u32 tile, const u8 *res) {
  u32 end = tile;
  if (res != nullptr) {
    const unknown002 *header = reinterpret_cast<const unknown002 *>(res);
    u16 paletteSize = header->unknown02;
    int width = header->unknown04;
    int height = header->unknown06;
    end = height;
    const u8 *src = header->unknown10 + paletteSize;
    u8 *dst = unknown18->unknown100 + ((tile & 0xfff) << 5);
    if (width == 0) {
      memcpy(dst, src, height << 5);
    } else {
      end = height * width >> 6;
      for (int row = 0; row < height; row++) {
        for (int x = 0; x < width; x += 8) {
          u32 word = unknown078(src);
          memcpy(dst, &word, sizeof(word));
          src += 4;
          dst += 4;
        }
      }
    }
    end += tile & 0xfff;
    if (paletteSize != 0) {
      _sPalette *slot = &unknown65c[(tile >> 8) & 0x3f0];
      const _sPalette *colors = reinterpret_cast<const _sPalette *>(header->unknown10);
      for (int i = 0; i < 16; i++) {
        slot->unknown00 = colors->unknown00;
        slot->unknown01 = colors->unknown01;
        slot->unknown02 = colors->unknown02;
        slot++;
        colors++;
      }
    }
  }
  return end;
}

// The game reads the sheet resource at byte offsets (decision 54: a resource blob plus a header offset read from that blob; the casts are that offset arithmetic only): unknown08 of the resource says
// whether frame data follows the tiles, which the frames pointer of the sheet is then computed from. Inlines archive::get_res; the tiles are decoded by decode_4bpp_sprt(u32, const u8 *)
// (0x71006adbd4), whose result (the first tile after the sheet) is returned: phase_title and phase_select chain the sheets with it (0x71006a4184, `add w8, w20, w0, uxth`). The arms read
// unknown04 and unknown06 again instead of sharing a local: a local gives 38 instructions (the unknown06 load is hoisted above the test).
u32 minigame::decode_4bpp_sprt(u32 tile, int sheet) {
  unknown30[sheet].unknown00 = tile;
  const void *blob = m_archive.get_res(sheet);
  const unknown002 *res = static_cast<const unknown002 *>(blob);
  if (res != nullptr) {
    u8 hasFrames = res->unknown08;
    unknown30[sheet].unknown04 = hasFrames;
    if (hasFrames != 0) {
      if (res->unknown04 == 0) {
        unknown30[sheet].unknown08 = reinterpret_cast<const unknown012 *>(res->unknown10 + res->unknown02 + res->unknown06 * 0x20);
      } else {
        unknown30[sheet].unknown08 = reinterpret_cast<const unknown012 *>(res->unknown10 + res->unknown02 + res->unknown04 * res->unknown06 / 2);
      }
    } else {
      unknown30[sheet].unknown08 = nullptr;
    }
  }
  return decode_4bpp_sprt(tile, static_cast<const u8 *>(blob));
}
} // namespace tora
} // namespace minigame
