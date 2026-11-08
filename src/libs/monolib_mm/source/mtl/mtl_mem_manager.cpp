#include <stddef.h>
#include <stdlib.h>

#include "ml/critical_section.h"
#include "ml/stack_trace.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/heap_allocator.h"
#include "mtl/alloc_handle.h"
#include "mtl/allocator_wrapper.h"
#include "mtl/asset_allocator.h"
#include "mtl/call_stack_manager.h"
#include "mtl/dl_allocator.h"
#include "mtl/dlmalloc.h"
#include "mtl/mem_allocator.h"
#include "mtl/mem_handlebase_allocator.h"
#include "mtl/mem_manager.h"
#include "mtl/mem_manager_region.h"
#include "mtl/null_allocator.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {

AllocatorWrapper::AllocatorWrapper() : m_allocator(nullptr), m_buffer(nullptr), m_capacity(0), unknown18(0) {}

AllocatorWrapper::~AllocatorWrapper() {}

void AllocatorWrapper::init(IMemAllocator *allocator, void *buffer, size_t size, const char *name) {
  m_allocator = allocator;
  m_buffer = buffer;
  m_capacity = size;
  unknown18 = 0;
  m_name = name != nullptr ? name : "no name";
  if (allocator != nullptr) {
    allocator->create(buffer, size, name);
  }
}

const char *AllocatorWrapper::getName() const { return m_name.c_str(); }

void *AllocatorWrapper::allocate(size_t size) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  void *pointer = m_allocator->allocate(size, 16);
  if (pointer != nullptr) {
    unknown18++;
  }
  return pointer;
}

void *AllocatorWrapper::allocate(size_t size, size_t alignment, const char *file, int line) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  void *pointer = m_allocator->allocate(size, alignment, file, line);
  if (pointer != nullptr) {
    unknown18++;
  }
  return pointer;
}

void *AllocatorWrapper::allocate_tail(size_t size, size_t alignment, const char *file, int line) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  void *pointer = m_allocator->allocate_tail(size, alignment, file, line);
  if (pointer != nullptr) {
    unknown18++;
  }
  return pointer;
}

void AllocatorWrapper::deallocate(void *pointer, size_t size) {
  if (pointer != nullptr && m_allocator != nullptr) {
    m_allocator->deallocate(pointer, size);
    unknown18--;
  }
}

void *AllocatorWrapper::reallocate(void *pointer, size_t size) {
  if (m_allocator == nullptr) {
    return nullptr;
  }
  return m_allocator->reallocate(pointer, size);
}

void AllocatorWrapper::log(MemoryInfo *info, bool isDetail) const {
  if (m_allocator != nullptr) {
    m_allocator->log(info, isDetail);
  }
}

void AllocatorWrapper::log_callSTack(void *callStack) const {
  if (m_allocator != nullptr) {
    m_allocator->log_callSTack(callStack);
  }
}

void AllocatorWrapper::checkLeakMemory() {
  if (m_allocator != nullptr) {
    m_allocator->checkLeakMemory();
  }
}

bool AllocatorWrapper::hasMemory(const void *pointer) const {
  if (m_allocator == nullptr) {
    return false;
  }
  return m_allocator->hasMemory(pointer);
}

size_t AllocatorWrapper::getAllocSize(const void *pointer) const {
  if (m_allocator == nullptr) {
    return 0;
  }
  return m_allocator->getAllocSize(pointer);
}

bool AllocatorWrapper::isArea(const void *pointer) const {
  if (m_allocator == nullptr) {
    return false;
  }
  if (pointer < m_buffer) {
    return false;
  }
  return m_capacity + reinterpret_cast<size_t>(m_buffer) > reinterpret_cast<size_t>(pointer);
}

size_t AllocatorWrapper::getCapacity() const { return m_capacity; }

void AllocatorWrapper::memoryInfo(MemoryInfo *info) const {
  if (m_allocator != nullptr) {
    m_allocator->memoryInfo(info);
  }
}

void AllocatorWrapper::getMemImage(MEMIMAGE_HEAD *head) const {
  if (m_allocator != nullptr) {
    m_allocator->getMemImage(head);
  }
}

bool AllocatorWrapper::getMemInfo1(MemoryInfo1 *info, u32 num) const {
  if (m_allocator == nullptr) {
    return false;
  }
  return m_allocator->getMemInfo1(info, num);
}

bool AllocatorWrapper::valid() const {
  if (m_allocator == nullptr) {
    return false;
  }
  return m_allocator->valid();
}

bool AllocatorWrapper::empty() const { return m_allocator == nullptr; }

bool AllocatorWrapper::dummy() const {
  if (m_allocator == nullptr) {
    return true;
  }
  return m_allocator->dummy();
}

void AllocatorWrapper::clear() {}

