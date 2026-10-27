#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {

class StaticAllocObj {
public:
  static StaticAllocObj *create(u32 size, const char *file, u32 line);
  static void destroy(StaticAllocObj *obj);
  void *sysAlloc(u32 size, u32 alignment, const char *file, u32 line);
  void sysFree(void *ptr);

  u8 *unknown00; // Inferred role: buffer; original member name unknown.
  u32 unknown08; // Inferred role: buffer size; original member name unknown.
  u32 unknown0c; // Inferred role: used size; original member name unknown.
};

static_assert(offsetof(StaticAllocObj, unknown08) == 0x08, "");
static_assert(offsetof(StaticAllocObj, unknown0c) == 0x0c, "");
static_assert(sizeof(StaticAllocObj) == 0x10, "");

} // namespace ptlib
