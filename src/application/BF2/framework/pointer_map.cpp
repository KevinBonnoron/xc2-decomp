#include "framework/pointer_map.h"

#include "mm/mm_std_base.h"

namespace fw {

PtrMapIterator PtrMapIterator::operator++() {
  ptr_detail::PtrParam *end = unknown00->end();
  if (unknown08 != end) {
    unknown08++;
    while (unknown08 != end && (unknown08->ptr == nullptr || unknown08->id == 0)) {
      unknown08++;
    }
  }

  return *this;
}

PointerMap::~PointerMap() { destroy(); }

void PointerMap::destroy() {
  unknown08.destroy();
  unknown20 = 0;
  unknown24 = 0;
}

PtrMapIterator PointerMap::begin() const {
  PtrMapIterator iterator(&unknown08, unknown08.begin());
  while (iterator.unknown08 != unknown08.end()) {
    if (iterator.unknown08->ptr != nullptr && iterator.unknown08->id != 0) {
      break;
    }

    ++iterator;
  }

  return iterator;
}

PtrMapIterator PointerMap::end() const { return PtrMapIterator(&unknown08, unknown08.end()); }

void PointerMap::setRange(u32 min, u32 max, u32 mask) {
  unknown2c = min;
  unknown30 = max;
  unknown34 = mask;
}

void PointerMap::reserve(mm::mtl::IAllocator *allocator, size_t capacity) {
  unknown08.setAllocator(allocator);
  unknown08.reserve(capacity);
  this->unknown20 = capacity;
}

void PointerMap::clear() {
  unknown08.fill(ptr_detail::PtrParam());
  unknown24 = 0;
}

u32 PointerMap::nextID(u32 id) {
  u32 next = id + 1;
  if (next > unknown30) {
    next = unknown2c;
  } else if (next < unknown2c) {
    next = unknown2c;
  }

  return next;
}

u32 PointerMap::regist(const void *ptr) {
  u32 tries = 0;
  while (++tries < unknown20) {
    unknown28 = nextID(unknown28);
    u32 index = unknown28 % unknown20;
    if (unknown08[index].ptr == nullptr) {
      unknown08[index].ptr = ptr;
      unknown08[index].id = unknown28;
      unknown24++;
      return unknown28;
    }
  }

  return 0;
}

void PointerMap::remove(u32 id) {
  if (unknown20 == 0) {
    return;
  }

  u32 maskedId = id & unknown34;
  u32 index = maskedId % unknown20;
  if (unknown08[index].ptr == nullptr) {
    mm::MMStdBase::mmPrint("[fw] not exist handle:%x", maskedId);
    return;
  }

  unknown08[index] = ptr_detail::PtrParam();
  unknown24--;
}

const void *PointerMap::replace(u32 id, const void *ptr) {
  if (unknown20 == 0) {
    return nullptr;
  }

  u32 index = (id & unknown34) % unknown20;
  if (unknown08[index].ptr == nullptr) {
    return nullptr;
  }

  const void *previous = unknown08[index].ptr;
  unknown08[index].ptr = ptr;
  return previous;
}

void *PointerMap::getPtr(u32 id) const {
  if (id == 0 || unknown20 == 0) {
    return nullptr;
  }

  u32 maskedId = id & unknown34;
  u32 index = maskedId % unknown20;
  if (unknown08[index].id != maskedId) {
    return nullptr;
  }

  return const_cast<void *>(unknown08[index].ptr);
}

u32 PointerMap::getHandle(const void *ptr) const {
  if (ptr != nullptr) {
    for (u32 i = 0; i < unknown08.size(); i++) {
      if (unknown08[i].ptr == ptr) {
        return unknown08[i].id;
      }
    }
  }

  return 0;
}

bool PointerMap::isValid(u32 id) const {
  if (id == 0 || unknown20 == 0) {
    return false;
  }

  u32 maskedId = id & unknown34;
  u32 index = maskedId % unknown20;
  return unknown08[index].id == maskedId;
}

} // namespace fw
