#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
template <typename T> struct Rect;
} // namespace mm

namespace fw {
namespace debug {

class InputCallback;

class DebugInputKeyboard {
public:
  static const u32 HISTORY_MAX = 32;

  DebugInputKeyboard();
  virtual ~DebugInputKeyboard();
  virtual void updateImpl(InputCallback *callback);
  virtual void renderImpl(const mm::Rect<int> &rect);

  bool unknown08;                                                     // Inferred role: input active; original member name unknown.
  bool unknown09;                                                     // Inferred role: browsing history; original member name unknown.
  size_t unknown10;                                                   // Inferred role: history index; original member name unknown.
  mm::mtl::FixStr<256> unknown18;                                     // Inferred role: input line; original member name unknown.
  mm::mtl::FixStr<256> unknown11c;                                    // Inferred role: saved input line; original member name unknown.
  int unknown220;                                                     // Inferred role: cursor position; original member name unknown.
  int unknown224;                                                     // Inferred role: saved cursor position; original member name unknown.
  u32 unknown228;                                                     // Inferred role: blink counter; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixStr<256>, HISTORY_MAX> unknown230; // Inferred role: history; original member name unknown.
};

static_assert(offsetof(DebugInputKeyboard, unknown08) == 0x08, "");
static_assert(offsetof(DebugInputKeyboard, unknown10) == 0x10, "");
static_assert(offsetof(DebugInputKeyboard, unknown18) == 0x18, "");
static_assert(offsetof(DebugInputKeyboard, unknown11c) == 0x11c, "");
static_assert(offsetof(DebugInputKeyboard, unknown220) == 0x220, "");
static_assert(offsetof(DebugInputKeyboard, unknown228) == 0x228, "");
static_assert(offsetof(DebugInputKeyboard, unknown230) == 0x230, "");
static_assert(sizeof(DebugInputKeyboard) == 0x22b8, "");

} // namespace debug
} // namespace fw
