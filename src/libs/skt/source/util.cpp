#include "skt/util.h"

#include <stdlib.h>

namespace skt {
namespace util {

bool strToInt(const char *str, int &value) {
  char *end;
  value = strtol(str, &end, 0);
  return end != str;
}

bool strToFloat(const char *str, f32 &value) {
  char *end;
  value = strtod(str, &end);
  return end != str;
}

int strToInt(const char *str) {
  char *end;
  return strtol(str, &end, 0);
}

f32 strToFloat(const char *str) {
  char *end;
  return strtod(str, &end);
}

bool utf8ToUtf16(const char *source, wchar_t *dest, u32 size) { return false; }

bool sjisToUtf16(const char *source, wchar_t *dest, u32 size) { return false; }

bool utf16ToSjis(const wchar_t *source, char *dest, u32 size) { return false; }

bool utf16ToUtf8(const wchar_t *source, char *dest, u32 size) { return false; }

bool utf8ToSjis(const char *source, char *dest, u32 size) { return false; }

} // namespace util
} // namespace skt
