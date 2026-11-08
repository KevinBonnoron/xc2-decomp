#pragma once
#include "types.h"

namespace skt {
namespace util {

bool strToInt(const char *str, int &value);
bool strToFloat(const char *str, f32 &value);
int strToInt(const char *str);
f32 strToFloat(const char *str);
bool utf8ToUtf16(const char *source, wchar_t *dest, u32 size);
bool sjisToUtf16(const char *source, wchar_t *dest, u32 size);
bool utf16ToSjis(const wchar_t *source, char *dest, u32 size);
bool utf16ToUtf8(const wchar_t *source, char *dest, u32 size);
bool utf8ToSjis(const char *source, char *dest, u32 size);

} // namespace util
} // namespace skt
