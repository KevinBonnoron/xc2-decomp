#pragma once
#include <stddef.h>

#include "nn/result.h"
#include "types.h"

// Controller support applet of the SDK. The type and function names come from the import of the game
// nn::hid::ShowControllerSupport(nn::hid::ControllerSupportResultInfo*, nn::hid::ControllerSupportArg const&);
// the layouts come from the stack layout of ml::ControllerApplet::showApplet. The member names are unknown.

namespace nn {
namespace util {

// Public SDK name, as in open-ead nnheaders include/nn/util/MathTypes.h (https://github.com/open-ead/nnheaders).
struct Color4u8Type {
  u8 unknown00[4]; // Inferred role: RGBA components; original member name unknown.
};

} // namespace util

namespace hid {

struct ControllerSupportArg {
  s8 unknown00;                    // Inferred role: minimum player count; original member name unknown.
  s8 unknown01;                    // Inferred role: maximum player count; original member name unknown.
  bool unknown02;                  // Inferred role: take over connection enable; original member name unknown.
  bool unknown03;                  // Inferred role: left justify enable; original member name unknown.
  bool unknown04;                  // Inferred role: permit joy dual enable; original member name unknown.
  bool unknown05;                  // Inferred role: single mode enable; original member name unknown.
  bool unknown06;                  // Inferred role: identification color enable; original member name unknown.
  util::Color4u8Type unknown07[4]; // Inferred role: identification colors; original member name unknown.
  bool unknown17;                  // Inferred role: explain text enable; original member name unknown.
  char unknown18[4][0x81];         // Inferred role: explain texts; original member name unknown.

  // Inferred role: sets the default arguments; original name unknown.
  void unknown001() {
    unknown00 = 0;
    unknown01 = 4;
    unknown02 = true;
    unknown03 = true;
    unknown04 = true;
    unknown05 = false;
    unknown06 = false;
    unknown17 = false;
  }
};

static_assert(offsetof(ControllerSupportArg, unknown07) == 0x07, "");
static_assert(offsetof(ControllerSupportArg, unknown17) == 0x17, "");
static_assert(offsetof(ControllerSupportArg, unknown18) == 0x18, "");

struct ControllerSupportResultInfo {
  s8 unknown00;  // Inferred role: player count; original member name unknown.
  u32 unknown04; // Inferred role: selected npad id; original member name unknown.
};

static_assert(offsetof(ControllerSupportResultInfo, unknown04) == 0x04, "");

Result ShowControllerSupport(ControllerSupportResultInfo *resultInfo, const ControllerSupportArg &arg);

} // namespace hid
} // namespace nn
