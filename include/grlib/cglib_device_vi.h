#pragma once
#include <stddef.h>

#include "types.h"

namespace nn {
namespace vi {
class Display;
class Layer;
} // namespace vi
} // namespace nn

namespace grlib {

class CGLibDeviceVI {
public:
  CGLibDeviceVI();
  ~CGLibDeviceVI();
  void init();
  void release();
  void update();

  void *unknown00;            // Inferred role: native window; original member name unknown.
  nn::vi::Display *unknown08; // Inferred role: default display; original member name unknown.
  nn::vi::Layer *unknown10;   // Inferred role: layer; original member name unknown.
  u32 unknown18;              // Inferred role: width; original member name unknown.
  u32 unknown1c;              // Inferred role: height; original member name unknown.
};

static_assert(offsetof(CGLibDeviceVI, unknown08) == 0x08, "");
static_assert(offsetof(CGLibDeviceVI, unknown10) == 0x10, "");
static_assert(offsetof(CGLibDeviceVI, unknown18) == 0x18, "");
static_assert(offsetof(CGLibDeviceVI, unknown1c) == 0x1c, "");
static_assert(sizeof(CGLibDeviceVI) == 0x20, "");

} // namespace grlib
