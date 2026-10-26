#pragma once
#include "mm_mtl/fixstr.h"

namespace ml {

class PathUtil {
public:
  static const char *getFilePtrFromPath(const char *path);
  static const char *getFileExtPtr(const char *path);
  static mm::mtl::FixStr<64> getNoPathExtName(const char *path);
  static void itoa(mm::mtl::FixStr<16> &string, int value, int base);
};

} // namespace ml
