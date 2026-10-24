#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace fw {

class MemHandlebaseAllocator : public mm::mtl::IAllocator {
public:
  MemHandlebaseAllocator();
  MemHandlebaseAllocator(mtl::ALLOC_HANDLE handle);
  void setMemHandle(mtl::ALLOC_HANDLE handle);
  mtl::ALLOC_HANDLE getMemHandle() const;
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;
  const char *getName() const override { return m_name.c_str(); }

  mtl::ALLOC_HANDLE unknown08; // Inferred role: handle; original member name unknown.
  mm::mtl::FixStr<64> m_name;
};

static_assert(offsetof(MemHandlebaseAllocator, unknown08) == 0x08, "");
static_assert(offsetof(MemHandlebaseAllocator, m_name) == 0x0c, "");
static_assert(sizeof(MemHandlebaseAllocator) == 0x50, "");

class Allocator {
public:
  class SysAllocator : public MemHandlebaseAllocator {
  public:
    const char *getName() const override { return "SystemMemoryAllocator"; }
  };

  class DebAllocator : public MemHandlebaseAllocator {
  public:
    const char *getName() const override { return "DebugMemoryAllocator"; }
  };

  class TmpAllocator : public MemHandlebaseAllocator {
  public:
    const char *getName() const override { return "TempMemoryAllocator"; }
  };

  class ProcAllocator : public MemHandlebaseAllocator {
  public:
    const char *getName() const override { return "ProcMemoryAllocator"; }
  };

  static mm::mtl::IAllocator *getSysAllocator();
  static mm::mtl::IAllocator *getDebAllocator();
  static mm::mtl::IAllocator *getTmpAllocator();
  static mm::mtl::IAllocator *getProcAllocator();
  static void setSysMemHandle(mtl::ALLOC_HANDLE handle);
  static void setDebMemHandle(mtl::ALLOC_HANDLE handle);
  static void setTmpMemHandle(mtl::ALLOC_HANDLE handle);
  static void setProcMemHandle(mtl::ALLOC_HANDLE handle);

  static SysAllocator m_SysAllocator;
  static DebAllocator m_DebAllocator;
  static TmpAllocator m_TmpAllocator;
  static ProcAllocator m_ProcAllocator;
};

} // namespace fw
