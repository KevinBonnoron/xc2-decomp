#pragma once
#include <stddef.h>

#include "framework/resource/common_resource.h"
#include "ml/work_event.h"
#include "mm_mtl/fixstr.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
enum LOAD_PRIO : int;

class LocalizeResource : public CommonResource, public ml::IWorkEvent {
public:
  // Inferred role: check state; original type name unknown.
  enum unknown001 {
    unknown001_0 = 0, // Inferred role: none; original name unknown.
    unknown001_1 = 1, // Inferred role: retry; original name unknown.
    unknown001_2 = 2, // Inferred role: lang; original name unknown.
    unknown001_3 = 3, // Inferred role: default; original name unknown.
    unknown001_4 = 4, // Inferred role: done; original name unknown.
  };

  LocalizeResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority);
  LocalizeResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority);
  ~LocalizeResource() override;
  static LocalizeResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe);
  static LocalizeResource *request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe);
  const char *getAssetName() const override;
  void update() override;
  void makeLocalizeFilePath(mm::mtl::FixStr<128> &filePath, const mm::mtl::FixStr<16> &folder);
  bool OnFileEvent(ml::EventFileTh *event) override;

  mm::mtl::FixStr<128> unknownd0; // Inferred role: localized path; original member name unknown.
  unknown001 unknown154;          // Inferred role: check state; original member name unknown.
};

static_assert(offsetof(LocalizeResource, unknownd0) == 0xd0, "");
static_assert(offsetof(LocalizeResource, unknown154) == 0x154, "");
static_assert(sizeof(LocalizeResource) == 0x158, "");

} // namespace fw
