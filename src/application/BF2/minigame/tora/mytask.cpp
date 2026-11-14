// Original file name unknown: the game calls these functions out of line from minigame_tora.cpp, so they are in another translation unit.
#include "minigame/tora/minigame_tora.h"

#include "gf/gf_allocator.h"

namespace minigame {
namespace tora {

mytask::~mytask() { gf::getAllocator(gf::ALLOCATOR_UNKNOWN_0)->deallocate(unknown00); }

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

} // namespace tora
} // namespace minigame
