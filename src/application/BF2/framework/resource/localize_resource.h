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
  LocalizeResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority);
  LocalizeResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority);
  ~LocalizeResource() override;
  static LocalizeResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority, bool isSafe);
  static LocalizeResource *request(mm::mtl::IAllocator *allocator, const char *path, int priority, bool isSafe);
  const char *getAssetName() const override;
  bool OnFileEvent(ml::EventFileTh *event) override;

  mm::mtl::FixStr<128> localizedPath;
  int checkState;
};

static_assert(offsetof(LocalizeResource, localizedPath) == 0xd0, "");
static_assert(offsetof(LocalizeResource, checkState) == 0x154, "");
static_assert(sizeof(LocalizeResource) == 0x158, "");

} // namespace fw
