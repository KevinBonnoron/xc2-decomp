#pragma once

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {

class BdatManager {
public:
  static bool loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path);
  static bool isEnableBdat(int id);
  static void unregistBdat(int id);
  static unsigned char *getFp(const char *name);
};

} // namespace fw