void NullAllocator::create(void *buffer, size_t size, const char *name) { m_name = name; }

void NullAllocator::destroy() {}

void *IMemAllocator::allocate_tail(size_t size, size_t alignment, const char *file, int line) { return nullptr; }

void IMemAllocator::log_callSTack(void *callStack) const {}

void IMemAllocator::checkLeakMemory() {}

AllocatorType NullAllocator::getType() const { return static_cast<AllocatorType>(0); }

void *NullAllocator::allocate(size_t size, size_t alignment) { return nullptr; }

void *NullAllocator::allocate(size_t size, size_t alignment, const char *file, int line) { return nullptr; }

void *NullAllocator::allocate_tail(size_t size, size_t alignment, const char *file, int line) { return nullptr; }

void NullAllocator::deallocate(void *pointer, size_t size) {}

void *NullAllocator::reallocate(void *pointer, size_t size) { return nullptr; }

void NullAllocator::log(MemoryInfo *info, bool isDetail) const {}

const char *NullAllocator::getName() const { return m_name.c_str(); }

bool NullAllocator::hasMemory(const void *pointer) const { return false; }

size_t NullAllocator::getAllocSize(const void *pointer) const { return 0; }

void NullAllocator::memoryInfo(MemoryInfo *info) const {}

void NullAllocator::getMemImage(MEMIMAGE_HEAD *head) const {}

bool NullAllocator::getMemInfo1(MemoryInfo1 *info, u32 num) const { return false; }

bool NullAllocator::empty() const { return m_name.c_str()[0] == '\0'; }

bool NullAllocator::valid() const { return m_name.c_str()[0] != '\0'; }

bool NullAllocator::dummy() const { return m_name.c_str()[0] != '\0'; }

u32 NullAllocator::getMemSize(const void *pointer) const { return 0; }

void MemManager::Region::initialize(IMemAllocator *allocator, void *buffer, size_t size, const char *name, bool isSection, bool isCritical) {
  m_blockSize = 1;
  if (isCritical) {
    unknownb0 |= UNKNOWN001_UNKNOWN_1;
  } else {
    unknownb0 &= ~UNKNOWN001_UNKNOWN_1;
  }
  if (isSection) {
    unknownb0 |= UNKNOWN001_UNKNOWN_0;
  } else {
    unknownb0 &= ~UNKNOWN001_UNKNOWN_0;
  }
  m_parent = ALLOC_HANDLE();
  unknown68 = ALLOC_HANDLE();
  m_topAdr = reinterpret_cast<u64>(buffer);
  unknown00 = allocator;
  unknown08 = buffer;
  unknownb0 |= UNKNOWN001_UNKNOWN_3 | UNKNOWN001_UNKNOWN_4 | UNKNOWN001_UNKNOWN_5;
  unknown10 = size;
  m_allocs = 0;
  m_name = name != nullptr ? name : "no name";
  if (allocator != nullptr) {
    allocator->create(buffer, size, name);
  }
}

void MemManager::Region::addChild(ALLOC_HANDLE handle) { unknownb4.push_back(handle); }

void MemManager::Region::removeChild(ALLOC_HANDLE handle) {
  mm::mtl::FixedList<ALLOC_HANDLE, 128>::iterator it = mm::mtl::find(unknownb4.begin(), unknownb4.end(), handle);
  if (it != unknownb4.end()) {
    unknownb4.erase(it);
  }
}

void MemManager::Region::checkLeakMemory() {
  if (m_name.c_str()[0] != '\0' && unknown00 != nullptr) {
    unknown00->checkLeakMemory();
  }
}

bool MemManager::Region::hasMemory(const void *pointer) const {
  if (unknown00 == nullptr) {
    return false;
  }
  return unknown00->hasMemory(pointer);
}

bool MemManager::Region::getMemInfo1(MemoryInfo1 *info, u32 num) const {
  ml::CSNC lock(unknown80);
  if (unknown00 == nullptr) {
    return false;
  }
  return unknown00->getMemInfo1(info, num);
}

void *MemManager::Region::allocate(size_t size, bool isBack) {
  if (m_blockSize > 1) {
    size = (size + m_blockSize - 1) / m_blockSize * m_blockSize;
  }
  if (!(unknownb0 & UNKNOWN001_UNKNOWN_1) || isBack) {
    if (unknown00 == nullptr) {
      return nullptr;
    }
    void *pointer = unknown00->allocate(size, 16);
    if (pointer != nullptr) {
      m_allocs++;
    }
    return pointer;
  }
  ml::CSNC lock(unknown80);
  if (unknown00 == nullptr) {
    return nullptr;
  }
  void *pointer = unknown00->allocate(size, 16);
  if (pointer != nullptr) {
    m_allocs++;
  }
  return pointer;
}

