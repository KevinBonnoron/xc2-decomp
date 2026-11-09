// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/minigame/tora/minigame_tora.cpp.
#include "minigame/tora/minigame_tora.h"

#include "gf/gf_allocator.h"

namespace minigame {
namespace tora {

mytask::~mytask() { gf::getAllocator(gf::ALLOCATOR_DEFAULT)->deallocate(unknown00); }

void *mytask::entry() { return entryEnd(); }

void *mytask::entryNext(void *task) {
  _sTask *node = unknown10;
  if (node == nullptr) {
    return nullptr;
  }
  _sTask *prev = static_cast<_sTask *>(task);
  unknown10 = node->unknown00;
  node->unknown08 = prev;
  if (prev == nullptr) {
    node->unknown00 = nullptr;
    unknown18 = node;
    unknown20 = node;
    return node;
  }
  node->unknown00 = prev->unknown00;
  if (node->unknown00 == nullptr) {
    unknown20 = node;
  } else {
    node->unknown00->unknown08 = node;
  }
  prev->unknown00 = node;
  return node;
}

void *mytask::entryTop() { return entryPrev(unknown18); }

void *mytask::entryPrev(void *task) {
  _sTask *node = unknown10;
  if (node == nullptr) {
    return nullptr;
  }
  _sTask *next = static_cast<_sTask *>(task);
  unknown10 = node->unknown00;
  node->unknown00 = next;
  if (next == nullptr) {
    node->unknown08 = nullptr;
    unknown18 = node;
    unknown20 = node;
    return node;
  }
  node->unknown08 = next->unknown08;
  if (node->unknown08 == nullptr) {
    unknown18 = node;
  } else {
    node->unknown08->unknown00 = node;
  }
  next->unknown08 = node;
  return node;
}

void *mytask::entryEnd() { return entryNext(unknown20); }

void mytask::remove(void *task) {
  _sTask *entry = static_cast<_sTask *>(task);
  if (entry == unknown28) {
    unknown28 = entry->unknown00;
  }
  if (entry->unknown00 == nullptr) {
    unknown20 = entry->unknown08;
  } else {
    entry->unknown00->unknown08 = entry->unknown08;
  }
  if (entry->unknown08 == nullptr) {
    unknown18 = entry->unknown00;
  } else {
    entry->unknown08->unknown00 = entry->unknown00;
  }
  entry->unknown00 = unknown10;
  unknown10 = entry;
  entry->unknown10 = nullptr;
  entry->unknown18 = nullptr;
}

void mytask::executeMove() {
  _sTask *entry = unknown18;
  while (entry != nullptr) {
    _sTask *next = entry->unknown00;
    unknown28 = next;
    if (entry->unknown10 != nullptr) {
      entry->unknown10(entry);
      next = unknown28;
    }
    entry = next;
  }
}

void mytask::executeDraw() {
  _sTask *entry = unknown18;
  while (entry != nullptr) {
    _sTask *next = entry->unknown00;
    unknown28 = next;
    if (entry->unknown18 != nullptr) {
      entry->unknown18(entry);
      next = unknown28;
    }
    entry = next;
  }
}

void *mytask::enum_next(void *task) {
  if (task == nullptr) {
    return unknown18;
  }
  return static_cast<_sTask *>(task)->unknown00;
}

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

void minigame::clip_screen(int &x, int &y, int &w, int &h, int &ox, int &oy) {
  ox = x;
  if (x < 0) {
    x = -x;
    ox = 0;
  } else {
    if (w + x > 320) {
      w = 320 - x;
    }
    x = 0;
  }
  oy = y;
  if (y < 0) {
    y = -y;
    oy = 0;
  } else {
    if (h + y > 240) {
      h = 240 - y;
    }
    y = 0;
  }
}

} // namespace tora
} // namespace minigame

template mm::mtl::PtrSingleton<minigame::tora::minigame>::~PtrSingleton();
