#pragma once
#include "framework/resource/common_resource.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {

class RenderResource : public CommonResource {
public:
  static RenderResource *request(mtl::ALLOC_HANDLE handle, const char *path, int priority);
};

} // namespace fw