void *MemManager::Region::allocate(size_t size, size_t alignment, bool isBack, const char *file, int line) {
  if (m_blockSize > 1) {
    size = (size + m_blockSize - 1) / m_blockSize * m_blockSize;
  }
  if (!(unknownb0 & UNKNOWN001_UNKNOWN_1) || isBack) {
    if (unknown00 == nullptr) {
      return nullptr;
    }
    void *pointer = unknown00->allocate(size, alignment, file, line);
    if (pointer != nullptr) {
      m_allocs++;
    }
    return pointer;
  }
  ml::CSNC lock(unknown80);
  if (unknown00 == nullptr) {
    return nullptr;
  }
  void *pointer = unknown00->allocate(size, alignment, file, line);
  if (pointer != nullptr) {
    m_allocs++;
  }
  return pointer;
}

void *MemManager::Region::allocate_tail(size_t size, size_t alignment, bool isBack, const char *file, int line) {
  if (m_blockSize > 1) {
    size = (size + m_blockSize - 1) / m_blockSize * m_blockSize;
  }
  if (!(unknownb0 & UNKNOWN001_UNKNOWN_1) || isBack) {
    if (unknown00 == nullptr) {
      return nullptr;
    }
    void *pointer = unknown00->allocate(size, alignment, file, line);
    if (pointer != nullptr) {
      m_allocs++;
    }
    return pointer;
  }
  ml::CSNC lock(unknown80);
  if (unknown00 == nullptr) {
    return nullptr;
  }
  void *pointer = unknown00->allocate_tail(size, alignment, file, line);
  if (pointer != nullptr) {
    m_allocs++;
  }
  return pointer;
}

void MemManager::Region::alloc(size_t size) {
  if (unknown00 != nullptr && unknown00->allocate(size, 16) != nullptr) {
    m_allocs++;
  }
}

void MemManager::Region::alloc(size_t size, size_t alignment, const char *file, int line) {
  if (unknown00 != nullptr && unknown00->allocate(size, alignment, file, line) != nullptr) {
    m_allocs++;
  }
}

void MemManager::Region::alloc_tail(size_t size, size_t alignment, const char *file, int line) {
  if (unknown00 != nullptr && unknown00->allocate_tail(size, alignment, file, line) != nullptr) {
    m_allocs++;
  }
}

void MemManager::Region::deallocate(void *pointer, size_t size, bool isBack) {
  if (!(unknownb0 & UNKNOWN001_UNKNOWN_1) || isBack) {
    if (pointer != nullptr && unknown00 != nullptr) {
      unknown00->deallocate(pointer, 0);
      m_allocs--;
    }
  } else {
    ml::CSNC lock(unknown80);
    if (pointer != nullptr && unknown00 != nullptr) {
      unknown00->deallocate(pointer, 0);
      m_allocs--;
    }
  }
}

void *MemManager::Region::reallocate(void *pointer, size_t size, bool isBack) {
  if (!(unknownb0 & UNKNOWN001_UNKNOWN_1) || isBack) {
    if (unknown00 == nullptr) {
      return nullptr;
    }
    return unknown00->reallocate(pointer, size);
  }
  ml::CSNC lock(unknown80);
  if (unknown00 == nullptr) {
    return nullptr;
  }
  return unknown00->reallocate(pointer, size);
}

size_t MemManager::Region::maxAllocSize() {
  ml::CSNC lock(unknown80);
  MemoryInfo info;
  memoryInfo(&info);
  size_t size = info.unknown18;
  if (size > 0x38) {
    size -= 0x38;
  }
  return size;
}

bool MemManager::Region::empty() const { return unknown00 == nullptr; }

void MemManager::Region::memoryInfo(MemoryInfo *info) {
  ml::CSNC lock(unknown80);
  if (unknown00 != nullptr) {
    unknown00->memoryInfo(info);
  }
  info->unknown30 = m_topAdr;
}

size_t MemManager::Region::getAllocSize(void *pointer) {
  if (unknown00 == nullptr) {
    return 0;
  }
  return unknown00->getAllocSize(pointer);
}

void MemManager::Region::log_callSTack(void *callStack) {
  if (m_name.c_str()[0] != '\0' && unknown00 != nullptr) {
    unknown00->log_callSTack(callStack);
  }
}

void MemManager::Region::log(MemoryInfo *info, bool isDetail) {
  if (m_name.c_str()[0] != '\0' && unknown00 != nullptr) {
    unknown00->log(info, isDetail);
  }
}

void MemManager::Region::getMemImage(MEMIMAGE_HEAD *head) {
  ml::CSNC lock(unknown80);
  if (unknown00 != nullptr) {
    unknown00->getMemImage(head);
  }
}

u64 MemManager::Region::getTopAdr() const { return m_topAdr; }

