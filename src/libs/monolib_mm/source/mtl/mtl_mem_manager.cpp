#include <stddef.h>

#include "ml/critical_section.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/heap_allocator.h"
#include "mtl/alloc_handle.h"
#include "mtl/allocator_wrapper.h"
#include "mtl/call_stack_manager.h"
#include "mtl/dl_allocator.h"
#include "mtl/mem_allocator.h"
#include "mtl/mem_manager.h"
#include "mtl/mem_manager_region.h"
#include "mtl/null_allocator.h"
#include "types.h"

namespace mtl {
struct MEMIMAGE_HEAD;
struct MemoryInfo1;

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

} // namespace mtl

template mm::mtl::FixedVector<mtl::MemManager::HandleRegion, 512>::~FixedVector();

void operator delete(void *pointer) noexcept { mtl::MemManager::deallocate(pointer, 0, false); }
