#pragma once
#include <stddef.h>

#include "mm_mtl/array.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

namespace ptr_detail {

struct PtrParam {
  PtrParam() : ptr(nullptr), id(0) {}

  const void *ptr;
  u32 id;
};

} // namespace ptr_detail

class PtrMapIterator {
public:
  PtrMapIterator(const mm::mtl::Array<ptr_detail::PtrParam> *params, ptr_detail::PtrParam *current) : params(params), current(current) {}

  PtrMapIterator operator++();

  const mm::mtl::Array<ptr_detail::PtrParam> *params;
  ptr_detail::PtrParam *current;
};

class PointerMap {
public:
  PointerMap() : capacity(0), count(0), currentId(0), rangeMin(1), rangeMax(0xffffffff), idMask(0xffffffff) {}
  virtual ~PointerMap();

  void destroy();
  PtrMapIterator begin() const;
  PtrMapIterator end() const;
  void setRange(u32 min, u32 max, u32 mask);
  void reserve(mm::mtl::IAllocator *allocator, size_t capacity);
  void clear();
  u32 nextID(u32 id);
  u32 regist(const void *ptr);
  void remove(u32 id);
  const void *replace(u32 id, const void *ptr);
  void *getPtr(u32 id) const;
  u32 getHandle(const void *ptr) const;
  bool isValid(u32 id) const;

  mm::mtl::Array<ptr_detail::PtrParam> params;
  u32 capacity;
  u32 count;
  u32 currentId;
  u32 rangeMin;
  u32 rangeMax;
  u32 idMask;
};

static_assert(offsetof(PointerMap, params) == 0x08, "");
static_assert(offsetof(PointerMap, capacity) == 0x20, "");
static_assert(offsetof(PointerMap, idMask) == 0x34, "");
static_assert(sizeof(PointerMap) == 0x38, "");

template <typename T> struct HandlePtr {
  HandlePtr() : id(0), map(nullptr) {}
  HandlePtr(const HandlePtr &other) : id(other.id), map(other.map) {}

  HandlePtr &operator=(const HandlePtr &other) {
    id = other.id;
    map = other.map;
    return *this;
  }

  T *get() const { return id != 0 ? static_cast<T *>(map->getPtr(id)) : nullptr; }

  u32 id;
  PointerMap *map;
};

} // namespace fw
