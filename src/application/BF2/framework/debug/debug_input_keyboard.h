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

class InputCallback {
public:
  virtual ~InputCallback() {}
  virtual void onEnter() = 0;
  virtual void onLeave() = 0;
  virtual void onDecide(const char *command) = 0;
};

class IDebugInput {
public:
  virtual ~IDebugInput() {}
  // Inferred role: non-virtual update entry calling updateImpl; original name unknown.
  void unknown001(InputCallback *callback) { updateImpl(callback); }
  // Inferred role: non-virtual render entry calling renderImpl, which orders the argument before the vtable load; original name unknown.
  void unknown002(const mm::Rect<int> &rect) { renderImpl(rect); }
  virtual void updateImpl(InputCallback *callback) = 0;
  virtual void renderImpl(const mm::Rect<int> &rect) = 0;
};

class DebugInputKeyboard : public IDebugInput {
public:
  static const u32 HISTORY_UNKNOWN_32 = 32; // Inferred role: maximum size of the input history; original name unknown.

  DebugInputKeyboard();
  ~DebugInputKeyboard() override;
  void updateImpl(InputCallback *callback) override;
  void renderImpl(const mm::Rect<int> &rect) override;

  bool unknown08;                                                            // Inferred role: input active; original member name unknown.
  bool unknown09;                                                            // Inferred role: browsing history; original member name unknown.
  size_t unknown10;                                                          // Inferred role: history index; original member name unknown.
  mm::mtl::FixStr<256> unknown18;                                            // Inferred role: input line; original member name unknown.
  mm::mtl::FixStr<256> unknown11c;                                           // Inferred role: saved input line; original member name unknown.
  int unknown220;                                                            // Inferred role: cursor position; original member name unknown.
  int unknown224;                                                            // Inferred role: saved cursor position; original member name unknown.
  u32 unknown228;                                                            // Inferred role: blink counter; original member name unknown.
  mm::mtl::FixedVector<mm::mtl::FixStr<256>, HISTORY_UNKNOWN_32> unknown230; // Inferred role: history; original member name unknown.
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
