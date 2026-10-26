#include "ml/path_util.h"

#include <string.h>

namespace ml {

const char *PathUtil::getFilePtrFromPath(const char *path) {
  for (int i = strlen(path); i > 0; i--) {
    char c = path[i - 1];
    if (c == '/' || c == '\\' || c == ':') {
      return path + i;
    }
  }
  return path;
}

const char *PathUtil::getFileExtPtr(const char *path) {
  int length = strlen(path);
  for (int i = 0; i < length - 1; i++) {
    if (path[i] == '.') {
      return path + (i + 1);
    }
  }
  return nullptr;
}

} // namespace ml
