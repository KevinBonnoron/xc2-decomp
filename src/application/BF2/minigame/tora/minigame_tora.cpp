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

void *archive::get_res(int index) {
  u8 *res = reinterpret_cast<u8 *>(unknown00) + ((unknown00[0] + 0x10) & ~0xf);
  if (index > 0) {
    res += unknown00[index];
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

// Inferred role: tests the solid bit (0x80) of the map tile at the pixel column x and the pixel row y, in the rows that start at `rows`; original name unknown. Used four times by
// check_map(_sTask *) (0x71006ae0ec), which holds the four tests as `ldrsb` and `cmp #0; csel`; the helper matches as written, so the repeated test is not written out (P4).
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
        u32 word = src[0] << 24 | src[1] << 16 | src[2] << 8 | src[3];
        memcpy(dst + row * 0x100, &word, sizeof(word));
        src += 4;
      }
    }
  }
}

bool minigame::check_rank() {
  if (unknown33e0 < 0 || unknown33e0 > 4) {
    return false;
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
  for (int i = 0; dst <= last && i < digits; i++) {
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

// The entries are counted by a variable of their own next to the byte offset: with `offset != 0xc00` as the only counter indvars widens the compare (`cmp x8`, the game has `cmp w8`).
// The destination is `*(dst + offset + k)` and the source `src[offset + k]` with the `+ 0` written out (the three channels are spelled alike, P3): `dst[offset + k]` biases both base registers by two
// (`ldurb [x12, #-2]`), and `*(dst + offset)` with `src[offset]` for the first channel gives 40 instructions against the game's 40 with other registers (update_palt, 0x71006ae474).
void minigame::update_palt(int level) {
  u8 *dst = unknown18->unknown20100;
  const u8 *src = unknown65c;
  int offset = 0;
  for (int entry = 0; entry < 0x400; entry++) {
    *(dst + offset + 0) = src[offset + 0] * level / 255;
    *(dst + offset + 1) = src[offset + 1] * level / 255;
    *(dst + offset + 2) = src[offset + 2] * level / 255;
    offset += 3;
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

// The game reads the sheet resource at byte offsets (decision 54: a resource blob plus a header offset read from that blob; the casts are that offset arithmetic only): unknown08 of the resource says
// whether frame data follows the tiles, which the frames pointer of the sheet is then computed from. Inlines archive::get_res; the tiles are decoded by decode_4bpp_sprt(u32, const u8 *)
// (0x71006adbd4). The arms read unknown04 and unknown06 again instead of sharing a local: a local gives 38 instructions (the unknown06 load is hoisted above the test).
void minigame::decode_4bpp_sprt(u32 tile, int sheet) {
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
  decode_4bpp_sprt(tile, static_cast<const u8 *>(blob));
}
} // namespace tora
} // namespace minigame
