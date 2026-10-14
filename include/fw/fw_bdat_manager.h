#pragma once
#include "mtl/alloc_handle.h"

namespace fw {

class BdatManager {
public:
  static bool loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path);
  static bool isEnableBdat(int id);
  static void unregistBdat(int id);
};

} // namespace fw
