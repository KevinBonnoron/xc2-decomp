#include "device/nx/file_loader.h"

#include <stdlib.h>

#include "device/nx/dev_file_util_nx.h"
#include "nn/result.h"
// The game builds DevFileUtilNx in the same unit, so getFileSize is inlined here.
#include "dev_file_util_nx.cpp"

namespace ml {
namespace detail {

FileLoader::~FileLoader() {
  unknown001();
  if (unknown08) {
    unknown08 = false;
    nn::fs::CloseFile(unknown00);
  }
}

void FileLoader::readFile() {
  if (unknown08) {
    s64 size = DevFileUtilNx::getFileSize(unknown00);
    if (size > 0) {
      unknown18 = size;
      unknown10 = malloc(size + 1);
      if (unknown10 != nullptr && !nn::fs::ReadFile(unknown00, 0, unknown10, size).IsSuccess()) {
        unknown001();
        unknown18 = 0;
      }
    }
  }
}

} // namespace detail
} // namespace ml
