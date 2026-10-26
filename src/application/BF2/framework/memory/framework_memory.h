#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

struct MemorySectionInfo {
  MemorySectionInfo();

  u32 unknown00;                 // Inferred role: section index; original member name unknown.
  mtl::ALLOC_HANDLE unknown04;   // Inferred role: parent section handle; original member name unknown.
  u64 unknown08;                 // Inferred role: size; original member name unknown.
  u32 unknown10;                 // Inferred role: alignment; original member name unknown.
  bool unknown14;                // Inferred role: allocate from the back; original member name unknown.
  mm::mtl::FixStr<64> unknown18; // Inferred role: name; original member name unknown.
  mtl::AllocatorType unknown5c;  // Inferred role: allocator type; original member name unknown.
};

static_assert(offsetof(MemorySectionInfo, unknown04) == 0x04, "");
static_assert(offsetof(MemorySectionInfo, unknown08) == 0x08, "");
static_assert(offsetof(MemorySectionInfo, unknown10) == 0x10, "");
static_assert(offsetof(MemorySectionInfo, unknown14) == 0x14, "");
static_assert(offsetof(MemorySectionInfo, unknown18) == 0x18, "");
static_assert(offsetof(MemorySectionInfo, unknown5c) == 0x5c, "");
static_assert(sizeof(MemorySectionInfo) == 0x60, "");

class FrameworkMemory : public mm::mtl::Singleton<FrameworkMemory> {
public:
  struct SectionRegistInfo : public MemorySectionInfo {
    SectionRegistInfo() : unknown64(0) {}

    mtl::ALLOC_HANDLE unknown60;      // Inferred role: section handle; original member name unknown.
    u32 unknown64;                    // Inferred role: name hash; original member name unknown.
    MemHandlebaseAllocator unknown68; // Inferred role: section allocator; original member name unknown.

    // Inferred role: clear the section handle and its allocator; original name unknown.
    void unknown001() {
      unknown60 = mtl::ALLOC_HANDLE();
      unknown64 = 0;
      unknown68.setMemHandle(mtl::ALLOC_HANDLE());
    }
  };

  FrameworkMemory();
  virtual ~FrameworkMemory() {}
  static void initialize(mtl::ALLOC_HANDLE handle, u32 sectionMax);
  static void finalize();
  mtl::ALLOC_HANDLE createSection(const MemorySectionInfo &info);
  void removeSection(mtl::ALLOC_HANDLE handle);
  void removeChildSection(mtl::ALLOC_HANDLE handle);
  static mtl::ALLOC_HANDLE getMem(u32 section);
  static mm::mtl::IAllocator *getAllocator(u32 section);

  mm::mtl::Array<SectionRegistInfo> unknown08; // Inferred role: sections; original member name unknown.
  bool unknown20;                              // Inferred role: initialized; original member name unknown.
  MemHandlebaseAllocator unknown28;            // Inferred role: section table allocator; original member name unknown.
};

static_assert(offsetof(FrameworkMemory::SectionRegistInfo, unknown60) == 0x60, "");
static_assert(offsetof(FrameworkMemory::SectionRegistInfo, unknown68) == 0x68, "");
static_assert(sizeof(FrameworkMemory::SectionRegistInfo) == 0xb8, "");
static_assert(offsetof(FrameworkMemory, unknown08) == 0x08, "");
static_assert(offsetof(FrameworkMemory, unknown20) == 0x20, "");
static_assert(offsetof(FrameworkMemory, unknown28) == 0x28, "");
static_assert(sizeof(FrameworkMemory) == 0x78, "");

} // namespace fw

void *operator new(size_t size, mm::mtl::IAllocator *allocator, int alignment, const char *file, size_t line);