u32 MemManager::Region::getAllocs() const { return m_allocs; }

void MemManager::tchk() {}

void *MemManager::getAllocatorList() { return &_existHandle; }

bool MemManager::isCollectCallStack() { return m_collectCallstack; }

bool MemManager::isInitialized() { return s_bInitialize; }

void MemManager::setCollectCallStack(bool collect) { m_collectCallstack = collect; }

ALLOC_HANDLE MemManager::create(void *buffer, size_t size, const char *name, bool isCritical) { return create(buffer, size, name, isCritical, ALLOCATOR_TYPE_PROGRAM); }

ALLOC_HANDLE MemManager::create(ALLOC_HANDLE parent, size_t size, const char *name, bool isCritical, const char *file, int line) {
  return create(parent, size, name, isCritical, ALLOCATOR_TYPE_PROGRAM, 0x10, file, line);
}

void MemManager::deallocate(void *pointer, size_t size, bool isBack) {
  if (s_bInitialize) {
    deallocate_section(pointer, size, isBack);
  }
}

bool MemManager::isArea(ALLOC_HANDLE handle, const void *pointer) { return getArea(handle, pointer) != nullptr; }

ALLOC_HANDLE MemManager::getParent(ALLOC_HANDLE handle) {
  Region *region = s_ptrMap.unknown003(handle);
  if (region != nullptr) {
    return region->m_parent;
  }
  return ALLOC_HANDLE();
}

void MemManager::setHaltAlloc(ALLOC_HANDLE handle, bool halt) {
  Region *region = s_ptrMap.unknown003(handle);
  if (region != nullptr) {
    region->unknownb0 = !halt ? region->unknownb0 & ~Region::UNKNOWN001_UNKNOWN_3 : region->unknownb0 | Region::UNKNOWN001_UNKNOWN_3;
  }
}

void MemManager::setWarnAlloc(ALLOC_HANDLE handle, bool warn) {
  Region *region = s_ptrMap.unknown003(handle);
  if (region != nullptr) {
    region->unknownb0 = !warn ? region->unknownb0 & ~Region::UNKNOWN001_UNKNOWN_4 : region->unknownb0 | Region::UNKNOWN001_UNKNOWN_4;
  }
}

void MemManager::setLogAlloc(ALLOC_HANDLE handle, bool log) {
  Region *region = s_ptrMap.unknown003(handle);
  if (region != nullptr) {
    region->unknownb0 = !log ? region->unknownb0 & ~Region::UNKNOWN001_UNKNOWN_5 : region->unknownb0 | Region::UNKNOWN001_UNKNOWN_5;
  }
}

// Inferred role: heap of the memory manager records (named "MemManagerHeap" at creation); original name unknown.
static mm::mtl::HeapAllocator unknown003;

void MemManager::destroyAllocator(AllocatorType type, IMemAllocator *allocator) {
  if (allocator != nullptr) {
    allocator->~IMemAllocator();
    unknown003.deallocate(allocator);
  }
}

void AllocatorWrapper::destroy() {
  if (m_allocator != nullptr) {
    MemManager::destroyAllocator(m_allocator->getType(), m_allocator);
    m_capacity = 0;
    unknown18 = 0;
    m_allocator = nullptr;
    m_buffer = nullptr;
  }
}

void MemManager::log_section(ALLOC_HANDLE handle, bool isDetail, MemoryInfo *info) {
  Region *region = s_ptrMap.unknown003(handle);
  if (region != nullptr) {
    region->log(info, isDetail);
  }
}

bool MemManager::valid_section(const ALLOC_HANDLE &handle, bool) {
  Region *region = s_ptrMap.unknown003(handle);
  if (region != nullptr && region->unknown00 != nullptr && region->unknown00->valid()) {
    MemoryInfo info;
    region->memoryInfo(&info);
    return true;
  }
  return false;
}

// Inferred role: parameters of dlmalloc (mparams); original type name unknown.
struct unknown006 {
  size_t unknown00; // Inferred role: magic of the dlmalloc spaces; original member name unknown.
  size_t unknown08; // Inferred role: page size; original member name unknown.
  size_t unknown10; // Inferred role: granularity; original member name unknown.
  size_t unknown18; // Inferred role: threshold of the mmap; original member name unknown.
  size_t unknown20; // Inferred role: threshold of the trim; original member name unknown.
  u32 unknown28;    // Inferred role: default flags; original member name unknown.
};

static_assert(sizeof(unknown006) == 0x30, "");

// Inferred role: parameters of dlmalloc (static struct malloc_params mparams in dlmalloc 2.8); original name unknown.
static unknown006 unknown007;

