#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "mtl/call_stack_manager.h"
#include "mtl/mem_allocator.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace mtl {

class DlAllocator : public IMemAllocator {
public:
  // Inferred role: footer written after the memory of every allocation; original type name unknown.
  struct unknown001 {
    u32 unknown00;            // Inferred role: signature of the footer; original member name unknown.
    size_t unknown08;         // Inferred role: offset of the footer from the allocation; original member name unknown.
    CallStackInfo *unknown10; // Inferred role: call stack of the allocation; original member name unknown.
  };

  // Layout of the dlmalloc space handed out by create_mspace_with_base (a game symbol, as are the other mspace_
  // functions); only what the code of this class reads is declared, the original type names are unknown.

  // Inferred role: chunk of dlmalloc, 0x10 bytes before the memory it hands out; original type name unknown.
  struct unknown002 {
    size_t unknown00; // Inferred role: size of the previous chunk when it is free; original member name unknown.
    size_t unknown08; // Inferred role: size of the chunk and its flags (bit 0 previous in use, bit 1 in use); original member name unknown.
  };

  // Inferred role: segment of the memory of a dlmalloc space; original type name unknown.
  struct unknown004 {
    u8 *unknown00;         // Inferred role: base of the segment; original member name unknown.
    size_t unknown08;      // Inferred role: size of the segment; original member name unknown.
    unknown004 *unknown10; // Inferred role: next segment; original member name unknown.
    u32 unknown18;         // Inferred role: flags of the segment; original member name unknown.
  };

  // Inferred role: state of a dlmalloc space (the mspace); original type name unknown.
  struct unknown003 {
    u8 unknown00[0x28];
    unknown002 *unknown28; // Inferred role: top chunk, null while the space is not initialized; original member name unknown.
    u8 unknown30[0x10];
    size_t unknown40; // Inferred role: magic, equal to the one of the parameters of dlmalloc; original member name unknown.
    u8 unknown48[0x330];
    unknown004 unknown378;  // Inferred role: first segment; original member name unknown.
    const char *unknown398; // Inferred role: name of the allocator given by create; original member name unknown.
  };

  static_assert(offsetof(unknown003, unknown28) == 0x28, "");
  static_assert(offsetof(unknown003, unknown40) == 0x40, "");
  static_assert(offsetof(unknown003, unknown378) == 0x378, "");
  static_assert(offsetof(unknown003, unknown398) == 0x398, "");

  DlAllocator();
  ~DlAllocator() override;
  void create(void *buffer, size_t size, const char *name) override;
  void destroy() override;
  AllocatorType getType() const override { return ALLOCATOR_TYPE_PROGRAM; }
  void *allocate(size_t size, size_t alignment) override;
  void *allocate(size_t size, size_t alignment, const char *file, int line) override;
  void deallocate(void *pointer, size_t size) override;
  void *reallocate(void *pointer, size_t size) override;
  void log(MemoryInfo *info, bool isDetail) const override;
  void log_callSTack(void *callStack) const override;
  void checkLeakMemory() override;
  const char *getName() const override;
  bool hasMemory(const void *pointer) const override;
  size_t getAllocSize(const void *pointer) const override;
  void memoryInfo(MemoryInfo *info) const override;
  void getMemImage(MEMIMAGE_HEAD *head) const override;
  bool getMemInfo1(MemoryInfo1 *info, u32 num) const override;
  bool empty() const override { return m_name.c_str()[0] == '\0'; }
  bool valid() const override { return m_name.c_str()[0] != '\0'; }
  bool dummy() const override { return m_name.c_str()[0] != '\0' && unknown30 == nullptr; }

  void swap(DlAllocator &other);
  size_t getAllocSize(size_t size) const;
  void initFooter(void *footer, const char *file, int line, int size);
  void finalizeFooter(void *footer);
  static void *getNewInfo(const void *pointer, size_t &size);

  mm::mtl::FixStr<32> m_name;
  unknown003 *unknown30;      // Inferred role: dlmalloc space of the buffer; original member name unknown.
  void *unknown38;            // Inferred role: buffer given to create; original member name unknown.
  size_t unknown40;           // Inferred role: size of the buffer; original member name unknown.
  CallStackManager unknown48; // Inferred role: call stacks of the allocations; original member name unknown.
};

static_assert(offsetof(DlAllocator, m_name) == 0x08, "");
static_assert(offsetof(DlAllocator, unknown30) == 0x30, "");
static_assert(offsetof(DlAllocator, unknown48) == 0x48, "");
static_assert(sizeof(DlAllocator) == 0x88, "");

} // namespace mtl
