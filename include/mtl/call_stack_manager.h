#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace mtl {

class CallStackInfo;

class CallStackManager : public mm::mtl::IntrusiveList<CallStackInfo> {
public:
  CallStackInfo *regist(u32 skip, const char *file, u32 line);
  void remove(CallStackInfo *info);
  static void initialize();
  static void finalize();
  static bool validMemoryRange(void *pointer);

  ml::CriticalSection unknown18; // Inferred role: lock of the list; original member name unknown.
};

static_assert(offsetof(CallStackManager, unknown18) == 0x18, "");
static_assert(sizeof(CallStackManager) == 0x40, "");

} // namespace mtl
