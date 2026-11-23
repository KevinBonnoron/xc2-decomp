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

// 1.0.0: 0x710075b788. The name without directory and extension; the search for the dot is the inlined FixStr::unknown004 and the substring is built in the return
// slot (FixStr::substr). The file part is the loop of getFilePtrFromPath (0x710075b6b4) written out (ruling 8): the game inlines it (no call, `subs x13, x12, #1` at
// 0x710075b7cc), but the call `const char *file = getFilePtrFromPath(path);` gives 104 instructions against 103, the loop counter being `x12 + 1` (`add x13, x12, #1 ;
// cmp x13, #1`) with a longer loop body. The same 104 with the call alone in a wrapper, with getFilePtrFromPath defined after the caller, and with the standalone body
// written as a `while`, as `&path[i]` (both still match the standalone function, 29 instructions); the scan from `strlen(path) - 1` gives 105 and does not match the
// standalone one either. The IR text handed to loop strength reduction is identical for the call and for the loop written out; [INFERENCE] the use-list order of the
// inlined body is what differs. `file != nullptr` is dead here but the game keeps it (`cbz x20, 0x710075b880` skips the whole assignment, 0x710075b800): without it
// the assertion of operator= stays (109 instructions).
mm::mtl::FixStr<64> PathUtil::getNoPathExtName(const char *path) {
  mm::mtl::FixStr<64> name;
  const char *file = path;
  for (int i = strlen(path); i > 0; i--) {
    char c = path[i - 1];
    if (c == '/' || c == '\\' || c == ':') {
      file = path + i;
      break;
    }
  }
  if (file != nullptr) {
    name = file;
  }
  int dot = name.unknown004('.');
  if (dot == -1 || dot == 0) {
    return name;
  }
  return name.substr(0, dot);
}

void PathUtil::itoa(mm::mtl::FixStr<16> &string, int value, int digits) {
  string = "";
  for (int i = 0; i < digits; i++) {
    char text[2] = {};
    int unit = 1;
    for (int j = 0; j < i; j++) {
      unit *= 10;
    }
    int digit = value % (unit * 10) / unit;
    text[0] = '0' + digit;
    mm::mtl::FixStr<16> character(text);
    string = character + string.c_str();
  }
}

void PathUtil::htoa(mm::mtl::FixStr<16> &string, u32 value, int digits) {
  string = "";
  for (int i = 0; i < digits; i++) {
    char text[2] = {};
    u32 unit = 1;
    for (int j = 0; j < i; j++) {
      unit *= 16;
    }
    // The game compares (digit & 0xfe) < 10 (0x710075bc54: and w9, w8, #0xfe; cmp w9, #10), which clang gives for a byte digit; an int or u32 digit is
    // compared whole and gives 96 instructions against the game's 97 (char, unsigned char and u8 match; s8 and u16 do not).
    u8 digit = value % (unit * 16) / unit;
    text[0] = digit < 10 ? '0' + digit : 'a' + digit - 10;
    mm::mtl::FixStr<16> character(text);
    string = character + string.c_str();
  }
}

// 1.0.0: 0x710075bd0c. Replaces the extension of name by ext (a dot is added when ext has none); the search is the inlined FixStr::unknown004.
bool PathUtil::changeExt(mm::mtl::FixStr<256> &path, const char *name, const char *ext) {
  if (name == nullptr || ext == nullptr) {
    return false;
  }
  path = name;
  int dot = path.unknown004('.');
  if (dot != -1) {
    path.erase(dot, -1);
  }
  if (strchr(ext, '.') == nullptr) {
    path += ".";
  }
  path += ext;
  return true;
}

} // namespace ml
