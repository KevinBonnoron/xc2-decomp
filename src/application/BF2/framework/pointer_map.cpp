#include "framework/pointer_map.h"

#include "mm/mm_std_base.h"

namespace fw {

PtrMapIterator PtrMapIterator::operator++() {
  ptr_detail::PtrParam *end = params->end();
  if (current != end) {
    current++;
    while (current != end && (current->ptr == nullptr || current->id == 0)) {
      current++;
    }
  }

  return *this;
}

PointerMap::~PointerMap() { destroy(); }

void PointerMap::destroy() {
  params.destroy();
  capacity = 0;
  count = 0;
}

PtrMapIterator PointerMap::begin() const {
  PtrMapIterator iterator(&params, params.begin());
  while (iterator.current != params.end()) {
    if (iterator.current->ptr != nullptr && iterator.current->id != 0) {
      break;
    }

    ++iterator;
  }

  return iterator;
}

PtrMapIterator PointerMap::end() const { return PtrMapIterator(&params, params.end()); }

void PointerMap::setRange(u32 min, u32 max, u32 mask) {
  rangeMin = min;
  rangeMax = max;
  idMask = mask;
}

void PointerMap::reserve(mm::mtl::IAllocator *allocator, size_t capacity) {
  params.setAllocator(allocator);
  params.reserve(capacity);
  this->capacity = capacity;
}

void PointerMap::clear() {
  params.fill(ptr_detail::PtrParam());
  count = 0;
}

u32 PointerMap::nextID(u32 id) {
  u32 next = id + 1;
  if (next > rangeMax) {
    next = rangeMin;
  } else if (next < rangeMin) {
    next = rangeMin;
  }

  return next;
}

u32 PointerMap::regist(const void *ptr) {
  u32 tries = 0;
  while (++tries < capacity) {
    currentId = nextID(currentId);
    u32 index = currentId % capacity;
    if (params[index].ptr == nullptr) {
      params[index].ptr = ptr;
      params[index].id = currentId;
      count++;
      return currentId;
    }
  }

  return 0;
}

void PointerMap::remove(u32 id) {
  if (capacity == 0) {
    return;
  }

  u32 maskedId = id & idMask;
  u32 index = maskedId % capacity;
  if (params[index].ptr == nullptr) {
    mm::MMStdBase::mmPrint("[fw] not exist handle:%x", maskedId);
    return;
  }

  params[index] = ptr_detail::PtrParam();
  count--;
}

const void *PointerMap::replace(u32 id, const void *ptr) {
  if (capacity == 0) {
    return nullptr;
  }

  u32 index = (id & idMask) % capacity;
  if (params[index].ptr == nullptr) {
    return nullptr;
  }

  const void *previous = params[index].ptr;
  params[index].ptr = ptr;
  return previous;
}

void *PointerMap::getPtr(u32 id) const {
  if (id == 0 || capacity == 0) {
    return nullptr;
  }

  u32 maskedId = id & idMask;
  u32 index = maskedId % capacity;
  if (params[index].id != maskedId) {
    return nullptr;
  }

  return const_cast<void *>(params[index].ptr);
}

u32 PointerMap::getHandle(const void *ptr) const {
  if (ptr != nullptr) {
    for (u32 i = 0; i < params.size(); i++) {
      if (params[i].ptr == ptr) {
        return params[i].id;
      }
    }
  }

  return 0;
}

bool PointerMap::isValid(u32 id) const {
  if (id == 0 || capacity == 0) {
    return false;
  }

  u32 maskedId = id & idMask;
  u32 index = maskedId % capacity;
  return params[index].id == maskedId;
}

} // namespace fw
