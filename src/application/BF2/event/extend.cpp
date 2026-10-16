#include "event/extend.h"

namespace event {

const char *Extend::mdo(const char *name) {
  path = name;
  path += ".wimdo";
  return path.c_str();
}

const char *Extend::arc(const char *name) {
  path = name;
  path += ".arc";
  return path.c_str();
}

const char *Extend::anm(const char *name) {
  path = name;
  path += ".anm";
  return path.c_str();
}

const char *Extend::anm2eva(const char *name) {
  path = name;
  const char *found = __builtin_strstr(path.c_str(), ".anm");
  if (found != nullptr) {
    path.erase(found - path.c_str(), 4);
  }
  path += ".eva";
  return path.c_str();
}

const char *Extend::eva(const char *name) {
  path = name;
  path += ".eva";
  return path.c_str();
}

const char *Extend::effeva(const char *name) {
  path = name;
  path += "_eff.eva";
  return path.c_str();
}

const char *Extend::efb(const char *name) {
  path = name;
  path += ".wiefb";
  return path.c_str();
}

const char *Extend::lgt(const char *name) {
  path = name;
  path += ".wilgt";
  return path.c_str();
}

const char *Extend::wav(const char *name) {
  path = name;
  path += ".nop";
  return path.c_str();
}

const char *Extend::acb(const char *name) {
  path = name;
  path += ".acb";
  return path.c_str();
}

const char *Extend::lip(const char *name) {
  path = name;
  path += ".lip";
  return path.c_str();
}

const char *Extend::xxlip(const char *name) {
  path = name;
  path += ".wilip";
  return path.c_str();
}

const char *Extend::evpa(const char *name) {
  path = name;
  path += ".evpa";
  return path.c_str();
}

const char *Extend::pack_efb(const char *name) {
  path = name;
  path += "_pack.wiefb";
  return path.c_str();
}

const char *Extend::sar(const char *name) {
  path = name;
  path += ".sar";
  return path.c_str();
}

const char *Extend::webm(const char *name) {
  path = name;
  path += ".webm";
  return path.c_str();
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
