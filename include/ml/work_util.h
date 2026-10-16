#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class WorkUtil {
public:
  static mtl::ALLOC_HANDLE getWorkMem();
};

} // namespace ml
