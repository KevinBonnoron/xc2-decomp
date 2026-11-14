#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

// Replaces every occurrence of srcPattern in str with dstPattern (1.0.0: 0x71001a86e0 for FixStr<256>).
// __LINE__ must be 64 and 65 as in the original header: they are the line arguments of the asserts.
#line 63
template <typename T> void replacestr(T &str, const char *srcPattern, const char *dstPattern) {
  MM_ASSERT(srcPattern);
  MM_ASSERT(dstPattern);
  T src(srcPattern);
  T dst(dstPattern);
  int pos = 0;
  while (str.length() > pos) {
    pos = str.unknown003(src.c_str(), pos);
    if (pos == -1) {
      break;
    }
    str.erase(pos, src.length());
    str.insert(pos, dst.c_str(), dst.length());
    pos += dst.length();
  }
}

} // namespace mtl
} // namespace mm