// Inferred role: offset of the footer from the memory handed out by dlmalloc: from the size of its chunk when the
// chunk is in use (the footer is the end of the memory), the size of the footer backwards otherwise; original name unknown.
static size_t unknown008(size_t memory) {
  DlAllocator::unknown002 *chunk = reinterpret_cast<DlAllocator::unknown002 *>(memory - sizeof(DlAllocator::unknown002));
  if ((chunk->unknown08 & 3) == 1) {
    return -sizeof(DlAllocator::unknown001);
  }
  return (chunk->unknown08 - sizeof(DlAllocator::unknown002) - sizeof(DlAllocator::unknown001)) & ~static_cast<size_t>(7);
}

// Inferred macro name; macros leave no trace in the binary. Initialization of the parameters of dlmalloc
// (ensure_initialization of dlmalloc 2.8, whose init_mparams the game inlines in every function that uses them).
#define DL_ALLOCATOR_ENSURE_INITIALIZATION()                                                                                                                                                           \
  do {                                                                                                                                                                                                 \
    if (unknown007.unknown00 == 0) {                                                                                                                                                                   \
      unknown007.unknown10 = 0x10000;                                                                                                                                                                  \
      unknown007.unknown08 = 0x1000;                                                                                                                                                                   \
      unknown007.unknown18 = ~static_cast<size_t>(0);                                                                                                                                                  \
      unknown007.unknown20 = 0x200000;                                                                                                                                                                 \
      unknown007.unknown28 = 4;                                                                                                                                                                        \
      /* The only volatile of the sources: dlmalloc 2.8 init_mparams writes the magic that way, */                                                                                                     \
      /* (*(volatile size_t *)(&(mparams.magic))) = magic; */                                                                                                                                          \
      (*(volatile size_t *)(&unknown007.unknown00)) = 0x520e9848;                                                                                                                                      \
    }                                                                                                                                                                                                  \
  } while (0)

// Inferred role: first chunk of the segment starting at base (align_as_chunk); original name unknown.
static DlAllocator::unknown002 *unknown009(u8 *base) {
  size_t address = reinterpret_cast<size_t>(base + sizeof(DlAllocator::unknown002));
  size_t offset = 0;
  if ((address & 0xf) != 0) {
    offset = (0x10 - (address & 0xf)) & 0xf;
  }
  return reinterpret_cast<DlAllocator::unknown002 *>(base + offset);
}

// Inferred role: chunk following the given one; original name unknown.
static DlAllocator::unknown002 *unknown010(DlAllocator::unknown002 *chunk) {
  return reinterpret_cast<DlAllocator::unknown002 *>(reinterpret_cast<u8 *>(chunk) + (chunk->unknown08 & ~static_cast<size_t>(7)));
}

// Inferred role: memory handed out for the chunk; original name unknown.
static void *unknown011(DlAllocator::unknown002 *chunk) { return chunk + 1; }

// Inferred role: offset of the footer from the memory of the chunk; original name unknown.
static size_t unknown012(const DlAllocator::unknown002 *chunk) { return (chunk->unknown08 - sizeof(DlAllocator::unknown002) - sizeof(DlAllocator::unknown001)) & ~static_cast<size_t>(7); }

// Inferred role: the chunk is in use (is_inuse); original name unknown.
static bool unknown013(const DlAllocator::unknown002 *chunk) { return (chunk->unknown08 & 3) != 1; }

// Inferred role: footer of the chunk; original name unknown.
static DlAllocator::unknown001 *unknown014(DlAllocator::unknown002 *chunk) { return reinterpret_cast<DlAllocator::unknown001 *>(static_cast<u8 *>(unknown011(chunk)) + unknown012(chunk)); }

size_t getMemoryChunkSize(void *pointer) {
  size_t size = 0;
  if (pointer != nullptr) {
    DlAllocator::unknown002 *chunk = reinterpret_cast<DlAllocator::unknown002 *>(static_cast<u8 *>(pointer) - sizeof(DlAllocator::unknown002));
    if (unknown013(chunk)) {
      size = (chunk->unknown08 - sizeof(DlAllocator::unknown002)) & ~static_cast<size_t>(7);
    }
  }
  return size;
}

void DlAllocator::create(void *buffer, size_t size, const char *name) {
  m_name = name;
  unknown30 = nullptr;
  unknown38 = buffer;
  unknown40 = size;
  if (buffer != nullptr) {
    unknown30 = static_cast<unknown003 *>(create_mspace_with_base(buffer, size));
    if (unknown30 != nullptr && unknown30->unknown40 == unknown007.unknown00) {
      unknown30->unknown398 = name != nullptr ? name : "no name";
    }
  }
}

void DlAllocator::swap(DlAllocator &other) {
  mm::mtl::FixStr<32> name(m_name);
  m_name = other.m_name;
  other.m_name = name;
  void *buffer = unknown38;
  unknown38 = other.unknown38;
  other.unknown38 = buffer;
  unknown003 *space = unknown30;
  unknown30 = other.unknown30;
  other.unknown30 = space;
  size_t size = unknown40;
  unknown40 = other.unknown40;
  other.unknown40 = size;
}

