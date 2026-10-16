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
      State state;
      u8 _004[0x148 - 0x004];
      void *data;
      u8 _150[0x158 - 0x150];
      void *loadingData;
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

    mm::mtl::IAllocator *allocator;
    mm::mtl::FixStr<256> basePath;
    u8 _10c[0x128 - 0x10c];
    BdatInfo infos[BDAT_MAX];
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

  Impl *impl;
  mm::mtl::IAllocator *allocator;
};

static_assert(offsetof(BdatManager::Impl, basePath) == 0x08, "");
static_assert(offsetof(BdatManager::Impl, infos) == 0x128, "");
static_assert(sizeof(BdatManager::Impl::BdatInfo) == 0x168, "");
static_assert(offsetof(BdatManager, impl) == 0x18, "");

} // namespace fw
