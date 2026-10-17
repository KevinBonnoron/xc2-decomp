#pragma once
#include "framework/resource/common_resource.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {
enum LOAD_PRIO : int;

class RenderResource : public CommonResource {
public:
  static RenderResource *search(mtl::ALLOC_HANDLE handle, const char *path);
  static RenderResource *search(mm::mtl::IAllocator *allocator, const char *path);
  static RenderResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority);
  static RenderResource *request(mm::mtl::IAllocator *allocator, const char *path, int priority);
  RenderResource(mtl::ALLOC_HANDLE handle, LOAD_PRIO priority);
  RenderResource(mm::mtl::IAllocator *allocator, LOAD_PRIO priority);
  ~RenderResource() override;
};

} // namespace fw
