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

// Inferred role: lower-cases a path from its last separator on, unless that part holds a byte above 0x80; no game symbol, original name unknown.
// Shape from gf::GfMenuMapInfo::initialize (1.0.0: 0x71003c6294 for FixStr<128>) and getMapInfoIndex (0x71003c84d4).
template <typename T> void unknown002(T &str) {
  int pos = str.unknown004('/');
  if (pos == -1) {
    pos = str.unknown004('\\');
  }
  if (pos == -1) {
    pos = 0;
  }
  for (int i = pos; i < str.length(); i++) {
    if (static_cast<unsigned char>(str[i]) > 0x80) {
      return;
    }
  }
  for (int i = pos; i < str.length(); i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] += 'a' - 'A';
    }
  }
}

} // namespace mtl
} // namespace mm
