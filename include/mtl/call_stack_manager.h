#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "mm_mtl/internal/heap_allocator.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace mm {
namespace mtl {
class HeapAllocator;
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {

// Evidence: CallStackManager::regist allocates 0xa8 bytes, links the node into the list of the manager and fills
// the members below; DlAllocator::getMemInfo1 reads the file and the line, DlAllocator::log_callSTack the trace.
class CallStackInfo : public mm::mtl::IntrusiveListNode<CallStackInfo> {
public:
  CallStackInfo();
  CallStackInfo(void **stack, u32 count, mm::mtl::IAllocator *allocator, const char *file, u32 line);
  int addRef() const;
  int release();
  bool equal(void **stack, u32 count, const char *file, u32 line) const;
  void log();

  u32 unknown10;         // Inferred role: signature, 'CSI1'; original member name unknown.
  mutable int unknown14; // Inferred role: reference count; original member name unknown.
  void *unknown18[16];   // Inferred role: addresses of the call stack, null terminated; original member name unknown.
  const char *unknown98; // Inferred role: file of the allocation; original member name unknown.
  u32 unknowna0;         // Inferred role: line of the allocation; original member name unknown.
  u16 unknowna4;         // Inferred role: number of addresses of the call stack; original member name unknown.
};

static_assert(offsetof(CallStackInfo, unknown10) == 0x10, "");
static_assert(offsetof(CallStackInfo, unknown18) == 0x18, "");
static_assert(offsetof(CallStackInfo, unknown98) == 0x98, "");
static_assert(offsetof(CallStackInfo, unknowna0) == 0xa0, "");
static_assert(offsetof(CallStackInfo, unknowna4) == 0xa4, "");
static_assert(sizeof(CallStackInfo) == 0xa8, "");

class CallStackManager : public mm::mtl::IntrusiveList<CallStackInfo> {
public:
  CallStackInfo *regist(u32 skip, const char *file, u32 line);
  void remove(CallStackInfo *info);
  static void initialize();
  static void finalize();
  static bool validMemoryRange(void *pointer);

  static void *m_buffer;
  static size_t m_bufferSize;
  static mm::mtl::HeapAllocator m_allocator;
  static u32 m_nowAllocate;
  static u32 m_nowAllocateSize;
  static u32 m_maxAllocate;
  static u32 m_maxAllocateSize;
  static int m_maxRefCount;
  static u32 MAX_ALLOCATE_SIZE;

  ml::CriticalSection unknown18; // Inferred role: lock of the list; original member name unknown.
};

static_assert(offsetof(CallStackManager, unknown18) == 0x18, "");
static_assert(sizeof(CallStackManager) == 0x40, "");

} // namespace mtl