DlAllocator::DlAllocator() : unknown30(nullptr), unknown38(nullptr), unknown40(0) {}

DlAllocator::~DlAllocator() {}

void DlAllocator::destroy() {
  unknown38 = nullptr;
  unknown40 = 0;
  unknown30 = nullptr;
}

const char *DlAllocator::getName() const { return m_name.c_str(); }

void *DlAllocator::allocate(size_t size, size_t alignment) { return allocate(size, 16, "no name", 0); }

size_t DlAllocator::getAllocSize(size_t size) const {
  size_t total = size + sizeof(unknown001);
  if ((total & 0xf) != 0) {
    total = total + 16 - (total & 0xf);
  }
  return total;
}

void DlAllocator::finalizeFooter(void *footer) {
  unknown001 *info = static_cast<unknown001 *>(footer);
  if (info != nullptr && info->unknown10 != nullptr) {
    unknown48.remove(info->unknown10);
    info->unknown10 = nullptr;
  }
}

void DlAllocator::initFooter(void *footer, const char *file, int line, int size) {
  unknown001 *info = static_cast<unknown001 *>(footer);
  if (info != nullptr) {
    int length = file != nullptr ? __builtin_strlen(file) : 0;
    int separator = -1;
    for (int i = 0; i < length; i++) {
      if (file[i] == '\\' || file[i] == '/') {
        separator = i;
      }
    }
    info->unknown00 = 0x44434241;
    info->unknown08 = size;
    if (MemManager::isCollectCallStack()) {
      info->unknown10 = unknown48.regist(4, separator < 0 ? file : file + (separator + 1), line);
    } else {
      info->unknown10 = nullptr;
    }
  }
}

CallStackInfo::CallStackInfo() : unknown10(0x43534931), unknown14(0), unknown98("noname"), unknowna0(0), unknowna4(0) {}

CallStackInfo::CallStackInfo(void **stack, u32 count, mm::mtl::IAllocator *allocator, const char *file, u32 line) : unknown10(0x43534931), unknown14(0), unknowna0(line), unknowna4(count) {
  u32 length = count < 16 ? count : 15;
  unknown98 = file == nullptr ? "noname" : file;
  for (u32 i = 0; i < length; i++) {
    unknown18[i] = stack[i];
  }
  unknown18[length] = nullptr;
}

int CallStackInfo::addRef() const { return ++unknown14; }

int CallStackInfo::release() { return --unknown14; }

bool CallStackInfo::equal(void **stack, u32 count, const char *file, u32 line) const {
  if (unknown98 == file && unknowna0 == line) {
    u32 length = unknowna4;
    if (count <= length) {
      length = count;
    }
    for (u32 i = 0; i < length; i++) {
      if (stack[i] != unknown18[i]) {
        return false;
      }
    }
    return true;
  }
  return false;
}

void CallStackInfo::log() {
  if (unknowna4 != 0) {
    mlStackTrace(unknown18);
  }
}

void CallStackManager::initialize() {
  m_maxAllocate = 0;
  m_nowAllocate = 0;
  m_maxAllocateSize = 0;
  m_nowAllocateSize = 0;
  m_bufferSize = 0;
  m_maxRefCount = 0;
  size_t size = MAX_ALLOCATE_SIZE * sizeof(CallStackInfo);
  m_buffer = malloc(size);
  if (m_buffer != nullptr) {
    m_allocator.create(m_buffer, size, "CallStackAllocator");
    m_bufferSize = size;
  }
}

void CallStackManager::finalize() {
  if (m_buffer != nullptr) {
    m_allocator.destroy(false);
    free(m_buffer);
    m_buffer = nullptr;
    m_bufferSize = 0;
  }
}

bool CallStackManager::validMemoryRange(void *pointer) {
  if (pointer == nullptr) {
    return true;
  }
  if (pointer < m_buffer) {
    return false;
  }
  return reinterpret_cast<size_t>(pointer) < m_bufferSize + reinterpret_cast<size_t>(m_buffer);
}

void CallStackManager::remove(CallStackInfo *info) {
  if (info != nullptr) {
    if (info->unknown14 == 1) {
      erase(info);
    }
    if (info->release() == 0) {
      ml::CS lock(unknown18);
      m_allocator.deallocate(info);
    }
  }
}

void *DlAllocator::getNewInfo(const void *pointer, size_t &size) {
  size = 0;
  size_t address = reinterpret_cast<size_t>(pointer);
  if (address != 0) {
    size_t offset = unknown008(address);
    address = offset + address;
    size = static_cast<int>(offset) > 0 ? offset : 0;
    address = static_cast<int>(offset) > 0 ? address : 0;
  }
  return reinterpret_cast<void *>(address);
}

