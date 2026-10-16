#pragma once
#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {

class ResourceManager : public ManagerObject, public mm::mtl::PtrSingleton<ResourceManager> {
public:
  static mtl::ALLOC_HANDLE m_hMemoryTemp;

  static mtl::ALLOC_HANDLE getMemSYS();
  static mtl::ALLOC_HANDLE getMemTMP();
  static void setMemTMP(mtl::ALLOC_HANDLE handle);
  static u32 getHash(const char *name);
};

} // namespace fw
