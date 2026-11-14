#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

struct UpdateInfo;

class BdatManager : public ManagerObject, public mm::mtl::PtrSingleton<BdatManager> {
public:
  class Impl {
  public:
    enum State {
      STATE_UNKNOWN_3 = 3, // Inferred role: enable; original name unknown.
    };

    struct BdatInfo {
      State unknown00; // Inferred role: state; original member name unknown.
      u8 _004[0x148 - 0x004];
      void *unknown148; // Inferred role: data; original member name unknown.
      u8 _150[0x158 - 0x150];
      void *unknown158; // Inferred role: loading data; original member name unknown.
      u8 _160[0x168 - 0x160];
    };

    // Sheet registered by updateLayer (0x7100153684) under the CRC of its name, and read back by getFp
    // (0x7100154050). Layout evidence: updateLayer fills the two FixStr then the data pointer and the bdat id, and
    // the node copy in Map<u32, SheetFpInfo>::insert (0x7100154fc8) puts them at 0x00, 0x24, 0x68 and 0x70.
    struct SheetFpInfo {
      mm::mtl::FixStr<32> unknown00; // Inferred role: bdat file name; original member name unknown.
      mm::mtl::FixStr<64> unknown24; // Inferred role: sheet name; original member name unknown.
      unsigned char *unknown68;      // Inferred role: sheet data; original member name unknown.
      int unknown70;                 // Inferred role: bdat id; original member name unknown.
    };

    static const u32 BDAT_UNKNOWN_16 = 16; // Inferred role: maximum number of registered bdat files; original name unknown.

    static bool isMsgFile(const char *name);
    ~Impl();
    void unregistBdat(int id);
    bool loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path);
    void reloadBdat(int id);
    void loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name);
    void loadBdatFromMemory(int id, void *data);
    void unregistBdat(const char *name);
    int find(const char *name) const;
    void update(const UpdateInfo &info);
    bool isExistBdat(int id) const;
    bool isEnableBdat(int id) const;

    mm::mtl::IAllocator *unknown00; // Inferred role: allocator; original member name unknown.
    mm::mtl::FixStr<256> unknown08; // Inferred role: base path; original member name unknown.
    u8 _10c[0x110 - 0x10c];
    mm::mtl::Map<u32, SheetFpInfo> unknown110; // Inferred role: sheets by name CRC; original member name unknown.
    BdatInfo unknown128[BDAT_UNKNOWN_16];      // Inferred role: infos; original member name unknown.
  };

  explicit BdatManager(mm::mtl::IAllocator *allocator);
  bool initialize() override;
  bool finalize() override;
  const char *getName() const override { return "BdatManager"; }
  virtual void update(const UpdateInfo &info);
  static void setBasePath(const char *path);
  static const char *getLocale();
  static bool loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path);
  static void reloadBdat(int id);
  static void loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name);
  static void loadBdatFromMemory(int id, void *data);
  static void unregistBdat(int id);
  static void unregistBdat(const char *name);
  static bool isExistBdat(int id);
  static bool isEnableBdat(int id);
  static unsigned char *getFp(const char *name);
  static unsigned char *getFp(int table, int id);

  Impl *unknown18;                // Inferred role: impl; original member name unknown.
  mm::mtl::IAllocator *unknown20; // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(BdatManager::Impl::SheetFpInfo, unknown24) == 0x24, "");
static_assert(offsetof(BdatManager::Impl::SheetFpInfo, unknown68) == 0x68, "");
static_assert(offsetof(BdatManager::Impl::SheetFpInfo, unknown70) == 0x70, "");
static_assert(sizeof(BdatManager::Impl::SheetFpInfo) == 0x78, "");
static_assert(offsetof(BdatManager::Impl, unknown08) == 0x08, "");
static_assert(offsetof(BdatManager::Impl, unknown110) == 0x110, "");
static_assert(offsetof(BdatManager::Impl, unknown128) == 0x128, "");
static_assert(sizeof(BdatManager::Impl::BdatInfo) == 0x168, "");
static_assert(offsetof(BdatManager, unknown18) == 0x18, "");

} // namespace fw
