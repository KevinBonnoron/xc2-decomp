#pragma once
#include <stddef.h>

#include "device/dev_file_dic_allocator.h"
#include "device/dev_file_dictionary.h"
#include "ml/dev_file_th.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {

class DevFileArchiver : public mm::mtl::PtrSingleton<DevFileArchiver> {
public:
  // Inferred type: entry of an archive file table, 0x18 bytes indexed by the dictionary value; the original type name is unknown.
  struct unknown001 {
    u64 unknown00; // Inferred role: data offset; original member name unknown.
    u32 unknown08; // Inferred role: stored size; original member name unknown.
    u32 unknown0c; // Inferred role: size; original member name unknown.
    u32 unknown10; // Inferred role: flags; original member name unknown.
    u32 unknown14; // Inferred role: identifier; original member name unknown.
  };

  // Inferred type: archive added by addArchive; the original type name is unknown.
  struct unknown002 {
    ~unknown002() {
      if (unknown1e0 != nullptr) {
        mtl::MemManager::deallocate(unknown1e0, 0, false);
        unknown1e0 = nullptr;
      }
    }

    mm::mtl::FixStr<128> unknown00;                                       // Inferred role: archive name, compared by removeArchive; original member name unknown.
    mm::mtl::FixStr<128> unknown84;                                       // Inferred role: archive path, copied into FileInfoResult; original member name unknown.
    mm::mtl::FixStr<128> unknown108;                                      // Inferred role: archive path with its media prefix; original member name unknown.
    DevFileDictionary<int, DevFileDicAllocator, -1, -2, true> unknown190; // Inferred role: file name dictionary; original member name unknown.
    void *unknown1e0;                                                     // Inferred role: archive header data; original member name unknown.
    unknown001 *unknown1e8;                                               // Inferred role: file table; original member name unknown.
  };

  // Inferred type: archives of one media; the original type name is unknown.
  struct unknown003 {
    unknown003() : unknown00(MEDIA_UNKNOWN_8), unknown04(false) {}

    MEDIA unknown00;                                  // Inferred role: media, set by initialize; original member name unknown.
    bool unknown04;                                   // Inferred role: enabled, set by initialize; original member name unknown.
    mm::mtl::FixedVector<unknown002 *, 16> unknown08; // Inferred role: archives; original member name unknown.
  };

  // Inferred layout: filled by getFileInfo; the type name comes from its symbol.
  struct FileInfoResult {
    MEDIA unknown00;                // Inferred role: media; original member name unknown.
    mm::mtl::FixStr<128> unknown04; // Inferred role: archive path; original member name unknown.
    unknown001 unknown88;           // Inferred role: file table entry; original member name unknown.
  };

  DevFileArchiver(mtl::ALLOC_HANDLE mem);
  ~DevFileArchiver() override;
  void initialize();
  void finalize();
  bool removeArchive(MEDIA media, const char *name);
  bool getFileInfo(MEDIA media, const char *path, FileInfoResult &result) const;

  u8 _08[0x0c - 0x08];
  mtl::ALLOC_HANDLE m_ALLOC_HANDLE;          // Inferred role: memory of the archives; original member name unknown.
  unknown003 unknown10[8];                   // Inferred role: archives per media; original member name unknown.
  DevFileDicAllocator m_devFileDicAllocator; // Inferred role: allocator of the dictionaries; original member name unknown.
};

static_assert(offsetof(DevFileArchiver::unknown001, unknown08) == 0x08, "");
static_assert(offsetof(DevFileArchiver::unknown001, unknown14) == 0x14, "");
static_assert(sizeof(DevFileArchiver::unknown001) == 0x18, "");
static_assert(offsetof(DevFileArchiver::unknown002, unknown84) == 0x84, "");
static_assert(offsetof(DevFileArchiver::unknown002, unknown108) == 0x108, "");
static_assert(offsetof(DevFileArchiver::unknown002, unknown190) == 0x190, "");
static_assert(offsetof(DevFileArchiver::unknown002, unknown190.unknown44) == 0x1d4, "");
static_assert(offsetof(DevFileArchiver::unknown002, unknown190.unknown48) == 0x1d8, "");
static_assert(offsetof(DevFileArchiver::unknown002, unknown1e0) == 0x1e0, "");
static_assert(sizeof(DevFileArchiver::unknown002) == 0x1f0, "");
static_assert(offsetof(DevFileArchiver::unknown003, unknown08) == 0x08, "");
static_assert(sizeof(DevFileArchiver::unknown003) == 0x90, "");
static_assert(offsetof(DevFileArchiver::FileInfoResult, unknown04) == 0x04, "");
static_assert(offsetof(DevFileArchiver::FileInfoResult, unknown88) == 0x88, "");
static_assert(sizeof(DevFileArchiver::FileInfoResult) == 0xa0, "");
static_assert(offsetof(DevFileArchiver, m_ALLOC_HANDLE) == 0x0c, "");
static_assert(offsetof(DevFileArchiver, unknown10) == 0x10, "");
static_assert(offsetof(DevFileArchiver, m_devFileDicAllocator) == 0x490, "");
static_assert(sizeof(DevFileArchiver) == 0x498, "");

} // namespace ml
