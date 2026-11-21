#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {

class PathUtil {
public:
  static const char *getFilePtrFromPath(const char *path);
  static const char *getFileExtPtr(const char *path);
  static mm::mtl::FixStr<64> getNoPathExtName(const char *path);
  template <class T> static bool getNoExtName(T &path, const char *name);
  template <class T> static bool getFsaPath(T &path, const char *name);
  static bool changeExt(mm::mtl::FixStr<256> &path, const char *name, const char *ext);
  static void htoa(mm::mtl::FixStr<16> &string, u32 value, int digits);
  static void itoa(mm::mtl::FixStr<16> &string, int value, int base);
};

// 1.0.0: getNoExtName<FixStr<256>> is the standalone instance 0x710019e430 (ScriptManager::makeFullPath calls it); the FixStr<128> one is inlined by its
// users. The search for the dot is the inlined FixStr::unknown004 (decision 55). `dot == 0` is the unsigned test `dot + 1 < 2` of the game.
template <class T> bool PathUtil::getNoExtName(T &path, const char *name) {
  path = name;
  int dot = path.unknown004('.');
  if (dot == -1 || dot == 0) {
    return false;
  }
  T head;
  path.unknown001(head, 0, dot);
  path = head;
  return true;
}

// 1.0.0: getFsaPath<FixStr<128>> 0x7100169e4c (fw::EffectData): removes the ':' (the device prefix) and turns the backslashes into slashes.
template <class T> bool PathUtil::getFsaPath(T &path, const char *name) {
  path = name;
  int pos = path.unknown004(':');
  if (pos != -1) {
    path.erase(pos, 1);
  }
  for (int i = 0; i < path.length(); i++) {
    if (path[i] == '\\') {
      path[i] = '/';
    }
  }
  return true;
}

} // namespace ml
