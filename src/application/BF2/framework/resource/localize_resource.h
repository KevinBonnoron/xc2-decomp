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
  enum CheckState {
    CHECK_STATE_NONE = 0,
    CHECK_STATE_RETRY = 1,
    CHECK_STATE_LANG = 2,
    CHECK_STATE_DEFAULT = 3,
    CHECK_STATE_DONE = 4,
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

  mm::mtl::FixStr<128> localizedPath;
  CheckState checkState;
};

static_assert(offsetof(LocalizeResource, localizedPath) == 0xd0, "");
static_assert(offsetof(LocalizeResource, checkState) == 0x154, "");
static_assert(sizeof(LocalizeResource) == 0x158, "");

} // namespace fw
