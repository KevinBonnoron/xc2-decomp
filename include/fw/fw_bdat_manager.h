#pragma once
#include <stddef.h>

#include "framework/lang_util.h"
#include "framework/manager_object.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class FileResTh;
} // namespace ml

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
      STATE_UNKNOWN_0 = 0, // Inferred role: unused; original name unknown.
      STATE_UNKNOWN_1 = 1, // Inferred role: loading; original name unknown.
      STATE_UNKNOWN_2 = 2, // Inferred role: loaded, sheets not registered; original name unknown.
      STATE_UNKNOWN_3 = 3, // Inferred role: enable; original name unknown.
    };

    // Layout evidence: loadBdat (0x7100153048), loadBdatFromMemory (0x7100153920) and unregistBdat (0x7100152ecc) clear and fill one
    // element in these members: the three FixStr (characters at 0x04, 0x108 and 0x12c, lengths at 0x104, 0x128 and 0x13c) and the
    // members at 0x00, 0x140, 0x148, 0x150, 0x158 and 0x160. The copy constructor (0x7100153578, C2 only: implicit, emitted for its
    // user reloadBdat) copies the strings one by one, the 16 bytes 0x140-0x14f and the 9 bytes 0x158-0x160 as memory blocks, and
    // 0x150 apart (mtl::ALLOC_HANDLE has a user-provided copy constructor): no member covers 0x161-0x167, which is tail padding.
    struct BdatInfo {
      State unknown00;                  // Inferred role: state; original member name unknown.
      mm::mtl::FixStr<256> unknown04;   // Inferred role: file path; original member name unknown.
      mm::mtl::FixStr<32> unknown108;   // Inferred role: name; original member name unknown.
      mm::mtl::FixStr<16> unknown12c;   // Inferred role: language folder; original member name unknown.
      u32 unknown140;                   // Inferred role: CRC of the name; original member name unknown.
      void *unknown148;                 // Inferred role: data; original member name unknown.
      mtl::ALLOC_HANDLE m_ALLOC_HANDLE; // Inferred role: allocator handle, a copy of the handle passed to loadBdat; original member name unknown.
      ml::FileResTh *unknown158;        // Inferred role: loading data; original member name unknown.
      bool unknown160;                  // Inferred role: data given by the caller; original member name unknown.
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
    // Defined in the class: the game passes `this` to it from loadBdat (0x710015311c: `mov x0, x19`) although the body never reads it.
    // Measured with clang 3.9: defined out of line in the unit, the call no longer sets x0 (loadBdat has 173 instructions against the
    // game's 174); defined in the class (an inline function, emitted as a weak copy) it keeps the argument and gives the 90
    // instructions of 0x7100152c60. The game computes the length of `name` and checks it against the capacity once in each arm, then
    // both arms join in the shared strcat of the tail: written as `if (...) { lang; "/"; } path += name;` it has 77 instructions, so
    // `path += name` is written in both arms.
    void makePath(mm::mtl::FixStr<256> &path, const char *name) {
      if (isMsgFile(name)) {
        path += LangUtil::getLangFolder().c_str();
        path += "/";
        path += name;
      } else {
        path += name;
      }
    }
    ~Impl();
    void unregistBdat(int id);
    bool loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path);
    bool reloadBdat(int id);
    bool loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name);
    void loadBdatFromMemory(int id, void *data);
    void unregistBdat(const char *name);
    int find(const char *name) const;
    void updateLayer(int id, BdatInfo &info);
    unsigned char *getFp(const char *name);
    void update(const UpdateInfo &info);
    bool isExistBdat(int id) const;
    bool isEnableBdat(int id) const;

    mm::mtl::IAllocator *unknown00; // Inferred role: allocator; original member name unknown.
    mm::mtl::FixStr<256> unknown08; // Inferred role: base path; original member name unknown.
    u8 _10c[0x110 - 0x10c];
    mm::mtl::Map<u32, SheetFpInfo> unknown110; // Inferred role: sheets by name CRC; original member name unknown.
    BdatInfo m_bdatInfo[BDAT_UNKNOWN_16];      // Inferred role: infos; original member name unknown.
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

  Impl *m_impl;                   // Inferred role: impl; original member name unknown.
  mm::mtl::IAllocator *unknown20; // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(BdatManager::Impl::SheetFpInfo, unknown24) == 0x24, "");
static_assert(offsetof(BdatManager::Impl::SheetFpInfo, unknown68) == 0x68, "");
static_assert(offsetof(BdatManager::Impl::SheetFpInfo, unknown70) == 0x70, "");
static_assert(sizeof(BdatManager::Impl::SheetFpInfo) == 0x78, "");
static_assert(offsetof(BdatManager::Impl, unknown08) == 0x08, "");
static_assert(offsetof(BdatManager::Impl, unknown110) == 0x110, "");
static_assert(offsetof(BdatManager::Impl, m_bdatInfo) == 0x128, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown04) == 0x04, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown108) == 0x108, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown12c) == 0x12c, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown140) == 0x140, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown148) == 0x148, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, m_ALLOC_HANDLE) == 0x150, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown158) == 0x158, "");
static_assert(offsetof(BdatManager::Impl::BdatInfo, unknown160) == 0x160, "");
static_assert(sizeof(BdatManager::Impl::BdatInfo) == 0x168, "");
static_assert(offsetof(BdatManager, m_impl) == 0x18, "");

} // namespace fw
