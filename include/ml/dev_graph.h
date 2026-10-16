#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class DevGraph {
public:
  static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
};

} // namespace ml
