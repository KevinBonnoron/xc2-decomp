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
  static s64 getFileSize(nn::fs::FileHandle &handle);
  static s64 getFileSize(const char *path);
  static void *zlibAlloc(void *opaque, u32 items, u32 size);
  static bool getTimeStamp(nn::fs::FileHandle &handle, u32 &first, u32 &second);
  static bool getTimeStamp(const char *path, u32 &first, u32 &second);
  static void zlibFree(void *opaque, void *address);
};

} // namespace ml