void DlAllocator::log_callSTack(void *callStack) const {
  if (callStack != nullptr && unknown30 != nullptr) {
    size_t address = reinterpret_cast<size_t>(callStack);
    size_t offset = unknown008(address);
    unknown001 *info = reinterpret_cast<unknown001 *>(offset + address);
    if (static_cast<int>(offset) > 0 && info != nullptr && info->unknown10 != nullptr && info->unknown00 == 0x44434241) {
      info->unknown10->log();
    }
  }
}

bool DlAllocator::hasMemory(const void *pointer) const {
  unknown003 *space = unknown30;
  if (pointer != nullptr && space != nullptr) {
    if (space->unknown40 == unknown007.unknown00) {
      DL_ALLOCATOR_ENSURE_INITIALIZATION();
      if (space->unknown28 != nullptr) {
        for (unknown004 *segment = &space->unknown378; segment != nullptr; segment = segment->unknown10) {
          unknown002 *chunk = unknown009(segment->unknown00);
          while (reinterpret_cast<u8 *>(chunk) >= segment->unknown00 && chunk != space->unknown28 && reinterpret_cast<u8 *>(chunk) < segment->unknown00 + segment->unknown08 &&
                 chunk->unknown08 != 0xb) {
            void *memory = unknown011(chunk);
            chunk = unknown010(chunk);
            if (memory == pointer) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

void DlAllocator::checkLeakMemory() {
  unknown003 *space = unknown30;
  if (space != nullptr) {
    DL_ALLOCATOR_ENSURE_INITIALIZATION();
    if (space->unknown28 != nullptr) {
      int index = 0;
      for (unknown004 *segment = &space->unknown378; segment != nullptr; segment = segment->unknown10) {
        unknown002 *chunk = unknown009(segment->unknown00);
        while (reinterpret_cast<u8 *>(chunk) >= segment->unknown00 && reinterpret_cast<u8 *>(chunk) < segment->unknown00 + segment->unknown08 && chunk != space->unknown28 && chunk->unknown08 != 0xb) {
          if (index > 0 && unknown013(chunk)) {
            CallStackInfo *info = unknown014(chunk)->unknown10;
            if (info != nullptr) {
              info->log();
            }
          }
          chunk = unknown010(chunk);
          index++;
        }
      }
    }
  }
}

void DlAllocator::getMemImage(MEMIMAGE_HEAD *head) const {
  unknown003 *space = unknown30;
  if (space != nullptr) {
    if (space->unknown40 == unknown007.unknown00) {
      DL_ALLOCATOR_ENSURE_INITIALIZATION();
      if (space->unknown28 != nullptr) {
        int index = 0;
        u32 count = 0;
        MEMIMAGE_HEAD::unknown001 *block = head->unknown18;
        for (unknown004 *segment = &space->unknown378; segment != nullptr; segment = segment->unknown10) {
          unknown002 *chunk = unknown009(segment->unknown00);
          while (reinterpret_cast<u8 *>(chunk) >= segment->unknown00 && reinterpret_cast<u8 *>(chunk) < segment->unknown00 + segment->unknown08 && chunk != space->unknown28 &&
                 chunk->unknown08 != 0xb) {
            size_t size = chunk->unknown08 & ~static_cast<size_t>(7);
            if (index > 0 && unknown013(chunk) && unknown012(chunk) == unknown014(chunk)->unknown08 && count < head->unknown10) {
              block->unknown00 = reinterpret_cast<size_t>(chunk);
              block->unknown08 = size;
              block++;
              count++;
            }
            chunk = unknown010(chunk);
            index++;
          }
        }
        head->unknown10 = count;
      }
    }
  } else {
    head->unknown08 = 0;
    head->unknown10 = 0;
    head->unknown00 = 0;
  }
}

template <int N> void AssetAllocator<N>::create(void *buffer, size_t size, const char *name) {
  unknown11090 = buffer;
  unknown110a8 = size >> 4;
  unknown11098 = (size >> 4) << 4;
  unknown110a0 = 0x10;
  m_name = name != nullptr ? name : "no name";
  unknown30.clear();
  unknown8860.clear();
  SMemChunk chunk = {nullptr, 0, 0, 0, static_cast<u32>(unknown110a8)};
  unknown30.push_back(chunk);
}

template <int N> void AssetAllocator<N>::destroy() {
  unknown110a8 = 0;
  unknown11098 = 0;
  unknown11090 = nullptr;
  unknown30.clear();
  unknown8860.clear();
}

template <int N> AllocatorType AssetAllocator<N>::getType() const { return ALLOCATOR_TYPE_RESOURCE; }

template <int N> void *AssetAllocator<N>::allocate(size_t size, size_t alignment) { return allocate(size, alignment, "", 0); }

template <int N> void *AssetAllocator<N>::reallocate(void *pointer, size_t size) { return nullptr; }

template <int N> void AssetAllocator<N>::log(MemoryInfo *info, bool isDetail) const {}

template <int N> const char *AssetAllocator<N>::getName() const { return m_name.c_str(); }

template <int N> bool AssetAllocator<N>::empty() const { return m_name.c_str()[0] == '\0'; }

template <int N> bool AssetAllocator<N>::valid() const { return m_name.c_str()[0] != '\0'; }

template <int N> bool AssetAllocator<N>::dummy() const { return m_name.c_str()[0] != '\0'; }

template <int N> bool AssetAllocator<N>::hasMemory(const void *pointer) const {
  bool found = false;
  for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown30.begin(); it != unknown30.end(); ++it) {
    if (unknown001(it->unknown0c) == pointer) {
      found = true;
      break;
    }
  }
  if (!found) {
    for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown8860.begin(); it != unknown8860.end(); ++it) {
      if (unknown001(it->unknown0c) == pointer) {
        found = true;
        break;
      }
    }
  }
  return found;
}

template <int N> size_t AssetAllocator<N>::getAllocSize(const void *pointer) const {
  size_t size = 0;
  for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown8860.begin(); it != unknown8860.end(); ++it) {
    if (unknown001(it->unknown0c) == pointer) {
      size = static_cast<size_t>(static_cast<int>(it->unknown10)) << 4;
      break;
    }
  }
  return size;
}

template <int N> void AssetAllocator<N>::memoryInfo(MemoryInfo *info) const {
  if (info != nullptr) {
    size_t freeSize = 0;
    size_t maxFreeSize = 0;
    for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown30.begin(); it != unknown30.end(); ++it) {
      size_t size = unknown002(it->unknown10);
      freeSize += size;
      if (size > maxFreeSize) {
        maxFreeSize = size;
      }
    }
    size_t usedSize = 0;
    for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown8860.begin(); it != unknown8860.end(); ++it) {
      usedSize += unknown002(it->unknown10);
    }
    int freeChunks = unknown30.size();
    u32 usedChunks = unknown8860.size();
    u32 chunks = usedChunks + freeChunks;
    info->unknown38 = reinterpret_cast<u64>(getName());
    info->unknown00 = unknown11098;
    info->unknown08 = freeSize;
    info->unknown10 = usedSize;
    info->unknown18 = maxFreeSize;
    f32 usedPercent = usedSize * 100.0f / unknown11098;
    f32 usedChunksPercent = usedChunks * 100.0f / chunks;
    info->unknown20 = usedPercent;
    info->unknown24 = usedChunksPercent;
    info->unknown28 = unknown8860.size();
  }
}

template <int N> void AssetAllocator<N>::getMemImage(MEMIMAGE_HEAD *head) const {
  size_t count = 0;
  MEMIMAGE_HEAD::unknown001 *block = head->unknown18;
  for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown8860.begin(); it != unknown8860.end(); ++it) {
    if (count < head->unknown10) {
      count++;
      block->unknown00 = reinterpret_cast<size_t>(unknown001(it->unknown0c));
      block->unknown08 = unknown002(it->unknown10);
      block++;
    }
  }
  head->unknown10 = count;
}

