#pragma once
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

enum FONT_STYLE : int {
  FONT_STYLE_NORMAL = 0,
};

class DevGraph {
public:
  static void setMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static void releaseMemPoolMemHandle(mtl::ALLOC_HANDLE handle);
  static int getRootWidth();
  static int getRootHeight();
  static f32 fontGetWidth(const char *text, FONT_STYLE style, f32 scale);
  static f32 fontGetHeight(FONT_STYLE style, f32 scale);
};

} // namespace ml
