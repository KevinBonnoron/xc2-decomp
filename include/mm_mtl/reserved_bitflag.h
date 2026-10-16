#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;

class ReservedBitflag {
public:
  void setLocal(u32 index, bool value);
  bool getLocal(u32 index) const;
  void flipLocal(u32 index);
  void clrLocal(u32 index);
  void clrLocal();
  ReservedBitflag();
  ~ReservedBitflag();
  void destroy();
  void initialize(IAllocator *allocator, u32 size);
  bool get(u32 start, u32 last) const;
  void set(u32 start, u32 last, bool value);
  void flip(u32 start, u32 last);
  void clear(u32 start, u32 last);
  bool test(u32 start, u32 last) const;

  u32 *m_element;
  u32 m_size;
  u32 m_elementCount;
  IAllocator *m_allocator;
};

static_assert(offsetof(ReservedBitflag, m_size) == 0x08, "");
static_assert(offsetof(ReservedBitflag, m_elementCount) == 0x0c, "");
static_assert(offsetof(ReservedBitflag, m_allocator) == 0x10, "");

} // namespace mtl
} // namespace mm
