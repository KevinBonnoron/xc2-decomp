#include "event/extend.h"

namespace event {

const char *Extend::mdo(const char *name) {
  unknown08 = name;
  unknown08 += ".wimdo";
  return unknown08.c_str();
}

const char *Extend::arc(const char *name) {
  unknown08 = name;
  unknown08 += ".arc";
  return unknown08.c_str();
}

const char *Extend::anm(const char *name) {
  unknown08 = name;
  unknown08 += ".anm";
  return unknown08.c_str();
}

const char *Extend::anm2eva(const char *name) {
  unknown08 = name;
  const char *found = __builtin_strstr(unknown08.c_str(), ".anm");
  if (found != nullptr) {
    unknown08.erase(found - unknown08.c_str(), 4);
  }
  unknown08 += ".eva";
  return unknown08.c_str();
}

const char *Extend::eva(const char *name) {
  unknown08 = name;
  unknown08 += ".eva";
  return unknown08.c_str();
}

const char *Extend::effeva(const char *name) {
  unknown08 = name;
  unknown08 += "_eff.eva";
  return unknown08.c_str();
}

const char *Extend::efb(const char *name) {
  unknown08 = name;
  unknown08 += ".wiefb";
  return unknown08.c_str();
}

const char *Extend::lgt(const char *name) {
  unknown08 = name;
  unknown08 += ".wilgt";
  return unknown08.c_str();
}

const char *Extend::wav(const char *name) {
  unknown08 = name;
  unknown08 += ".nop";
  return unknown08.c_str();
}

const char *Extend::acb(const char *name) {
  unknown08 = name;
  unknown08 += ".acb";
  return unknown08.c_str();
}

const char *Extend::lip(const char *name) {
  unknown08 = name;
  unknown08 += ".lip";
  return unknown08.c_str();
}

const char *Extend::xxlip(const char *name) {
  unknown08 = name;
  unknown08 += ".wilip";
  return unknown08.c_str();
}

const char *Extend::evpa(const char *name) {
  unknown08 = name;
  unknown08 += ".evpa";
  return unknown08.c_str();
}

const char *Extend::pack_efb(const char *name) {
  unknown08 = name;
  unknown08 += "_pack.wiefb";
  return unknown08.c_str();
}

const char *Extend::sar(const char *name) {
  unknown08 = name;
  unknown08 += ".sar";
  return unknown08.c_str();
}

const char *Extend::webm(const char *name) {
  unknown08 = name;
  unknown08 += ".webm";
  return unknown08.c_str();
}

const char *Extend::dirname(const char *path) {
  static mm::mtl::FixStr<256> s_dirname;
  const char *separator = __builtin_strrchr(path, '\\');
  if (separator == nullptr) {
    separator = __builtin_strrchr(path, '/');
  }
  if (separator != nullptr) {
    s_dirname.assign(path, separator - path);
    path = s_dirname.c_str();
  }
  return path;
}

const char *Extend::filename(const char *path) {
  const char *separator = __builtin_strrchr(path, '\\');
  if (separator != nullptr) {
    return separator + 1;
  }
  separator = __builtin_strrchr(path, '/');
  return separator != nullptr ? separator + 1 : path;
}

const char *Extend::replaceString(const char *string, const char *from, const char *to) {
  static char s_buffer[256];
  __builtin_memset(s_buffer, 0, sizeof(s_buffer));
  char *out = s_buffer;
  while (*string != '\0') {
    if (__builtin_memcmp(string, from, __builtin_strlen(from)) == 0) {
      __builtin_memcpy(out, to, __builtin_strlen(to));
      string += __builtin_strlen(from);
      out += __builtin_strlen(to);
    } else {
      *out++ = *string++;
    }
  }
  return s_buffer;
}

} // namespace event
