#pragma once
#include "types.h"

namespace nn {
namespace fs {
struct FileHandle;
} // namespace fs
} // namespace nn

namespace ml {

class DevFileUtilNx {
public:
  static bool getTimeStamp(nn::fs::FileHandle &handle, u32 &first, u32 &second);
  static bool getTimeStamp(const char *path, u32 &first, u32 &second);
  static void zlibFree(void *opaque, void *address);
};

} // namespace ml
