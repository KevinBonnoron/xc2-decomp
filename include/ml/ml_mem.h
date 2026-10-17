#pragma once
#include <stddef.h>

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class MlMem {
public:
  enum AccessMode {};

  static void setProductMem(mtl::ALLOC_HANDLE handle);
  static mtl::ALLOC_HANDLE getProductMem();
  static void setDebugMem(mtl::ALLOC_HANDLE handle);
  static mtl::ALLOC_HANDLE getDebugMem();
  static void setGraphicMem(mtl::ALLOC_HANDLE handle);
  static mtl::ALLOC_HANDLE getGraphicMem();
  static int getExtMemNum();
  static bool isDebug(const void *pointer);
  static void setMemoryPermission(void *address, size_t size, AccessMode mode);
};

} // namespace ml
