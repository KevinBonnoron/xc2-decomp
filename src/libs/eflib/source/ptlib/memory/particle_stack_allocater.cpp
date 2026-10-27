#include "ptlib/particle_stack_allocater.h"
#include "mm/mm_std_base.h"
#include "ptlib/particle_system.h"

namespace ptlib {

StaticAllocObj *StaticAllocObj::create(u32 size, const char *file, u32 line) {
  StaticAllocObj *obj = static_cast<StaticAllocObj *>(ParticleManager::sysAlloc(size + 0x20, 0x10, file, line));
  efAstMsg("s_pIns", "alloc miss");
  if (obj != nullptr) {
    obj->unknown00 = reinterpret_cast<u8 *>(obj + 1);
    obj->unknown08 = size;
    obj->unknown0c = 0;
  }
  return obj;
}

void StaticAllocObj::destroy(StaticAllocObj *obj) {
  if (obj != nullptr) {
    obj->unknown00 = nullptr;
    obj->unknown08 = 0;
    obj->unknown0c = 0;
    ParticleManager::sysFree(obj);
  }
}

void *StaticAllocObj::sysAlloc(u32 size, u32 alignment, const char *file, u32 line) {
  u32 rem = size % alignment;
  if (rem != 0) {
    size = alignment + size - rem;
  }
  u32 offset = unknown0c;
  u32 end = size + offset;
  void *ptr = nullptr;
  if (end > unknown08) {
#line 78
    MM_ASSERT(0);
    efAstMsg("0", "memory empty");
  } else {
    ptr = unknown00 + offset;
    unknown0c = end;
  }
  return ptr;
}

void StaticAllocObj::sysFree(void *ptr) {}

} // namespace ptlib
