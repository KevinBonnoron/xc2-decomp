#pragma once
#include "types.h"

namespace nn {
namespace fs {
struct FileHandle;
} // namespace fs
} // namespace nn

namespace ml {

class FileHandleTh;

// Name from the symbols (DevFileUtilNx::readFile).
struct FileReadResult {
  FileReadResult() : unknown00(-1), unknown08(false), unknown0c(0), unknown10(0) {}

  s64 unknown00;  // Inferred role: read size; original member name unknown.
  bool unknown08; // Inferred role: end of file reached; original member name unknown.
  u32 unknown0c;  // Inferred role: time stamp, high word; original member name unknown.
  u32 unknown10;  // Inferred role: time stamp, low word; original member name unknown.
};

class DevFileUtilNx {
public:
  static s64 getFileSize(nn::fs::FileHandle &handle);
  static s64 getFileSize(const char *path);
  static bool readFile(FileHandleTh *&handle, nn::fs::FileHandle &file, int size, s64 offset, void *buffer, u32 bufferSize, FileReadResult &result);
  static bool readFileSlice(FileHandleTh *handle, nn::fs::FileHandle &file, s64 size, s64 offset, void *buffer, u32 bufferSize, FileReadResult &result);
  static void *zlibAlloc(void *opaque, u32 items, u32 size);
  static bool getTimeStamp(nn::fs::FileHandle &handle, u32 &first, u32 &second);
  static bool getTimeStamp(const char *path, u32 &first, u32 &second);
  static void zlibFree(void *opaque, void *address);
};

} // namespace ml
