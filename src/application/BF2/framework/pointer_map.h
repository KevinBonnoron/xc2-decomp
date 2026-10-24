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
  PtrMapIterator(const mm::mtl::Array<ptr_detail::PtrParam> *params, ptr_detail::PtrParam *current) : unknown00(params), unknown08(current) {}

  PtrMapIterator operator++();

  const mm::mtl::Array<ptr_detail::PtrParam> *unknown00; // Inferred role: params; original member name unknown.
  ptr_detail::PtrParam *unknown08;                       // Inferred role: current; original member name unknown.
};

class PointerMap {
public:
  PointerMap() : unknown20(0), unknown24(0), unknown28(0), unknown2c(1), unknown30(0xffffffff), unknown34(0xffffffff) {}
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

  mm::mtl::Array<ptr_detail::PtrParam> unknown08; // Inferred role: params; original member name unknown.
  u32 unknown20;                                  // Inferred role: capacity; original member name unknown.
  u32 unknown24;                                  // Inferred role: count; original member name unknown.
  u32 unknown28;                                  // Inferred role: current id; original member name unknown.
  u32 unknown2c;                                  // Inferred role: range min; original member name unknown.
  u32 unknown30;                                  // Inferred role: range max; original member name unknown.
  u32 unknown34;                                  // Inferred role: id mask; original member name unknown.
};

static_assert(offsetof(PointerMap, unknown08) == 0x08, "");
static_assert(offsetof(PointerMap, unknown20) == 0x20, "");
static_assert(offsetof(PointerMap, unknown34) == 0x34, "");
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