template <int N> bool AssetAllocator<N>::getMemInfo1(MemoryInfo1 *info, u32 num) const {
  u32 count = 0;
  for (typename mm::mtl::FixedList<SMemChunk, N>::const_iterator it = unknown8860.begin(); it != unknown8860.end(); ++it) {
    if (count < num) {
      count++;
      info->unknown00 = reinterpret_cast<size_t>(unknown001(it->unknown0c));
      info->unknown08 = unknown002(it->unknown10);
      info->unknown10 = it->unknown00 != nullptr ? it->unknown00 : "";
      info->unknown18 = it->unknown08;
      info++;
    }
  }
  return count != 0;
}

// The line argument of the allocation is the line of the original file.
#line 1906
void *MemHandlebaseAllocator::allocate(size_t size, size_t alignment) { return MemManager::allocate(unknown08, size, alignment, false, __FILE__, __LINE__); }

void MemHandlebaseAllocator::deallocate(void *pointer) { MemManager::deallocate(pointer, 0, false); }

const char *MemHandlebaseAllocator::getName() const { return "MemHandlebaseAllocator"; }

} // namespace mtl

template mm::mtl::FixedVector<mtl::MemManager::HandleRegion, 512>::~FixedVector();

void operator delete(void *pointer) noexcept { mtl::MemManager::deallocate(pointer, 0, false); }

template class mtl::AssetAllocator<1024>;
