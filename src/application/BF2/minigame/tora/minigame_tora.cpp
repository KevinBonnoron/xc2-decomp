// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/minigame/tora/minigame_tora.cpp.
#include "minigame/tora/minigame_tora.h"

#include <math.h>
#include <string.h>

#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_manager.h"
#include "mm_mtl/fixstr.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace minigame {
namespace tora {

void minigame::get_pc_pos(int &x, int &y) {
  x = unknown3528->unknown2c;
  y = unknown3528->unknown30 + unknown3560 / 256;
}

void minigame::get_pc_dxdy(int x, int y, int &dx, int &dy) {
  dx = x - unknown3528->unknown2c;
  dy = y - unknown3528->unknown30 - unknown3560 / 256;
}

void minigame::get_coli_xy(int &x, int &y, _sTask *task) {
  x = task->unknown2c >> 8;
  y = task->unknown30 >> 8;
  x += task->unknown36;
  y += task->unknown38;
}

void minigame::get_pc_atk_xy(int &x, int &y, _sTask *task) {
  x = task->unknown2c >> 8;
  y = task->unknown30 >> 8;
  x += task->unknown58;
  y += task->unknown5a;
  x -= task->unknown5c;
  y -= task->unknown5d;
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

u8 minigame::get_tbox_type(int index) { return unknown1688[index].unknown00; }

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
  unknown002 *res = static_cast<unknown002 *>(unknown20.get_res(index));
  if (res->unknown02 == 0) {
    return nullptr;
  }
  return res->unknown10;
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

int minigame::add_item(int item, void *param) {
  if (unknown1688[item].unknown00 == 2) {
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
    if (unknown1688[unknown3420[i].unknown00].unknown00 == 0) {
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
} // namespace tora
} // namespace minigame

template mm::mtl::PtrSingleton<minigame::tora::minigame>::~PtrSingleton();
