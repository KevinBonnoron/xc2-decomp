#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/fixstr.h"
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
      STATE_ENABLE = 3,
    };

    struct BdatInfo {
      State unknown00; // Inferred role: state; original member name unknown.
      u8 _004[0x148 - 0x004];
      void *unknown148; // Inferred role: data; original member name unknown.
      u8 _150[0x158 - 0x150];
      void *unknown158; // Inferred role: loading data; original member name unknown.
      u8 _160[0x168 - 0x160];
    };

    static const u32 BDAT_MAX = 16;

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
    u8 _10c[0x128 - 0x10c];
    BdatInfo unknown128[BDAT_MAX]; // Inferred role: infos; original member name unknown.
  };

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

static_assert(offsetof(BdatManager::Impl, unknown08) == 0x08, "");
static_assert(offsetof(BdatManager::Impl, unknown128) == 0x128, "");
static_assert(sizeof(BdatManager::Impl::BdatInfo) == 0x168, "");
static_assert(offsetof(BdatManager, unknown18) == 0x18, "");

} // namespace fw
