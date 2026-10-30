#pragma once
#include <stddef.h>

#include "types.h"

namespace nn {
class Result;
} // namespace nn

namespace ml {
enum LangType : int;

class ErrorApplet {
public:
  struct Config {
    u32 unknown00;         // Inferred role: application error code; original member name unknown.
    const char *unknown08; // Inferred role: dialog message; original member name unknown.
    const char *unknown10; // Inferred role: full screen message; original member name unknown.
    LangType unknown18;    // Inferred role: message language; original member name unknown.
  };

  static bool showApplet(const Config &config);
};

static_assert(offsetof(ErrorApplet::Config, unknown08) == 0x08, "");
static_assert(offsetof(ErrorApplet::Config, unknown10) == 0x10, "");
static_assert(offsetof(ErrorApplet::Config, unknown18) == 0x18, "");
static_assert(sizeof(ErrorApplet::Config) == 0x20, "");

class SystemErrorApplet {
public:
  static bool showApplet(nn::Result &result);
};

} // namespace ml
